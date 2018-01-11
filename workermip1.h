#ifndef WORKERMIP1_H
#define WORKERMIP1_H

#include <QObject>
#include <QWidget>

class WorkerMip1 : public QObject {
    Q_OBJECT

public:
    WorkerMip1(QString filename, QString fileresult);
    ~WorkerMip1();
public slots :
    void process();
signals:
    void finished();
    void error(QString err);
private:
    QString filename;
    QString fileresult;
};

#endif // WORKERMIP1_H
