#ifndef GENERATEINSTANCE_H
#define GENERATEINSTANCE_H

#include <QDialog>

namespace Ui {
class GenerateInstance;
}

class GenerateInstance : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateInstance(QWidget *parent = 0);
    ~GenerateInstance();

private slots:
    void on_okPushButton_clicked();

    void on_annulerPushButton_clicked();

private:
    Ui::GenerateInstance *ui;
};

#endif // GENERATEINSTANCE_H
