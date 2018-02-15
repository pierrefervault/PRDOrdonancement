#ifndef CLASSTEST_H
#define CLASSTEST_H

#include <QtTest/QTest>
#include <QObject>
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

    void testSolutionInstanceMip1();

    /**
     * @brief
     *
     */
    void testSolutionInstanceMip2();
};

#endif // CLASSTEST_H
