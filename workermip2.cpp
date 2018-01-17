#include "workermip2.h"
#include "plnemip2.h"
#include <iostream>

using namespace std;

WorkerMip2::WorkerMip2(QString filename, QString fileresult)
{
    this->filename = filename;
    this->fileresult = fileresult;
}

WorkerMip2::~WorkerMip2(){

}

void WorkerMip2::process(){
    resolvePlneMip2(this->filename.toStdString().c_str(), this->fileresult.toStdString().c_str());
    emit finished();
}
