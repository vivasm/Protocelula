#ifndef DIALOG_H
#define DIALOG_H


#include <QDialog>
#include "ambiente.h"
#include <QTimer>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButtonRoda_clicked();
    void roda();

private:
    Ui::Dialog *ui;
    ambiente amb;
    QTimer *tic;


protected:
    void paintEvent(QPaintEvent *e);
};

#endif // DIALOG_H
