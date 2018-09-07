#ifndef ENCODE_H
#define ENCODE_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <iostream>
#include <QByteArray>
#include "stegoblock.h"
#include "aes256.h"

namespace Ui {
class Encode;
}

class Encode : public QDialog
{
    Q_OBJECT

public:
    explicit Encode(QWidget *parent = 0);
    ~Encode();

private slots:
    void on_backButton_clicked();
    void on_randomBitRadioButton_clicked(bool checked);
    void on_lsbRadioButton_clicked(bool checked);
    void on_msbRadioButton_clicked(bool checked);
    void on_startButton_clicked();


private:
    Ui::Encode *ui;
    QFile dataFile;
    QFile containerFile;
    QFile stegoFile;
};

#endif // ENCODE_H
