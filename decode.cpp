#include "decode.h"
#include "ui_decode.h"

Decode::Decode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Decode)
{
    ui->setupUi(this);
}

void Decode::on_backButton_clicked()
{
    this->close();
}

void Decode::on_randomBitRadioButton_clicked(bool checked)
{
    if(checked)
        ui->keyLineEdit->setEnabled(true);
}

void Decode::on_lsbRadioButton_clicked(bool checked)
{
    if(checked)
    {
         ui->keyLineEdit->setDisabled(true);
    }
}

void Decode::on_msbRadioButton_clicked(bool checked)
{
    if(checked)
    {
         ui->keyLineEdit->setDisabled(true);
    }
}

void Decode::on_startButton_clicked()
{
    QString dataFileName = QString("finaldata.txt");
    QString stegoFileName = ui->containerFileLineEdit->text();
    QByteArray containerBlock;
    int headerLength = 54;
    if(ui->musicBox->isChecked())
    {
        headerLength = 104;
        dataFileName = QString("musicdata.txt");
    }

    dataFile.setFileName(dataFileName);
    stegoFile.setFileName(stegoFileName);

    dataFile.open(QIODevice::ReadWrite);
    stegoFile.open(QIODevice::ReadOnly);


    containerBlock = stegoFile.read(headerLength); //skip header


    int containerBlocksAmount = (stegoFile.size() - headerLength) / 256+1;
    int length = containerBlocksAmount;
    StegoBlock block;
    bool endFlag = false;
    block.setKey(ui->keyLineEdit->text().toInt());

    for(int i=0; i < length; ++i)
    {

        containerBlock = stegoFile.read(256);
        block.setContainerBlock(containerBlock);


        if(ui->lsbRadioButton->isChecked())         //decode
            endFlag = block.decode(stegoType::LSB);

        if(ui->msbRadioButton->isChecked())         //decode
            endFlag = block.decode(stegoType::MSB);

        if(ui->randomBitRadioButton->isChecked())         //decode
            endFlag = block.decode(stegoType::RandomBits);

        dataFile.write((QByteArray)block.getDataArray());

        if(endFlag)
            break;
    }


    dataFile.close();

    stegoFile.close();
    ui->doneLabel->setText("DONE.");

    //QMessageBox::information(this,"Decode", "Done.");

}

Decode::~Decode()
{
    delete ui;
}
