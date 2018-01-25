#include "workerfolder.h"
#include "plne.h"
#include "plnemip2.h"
#include <iostream>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>

WorkerFolder::WorkerFolder(QString filename, QString typeOfResolution)
{
    this->filename = filename;
    this->typeOfResolution = typeOfResolution;
}

WorkerFolder::~WorkerFolder(){

}

void WorkerFolder::process(){

    QString dossierInstance = this->filename;
    QFileInfo path(dossierInstance);


    // On remplit une QStringList avec chacun des filtres désirés ici "*.mp3" et "*.avi".
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
        if (folderName != repertoire.path()){
            repertoire.removeRecursively();
            folderName = repertoire.path();
            repertoire.mkpath(".");
        }

        if (typeOfResolution == "mip1"){
            //On donne le nouveau chemin pour le fichier de résultat
            QString fichierResultat = repertoire.path()+"/resolutionMip1"+fichier.right(fichier.size()-fichier.split("-")[0].size());
            resolvePlne(fichierInstance.toStdString(), fichierResultat.toStdString());
        }

        if (typeOfResolution == "mip2"){
            //On donne le nouveau chemin pour le fichier de résultat
            QString fichierResultat = repertoire.path()+"/resolutionMip2"+fichier.right(fichier.size()-fichier.split("-")[0].size());
            resolvePlneMip2(fichierInstance.toStdString(), fichierResultat.toStdString());
        }
    }

    emit finished();
}

