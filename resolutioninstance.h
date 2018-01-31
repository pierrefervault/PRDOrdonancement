#ifndef RESOLUTIONINSTANCE_H
#define RESOLUTIONINSTANCE_H

#include <QDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QtConcurrent/QtConcurrent>
#include "workerfichier.h"
#include "workerdossier.h"
#include <iostream>

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
    ~ResolutionInstance();

private slots:
    void on_choisirFichierPushButton_clicked();

    void on_validerPushButton_clicked();

    void on_annulerPushButton_clicked();

    void on_fichierRadioButton_clicked();

    void on_dossierRadioButton_clicked();

    void on_typeResolutionComboBox_currentIndexChanged(int index);

    void on_typeResolutionComboBox_currentTextChanged(const QString &arg1);

private:
    Ui::ResolutionInstance *ui;
};

#endif // RESOLUTIONINSTANCE_H
