#ifndef CLASSTEST_H
#define CLASSTEST_H

#include <QtTest/QTest>
#include <QObject>
#include <QDir>
#include <QDirIterator>
#include "instance.h"
#include "resultat.h"
#include "heuristique.h"
#include "methodeexacte.h"
#include "calculcomparaison.h"

using namespace std;

/**
 * @brief Classe permetant d'effectuer les tests des fonctionnalités du programme principal
 *
 */
class ClassTest : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Contructeur de la classe de test
     *
     * @param parent
     */
    explicit ClassTest(QObject *parent = 0);

private slots:

    /**
     * @brief Test la génération de fichier d'instance et
     * vérifie que chacune des valeurs spécifiées est correcte
     *
     */
    void testGeneration();

    /**
     * @brief Test vérifiant que les affectations machines par machines
     * donnent des solutions dont les valeurs sont inférieures au nombre de jobs de l'instance
     *
     */
    void testSolutionInferieureOuEgaleNbrJobsAffectation1();

    /**
     * @brief Test vérifiant que les affectations priorisant la machine la moins chargée
     * donnent des solutions dont les valeurs sont inférieures au nombre de jobs de l'instance
     *
     */
    void testSolutionInferieureOuEgaleNbrJobsAffectation2();

    /**
     * @brief Test vérifiant que la résolution exacte indexée temps
     * donne des solutions dont les valeurs sont inférieures au nombre de jobs de l'instance
     *
     */
    void testSolutionInferieureOuEgaleNbrJobsMip1();

    /**
     * @brief Test vérifiant que la résolution exacte indexée jobs
     * donne des solutions dont les valeurs sont inférieures au nombre de jobs de l'instance
     *
     */
    void testSolutionInferieureOuEgaleNbrJobsMip2();


    /**
     * @brief Test vérifiant que la résolution exacte indexée temps
     * donne des solutions égales à celles trouvées par la résolution exacte indexée jobs
     *
     */
    void testSolutionMip1EgaleMip2();

    /**
     * @brief Test vérifiant que la résolution exacte indexée temps
     * donne des solutions égales ou meilleures que celles trouvées par les heuristiques
     *
     */
    void testSolutionMip1SuperieureOuEgaleHeuristique();

    /**
     * @brief Test vérifiant la cohérence de la comparaison des différentes méthodes de résolution d'instances
     *
     */
    void testCoherenceComparaison();

    /**
     * @brief Supprime les dossiers d'instances et de résultats générés pour les tests
     *
     */
    void supprimerInstanceEtResultat();
};

#endif // CLASSTEST_H
