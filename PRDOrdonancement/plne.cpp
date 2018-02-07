#include "plne.h"

int resolvePlne(string fichierInstance, string fichierResultat)
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
	IloInt id , s_i , f_i ;
	IloInt cmax=0;

    //Ici, on mets à jour les instant de début (S_j) et de fin (F_j) pour chaque job
    for (i=0 ; i < nb_job ; i++)
	{
		f >> id >> s_i >> f_i ;
		
		S_j[i]=s_i;
		F_j[i]=f_i;
		
		
		if (cmax <= f_i ) cmax = f_i;
		
		
		//cout << id << " " << s_i << " " << f_i << " " << endl;
	}
	//cout << endl;
	
	//cout <<"cmax : " <<cmax << endl;
	


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


    //Ici on créer les variables Y qui valent 1 si le jobs i est exécuté à l'instant t sur une machine m

	IloArray<NumVarMatrix> Y(env,nb_job) ;
	for (i=0 ; i < nb_job ; i++)
	{
        Y[i]= NumVarMatrix(env,nb_machines);
		for (int machine= 0 ; machine < nb_machines ; machine++)
		{
			Y[i][machine] = IloNumVarArray (env,cmax+1);
			for (int t= 0 ; t < cmax+1 ; t++)
			{
				Y[i][machine][t]=IloNumVar(env,0,1,ILOINT);
			}
		}			
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
    //il est exécuté durant la période [S[i],F[i][
	for (i=0 ; i < nb_job ; i++) {
		
		
		for (int m= 0 ; m < nb_machines ; m++) {
			IloExpr temps_total_execution_job(env);			
			for (int t= S_j[i] ; t < F_j[i] ; t++) {
				temps_total_execution_job +=  Y[i][m][t];
			}
			model.add(temps_total_execution_job ==  (F_j[i]-S_j[i])*X[i][m]);
		}
	}
	
    //Ici on ajoute la contrainte qui vérifie que si un jobs est exécuté,
    //pour chaque t les valeurs de ressources sur la machine m ne sont pas dépassée
	for (int r=0; r < nb_ressources ; r++) {
		for (int t= 0 ; t < cmax+1 ; t++) {
			for (int m= 0 ; m < nb_machines ; m++) {
				IloExpr capacite_ressources(env);
				for (i=0 ; i < nb_job ; i++) {
				
					capacite_ressources += Y[i][m][t] * C[i][r] ;
				
				}
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
	
	
    //Ici, on ajoute la fonction objective qui correspond à maximiser le nombre de jobs ordonnancés
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
					
						if (cplex.getValue(Y[i][m][t]) >= 0.9)
						{
							cout << t << " " ;
						}
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
}*/
    env.end();
	return 0;
}

