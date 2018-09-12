#include "encode.h"
#include "ui_encode.h"

Encode::Encode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Encode)
{
    ui->setupUi(this);
    setStyles(styles);
    stegoFile.setFileName("stegoPicture.bmp");

    ui->keyLineEdit->setVisible(false);
    ui->keyLabel->setVisible(false);

    QPixmap background(":/image/rc/background.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    ui->aesKeyLineEdit->setStyleSheet(styles[1]);
    ui->containerFileLineEdit->setStyleSheet(styles[1]);
    ui->dataFileLineEdit->setStyleSheet(styles[1]);
    ui->keyLineEdit->setStyleSheet(styles[1]);

    ui->lsbRadioButton->setStyleSheet(styles[2]);
    ui->msbRadioButton->setStyleSheet(styles[2]);
    ui->randomBitRadioButton->setStyleSheet(styles[2]);

    ui->backButton->setStyleSheet(styles[3]);
    ui->startButton->setStyleSheet(styles[3]);



}

Encode::~Encode()
{
    delete ui;
}

void Encode::on_startButton_clicked()
{
    QByteArray dataBlock, containerBlock, dataBlock2;
    QString dataFileName = ui->dataFileLineEdit->text();
    QString containerFileName = ui->containerFileLineEdit->text();

    int headerLength = 54;
    AES256 aes;
    bool isKey = true;
    containerFileName = ui->containerFileLineEdit->text();
    ui->progressBar->setValue(0);

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

    containerBlock = containerFile.read(headerLength); //copy header
    stegoFile.write(containerBlock);

    int containerBlocksAmount = (containerFile.size() - headerLength) / 128+1;
    int dataBlocksAmount = dataFile.size() / 16+2;
    int length = containerBlocksAmount < dataBlocksAmount ? containerBlocksAmount  : dataBlocksAmount;
    StegoBlock block;
    block.setKey(ui->keyLineEdit->text().toInt());

    aes.setKey(ui->aesKeyLineEdit->text().toLatin1());
    if(ui->aesKeyLineEdit->text() == "")
        isKey = false;

    for(int i=0; i < length; ++i)
    {
        if(length == dataBlocksAmount &&  i == (length-1))
        {
            for(int j = 0; j < 16; j++)
                dataBlock[j] = 0;
        }
        else
            dataBlock = dataFile.read(16);
        containerBlock = containerFile.read(128);

        if(isKey)
            aes.encrypt(dataBlock);        //encrypt aes256

        block.setDataArray(dataBlock);
        block.setContainerBlock(containerBlock);


        if(ui->lsbRadioButton->isChecked())         //encode
            block.encode(stegoType::LSB);
        if(ui->msbRadioButton->isChecked())         //encode
            block.encode(stegoType::MSB);
        if(ui->randomBitRadioButton->isChecked())         //encode
            block.encode(stegoType::RandomBits);

        stegoFile.write((QByteArray)block.getContainerBlock());
        ui->progressBar->setValue(i * 100 / length + 1);
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
}

void Encode::on_backButton_clicked()
{
    this->close();
}

void Encode::on_randomBitRadioButton_clicked(bool checked)
{
    if(checked)
    {
        ui->keyLineEdit->setVisible(true);
        ui->keyLabel->setVisible(true);
    }
}

void Encode::on_lsbRadioButton_clicked(bool checked)
{
    if(checked)
    {
        ui->keyLineEdit->setVisible(false);
        ui->keyLabel->setVisible(false);
    }
}

void Encode::on_msbRadioButton_clicked(bool checked)
{
    if(checked)
    {
        ui->keyLineEdit->setVisible(false);
        ui->keyLabel->setVisible(false);
    }
}




