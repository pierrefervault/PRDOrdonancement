#ifndef PLNE_H
#define PLNE_H
#include <ilcplex/ilocplex.h>
#include<iostream>
#include <time.h>

using namespace std;

//Déclarartion de l'ensemble des types utilisés par cplex

ILOSTLBEGIN
typedef IloArray<IloIntArray>    IntMatrix;
typedef IloArray<IloNumArray>    NumMatrix;
typedef IloArray<NumMatrix>    NumMatrix3;
typedef IloArray<NumMatrix3>    NumMatrix4;
typedef IloArray<NumMatrix4>    NumMatrix5;
typedef IloArray<IloNumVarArray> NumVarMatrix;
typedef IloArray<NumVarMatrix> NumVarMatrix3;
typedef IloArray<NumVarMatrix3> NumVarMatrix4;
typedef IloArray<NumVarMatrix4> NumVarMatrix5;
typedef IloArray<NumVarMatrix5> NumVarMatrix6;

int resolvePlne(string fichierInstance, string fichierResultat);

#endif // PLNE_H
