#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>

namespace Ui {
class FenetrePrincipale;
}

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenetrePrincipale(QWidget *parent = 0);
    ~FenetrePrincipale();

private slots:



    void on_actionG_n_rer_des_instances_triggered();

    void on_actionQuitter_l_application_triggered();

    void on_actionR_soudre_des_instances_triggered();

private:
    Ui::FenetrePrincipale *ui;
};

#endif // FENETREPRINCIPALE_H
