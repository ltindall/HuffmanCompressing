//
//  BitInputStream.cpp
//  HuffmanCompressing
//
//  Created by YICHI ZHANG on 5/1/13.
//  Copyright (c) 2013 YICHI ZHANG. All rights reserved.
//

#include "BitInputStream.hpp"

int BitInputStream::readBit()
{
    if (bufi==8)
    {
        if(in.eof())
            return -1;
        buf=in.get();
        bufi=0;
    }
    bufi++;
    int i = buf>>7;
    buf<<=1;
    return i;
    
}

int BitInputStream::readByte()
{
    if(in.eof())
        return -1;
    return in.get();
}

int BitInputStream::readInt()
{
    int i=0,temp;
    for (int j=0;j<4;j++)
    {
        if (in.eof())
            return -1;
        temp=in.get();
        temp<<=((3-j)*8);
        i|=temp;
    }
    return i;
}

bool BitInputStream::eof()
{
    return in.eof();
}