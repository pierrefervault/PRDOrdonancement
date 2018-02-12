#ifndef RESOLUTIONINSTANCE_H
#define RESOLUTIONINSTANCE_H

#include <QDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QtConcurrent/QtConcurrent>
#include "workerfichier.h"
#include "workerdossier.h"
#include <iostream>

using namespace std;

namespace Ui {
class ResolutionInstance;
}

class ResolutionInstance : public QDialog
{
    Q_OBJECT

public:
    explicit ResolutionInstance(QWidget *parent = 0);
    void executionFichier(QString fichierInstance, QString typeResolution);
    void executionDossier(QString fichierInstance, QString typeResolution);
    QString trouverMethodeResolution(int indexTableau, int indexSousElement = -1);
    ~ResolutionInstance();

private slots:
    void on_choisirFichierPushButton_clicked();

    void on_validerPushButton_clicked();

    void on_annulerPushButton_clicked();

    void on_fichierRadioButton_clicked();

    void on_dossierRadioButton_clicked();

    void on_agentSpinBox_valueChanged(int arg1);

    void on_agentComboBox_currentIndexChanged(int index);

    void on_validerPourcentagePushButton_clicked();

private:
    Ui::ResolutionInstance *ui;
    vector<int> pourcentageParAgent;
};

#endif // RESOLUTIONINSTANCE_H