#include "workerfile.h"
#include "plne.h"
#include "plnemip2.h"
#include <iostream>
#include <QFileDialog>
#include <QFileInfo>
#include <heuristic.h>

WorkerFile::WorkerFile(QString filename, QString typeOfResolution)
{
    this->filename = filename;
    this->typeOfResolution = typeOfResolution;
}

WorkerFile::~WorkerFile(){

}

void WorkerFile::process(){
    //On récupère le chemin du fichier
    QString fichierInstance = this->filename;

    //On récupère le nom du fichier
    QFileInfo path(fichierInstance);
    QString fichier = path.fileName();

    //On crée le nouveau répertoire
    QString tmpFolder = fichierInstance.right(fichierInstance.size()-9);
    QDir repertoire = QDir("Resultat"+tmpFolder.left(tmpFolder.size()-fichier.size()-1));
    repertoire.mkpath(".");

    if (typeOfResolution == "mip1"){
        //On donne le nouveau chemin pour le fichier de résultat
        QString fichierResultat = repertoire.path()+"/resolutionMip1-"+fichier.right(fichier.size()-8);

        resolvePlne(fichierInstance.toStdString(), fichierResultat.toStdString());
    }
    if (typeOfResolution == "mip2"){
        //On donne le nouveau chemin pour le fichier de résultat
        QString fichierResultat = repertoire.path()+"/resolutionMip2-"+fichier.right(fichier.size()-8);

        resolvePlneMip2(fichierInstance.toStdString(), fichierResultat.toStdString());
    }

    if (typeOfResolution == "heuristique"){
        //On donne le nouveau chemin pour le fichier de résultat
        QString fichierResultat = repertoire.path()+"/heuristique-"+fichier.right(fichier.size()-8);

        cout << "Test Heuristique" << endl;
        Heuristic heuristic(fichierInstance.toStdString());
        heuristic.resolveMachinePerMachine(heuristic.trierCCmax());
        //heuristic.resolveMachinePerMachine(heuristic.trierSommeRessources());
        //heuristic.resolveMachinePerMachine(heuristic.trierMoyenneRessourcesSousEnsembles());
    }

    emit finished();
}

