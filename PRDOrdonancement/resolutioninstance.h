#ifndef RESOLUTIONINSTANCE_H
#define RESOLUTIONINSTANCE_H

#include <QDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QtConcurrent/QtConcurrent>
#include "workerfichier.h"
#include "workerdossier.h"
#include <iostream>
#include "QCheckBox"
#include "QBoxLayout"
#include "QMessageBox"

using namespace std;

namespace Ui {
class ResolutionInstance;
}

/**
 * @brief Fenêtre ResolutionInstance
 *
 */
class ResolutionInstance : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe ResolutionInstance
     *
     * @param parent
     */
    explicit ResolutionInstance(QWidget *parent = 0);
    /**
     * @brief Execution de la résolution avec un seul fichier d'instance
     *
     * @param fichierInstance Chemin vers le fichier d'instance
     * @param typeResolution Type de la résolution
     */
    void executionFichier(QString fichierInstance, QString typeResolution);
    /**
     * @brief Execution de la résolution avec un seul fichier d'instance
     *
     * @param dossierInstance Chemin vers le dossier d'instances
     * @param typeResolution Type de la résolution
     */
    void executionDossier(QString dossierInstance, QString typeResolution);
    /**
     * @brief Fonction permetant de trouver la methode de résolution suivant les champs CheckBox remplis
     *
     * @param indexTableau Index du tableau selectionné
     * @param indexSousElement Index du sous-élément du tableau selectionné (-1 si il n'y a pas de sous-élément)
     * @return QString La méthode de résolution
     */
    QString trouverMethodeResolution(unsigned int indexTableau, unsigned int indexSousElement = -1);
    /**
     * @brief Destructeur de la classe ResolutionInstance
     *
     */
    ~ResolutionInstance();

private slots:
    /**
     * @brief Action effectuée lors du clic sur le bouton permettant de choisir un fichier ou un dossier
     *
     */
    void on_choisirFichierPushButton_clicked();

    /**
     * @brief Action effectuée lors du clic sur le bouton permettant de valider
     *
     */
    void on_validerPushButton_clicked();

    /**
     * @brief Action effectuée lors du clic sur le bouton permettant d'annuler
     *
     */
    void on_annulerPushButton_clicked();

    /**
     * @brief Action effectuée lors du clic sur le bouton permettant de spécifié que l'on veut choisir un fichier
     *
     */
    void on_fichierRadioButton_clicked();

    /**
     * @brief Action effectuée lors du clic sur le bouton permettant de spécifié que l'on veut choisir un dossier
     *
     */
    void on_dossierRadioButton_clicked();

    /**
     * @brief Action effectuée lors du changement de l'objet SpinBox spécifique au nombre d'agent
     *
     * @param arg1
     */
    void on_agentSpinBox_valueChanged(int arg1);

    /**
     * @brief Action effectuée lors du changement de l'objet ComboBox spécifique au nombre d'agent
     *
     * @param index
     */
    void on_agentComboBox_currentIndexChanged(int index);

    /**
     * @brief Action effectuée lors du clic sur le bouton permetant de valider le pourcentage de jobs affectés à un agent
     *
     */
    void on_validerPourcentagePushButton_clicked();

    /**
     * @brief Action effectuée lors du clic sur le bouton permetant de cocher l'ensemble des méthodes de résolution en meme temps
     *
     */
    void on_toutCocherCheckBox_clicked(bool checked);

private:
    Ui::ResolutionInstance *ui; /**< La fenêtre de résolution d'instances */
    vector<unsigned int> pourcentageParAgent; /**< Le pourcentage attribué à chaque agent */
};

#endif // RESOLUTIONINSTANCE_H
