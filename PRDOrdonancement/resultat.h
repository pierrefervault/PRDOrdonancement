#ifndef RESULTAT_H
#define RESULTAT_H

#include <QObject>
#include "iostream"
#include "fstream"
#include "instance.h"

using namespace std;

/**
 * @brief La classe représentant un fichier de résultat
 *
 */
class Resultat
{
public:
    /**
     * @brief Le constructeur de la classe Resultat
     *
     */
    Resultat();

    /**
     * @brief Permet de charger un résulat à partir d'un fichier de résultat
     *
     * @param fichierResultat Le fichier contenant les données spécifiques à des résultats de résolution
     */
    void chargerResultat(QString fichierResultat);


    /**
     * @brief Permet de sauvegarder le résultat d'une résolution d'instance dans un fichier de résultat
     *
     * @param instance L'instance que l'on a résolu
     * @param jobsOrdonnances Le tableau de jobs ordonancés
     * @param typeResolution Le type de résolution
     * @param fichierResultat Le fichier où seront stockés les résulats
     * @param dureeExecution La durée d'execution de la résolution
     * @return unsigned int Le nombre de jobs ordonnancés
     */
    unsigned int sauvegarderResultat(Instance instance, vector<vector<unsigned int>> jobsOrdonnances, QString typeResolution, QString fichierResultat, double dureeExecution);


    /**
     * @brief Getter permetant d'obtenir le tableau contenant l'ensemble des solutions trouvées
     *
     * @return vector<unsigned int> Le tableau contenant l'ensemble des solutions trouvées
     */
    vector<unsigned int> getSolutions() const;

    /**
     * @brief Setter permetant de spécifier le tableau contenant l'ensemble des solutions trouvées
     *
     * @param value Le tableau contenant l'ensemble des solutions trouvées
     */
    void setSolutions(const vector<unsigned int> &value);

    /**
     * @brief Getter permetant d'obtenir le tableau contenant les temps de calcul pour chaque solution
     *
     * @return vector<double> Le tableau contenant les temps de calcul pour chaque solution
     */
    vector<double> getTempsExecution() const;

    /**
     * @brief Getter permetant d'obtenir le nombre de jobs pour chaque solution
     *
     * @return unsigned int Le nombre de jobs pour chaque solution
     */
    unsigned int getNbrJobs() const;

    /**
     * @brief Setter permetant de spécifier le nombre de jobs pour chaque solution
     *
     * @param value Le nombre de jobs pour chaque solution
     */
    void setNbrJobs(unsigned int value);

    /**
     * @brief Getter permetant d'obtenir le nombre de ressources pour chaque solution
     *
     * @return unsigned int Le nombre de ressources pour chaque solution
     */
    unsigned int getNbrRessources() const;

    /**
     * @brief Setter permetant de spécifier le nombre de ressources pour chaque solution
     *
     * @param value Le nombre de ressources pour chaque solution
     */
    void setNbrRessources(unsigned int value);

    /**
     * @brief Getter permetant d'obtenir le nombre de machines pour chaque solution
     *
     * @return unsigned int Le nombre de machines pour chaque solution
     */
    unsigned int getNbrMachines() const;

    /**
     * @brief Setter permetant de spécifier le nombre de machines pour chaque solution
     *
     * @param value Le nombre de machines pour chaque solution
     */
    void setNbrMachines(unsigned int value);

    /**
     * @brief Getter permetant d'obtenir le fichier de resultat
     *
     * @return unsigned int Le le fichier de resultat
     */
    QString getFichierResultat() const;

    /**
     * @brief Setter permetant de spécifier le fichier de resultat
     *
     * @return unsigned int Le le fichier de resultat
     */
    void setFichierResultat(const QString &value);

private:
    vector<unsigned int> solutions; /**< Le tableau de solutions trouvées */
    vector<double> tempsExecution; /**< Le tableau contenant les temps de calcul pour chaques solutions trouvées */
    unsigned int nbrJobs; /**< Le nombre de jobs pour chaque solution */
    unsigned int nbrRessources; /**< Le nombre de ressources pour chaque solution */
    unsigned int nbrMachines; /**< Le nombre de machines pour chaque solution */
    QString fichierResultat; /**< Le fichier de résultat */
};

#endif // RESULTAT_H
