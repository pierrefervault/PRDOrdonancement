#include "heuristic.h"
#include <iostream>
#include <fstream>

Heuristic::Heuristic()
{

}

void Heuristic::trierCCmax(string filename){

    std::ifstream f(filename);
    if (!f)
    {
        cout << filename <<" invalid file" << endl;
    }


    int i, m;
    int nb_job , nb_ressources, nb_machines ;
    f >> nb_job >> nb_ressources >> nb_machines;

    int cap_ressources[nb_ressources][nb_machines];

    //Ici on créer un tableau contenant la capacité en ressources pour la ressource r de chaque machine
    for (int r=0; r < nb_ressources ; r++)
    {
        //cap_ressources[r] = IloIntArray (env, nb_machines);
        //f >> cap_ressources[r];
        //cout << "Nombre de machines : " << nb_machines << endl;
        for (int machine=0; machine < nb_machines ; machine++)
        {
            f >> cap_ressources[r][machine];
            //cout <<  cap_ressources[r][machine] << " ";
        }
        //cout << endl;
    }

    //cout << "Nombre de jobs : " << nb_job << endl;

    int S_j[nb_job];
    int F_j[nb_job];
    int id , s_i , f_i ;
    int cmax=0;

    //Ici, on mets à jour les instant de début et de fin pour chaque job
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
    int C [nb_job][nb_ressources];

    for( i=0 ; i<nb_job ; i++)
    {
        //C[i] = IloNumArray  (env,nb_ressources);
        for (int r=0; r < nb_ressources ; r++)
        {
            //f >> cap;
            //C[i][r]=cap;
            f >> C[i][r];
            //	cout << C[i][r] << " ";
        }

        //	cout << endl;
    }

    //Ici on créer le tableau de valeur pour CCMax
    int tableauInitial [nb_job][2];

    for( i=0 ; i<nb_job ; i++)
    {
        for (int r=0; r < nb_ressources ; r++)
        {
            tableauInitial[i][0] = i;
            tableauInitial[i][1] = C[i][r] * (F_j[i]-S_j[i]);
        }
    }

    //Trie par ordre croissant du tableau de job
    bool tab_en_ordre = false;
    int taille = nb_job;
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

    for (i=0; i < nb_job; i++){
        cout << tableauInitial[i][0] << " " << tableauInitial[i][1] << endl;
    }

}
