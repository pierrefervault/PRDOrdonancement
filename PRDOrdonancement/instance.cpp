#include "instance.h"

/**
 * @brief Constructeur de la classe Instance
 *
 */
Instance::Instance()
{

}

/**
 * @brief Permet de charger une instance à partir d'un chemin vers un fichier d'instance
 *
 * @param fichierInstance Le chemin vers le fichier d'instance
 */
void Instance::chargerInstance(string fichierInstance){

    //On cherche à lire le fichier, si ce n'est pas possible on l'indique
    std::ifstream f(fichierInstance);
    if (!f)
    {
        cout << fichierInstance <<" invalid file" << endl;
    }

    this->fichierInstance = QString::fromStdString(fichierInstance);

    //Nous spécifions en attribut le nombre de jobs, de ressources et de machines selon ce qu'on a lu dans le fichier
    unsigned int i;

    f >> nbrJobs >> nbrRessources >> nbrMachines;

    capRessources.clear();

    //Ici on créer un tableau contenant la capacité en ressources pour la ressource r de chaque machine
    for (unsigned int r=0; r < nbrRessources ; r++)
    {
        vector<unsigned int> ressources;
        for (unsigned int machine=0; machine < nbrMachines ; machine++)
        {
            unsigned int value;
            f >> value;
            ressources.push_back(value);
        }
        capRessources.push_back(ressources);
    }

    //cout << "Nombre de jobs : " << nb_job << endl;

    unsigned int id , s_i , f_i ;

    sj.clear();
    fj.clear();

    horizonMax = 0;

    //Ici, on mets à jour les instant de début et de fin pour chaque job
    for (i=0 ; i < nbrJobs ; i++)
    {
        f >> id >> s_i >> f_i ;

        sj.push_back(s_i);
        fj.push_back(f_i);


        if (horizonMax <= f_i ) horizonMax = f_i;


        //cout << id << " " << s_i << " " << f_i << " " << endl;
    }

    //Ici, on créer le tableau ou est stocké pour chaque job i la valeur pour la ressource r associée au job

    tableauRessourcesJobs.clear();

    for( i=0 ; i< nbrJobs ; i++)
    {
        vector<unsigned int> ressources;

        for (unsigned int r=0; r < nbrRessources ; r++)
        {
            unsigned int value;
            f >> value;
            ressources.push_back(value);
        }
        tableauRessourcesJobs.push_back(ressources);
    }
}


/**
 * @brief
 *
 * @param nbrInstance Le nombre d'instance à générer
 * @param nbrJobs Le nombre de jobs par instance
 * @param nbrRessources Le nombre de ressources par instance
 * @param nbrMachines Le nombre de machines par instance
 * @param horizonPlanification L'horizon de planification maximal de chaque instance
 */
void Instance::sauvegarderInstance(unsigned int nbrInstance, unsigned int nbrJobs, unsigned int nbrRessources, unsigned int nbrMachines, unsigned int horizonPlanification){

    std::random_device rd;
    std::mt19937 gen(rd());

    unsigned int numInstance;
    unsigned int numJob;
    unsigned int numRessource;
    unsigned int numMachine;

    unsigned int dossier = 0;

    string cheminDossier = "Instances/"+to_string(dossier)+"/"+to_string(nbrJobs)+"/"+to_string(nbrRessources)+"/"+to_string(nbrMachines);

    QDir *repertoire = new QDir(QString::fromStdString(cheminDossier));

    //J'ai limité à 1000 sous-dossiers différents
    while (repertoire->exists() && dossier < 1000){
        dossier++;
        cheminDossier = "Instances/"+to_string(dossier)+"/"+to_string(nbrJobs)+"/"+to_string(nbrRessources)+"/"+to_string(nbrMachines);
        repertoire->setPath(QString::fromStdString(cheminDossier));
    }

    repertoire->mkpath(".");

    for(numInstance = 0; numInstance < nbrInstance; numInstance++){


        ofstream fichier(cheminDossier+"/instance"+to_string(numInstance)+"-"+to_string(nbrJobs)+"-"+to_string(nbrRessources)
                         +"-"+to_string(nbrMachines)+".data", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert

        if(fichier){

            fichier << nbrJobs << " " << nbrRessources
                    << " " << nbrMachines << endl;

            for (numMachine = 0; numMachine < nbrMachines; numMachine++){

                for (numRessource = 0; numRessource < nbrRessources; numRessource++){

                    fichier << "1000";

                    if (numRessource != nbrRessources-1){
                        fichier << " ";
                    }
                }

                fichier << endl;
            }

            fichier << endl;

            std::uniform_int_distribution<> dis(0, horizonPlanification - 1);

            for (numJob = 0; numJob < nbrJobs; numJob++){
                unsigned int startTime = dis(rd);
                std::uniform_int_distribution<> disFinish(startTime + 1, horizonPlanification);
                unsigned int finishTime = disFinish(rd);
                fichier << numJob << "\t" << startTime << "\t" << finishTime << endl;
            }

            fichier << endl;

            std::uniform_int_distribution<> disRessource(1, 1000);

            for (numJob = 0; numJob < nbrJobs; numJob++){
                for (numRessource = 0; numRessource < nbrRessources; numRessource++){
                    fichier << disRessource(rd);
                    if (numRessource != nbrRessources-1){
                        fichier << " ";
                    }
                }
                fichier << endl;
            }
            fichier.close();
        }
        else cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
}


/**
 * @brief Retourne les sous-ensembles maximaux de jobs de l'instance (jobs se chevauchant)
 *
 * @return map<unsigned int, vector<unsigned int> > Les sous-ensembles maximaux de jobs de l'instance
 */
map<unsigned int,vector<unsigned int>> Instance::getSousEnsemblesMaximaux(){

    //On crée le tableau d'événement eh nécessaire à la création des sous-ensembles de jobs maximaux
    vector<vector<unsigned int>> eh;
    for (unsigned int i=0 ; i < nbrJobs ; i++)
    {
        vector<unsigned int> debut;
        debut.push_back(sj[i]);
        debut.push_back(i);
        debut.push_back(1);
        debut.push_back(fj[i]);

        eh.push_back(debut);

        vector<unsigned int> fin;
        fin.push_back(fj[i]);
        fin.push_back(i);
        fin.push_back(0);
        fin.push_back(fj[i]);

        eh.push_back(fin);
    }

    //Trie à bulle du tableau d'événement eh suivant l'ordre défini par l'algorithme
    bool tab_en_ordre = false;
    unsigned int taille = nbrJobs*2;
    while(!tab_en_ordre)
    {
        tab_en_ordre = true;
        for(unsigned int i=0 ; i < taille-1 ; i++)
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

    map<unsigned int,vector<unsigned int>> Jk;

    //numero du sous-ensemble maximal
    unsigned int k = 0;

    //Permet de savoir si on doit encore enlever des jobs du sous ensembles après une première supression
    unsigned int inc = 0;

    //Nombre d'événement de typesj parcourus
    unsigned int nbStartEvent = 0;

    for(unsigned int h = 0 ; h < nbrJobs * 2; h++){

        //Si l'événement est de typesj, on ajoute le job correspondant au sous-ensemble k
        if(eh[h][2] == 1){
            nbStartEvent++;
            Jk[k].push_back(eh[h][1]);

            //On spécifie que le sous-ensemble est maximal
            inc = 0;
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
                    for (std::vector<unsigned int>::iterator it = Jk[k].begin(); it != Jk[k].end();) {
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

                    for (std::vector<unsigned int>::iterator it = Jk[k].begin(); it != Jk[k].end();) {
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
    return Jk;
}

/**
 * @brief Permet de retourner le chemin vers le fichier d'instance
 *
 * @return QString Le chemin vers le fichier d'instance
 */
QString Instance::getFichierInstance() const
{
    return fichierInstance;
}

/**
 * @brief Setter du chemin vers le fichier d'instance
 *
 * @param value Le chemin vers le fichier d'instance que l'on souhaite
 */
void Instance::setFichierInstance(const QString &value)
{
    fichierInstance = value;
}

/**
 * @brief Permet d'obtenir le nombre de jobs de l'instance
 *
 * @return unsigned int Le nombre de jobs
 */
unsigned int Instance::getNbrJobs() const
{
    return nbrJobs;
}

/**
 * @brief Setter du nombre de jobs de l'instance
 *
 * @param value Le nombre de jobs souhaité de l'instance
 */
void Instance::setNbrJobs(unsigned int value)
{
    nbrJobs = value;
}

/**
 * @brief Permet d'obtenir le nombre de ressources de l'instance
 *
 * @return unsigned int Le nombre de ressources
 */
unsigned int Instance::getNbrRessources() const
{
    return nbrRessources;
}

/**
 * @brief Setter du nombre de ressources de l'instance
 *
 * @param value Le nombre de ressources souhaité de l'instance
 */
void Instance::setNbrRessources(unsigned int value)
{
    nbrRessources = value;
}

/**
 * @brief Permet d'obtenir le nombre de machines de l'instance
 *
 * @return unsigned int Le nombre de machines
 */
unsigned int Instance::getNbrMachines() const
{
    return nbrMachines;
}

/**
 * @brief Setter du nombre de machines de l'instance
 *
 * @param value Le nombre de machines souhaité de l'instance
 */
void Instance::setNbrMachines(unsigned int value)
{
    nbrMachines = value;
}

/**
 * @brief Permet d'obtenir le tableau des instants de départ de l'ensemble des jobs
 *
 * @return vector<unsigned int> Le tableau des instants de départ de l'ensemble des jobs
 */
vector<unsigned int> Instance::getSj() const
{
    return sj;
}

/**
 * @brief Setter du tableau des instants de départ de l'ensemble des jobs
 *
 * @param value Le tableau des instants de départ de l'ensemble des jobs souhaité
 */
void Instance::setSj(const vector<unsigned int> &value)
{
   sj = value;
}

/**
 * @brief Permet d'obtenir le tableau des instants de fin de l'ensemble des jobs
 *
 * @return vector<unsigned int> Le tableau des instants de fin de l'ensemble des jobs
 */
vector<unsigned int> Instance::getFj() const
{
    return fj;
}

/**
 * @brief Setter du tableau des instants de fin de l'ensemble des jobs
 *
 * @param value Le tableau des instants de fin de l'ensemble des jobs souhaité
 */
void Instance::setFj(const vector<unsigned int> &value)
{
    fj = value;
}

/**
 * @brief Permet d'obtenir le tableau des capacités en ressource pour l'ensemble des machines
 *
 * @return vector<vector<unsigned int>> Le tableau des capacités en ressource pour l'ensemble des machines
 */
vector<vector<unsigned int> > Instance::getCapRessources() const
{
    return capRessources;
}

/**
 * @brief Setter du tableau des capacités en ressource pour l'ensemble des machines
 *
 * @param value Le tableau des capacités en ressource pour l'ensemble des machines souhaité
 */
void Instance::setCapRessources(const vector<vector<unsigned int> > &value)
{
    capRessources = value;
}

/**
 * @brief Permet d'obtenir le tableau des capacités en ressource pour l'ensemble des jobs
 *
 * @return vector<vector<unsigned int>> Le tableau des capacités en ressource pour l'ensemble des jobs
 */
vector<vector<unsigned int> > Instance::getTableauRessourcesJobs() const
{
    return tableauRessourcesJobs;
}

/**
 * @brief Setter du tableau des capacités en ressource pour l'ensemble des jobs
 *
 * @param value Le tableau des capacités en ressource pour l'ensemble des jobs souhaité
 */
void Instance::setTableauRessourcesJobs(const vector<vector<unsigned int> > &value)
{
    tableauRessourcesJobs = value;
}

/**
 * @brief Permet d'obtenir l'horizon maximale de planification de l'instance
 *
 * @return unsigned int L'horizon maximale de planification de l'instance
 */
unsigned int Instance::getHorizonMax() const
{
    return horizonMax;
}

/**
 * @brief Setter de l'horizon maximale de planification de l'instance
 *
 * @param value L'horizon maximale de planification de l'instance souhaitée
 */
void Instance::setHorizonMax(unsigned int value)
{
    horizonMax = value;
}
