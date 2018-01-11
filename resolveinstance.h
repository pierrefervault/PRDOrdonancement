#ifndef RESOLVEINSTANCE_H
#define RESOLVEINSTANCE_H

#include <QDialog>

namespace Ui {
class ResolveInstance;
}

class ResolveInstance : public QDialog
{
    Q_OBJECT

public:
    explicit ResolveInstance(QWidget *parent = 0);
    void processPlneMIP1(QString command);
    ~ResolveInstance();

private slots:
    void on_choisirFichierPushButton_clicked();

    void on_validerPushButton_clicked();

    void on_annulerPushButton_clicked();

private:
    Ui::ResolveInstance *ui;
};

#endif // RESOLVEINSTANCE_H
