#include "classtest.h"


/**
 * @brief Contructeur de la classe de test
 *
 * @param parent
 */
ClassTest::ClassTest(QObject *parent)
{

}

/**
 * @brief Test la génération de fichier d'instance et
 * vérifie que chacune des valeurs spécifiées est correcte
 *
 */
void ClassTest::testGeneration(){

    Instance instance;

    unsigned int nbrInstances = 10;

    instance.sauvegarderInstance(nbrInstances,8,3,3,1440);

    QString dossierInstance = "Instances/0/8/3/3/";

    // On remplit une QStringList avec chacun des filtres désirés ici "*.data".
    QStringList listFilter;
    listFilter << "*.data";

    // On déclare un QDirIterator dans lequel on indique que l'on souhaite parcourir un répertoire et ses sous-répertoires.
    // De plus, on spécifie le filtre qui nous permettra de récupérer uniquement les fichiers du type souhaité.
    QDirIterator dirIterator(dossierInstance, listFilter ,QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

    // Variable qui contiendra tous les fichiers correspondant à notre recherche
    QStringList fileList;
    // Tant qu'on n'est pas arrivé à la fin de l'arborescence...
    while(dirIterator.hasNext())
    {
        // ...on va au prochain fichier correspondant à notre filtre et le stocke dans la liste
        fileList << dirIterator.next();
    }

    QVERIFY2(fileList.size() == nbrInstances, "Nombre d'instances générées incorrect");

}


/**
 * @brief Test vérifiant que les affectations machines par machines
 * donnent des solutions dont les valeurs sont inférieures au nombre de jobs de l'instance
 *
 */
void ClassTest::testSolutionInferieureOuEgaleNbrJobsAffectation1(){

    string fichierInstance = "Instances/0/8/3/3/instance0-8-3-3.data";

    map<unsigned int, unsigned int> pourcentageParAgent;

    Heuristique heuristique(fichierInstance, pourcentageParAgent);

    QVERIFY2(heuristique.resolveMachinePerMachine("SommeRessources","") <= heuristique.getInstance().getNbrJobs(), "Solution trouvée supérieure au nombre de jobs total");
    QVERIFY2(heuristique.resolveMachinePerMachine("CCmaxSommeRessources","") <= heuristique.getInstance().getNbrJobs(), "Solution trouvée supérieure au nombre de jobs total");
    QVERIFY2(heuristique.resolveMachinePerMachine("CCmaxMaxRessources","") <= heuristique.getInstance().getNbrJobs(), "Solution trouvée supérieure au nombre de jobs total");
    QVERIFY2(heuristique.resolveMachinePerMachine("MoyenneRessourcesSousEnsembles","") <= heuristique.getInstance().getNbrJobs(), "Solution trouvée supérieure au nombre de jobs total");
}

/**
 * @brief Test vérifiant que les affectations priorisant la machine la moins chargée
 * donnent des solutions dont les valeurs sont inférieures au nombre de jobs de l'instance
 */
void ClassTest::testSolutionInferieureOuEgaleNbrJobsAffectation2(){

    string fichierInstance = "Instances/0/8/3/3/instance0-8-3-3.data";

    map<unsigned int, unsigned int> pourcentageParAgent;

    Heuristique heuristique(fichierInstance, pourcentageParAgent);

    QVERIFY2(heuristique.resolveMachineLessUsedMachine("SommeRessources","") <= heuristique.getInstance().getNbrJobs(), "Solution trouvée supérieure au nombre de jobs total");
    QVERIFY2(heuristique.resolveMachineLessUsedMachine("CCmaxSommeRessources","") <= heuristique.getInstance().getNbrJobs(), "Solution trouvée supérieure au nombre de jobs total");
    QVERIFY2(heuristique.resolveMachineLessUsedMachine("CCmaxMaxRessources","") <= heuristique.getInstance().getNbrJobs(), "Solution trouvée supérieure au nombre de jobs total");
    QVERIFY2(heuristique.resolveMachineLessUsedMachine("MoyenneRessourcesSousEnsembles","") <= heuristique.getInstance().getNbrJobs(), "Solution trouvée supérieure au nombre de jobs total");

}

/**
 * @brief Test vérifiant que la résolution exacte indexée temps
 * donne des solutions dont les valeurs sont inférieures au nombre de jobs de l'instance
 *
 */
void ClassTest::testSolutionInferieureOuEgaleNbrJobsMip1(){

    string fichierInstance = "Instances/0/8/3/3/instance0-8-3-3.data";

    map<unsigned int, unsigned int> pourcentageParAgent;

    MethodeExacte methodeExacte(fichierInstance, pourcentageParAgent);

    QVERIFY2(methodeExacte.resolutionPlneMip1("") <= methodeExacte.getInstance().getNbrJobs(), "Solution trouvée supérieure au nombre de jobs total");
}

/**
 * @brief Test vérifiant que la résolution exacte indexée jobs
 * donne des solutions dont les valeurs sont inférieures au nombre de jobs de l'instance
 *
 */
void ClassTest::testSolutionInferieureOuEgaleNbrJobsMip2(){

    string fichierInstance = "Instances/0/8/3/3/instance0-8-3-3.data";

    map<unsigned int, unsigned int> pourcentageParAgent;

    MethodeExacte methodeExacte(fichierInstance, pourcentageParAgent);

    QVERIFY2(methodeExacte.resolutionPlneMip2("") <= methodeExacte.getInstance().getNbrJobs(), "Solution trouvée supérieure au nombre de jobs total");

}

/**
 * @brief Test vérifiant que la résolution exacte indexée temps
 * donne des solutions égales à celles trouvées par la résolution exacte indexée jobs
 *
 */
void ClassTest::testSolutionMip1EgaleMip2(){

    string fichierInstance = "Instances/0/8/3/3/instance0-8-3-3.data";

    map<unsigned int, unsigned int> pourcentageParAgent;

    MethodeExacte methodeExacte(fichierInstance,pourcentageParAgent);

    QVERIFY2(methodeExacte.resolutionPlneMip1("") == methodeExacte.resolutionPlneMip2(""), "La solution du Mip1 est différente du Mip2");
}

/**
 * @brief Test vérifiant que la résolution exacte indexée temps
 * donne des solutions égales ou meilleures que celles trouvées par les heuristiques
 *
 */
void ClassTest::testSolutionMip1SuperieureOuEgaleHeuristique(){

    string fichierInstance = "Instances/0/8/3/3/instance0-8-3-3.data";

    map<unsigned int, unsigned int> pourcentageParAgent;

    MethodeExacte methodeExacte(fichierInstance, pourcentageParAgent);
    Heuristique heuristique(fichierInstance, pourcentageParAgent);

    QDir repertoire = QDir("Resultat/0/8/3/3/");
    repertoire.mkpath(".");

    QVERIFY2(heuristique.resolveMachinePerMachine("SommeRessources","Resultat/0/8/3/3/Affectation1-SommeRessources-8-3-3.data") <=
             methodeExacte.resolutionPlneMip1("Resultat/0/8/3/3/resolutionMip1-8-3-3.data"), "Solution trouvée supérieure au Mip1");
    QVERIFY2(heuristique.resolveMachinePerMachine("CCmaxSommeRessources","Resultat/0/8/3/3/Affectation1-CCmaxSommeRessources-8-3-3.data") <=
             methodeExacte.resolutionPlneMip2("Resultat/0/8/3/3/resolutionMip2-8-3-3.data"), "Solution trouvée supérieure au Mip1");
    QVERIFY2(heuristique.resolveMachinePerMachine("CCmaxMaxRessources","Resultat/0/8/3/3/Affectation1-CCmaxMaxRessources-8-3-3.data") <= methodeExacte.resolutionPlneMip1(""), "Solution trouvée supérieure au Mip1");
    QVERIFY2(heuristique.resolveMachinePerMachine("MoyenneRessourcesSousEnsembles","Resultat/0/8/3/3/Affectation1-MoyenneRessourcesSousEnsembles-8-3-3.data") <= methodeExacte.resolutionPlneMip1(""), "Solution trouvée supérieure au Mip1");

    QVERIFY2(heuristique.resolveMachineLessUsedMachine("SommeRessources","Resultat/0/8/3/3/Affectation2-SommeRessources-8-3-3.data") <= methodeExacte.resolutionPlneMip1(""), "Solution trouvée supérieure au Mip1");
    QVERIFY2(heuristique.resolveMachineLessUsedMachine("CCmaxSommeRessources","Resultat/0/8/3/3/Affectation2-CCmaxSommeRessources-8-3-3.data") <= methodeExacte.resolutionPlneMip1(""), "Solution trouvée supérieure au Mip1");
    QVERIFY2(heuristique.resolveMachineLessUsedMachine("CCmaxMaxRessources","Resultat/0/8/3/3/Affectation2-CCmaxMaxRessources-8-3-3.data") <= methodeExacte.resolutionPlneMip1(""), "Solution trouvée supérieure au Mip1");
    QVERIFY2(heuristique.resolveMachineLessUsedMachine("MoyenneRessourcesSousEnsembles","Resultat/0/8/3/3/Affectation1-MoyenneRessourcesSousEnsembles-8-3-3.data") <= methodeExacte.resolutionPlneMip1(""), "Solution trouvée supérieure au Mip1");

}

/**
 * @brief Test vérifiant la cohérence de la comparaison des différentes méthodes de résolution d'instances
 *
 */
void ClassTest::testCoherenceComparaison(){

    QString dossierResultat = "Resultat/0/";

    QStringList filter;
    filter << "*.data";

    QDirIterator it(dossierResultat, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList files;
    while (it.hasNext())
        files << it.next();
    files.sort();

    std::list<QString> list = files.toStdList();

    map<unsigned int,vector<Resultat>> tableauComparaison;

    for(std::list<QString>::iterator it = list.begin() ; it != list.end() ; ++it){

        QString fichier = *it;

        Resultat resultat;

        resultat.chargerResultat(fichier);

        tableauComparaison[fichier.split("/")[fichier.split("/").size()-4].toInt()].push_back(resultat);

    }

    CalculComparaison calculComparaison;

    map<unsigned int,map<QString,unsigned int>> tableauGap = calculComparaison.calculGap(tableauComparaison);

    for (std::map<unsigned int,map<QString,unsigned int>>::iterator it=tableauGap.begin(); it!=tableauGap.end(); ++it)
    {
        for (std::map<QString,unsigned int>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            QVERIFY2(it2->second >= 0, "Gap inférieur à 0");
        }
    }

    map<unsigned int,map<QString,unsigned int>> tableauPourcentageSolutionOptimale = calculComparaison.calculPourcentageSolutionOptimale(tableauComparaison);

    for (std::map<unsigned int,map<QString,unsigned int>>::iterator it=tableauPourcentageSolutionOptimale.begin(); it!=tableauPourcentageSolutionOptimale.end(); ++it)
    {
        for (std::map<QString,unsigned int>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            QVERIFY2(it2->second <= 100, "Pourcentage Solution Optimale supérieur à 100");
            QVERIFY2(it2->second >= 0, "Pourcentage Solution Optimale inférieur à 0");
        }
    }

    map<unsigned int,map<QString,unsigned int>> tableauPourcentageTempsResolution = calculComparaison.calculPourcentageTempsResolution(tableauComparaison);

    for (std::map<unsigned int,map<QString,unsigned int>>::iterator it=tableauPourcentageTempsResolution.begin(); it!=tableauPourcentageTempsResolution.end(); ++it)
    {
        for (std::map<QString,unsigned int>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2){
            QVERIFY2(it2->second >= 0, "Pourcentage Temps Resolution Optimale inférieur à 0");
        }
    }
}

/**
 * @brief Supprime les dossiers d'instances et de résultats générés pour les tests
 *
 */
void ClassTest::supprimerInstanceEtResultat(){
    QDir repertoire = QDir("Instances");
    repertoire.removeRecursively();
    repertoire.setPath("Resultat");
    repertoire.removeRecursively();
}
