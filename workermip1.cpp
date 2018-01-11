#include "workermip1.h"
#include "plne.h"
#include <iostream>

using namespace std;

WorkerMip1::WorkerMip1(QString filename, QString fileresult)
{
    this->filename = filename;
    this->fileresult = fileresult;
}

WorkerMip1::~WorkerMip1(){

}

void WorkerMip1::process(){
    resolvePlne(this->filename.toStdString().c_str(), this->fileresult.toStdString().c_str());
    emit finished();
}
