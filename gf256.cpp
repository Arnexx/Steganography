#include "gf256.h"

GF256::GF256()
{
   // file.setFileName("inv.txt");
   // array.resize(256);

}

//void GF256::test()
//{

//    file.open(QIODevice::WriteOnly);
//    char temp[5];
//    int num = 0;
//    unsigned char i = 1, j = 1;
//    temp[3] = ',';
//    temp[4] = ' ';
//    array[0] = 0;
//    for(int indx = 1 ;indx <= 255; indx++)
//    {
//        for(int jndx = 0; jndx <= 255; jndx++)
//        {
//            if(array[i])
//            {
//                if(mult(i,j) == 1)
//                {
//                    array[i] = j;
//                    array[j] = i;
//                    break;
//                }
//            }
//            j++;
//        }
//        num = (array[i] + 256) % 256;
//        temp[2] = (num % 10) + 48;
//        num /= 10;
//        temp[1] = (num % 10) + 48;
//        num /= 10;
//        temp[0] = (num % 10) + 48;
//        num /= 10;
//        file.write(temp, 5);
//        i++;
//    }

//    file.close();
//}

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
