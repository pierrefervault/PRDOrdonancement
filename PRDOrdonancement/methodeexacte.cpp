#include "methodeexacte.h"

/**
 * @brief Constructeur de la classe MethodeExacte
 *
 * @param fichierInstance Le chemin vers le fichier d'instance
 */
MethodeExacte::MethodeExacte(string fichierInstance)
{

    //On cherche à lire le fichier, si ce n'est pas possible on l'indique
    std::ifstream f(fichierInstance);
    if (!f)
    {
        cout << fichierInstance <<" invalid file" << endl;
    }
    this->instance.setFichierInstance(QString::fromStdString(fichierInstance));

    //Nous spécifions en attribut le nombre de jobs, de ressources et de machines selon ce qu'on a lu dans le fichier

    int nbrJobs, nbrRessources, nbrMachines;
    f >> nbrJobs >> nbrRessources >> nbrMachines;

    this->instance.setNbrJobs(nbrJobs);
    this->instance.setNbrRessources(nbrRessources);
    this->instance.setNbrMachines(nbrMachines);

    vector<vector<int>> capRessources;

    //Ici on créer un tableau contenant la capacité en ressources pour la ressource r de chaque machine
    for (int r=0; r < this->instance.getNbrRessources() ; r++)
    {
        vector<int> ressources;
        for (int machine=0; machine < this->instance.getNbrMachines() ; machine++)
        {
            int value;
            f >> value;
            ressources.push_back(value);
        }
        capRessources.push_back(ressources);
    }
    this->instance.setCapRessources(capRessources);

    //cout << "Nombre de jobs : " << nb_job << endl;

    int id , s_i , f_i ;

    vector<int>sj;
    vector<int> fj;

    int horizonMax=0;

    //Ici, on mets à jour les instant de début et de fin pour chaque job
    for (int i=0 ; i < this->instance.getNbrJobs() ; i++)
    {
        f >> id >> s_i >> f_i ;

       sj.push_back(s_i);
        fj.push_back(f_i);


        if (horizonMax <= f_i ) horizonMax = f_i;


        //cout << id << " " << s_i << " " << f_i << " " << endl;
    }

    this->instance.setSj(sj);
    this->instance.setFj(fj);
    this->instance.setHorizonMax(horizonMax);

    //Ici, on créer le tableau ou est stocké pour chaque job i la valeur pour la ressource r associée au job

    vector<vector<int>> tableauRessourcesJobs;

    for(int i=0 ; i<this->instance.getNbrJobs() ; i++)
    {
        vector<int> ressources;

        for (int r=0; r < this->instance.getNbrRessources() ; r++)
        {
            int value;
            f >> value;
            ressources.push_back(value);
        }
        tableauRessourcesJobs.push_back(ressources);
    }
    this->instance.setTableauRessourcesJobs(tableauRessourcesJobs);

}

/**
 * @brief Methode de résolution exacte indéxée temps
 *
 * @param fichierResultat Le fichier où seront stockés les résulats
 * @return int Le nombre de jobs ordonnancés
 */
int MethodeExacte::resolutionPlneMip1(string fichierResultat)
{
    //Déclaration de l'environnement
    IloEnv env;

    IloModel model(env);

    //Ici on créer les variables Y qui valent 1 si le jobs i est exécuté à l'instant t sur une machine m

    IloArray<IloArray<IloNumVarArray>> Y(env,this->instance.getNbrJobs()) ;
    for (int i=0 ; i < this->instance.getNbrJobs() ; i++)
    {
        Y[i]= IloArray<IloNumVarArray>(env,this->instance.getNbrMachines());
        for (int machine= 0 ; machine < this->instance.getNbrMachines() ; machine++)
        {
            Y[i][machine] = IloNumVarArray (env,this->instance.getHorizonMax()+1);
            for (int t= 0 ; t < this->instance.getHorizonMax()+1 ; t++)
            {
                Y[i][machine][t]=IloNumVar(env,0,1,ILOINT);
            }
        }
    }

    //Ici on créer les variables X qui valent 1 si le jobs i est exécuté sur une machine m

    IloArray<IloNumVarArray> X(env,this->instance.getNbrJobs()) ;
    for (int i=0 ; i < this->instance.getNbrJobs() ; i++)
    {
        X[i] = IloNumVarArray (env,this->instance.getNbrMachines()) ;
        for (int m=0 ; m < this->instance.getNbrMachines() ; m++)
        {
            X[i][m]=IloNumVar(env,0,1,ILOINT);
        }
    }


    //Ici on ajoute la contrainte qui vérifie que si un jobs est exécuté,
    //il est exécuté durant la période [S[i],F[i][
    for (int i=0 ; i < this->instance.getNbrJobs() ; i++) {


        for (int m= 0 ; m < this->instance.getNbrMachines() ; m++) {
            IloExpr temps_total_execution_job(env);
            for (int t=this->instance.getSj()[i] ; t < this->instance.getFj()[i] ; t++) {
                temps_total_execution_job +=  Y[i][m][t];
            }
            model.add(temps_total_execution_job ==  (this->instance.getFj()[i]-this->instance.getSj()[i])*X[i][m]);
        }
    }

    //Ici on ajoute la contrainte qui vérifie que si un jobs est exécuté,
    //pour chaque t les valeurs de ressources sur la machine m ne sont pas dépassée
    for (int r=0; r < this->instance.getNbrRessources() ; r++) {
        for (int t= 0 ; t < this->instance.getHorizonMax()+1 ; t++) {
            for (int m= 0 ; m < this->instance.getNbrMachines() ; m++) {
                IloExpr capacite_ressources(env);
                for (int i=0 ; i < this->instance.getNbrJobs() ; i++) {

                    capacite_ressources += Y[i][m][t] * this->instance.getTableauRessourcesJobs()[i][r] ;

                }
                model.add( capacite_ressources <= this->instance.getCapRessources()[r][m] ) ;
            }
        }
    }

    //Ici on ajoute la contrainte qui vérifie qu'un job ne peut être exécuter au maximum que sur une seule machine
    for( int i=0 ; i<this->instance.getNbrJobs() ; i++)
    {
        IloExpr unicite_job(env);
        for (int m= 0 ; m < this->instance.getNbrMachines() ; m++) {
            unicite_job +=  X[i][m];
        }
        model.add( unicite_job <= 1 ) ;
    }


    //Ici, on ajoute la fonction objective qui correspond à maximiser le nombre de jobs ordonnancés
    IloExpr numberJob(env);

    for( int i=0 ; i<this->instance.getNbrJobs() ; i++)
    {
        for (int m= 0 ; m < this->instance.getNbrMachines() ; m++) {
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



        cout << "Solution status:" << cplex.getStatus() << endl;
        cout << " Optimal Value=" << cplex.getObjValue() << endl;
        //cout << " temps écouler = " <<cplex.getCplexTime() << endl;
        //cout << " temps écouler = " << cplex.getTime() << endl;

        output_file << "Instance:" << this->instance.getFichierInstance().toStdString() << endl;
        output_file << "Solution status:" << cplex.getStatus() << endl;
        output_file << " Optimal Value=" << cplex.getObjValue() << endl;
        //output_file << " Optimal Value = " << cplex.getTime() << endl;

        for (int m= 0 ; m < this->instance.getNbrMachines() ; m++) {
            for( int i=0 ; i<this->instance.getNbrJobs() ; i++){
                if (cplex.getValue(X[i][m])>=0.9)
                {
                    // cout << "VM_" << i+1 << " : " << cplex.getValue(X[i]) << "[ "  ;
                    cout << "Machine_"<< m+1 << " VM_" << i+1 << " : [ "  ;

                    for (int t=this->instance.getSj()[i] ; t < this->instance.getFj()[i] ; t++) {

                        if (cplex.getValue(Y[i][m][t]) >= 0.9)
                        {
                            cout << t << " " ;
                        }
                    }

                    cout << this->instance.getFj()[i] << " ]" <<endl;
                }
            }
        }

        cout << endl;



    }

    double Apres = cplex.getCplexTime();

    output_file << "temps écoulé (en secondes):" << (double)(Apres - Avant) << endl;

    output_file << "IdMachine " << "Nombre de jobs ordonnancés" << endl;

    for (int m= 0 ; m < this->instance.getNbrMachines() ; m++) {
        int nb = 0;
        for( int i=0 ; i<this->instance.getNbrJobs() ; i++){
            if (cplex.getValue(X[i][m])>=0.9)
            {
                nb++;
            }
        }
        output_file << m << " " << nb << endl;
    }

    output_file << "IdMachine " << "n°Job " << "Si " << "Fi " << endl;

    for (int m= 0 ; m < this->instance.getNbrMachines() ; m++) {
        for( int i=0 ; i<this->instance.getNbrJobs() ; i++){
            if (cplex.getValue(X[i][m])>=0.9)
            {
                output_file << m << " " << i << " " << this->instance.getSj()[i] << " " << this->instance.getFj()[i] << endl;
            }
        }
    }



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

/**
 * @brief Methode de résolution exacte indéxée jobs
 *
 * @param fichierResultat Le fichier où seront stockés les résulats
 * @return int Le nombre de jobs ordonnancés
 */
int MethodeExacte::resolutionPlneMip2(string fichierResultat)
{
    //Déclaration de l'environnement
    IloEnv env;

    IloModel model(env);

    //On crée le tableau d'événement eh nécessaire à la création des sous-ensembles de jobs maximaux
    vector<vector<int>> eh;
    for (int i=0 ; i < this->instance.getNbrJobs() ; i++)
    {
        vector<int> debut;
        debut.push_back(this->instance.getSj()[i]);
        debut.push_back(i);
        debut.push_back(1);
        debut.push_back(this->instance.getFj()[i]);

        eh.push_back(debut);

        vector<int> fin;
        fin.push_back(this->instance.getFj()[i]);
        fin.push_back(i);
        fin.push_back(0);
        fin.push_back(this->instance.getFj()[i]);

        eh.push_back(fin);
    }

    //Trie à bulle du tableau d'événement eh suivant l'ordre défini par l'algorithme
    bool tab_en_ordre = false;
    int taille = (this->instance.getNbrJobs()*2);
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

    //Algorithme de création de sous-ensembles maximaux

    map<int,vector<int>> Jk = getSousEnsemblesMaximaux(eh, this->instance.getNbrJobs());

    for(std::map<int,vector<int>>::iterator it = Jk.begin() ; it != Jk.end() ; ++it){
        cout << it->first << endl;
        for(std::vector<int>::iterator itVect = it->second.begin() ; itVect != it->second.end() ; ++itVect){
            cout << *itVect << " ";
        }
        cout << endl;
    }

    //Ici on créer les variables X qui valent 1 si le jobs i est exécuté sur une machine m
    IloArray<IloNumVarArray> X(env,this->instance.getNbrJobs()) ;
    for (int i=0 ; i < this->instance.getNbrJobs() ; i++)
    {
        X[i] = IloNumVarArray (env,this->instance.getNbrMachines()) ;
        for (int m=0 ; m < this->instance.getNbrMachines(); m++)
        {
            X[i][m]=IloNumVar(env,0,1,ILOINT);
        }
    }

    //Ici on ajoute la contrainte qui vérifie que si un jobs est exécuté,
    //les valeurs de ressources sur la machine m ne sont pas dépassée
   for (int r=0; r < this->instance.getNbrRessources() ; r++) {
        for (int m= 0 ; m < this->instance.getNbrMachines() ; m++) {
            for (unsigned int h= 0 ; h < Jk.size() ; h++) {
                IloExpr capacite_ressources(env);
                for (unsigned int l=0 ; l < Jk[h].size() ; l++) {
                    cout << "Job : " << Jk[h][l] << " ";
                    capacite_ressources += X[(Jk[h][l])][m] * this->instance.getTableauRessourcesJobs()[(Jk[h][l])][r] ;
                }
                cout << endl;
                model.add( capacite_ressources <= this->instance.getCapRessources()[r][m] ) ;
            }
        }
    }

    //Ici on ajoute la contrainte qui vérifie qu'un job ne peut être exécuter au maximum que sur une seule machine
    for( int i=0 ; i<this->instance.getNbrJobs() ; i++)
    {
        IloExpr unicite_job(env);
        for (int m= 0 ; m < this->instance.getNbrMachines() ; m++) {
            unicite_job +=  X[i][m];
        }
        model.add( unicite_job <= 1 ) ;
    }


    IloExpr numberJob(env);

    for(int i=0 ; i<this->instance.getNbrJobs() ; i++)
    {
        for (int m= 0 ; m < this->instance.getNbrMachines() ; m++) {
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



        cout << "Solution status:" << cplex.getStatus() << endl;
        cout << " Optimal Value=" << cplex.getObjValue() << endl;
        //cout << " temps écouler = " <<cplex.getCplexTime() << endl;
        //cout << " temps écouler = " << cplex.getTime() << endl;

        output_file << "Instance:" << this->instance.getFichierInstance().toStdString() << endl;
        output_file << "Solution status:" << cplex.getStatus() << endl;
        output_file << " Optimal Value=" << cplex.getObjValue() << endl;
        //output_file << " Optimal Value = " << cplex.getTime() << endl;

        for (int m= 0 ; m < this->instance.getNbrMachines() ; m++) {
            for(int i=0 ; i<this->instance.getNbrJobs() ; i++){
                if (cplex.getValue(X[i][m])>=0.9)
                {
                    // cout << "VM_" << i+1 << " : " << cplex.getValue(X[i]) << "[ "  ;
                    cout << "Machine_"<< m+1 << " VM_" << i+1 << " : [ "  ;

                    for (int t=this->instance.getSj()[i] ; t < this->instance.getFj()[i] ; t++) {
                        cout << t << " " ;
                    }

                    cout << this->instance.getFj()[i] << " ]" <<endl;
                }
            }
        }

        cout << endl;



    }

    double Apres = cplex.getCplexTime();

    output_file << "temps écoulé (en secondes):" << (double)(Apres - Avant) << endl;

    output_file << "IdMachine " << "Nombre de jobs ordonnancés" << endl;

    for (int m= 0 ; m < this->instance.getNbrMachines() ; m++) {
        int nb = 0;
        for(int i=0 ; i<this->instance.getNbrJobs() ; i++){
            if (cplex.getValue(X[i][m])>=0.9)
            {
                nb++;
            }
        }
        output_file << m << " " << nb << endl;
    }

    output_file << "IdMachine " << "n°Job " << "Si " << "Fi " << endl;

    for (int m= 0 ; m < this->instance.getNbrMachines() ; m++) {
        for(int i=0 ; i<this->instance.getNbrJobs() ; i++){
            if (cplex.getValue(X[i][m])>=0.9)
            {
                output_file << m << " " << i << " " << this->instance.getSj()[i] << " " << this->instance.getFj()[i] << endl;
            }
        }
    }

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

/**
 * @brief Algorithme permetant de récupérer les sous-ensembles maximaux de l'instance
 *
 * @param eh La liste d'événement classée
 * @param nb_job Le nombre de jobs de l'instance
 * @return map<int, vector<int> > Les sous ensembles maximaux
 */
map<int,vector<int>> MethodeExacte::getSousEnsemblesMaximaux(vector<vector<int>> eh, int nb_job){

    map<int,vector<int>> Jk;

    //numero du sous-ensemble maximal
    int k = 0;

    //Permet de savoir si on doit encore enlever des jobs du sous ensembles après une première supression
    int inc = 0;

    //Nombre d'événement de typesj parcourus
    int nbStartEvent = 0;

    for(int h = 0 ; h < (nb_job * 2); h++){

        //Si l'événement est de typesj, on ajoute le job correspondant au sous-ensemble k
        if(eh[h][2] == 1){
            nbStartEvent++;
            Jk[k].push_back(eh[h][1]);

            //On spécifie que le sous-ensemble est maximal
            inc = 0;
        }
        else{

            //Si on a parcouru l'ensemble des événements de typesj on retourne les sous-ensembles
            if(nbStartEvent == nb_job){
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
