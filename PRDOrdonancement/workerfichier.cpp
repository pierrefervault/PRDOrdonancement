#include "workerfichier.h"

/**
 * @brief Constructeur de la classe WorkerFichier
 *
 * @param fichierInstance Le chemin vers le fichier d'instance
 * @param typeResolution Le type de résolution à effectuer
 */
WorkerFichier::WorkerFichier(QString fichierInstance, QString typeResolution, map<unsigned int, unsigned int> pourcentagesParAgent)
{
    this->fichierInstance = fichierInstance;
    this->typeResolution = typeResolution;
    this->pourcentagesParAgent= pourcentagesParAgent;
}

/**
 * @brief Destructeur de la classe WorkerFichier
 *
 */
WorkerFichier::~WorkerFichier(){

}

/**
 * @brief Action effectuée lors du lancement du worker
 *
 */
void WorkerFichier::process(){
    //On récupère le chemin du fichier
    QString fichierInstance = this->fichierInstance;

    //On récupère le nom du fichier
    QFileInfo path(fichierInstance);
    QString fichier = path.fileName();

    //On crée le nouveau répertoire
    QString tmpFolder = fichierInstance.right(fichierInstance.size()-fichier.split("-")[0].size());
    QDir repertoire = QDir("Resultat"+tmpFolder.left(tmpFolder.size()-fichier.size()-1));
    repertoire.mkpath(".");

    if (typeResolution.split(" ")[0] == "mip1"){
        //On donne le nouveau chemin pour le fichier de résultat
        QString fichierResultat = repertoire.path()+"/resolutionMip1"+fichier.right(fichier.size()-fichier.split("-")[0].size());

        MethodeExacte methodeExacte(fichierInstance.toStdString(), this->pourcentagesParAgent);
        methodeExacte.resolutionPlneMip1(fichierResultat.toStdString());
    }
    if (typeResolution.split(" ")[0] == "mip2"){
        //On donne le nouveau chemin pour le fichier de résultat
        QString fichierResultat = repertoire.path()+"/resolutionMip2"+fichier.right(fichier.size()-fichier.split("-")[0].size());

        MethodeExacte methodeExacte(fichierInstance.toStdString(), this->pourcentagesParAgent);
        methodeExacte.resolutionPlneMip2(fichierResultat.toStdString());
    }

    if (typeResolution.split(" ")[0] == "mip1MultiAgent"){
        //On donne le nouveau chemin pour le fichier de résultat
        QString fichierResultat = repertoire.path()+"/resolutionMip1MultiAgent"+fichier.right(fichier.size()-fichier.split("-")[0].size());

        MethodeExacte methodeExacte(fichierInstance.toStdString(), this->pourcentagesParAgent);
        methodeExacte.resolutionPlneMip1MultiAgent(fichierResultat.toStdString());
    }
    if (typeResolution.split(" ")[0] == "mip2MultiAgent"){
        //On donne le nouveau chemin pour le fichier de résultat
        QString fichierResultat = repertoire.path()+"/resolutionMip2MultiAgent"+fichier.right(fichier.size()-fichier.split("-")[0].size());

        MethodeExacte methodeExacte(fichierInstance.toStdString(), this->pourcentagesParAgent);
        methodeExacte.resolutionPlneMip2MultiAgent(fichierResultat.toStdString());
    }

    if (typeResolution.split(" ")[0] == "Affectation1"){

        Heuristique heuristic(fichierInstance.toStdString(), this->pourcentagesParAgent);

        //On donne le nouveau chemin pour le fichier de résultat (on enlève 8 caractères au nom de fichier initial qui correspondent à "instance")
        QString fichierResultat = repertoire.path()+"/Affectation1-"+typeResolution.split(" ")[1]+fichier.right(fichier.size()-fichier.split("-")[0].size());
        heuristic.resolveMachinePerMachine(typeResolution.split(" ")[1], fichierResultat);
    }

    if (typeResolution.split(" ")[0] == "Affectation2"){

        Heuristique heuristic(fichierInstance.toStdString(), this->pourcentagesParAgent);

        //On donne le nouveau chemin pour le fichier de résultat (on enlève 8 caractères au nom de fichier initial qui correspondent à "instance")
        QString fichierResultat = repertoire.path()+"/Affectation2-"+typeResolution.split(" ")[1]+fichier.right(fichier.size()-fichier.split("-")[0].size());
        heuristic.resolveMachineLessUsedMachine(typeResolution.split(" ")[1], fichierResultat);
    }

    cout << "Résolution " << this->typeResolution.toStdString() << " terminée" << endl;

    emit finished();
}
