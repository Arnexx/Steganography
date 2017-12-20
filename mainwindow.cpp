#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stegoblock.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_encodeButton_clicked()
{
    Encode *encodeWindow = new Encode(this);
      encodeWindow->show(); //вызов диалогового окна
}

void MainWindow::on_decodeButton_clicked()
{
    Decode *encodeWindow = new Decode(this);
      encodeWindow->show(); //вызов диалогового окна

}


