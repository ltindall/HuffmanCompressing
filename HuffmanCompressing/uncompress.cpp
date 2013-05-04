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
    infile.open(argv[1],ios_base::binary);
    if(! infile.good() )
        cerr<<"Can't open input file!"<<endl;
    BitInputStream in(infile);
    
    outfile.open(argv[2],ios_base::binary);
    if(! outfile.good() )
        cerr<<"Can't open output file!"<<endl;
    BitOutputStream out(outfile);
    
    HCTree tree;
    
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
