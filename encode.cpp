#include "encode.h"
#include "ui_encode.h"

Encode::Encode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Encode)
{
    ui->setupUi(this);
    stegoFile.setFileName("stegoPicture.bmp");
}

Encode::~Encode()
{
    delete ui;
}

void Encode::on_backButton_clicked()
{
    this->close();
}

void Encode::on_randomBitRadioButton_clicked(bool checked)
{
    if(checked)
        ui->keyLineEdit->setEnabled(true);
}

void Encode::on_lsbRadioButton_clicked(bool checked)
{
    if(checked)
    {
         ui->keyLineEdit->setDisabled(true);
    }
}

void Encode::on_msbRadioButton_clicked(bool checked)
{
    if(checked)
    {
         ui->keyLineEdit->setDisabled(true);
    }
}

void Encode::on_startButton_clicked()
{
    QString dataFileName = ui->dataFileLineEdit->text();
    QString containerFileName = ui->containerFileLineEdit->text();
    QByteArray dataBlock, containerBlock;
    int headerLength = 54;
    AES256 aes;
    dataFile.setFileName(dataFileName);
    containerFile.setFileName(containerFileName);

    if(ui->musicBox->isChecked())
    {
        headerLength = 104;
        stegoFile.setFileName("stegoMusic.wav");
    }

    dataFile.open(QIODevice::ReadWrite);
    containerFile.open(QIODevice::ReadWrite);
    stegoFile.open(QIODevice::WriteOnly);

    containerBlock.resize(128);
    containerBlock = containerFile.read(headerLength); //copy header
    stegoFile.write(containerBlock);

    int containerBlocksAmount = (containerFile.size() - headerLength) / 128+1;
    int dataBlocksAmount = dataFile.size() / 16+1;
    int length = containerBlocksAmount < dataBlocksAmount ? containerBlocksAmount  : dataBlocksAmount;
    StegoBlock block;
    block.setKey(ui->keyLineEdit->text().toInt());

    aes.setKey(ui->aesKeyLineEdit->text().toLatin1());

    for(int i=0; i < length; ++i)
    {
        dataBlock = dataFile.read(16);
        containerBlock = containerFile.read(128);

        aes.encrypt(dataBlock);
        //encode aes256
        //
        block.setDataArray(dataBlock);
        block.setContainerBlock(containerBlock);


        if(ui->lsbRadioButton->isChecked())         //encode
            block.encode(stegoType::LSB);
        if(ui->msbRadioButton->isChecked())         //encode
            block.encode(stegoType::MSB);
        if(ui->randomBitRadioButton->isChecked())         //encode
            block.encode(stegoType::RandomBits);



        stegoFile.write((QByteArray)block.getContainerBlock());
    }
    if(containerBlocksAmount > length)
    {
        for(int i = 0; i < containerBlocksAmount - length + 1; ++i)
        {
            containerBlock = containerFile.read(128);
            stegoFile.write(containerBlock);
        }
    }

    dataFile.close();
    containerFile.close();
    stegoFile.close();
    ui->doneLabel->setText("DONE.");

    //QMessageBox::information(this,"Encode", "Done.");

}


