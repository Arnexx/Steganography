#include "aes256.h"

AES256::AES256()
{

    unsigned char tempinvMult[256] = {0, 1, 141, 246, 203, 82, 123, 209, 232, 79, 41, 192, 176, 225, 229, 199, \
               116, 180, 170, 75, 153, 43, 96, 95, 88, 63, 253, 204, 255, 64, 238, 178, \
               58, 110, 90, 241, 85, 77, 168, 201, 193, 10, 152, 21, 48, 68, 162, 194, \
               44, 69, 146, 108, 243, 57, 102, 66, 242, 53, 32, 111, 119, 187, 89, 25,\
               29, 254, 55, 103, 45, 49, 245, 105, 167, 100, 171, 19, 84, 37, 233, 9, \
               237, 92, 5, 202, 76, 36, 135, 191, 24, 62, 34, 240, 81, 236, 97, 23,\
               22, 94, 175, 211, 73, 166, 54, 67, 244, 71, 145, 223, 51, 147, 33, 59, \
               121, 183, 151, 133, 16, 181, 186, 60, 182, 112, 208, 6, 161, 250, 129, 130, \
               131, 126, 127, 128, 150, 115, 190, 86, 155, 158, 149, 217, 247, 2, 185, 164, \
               222, 106, 50, 109, 216, 138, 132, 114, 42, 20, 159, 136, 249, 220, 137, 154, \
               251, 124, 46, 195, 143, 184, 101, 72, 38, 200, 18, 74, 206, 231, 210, 98, \
               12, 224, 31, 239, 17, 117, 120, 113, 165, 142, 118, 61, 189, 188, 134, 87, \
               11, 40, 47, 163, 218, 212, 228, 15, 169, 39, 83, 4, 27, 252, 172, 230, \
               122, 7, 174, 99, 197, 219, 226, 234, 148, 139, 196, 213, 157, 248, 144, 107, \
               177, 13, 214, 235, 198, 14, 207, 173, 8, 78, 215, 227, 93, 80, 30, 179, \
               91, 35, 56, 52, 104, 70, 3, 140, 221, 156, 125, 160, 205, 26, 65, 28 };

   unsigned char tempsBox[256] = {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, \
            0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, \
            0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, \
            0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, \
            0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, \
            0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, \
            0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, \
            0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, \
            0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, \
            0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, \
            0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, \
            0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, \
            0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, \
            0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, \
            0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, \
            0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

    unsigned char tempinvSBox[256] = {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,  \
               0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,  \
               0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,  \
               0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,  \
               0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,  \
               0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,  \
               0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,  \
               0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,  \
               0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,  \
               0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,  \
               0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,  \
               0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,  \
               0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,  \
               0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,  \
               0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,  \
               0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d};
    GF256 gf256;

    for(int i = 0; i < 256; i++)
    {
        invMult[i] = tempinvMult[i];
        sBox[i] = tempsBox[i];
        invSBox[i] = tempinvSBox[i];
    }

    for(int i = 1; i < 15; i++)
    {
        rCon[0][i] = gf256.pow(0x01, i);
        rCon[1][i] = rCon[2][i] = rCon[3][i] = 0;
    }

}

void AES256::encrypt(QByteArray data)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            state[i][j] = data[i + 4*j];

    addRoundKey(0);
    for (int i = 1; i < 14; i++)
    {
        subBytes();
        shiftRows();
        mixColumns();
        addRoundKey(i);
    }
    subBytes();
    shiftRows();
    addRoundKey(14);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            data[i + 4*j] = state[i][j];


}

void AES256::decrypt(QByteArray data)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            state[i][j] = data[i + 4*j];

    addRoundKey(14);
    for (int i = 13; i > 0; i--)
    {
        shiftRows();
        subBytes();
        addRoundKey(i);
        mixColumns();
    }
    shiftRows();
    subBytes();
    addRoundKey(0);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            data[i + 4*j] = state[i][j];

}

void AES256::setKey(QByteArray key)
{
    this->key.resize(32);
    for(int i = 0; i < key.length(); i++)
        this->key[i] = key[i];
    keyExpansion();
}

void AES256::subWord(unsigned char word[4])
{
    for (int i = 0; i < 4; ++i)
    {
        word[i] = sBox[word[i]];
    }
}

void AES256::rotWord(unsigned char word[4])
{
    unsigned char temp = word[0];
    for(int i = 0; i < 3; i++)
    {
        word[i] = word[i + 1];
    }
    word[3] = temp;
}

//unsigned char multx4(unsigned char a, unsigned char k)
//{
//    if(k == 0x01)
//        return a;
//    if(k == 0x02)
//    {
//        if(a < 0x80)
//        {
//            a <<= 1;
//        }
//        else
//        {
//            a <<= 1;
//            a ^= 0x1b;
//        }
//    }
//    if(k == 0x03)
//    {
//        a = mult4(a, 0x02) ^ a;
//    }
//    return a;
//}

void AES256::subBytes()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            state[i][j] = sBox[state[i][j]];
        }
}

void AES256::shiftRows()
{
    unsigned char temp;
    for(int step = 1; step < 3; step++)
    {
        for(int i = step; i < 4; i++)
        {
            temp = state[i][0];
            for(int j = 0; j < 3; j++)
            {
                state[i][j] = state[i][j+1];
            }
            state[i][3] = temp;

        }
    }
}

void AES256::mixColumns()
{
    unsigned char s0, s1, s2, s3;
    GF256 gf256;

    for(int i = 0; i < 4; i++)
    {
        s0 = gf256.mult(state[0][i], 0x02) ^ gf256.mult(state[1][i], 0x03) ^ state[2][i] ^ state[3][i];
        s1 = state[0][i] ^ gf256.mult(state[1][i], 0x02) ^ gf256.mult(state[2][i], 0x03) ^ state[3][i];
        s2 = state[0][i] ^ state[1][i] ^ gf256.mult(state[2][i], 0x02) ^ gf256.mult(state[3][i], 0x03);
        s3 = gf256.mult(state[0][i], 0x03) ^ state[1][i] ^ state[2][i] ^ gf256.mult(state[3][i], 0x02);

        state[0][i] = s0;
        state[1][i] = s1;
        state[2][i] = s2;
        state[3][i] = s3;
    }
}

void AES256::addRoundKey(int roundNum)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            state[i][j] ^= keySchedule[i][j + roundNum * 4];
        }
}

void AES256::keyExpansion()
{
    unsigned char word[4] = {};
    int i = 0;
    while(i < 8)
    {
        for(int j = 0; j < 4; j++)
        {
            keySchedule[j][i] = key[4 * i + j];
        }

        i++;
    }

    i = 8;

    while(i < 60)
    {
        for(int j = 0; j < 4; j++)
        {
            word[j] = keySchedule[j][i - 1];
        }

        if (i % 8 == 0)
        {
            rotWord(word);
            subWord(word);
            word[0] ^=  rCon[0][i / 8];
        }
        else if (i % 8 == 4)
            subWord(word);

        for(int j = 0; j < 4; j++)
        {
            keySchedule[j][i] = keySchedule[j][i - 8] ^ word[j];
        }

        i++;
    }
}

void AES256::invSubBytes()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            state[i][j] = invSBox[state[i][j]];
        }
}

void AES256::invShiftRows()
{
    unsigned char temp;
    for(int step = 1; step < 3; step++)
    {
        for(int i = step; i < 4; i++)
        {
            temp = state[i][3];
            for(int j = 3; j > 0; j--)
            {
                state[i][j] = state[i][j - 1];
            }
            state[i][0] = temp;

        }
    }
}

void AES256::invMixColumns()
{
    unsigned char s0, s1, s2, s3;
    GF256 gf256;

    for(int i = 0; i < 4; i++)
    {
        s0 = gf256.mult(state[0][i], 0x0e) ^ gf256.mult(state[1][i], 0x0b) ^ gf256.mult(state[2][i], 0x0d) ^ gf256.mult(state[3][i], 0x09);
        s1 = gf256.mult(state[0][i], 0x09) ^ gf256.mult(state[1][i], 0x0e) ^ gf256.mult(state[2][i], 0x0b) ^ gf256.mult(state[3][i], 0x0d);
        s2 = gf256.mult(state[0][i], 0x0d) ^ gf256.mult(state[1][i], 0x09) ^ gf256.mult(state[2][i], 0x0e) ^ gf256.mult(state[3][i], 0x0b);
        s3 = gf256.mult(state[0][i], 0x0b) ^ gf256.mult(state[1][i], 0x0d) ^ gf256.mult(state[2][i], 0x09) ^ gf256.mult(state[3][i], 0x0e);


        state[0][i] = s0;
        state[1][i] = s1;
        state[2][i] = s2;
        state[3][i] = s3;
    }
}
