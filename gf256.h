#ifndef GF256_H
#define GF256_H
#include <QFile>
//#include <QByteArray>


class GF256
{
public:
    GF256();
    static unsigned char mult(unsigned char a, unsigned char b);
    static unsigned char pow(unsigned char a, int n);
    static unsigned char xMult(unsigned char a);
   // QFile file;
   // QByteArray array;
   // void test();

};

#endif // GF256_H
