#ifndef ADDBAUDDIALOG_H
#define ADDBAUDDIALOG_H

#include <QDialog>

namespace Ui {
class AddBaudDialog;
}

class AddBaudDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBaudDialog(QWidget *parent = 0);
    ~AddBaudDialog();
signals:
    addbaud(int);

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::AddBaudDialog *ui;
};

#endif // ADDBAUDDIALOG_H
