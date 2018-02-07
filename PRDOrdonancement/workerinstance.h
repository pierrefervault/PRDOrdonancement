#ifndef WORKERINSTANCE_H
#define WORKERINSTANCE_H

#include <QObject>
#include <QWidget>
#include <QDir>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <random>

using namespace std;

class WorkerInstance : public QObject {
    Q_OBJECT

public:
    WorkerInstance(int nbrInstance, int nbrJobs, int nbrRessources, int nbrMachines, int horizonPlanification);
     ~WorkerInstance();

public slots :
    void process();
signals:
    void finished();
    void error(QString err);
private:
    int nbrInstance;
    int nbrJobs;
    int nbrRessources;
    int nbrMachines;
    int horizonPlanification;
};

#endif // WORKERINSTANCE_H
