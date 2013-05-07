//
//  BitOutputStream.cpp
//  HuffmanCompressing
//
//  Created by YICHI ZHANG on 5/1/13.
//  Copyright (c) 2013 YICHI ZHANG. All rights reserved.
//

#include "BitOutputStream.hpp"

void BitOutputStream::writeBit(int bit)
{
    
    if (bufi==8)
        flush();
    buf<<=1;
    buf|=bit;
    bufi++;
#define test1
#ifndef test1
#define test1
    cout<<buf;
#endif
}

void BitOutputStream::writeByte(int b)
{
#define test2
#ifndef test2
#define test2
    cout<<b;
#endif
    out.put((unsigned char)b);
}

void BitOutputStream::writeInt(int i)
{
    for (int j=0;j<4;j++)
    {
        unsigned char tempbuf=(unsigned char)(i>>((3-j)*8));
        out.put(tempbuf);
#define test3
#ifndef test3
#define test3
        cout<<tempbuf;
#endif
    }

}

void BitOutputStream::flush()
{
    if (bufi)
    {
        buf=buf<<(8-bufi);
        out.put(buf);
        buf=bufi=0;
    }
}

