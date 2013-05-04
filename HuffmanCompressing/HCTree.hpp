#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <queue>
#include <vector>
#include <algorithm>
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;

/** A 'function class' for use as the Compare class in a
 *  priority_queue<HCNode*>.
 *  For this to work, operator< must be defined to
 *  do the right thing on HCNodes.
 */
class HCNodePtrComp {
public:
    bool operator()(HCNode*& lhs, HCNode*& rhs) const {
        return *lhs < *rhs;
    }
};

/** A Huffman Code Tree class.
 *  Not very generic:  Use only if alphabet consists
 *  of unsigned chars.
 */
class HCTree {
private:
    HCNode* root;
    vector<HCNode*> leaves;

public:
    explicit HCTree() : root(0) {
        leaves = vector<HCNode*>(256, (HCNode*) 0);
    }

    ~HCTree();

    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void build(const vector<int>& freqs);

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void encode(byte symbol, BitOutputStream& out) const;

    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    int decode(BitInputStream& in) const;
    
    /** Compress the Huffman tree and write the header
     *  The first byte of the header record number of symbols appeared in the text
     *  Next is an array recording the appeared symbol in the order of
     *  left-to-right as it appeared in the Huffman tree
     *  (assuming 0 is always the left edge)
     *  The last array records the depth of each leaves in the order
     *  from left-to-right (same as the second array)
     *  it takes 2m(all the symbols appeared in the text)+1 bytes to write
     *  a header
     */
    void writeHeader(BitOutputStream& out);
    
    /** reconstruct the Huffman tree for decoding
     *  return the size of the text
     */
    int readHeader(BitInputStream & in);
    
private:    
    /** Recursively print out the leaves from the left to right
     */
    void printLeaves(HCNode *&t,int depth, BitOutputStream &out) const;
    
    /** Clear the whole tree
     */
    void makeEmpty(HCNode *&t);
    
    
    /** Recursively search for the root from the leaf and encode the byte from
     *  the root
     *  if t is the 0child of its parent, set c1t false
     *  otherwise set true
     */
    void bitEncode(HCNode *&t,bool c1t,BitOutputStream& out) const;
    
};


/** define a linkedList to store every leaf for the reconstruction of
 *  the Huffman tree
 */
class linkedNode
{
public:
    HCNode* node;
    linkedNode* next;
    linkedNode(HCNode* node):node(node),next(nullptr){};
};

#endif // HCTREE_HPP
