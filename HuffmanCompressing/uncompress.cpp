//
//  uncompress.cpp
//  HuffmanUncompressing
//
//  Created by YICHI ZHANG on 5/3/13.
//  Copyright (c) 2013 YICHI ZHANG. All rights reserved.
//

#include "HCTree.hpp"
#include <fstream>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[])
{
    ifstream infile;
    ofstream outfile;
    outfile.open(argv[2],ios_base::binary);
    BitOutputStream out(outfile);
    HCTree tree;
    infile.open(argv[1],ios_base::binary);
    BitInputStream in(infile);
        
    //first read the header
    int textsize=tree.readHeader(in);
    for (int i=0;i<textsize;i++)
    {
        byte temp=tree.decode(in);
        if (temp==-1)
            return 0;
        out.writeByte(temp);
    }
}
