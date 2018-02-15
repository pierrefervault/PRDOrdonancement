#include "classtest.h"


ClassTest::ClassTest(QObject *parent)
{

}

void ClassTest::testSolutionInferieureOuEgaleNbrJobsAffectation1(){

    string fichierInstance = "instance-8-3-3.data";

    Heuristique* heuristique = new Heuristique(fichierInstance);

    QVERIFY2(heuristique->resolveMachinePerMachine("SommeRessources","") <= heuristique->getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");
    QVERIFY2(heuristique->resolveMachinePerMachine("CCmaxSommeRessources","") <= heuristique->getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");
    QVERIFY2(heuristique->resolveMachinePerMachine("CCmaxMaxRessources","") <= heuristique->getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");
    QVERIFY2(heuristique->resolveMachinePerMachine("MoyenneRessourcesSousEnsembles","") <= heuristique->getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");
}

void ClassTest::testSolutionInferieureOuEgaleNbrJobsAffectation2(){

    string fichierInstance = "instance-8-3-3.data";

    Heuristique* heuristique = new Heuristique(fichierInstance);

    QVERIFY2(heuristique->resolveMachineLessUsedMachine("SommeRessources","") <= heuristique->getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");
    QVERIFY2(heuristique->resolveMachineLessUsedMachine("CCmaxSommeRessources","") <= heuristique->getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");
    QVERIFY2(heuristique->resolveMachineLessUsedMachine("CCmaxMaxRessources","") <= heuristique->getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");
    QVERIFY2(heuristique->resolveMachineLessUsedMachine("MoyenneRessourcesSousEnsembles","") <= heuristique->getInstance().getNbrJobs(), "Solution trouve inférieure ou égale au nombre de jobs total");

}

void ClassTest::testSolutionInferieureOuEgaleNbrJobsMip1(){

    string fichierInstance = "instance-8-3-3.data";

    MethodeExacte* methodeExacte = new MethodeExacte(fichierInstance);

    QVERIFY2(methodeExacte->resolutionPlneMip1("") <= 8, "Solution trouve inférieure ou égale au nombre de jobs total");
}

void ClassTest::testSolutionInferieureOuEgaleNbrJobsMip2(){

    string fichierInstance = "instance-8-3-3.data";

    MethodeExacte* methodeExacte = new MethodeExacte(fichierInstance);

    QVERIFY2(methodeExacte->resolutionPlneMip2("") <= 8, "Solution trouve inférieure ou égale au nombre de jobs total");

}

void ClassTest::testSolutionInstanceMip1(){

    string fichierInstance = "instance-8-3-3.data";

    MethodeExacte* methodeExacte = new MethodeExacte(fichierInstance);

    QVERIFY2(methodeExacte->resolutionPlneMip1("") == 7, "Solution optimale trouvée avec le Mip1");
}

void ClassTest::testSolutionInstanceMip2(){

    string fichierInstance = "instance-8-3-3.data";

    MethodeExacte* methodeExacte = new MethodeExacte(fichierInstance);

    QVERIFY2(methodeExacte->resolutionPlneMip2("") == 7, "Solution optimale trouvée avec le Mip2");

}
