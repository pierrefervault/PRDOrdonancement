#include "methodeexacte.h"

MethodeExacte::MethodeExacte()
{

}

int MethodeExacte::resolutionPlneMip1(string fichierInstance, string fichierResultat)
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
        return 0;
    }


    //On déclare un modèle qui nous servira à générer notre solution avec différentes contraintes
    IloModel model(env);
    IloInt i, m;
    //Nous déclarons le nombre de jobs, de ressources et de machines selon ce qu'on a lu dans le fichier
    IloInt nbrJobs , nbrRessources, nbrMachines ;
    f >> nbrJobs >> nbrRessources >> nbrMachines;

    //cout << "nbrJobs : " << nbrJobs << " nbrRessources : " << nbrRessources << endl;
    // cout << endl;
    IntMatrix capRessources (env, nbrRessources);

    //Ici on créer un tableau contenant la capacité en ressources pour la ressource r de chaque machine
    for (int r=0; r < nbrRessources ; r++)
    {
        capRessources[r] = IloIntArray (env, nbrMachines);
        f >> capRessources[r];
        //cout << "Nombre de machines : " << nbrMachines << endl;
        for (int machine=0; machine < nbrMachines ; machine++)
        {
            f >> capRessources[r][machine];
            cout <<  capRessources[r][machine] << " ";
        }
    }

    //cout << "Nombre de jobs : " << nbrJobs << endl;

    IloIntArray sj (env, nbrJobs);
    IloIntArray fj (env, nbrJobs);
    IloInt id , s_i , f_i ;
    IloInt cmax=0;

    //Ici, on mets à jour les instant de début (Sj) et de fin (fj) pour chaque job
    for (i=0 ; i < nbrJobs ; i++)
    {
        f >> id >> s_i >> f_i ;

        sj[i]=s_i;
        fj[i]=f_i;


        if (cmax <= f_i ) cmax = f_i;


        //cout << id << " " << s_i << " " << f_i << " " << endl;
    }
    //cout << endl;

    //cout <<"cmax : " <<cmax << endl;



    //Ici, on créer le tableau ou est stocké pour chaque job i la valeur pour la ressource r associée au job
    NumMatrix C (env,nbrJobs);
    for( i=0 ; i<nbrJobs ; i++)
    {
        IloInt cap;
        C[i] = IloNumArray  (env,nbrRessources);
        for (int r=0; r < nbrRessources ; r++)
        {
            f >> cap;
            C[i][r]=cap;
            //	cout << C[i][r] << " ";
        }

        //	cout << endl;
    }


    //Ici on créer les variables Y qui valent 1 si le jobs i est exécuté à l'instant t sur une machine m

    IloArray<NumVarMatrix> Y(env,nbrJobs) ;
    for (i=0 ; i < nbrJobs ; i++)
    {
        Y[i]= NumVarMatrix(env,nbrMachines);
        for (int machine= 0 ; machine < nbrMachines ; machine++)
        {
            Y[i][machine] = IloNumVarArray (env,cmax+1);
            for (int t= 0 ; t < cmax+1 ; t++)
            {
                Y[i][machine][t]=IloNumVar(env,0,1,ILOINT);
            }
        }
    }

    //Ici on créer les variables X qui valent 1 si le jobs i est exécuté sur une machine m

    NumVarMatrix X(env,nbrJobs) ;
    for (i=0 ; i < nbrJobs ; i++)
    {
        X[i] = IloNumVarArray (env,nbrMachines) ;
        for (m=0 ; m < nbrMachines ; m++)
        {
            X[i][m]=IloNumVar(env,0,1,ILOINT);
        }
    }


    //Ici on ajoute la contrainte qui vérifie que si un jobs est exécuté,
    //il est exécuté durant la période [S[i],F[i][
    for (i=0 ; i < nbrJobs ; i++) {


        for (int m= 0 ; m < nbrMachines ; m++) {
            IloExpr temps_total_execution_job(env);
            for (int t=sj[i] ; t < fj[i] ; t++) {
                temps_total_execution_job +=  Y[i][m][t];
            }
            model.add(temps_total_execution_job ==  (fj[i]-sj[i])*X[i][m]);
        }
    }

    //Ici on ajoute la contrainte qui vérifie que si un jobs est exécuté,
    //pour chaque t les valeurs de ressources sur la machine m ne sont pas dépassée
    for (int r=0; r < nbrRessources ; r++) {
        for (int t= 0 ; t < cmax+1 ; t++) {
            for (int m= 0 ; m < nbrMachines ; m++) {
                IloExpr capacite_ressources(env);
                for (i=0 ; i < nbrJobs ; i++) {

                    capacite_ressources += Y[i][m][t] * C[i][r] ;

                }
                model.add( capacite_ressources <= capRessources[r][m] ) ;
            }
        }
    }

    //Ici on ajoute la contrainte qui vérifie qu'un job ne peut être exécuter au maximum que sur une seule machine
    for( i=0 ; i<nbrJobs ; i++)
    {
        IloExpr unicite_job(env);
        for (int m= 0 ; m < nbrMachines ; m++) {
            unicite_job +=  X[i][m];
        }
        model.add( unicite_job <= 1 ) ;
    }


    //Ici, on ajoute la fonction objective qui correspond à maximiser le nombre de jobs ordonnancés
    IloExpr numberJob(env);

    for( i=0 ; i<nbrJobs ; i++)
    {
        for (int m= 0 ; m < nbrMachines ; m++) {
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
    // sprintf(output_file_name,"sol-%d-%d%s",nbrJobs,nbrRessources ,".txt");
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

        for (int m= 0 ; m < nbrMachines ; m++) {
            for( i=0 ; i<nbrJobs ; i++){
                if (cplex.getValue(X[i][m])>=0.9)
                {
                    // cout << "VM_" << i+1 << " : " << cplex.getValue(X[i]) << "[ "  ;
                    cout << "Machine_"<< m+1 << " VM_" << i+1 << " : [ "  ;

                    for (int t=sj[i] ; t < fj[i] ; t++) {

                        if (cplex.getValue(Y[i][m][t]) >= 0.9)
                        {
                            cout << t << " " ;
                        }
                    }

                    cout << fj[i] << " ]" <<endl;
                }
            }
        }

        cout << endl;



    }

    double Apres = cplex.getCplexTime();

    output_file << "temps écoulé: " << (double)(Apres - Avant)  << " seconds" << endl;

    ///////////////////////////////////////////////////

    int optimal = cplex.getObjValue();

    /* }

catch (IloException& ex) {
    cerr << "Error: " << ex << endl;
}
catch (...) {
    cerr << "Error" << endl;
}*/
    env.end();
    return optimal;
}

int MethodeExacte::resolutionPlneMip2(string fichierInstance, string fichierResultat)
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
        return 0;
    }


    //On déclare un modèle qui nous servira à générer notre solution avec différentes contraintes
    IloModel model(env);
    IloInt i, m;
    //Nous déclarons le nombre de jobs, de ressources et de machines selon ce qu'on a lu dans le fichier
    IloInt nbrJobs , nbrRessources, nbrMachines ;
    f >> nbrJobs >> nbrRessources >> nbrMachines;

    //cout << "nbrJobs : " << nbrJobs << " nbrRessources : " << nbrRessources << endl;
    // cout << endl;
    IntMatrix capRessources (env, nbrRessources);

    //Ici on créer un tableau contenant la capacité en ressources pour la ressource r de chaque machine
    for (int r=0; r < nbrRessources ; r++)
    {
        capRessources[r] = IloIntArray (env, nbrMachines);
        f >> capRessources[r];
        //cout << "Nombre de machines : " << nbrMachines << endl;
        for (int machine=0; machine < nbrMachines ; machine++)
        {
            f >> capRessources[r][machine];
            cout <<  capRessources[r][machine] << " ";
        }
    }

    //cout << "Nombre de jobs : " << nbrJobs << endl;

    IloIntArray sj (env, nbrJobs);
    IloIntArray fj (env, nbrJobs);
    IloIntArray idj (env, nbrJobs);
    IloInt id , s_i , f_i ;
    IloInt cmax=0;


    //Tableau d'évenement eh

    NumMatrix eh(env,nbrJobs*2);

    //Ici, on mets à jour les instant de début et de fin pour chaque job
    for (i=0 ; i < nbrJobs ; i++)
    {
        f >> id >> s_i >> f_i ;

        sj[i]=s_i;
        fj[i]=f_i;
        idj[i]=id;

        eh[(2*i)] = IloNumArray (env,4);

        eh[(2*i)][0] =sj[i];
        eh[(2*i)][1] = i;
        eh[(2*i)][2] = 1;
        eh[(2*i)][3] = fj[i];

        eh[1 + (2*i)] = IloNumArray (env,4);

        eh[1 + (2*i)][0] = fj[i];
        eh[1 + (2*i)][1] = i;
        eh[1 + (2*i)][2] = 0;
        eh[1 + (2*i)][3] = fj[i];


        if (cmax <= f_i ) cmax = f_i;


        //cout << id << " " << s_i << " " << f_i << " " << endl;
    }


    cout << endl;

    for (i=0; i < (nbrJobs * 2); i++){
        cout << eh[i][0] << " " << eh[i][1] << " " << eh[i][2] << " " << endl;
    }

    //Trie à bulle du tableau d'événement eh
    bool tab_en_ordre = false;
    int taille = (nbrJobs * 2);
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

    for (i=0; i < (nbrJobs * 2); i++){
        cout << eh[i][0] << " " << eh[i][1] << " " << eh[i][2] << " " << eh[i][3] << endl;
    }

    //Algorithme de création de sous-ensembles maximaux

    map<int,vector<int>> Jk = getSousEnsemblesMaximaux(eh, nbrJobs);

    for(std::map<int,vector<int>>::iterator it = Jk.begin() ; it != Jk.end() ; ++it){
        cout << it->first << endl;
        for(std::vector<int>::iterator itVect = it->second.begin() ; itVect != it->second.end() ; ++itVect){
            cout << *itVect << " ";
        }
        cout << endl;
    }

    //cout <<"cmax : " <<cmax << endl;*

    //Ici, on créer le tableau ou est stocké pour chaque job i la valeur pour la ressource r associée au job
    NumMatrix C (env,nbrJobs);
    for( i=0 ; i<nbrJobs ; i++)
    {
        IloInt cap;
        C[i] = IloNumArray  (env,nbrRessources);
        for (int r=0; r < nbrRessources ; r++)
        {
            f >> cap;
            C[i][r]=cap;
            //	cout << C[i][r] << " ";
        }

        //	cout << endl;
    }

    //Ici on créer les variables X qui valent 1 si le jobs i est exécuté sur une machine m
    NumVarMatrix X(env,nbrJobs) ;
    for (i=0 ; i < nbrJobs ; i++)
    {
        X[i] = IloNumVarArray (env,nbrMachines) ;
        for (m=0 ; m < nbrMachines ; m++)
        {
            X[i][m]=IloNumVar(env,0,1,ILOINT);
        }
    }

    //Ici on ajoute la contrainte qui vérifie que si un jobs est exécuté,
    //les valeurs de ressources sur la machine m ne sont pas dépassée
   for (int r=0; r < nbrRessources ; r++) {
        for (int m= 0 ; m < nbrMachines ; m++) {
            for (unsigned int h= 0 ; h < Jk.size() ; h++) {
                IloExpr capacite_ressources(env);
                for (unsigned int l=0 ; l < Jk[h].size() ; l++) {
                    cout << "Job : " << Jk[h][l] << " ";
                    capacite_ressources += X[(Jk[h][l])][m] * C[(Jk[h][l])][r] ;
                }
                cout << endl;
                model.add( capacite_ressources <= capRessources[r][m] ) ;
            }
        }
    }

    //Ici on ajoute la contrainte qui vérifie qu'un job ne peut être exécuter au maximum que sur une seule machine
    for( i=0 ; i<nbrJobs ; i++)
    {
        IloExpr unicite_job(env);
        for (int m= 0 ; m < nbrMachines ; m++) {
            unicite_job +=  X[i][m];
        }
        model.add( unicite_job <= 1 ) ;
    }


    IloExpr numberJob(env);

    for( i=0 ; i<nbrJobs ; i++)
    {
        for (int m= 0 ; m < nbrMachines ; m++) {
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
    // sprintf(output_file_name,"sol-%d-%d%s",nbrJobs,nbrRessources ,".txt");
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

        for (int m= 0 ; m < nbrMachines ; m++) {
            for( i=0 ; i<nbrJobs ; i++){
                if (cplex.getValue(X[i][m])>=0.9)
                {
                    // cout << "VM_" << i+1 << " : " << cplex.getValue(X[i]) << "[ "  ;
                    cout << "Machine_"<< m+1 << " VM_" << i+1 << " : [ "  ;

                    for (int t=sj[i] ; t < fj[i] ; t++) {
                        cout << t << " " ;
                    }

                    cout << fj[i] << " ]" <<endl;
                }
            }
        }

        cout << endl;



    }

    double Apres = cplex.getCplexTime();

    output_file << "temps écoulé: " << (double)(Apres - Avant)  << " seconds" << endl;

    ///////////////////////////////////////////////////

    int optimal = cplex.getObjValue();

    /* }

catch (IloException& ex) {
    cerr << "Error: " << ex << endl;
}
catch (...) {
    cerr << "Error" << endl;
}*/
    env.end();
    return optimal;
}

map<int,vector<int>> MethodeExacte::getSousEnsemblesMaximaux(NumMatrix eh, int nbrJobs){

    map<int,vector<int>> Jk;

    //numero du sous-ensemble maximal
    int k = 0;

    //Permet de savoir si on doit encore enlever des jobs du sous ensembles après une première supression
    int inc = 0;

    //Nombre d'événement de typesj parcourus
    int nbStartEvent = 0;

    for(int h = 0 ; h < (nbrJobs * 2); h++){

        //Si l'événement est de typesj, on ajoute le job correspondant au sous-ensemble k
        if(eh[h][2] == 1){
            nbStartEvent++;
            Jk[k].push_back(eh[h][1]);

            //On spécifie que le sous-ensemble est maximal
            inc = 0;
           // cout << "Startevent :"<< nbStartEvent << " SousEnsembles : " << k << " Job : " << eh[h][1] << endl;
        }
        else{

            //Si on a parcouru l'ensemble des événements de typesj on retourne les sous-ensembles
            if(nbStartEvent == nbrJobs){
                return Jk;
            }

            else{

                //Si le sous ensembles est maximal et que l'on parcoure un événement de type fj
                if(inc == 0){

                    //On considère le nouveau sous-ensemble non maximal
                    inc = 1;
                    k++;

                    //Le nouveau sous-ensemble corespond à l'ancien où l'on exclu le jobs correspondant à l'événement fj
                    Jk[k] = Jk[k-1];
                    for (std::vector<int>::iterator it = Jk[k].begin(); it != Jk[k].end();) {
                        if (*it == eh[h][1]) {
                            it = Jk[k].erase(it);
                        } else {
                            ++it;
                        }
                    }
                }

                //Si le sous ensembles n'est pas maximal et que l'on parcoure un événement de type fj
                else{

                    //On enlève le jobs correspondant à l'événement fj du sous-ensemble

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
