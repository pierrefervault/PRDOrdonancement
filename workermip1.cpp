#include "workermip1.h"

WorkerMip1::WorkerMip1(QString command)
{
    this->command = command;
}

WorkerMip1::~WorkerMip1(){

}

void WorkerMip1::process(){
    system(command.toStdString().c_str());
    emit finished();
}

void WorkerMip1::error(QString err){

}

void WorkerMip1::finished(){

}
