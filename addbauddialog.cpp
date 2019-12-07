#include "addbauddialog.h"
#include "ui_addbauddialog.h"

AddBaudDialog::AddBaudDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBaudDialog)
{
    ui->setupUi(this);
    // 设置只能输入数字
    QRegExp regexp("[0-9]{100}");
    ui->lineEdit->setValidator(new QRegExpValidator(regexp, this));
}

AddBaudDialog::~AddBaudDialog()
{
    delete ui;
}

void AddBaudDialog::on_pushButton_ok_clicked()
{
    emit addbaud(ui->lineEdit->text().toInt());
    this->accept();
}

void AddBaudDialog::on_pushButton_cancel_clicked()
{
    this->reject();
}
