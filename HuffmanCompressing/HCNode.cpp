//
//  HCNode.cpp
//  HuffmanCompressing
//
//  Created by YICHI ZHANG on 5/1/13.
//  Copyright (c) 2013 YICHI ZHANG. All rights reserved.
//

#include "HCNode.hpp"
/** less-than comparator compares priority
 *  smaller counts have higher priority
 *  if counts are equal, use symbol to break tie
 */
bool HCNode::operator<(const HCNode& other)
{
    if (count!=other.count) return count>other.count;
    return symbol<other.symbol;
}

bool comp(HCNode* one, HCNode* other)
{
    return one<other;
}