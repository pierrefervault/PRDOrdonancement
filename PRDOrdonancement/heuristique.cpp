#include "heuristique.h"


Heuristique::Heuristique(string fichierInstance)
{
    //On cherche à lire le fichier, si ce n'est pas possible on l'indique
    std::ifstream f(fichierInstance);
    if (!f)
    {
        cout << fichierInstance <<" invalid file" << endl;
    }
    this->instance.setFichierInstance(QString::fromStdString(fichierInstance));

    //Nous spécifions en attribut le nombre de jobs, de ressources et de machines selon ce qu'on a lu dans le fichier
    int i;
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

    int horizonMax = 0;

    //Ici, on mets à jour les instant de début et de fin pour chaque job
    for (i=0 ; i < this->instance.getNbrJobs() ; i++)
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

    for( i=0 ; i<this->instance.getNbrJobs() ; i++)
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

vector<int> Heuristique::trierCCmaxSommeRessources(){

    //Ici on créer le tableau de valeur pour CCMax
    //selon la formule sommes des ressources pour un job * (F(i)-S(i))
    vector<vector<int>> tableauInitial;

    for(int i = 0 ; i<this->instance.getNbrJobs() ; i++)
    {
        vector<int> jobCCmax;
        jobCCmax.push_back(i);
        jobCCmax.push_back(0);
        for (int r = 0; r < this->instance.getNbrRessources() ; r++)
        {
            jobCCmax[1] += (this->instance.getTableauRessourcesJobs()[i][r] * (this->instance.getFj()[i]-this->instance.getSj()[i]));
        }
        tableauInitial.push_back(jobCCmax);
    }

    //Trie par ordre croissant de valeur de CCmax du tableau de job
    bool tab_en_ordre = false;
    int taille = this->instance.getNbrJobs();
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
                    if(this->instance.getSj()[i] > this->instance.getSj()[i+1])
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

    for (int i = 0; i < this->instance.getNbrJobs(); i++){
        tableauJobs.push_back(tableauInitial[i][0]);
    }

    return tableauJobs;

}

vector<int> Heuristique::trierCCmaxMaxRessources(){

    //Ici on créer le tableau de valeur pour CCMax
    //selon la formule valeur de la ressource la plus importante pour un job * (F(i)-S(i))
    vector<vector<int>> tableauInitial;

    for(int i = 0 ; i<this->instance.getNbrJobs() ; i++)
    {
        vector<int> jobCCmax;
        jobCCmax.push_back(i);
        jobCCmax.push_back(0);
        //On prend en compte la ressource la plus importante pour calculer le CCmax
        int maxRessource = 0;
        for (int r = 0; r < this->instance.getNbrJobs() ; r++)
        {
            if (this->instance.getTableauRessourcesJobs()[i][r] > maxRessource) maxRessource = this->instance.getTableauRessourcesJobs()[i][r];
        }
        jobCCmax[1] = (maxRessource * (this->instance.getFj()[i]-this->instance.getSj()[i]));
        tableauInitial.push_back(jobCCmax);
    }

    //Trie par ordre croissant de valeur de CCmax du tableau de job
    bool tab_en_ordre = false;
    int taille = this->instance.getNbrJobs();
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
                    if(this->instance.getSj()[i] > this->instance.getSj()[i+1])
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

    for (int i = 0; i < this->instance.getNbrJobs(); i++){
        tableauJobs.push_back(tableauInitial[i][0]);
    }

    return tableauJobs;

}

vector<int> Heuristique::trierSommeRessources(){

    //Ici on créer le tableau de valeur avec pour chaque job la somme de ces ressources
    vector<vector<int>> tableauInitial;

    for(int i = 0 ; i<this->instance.getNbrJobs() ; i++)
    {
        vector<int> jobCCmax;
        jobCCmax.push_back(i);
        jobCCmax.push_back(0);
        for (int r = 0; r < this->instance.getNbrJobs() ; r++)
        {
            jobCCmax[1] += this->instance.getTableauRessourcesJobs()[i][r];
        }
        tableauInitial.push_back(jobCCmax);
    }

    //Trie par ordre croissant de la sommes de ressources de chaque jobs du tableau
    bool tab_en_ordre = false;
    int taille = this->instance.getNbrJobs();
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
                    if(this->instance.getSj()[i] > this->instance.getSj()[i+1])
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

    for (int i = 0; i < this->instance.getNbrJobs(); i++){
        tableauJobs.push_back(tableauInitial[i][0]);
    }

    return tableauJobs;

}

vector<int> Heuristique::trierMoyenneRessourcesSousEnsembles(){

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

    for(unsigned int i = 0; i < Jk.size(); i++){
        cout << "Sous-ensembles " << i << " : ";
        for(unsigned int j = 0; j < Jk[i].size(); j++){
            cout << Jk[i][j] << " ";
        }
        cout << endl;
    }

    vector<int> moyenneRessourceJk;

    //Calcul des moyennes de ressources par sous-ensembles
    for(unsigned int i = 0 ; i < Jk.size(); i++){
        int moyenneRessource = 0;
        for(unsigned int j = 0; j < Jk[i].size(); j++){
            for (int r = 0; r < this->instance.getNbrRessources(); r++){
                moyenneRessource += this->instance.getTableauRessourcesJobs()[Jk[i][j]][r];
            }
        }
        moyenneRessource /= Jk[i].size();
        moyenneRessourceJk.push_back(moyenneRessource);
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

    for(unsigned int i = 0 ; i < Jk.size(); i++){
        for(unsigned int j = 0; j < Jk[i].size(); j++){
            if(std::find(tableauJobs.begin(), tableauJobs.end(), Jk[i][j]) == tableauJobs.end())
            {
              tableauJobs.push_back(Jk[i][j]);
            }
        }
    }

    //Affichage du tableau de jobs triés

    return tableauJobs;
}

map<int,vector<int>> Heuristique::getSousEnsemblesMaximaux(vector<vector<int>> eh, int nb_job){

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

int Heuristique::resolveMachinePerMachine(QString typeTri, QString fichierResultat){

    auto start = std::chrono::high_resolution_clock::now();

    vector<int> tableauJobs;

    if(typeTri == "CCmaxSommeRessources") tableauJobs = this->trierCCmaxSommeRessources();
    if(typeTri == "CCmaxMaxRessources") tableauJobs = this->trierCCmaxMaxRessources();
    if(typeTri == "SommeRessources") tableauJobs = this->trierSommeRessources();
    if(typeTri == "MoyenneRessourcesSousEnsembles") tableauJobs = this->trierMoyenneRessourcesSousEnsembles();

    vector<vector<int>> jobsOrdonnances;
    for(int m = 0; m < this->instance.getNbrMachines() ; m++){
        vector<int> jobsMachine;
        vector<int> Lm = tableauJobs;
        while(Lm.size() != 0){
            vector<int> Sm;
            for(unsigned int i = 0; i < jobsMachine.size(); i++){
                if(this->instance.getSj()[Lm[0]] < this->instance.getFj()[jobsMachine[i]] && this->instance.getFj()[Lm[0]] > this->instance.getSj()[jobsMachine[i]]){
                    Sm.push_back(jobsMachine[i]);
                }
            }

            bool jobOrdonancable = true;

            for(int i = this->instance.getSj()[Lm[0]]; i < this->instance.getFj()[Lm[0]]; i++){
                for(int r = 0; r < this->instance.getNbrRessources() ; r++){
                    int sommesRessources = 0;
                    for(unsigned int j = 0; j < Sm.size(); j++){
                        if(this->instance.getSj()[Sm[j]] <= i && this->instance.getFj()[Sm[j]] > i )
                        sommesRessources += this->instance.getTableauRessourcesJobs()[Sm[j]][r];
                    }
                    sommesRessources += this->instance.getTableauRessourcesJobs()[Lm[0]][r];
                   // cout << "Sommes Ressources : " << sommesRessources << endl;
                    if(sommesRessources > this->instance.getCapRessources()[r][m])
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

    return writeInFile(jobsOrdonnances, "Affectation1-"+typeTri, fichierResultat, time);

}

int Heuristique::resolveMachineLessUsedMachine(QString typeTri, QString fichierResultat){

    auto start = std::chrono::high_resolution_clock::now();

    vector<int> tableauJobs;

    if(typeTri == "CCmaxSommeRessources") tableauJobs = this->trierCCmaxSommeRessources();
    if(typeTri == "CCmaxMaxRessources") tableauJobs = this->trierCCmaxMaxRessources();
    if(typeTri == "SommeRessources") tableauJobs = this->trierSommeRessources();
    if(typeTri == "MoyenneRessourcesSousEnsembles") tableauJobs = this->trierMoyenneRessourcesSousEnsembles();

    vector<vector<int>> jobsOrdonnances;
    for(int m = 0; m < this->instance.getNbrMachines() ; m++){
        vector<int> tableauMachines;
        jobsOrdonnances.push_back(tableauMachines);
    }
    while(tableauJobs.size() != 0){
        vector<vector<int>> chargeEnsemblesMachine;
        for(int m = 0; m < this->instance.getNbrMachines() ; m++){
            vector<int> chargeMachine;
            chargeMachine.push_back(m);
            int charge = 0;
            for(int i = this->instance.getSj()[tableauJobs[0]]; i < this->instance.getFj()[tableauJobs[0]]; i++){
                for(int r = 0; r < this->instance.getNbrRessources() ; r++){
                    for(unsigned int j = 0; j < jobsOrdonnances[m].size(); j++){
                        if(this->instance.getSj()[jobsOrdonnances[m][j]] <= i && this->instance.getFj()[jobsOrdonnances[m][j]] > i )
                            charge += this->instance.getTableauRessourcesJobs()[jobsOrdonnances[m][j]][r];
                    }
                }
            }
            chargeMachine.push_back(charge);
            chargeEnsemblesMachine.push_back(chargeMachine);
            //cout << "Machine : " << m << " Charge : " << charge << endl;
        }
        //Trie à bulle des machines suivant la charge sur chacune d'elles
        bool tab_en_ordre = false;
        int taille = this->instance.getNbrMachines();
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

        for (unsigned int m = 0; m < chargeEnsemblesMachine.size(); m++){
            if(numeroJob == tableauJobs[0] && tableauJobs.size() != 0){
                vector<int> Sm;
                for(unsigned int i = 0; i < jobsOrdonnances[chargeEnsemblesMachine[m][0]].size(); i++){

                    if(this->instance.getSj()[tableauJobs[0]] < this->instance.getFj()[jobsOrdonnances[chargeEnsemblesMachine[m][0]][i]] &&
                            this->instance.getFj()[tableauJobs[0]] > this->instance.getSj()[jobsOrdonnances[chargeEnsemblesMachine[m][0]][i]])
                    {
                        Sm.push_back(jobsOrdonnances[chargeEnsemblesMachine[m][0]][i]);
                    }

                }

                bool jobOrdonancable = true;

                for(int i = this->instance.getSj()[tableauJobs[0]]; i < this->instance.getFj()[tableauJobs[0]]; i++){
                    for(int r = 0; r < this->instance.getNbrRessources() ; r++){
                        int sommesRessources = 0;
                        for(unsigned int j = 0; j < Sm.size(); j++){
                            if(this->instance.getSj()[Sm[j]] <= i && this->instance.getFj()[Sm[j]] > i )
                            sommesRessources += this->instance.getTableauRessourcesJobs()[Sm[j]][r];
                        }
                        sommesRessources += this->instance.getTableauRessourcesJobs()[tableauJobs[0]][r];
                        //cout << "Sommes Ressources : " << sommesRessources << endl;
                        if(sommesRessources > this->instance.getCapRessources()[r][chargeEnsemblesMachine[m][0]])
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

    return writeInFile(jobsOrdonnances, "Affectation1-"+typeTri, fichierResultat, time);

}

int Heuristique::writeInFile(vector<vector<int>> jobsOrdonnances, QString typeResolution, QString fichierResultat, double dureeExecution){

    int nbrJobsOrdonnances = 0;
    for(unsigned int i = 0; i < jobsOrdonnances.size(); i++){
        cout << "Machines : " << i << " : ";
        for(unsigned int j = 0; j < jobsOrdonnances[i].size(); j++){
            cout << jobsOrdonnances[i][j] << " ";
            nbrJobsOrdonnances++;
        }
        cout << endl;
    }

    ofstream output_file(fichierResultat.toStdString(),ios::app);

    output_file << "Instance \t: " << this->instance.getFichierInstance().toStdString() << endl;
    output_file << "Solution status: " << typeResolution.toStdString() << endl;
    output_file << " Optimal Value = " << nbrJobsOrdonnances << endl;

    output_file << "temps écoulé: " << dureeExecution  << " seconds" << endl;

    output_file << "IdMachine " << "nb " << endl;

    for(unsigned int i = 0; i < jobsOrdonnances.size(); i++){
        output_file << i+1 << " " << jobsOrdonnances[i].size() << endl;
    }

    output_file << "IdMachine " << "n°Job " << "Si " << "Fi " << endl;

    for(unsigned int i = 0; i < jobsOrdonnances.size(); i++){
        for(unsigned int j = 0; j < jobsOrdonnances[i].size(); j++){
            output_file << i+1 << " " << jobsOrdonnances[i][j] << " " << this->instance.getSj()[jobsOrdonnances[i][j]] << " " << this->instance.getFj()[jobsOrdonnances[i][j]] << endl;
        }
    }

    return nbrJobsOrdonnances;
}

Instance Heuristique::getInstance() const
{
    return instance;
}

void Heuristique::setInstance(const Instance &value)
{
    instance = value;
}
