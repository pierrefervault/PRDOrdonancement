#include "plnemip2.h"

int resolvePlneMip2(string fichierInstance, string fichierResultat)
{
    //Déclaration de l'environnement
    IloEnv env;
    //  try {

    cout << fichierInstance << endl;
    cout << fichierResultat << endl;

    //On cherche à lire le fichier, si ce n'est pas possible on l'indique
    std::ifstream f(fichierInstance);
    if (!f)
    {
        cout << fichierInstance <<" invalid file" << endl;
    }


    //On déclare un modèle qui nous servira à générer notre solution avec différentes contraintes
    IloModel model(env);
    IloInt i, m;
    //Nous déclarons le nombre de jobs, de ressources et de machines selon ce qu'on a lu dans le fichier
    IloInt nb_job , nb_ressources, nb_machines ;
    f >> nb_job >> nb_ressources >> nb_machines;

    //cout << "nb_job : " << nb_job << " nb_ressources : " << nb_ressources << endl;
    // cout << endl;
    IntMatrix cap_ressources (env, nb_ressources);

    //Ici on créer un tableau contenant la capacité en ressources pour la ressource r de chaque machine
    for (int r=0; r < nb_ressources ; r++)
    {
        cap_ressources[r] = IloIntArray (env, nb_machines);
        f >> cap_ressources[r];
        //cout << "Nombre de machines : " << nb_machines << endl;
        for (int machine=0; machine < nb_machines ; machine++)
        {
            f >> cap_ressources[r][machine];
            cout <<  cap_ressources[r][machine] << " ";
        }
    }

    //cout << "Nombre de jobs : " << nb_job << endl;

    IloIntArray S_j (env, nb_job);
    IloIntArray F_j (env, nb_job);
    IloIntArray ID_j (env, nb_job);
    IloInt id , s_i , f_i ;
    IloInt cmax=0;


    //Tableau d'évenement eh

    NumMatrix eh(env,nb_job*2);

    //Ici, on mets à jour les instant de début et de fin pour chaque job
    for (i=0 ; i < nb_job ; i++)
    {
        f >> id >> s_i >> f_i ;

        S_j[i]=s_i;
        F_j[i]=f_i;
        ID_j[i]=id;

        eh[(2*i)] = IloNumArray (env,4);

        eh[(2*i)][0] = S_j[i];
        eh[(2*i)][1] = i;
        eh[(2*i)][2] = 1;
        eh[(2*i)][3] = F_j[i];

        eh[1 + (2*i)] = IloNumArray (env,4);

        eh[1 + (2*i)][0] = F_j[i];
        eh[1 + (2*i)][1] = i;
        eh[1 + (2*i)][2] = 0;
        eh[1 + (2*i)][3] = F_j[i];


        if (cmax <= f_i ) cmax = f_i;


        //cout << id << " " << s_i << " " << f_i << " " << endl;
    }


    cout << endl;

    for (i=0; i < (nb_job * 2); i++){
        cout << eh[i][0] << " " << eh[i][1] << " " << eh[i][2] << " " << endl;
    }

    //Trie à bulle du tableau d'événement eh
    bool tab_en_ordre = false;
    int taille = (nb_job * 2);
    while(!tab_en_ordre)
    {
        tab_en_ordre = true;
        for(int i=0 ; i < taille-1 ; i++)
        {
            if(eh[i][0] > eh[i+1][0])
            {
                swap(eh[i],eh[i+1]);
                tab_en_ordre = false;
            }
            else {
                if(eh[i][0] == eh[i+1][0])
                {
                    if(eh[i][3] > eh[i+1][3])
                    {
                        swap(eh[i],eh[i+1]);
                        tab_en_ordre = false;
                    }
                }
            }
        }
        taille--;
    }

    //cout << endl;

    for (i=0; i < (nb_job * 2); i++){
        cout << eh[i][0] << " " << eh[i][1] << " " << eh[i][2] << " " << eh[i][3] << endl;
    }

    //Algorithme de création de sous-ensembles maximaux

    map<int,vector<int>> Jk = getSubset(eh, nb_job);

    for(std::map<int,vector<int>>::iterator it = Jk.begin() ; it != Jk.end() ; ++it){
        cout << it->first << endl;
        for(std::vector<int>::iterator itVect = it->second.begin() ; itVect != it->second.end() ; ++itVect){
            cout << *itVect << " ";
        }
        cout << endl;
    }

    //cout <<"cmax : " <<cmax << endl;*

    //Ici, on créer le tableau ou est stocké pour chaque job i la valeur pour la ressource r associée au job
    NumMatrix C (env,nb_job);
    for( i=0 ; i<nb_job ; i++)
    {
        IloInt cap;
        C[i] = IloNumArray  (env,nb_ressources);
        for (int r=0; r < nb_ressources ; r++)
        {
            f >> cap;
            C[i][r]=cap;
            //	cout << C[i][r] << " ";
        }

        //	cout << endl;
    }

    //Ici on créer les variables X qui valent 1 si le jobs i est exécuté sur une machine m
    NumVarMatrix X(env,nb_job) ;
    for (i=0 ; i < nb_job ; i++)
    {
        X[i] = IloNumVarArray (env,nb_machines) ;
        for (m=0 ; m < nb_machines ; m++)
        {
            X[i][m]=IloNumVar(env,0,1,ILOINT);
        }
    }

    //Ici on ajoute la contrainte qui vérifie que si un jobs est exécuté,
    //les valeurs de ressources sur la machine m ne sont pas dépassée
   for (int r=0; r < nb_ressources ; r++) {
        for (int m= 0 ; m < nb_machines ; m++) {
            for (unsigned int h= 0 ; h < Jk.size() ; h++) {
                IloExpr capacite_ressources(env);
                for (unsigned int l=0 ; l < Jk[h].size() ; l++) {
                    cout << "Job : " << Jk[h][l] << " ";
                    capacite_ressources += X[(Jk[h][l])][m] * C[(Jk[h][l])][r] ;
                }
                cout << endl;
                model.add( capacite_ressources <= cap_ressources[r][m] ) ;
            }
        }
    }

    //Ici on ajoute la contrainte qui vérifie qu'un job ne peut être exécuter au maximum que sur une seule machine
    for( i=0 ; i<nb_job ; i++)
    {
        IloExpr unicite_job(env);
        for (int m= 0 ; m < nb_machines ; m++) {
            unicite_job +=  X[i][m];
        }
        model.add( unicite_job <= 1 ) ;
    }


    IloExpr numberJob(env);

    for( i=0 ; i<nb_job ; i++)
    {
        for (int m= 0 ; m < nb_machines ; m++) {
            numberJob +=  X[i][m];
        }
    }

    IloObjective objective = IloMaximize(env,numberJob);
    model.add(objective);

    //----------------------------------------------------------------------------
    IloCplex cplex(env);
    //IloTimer timer(env);

    cplex.extract(model);
    cplex.exportModel("toto.lp");
    cplex.setParam(IloCplex::Param::Emphasis::MIP, 4);
    //cplex.setParam(IloCplex::Param::ClockType,0);

    //char output_file_name[80];
    // sprintf(output_file_name,"sol-%d-%d%s",nb_job,nb_ressources ,".txt");
    //ofstream output_file(output_file_name);
    ofstream output_file(fichierResultat,ios::app);

    double Avant = cplex.getCplexTime();
    if (cplex.solve()) {



        cout << "Solution status: " << cplex.getStatus() << endl;
        cout << " Optimal Value = " << cplex.getObjValue() << endl;
        //cout << " temps écouler = " <<cplex.getCplexTime() << endl;
        //cout << " temps écouler = " << cplex.getTime() << endl;

        output_file << "Instance \t: " << fichierInstance << endl;
        output_file << "Solution status: " << cplex.getStatus() << endl;
        output_file << " Optimal Value = " << cplex.getObjValue() << endl;
        //output_file << " Optimal Value = " << cplex.getTime() << endl;

        for (int m= 0 ; m < nb_machines ; m++) {
            for( i=0 ; i<nb_job ; i++){
                if (cplex.getValue(X[i][m])>=0.9)
                {
                    // cout << "VM_" << i+1 << " : " << cplex.getValue(X[i]) << "[ "  ;
                    cout << "Machine_"<< m+1 << " VM_" << i+1 << " : [ "  ;

                    for (int t= S_j[i] ; t < F_j[i] ; t++) {
                        cout << t << " " ;
                    }

                    cout << F_j[i] << " ]" <<endl;
                }
            }
        }

        cout << endl;



    }

    double Apres = cplex.getCplexTime();

    output_file << "temps écoulé: " << (double)(Apres - Avant)  << " seconds" << endl;

    ///////////////////////////////////////////////////

    /* }

catch (IloException& ex) {
    cerr << "Error: " << ex << endl;
}
catch (...) {
    cerr << "Error" << endl;
}
    env.end();*/
    return 0;
}

map<int,vector<int>> getSubset(NumMatrix eh, int nb_job){

    map<int,vector<int>> Jk;

    //numero du sous-ensemble maximal
    int k = 0;

    //Permet de savoir si on doit encore enlever des jobs du sous ensembles après une première supression
    int inc = 0;

    //Nombre d'événement de type S_j parcourus
    int nbStartEvent = 0;

    for(int h = 0 ; h < (nb_job * 2); h++){

        //Si l'événement est de type S_j, on ajoute le job correspondant au sous-ensemble k
        if(eh[h][2] == 1){
            nbStartEvent++;
            Jk[k].push_back(eh[h][1]);

            //On spécifie que le sous-ensemble est maximal
            inc = 0;
           // cout << "Startevent :"<< nbStartEvent << " SousEnsembles : " << k << " Job : " << eh[h][1] << endl;
        }
        else{

            //Si on a parcouru l'ensemble des événements de type S_j on retourne les sous-ensembles
            if(nbStartEvent == nb_job){
                return Jk;
            }

            else{

                //Si le sous ensembles est maximal et que l'on parcoure un événement de type F_j
                if(inc == 0){

                    //On considère le nouveau sous-ensemble non maximal
                    inc = 1;
                    k++;

                    //Le nouveau sous-ensemble corespond à l'ancien où l'on exclu le jobs correspondant à l'événement F_j
                    Jk[k] = Jk[k-1];
                    for (std::vector<int>::iterator it = Jk[k].begin(); it != Jk[k].end();) {
                        if (*it == eh[h][1]) {
                            it = Jk[k].erase(it);
                        } else {
                            ++it;
                        }
                    }
                }

                //Si le sous ensembles n'est pas maximal et que l'on parcoure un événement de type F_j
                else{

                    //On enlève le jobs correspondant à l'événement F_j du sous-ensemble

                    for (std::vector<int>::iterator it = Jk[k].begin(); it != Jk[k].end();) {
                        if (*it == eh[h][1]) {
                            it = Jk[k].erase(it);
                        } else {
                            ++it;
                        }
                    }
                }
            }
        }
    }
}
