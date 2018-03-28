#ifndef WORKERDOSSIER_H
#define WORKERDOSSIER_H

#include <QObject>
#include <QWidget>
#include <iostream>
#include "methodeexacte.h"
#include <iostream>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>
#include <heuristique.h>

using namespace std;

/**
 * @brief Le Worker permetant de gérer la résolution d'un dossier d'instances
 *
 */
class WorkerDossier : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe WorkerDossier
     *
     * @param dossierInstance Le chemin vers le dossier d'instance
     * @param typeResolution Le type de résolution à effectuer
     */
    WorkerDossier(QString dossierInstance, QString typeResolution, map<unsigned int, unsigned int> pourcentagesParAgent);
    /**
     * @brief Destructeur de la classe WorkerDossier
     *
     */
    ~WorkerDossier();
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
    QString dossierInstance; /**< Le chemin vers le dossier d'instances */
    QString typeResolution; /**< Le type de résolution à effectuer */
    map<unsigned int, unsigned int> pourcentagesParAgent /**< Le tableau de pourcentage par agent*/;
};

#endif // WORKERDOSSIER_H
