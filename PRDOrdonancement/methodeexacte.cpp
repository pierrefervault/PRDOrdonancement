#include "methodeexacte.h"

/**
 * @brief Constructeur de la classe MethodeExacte
 *
 * @param fichierInstance Le chemin vers le fichier d'instance
 */
MethodeExacte::MethodeExacte(string fichierInstance)
{
    this->instance = new Instance();
    this->instance->chargerInstance(fichierInstance);
}

/**
 * @brief Methode de résolution exacte indéxée temps
 *
 * @param fichierResultat Le fichier où seront stockés les résulats
 * @return unsigned int Le nombre de jobs ordonnancés
 */
unsigned int MethodeExacte::resolutionPlneMip1(string fichierResultat)
{
    //Déclaration de l'environnement
    IloEnv env;

    IloModel model(env);

    //Ici on créer les variables Y qui valent 1 si le jobs i est exécuté à l'instant t sur une machine m

    IloArray<IloArray<IloNumVarArray>> Y(env,this->instance->getNbrJobs()) ;
    for (unsigned int i=0 ; i < this->instance->getNbrJobs() ; i++)
    {
        Y[i]= IloArray<IloNumVarArray>(env,this->instance->getNbrMachines());
        for (unsigned int machine= 0 ; machine < this->instance->getNbrMachines() ; machine++)
        {
            Y[i][machine] = IloNumVarArray (env,this->instance->getHorizonMax()+1);
            for (unsigned int t= 0 ; t < this->instance->getHorizonMax()+1 ; t++)
            {
                Y[i][machine][t]=IloNumVar(env,0,1,ILOINT);
            }
        }
    }

    //Ici on créer les variables X qui valent 1 si le jobs i est exécuté sur une machine m

    IloArray<IloNumVarArray> X(env,this->instance->getNbrJobs()) ;
    for (unsigned int i=0 ; i < this->instance->getNbrJobs() ; i++)
    {
        X[i] = IloNumVarArray (env,this->instance->getNbrMachines()) ;
        for (unsigned int m=0 ; m < this->instance->getNbrMachines() ; m++)
        {
            X[i][m]=IloNumVar(env,0,1,ILOINT);
        }
    }


    //Ici on ajoute la contrainte qui vérifie que si un jobs est exécuté,
    //il est exécuté durant la période [S[i],F[i][
    for (unsigned int i=0 ; i < this->instance->getNbrJobs() ; i++) {


        for (unsigned int m= 0 ; m < this->instance->getNbrMachines() ; m++) {
            IloExpr temps_total_execution_job(env);
            for (unsigned int t=this->instance->getSj()[i] ; t < this->instance->getFj()[i] ; t++) {
                temps_total_execution_job +=  Y[i][m][t];
            }
            model.add(temps_total_execution_job ==  (int)(this->instance->getFj()[i]-this->instance->getSj()[i])*X[i][m]);
        }
    }

    //Ici on ajoute la contrainte qui vérifie que si un jobs est exécuté,
    //pour chaque t les valeurs de ressources sur la machine m ne sont pas dépassée
    for (unsigned int r=0; r < this->instance->getNbrRessources() ; r++) {
        for (unsigned int t= 0 ; t < this->instance->getHorizonMax()+1 ; t++) {
            for (unsigned int m= 0 ; m < this->instance->getNbrMachines() ; m++) {
                IloExpr capacite_ressources(env);
                for (unsigned int i=0 ; i < this->instance->getNbrJobs() ; i++) {

                    capacite_ressources += Y[i][m][t] * (int)this->instance->getTableauRessourcesJobs()[i][r] ;

                }
                model.add( capacite_ressources <= (int)this->instance->getCapRessources()[r][m] ) ;
            }
        }
    }

    //Ici on ajoute la contrainte qui vérifie qu'un job ne peut être exécuter au maximum que sur une seule machine
    for( unsigned int i=0 ; i<this->instance->getNbrJobs() ; i++)
    {
        IloExpr unicite_job(env);
        for (unsigned int m= 0 ; m < this->instance->getNbrMachines() ; m++) {
            unicite_job +=  X[i][m];
        }
        model.add( unicite_job <= 1 ) ;
    }


    //Ici, on ajoute la fonction objective qui correspond à maximiser le nombre de jobs ordonnancés
    IloExpr numberJob(env);

    for( unsigned int i=0 ; i<this->instance->getNbrJobs() ; i++)
    {
        for (unsigned int m= 0 ; m < this->instance->getNbrMachines() ; m++) {
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

        output_file << "Instance:" << this->instance->getFichierInstance().toStdString() << endl;
        output_file << "Solution status:" << cplex.getStatus() << endl;
        output_file << " Optimal Value=" << cplex.getObjValue() << endl;
        //output_file << " Optimal Value = " << cplex.getTime() << endl;

        for (unsigned int m= 0 ; m < this->instance->getNbrMachines() ; m++) {
            for( unsigned int i=0 ; i<this->instance->getNbrJobs() ; i++){
                if (cplex.getValue(X[i][m])>=0.9)
                {
                    // cout << "VM_" << i+1 << " : " << cplex.getValue(X[i]) << "[ "  ;
                    cout << "Machine_"<< m+1 << " VM_" << i+1 << " : [ "  ;

                    for (unsigned int t=this->instance->getSj()[i] ; t < this->instance->getFj()[i] ; t++) {

                        if (cplex.getValue(Y[i][m][t]) >= 0.9)
                        {
                            cout << t << " " ;
                        }
                    }

                    cout << this->instance->getFj()[i] << " ]" <<endl;
                }
            }
        }

        cout << endl;



    }

    double Apres = cplex.getCplexTime();

    output_file << "temps écoulé (en secondes):" << (double)(Apres - Avant) << endl;

    output_file << "IdMachine " << "Nombre de jobs ordonnancés" << endl;

    for (unsigned int m= 0 ; m < this->instance->getNbrMachines() ; m++) {
        unsigned int nb = 0;
        for( unsigned int i=0 ; i<this->instance->getNbrJobs() ; i++){
            if (cplex.getValue(X[i][m])>=0.9)
            {
                nb++;
            }
        }
        output_file << m << " " << nb << endl;
    }

    output_file << "IdMachine " << "n°Job " << "Si " << "Fi " << endl;

    for (unsigned int m= 0 ; m < this->instance->getNbrMachines() ; m++) {
        for( unsigned int i=0 ; i<this->instance->getNbrJobs() ; i++){
            if (cplex.getValue(X[i][m])>=0.9)
            {
                output_file << m << " " << i << " " << this->instance->getSj()[i] << " " << this->instance->getFj()[i] << endl;
            }
        }
    }



    ///////////////////////////////////////////////////

    unsigned int optimal = cplex.getObjValue();

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
 * @return unsigned int Le nombre de jobs ordonnancés
 */
unsigned int MethodeExacte::resolutionPlneMip2(string fichierResultat)
{
    //Déclaration de l'environnement
    IloEnv env;

    IloModel model(env);

    //Algorithme de création de sous-ensembles maximaux

    map<unsigned int,vector<unsigned int>> Jk = this->instance->getSousEnsemblesMaximaux();

    for(std::map<unsigned int,vector<unsigned int>>::iterator it = Jk.begin() ; it != Jk.end() ; ++it){
        cout << it->first << endl;
        for(std::vector<unsigned int>::iterator itVect = it->second.begin() ; itVect != it->second.end() ; ++itVect){
            cout << *itVect << " ";
        }
        cout << endl;
    }

    //Ici on créer les variables X qui valent 1 si le jobs i est exécuté sur une machine m
    IloArray<IloNumVarArray> X(env,this->instance->getNbrJobs()) ;
    for (unsigned int i=0 ; i < this->instance->getNbrJobs() ; i++)
    {
        X[i] = IloNumVarArray (env,this->instance->getNbrMachines()) ;
        for (unsigned int m=0 ; m < this->instance->getNbrMachines(); m++)
        {
            X[i][m]=IloNumVar(env,0,1,ILOINT);
        }
    }

    //Ici on ajoute la contrainte qui vérifie que si un jobs est exécuté,
    //les valeurs de ressources sur la machine m ne sont pas dépassée
   for (unsigned int r=0; r < this->instance->getNbrRessources() ; r++) {
        for (unsigned int m= 0 ; m < this->instance->getNbrMachines() ; m++) {
            for (unsigned int h= 0 ; h < Jk.size() ; h++) {
                IloExpr capacite_ressources(env);
                for (unsigned int l=0 ; l < Jk[h].size() ; l++) {
                    cout << "Job : " << Jk[h][l] << " ";
                    capacite_ressources += X[(Jk[h][l])][m] * (int)this->instance->getTableauRessourcesJobs()[(Jk[h][l])][r] ;
                }
                cout << endl;
                model.add( capacite_ressources <= (int)this->instance->getCapRessources()[r][m] ) ;
            }
        }
    }

    //Ici on ajoute la contrainte qui vérifie qu'un job ne peut être exécuter au maximum que sur une seule machine
    for( unsigned int i=0 ; i<this->instance->getNbrJobs() ; i++)
    {
        IloExpr unicite_job(env);
        for (unsigned int m= 0 ; m < this->instance->getNbrMachines() ; m++) {
            unicite_job +=  X[i][m];
        }
        model.add( unicite_job <= 1 ) ;
    }


    IloExpr numberJob(env);

    for(unsigned int i=0 ; i<this->instance->getNbrJobs() ; i++)
    {
        for (unsigned int m= 0 ; m < this->instance->getNbrMachines() ; m++) {
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

        output_file << "Instance:" << this->instance->getFichierInstance().toStdString() << endl;
        output_file << "Solution status:" << cplex.getStatus() << endl;
        output_file << " Optimal Value=" << cplex.getObjValue() << endl;
        //output_file << " Optimal Value = " << cplex.getTime() << endl;

        for (unsigned int m= 0 ; m < this->instance->getNbrMachines() ; m++) {
            for(unsigned int i=0 ; i<this->instance->getNbrJobs() ; i++){
                if (cplex.getValue(X[i][m])>=0.9)
                {
                    // cout << "VM_" << i+1 << " : " << cplex.getValue(X[i]) << "[ "  ;
                    cout << "Machine_"<< m+1 << " VM_" << i+1 << " : [ "  ;

                    for (unsigned int t=this->instance->getSj()[i] ; t < this->instance->getFj()[i] ; t++) {
                        cout << t << " " ;
                    }

                    cout << this->instance->getFj()[i] << " ]" <<endl;
                }
            }
        }

        cout << endl;



    }

    double Apres = cplex.getCplexTime();

    output_file << "temps écoulé (en secondes):" << (double)(Apres - Avant) << endl;

    output_file << "IdMachine " << "Nombre de jobs ordonnancés" << endl;

    for (unsigned int m= 0 ; m < this->instance->getNbrMachines() ; m++) {
        unsigned int nb = 0;
        for(unsigned int i=0 ; i<this->instance->getNbrJobs() ; i++){
            if (cplex.getValue(X[i][m])>=0.9)
            {
                nb++;
            }
        }
        output_file << m << " " << nb << endl;
    }

    output_file << "IdMachine " << "n°Job " << "Si " << "Fi " << endl;

    for (unsigned int m= 0 ; m < this->instance->getNbrMachines() ; m++) {
        for(unsigned int i=0 ; i<this->instance->getNbrJobs() ; i++){
            if (cplex.getValue(X[i][m])>=0.9)
            {
                output_file << m << " " << i << " " << this->instance->getSj()[i] << " " << this->instance->getFj()[i] << endl;
            }
        }
    }

    ///////////////////////////////////////////////////

    unsigned int optimal = cplex.getObjValue();

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
