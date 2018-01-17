#ifndef WORKERMIP2_H
#define WORKERMIP2_H

#include <QObject>
#include <QWidget>

class WorkerMip2 : public QObject {
    Q_OBJECT

public:
    WorkerMip2(QString filename, QString fileresult);
    ~WorkerMip2();
public slots :
    void process();
signals:
    void finished();
    void error(QString err);
private:
    QString filename;
    QString fileresult;
};

#endif // WORKERMIP2_H
