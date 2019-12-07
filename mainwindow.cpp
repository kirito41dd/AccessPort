#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "qmessagebox.h"
#include <iostream>
#include <string.h>

QSerialPort *g_mySerialPort;
QByteArray g_arry;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->verticalLayout_2);
    init();
    connect(g_mySerialPort, SIGNAL(readyRead()), this, SLOT(recv_data()));
    ui->statusBar->showMessage("1710252441-郑世豪");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPort()
{
    g_mySerialPort->setPortName(ui->comboBox_COMx->currentText());
    g_mySerialPort->setBaudRate(ui->comboBox_Baud->currentText().toInt());
    g_mySerialPort->setDataBits(QSerialPort::Data8);
    g_mySerialPort->setStopBits(QSerialPort::OneStop);
    g_mySerialPort->setParity(QSerialPort::NoParity);
}

void MainWindow::init()
{
    // 添加所有串口到comboBox
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->comboBox_COMx->addItem(info.portName());
    }
    if (QSerialPortInfo::availablePorts().size() == 0) {
        ui->statusBar->showMessage("未检测到COM");
    }
    // 添加波特率
    QVector<int> vaud = {50,75,100,150,300,600,1200,2400,4800,9600,19200,38400};
    foreach (int a, vaud) {
        ui->comboBox_Baud->addItem(QString::number(a));
    }
    // 添加停止位
    ui->comboBox_StopBits->addItem(QString::number(1));
    // 添加数据位
    ui->comboBox_DataBits->addItem(QString::number(8));
    // 添加奇偶校验
    ui->comboBox_Parity->addItem(tr("no"));

    g_mySerialPort = new QSerialPort(this);

    // 设置16进制输入
    QRegExp regexp("[a-fA-f0-9 ]{100}");
    ui->lineEdit_send_16->setValidator(new QRegExpValidator(regexp, this));
}

void MainWindow::showData()
{
    if (ui->pushButton_mode->text() == tr("字符模式")) {
        ui->plainTextEdit_recv->clear();
        ui->plainTextEdit_recv->appendPlainText(tr(g_arry));
    } else {
        std::string str;
        char c[10];
        for (int i=0; i<g_arry.length(); ++i) {
            int a = (unsigned char)(g_arry[i]);
            snprintf(c, 10, "%02X ", a);
            c[3]=0;
            str += c;
        }
        ui->plainTextEdit_recv->clear();
        ui->plainTextEdit_recv->appendPlainText(QString::fromStdString(str));
    }
}

void MainWindow::recv_data()
{
    QByteArray buf = g_mySerialPort->readAll();
    if (!buf.isEmpty()) {
        g_arry.append(buf);

        showData();
    }
}


void MainWindow::on_pushButton_open_clicked()
{
    if (ui->pushButton_open->text() == tr("打开串口")) {
        setPort();
        if (g_mySerialPort->open(QIODevice::ReadWrite)) {

        } else {
            QMessageBox::information(this, tr("错误"), tr("打开失败"), tr("确定"));
            return;
        }
        ui->pushButton_open->setText(tr("关闭串口"));
        ui->statusBar->showMessage("打开成功");
    } else {
        g_mySerialPort->close();
        ui->pushButton_open->setText(tr("打开串口"));
        ui->statusBar->showMessage("已关闭");
    }

}

void MainWindow::on_pushButton_send_clicked()
{
    QString str = ui->lineEdit_send->text().toLatin1();
    g_mySerialPort->write(str.toLatin1());
}

void MainWindow::on_pushButton_send_16_clicked()
{
     QString str = ui->lineEdit_send_16->text().toLatin1();
     str.remove(QRegExp("\\s"));
     qDebug() << str;
     QByteArray arry = QByteArray::fromHex(str.toLatin1());
     for (int a=0; a<arry.length(); a++) {
         qDebug() << (unsigned char)(arry[a]);
     }
     g_mySerialPort->write(arry);
}

void MainWindow::on_pushButton_mode_clicked()
{
    if (ui->pushButton_mode->text() == tr("字符模式")) {
        ui->pushButton_mode->setText(tr("二进制模式"));
        showData();
    } else {
        ui->pushButton_mode->setText(tr("字符模式"));
        showData();
    }
}

void MainWindow::on_pushButton_clear_clicked()
{
    g_arry.clear();
    ui->plainTextEdit_recv->clear();
}
