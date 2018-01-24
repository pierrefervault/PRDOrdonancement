#ifndef RESOLVEINSTANCE_H
#define RESOLVEINSTANCE_H

#include <QDialog>

namespace Ui {
class ResolveInstance;
}

class ResolveInstance : public QDialog
{
    Q_OBJECT

public:
    explicit ResolveInstance(QWidget *parent = 0);
    void processFile(QString filename, QString typeOfResolution);
    void processFolder(QString filename, QString typeOfResolution);
    ~ResolveInstance();

private slots:
    void on_choisirFichierPushButton_clicked();

    void on_validerPushButton_clicked();

    void on_annulerPushButton_clicked();

    void on_fichierRadioButton_clicked();

    void on_dossierRadioButton_clicked();

private:
    Ui::ResolveInstance *ui;
};

#endif // RESOLVEINSTANCE_H
