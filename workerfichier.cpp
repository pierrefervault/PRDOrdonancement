#include "workerfichier.h"

WorkerFichier::WorkerFichier(QString fichierInstance, QString typeResolution)
{
    this->fichierInstance = fichierInstance;
    this->typeResolution = typeResolution;
}

WorkerFichier::~WorkerFichier(){

}

void WorkerFichier::process(){
    //On récupère le chemin du fichier
    QString fichierInstance = this->fichierInstance;

    //On récupère le nom du fichier
    QFileInfo path(fichierInstance);
    QString fichier = path.fileName();

    //On crée le nouveau répertoire
    QString tmpFolder = fichierInstance.right(fichierInstance.size()-9);
    QDir repertoire = QDir("Resultat"+tmpFolder.left(tmpFolder.size()-fichier.size()-1));
    repertoire.mkpath(".");

    if (typeResolution.split(" ")[0] == "mip1"){
        //On donne le nouveau chemin pour le fichier de résultat
        QString fichierResultat = repertoire.path()+"/resolutionMip1-"+fichier.right(fichier.size()-8);

        MethodeExacte methodeExacte;
        methodeExacte.resolutionPlneMip1(fichierInstance.toStdString(), fichierResultat.toStdString());
    }
    if (typeResolution.split(" ")[0] == "mip2"){
        //On donne le nouveau chemin pour le fichier de résultat
        QString fichierResultat = repertoire.path()+"/resolutionMip2-"+fichier.right(fichier.size()-8);

        MethodeExacte methodeExacte;
        methodeExacte.resolutionPlneMip2(fichierInstance.toStdString(), fichierResultat.toStdString());
    }

    if (typeResolution.split(" ")[0] == "Affectation1"){

        Heuristique heuristic(fichierInstance.toStdString());

        //On donne le nouveau chemin pour le fichier de résultat
        QString fichierResultat = repertoire.path()+"/Affectation1-"+typeResolution.split(" ")[1]+"-"+fichier.right(fichier.size()-8);
        heuristic.resolveMachinePerMachine(typeResolution.split(" ")[1], fichierResultat);
    }

    if (typeResolution.split(" ")[0] == "Affectation2"){

        Heuristique heuristic(fichierInstance.toStdString());

        //On donne le nouveau chemin pour le fichier de résultat
        QString fichierResultat = repertoire.path()+"/Affectation2-"+typeResolution.split(" ")[1]+"-"+fichier.right(fichier.size()-8);
        heuristic.resolveMachineLessUsedMachine(typeResolution.split(" ")[1], fichierResultat);
    }


    emit finished();
}

