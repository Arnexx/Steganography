#include "stegoblock.h"

StegoBlock::StegoBlock()
{
    key = 0;
    nullBytesCounter = 0;

}

StegoBlock::~StegoBlock()
{

}
void StegoBlock::setKey(int key)
{
    this->key = key;
    qsrand(key);
}

void StegoBlock::setContainerBlock(QByteArray a)
{
   containerBlock = a;
}

QByteArray StegoBlock::getContainerBlock()
{
    return containerBlock;
}

void StegoBlock::setDataArray(QByteArray a)
{
    dataArray = a;
}

QByteArray StegoBlock::getDataArray()
{
    return dataArray;
}

unsigned char StegoBlock::setBit(unsigned char bitValue, unsigned char byteValue, int bitNum)
{
    unsigned char byte, bitMask = 1 << bitNum;
    if(bitValue == 0)
    {
        bitMask ^= (unsigned char)255;
        byteValue &= bitMask;
    }
    else
    {
        byteValue |= bitMask;
    }
    byte = byteValue;
    return byte;
}

unsigned char StegoBlock::getBit(unsigned char byteValue, int bitNum)
{
     unsigned char bitValue, bitMask = 1 << bitNum;
     bitValue = byteValue & bitMask;
     bitValue >>= bitNum;
     return bitValue;
}

void StegoBlock::encode(stegoType type)
{
    int iter = 0;
    for(int i = 0; i < 32; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            if(type == stegoType::LSB)
            {
               containerBlock[iter] = setBit((unsigned char)dataArray[i] % 2, (unsigned char)containerBlock[iter],  0);
            }
            if(type == stegoType::MSB)
            {
               containerBlock[iter] = setBit((unsigned char)dataArray[i] % 2, (unsigned char)containerBlock[iter],  7);
            }
            if(type == stegoType::RandomBits)
            {
               containerBlock[iter] = setBit((unsigned char)dataArray[i] % 2, (unsigned char)containerBlock[iter],  qrand() % 8);
            }

            dataArray[i] = (unsigned char)dataArray[i] >> 1;
            ++iter;
        }
    }
}

bool StegoBlock::decode(stegoType type)
{
    int iter = 0;
    for(int i = 0; i < 32; ++i)
    {
        dataArray[i] = 0;

        for(int j = 0; j < 8; ++j)
        {
            if(j)
                dataArray[i] = (unsigned char)dataArray[i] >> 1;

            if(type == stegoType::LSB)
            {
               dataArray[i] = (unsigned char)dataArray[i] | (getBit((unsigned char)containerBlock[iter],  0)<< 7);
            }
            if(type == stegoType::MSB)
            {
               dataArray[i] = (unsigned char)dataArray[i] | (getBit((unsigned char)containerBlock[iter],  7)) << 7;
            }
            if(type == stegoType::RandomBits)
            {
               dataArray[i] = (unsigned char)dataArray[i] | (getBit((unsigned char)containerBlock[iter],  qrand() % 8)) << 7;
            }

            ++iter;            
        }
        if(0x0 == dataArray[i])
            nullBytesCounter++;
    }

    if (nullBytesCounter >= 4)
        return true;
    else
        return false;
}
