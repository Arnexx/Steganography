#ifndef STEGOBLOCK_H
#define STEGOBLOCK_H
#include <QtGlobal>
#include <QByteArray>

enum class stegoType {LSB, MSB, RandomBits};
class StegoBlock
{
private:
    QByteArray dataArray;
    QByteArray containerBlock;
    int key;
    int nullBytesCounter;

public:
    StegoBlock();
    ~StegoBlock();

    void setContainerBlock(QByteArray a);
    QByteArray getContainerBlock();
    void setDataArray(QByteArray a);
    QByteArray getDataArray();
    void encode(stegoType type);
    bool decode(stegoType type);
    void setKey(int key);
private:
    unsigned char setBit(unsigned char bitValue, unsigned char byteValue, int bitNum);
    unsigned char getBit(unsigned char byteValue, int bitNum);
};

#endif // STEGOBLOCK_H
