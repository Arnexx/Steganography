#ifndef DECODE_H
#define DECODE_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <iostream>
#include "stegoblock.h"

namespace Ui {
class Decode;
}

class Decode : public QDialog
{
    Q_OBJECT

public:
    explicit Decode(QWidget *parent = 0);
    ~Decode();

private slots:
    void on_backButton_clicked();
    void on_randomBitRadioButton_clicked(bool checked);
    void on_lsbRadioButton_clicked(bool checked);
    void on_msbRadioButton_clicked(bool checked);
    void on_startButton_clicked();

private:
    Ui::Decode *ui;
    QFile dataFile;
    QFile stegoFile;
};

#endif // DECODE_H