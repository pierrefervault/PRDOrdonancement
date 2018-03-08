#ifndef CALCULCOMPARAISON_H
#define CALCULCOMPARAISON_H

#include <QObject>
#include <QWidget>
#include "iostream"
#include "resultat.h"

using namespace std;

/**
 * @brief La classe permetant d'effectuer des comparaisons
 * entre les différentes méthodes de résolution
 *
 */
class CalculComparaison
{
public:
    /**
     * @brief Le constructeur de la classe CalculComparaison
     *
     */
    CalculComparaison();

    /**
     * @brief Calcul le gap de toutes les méthodes de résolution
     *
     * @param tableauComparaison Le tableau contenant pour chaque nombre de jobs, les fichiers de resultat pour chaque méthode de résolution.
     * @return map<unsigned int, map<QString, unsigned int> > Le tableau contenant pour chaque nombre de jobs, le gap pour chaque méthode de résolution.
     */
    map<unsigned int,map<QString,unsigned int>> calculGap(map<unsigned int,vector<Resultat>> tableauComparaison);

    /**
     * @brief Calcul le pourcentage de solution optimale pour chaque méthode de résolution.
     *
     * @param tableauComparaison Le tableau contenant pour chaque nombre de jobs, les fichiers de resultat pour chaque méthode de résolution.
     * @return map<unsigned int, map<QString, unsigned int> > Le tableau contenant pour chaque nombre de jobs, le pourcentage de solution optimale pour chaque méthode de résolution.
     */
    map<unsigned int,map<QString,unsigned int>> calculPourcentageSolutionOptimale(map<unsigned int,vector<Resultat>> tableauComparaison);

    /**
     * @brief Calcul le pourcentage du temps de résolution exacte pour chaque méthode de résolution.
     *
     * @param tableauComparaison Le tableau contenant pour chaque nombre de jobs, les fichiers de resultat pour chaque méthode de résolution.
     * @return map<unsigned int, map<QString, unsigned int> > Le tableau contenant pour chaque nombre de jobs, le pourcentage du temps de résolution exacte pour chaque méthode de résolution.
     */
    map<unsigned int,map<QString,unsigned int>> calculPourcentageTempsResolution(map<unsigned int,vector<Resultat>> tableauComparaison);

};

#endif // CALCULCOMPARAISON_H
