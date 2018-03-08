#include "workercomparaison.h"
#include "fstream"
#include "calculcomparaison.h"

/**
 * @brief Constructeur de la classe WorkerComparaison
 *
 * @param dossierResultat Le chemin vers le dossier contenant les résultats des méthodes de résolution
 * @param typeComparaison Le type de comparaison à effectuer
 */
WorkerComparaison::WorkerComparaison(QString dossierResultat, QString typeComparaison, int nbrRessources, int nbrMachines){
    this->dossierResultat = dossierResultat;
    this->typeComparaison = typeComparaison;
    this->nbrRessources = nbrRessources;
    this->nbrMachines = nbrMachines;
}

/**
 * @brief Destructeur de la classe WorkerComparaison
 *
 */
WorkerComparaison::~WorkerComparaison(){

}

/**
 * @brief Action effectuée lors du lancement du worker
 *
 */
void WorkerComparaison::process(){

    QString dossierResultat = this->dossierResultat;
    QFileInfo path(dossierResultat);

    QStringList filter;
    filter << "*-"+QString::number(nbrRessources)+"-"+QString::number(nbrMachines)+".data";

    cout << filter[0].toStdString() << endl;

    QDirIterator it(dossierResultat, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList files;
    while (it.hasNext())
        files << it.next();
    files.sort();

    std::list<QString> list = files.toStdList();

    map<unsigned int,vector<Resultat>> tableauComparaison;

    for(std::list<QString>::iterator it = list.begin() ; it != list.end() ; ++it){

        QString fichier = *it;

        Resultat resultat;

        resultat.chargerResultat(fichier);

        tableauComparaison[fichier.split("/")[fichier.split("/").size()-4].toInt()].push_back(resultat);

    }

    CalculComparaison calculComparaison;

    if (this->typeComparaison == "Gap"){
        emit updateLayout(calculComparaison.calculGap(tableauComparaison), this->typeComparaison);
    }

    if (this->typeComparaison == "PourcentageSolutionsOptimales"){
        emit updateLayout(calculComparaison.calculPourcentageSolutionOptimale(tableauComparaison), this->typeComparaison);
    }

    if (this->typeComparaison == "PourcentageTempsResolutionExacte"){
        emit updateLayout(calculComparaison.calculPourcentageTempsResolution(tableauComparaison), this->typeComparaison);
    }

    emit finished();
}
