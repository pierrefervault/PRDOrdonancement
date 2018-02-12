#ifndef CLASSTEST_H
#define CLASSTEST_H

#include <QtTest/QTest>
#include <QObject>
#include "heuristique.h"
#include "methodeexacte.h"

using namespace std;

class ClassTest : public QObject
{
    Q_OBJECT

public:
    explicit ClassTest(QObject *parent = 0);

private slots:

    void testSolutionInferieureOuEgaleNbrJobsAffectation1();
    void testSolutionInferieureOuEgaleNbrJobsAffectation2();
    void testSolutionInferieureOuEgaleNbrJobsMip1();
    void testSolutionInferieureOuEgaleNbrJobsMip2();
};

#endif // CLASSTEST_H
