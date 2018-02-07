#ifndef PLNEMIP2_H
#define PLNEMIP2_H
#include <ilcplex/ilocplex.h>
#include <iostream>
#include <algorithm>
#include<string>
#include <time.h>
#include <map>
#include <vector>

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

int resolvePlneMip2(string fichierInstance, string fichierResultat);

map<int,vector<int>> getSubset(NumMatrix eh, int nb_job);

#endif // PLNEMIP2_H
