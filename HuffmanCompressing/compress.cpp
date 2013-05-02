//
//  compress.cpp
//  HuffmanCompressing
//
//  Created by YICHI ZHANG on 5/1/13.
//  Copyright (c) 2013 YICHI ZHANG. All rights reserved.
//

#include "HcTree.hpp"
#include <fstream>
#include <iomanip>
using namespace std;
vector<int> freqs(256,0);

int main(int argc, char * argv[])
{
/** First read in the file and count the freq of every byte
 */
    ifstream infile;
    infile.open(argv[1],ios_base::binary);
    BitInputStream in(infile);
    while(!in.eof())
    {
        unsigned char temp = in.readByte();
        for(int i=0;i<256;i++)
        {
            if (temp==i)
                freqs[i]++;
        }
    }
    infile.close();
    
#ifndef testinput
#define testinput
    for (int i=0;i<256;i++)
    {
        cout<<setw(6)<<i<<": "<<setw(6)<<freqs[i];
        if (i%4==3)
            cout<<endl;
    }
#endif
    
    
}
