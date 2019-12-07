#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

extern QSerialPort *g_mySerialPort;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setPort();

private slots:

    void on_pushButton_open_clicked();

private:
    Ui::MainWindow *ui;
    void init();
    void showData();

 private slots:
    void recv_data(void);
    void on_pushButton_send_clicked();
    void on_pushButton_send_16_clicked();
    void on_pushButton_mode_clicked();
    void on_pushButton_clear_clicked();
};

#endif // MAINWINDOW_H
