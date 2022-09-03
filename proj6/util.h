// Filename: util.h
// included in main.c
// Created by: Shanon Reckinger
// Modified by: Haoji Ni
// University of Illinois at Chicago
// CS 251: Spring 2022
// 2022/04/02

#include <fstream>
#include <functional>  // std::greater
#include <iostream>
#include <map>
#include <queue>  // std::priority_queue
#include <string>
#include <vector>  // std::vector

#include "bitstream.h"
#include "hashmap.h"
#include "mymap.h"
#pragma once

// tree structure
struct HuffmanNode {
    int character;
    int count;
    HuffmanNode* zero;
    HuffmanNode* one;
};

// class for priority queue
// compare lhs and rhs based on count
class prioritize {
public:
    bool operator()(HuffmanNode*& lhs, HuffmanNode*& rhs) {
        return lhs->count > rhs->count;
    }
};

// *This method frees the memory allocated for the Huffman tree.
// use past order to free the memory
void freeTree(HuffmanNode* node) {
    // if null, return
    if (node == nullptr) {
        return;
    }
    // call function recursively
    freeTree(node->zero);
    freeTree(node->one);
    delete node;
}

// This is a helper function for buildHuffmanTree
// It will put chars into hashmap
void put_chars(char c, hashmap& map) {
    // if contain, add 1
    if (map.containsKey(int(c))) {
        // update count
        map.put(int(c), map.get(c) + 1);
    } else {
        // if not contain, put 1
        map.put(int(c), 1);
    }
}

// *This function build the frequency map.  If isFile is true, then it reads
// from filename.  If isFile is false, then it reads from a string filename.
void buildFrequencyMap(string filename, bool isFile, hashmap& map) {
    // if is a file, open it and read it
    if (isFile) {
        ifstream inFS(filename);
        char c;
        while (inFS.get(c)) {
            put_chars(c, map);
        }
        inFS.close();
    } else {
        // if not a file, read from string
        for (char c : filename) {
            put_chars(c, map);
        }
    }
    // add eof to map
    map.put(256, 1);
}

// *This function builds an encoding tree from the frequency map.
HuffmanNode* buildEncodingTree(hashmap& map) {
    // create a priority queue and push all the nodes into it
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, prioritize> pq;
    // create a vector of all the keys
    vector<int> keys = map.keys();
    // for range loop, this will push back node into priority queue
    for (int i : keys) {
        HuffmanNode* node = new HuffmanNode();
        node->character = i;
        node->count = map.get(i);
        node->zero = nullptr;
        node->one = nullptr;
        pq.push(node);
    }
    // build huffman tree
    while (pq.size() > 1) {
        // pop two nodes and save them
        HuffmanNode* first_node = pq.top();
        pq.pop();
        HuffmanNode* second_node = pq.top();
        pq.pop();
        // create a new node
        HuffmanNode* linked_node = new HuffmanNode();
        // 257 stands for not a character
        linked_node->character = 257;
        // add count and link the nodes
        linked_node->count = first_node->count + second_node->count;
        linked_node->zero = first_node;
        linked_node->one = second_node;
        // push the new node into the queue
        pq.push(linked_node);
    }
    return pq.top();
}

// This is a helper function for buildEncodingMap
// it will call itself recursively to build the encoding map
void build_encoding_map(HuffmanNode* node, string code,
                        mymap<int, string>& map) {
    // instead of using pass by reference, update value in function
    // would be a better way to do this
    // if go to zero, add 0 to code
    if (node->zero != nullptr) {
        build_encoding_map(node->zero, code + "0", map);
    }
    // otherwise, add 1 to code
    if (node->one != nullptr) {
        build_encoding_map(node->one, code + "1", map);
    }
    // if reach a leaf node, add to map
    if (node->character != 257) {
        map.put(node->character, code);
    }
}

// *This function builds the encoding map from an encoding tree.
mymap<int, string> buildEncodingMap(HuffmanNode* tree) {
    // initialize variables
    mymap<int, string> encodingMap;
    string code = "";
    HuffmanNode* node = tree;
    // call helper function
    build_encoding_map(node, code, encodingMap);
    return encodingMap;
}

// *This function encodes the data in the input stream into the output stream
// using the encodingMap.  This function calculates the number of bits
// written to the output stream and sets result to the size parameter, which is
// passed by reference.  This function also returns a string representation of
// the output file, which is particularly useful for testing.
string encode(ifstream& input, mymap<int, string>& encodingMap,
              ofbitstream& output, int& size, bool makeFile) {
    // initialize variables
    string result = "";
    char c;
    while (input.get(c)) {
        // update string and size
        result += encodingMap.get(int(c));
        size += encodingMap.get(int(c)).size();
    }
    // add eof at the end of string
    result += encodingMap.get(256);
    size += encodingMap.get(256).size();
    // check make file flag
    if (makeFile) {
        // convert chars to ints, this cause me a lot of trouble
        for (char c : result) {
            output.writeBit(c == '0' ? 0 : 1);
        }
    }
    return result;
}

//
// *This function decodes the input stream and writes the result to the output
// stream using the encodingTree.  This function also returns a string
// representation of the output file, which is particularly useful for testing.
//
string decode(ifbitstream& input, HuffmanNode* encodingTree, ofstream& output) {
    // initialize variables
    string result = "";
    HuffmanNode* node = encodingTree;
    // while not eof, read chars from input
    while (!input.eof()) {
        // if reach a leaf node, add to result
        if (node->character != 257) {
            // if is eof, don't add anything
            // and reset node to root
            if (node->character == 256) {
                return result;
            } else {
                // if is other than eof, add to result and output
                // and reset node to root
                output.put(char(node->character));
                result += char(node->character);
                node = encodingTree;
            }
        }
        // if is not a leaf node, read bit from input
        // and traverse the tree
        int bit = input.readBit();
        if (bit == 0) {
            node = node->zero;
        } else {
            node = node->one;
        }
    }
    return result;
}

// *This function completes the entire compression process.  Given a file,
// filename, this function (1) builds a frequency map; (2) builds an encoding
// tree; (3) builds an encoding map; (4) encodes the file (don't forget to
// include the frequency map in the header of the output file).  This function
// should create a compressed file named (filename + ".huf") and should also
// return a string version of the bit pattern.
string compress(string filename) {
    // initialize variables and call functions
    int size = 0;
    hashmap freq_map;
    buildFrequencyMap(filename,true,freq_map);
    HuffmanNode* encodingTree = buildEncodingTree(freq_map);
    mymap<int, string> encode_map = buildEncodingMap(encodingTree);

    // create encoded file
    ofbitstream output(filename + ".huf");
    // import freq_map for decoding
    output << freq_map;
    // open input file for encoding
    ifstream input(filename);

    // encode file
    string result = encode(input, encode_map, output, size, true);

    // close everything, free memory
    input.close();
    output.close();
    freeTree(encodingTree);
    return result;
}

// *This function completes the entire decompression process.  Given the file,
// filename (which should end with ".huf"), (1) extract the header and build
// the frequency map; (2) build an encoding tree from the frequency map; (3)
// using the encoding tree to decode the file.  This function should create a
// compressed file using the following convention.
// If filename = "example.txt.huf", then the uncompressed file should be named
// "example_unc.txt".  The function should return a string version of the
// uncompressed file.  Note: this function should reverse what the compress
// function did.
string decompress(string filename) {
    // initialize variables, input, and output
    hashmap freq_map;
    ifbitstream input(filename);
    ofstream output(filename.substr(0,filename.size()-8) + "_unc.txt");

    // get frequency map and build encoding tree
    input >> freq_map;
    HuffmanNode* encodingTree = buildEncodingTree(freq_map);

    // decode file
    string result = decode(input, encodingTree, output);

    // close everything, free memory
    input.close();
    output.close();
    freeTree(encodingTree);
    return result;
}
