#ifndef CALCULCOMPARAISON_H
#define CALCULCOMPARAISON_H

#include <QObject>
#include <QWidget>
#include "iostream"
#include "resultat.h"

using namespace std;

/**
 * @brief
 *
 */
class CalculComparaison
{
public:
    /**
     * @brief
     *
     */
    CalculComparaison();

    /**
     * @brief
     *
     */
    map<unsigned int,map<QString,unsigned int>> calculGap(map<unsigned int,vector<Resultat>> tableauComparaison);

    /**
     * @brief
     *
     */
    map<unsigned int,map<QString,unsigned int>> calculPourcentageSolutionOptimale(map<unsigned int,vector<Resultat>> tableauComparaison);

    /**
     * @brief
     *
     */
    map<unsigned int,map<QString,unsigned int>> calculPourcentageTempsResolution(map<unsigned int,vector<Resultat>> tableauComparaison);

    void afficherGraphique(map<unsigned int,vector<Resultat>> tableauComparaison, QString typeComparaison);

private:
    //vector<Resultat> resultats;
};

#endif // CALCULCOMPARAISON_H
