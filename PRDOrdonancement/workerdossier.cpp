#include "workerdossier.h"

/**
 * @brief Constructeur de la classe WorkerDossier
 *
 * @param dossierInstance Le chemin vers le dossier d'instance
 * @param typeResolution Le type de résolution à effectuer
 */
WorkerDossier::WorkerDossier(QString dossierInstance, QString typeResolution, map<unsigned int, unsigned int> pourcentagesParAgent)
{
    this->dossierInstance = dossierInstance;
    this->typeResolution = typeResolution;
    this->pourcentagesParAgent = pourcentagesParAgent;
}

/**
 * @brief Destructeur de la classe WorkerDossier
 *
 */
WorkerDossier::~WorkerDossier(){

}

/**
 * @brief Action effectuée lors du lancement du worker
 *
 */
void WorkerDossier::process(){

    QString dossierInstance = this->dossierInstance;
    QFileInfo path(dossierInstance);


    // On remplit une QStringList avec chacun des filtres désirés ici "*.data".
    QStringList listFilter;
    listFilter << "*.data";

    // On déclare un QDirIterator dans lequel on indique que l'on souhaite parcourir un répertoire et ses sous-répertoires.
    // De plus, on spécifie le filtre qui nous permettra de récupérer uniquement les fichiers du type souhaité.
    QDirIterator dirIterator(dossierInstance, listFilter ,QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

    // Variable qui contiendra tous les fichiers correspondant à notre recherche
    QStringList fileList;
    // Tant qu'on n'est pas arrivé à la fin de l'arborescence...
    while(dirIterator.hasNext())
    {
        // ...on va au prochain fichier correspondant à notre filtre et le stocke dans la liste
        fileList << dirIterator.next();
    }
    fileList.sort();

    std::list<QString> list = fileList.toStdList();

    QString folderName = "";

    //Pour chaque élément de la liste
    for(std::list<QString>::iterator it = list.begin() ; it != list.end() ; ++it){

        //On récupère le chemin du fichier d'instance
        QString fichierInstance = *it;

        //On récupère le nom du fichier
        QFileInfo path(fichierInstance);
        QString fichier = path.fileName();

        //On crée le nouveau répertoire
        QString tmpFolder = fichierInstance.right(fichierInstance.size()-9);
        QDir repertoire = QDir("Resultat"+tmpFolder.left(tmpFolder.size()-fichier.size()-1));

        if (typeResolution.split(" ")[0] == "mip1"){

            if (folderName != repertoire.path()){
                repertoire.remove("resolutionMip1"+fichier.right(fichier.size()-fichier.split("-")[0].size()));
                folderName = repertoire.path();
                repertoire.mkpath(".");
            }

            //On donne le nouveau chemin pour le fichier de résultat
            QString fichierResultat = repertoire.path()+"/resolutionMip1"+fichier.right(fichier.size()-fichier.split("-")[0].size());

            MethodeExacte methodeExacte(fichierInstance.toStdString(), this->pourcentagesParAgent);
            methodeExacte.resolutionPlneMip1(fichierResultat.toStdString());
        }

        if (typeResolution.split(" ")[0] == "mip1MultiAgent"){

            if (folderName != repertoire.path()){
                repertoire.remove("resolutionMip1MultiAgent"+fichier.right(fichier.size()-fichier.split("-")[0].size()));
                folderName = repertoire.path();
                repertoire.mkpath(".");
            }

            //On donne le nouveau chemin pour le fichier de résultat
            QString fichierResultat = repertoire.path()+"/resolutionMip1MultiAgent"+fichier.right(fichier.size()-fichier.split("-")[0].size());

            MethodeExacte methodeExacte(fichierInstance.toStdString(), this->pourcentagesParAgent);
            methodeExacte.resolutionPlneMip1MultiAgent(fichierResultat.toStdString());
        }

        if (typeResolution.split(" ")[0] == "mip2"){

            if (folderName != repertoire.path()){
                repertoire.remove("resolutionMip2"+fichier.right(fichier.size()-fichier.split("-")[0].size()));
                folderName = repertoire.path();
                repertoire.mkpath(".");
            }

            //On donne le nouveau chemin pour le fichier de résultat
            QString fichierResultat = repertoire.path()+"/resolutionMip2"+fichier.right(fichier.size()-fichier.split("-")[0].size());

            MethodeExacte methodeExacte(fichierInstance.toStdString(), this->pourcentagesParAgent);
            methodeExacte.resolutionPlneMip2(fichierResultat.toStdString());
        }

        if (typeResolution.split(" ")[0] == "mip2MultiAgent"){

            if (folderName != repertoire.path()){
                repertoire.remove("resolutionMip2MultiAgent"+fichier.right(fichier.size()-fichier.split("-")[0].size()));
                folderName = repertoire.path();
                repertoire.mkpath(".");
            }

            //On donne le nouveau chemin pour le fichier de résultat
            QString fichierResultat = repertoire.path()+"/resolutionMip2Multi"+fichier.right(fichier.size()-fichier.split("-")[0].size());

            MethodeExacte methodeExacte(fichierInstance.toStdString(), this->pourcentagesParAgent);
            methodeExacte.resolutionPlneMip2MultiAgent(fichierResultat.toStdString());
        }

        if (typeResolution.split(" ")[0] == "Affectation1"){

            if (folderName != repertoire.path()){
                repertoire.remove("Affectation1-"+typeResolution.split(" ")[1]+fichier.right(fichier.size()-fichier.split("-")[0].size()));
                folderName = repertoire.path();
                repertoire.mkpath(".");
            }

            Heuristique heuristic(fichierInstance.toStdString(), this->pourcentagesParAgent);

            //On donne le nouveau chemin pour le fichier de résultat
            QString fichierResultat = repertoire.path()+"/Affectation1-"+typeResolution.split(" ")[1]+fichier.right(fichier.size()-fichier.split("-")[0].size());
            heuristic.resolveMachinePerMachine(typeResolution.split(" ")[1], fichierResultat);
        }

        if (typeResolution.split(" ")[0] == "Affectation2"){

            if (folderName != repertoire.path()){
                repertoire.remove("Affectation2-"+typeResolution.split(" ")[1]+fichier.right(fichier.size()-fichier.split("-")[0].size()));
                folderName = repertoire.path();
                repertoire.mkpath(".");
            }

            Heuristique heuristic(fichierInstance.toStdString(), this->pourcentagesParAgent);

            //On donne le nouveau chemin pour le fichier de résultat
            QString fichierResultat = repertoire.path()+"/Affectation2-"+typeResolution.split(" ")[1]+fichier.right(fichier.size()-fichier.split("-")[0].size());
            heuristic.resolveMachineLessUsedMachine(typeResolution.split(" ")[1], fichierResultat);
        }
    }

    cout << "Résolution " << this->typeResolution.toStdString() << " terminée" << endl;

    emit finished();
}

