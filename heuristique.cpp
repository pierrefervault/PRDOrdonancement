#include "heuristique.h"

Heuristique::Heuristique(string fichierInstance)
{
    //On cherche à lire le fichier, si ce n'est pas possible on l'indique
    std::ifstream f(fichierInstance);
    if (!f)
    {
        cout << fichierInstance <<" invalid file" << endl;
    }
    this->fichierInstance = QString::fromStdString(fichierInstance);

    //Nous spécifions en attribut le nombre de jobs, de ressources et de machines selon ce qu'on a lu dans le fichier
    int i, m;
    f >> this->nbr_jobs >> this->nbr_ressources >> this->nbr_machines;


    //Ici on créer un tableau contenant la capacité en ressources pour la ressource r de chaque machine
    for (int r=0; r < this->nbr_ressources ; r++)
    {
        vector<int> ressources;
        for (int machine=0; machine < this->nbr_machines ; machine++)
        {
            int value;
            f >> value;
            ressources.push_back(value);
        }
        this->cap_ressources.push_back(ressources);
    }

    //cout << "Nombre de jobs : " << nb_job << endl;

    int id , s_i , f_i ;
    int cmax=0;

    //Ici, on mets à jour les instant de début et de fin pour chaque job
    for (i=0 ; i < this->nbr_jobs ; i++)
    {
        f >> id >> s_i >> f_i ;

        this->S_j.push_back(s_i);
        this->F_j.push_back(f_i);


        if (cmax <= f_i ) cmax = f_i;


        //cout << id << " " << s_i << " " << f_i << " " << endl;
    }
    //cout << endl;

    //cout <<"cmax : " <<cmax << endl;

    //Ici, on créer le tableau ou est stocké pour chaque job i la valeur pour la ressource r associée au job

    for( i=0 ; i<this->nbr_jobs ; i++)
    {
        vector<int> ressources;
        //C[i] = IloNumArray  (env,nb_ressources);
        for (int r=0; r < this->nbr_ressources ; r++)
        {
            //f >> cap;
            //C[i][r]=cap;
            int value;
            f >> value;
            ressources.push_back(value);
            //	cout << C[i][r] << " ";
        }
        this->C.push_back(ressources);

        //	cout << endl;
    }

}

vector<int> Heuristique::trierCCmaxSommeRessources(){

    //Ici on créer le tableau de valeur pour CCMax
    //selon la formule sommes des ressources pour un job * (F(i)-S(i))
    vector<vector<int>> tableauInitial;

    for(int i = 0 ; i<this->nbr_jobs ; i++)
    {
        vector<int> jobCCmax;
        jobCCmax.push_back(i);
        jobCCmax.push_back(0);
        for (int r = 0; r < this->nbr_ressources ; r++)
        {
            jobCCmax[1] += (this->C[i][r] * (this->F_j[i]-this->S_j[i]));
        }
        tableauInitial.push_back(jobCCmax);
    }

    //Trie par ordre croissant de valeur de CCmax du tableau de job
    bool tab_en_ordre = false;
    int taille = this->nbr_jobs;
    while(!tab_en_ordre)
    {
        tab_en_ordre = true;
        for(int i=0 ; i < taille-1 ; i++)
        {
            if(tableauInitial[i][1] > tableauInitial[i+1][1])
            {
                swap(tableauInitial[i],tableauInitial[i+1]);
                tab_en_ordre = false;
            }
            else {
                if(tableauInitial[i][1] == tableauInitial[i+1][1])
                {
                    if(S_j[i] > S_j[i+1])
                    {
                        swap(tableauInitial[i],tableauInitial[i+1]);
                        tab_en_ordre = false;
                    }
                }
            }
        }
        taille--;
    }

    //Création du tableau de jobstriés selon la règle CCmax (sommesRessources)
    vector<int> tableauJobs;

    for (int i = 0; i < this->nbr_jobs; i++){
        //cout << tableauInitial[i][0] << " " << tableauInitial[i][1] << endl;
        tableauJobs.push_back(tableauInitial[i][0]);
    }

    return tableauJobs;

}

vector<int> Heuristique::trierCCmaxMaxRessources(){

    //Ici on créer le tableau de valeur pour CCMax
    //selon la formule valeur de la ressource la plus importante pour un job * (F(i)-S(i))
    vector<vector<int>> tableauInitial;

    for(int i = 0 ; i<this->nbr_jobs ; i++)
    {
        vector<int> jobCCmax;
        jobCCmax.push_back(i);
        jobCCmax.push_back(0);
        //On prend en compte la ressource la plus importante pour calculer le CCmax
        int maxRessource = 0;
        for (int r = 0; r < this->nbr_ressources ; r++)
        {
            if (this->C[i][r] > maxRessource) maxRessource = this->C[i][r];
        }
        jobCCmax[1] = (maxRessource * (this->F_j[i]-this->S_j[i]));
        tableauInitial.push_back(jobCCmax);
    }

    //Trie par ordre croissant de valeur de CCmax du tableau de job
    bool tab_en_ordre = false;
    int taille = this->nbr_jobs;
    while(!tab_en_ordre)
    {
        tab_en_ordre = true;
        for(int i=0 ; i < taille-1 ; i++)
        {
            if(tableauInitial[i][1] > tableauInitial[i+1][1])
            {
                swap(tableauInitial[i],tableauInitial[i+1]);
                tab_en_ordre = false;
            }
            else {
                if(tableauInitial[i][1] == tableauInitial[i+1][1])
                {
                    if(S_j[i] > S_j[i+1])
                    {
                        swap(tableauInitial[i],tableauInitial[i+1]);
                        tab_en_ordre = false;
                    }
                }
            }
        }
        taille--;
    }

    //Création du tableau de jobstriés selon la règle CCmax (par rapport à la ressource maximale)
    vector<int> tableauJobs;

    for (int i = 0; i < this->nbr_jobs; i++){
        //cout << tableauInitial[i][0] << " " << tableauInitial[i][1] << endl;
        tableauJobs.push_back(tableauInitial[i][0]);
    }

    return tableauJobs;

}

vector<int> Heuristique::trierSommeRessources(){

    //Ici on créer le tableau de valeur avec pour chaque job la somme de ces ressources
    vector<vector<int>> tableauInitial;

    for(int i = 0 ; i<this->nbr_jobs ; i++)
    {
        vector<int> jobCCmax;
        jobCCmax.push_back(i);
        jobCCmax.push_back(0);
        for (int r = 0; r < this->nbr_ressources ; r++)
        {
            jobCCmax[1] += this->C[i][r];
        }
        tableauInitial.push_back(jobCCmax);
    }

    //Trie par ordre croissant de la sommes de ressources de chaque jobs du tableau
    bool tab_en_ordre = false;
    int taille = this->nbr_jobs;
    while(!tab_en_ordre)
    {
        tab_en_ordre = true;
        for(int i=0 ; i < taille-1 ; i++)
        {
            if(tableauInitial[i][1] > tableauInitial[i+1][1])
            {
                swap(tableauInitial[i],tableauInitial[i+1]);
                tab_en_ordre = false;
            }
            else {
                if(tableauInitial[i][1] == tableauInitial[i+1][1])
                {
                    if(S_j[i] > S_j[i+1])
                    {
                        swap(tableauInitial[i],tableauInitial[i+1]);
                        tab_en_ordre = false;
                    }
                }
            }
        }
        taille--;
    }

    //On crée le tableau de jobs triés
    vector<int> tableauJobs;

    for (int i = 0; i < this->nbr_jobs; i++){
        //cout << tableauInitial[i][0] << " " << tableauInitial[i][1] << endl;
        tableauJobs.push_back(tableauInitial[i][0]);
    }

    return tableauJobs;

}

vector<int> Heuristique::trierMoyenneRessourcesSousEnsembles(){

    //On crée le tableau d'événement eh nécessaire à la création des sous-ensembles de jobs maximaux
    vector<vector<int>> eh;
    for (int i=0 ; i < this->nbr_jobs ; i++)
    {
        vector<int> debut;
        debut.push_back(this->S_j[i]);
        debut.push_back(i);
        debut.push_back(1);
        debut.push_back(this->F_j[i]);

        eh.push_back(debut);

        vector<int> fin;
        fin.push_back(this->F_j[i]);
        fin.push_back(i);
        fin.push_back(0);
        fin.push_back(this->F_j[i]);

        eh.push_back(fin);
    }


    /*cout << endl;

    for (int i=0; i < (this->nbr_jobs * 2); i++){
        cout << eh[i][0] << " " << eh[i][1] << " " << eh[i][2] << " " << endl;
    }*/

    //Trie à bulle du tableau d'événement eh suivant l'ordre défini par l'algorithme
    bool tab_en_ordre = false;
    int taille = (this->nbr_jobs*2);
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

    map<int,vector<int>> Jk = getSousEnsemblesMaximaux(eh, this->nbr_jobs);

    for(int i = 0; i < Jk.size(); i++){
        cout << "Sous-ensembles " << i << " : ";
        for(int j = 0; j < Jk[i].size(); j++){
            cout << Jk[i][j] << " ";
        }
        cout << endl;
    }

    vector<int> moyenneRessourceJk;

    //Calcul des moyennes de ressources par sous-ensembles
    for(int i = 0 ; i < Jk.size(); i++){
        int moyenneRessource = 0;
        for(int j = 0; j < Jk[i].size(); j++){
            //cout << Jk[i][j] << " ";
            for (int r = 0; r < this->nbr_ressources; r++){
                moyenneRessource += this->C[Jk[i][j]][r];
            }
        }
        //cout << endl;
        moyenneRessource /= Jk[i].size();
        moyenneRessourceJk.push_back(moyenneRessource);
        //cout << moyenneRessourceJk[i] << endl;
    }

    //Trie par ordre croissant de moyennes de ressources pour chaque sous-ensembles
    tab_en_ordre = false;
    taille = Jk.size();
    while(!tab_en_ordre)
    {
        tab_en_ordre = true;
        for(int i=0 ; i < taille-1 ; i++)
        {
            if(moyenneRessourceJk[i] > moyenneRessourceJk[i+1])
            {
                swap(Jk[i],Jk[i+1]);
                swap(moyenneRessourceJk[i],moyenneRessourceJk[i+1]);
                tab_en_ordre = false;
            }
        }
        taille--;
    }

    //Création du tableau de jobs triés

    vector<int> tableauJobs;

    for(int i = 0 ; i < Jk.size(); i++){
        for(int j = 0; j < Jk[i].size(); j++){
            if(std::find(tableauJobs.begin(), tableauJobs.end(), Jk[i][j]) == tableauJobs.end())
            {
              tableauJobs.push_back(Jk[i][j]);
            }
        }
    }

    //Affichage du tableau de jobs triés
/*    cout << endl;
    for(int i = 0; i < tableauJobs.size(); i++) {
        cout << tableauJobs[i] << " ";
    }
    cout << endl;*/

    return tableauJobs;
}

map<int,vector<int>> Heuristique::getSousEnsemblesMaximaux(vector<vector<int>> eh, int nb_job){

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

void Heuristique::resolveMachinePerMachine(QString typeTri, QString fichierResultat){

    auto start = std::chrono::high_resolution_clock::now();

    vector<int> tableauJobs;

    if(typeTri == "CCmaxSommeRessources") tableauJobs = this->trierCCmaxSommeRessources();
    if(typeTri == "CCmaxMaxRessources") tableauJobs = this->trierCCmaxMaxRessources();
    if(typeTri == "SommeRessources") tableauJobs = this->trierSommeRessources();
    if(typeTri == "MoyenneRessourcesSousEnsembles") tableauJobs = this->trierMoyenneRessourcesSousEnsembles();

    vector<vector<int>> jobsOrdonnances;
    for(int m = 0; m < this->nbr_machines ; m++){
        vector<int> jobsMachine;
        vector<int> Lm = tableauJobs;
        while(Lm.size() != 0){
            vector<int> Sm;
            for(int i = 0; i < jobsMachine.size(); i++){
                if(this->S_j[Lm[0]] < this->F_j[jobsMachine[i]] && this->F_j[Lm[0]] > this->S_j[jobsMachine[i]]){
                    Sm.push_back(jobsMachine[i]);
                }
            }

            bool jobOrdonancable = true;

            for(int i = this->S_j[Lm[0]]; i < this->F_j[Lm[0]]; i++){
                for(int r = 0; r < this->nbr_ressources ; r++){
                    int sommesRessources = 0;
                    for(int j = 0; j < Sm.size(); j++){
                        if(this->S_j[Sm[j]] <= i && this->F_j[Sm[j]] > i )
                        sommesRessources += C[Sm[j]][r];
                    }
                    sommesRessources += C[Lm[0]][r];
                   // cout << "Sommes Ressources : " << sommesRessources << endl;
                    if(sommesRessources > this->cap_ressources[r][m])
                        jobOrdonancable = false;
                   // cout << jobOrdonancable << endl;
                }
            }

            if (jobOrdonancable){
                jobsMachine.push_back(Lm[0]);
                tableauJobs.erase(std::remove(tableauJobs.begin(), tableauJobs.end(), Lm[0]), tableauJobs.end());
            }
            Lm.erase(std::remove(Lm.begin(), Lm.end(), Lm[0]), Lm.end());
        }
        jobsOrdonnances.push_back(jobsMachine);
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    double nanoseconds = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count());

    double time = nanoseconds/1000000000;

    writeInFile(jobsOrdonnances, "Affectation1-"+typeTri, fichierResultat, time);

}

void Heuristique::resolveMachineLessUsedMachine(QString typeTri, QString fichierResultat){

    auto start = std::chrono::high_resolution_clock::now();

    vector<int> tableauJobs;

    if(typeTri == "CCmaxSommeRessources") tableauJobs = this->trierCCmaxSommeRessources();
    if(typeTri == "CCmaxMaxRessources") tableauJobs = this->trierCCmaxMaxRessources();
    if(typeTri == "SommeRessources") tableauJobs = this->trierSommeRessources();
    if(typeTri == "MoyenneRessourcesSousEnsembles") tableauJobs = this->trierMoyenneRessourcesSousEnsembles();

    vector<vector<int>> jobsOrdonnances;
    for(int m = 0; m < this->nbr_machines ; m++){
        vector<int> tableauMachines;
        jobsOrdonnances.push_back(tableauMachines);
    }
    while(tableauJobs.size() != 0){
        vector<vector<int>> chargeEnsemblesMachine;
        for(int m = 0; m < this->nbr_machines ; m++){
            vector<int> chargeMachine;
            chargeMachine.push_back(m);
            int charge = 0;
            for(int i = this->S_j[tableauJobs[0]]; i < this->F_j[tableauJobs[0]]; i++){
                for(int r = 0; r < this->nbr_ressources ; r++){
                    for(int j = 0; j < jobsOrdonnances[m].size(); j++){
                        if(this->S_j[jobsOrdonnances[m][j]] <= i && this->F_j[jobsOrdonnances[m][j]] > i )
                            charge += C[jobsOrdonnances[m][j]][r];
                    }
                }
            }
            chargeMachine.push_back(charge);
            chargeEnsemblesMachine.push_back(chargeMachine);
            //cout << "Machine : " << m << " Charge : " << charge << endl;
        }
        //Trie à bulle des machines suivant la charge sur chacune d'elles
        bool tab_en_ordre = false;
        int taille = this->nbr_machines;
        while(!tab_en_ordre)
        {
            tab_en_ordre = true;
            for(int i=0 ; i < taille-1 ; i++)
            {
                if(chargeEnsemblesMachine[i][1] > chargeEnsemblesMachine[i+1][1])
                {
                    swap(chargeEnsemblesMachine[i],chargeEnsemblesMachine[i+1]);
                    tab_en_ordre = false;
                }
            }
            taille--;
        }

        int numeroJob = tableauJobs[0];

        for (int m = 0; m < chargeEnsemblesMachine.size(); m++){
            if(numeroJob == tableauJobs[0] && tableauJobs.size() != 0){
                vector<int> Sm;
                for(int i = 0; i < jobsOrdonnances[chargeEnsemblesMachine[m][0]].size(); i++){

                    if(this->S_j[tableauJobs[0]] < this->F_j[jobsOrdonnances[chargeEnsemblesMachine[m][0]][i]] &&
                            this->F_j[tableauJobs[0]] > this->S_j[jobsOrdonnances[chargeEnsemblesMachine[m][0]][i]])
                    {
                        Sm.push_back(jobsOrdonnances[chargeEnsemblesMachine[m][0]][i]);
                    }

                }

                bool jobOrdonancable = true;

                for(int i = this->S_j[tableauJobs[0]]; i < this->F_j[tableauJobs[0]]; i++){
                    for(int r = 0; r < this->nbr_ressources ; r++){
                        int sommesRessources = 0;
                        for(int j = 0; j < Sm.size(); j++){
                            if(this->S_j[Sm[j]] <= i && this->F_j[Sm[j]] > i )
                            sommesRessources += C[Sm[j]][r];
                        }
                        sommesRessources += C[tableauJobs[0]][r];
                        //cout << "Sommes Ressources : " << sommesRessources << endl;
                        if(sommesRessources > this->cap_ressources[r][chargeEnsemblesMachine[m][0]])
                            jobOrdonancable = false;
                        //cout << jobOrdonancable << endl;
                    }
                }

                if (jobOrdonancable){
                    //cout << "Job " << numeroJob << " ajoute à la machines : " << chargeEnsemblesMachine[m][0] << endl;
                    jobsOrdonnances[chargeEnsemblesMachine[m][0]].push_back(tableauJobs[0]);
                    tableauJobs.erase(std::remove(tableauJobs.begin(), tableauJobs.end(), numeroJob), tableauJobs.end());
                }
            }
        }

        if(numeroJob == tableauJobs[0] && tableauJobs.size() != 0){
            //cout << "Job refusé = " << numeroJob << endl;
            tableauJobs.erase(std::remove(tableauJobs.begin(), tableauJobs.end(), numeroJob), tableauJobs.end());
        }
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    double nanoseconds = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count());

    double time = nanoseconds/1000000000;

    writeInFile(jobsOrdonnances, "Affectation1-"+typeTri, fichierResultat, time);

}

void Heuristique::writeInFile(vector<vector<int>> jobsOrdonnances, QString typeResolution, QString fichierResultat, double dureeExecution){

    int nbrJobsOrdonnances = 0;
    for(int i = 0; i < jobsOrdonnances.size(); i++){
        cout << "Machines : " << i << " : ";
        for(int j = 0; j < jobsOrdonnances[i].size(); j++){
            cout << jobsOrdonnances[i][j] << " ";
            nbrJobsOrdonnances++;
        }
        cout << endl;
    }

    ofstream output_file(fichierResultat.toStdString(),ios::app);

    output_file << "Instance \t: " << this->fichierInstance.toStdString() << endl;
    output_file << "Solution status: " << typeResolution.toStdString() << endl;
    output_file << " Optimal Value = " << nbrJobsOrdonnances << endl;

    output_file << "temps écoulé: " << dureeExecution  << " seconds" << endl;
}
