#ifndef CLASSTEST_H
#define CLASSTEST_H

#include <QtTest/QTest>
#include <QObject>
#include <QDir>
#include "instance.h"
#include "resultat.h"
#include "heuristique.h"
#include "methodeexacte.h"

using namespace std;

/**
 * @brief
 *
 */
class ClassTest : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit ClassTest(QObject *parent = 0);

private slots:

    void testGeneration();

    /**
     * @brief
     *
     */
    void testSolutionInferieureOuEgaleNbrJobsAffectation1();

    /**
     * @brief
     *
     */
    void testSolutionInferieureOuEgaleNbrJobsAffectation2();

    /**
     * @brief
     *
     */
    void testSolutionInferieureOuEgaleNbrJobsMip1();

    /**
     * @brief
     *
     */
    void testSolutionInferieureOuEgaleNbrJobsMip2();


    void testSolutionMip1EgaleMip2();

    /**
     * @brief
     *
     */
    void testSolutionMip1SuperieureOuEgaleHeuristique();

    void testHeuristiqueGapPositif();

    void supprimerInstanceEtResultat();
};

#endif // CLASSTEST_H
