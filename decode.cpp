#include "decode.h"
#include "ui_decode.h"

Decode::Decode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Decode)
{
    ui->setupUi(this);
    setStyles(styles);

    ui->keyLineEdit->setVisible(false);
    ui->keyLabel->setVisible(false);

    QPixmap background(":/image/rc/background.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    ui->aesKeyLineEdit->setStyleSheet(styles[1]);
    ui->containerFileLineEdit->setStyleSheet(styles[1]);
    ui->keyLineEdit->setStyleSheet(styles[1]);

    ui->lsbRadioButton->setStyleSheet(styles[2]);
    ui->msbRadioButton->setStyleSheet(styles[2]);
    ui->randomBitRadioButton->setStyleSheet(styles[2]);

    ui->backButton->setStyleSheet(styles[3]);
    ui->startButton->setStyleSheet(styles[3]);
}

void Decode::on_backButton_clicked()
{
    this->close();
}

void Decode::on_randomBitRadioButton_clicked(bool checked)
{
    if(checked)
    {
        ui->keyLineEdit->setVisible(true);
        ui->keyLabel->setVisible(true);
    }
}

void Decode::on_lsbRadioButton_clicked(bool checked)
{
    if(checked)
    {
        ui->keyLineEdit->setVisible(false);
        ui->keyLabel->setVisible(false);
    }
}

void Decode::on_msbRadioButton_clicked(bool checked)
{
    if(checked)
    {
        ui->keyLineEdit->setVisible(false);
        ui->keyLabel->setVisible(false);
    }
}

void Decode::on_startButton_clicked()
{
    QString dataFileName = QString("finaldata.txt");
    QString stegoFileName = ui->containerFileLineEdit->text();
    QByteArray containerBlock, dataBlock, bbbb;
    AES256 aes;
    aes.setKey(ui->aesKeyLineEdit->text().toLatin1());
    ui->progressBar->setValue(0);

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


    int containerBlocksAmount = (stegoFile.size() - headerLength) / 128+1;
    int length = containerBlocksAmount;
    StegoBlock block;
    bool endFlag = false;
    block.setKey(ui->keyLineEdit->text().toInt());

    for(int i=0; i < length; ++i)
    {

        containerBlock = stegoFile.read(128);
        block.setContainerBlock(containerBlock);


        if(ui->lsbRadioButton->isChecked())         //decode
            endFlag = block.decode(stegoType::LSB);

        if(ui->msbRadioButton->isChecked())         //decode
            endFlag = block.decode(stegoType::MSB);

        if(ui->randomBitRadioButton->isChecked())         //decode
            endFlag = block.decode(stegoType::RandomBits);

        dataBlock = (QByteArray)block.getDataArray();
        aes.decrypt(dataBlock);                //decrypt aes256
         ui->progressBar->setValue(i * 100 / length + 1);
        if(checkNullBlock(dataBlock))
        {
             ui->progressBar->setValue(100);
            break;
        }
        dataFile.write(dataBlock);

        if(endFlag)
            break;
    }


    dataFile.close();

    stegoFile.close();


    //QMessageBox::information(this,"Decode", "Done.");

}

bool Decode::checkNullBlock(QByteArray block)
{
    for(int i = 0; i < 16; i++)
        if(block[i] != 0)
            return false;
        else
            return true;

}

Decode::~Decode()
{
    delete ui;
}
