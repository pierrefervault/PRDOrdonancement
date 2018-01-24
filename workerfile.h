#ifndef WORKERFILE_H
#define WORKERFILE_H

#include <QObject>
#include <QWidget>

class WorkerFile : public QObject {
    Q_OBJECT

public:
    WorkerFile(QString filename, QString typeOfResolution);
    ~WorkerFile();
public slots :
    void process();
signals:
    void finished();
    void error(QString err);
private:
    QString filename;
    QString typeOfResolution;
};

#endif // WORKERFILE_H
