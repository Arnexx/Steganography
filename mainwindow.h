#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "encode.h"
#include "decode.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_encodeButton_clicked();
    void on_decodeButton_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
