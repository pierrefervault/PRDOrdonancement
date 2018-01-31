#ifndef WORKERDOSSIER_H
#define WORKERDOSSIER_H

#include <QObject>
#include <QWidget>
#include "methodeexacte.h"
#include <iostream>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>
#include <heuristique.h>

class WorkerDossier : public QObject {
    Q_OBJECT

public:
    WorkerDossier(QString dossierInstance, QString typeResolution);
    ~WorkerDossier();
public slots :
    void process();
signals:
    void finished();
    void error(QString err);
private:
    QString dossierInstance;
    QString typeResolution;
};

#endif // WORKERDOSSIER_H
