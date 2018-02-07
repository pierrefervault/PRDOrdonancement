#ifndef WORKERFICHIER_H
#define WORKERFICHIER_H

#include <QObject>
#include <QWidget>
#include "methodeexacte.h"
#include <iostream>
#include <QFileDialog>
#include <QFileInfo>
#include <heuristique.h>

class WorkerFichier : public QObject {
    Q_OBJECT

public:
    WorkerFichier(QString fichierInstance, QString typeResolution);
    ~WorkerFichier();
public slots :
    void process();
signals:
    void finished();
    void error(QString err);
private:
    QString fichierInstance;
    QString typeResolution;
};

#endif // WORKERFICHIER_H
