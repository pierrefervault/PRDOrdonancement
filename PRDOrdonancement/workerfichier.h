#ifndef WORKERFICHIER_H
#define WORKERFICHIER_H

#include <QObject>
#include <QWidget>
#include <iostream>
#include "methodeexacte.h"
#include <iostream>
#include <QFileDialog>
#include <QFileInfo>
#include <heuristique.h>
#include "QMessageBox"

using namespace std;

/**
 * @brief Le Worker permetant de gérer la résolution d'un fichier d'instance
 *
 */
class WorkerFichier : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe WorkerFichier
     *
     * @param fichierInstance Le chemin vers le fichier d'instance
     * @param typeResolution Le type de résolution à effectuer
     */
    WorkerFichier(QString fichierInstance, QString typeResolution, map<unsigned int, unsigned int> pourcentagesParAgent);
    /**
     * @brief Destructeur de la classe WorkerFichier
     *
     */
    ~WorkerFichier();
public slots :
    /**
     * @brief Action effectuée lors du lancement du worker
     *
     */
    void process();
signals:
    /**
     * @brief Action effectuée lorsque le worker a fini l'ensemble de ces tâches
     *
     */
    void finished();
    /**
     * @brief Action effectuée lorsqu'il y a une erreur dans le worker
     *
     * @param err
     */
    void error(QString err);
private:
    QString fichierInstance; /**< Le chemin vers le fichier d'instance */
    QString typeResolution; /**< Le type de résolution à effectuer */
    map<unsigned int, unsigned int> pourcentagesParAgent; /**< Le tableau de pourcentage par agent */
};

#endif // WORKERFICHIER_H
