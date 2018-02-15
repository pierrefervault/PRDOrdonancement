#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>

namespace Ui {
class FenetrePrincipale;
}

/**
 * @brief La Fenêtre Principale
 *
 */
class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la Fenêtre Principale
     *
     * @param parent
     */
    explicit FenetrePrincipale(QWidget *parent = 0);
    /**
     * @brief Destructeur de la Fenêtre Principale
     *
     */
    ~FenetrePrincipale();

private slots:

    /**
     * @brief Action effectuée lors du clic sur le bouton de génération d'instance
     *
     */
    void on_actionG_n_rer_des_instances_triggered();

    /**
     * @brief Action effectuée lors du clic sur le bouton permettant de quitter l'application
     *
     */
    void on_actionQuitter_l_application_triggered();

    /**
     * @brief Action effectuée lors du clic sur le bouton de résolution d'instance
     *
     */
    void on_actionR_soudre_des_instances_triggered();

    void on_actionComparer_des_m_thodes_de_r_solutions_triggered();

private:
    Ui::FenetrePrincipale *ui; /**< Interface de la Fenetre Principale*/
};

#endif // FENETREPRINCIPALE_H
