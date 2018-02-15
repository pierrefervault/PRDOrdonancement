#ifndef WORKERCOMPARAISON_H
#define WORKERCOMPARAISON_H

#include <QObject>
#include <QWidget>
#include <iostream>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>

using namespace std;

/**
 * @brief Le Worker permetant de gérer la comparaison d'un dossier de résultats
 *
 */
class WorkerComparaison : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe WorkerComparaison
     *
     * @param dossierResultat Le chemin vers le dossier contenant les résultats des méthodes de résolution
     * @param typeComparaison Le type de comparaison à effectuer
     */
    WorkerComparaison(QString dossierResultat, QString typeComparaison);
    /**
     * @brief Destructeur de la classe WorkerComparaison
     *
     */
    ~WorkerComparaison();
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
    QString dossierResultat; /**< Le chemin vers le dossier contenant les résultats des méthodes de résolution */
    QString typeComparaison; /**< Le type de comparaison à effectuer */
};

#endif // WORKERCOMPARAISON_H
