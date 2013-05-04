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

int main(int argc, char * argv[])
{
    

    ifstream infile;
    ofstream outfile;
    vector<int> freqs(256,0);
    HCTree tree;
    
    infile.open(argv[1],ios_base::binary);
    if(! infile.good() )
        cerr<<"Can't open input file!"<<endl;
    BitInputStream in(infile);
    
    /** First read in the file and count the freq of every byte
     */
    unsigned char temp;
    while(1)
    {
        temp=in.readByte();
        if(in.eof())
            break;
        freqs[temp]++;
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
    //build tree;
    tree.build(freqs);
    
    outfile.open(argv[2],ios_base::binary);
    BitOutputStream out(outfile);
    
    if(! outfile.good() )
        cerr<<"Can't open output file!"<<endl;
    
    //write header to target file
    tree.writeHeader(out);
    
    //reopen input file, and encode the byte, write to the target file the encoded bits
    infile.open(argv[1],ios_base::binary);
    while(1)
    {
        temp = in.readByte();
        if(in.eof())
            break;
        tree.encode(temp,out);
    }
    //flush the last bit buffer
    out.flush();
    infile.close();
    outfile.close();
    
    
}
