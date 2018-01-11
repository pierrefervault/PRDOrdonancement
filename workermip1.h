#ifndef WORKERMIP1_H
#define WORKERMIP1_H

#include <QObject>
#include <QWidget>

class WorkerMip1 : public QObject {
    Q_OBJECT

public:
    WorkerMip1(QString command);
    ~WorkerMip1();
public slots :
    void process();
signals:
    void finished();
    void error(QString err);
private:
    QString command;
};

#endif // WORKERMIP1_H
