//
//  HCTree.cpp
//  HuffmanCompressing
//
//  Created by YICHI ZHANG on 5/1/13.
//  Copyright (c) 2013 YICHI ZHANG. All rights reserved.
//

#include "HCTree.hpp"

HCTree::~HCTree()
{
    makeEmpty(root);
}

void HCTree::build(const vector<int>& freqs)
{
    /** build priority queue to store the HCNode forest
     */
    priority_queue<HCNode*,vector<HCNode*>,HCNodePtrComp> pq;
    for (int i=0;i<256;i++)
    {
        leaves[i]= new HCNode(freqs[i],i);
        
        pq.push(leaves[i]);
    }
    
    HCNode *n1,*n2,*nodeNew;
    
    /** build the Huffman tree
     */
    while(1)
    {
        //first get rid of the byte that is not used
        while((!pq.empty())&&(pq.top()->count)==0)
            pq.pop();
        
        
        if (pq.size()<=1)
            break;
        else{
            //add the count of the two node together to form their parent node
            n1=pq.top();
            pq.pop();
            n2=pq.top();
            pq.pop();
            nodeNew= new HCNode(n1->count+n2->count,n1->symbol,n1,n2);
            n1->p=nodeNew;
            n2->p=nodeNew;
            pq.push(nodeNew);
        }
    }
    if(pq.empty())
    {
        root=nullptr;
        cerr<<"Empty file"<<endl;
    }
    else
    root=pq.top();
}

void HCTree::writeHeader(BitOutputStream& out)
{
    byte symbolnumber=0;
    int textsize=0;
    
    //if the original file is empty don't write anything
    if(root==nullptr)
    {
        return;
        
    }
    
    else
    {
        //sum of the total bytes being used and the size of the text
        for(int i=0;i<256;i++)
        {
            if(leaves[i]->count)
            {
                symbolnumber++;
                textsize+=leaves[i]->count;
            }
            else
            {
               delete leaves[i];
                leaves[i]=nullptr;
            }
        }
        
        //write bytes number appeared in the text, byte symbol, position in the tree, and the total text size
        out.writeByte(symbolnumber);
        printLeaves(root,0,out);
        out.writeInt(textsize);
    }
}

int HCTree::readHeader(BitInputStream& in)
{
    //first read the size of the total bytes being used
    int size = in.readByte();
    
    int deepest=0;
    linkedNode* header=nullptr;
    linkedNode* ptr;
    
    //if eof reached when reading file, the file is empty
    if (size==-1)
    {
        cerr<<"Empty file"<<endl;
        return 0;
    }
    else
    {
        for (int i=0;i<size;i++)
        {
            byte symbol= in.readByte();
            int depth=in.readByte();
        
            //Use count to store the depth information of the leaf;
            HCNode * nodeNew= new HCNode(depth,symbol);
            leaves[symbol]=(nodeNew);
        
            //Use a linkedlist to store depth and symbol
            if(header==nullptr)
            {
                header=ptr = new linkedNode(nodeNew);
            }
            else
            {
                ptr->next=new linkedNode(nodeNew);
                ptr=ptr->next;
            }
            //record the deepest depth the tree has
            if(depth>deepest)
                deepest=depth;
        }
    
        //reconstruct the tree
        while(deepest)
        {
            ptr=header;
            while(ptr->next!=nullptr)
            {
            
                //replace the two deepest nodes with a new node in the linkedList, the new node has depth deepest-1
                if((ptr->node)->count==deepest)
                {
                    HCNode *nodeNew=new HCNode(deepest-1,0,ptr->node,(ptr->next)->node);
                    (ptr->node)->p=nodeNew;
                    ((ptr->next)->node)->p=nodeNew;
                    linkedNode* temp=ptr->next;
                    ptr->node=nodeNew;
                    ptr->next=(ptr->next)->next;
                    delete temp;
                }
                if(ptr->next)
                {
                ptr=ptr->next;
                }
            }
            deepest--;
        }
        root=ptr->node;
        delete ptr;
    return in.readInt();
    }
}

void HCTree::printLeaves(HCNode *&t, int depth, BitOutputStream &out) const
{
    if(t->c0!=nullptr)
    {
        printLeaves(t->c0,depth+1,out);
        printLeaves(t->c1,depth+1,out);
    }
    else
    {
        out.writeByte(t->symbol);
        out.writeByte(depth);
    }
}

void HCTree::makeEmpty (HCNode *&t) {
    if (t!=nullptr)
    {
        makeEmpty(t->c0);
        makeEmpty(t->c1);
        delete t;
    }
    t=nullptr;
}

void HCTree::encode(byte symbol,BitOutputStream& out) const
{
    if(root==nullptr)
        return;
    else
    {
        HCNode * current=leaves[symbol];
        if(current->p==nullptr)
            out.writeBit(0);
        else if ((current->p)->c0==current)
            bitEncode(current->p,false,out);
        else bitEncode(current->p,true,out);
    }
    
}

void HCTree::bitEncode(HCNode *&t,bool c1t,BitOutputStream &out) const
{
    if(t!=root)
    {
        if((t->p)->c0==t)
        {
            bitEncode(t->p,false,out);
        }
        else
            bitEncode(t->p,true,out);
    }
    out.writeBit(c1t);
}


int HCTree::decode (BitInputStream& in) const
{
    if(root==nullptr)
    {
        cerr<<"empty File"<<endl;
        return -1;
    }
    else
    {
        if (root->c0==nullptr)
        {
            in.readBit();
            return root->symbol;
        }
        else{
            HCNode* node=root;
            while(node->c0!=nullptr)
            {
                int t;
                if((t=in.readBit()))
                {
                    node=node->c1;
                }
                else node=node->c0;
            }
            return node->symbol;
        }
    }
}