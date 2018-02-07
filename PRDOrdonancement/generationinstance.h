#ifndef GENERATIONINSTANCE_H
#define GENERATIONINSTANCE_H

#include <QDialog>
#include "workerinstance.h"
#include <QtConcurrent/QtConcurrent>
#include <iostream>

namespace Ui {
class GenerationInstance;
}

class GenerationInstance : public QDialog
{
    Q_OBJECT

public:
    explicit GenerationInstance(QWidget *parent = 0);
    ~GenerationInstance();
    void executionGenerationInstance(int nbrInstance, int nbrJobs, int nbrRessources, int nbrMachines, int horizonPlanification);

private slots:
    void on_okPushButton_clicked();

    void on_annulerPushButton_clicked();

private:
    Ui::GenerationInstance *ui;
};

#endif //GENERATIONINSTANCE_H
