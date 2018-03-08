#include "heuristique.h"


/**
 * @brief Constructeur de la classe Heuristique
 *
 * @param fichierInstance Le fichier d'instance
 */
Heuristique::Heuristique(string fichierInstance)
{
    this->instance.chargerInstance(fichierInstance);
}

/**
 * @brief Tri selon la méthode CCmax basée sur la somme des ressources de chaque job
 *
 * @return vector<unsigned int> La liste des jobs triés
 */
vector<unsigned int> Heuristique::trierCCmaxSommeRessources(){

    //Ici on créer le tableau de valeur pour CCMax
    //selon la formule sommes des ressources pour un job * (F(i)-S(i))
    vector<vector<unsigned int>> tableauInitial;

    for(unsigned int i = 0 ; i<this->instance.getNbrJobs() ; i++)
    {
        vector<unsigned int> jobCCmax;
        jobCCmax.push_back(i);
        jobCCmax.push_back(0);
        for (unsigned int r = 0; r < this->instance.getNbrRessources() ; r++)
        {
            jobCCmax[1] += (this->instance.getTableauRessourcesJobs()[i][r] * (this->instance.getFj()[i]-this->instance.getSj()[i]));
        }
        tableauInitial.push_back(jobCCmax);
    }

    //Trie par ordre croissant de valeur de CCmax du tableau de job
    bool tab_en_ordre = false;
    unsigned int taille = this->instance.getNbrJobs();
    while(!tab_en_ordre)
    {
        tab_en_ordre = true;
        for(unsigned int i=0 ; i < taille-1 ; i++)
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
    vector<unsigned int> tableauJobs;

    for (unsigned int i = 0; i < this->instance.getNbrJobs(); i++){
        tableauJobs.push_back(tableauInitial[i][0]);
    }

    return tableauJobs;

}

/**
 * @brief Tri selon la méthode CCmax basée sur la valeur de ressource maximale de chaque job
 *
 * @return vector<unsigned int> La liste des jobs triés
 */
vector<unsigned int> Heuristique::trierCCmaxMaxRessources(){

    //Ici on créer le tableau de valeur pour CCMax
    //selon la formule valeur de la ressource la plus importante pour un job * (F(i)-S(i))
    vector<vector<unsigned int>> tableauInitial;

    for(unsigned int i = 0 ; i<this->instance.getNbrJobs() ; i++)
    {
        vector<unsigned int> jobCCmax;
        jobCCmax.push_back(i);
        jobCCmax.push_back(0);
        //On prend en compte la ressource la plus importante pour calculer le CCmax
        unsigned int maxRessource = 0;
        for (unsigned int r = 0; r < this->instance.getNbrJobs() ; r++)
        {
            if (this->instance.getTableauRessourcesJobs()[i][r] > maxRessource) maxRessource = this->instance.getTableauRessourcesJobs()[i][r];
        }
        jobCCmax[1] = (maxRessource * (this->instance.getFj()[i]-this->instance.getSj()[i]));
        tableauInitial.push_back(jobCCmax);
    }

    //Trie par ordre croissant de valeur de CCmax du tableau de job
    bool tab_en_ordre = false;
    unsigned int taille = this->instance.getNbrJobs();
    while(!tab_en_ordre)
    {
        tab_en_ordre = true;
        for(unsigned int i=0 ; i < taille-1 ; i++)
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
    vector<unsigned int> tableauJobs;

    for (unsigned int i = 0; i < this->instance.getNbrJobs(); i++){
        tableauJobs.push_back(tableauInitial[i][0]);
    }

    return tableauJobs;

}

/**
 * @brief Tri selon la somme des ressources de chaque job
 *
 * @return vector<unsigned int> La liste des jobs triés
 */
vector<unsigned int> Heuristique::trierSommeRessources(){

    //Ici on créer le tableau de valeur avec pour chaque job la somme de ces ressources
    vector<vector<unsigned int>> tableauInitial;

    for(unsigned int i = 0 ; i<this->instance.getNbrJobs() ; i++)
    {
        vector<unsigned int> jobCCmax;
        jobCCmax.push_back(i);
        jobCCmax.push_back(0);
        for (unsigned int r = 0; r < this->instance.getNbrJobs() ; r++)
        {
            jobCCmax[1] += this->instance.getTableauRessourcesJobs()[i][r];
        }
        tableauInitial.push_back(jobCCmax);
    }

    //Trie par ordre croissant de la sommes de ressources de chaque jobs du tableau
    bool tab_en_ordre = false;
    unsigned int taille = this->instance.getNbrJobs();
    while(!tab_en_ordre)
    {
        tab_en_ordre = true;
        for(unsigned int i=0 ; i < taille-1 ; i++)
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
    vector<unsigned int> tableauJobs;

    for (unsigned int i = 0; i < this->instance.getNbrJobs(); i++){
        tableauJobs.push_back(tableauInitial[i][0]);
    }

    return tableauJobs;

}

/**
 * @brief Tri selon la moyenne des ressources de chaque sous-ensembles maximaux de l'instance
 *
 * @return vector<unsigned int> La liste des jobs triés
 */
vector<unsigned int> Heuristique::trierMoyenneRessourcesSousEnsembles(){

    //Algorithme de création de sous-ensembles maximaux

    map<unsigned int,vector<unsigned int>> Jk = this->instance.getSousEnsemblesMaximaux();

    for(unsigned int i = 0; i < Jk.size(); i++){
        //cout << "Sous-ensembles " << i << " : ";
        for(unsigned int j = 0; j < Jk[i].size(); j++){
            //cout << Jk[i][j] << " ";
        }
        //cout << endl;
    }

    vector<unsigned int> moyenneRessourceJk;

    //Calcul des moyennes de ressources par sous-ensembles
    for(unsigned int i = 0 ; i < Jk.size(); i++){
        unsigned int moyenneRessource = 0;
        for(unsigned int j = 0; j < Jk[i].size(); j++){
            for (unsigned int r = 0; r < this->instance.getNbrRessources(); r++){
                moyenneRessource += this->instance.getTableauRessourcesJobs()[Jk[i][j]][r];
            }
        }
        moyenneRessource /= Jk[i].size();
        moyenneRessourceJk.push_back(moyenneRessource);
    }

    //Trie par ordre croissant de moyennes de ressources pour chaque sous-ensembles
    bool tab_en_ordre = false;
    unsigned int taille = Jk.size();
    while(!tab_en_ordre)
    {
        tab_en_ordre = true;
        for(unsigned int i=0 ; i < taille-1 ; i++)
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

    vector<unsigned int> tableauJobs;

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

/**
 * @brief Affectation machine par machine
 *
 * @param typeTri Le type de tri à utiliser avant l'affectation
 * @param fichierResultat Le fichier où seront stockés les résulats
 * @return unsigned int Le nombre de jobs ordonnancés
 */
unsigned int Heuristique::resolveMachinePerMachine(QString typeTri, QString fichierResultat){

    //Déclaration de variable en local pour améliorer les performances des heuristiques
    unsigned int nbr_machines = this->instance.getNbrMachines();
    unsigned int nbr_ressources = this->instance.getNbrRessources();
    vector<unsigned int> s_j = this->instance.getSj();
    vector<unsigned int> f_j = this->instance.getFj();

    vector<vector<unsigned int>> capRessources = this->instance.getCapRessources();
    vector<vector<unsigned int>> tableauRessourcesJobs = this->instance.getTableauRessourcesJobs();

    auto start = std::chrono::high_resolution_clock::now();

    vector<unsigned int> tableauJobs;

    if(typeTri == "CCmaxSommeRessources") tableauJobs = this->trierCCmaxSommeRessources();
    if(typeTri == "CCmaxMaxRessources") tableauJobs = this->trierCCmaxMaxRessources();
    if(typeTri == "SommeRessources") tableauJobs = this->trierSommeRessources();
    if(typeTri == "MoyenneRessourcesSousEnsembles") tableauJobs = this->trierMoyenneRessourcesSousEnsembles();

    vector<vector<unsigned int>> jobsOrdonnances;
    for(unsigned int m = 0; m < nbr_machines ; m++){
        vector<unsigned int> jobsMachine;
        vector<unsigned int> Lm = tableauJobs;
        while(Lm.size() != 0){
            vector<unsigned int> Sm;
            for(unsigned int i = 0; i < jobsMachine.size(); i++){
                if(s_j[Lm[0]] < f_j[jobsMachine[i]] && f_j[Lm[0]] > s_j[jobsMachine[i]]){
                    Sm.push_back(jobsMachine[i]);
                }
            }

            bool jobOrdonancable = true;

            for(unsigned int i = s_j[Lm[0]]; i < f_j[Lm[0]]; i++){
                for(unsigned int r = 0; r < nbr_ressources ; r++){
                    unsigned int sommesRessources = 0;
                    for(unsigned int j = 0; j < Sm.size(); j++){
                        if(s_j[Sm[j]] <= i && f_j[Sm[j]] > i )
                        sommesRessources += tableauRessourcesJobs[Sm[j]][r];
                    }
                    sommesRessources += tableauRessourcesJobs[Lm[0]][r];
                   // cout << "Sommes Ressources : " << sommesRessources << endl;
                    if(sommesRessources > capRessources[r][m])
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

    return this->resultat.sauvegarderResultat(this->instance, jobsOrdonnances, "Affectation1-"+typeTri, fichierResultat, time);

}

/**
 * @brief Affectation privilégiant la machine la moins chargée
 *
 * @param typeTri Le type de tri à utiliser avant l'affectation
 * @param fichierResultat Le fichier où seront stockés les résulats
 * @return unsigned int Le nombre de jobs ordonnancés
 */

unsigned int Heuristique::resolveMachineLessUsedMachine(QString typeTri, QString fichierResultat){

    //Déclaration de variable en local pour améliorer les performances des heuristiques
    unsigned int nbr_machines = this->instance.getNbrMachines();
    unsigned int nbr_ressources = this->instance.getNbrRessources();
    vector<unsigned int> sj = this->instance.getSj();
    vector<unsigned int> fj = this->instance.getFj();

    vector<vector<unsigned int>> capRessources = this->instance.getCapRessources();
    vector<vector<unsigned int>> tableauRessourcesJobs = this->instance.getTableauRessourcesJobs();

    auto start = std::chrono::high_resolution_clock::now();

    vector<unsigned int> tableauJobs;

    if(typeTri == "CCmaxSommeRessources") tableauJobs = this->trierCCmaxSommeRessources();
    if(typeTri == "CCmaxMaxRessources") tableauJobs = this->trierCCmaxMaxRessources();
    if(typeTri == "SommeRessources") tableauJobs = this->trierSommeRessources();
    if(typeTri == "MoyenneRessourcesSousEnsembles") tableauJobs = this->trierMoyenneRessourcesSousEnsembles();

    vector<vector<unsigned int>> jobsOrdonnances;
    for(unsigned int m = 0; m < nbr_machines ; m++){
        vector<unsigned int> tableauMachines;
        jobsOrdonnances.push_back(tableauMachines);
    }
    while(tableauJobs.size() != 0){
        vector<vector<unsigned int>> chargeEnsemblesMachine;
        for(unsigned int m = 0; m < nbr_machines ; m++){
            vector<unsigned int> chargeMachine;
            chargeMachine.push_back(m);
            unsigned int charge = 0;
            for(unsigned int i = sj[tableauJobs[0]]; i < fj[tableauJobs[0]]; i++){
                for(unsigned int r = 0; r < nbr_ressources ; r++){
                    for(unsigned int j = 0; j < jobsOrdonnances[m].size(); j++){
                        if(sj[jobsOrdonnances[m][j]] <= i && fj[jobsOrdonnances[m][j]] > i )
                            charge += tableauRessourcesJobs[jobsOrdonnances[m][j]][r];
                    }
                }
            }
            chargeMachine.push_back(charge);
            chargeEnsemblesMachine.push_back(chargeMachine);
            //cout << "Machine : " << m << " Charge : " << charge << endl;
        }
        //Trie à bulle des machines suivant la charge sur chacune d'elles
        bool tab_en_ordre = false;
        unsigned int taille = nbr_machines;
        while(!tab_en_ordre)
        {
            tab_en_ordre = true;
            for(unsigned int i=0 ; i < taille-1 ; i++)
            {
                if(chargeEnsemblesMachine[i][1] > chargeEnsemblesMachine[i+1][1])
                {
                    swap(chargeEnsemblesMachine[i],chargeEnsemblesMachine[i+1]);
                    tab_en_ordre = false;
                }
            }
            taille--;
        }

        unsigned int numeroJob = tableauJobs[0];

        for (unsigned int m = 0; m < chargeEnsemblesMachine.size(); m++){
            if(numeroJob == tableauJobs[0] && tableauJobs.size() != 0){
                vector<unsigned int> Sm;
                for(unsigned int i = 0; i < jobsOrdonnances[chargeEnsemblesMachine[m][0]].size(); i++){

                    if(sj[tableauJobs[0]] < fj[jobsOrdonnances[chargeEnsemblesMachine[m][0]][i]] &&
                            fj[tableauJobs[0]] > sj[jobsOrdonnances[chargeEnsemblesMachine[m][0]][i]])
                    {
                        Sm.push_back(jobsOrdonnances[chargeEnsemblesMachine[m][0]][i]);
                    }

                }

                bool jobOrdonancable = true;

                for(unsigned int i = sj[tableauJobs[0]]; i < fj[tableauJobs[0]]; i++){
                    for(unsigned int r = 0; r < nbr_ressources ; r++){
                        unsigned int sommesRessources = 0;
                        for(unsigned int j = 0; j < Sm.size(); j++){
                            if(sj[Sm[j]] <= i && fj[Sm[j]] > i )
                            sommesRessources += tableauRessourcesJobs[Sm[j]][r];
                        }
                        sommesRessources += tableauRessourcesJobs[tableauJobs[0]][r];
                        //cout << "Sommes Ressources : " << sommesRessources << endl;
                        if(sommesRessources > capRessources[r][chargeEnsemblesMachine[m][0]])
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

    return this->resultat.sauvegarderResultat(this->instance, jobsOrdonnances, "Affectation2-"+typeTri, fichierResultat, time);

}

/**
 * @brief Getter de l'instance pour laquelle on veut appliquer une heuristique
 *
 * @return Instance L'instance pour laquelle on veut appliquer une heuristique
 */
Instance Heuristique::getInstance() const
{
    return instance;
}


/**
 * @brief Setter de l'instance pour laquelle on veut appliquer une heuristique
 *
 * @param value L'instance pour laquelle on veut appliquer une heuristique
 */
void Heuristique::setInstance(Instance value)
{
    instance = value;
}
