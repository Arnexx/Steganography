#include "gf256.h"

GF256::GF256()
{

}

unsigned char GF256::mult(unsigned char a, unsigned char b)
{
    unsigned char sum = 0;
    for(int i = 0; i < 8; i++)
    {
        if(b % 2)
        {
            sum ^= pow(a,i);
        }
        b >>= 1;
    }
    return sum;
}


unsigned char GF256::pow(unsigned char a, int n)
{
    if(n <= 0)
        return a;
    for(int i = 0; i < n; i++)
    {
        a = xMult(a);
    }
    return a;
}


unsigned char GF256::xMult(unsigned char a)
{
    int temp = a;
    int p = 0x011b;
    temp <<= 1;
    if((temp >> 8) % 2)
        temp ^= p;

    return (unsigned char)temp;
}
