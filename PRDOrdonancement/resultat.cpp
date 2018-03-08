#include "resultat.h"

/**
 * @brief Le constructeur de la classe Resultat
 *
 */
Resultat::Resultat()
{
    this->setNbrJobs(0);
    this->setNbrRessources(0);
    this->setNbrMachines(0);
}

/**
 * @brief Permet de charger un résulat à partir d'un fichier de résultat
 *
 * @param fichierResultat Le fichier contenant les données spécifiques à des résultats de résolution
 */
void Resultat::chargerResultat(QString fichierResultat){
    this->fichierResultat = fichierResultat;

    std::ifstream f(fichierResultat.toStdString());

    if (!f)
    {
        cout << fichierResultat.toStdString() <<" invalid file" << endl;
    }

    this->nbrJobs = (unsigned int) fichierResultat.split("/")[2].toInt();
    this->nbrRessources = (unsigned int) fichierResultat.split("/")[3].toInt();
    this->nbrMachines = (unsigned int) fichierResultat.split("/")[4].toInt();

    string line;

    vector <unsigned int> solutionTrouve;
    vector<double> tempsExecution;

    while(getline(f,line)) {
        cout << line << endl ;
        getline(f,line);

        getline(f,line);
        QString ligneOptimale = QString::fromStdString(line);
        unsigned int optimal = ligneOptimale.split("=")[1].toInt();
        solutionTrouve.push_back(optimal);

        getline(f,line);
        QString tempsEcoule = QString::fromStdString(line);
        tempsExecution.push_back(tempsEcoule.split(":")[1].toDouble());

        getline(f,line);
        for (int i = 0; i < fichierResultat.split("/")[4].toInt() ; i++){
            getline(f,line);
        }

        getline(f,line);
        for (unsigned int i = 0; i < optimal ; i++){
            getline(f,line);
        }
    }

    f.close();

    this->solutions = solutionTrouve;
    this->tempsExecution = tempsExecution;
}


/**
 * @brief Permet de sauvegarder le résultat d'une résolution d'instance dans un fichier de résultat
 *
 * @param instance L'instance que l'on a résolu
 * @param jobsOrdonnances Le tableau de jobs ordonancés
 * @param typeResolution Le type de résolution
 * @param fichierResultat Le fichier où seront stockés les résulats
 * @param dureeExecution La durée d'execution de la résolution
 * @return unsigned int Le nombre de jobs ordonnancés
 */
unsigned int Resultat::sauvegarderResultat(Instance instance, vector<vector<unsigned int>> jobsOrdonnances, QString typeResolution, QString fichierResultat, double dureeExecution){

    unsigned int nbrJobsOrdonnances = 0;
    for(unsigned int i = 0; i < jobsOrdonnances.size(); i++){
        //cout << "Machines : " << i << " : ";
        for(unsigned int j = 0; j < jobsOrdonnances[i].size(); j++){
            cout << jobsOrdonnances[i][j] << " ";
            nbrJobsOrdonnances++;
        }
        //cout << endl;
    }

    ofstream output_file(fichierResultat.toStdString(),ios::app);

    output_file << "Instance:" << instance.getFichierInstance().toStdString() << endl;
    output_file << "Solution status:" << typeResolution.toStdString() << endl;
    output_file << " Optimal Value=" << nbrJobsOrdonnances << endl;

    output_file << "temps écoulé (en secondes):" << dureeExecution << endl;

    output_file << "IdMachine " << "Nombre de jobs ordonnancés" << endl;

    for(unsigned int i = 0; i < jobsOrdonnances.size(); i++){
        output_file << i << " " << jobsOrdonnances[i].size() << endl;
    }

    output_file << "IdMachine " << "n°Job " << "Si " << "Fi " << endl;

    for(unsigned int i = 0; i < jobsOrdonnances.size(); i++){
        for(unsigned int j = 0; j < jobsOrdonnances[i].size(); j++){
            output_file << i << " " << jobsOrdonnances[i][j] << " " << instance.getSj()[jobsOrdonnances[i][j]] << " " << instance.getFj()[jobsOrdonnances[i][j]] << endl;
        }
    }

    return nbrJobsOrdonnances;
}


/**
 * @brief Getter permetant d'obtenir le tableau contenant l'ensemble des solutions trouvées
 *
 * @return vector<unsigned int> Le tableau contenant l'ensemble des solutions trouvées
 */
vector<unsigned int> Resultat::getSolutions() const
{
    return solutions;
}

/**
 * @brief Setter permetant de spécifier le tableau contenant l'ensemble des solutions trouvées
 *
 * @param value Le tableau contenant l'ensemble des solutions trouvées
 */
void Resultat::setSolutions(const vector<unsigned int> &value)
{
    solutions = value;
}

/**
 * @brief Getter permetant d'obtenir le tableau contenant les temps de calcul pour chaque solution
 *
 * @return vector<double> Le tableau contenant les temps de calcul pour chaque solution
 */
vector<double> Resultat::getTempsExecution() const
{
    return tempsExecution;
}

/**
 * @brief Getter permetant d'obtenir le nombre de jobs pour chaque solution
 *
 * @return unsigned int Le nombre de jobs pour chaque solution
 */
unsigned int Resultat::getNbrJobs() const
{
    return nbrJobs;
}

/**
 * @brief Setter permetant de spécifier le nombre de jobs pour chaque solution
 *
 * @param value Le nombre de jobs pour chaque solution
 */
void Resultat::setNbrJobs(unsigned int value)
{
    nbrJobs = value;
}

/**
 * @brief Getter permetant d'obtenir le nombre de ressources pour chaque solution
 *
 * @return unsigned int Le nombre de ressources pour chaque solution
 */
unsigned int Resultat::getNbrRessources() const
{
    return nbrRessources;
}

/**
 * @brief Setter permetant de spécifier le nombre de ressources pour chaque solution
 *
 * @param value Le nombre de ressources pour chaque solution
 */
void Resultat::setNbrRessources(unsigned int value)
{
    nbrRessources = value;
}

/**
 * @brief Getter permetant d'obtenir le nombre de machines pour chaque solution
 *
 * @return unsigned int Le nombre de machines pour chaque solution
 */
unsigned int Resultat::getNbrMachines() const
{
    return nbrMachines;
}

/**
 * @brief Setter permetant de spécifier le nombre de machines pour chaque solution
 *
 * @param value Le nombre de machines pour chaque solution
 */
void Resultat::setNbrMachines(unsigned int value)
{
    nbrMachines = value;
}

/**
 * @brief Getter permetant d'obtenir le fichier de resultat
 *
 * @return unsigned int Le le fichier de resultat
 */
QString Resultat::getFichierResultat() const
{
    return fichierResultat;
}

/**
 * @brief Setter permetant de spécifier le fichier de resultat
 *
 * @return unsigned int Le le fichier de resultat
 */
void Resultat::setFichierResultat(const QString &value)
{
    fichierResultat = value;
}
