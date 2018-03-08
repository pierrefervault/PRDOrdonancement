#include "classtest.h"


ClassTest::ClassTest(QObject *parent)
{

}

void ClassTest::testGeneration(){

    Instance instance;

    instance.sauvegarderInstance(1,8,3,3,1440);

}


void ClassTest::testSolutionInferieureOuEgaleNbrJobsAffectation1(){

    string fichierInstance = "Instances/0/8/3/3/instance0-8-3-3.data";

    Heuristique heuristique(fichierInstance);

    QVERIFY2(heuristique.resolveMachinePerMachine("SommeRessources","") <= heuristique.getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");
    QVERIFY2(heuristique.resolveMachinePerMachine("CCmaxSommeRessources","") <= heuristique.getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");
    QVERIFY2(heuristique.resolveMachinePerMachine("CCmaxMaxRessources","") <= heuristique.getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");
    QVERIFY2(heuristique.resolveMachinePerMachine("MoyenneRessourcesSousEnsembles","") <= heuristique.getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");
}

void ClassTest::testSolutionInferieureOuEgaleNbrJobsAffectation2(){

    string fichierInstance = "Instances/0/8/3/3/instance0-8-3-3.data";

    Heuristique heuristique(fichierInstance);

    QVERIFY2(heuristique.resolveMachineLessUsedMachine("SommeRessources","") <= heuristique.getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");
    QVERIFY2(heuristique.resolveMachineLessUsedMachine("CCmaxSommeRessources","") <= heuristique.getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");
    QVERIFY2(heuristique.resolveMachineLessUsedMachine("CCmaxMaxRessources","") <= heuristique.getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");
    QVERIFY2(heuristique.resolveMachineLessUsedMachine("MoyenneRessourcesSousEnsembles","") <= heuristique.getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");

}

void ClassTest::testSolutionInferieureOuEgaleNbrJobsMip1(){

    string fichierInstance = "Instances/0/8/3/3/instance0-8-3-3.data";

    MethodeExacte methodeExacte(fichierInstance);

    QVERIFY2(methodeExacte.resolutionPlneMip1("") <= methodeExacte.getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");
}

void ClassTest::testSolutionInferieureOuEgaleNbrJobsMip2(){

    string fichierInstance = "Instances/0/8/3/3/instance0-8-3-3.data";

    MethodeExacte methodeExacte(fichierInstance);

    QVERIFY2(methodeExacte.resolutionPlneMip2("") <= methodeExacte.getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");

}

void ClassTest::testSolutionMip1EgaleMip2(){

    string fichierInstance = "Instances/0/8/3/3/instance0-8-3-3.data";

    MethodeExacte methodeExacte(fichierInstance);

    QVERIFY2(methodeExacte.resolutionPlneMip1("") == methodeExacte.resolutionPlneMip2(""), "La solution du Mip1 vaut le Mip2");
}

void ClassTest::testSolutionMip1SuperieureOuEgaleHeuristique(){

    string fichierInstance = "Instances/0/8/3/3/instance0-8-3-3.data";

    MethodeExacte methodeExacte(fichierInstance);
    Heuristique heuristique(fichierInstance);

    QDir repertoire = QDir("Resultat/0/8/3/3/");
    repertoire.mkpath(".");

    QVERIFY2(heuristique.resolveMachinePerMachine("SommeRessources","Resultat/0/8/3/3/Affectation1-SommeRessources-8-3-3.data") <=
             methodeExacte.resolutionPlneMip1("Resultat/0/8/3/3/resolutionMip1-8-3-3.data"), "Solution trouve inférieure ou égale au nombre de jobs total");
    QVERIFY2(heuristique.resolveMachinePerMachine("CCmaxSommeRessources","Resultat/0/8/3/3/Affectation1-CCmaxSommeRessources-8-3-3.data") <=
             methodeExacte.resolutionPlneMip2("Resultat/0/8/3/3/resolutionMip2-8-3-3.data"), "Solution trouve inférieure ou égale au nombre de jobs total");
    QVERIFY2(heuristique.resolveMachinePerMachine("CCmaxMaxRessources","Resultat/0/8/3/3/Affectation1-CCmaxMaxRessources-8-3-3.data") <= methodeExacte.resolutionPlneMip1(""), "Solution trouve inférieure ou égale au nombre de jobs total");
    QVERIFY2(heuristique.resolveMachinePerMachine("MoyenneRessourcesSousEnsembles","Resultat/0/8/3/3/Affectation1-MoyenneRessourcesSousEnsembles-8-3-3.data") <= methodeExacte.resolutionPlneMip1(""), "Solution trouve inférieure ou égale au nombre de jobs total");

    QVERIFY2(heuristique.resolveMachineLessUsedMachine("SommeRessources","Resultat/0/8/3/3/Affectation2-SommeRessources-8-3-3.data") <= methodeExacte.resolutionPlneMip1(""), "Solution trouve inférieure ou égale au Mip1");
    QVERIFY2(heuristique.resolveMachineLessUsedMachine("CCmaxSommeRessources","Resultat/0/8/3/3/Affectation2-CCmaxSommeRessources-8-3-3.data") <= methodeExacte.resolutionPlneMip1(""), "Solution trouve inférieure ou égale au Mip1");
    QVERIFY2(heuristique.resolveMachineLessUsedMachine("CCmaxMaxRessources","Resultat/0/8/3/3/Affectation2-CCmaxMaxRessources-8-3-3.data") <= methodeExacte.resolutionPlneMip1(""), "Solution trouve inférieure ou égale au Mip1");
    QVERIFY2(heuristique.resolveMachineLessUsedMachine("MoyenneRessourcesSousEnsembles","Resultat/0/8/3/3/Affectation1-MoyenneRessourcesSousEnsembles-8-3-3.data") <= methodeExacte.resolutionPlneMip1(""), "Solution trouve inférieure ou égale au Mip1");
}

void ClassTest::testHeuristiqueGapPositif(){

    string fichierResultat = "Resultat/0/8/3/3/resultat0-8-3-3.data";

    Resultat resultat;

}

void ClassTest::supprimerInstanceEtResultat(){
    QDir repertoire = QDir("Instances");
    repertoire.removeRecursively();
    repertoire.setPath("Resultat");
    repertoire.removeRecursively();
}
