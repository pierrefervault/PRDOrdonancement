#include "heuristic.h"
#include <iostream>
#include <fstream>

Heuristic::Heuristic(string filename)
{
    std::ifstream f(filename);
    if (!f)
    {
        cout << filename <<" invalid file" << endl;
    }


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

vector<int> Heuristic::trierCCmax(){

    //Ici on créer le tableau de valeur pour CCMax
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

    //Trie par ordre croissant du tableau de job
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

    vector<int> tableauJobs;

    for (int i = 0; i < this->nbr_jobs; i++){
        //cout << tableauInitial[i][0] << " " << tableauInitial[i][1] << endl;
        tableauJobs.push_back(tableauInitial[i][0]);
    }

    return tableauJobs;

}

vector<int> Heuristic::trierSommeRessources(){

    //Ici on créer le tableau de valeur pour SommeRessources
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

    //Trie par ordre croissant du tableau de job
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

    vector<int> tableauJobs;

    for (int i = 0; i < this->nbr_jobs; i++){
        cout << tableauInitial[i][0] << " " << tableauInitial[i][1] << endl;
        tableauJobs.push_back(tableauInitial[i][0]);
    }

    return tableauJobs;

}

vector<int> Heuristic::trierMoyenneRessourcesSousEnsembles(){

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


    cout << endl;

    for (int i=0; i < (this->nbr_jobs * 2); i++){
        cout << eh[i][0] << " " << eh[i][1] << " " << eh[i][2] << " " << endl;
    }

    //Trie à bulle du tableau d'événement eh
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

    map<int,vector<int>> Jk = getSubset(eh, this->nbr_jobs);


    vector<int> moyenneRessourceJk;

    //Calcul des moyennes de ressources par sous-ensembles
    for(int i = 0 ; i < Jk.size(); i++){
        int moyenneRessource = 0;
        for(int j = 0; j < Jk[i].size(); j++){
            cout << Jk[i][j] << " ";
            for (int r = 0; r < this->nbr_ressources; r++){
                moyenneRessource += this->C[Jk[i][j]][r];
            }
        }
        cout << endl;
        moyenneRessource /= Jk[i].size();
        moyenneRessourceJk.push_back(moyenneRessource);
        cout << moyenneRessourceJk[i] << endl;
    }

    //Trie à bulle des sous-ensembles
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

    vector<int> tableauJobs;

    for(int i = 0 ; i < Jk.size(); i++){
        for(int j = 0; j < Jk[i].size(); j++){
            if(std::find(tableauJobs.begin(), tableauJobs.end(), Jk[i][j]) == tableauJobs.end())
            {
              tableauJobs.push_back(Jk[i][j]);
            }
        }
    }

    cout << endl;
    for(int i = 0; i < tableauJobs.size(); i++) {
        cout << tableauJobs[i] << " ";
    }
    cout << endl;

    return tableauJobs;

}

map<int,vector<int>> Heuristic::getSubset(vector<vector<int>> eh, int nb_job){
    map<int,vector<int>> Jk;
    int k = 0; //numero du sous-ensemble maximal
    int inc = 0; //Permet de savoir si on doit encore enlever des jobs du sous ensembles après une première supression
    int nbStartEvent = 0;
    for(int h = 0 ; h < (nb_job * 2); h++){
        if(eh[h][2] == 1){
            nbStartEvent++;
            Jk[k].push_back(eh[h][1]);
            inc = 0;
           // cout << "Startevent :"<< nbStartEvent << " SousEnsembles : " << k << " Job : " << eh[h][1] << endl;
        }
        else{
            if(nbStartEvent == nb_job){
                return Jk;
            }
            else{
                if(inc == 0){
                    inc = 1;
                    k++;
                    Jk[k] = Jk[k-1];
                    for (std::vector<int>::iterator it = Jk[k].begin(); it != Jk[k].end();) {
                        if (*it == eh[h][1]) {
                            it = Jk[k].erase(it);
                        } else {
                            ++it;
                        }
                    }
                }
                else{
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

void Heuristic::resolveMachinePerMachine(vector<int> tableauJobs){

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

    int nbrJobsOrdonnances = 0;
    for(int i = 0; i < jobsOrdonnances.size(); i++){
        cout << "Machines : " << i << " : ";
        for(int j = 0; j < jobsOrdonnances[i].size(); j++){
            cout << jobsOrdonnances[i][j] << " ";
            nbrJobsOrdonnances++;
        }
        cout << endl;
    }
    cout << "Nombre de jobs Ordonnances : " << nbrJobsOrdonnances << endl;

}
