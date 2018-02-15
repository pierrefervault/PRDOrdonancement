#ifndef COMPARAISONSOLUTION_H
#define COMPARAISONSOLUTION_H

#include <QDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QtConcurrent/QtConcurrent>
#include "workercomparaison.h"

namespace Ui {
class ComparaisonSolution;
}

class ComparaisonSolution : public QDialog
{
    Q_OBJECT

public:
    explicit ComparaisonSolution(QWidget *parent = 0);
    ~ComparaisonSolution();

private slots:
    void on_choisirDossierPushButton_clicked();

    void on_validerPushButton_clicked();

    void on_annulerPushButton_clicked();

private:
    Ui::ComparaisonSolution *ui;
};

#endif // COMPARAISONSOLUTION_H
