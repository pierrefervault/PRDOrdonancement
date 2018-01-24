#ifndef WORKERFOLDER_H
#define WORKERFOLDER_H

#include <QObject>
#include <QWidget>

class WorkerFolder : public QObject {
    Q_OBJECT

public:
    WorkerFolder(QString filename, QString typeOfResolution);
    ~WorkerFolder();
public slots :
    void process();
signals:
    void finished();
    void error(QString err);
private:
    QString filename;
    QString typeOfResolution;
};

#endif // WORKERFOLDER_H
