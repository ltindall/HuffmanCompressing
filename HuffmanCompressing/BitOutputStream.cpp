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
    buf|=bit;
    buf<<=1;
    bufi++;
}

void BitOutputStream::writeByte(int b)
{
    out.put((char)b);
}

void BitOutputStream::writeInt(int i)
{
    for (int j=0;j<4;j++)
    {
        char tempbuf=(char)(i>>((3-j)*8));
        out.put(tempbuf);
    }
}

void BitOutputStream::flush()
{
    if (buf)
    {
        out.put(buf);
        buf=bufi=0;
    }
}

