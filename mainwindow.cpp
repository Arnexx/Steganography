#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyles(styles);
    ui->encodeButton->setStyleSheet(styles[0]);
    ui->decodeButton->setStyleSheet(styles[0]);

    QPixmap pixmap(":/image/rc/lock.png");
    QIcon ButtonIcon(pixmap);
    ui->encodeButton->setIcon(ButtonIcon);
    ui->encodeButton->setIconSize(QSize(24, 24));

    pixmap.load(":/image/rc/unlock.png");
    ButtonIcon.addPixmap(pixmap);
    ui->decodeButton->setIcon(ButtonIcon);
    ui->decodeButton->setIconSize(QSize(24, 24));

    QPixmap background(":/image/rc/background.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
    this->setFixedSize(360,240);

    pixmap.load(":/image/rc/logo.png");
    this->setWindowIcon(QIcon(pixmap));


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



