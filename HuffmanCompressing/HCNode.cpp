//
//  HCNode.cpp
//  HuffmanCompressing
//
//  Created by YICHI ZHANG on 5/1/13.
//  Copyright (c) 2013 YICHI ZHANG. All rights reserved.
//

#include "HCNode.hpp"
/** less-than comparator returns true if
 *  count of this node is less than that of other node
 *  or counts are equal but the symbol of this node is less than other node
 */
bool HCNode::operator<(const HCNode& other)
{
    if (count<other.count)
        return true;
    else if (count==other.count)
    {
        
        if (symbol<other.symbol)
            return true;
        else return false;
    }
    else return false;
}

bool comp(HCNode* one, HCNode* other)
{
    return one<other;
}