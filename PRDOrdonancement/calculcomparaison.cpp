#include "calculcomparaison.h"

/**
 * @brief Le constructeur de la classe CalculComparaison
 *
 */
CalculComparaison::CalculComparaison()
{

}

/**
 * @brief Calcul le gap de toutes les méthodes de résolution
 *
 * @param tableauComparaison Le tableau contenant pour chaque nombre de jobs, les fichiers de resultat pour chaque méthode de résolution.
 * @return map<unsigned int, map<QString, unsigned int> > Le tableau contenant pour chaque nombre de jobs, le gap pour chaque méthode de résolution.
 */
map<unsigned int,map<QString,unsigned int>> CalculComparaison::calculGap(map<unsigned int,vector<Resultat>> tableauComparaison){

    map<unsigned int,map<QString,unsigned int>> tableauGap;

    for (map<unsigned int,vector<Resultat>>::iterator it=tableauComparaison.begin(); it!=tableauComparaison.end(); ++it)
    {
        //cout << "Element" << endl;

        vector<unsigned int> solutionOptimal;
        for (std::vector<Resultat>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            if(it2->getFichierResultat().contains("resolutionMip1")){
                solutionOptimal = it2->getSolutions();
            }
        }

        if (solutionOptimal.empty()){
            cout << "Il n'y a pas de solution optimale de trouvée" << endl;
        }
        else{
            //cout << solutionOptimal.size() << endl;
            for (std::vector<Resultat>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
                double gapSolution = 0;
                for(unsigned int i = 0 ; i < it2->getSolutions().size() ; i++){
                    gapSolution += (double)it2->getSolutions()[i] / (double)solutionOptimal[i];
                }
                gapSolution /= it2->getSolutions().size();
                tableauGap[it->first][it2->getFichierResultat()] = (double)(100 - (100 * gapSolution));
            }
        }
    }

    return tableauGap;

}

/**
 * @brief Calcul le pourcentage de solution optimale pour chaque méthode de résolution.
 *
 * @param tableauComparaison Le tableau contenant pour chaque nombre de jobs, les fichiers de resultat pour chaque méthode de résolution.
 * @return map<unsigned int, map<QString, unsigned int> > Le tableau contenant pour chaque nombre de jobs, le pourcentage de solution optimale pour chaque méthode de résolution.
 */
map<unsigned int,map<QString,unsigned int>> CalculComparaison::calculPourcentageSolutionOptimale(map<unsigned int, vector<Resultat> > tableauComparaison){

    map<unsigned int,map<QString,unsigned int>> tableauPourcentageSolutionOptimale;

    for (map<unsigned int,vector<Resultat>>::iterator it=tableauComparaison.begin(); it!=tableauComparaison.end(); ++it)
    {
        //cout << "Element" << endl;

        vector<unsigned int> solutionOptimal;
        for (std::vector<Resultat>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            if(it2->getFichierResultat().contains("resolutionMip1")){
                solutionOptimal = it2->getSolutions();
            }
        }
        //cout << solutionOptimal.size() << endl;

        if (solutionOptimal.empty()){
            cout << "Il n'y a pas de solution optimale de trouvée" << endl;
        }
        else{
            for (std::vector<Resultat>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
                double pourcentageSolutionOptimale = 0;
                for(unsigned int i = 0 ; i < it2->getSolutions().size() ; i++){
                    if (it2->getSolutions()[i] == solutionOptimal[i])
                    pourcentageSolutionOptimale++;
                }
                pourcentageSolutionOptimale /= it2->getSolutions().size();
                tableauPourcentageSolutionOptimale[it->first][it2->getFichierResultat()] = (double)(100 * pourcentageSolutionOptimale);
                //it2->second = (double)(100 * gapSolution);
            }
        }
    }

    /*for (std::map<unsigned int,map<QString,unsigned int>>::iterator it=tableauPourcentageSolutionOptimale.begin(); it!=tableauPourcentageSolutionOptimale.end(); ++it)
    {
        for (std::map<QString,unsigned int>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            cout << it->first << " => " << it2->first.toStdString() << " => " << it2->second << '\n';
        }
    }*/

    return tableauPourcentageSolutionOptimale;
}

/**
 * @brief Calcul le pourcentage du temps de résolution exacte pour chaque méthode de résolution.
 *
 * @param tableauComparaison Le tableau contenant pour chaque nombre de jobs, les fichiers de resultat pour chaque méthode de résolution.
 * @return map<unsigned int, map<QString, unsigned int> > Le tableau contenant pour chaque nombre de jobs, le pourcentage du temps de résolution exacte pour chaque méthode de résolution.
 */
map<unsigned int,map<QString,unsigned int>> CalculComparaison::calculPourcentageTempsResolution(map<unsigned int, vector<Resultat> > tableauComparaison){

    map<unsigned int,map<QString,unsigned int>> tableauPourcentageTempsResolution;

    for (map<unsigned int,vector<Resultat>>::iterator it=tableauComparaison.begin(); it!=tableauComparaison.end(); ++it)
    {
        //cout << "Element" << endl;

        vector<double> tempsResolutionOptimal;
        for (std::vector<Resultat>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            if(it2->getFichierResultat().contains("resolutionMip1")){
                tempsResolutionOptimal = it2->getTempsExecution();
            }
        }
        //cout << solutionOptimal.size() << endl;

        if (tempsResolutionOptimal.empty()){
            cout << "Il n'y a pas de temps pour la résolution optimale de trouvée" << endl;
        }
        else{
            for (std::vector<Resultat>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
                double pourcentageTempsResolution = 0;
                for(unsigned int i = 0 ; i < it2->getSolutions().size() ; i++){
                    pourcentageTempsResolution += (double)it2->getTempsExecution()[i] / (double)tempsResolutionOptimal[i];
                }
                pourcentageTempsResolution /= it2->getTempsExecution().size();
                tableauPourcentageTempsResolution[it->first][it2->getFichierResultat()] = (double)(100 * pourcentageTempsResolution);
                //it2->second = (double)(100 * gapSolution);
            }
        }
    }

    /*for (std::map<unsigned int,map<QString,unsigned int>>::iterator it=tableauPourcentageTempsResolution.begin(); it!=tableauPourcentageTempsResolution.end(); ++it)
    {
        for (std::map<QString,unsigned int>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            cout << it->first << " => " << it2->first.toStdString() << " => " << it2->second << '\n';
        }
    }*/

    return tableauPourcentageTempsResolution;

}
