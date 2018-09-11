#ifndef AES256_H
#define AES256_H
#include <QByteArray>
#include "gf256.h"


class AES256
{
private:
    QByteArray block;
    QByteArray key;
    unsigned char state[4][4];
    unsigned char keySchedule[4][60];
    unsigned char sBox[256];
    unsigned char invMult[256];
    unsigned char invSBox[256];
    unsigned char rCon[4][15];

    void subBytes();
    void shiftRows();
    void mixColumns();
    void addRoundKey(int roundNum);
    void keyExpansion();
    void invSubBytes();
    void invShiftRows();
    void invMixColumns();
    void subWord(unsigned char word[4]);
    void rotWord(unsigned char word[4]);

public:
    AES256();
    void encrypt(QByteArray &data);
    void decrypt(QByteArray &data);
    void setKey(QByteArray key);
};

#endif // AES256_H
