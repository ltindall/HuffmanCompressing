//
//  compress.cpp
//  HuffmanCompressing
//
//  Created by YICHI ZHANG on 5/1/13.
//  Copyright (c) 2013 YICHI ZHANG. All rights reserved.
//

#include "HCTree.hpp"
#include <fstream>
#include <iomanip>
using namespace std;
vector<int> freqs(256,0);

int main(int argc, char * argv[])
{
/** First read in the file and count the freq of every byte
 */
    ifstream infile;
    ofstream outfile;
    infile.open(argv[1],ios_base::binary);
    BitInputStream in(infile);
    unsigned char temp;
    while(!in.eof())
    {
        temp=in.readByte();
        for(int i=0;i<256;i++)
        {
            if (temp==i)
                freqs[i]++;
        }
    }
    infile.close();
#define testinput
#ifndef testinput
#define testinput
    for (int i=0;i<256;i++)
    {
        cout<<setw(6)<<i<<": "<<setw(6)<<freqs[i];
        if (i%4==3)
            cout<<endl;
    }
#endif

    HCTree tree;
    tree.build(freqs);
    
    outfile.open(argv[2],ios_base::binary);
    BitOutputStream out(outfile);
    tree.writeHeader(out);
    infile.open(argv[1],ios_base::binary);
    while(!in.eof())
    {
        tree.encode(in.readByte(),out);
    }
    //flush the Bit buffer
    out.flush();
    infile.close();
    outfile.close();
    
    
}
