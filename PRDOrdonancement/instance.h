#ifndef INSTANCE_H
#define INSTANCE_H

#include <QString>
#include <vector>

using namespace std;

/**
 * @brief Classe représentant une instance
 *
 */
class Instance
{
public:
    /**
     * @brief Constructeur de la classe Instance
     *
     */
    Instance();

    /**
     * @brief Permet de retourner le chemin vers le fichier d'instance
     *
     * @return QString Le chemin vers le fichier d'instance
     */
    QString getFichierInstance() const;
    /**
     * @brief Setter du chemin vers le fichier d'instance
     *
     * @param value Le chemin vers le fichier d'instance que l'on souhaite
     */
    void setFichierInstance(const QString &value);

    /**
     * @brief Permet d'obtenir le nombre de jobs de l'instance
     *
     * @return int Le nombre de jobs
     */
    int getNbrJobs() const;
    /**
     * @brief Setter du nombre de jobs de l'instance
     *
     * @param value Le nombre de jobs souhaité de l'instance
     */
    void setNbrJobs(int value);

    /**
     * @brief Permet d'obtenir le nombre de ressources de l'instance
     *
     * @return int Le nombre de ressources
     */
    int getNbrRessources() const;
    /**
     * @brief Setter du nombre de ressources de l'instance
     *
     * @param value Le nombre de ressources souhaité de l'instance
     */
    void setNbrRessources(int value);

    /**
     * @brief Permet d'obtenir le nombre de machines de l'instance
     *
     * @return int Le nombre de machines
     */
    int getNbrMachines() const;
    /**
     * @brief Setter du nombre de machines de l'instance
     *
     * @param value Le nombre de machines souhaité de l'instance
     */
    void setNbrMachines(int value);

    /**
     * @brief Permet d'obtenir le tableau des instants de départ de l'ensemble des jobs
     *
     * @return vector<int> Le tableau des instants de départ de l'ensemble des jobs
     */
    vector<int> getSj() const;
    /**
     * @brief Setter du tableau des instants de départ de l'ensemble des jobs
     *
     * @param value Le tableau des instants de départ de l'ensemble des jobs souhaité
     */
    void setSj(const vector<int> &value);

    /**
     * @brief Permet d'obtenir le tableau des instants de fin de l'ensemble des jobs
     *
     * @return vector<int> Le tableau des instants de fin de l'ensemble des jobs
     */
    vector<int> getFj() const;
    /**
     * @brief Setter du tableau des instants de fin de l'ensemble des jobs
     *
     * @param value Le tableau des instants de fin de l'ensemble des jobs souhaité
     */
    void setFj(const vector<int> &value);

    /**
     * @brief Permet d'obtenir le tableau des capacités en ressource pour l'ensemble des machines
     *
     * @return vector<vector<int>> Le tableau des capacités en ressource pour l'ensemble des machines
     */
    vector<vector<int>> getCapRessources() const;
    /**
     * @brief Setter du tableau des capacités en ressource pour l'ensemble des machines
     *
     * @param value Le tableau des capacités en ressource pour l'ensemble des machines souhaité
     */
    void setCapRessources(const vector<vector<int>> &value);

    /**
     * @brief Permet d'obtenir le tableau des capacités en ressource pour l'ensemble des jobs
     *
     * @return vector<vector<int>> Le tableau des capacités en ressource pour l'ensemble des jobs
     */
    vector<vector<int>> getTableauRessourcesJobs() const;
    /**
     * @brief Setter du tableau des capacités en ressource pour l'ensemble des jobs
     *
     * @param value Le tableau des capacités en ressource pour l'ensemble des jobs souhaité
     */
    void setTableauRessourcesJobs(const vector<vector<int> > &value);

    /**
     * @brief Permet d'obtenir l'horizon maximale de planification de l'instance
     *
     * @return int L'horizon maximale de planification de l'instance
     */
    int getHorizonMax() const;
    /**
     * @brief Setter de l'horizon maximale de planification de l'instance
     *
     * @param value L'horizon maximale de planification de l'instance souhaitée
     */
    void setHorizonMax(int value);

private:

    QString fichierInstance; /**< Le chemin vers le fichier d'instance*/
    int nbrJobs; /**< Le nombre de jobs de l'instance */
    int nbrRessources; /**< Le nombre de ressources de l'instance */
    int nbrMachines; /**< Le nombre de machines de l'instance */

    vector<int> sj; /**< Le tableau des instants de début pour l'ensemble des jobs */
    vector<int> fj; /**< Le tableau des instants de fin pour l'ensemble des jobs */
    int horizonMax; /**< L'horizon maximale de planification de l'instance */

    vector<vector<int>> capRessources; /**< Le tableau des capacités en ressource pour l'ensemble des machines */
    vector<vector<int>> tableauRessourcesJobs; /**< Le tableau des capacités en ressource pour l'ensemble des jobs */

};

#endif // INSTANCE_H
