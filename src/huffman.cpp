#include "../include/huffman.h"
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"


string Huffman::HuffmanValue[256] = {""};

unsigned long long Huffman::Utility::getFileSize(const char* filename){
    FILE* fptr = fopen(filename, "rb");
    fseek(fptr, 0, SEEK_END);
    unsigned long long filesize = ftell(fptr);
    return filesize;
}

map<char, unsigned long long> Huffman::Compress::parseFile(const char* filename, unsigned long long fileSize){
    FILE* fptr = fopen(filename, "rb");
    if(fptr == NULL){
        cout << ANSI_COLOR_RED << "File Not Found!" << ANSI_COLOR_RESET << endl;
        exit(-1);
    }

    vector<unsigned long long> charCount(256, 0);
    unsigned char ch;
    unsigned long long i = 0, f_size = fileSize;

    while(i != f_size){
        ch = fgetc(fptr);
        ++charCount[ch];
        ++i;
    }

    map<char, unsigned long long> charCountMap;
    for(int j = 0; j < 256; ++j){
        if(charCount[j]) charCountMap[j] = charCount[j];
    } 

    fclose(fptr);
    return charCountMap;
}


bool sortbyCount(const Huffman::Node *a, const Huffman::Node *b) {
    return (a->count > b->count);
}
Huffman::Node* Huffman::Compress::combineNodes(Huffman::Node* a, Huffman::Node* b){
    Node *parent = new Node((a ? a->count : 0) + (b ? b->count : 0));
    parent->left = b;
    parent->right = a;
    return parent; 
}
vector<Huffman::Node*> Huffman::Compress::sortByCharCount(const map<char, unsigned long long>& charCountMap){
    vector<Node*> store;
    for(auto& i : charCountMap){
        store.push_back(new Node(i.first, i.second));
    }
    sort(store.begin(), store.end(), sortbyCount);
    return store;
}
Huffman::Node* Huffman::Compress::generateHuffmanTree(const map<char, unsigned long long>& charCountMap){
    vector<Node*> store = sortByCharCount(charCountMap);
    Node* one, *two, *parent;
    sort(store.begin(), store.end(), sortbyCount);
    
    if(store.size() == 1) return combineNodes(store.back(), nullptr);

    while(store.size() > 2){
        one = *(store.end()-1);
        two = *(store.end()-2);
        parent = (combineNodes(one, two));
        store.pop_back(); store.pop_back();
        store.push_back(parent);

        vector<Node*>::iterator iter1 = store.end()-2;
        while((*iter1)->count < parent->count && iter1 != store.begin()){
            --iter1;
        }
        sort(store.begin(), store.end(), sortbyCount);
    }
    one = *(store.end()-1);
    two = *(store.end()-2);
    return combineNodes(one, two);
}

unsigned long long Huffman::Compress::storeHuffmanValue(const Huffman::Node* root, string& buffer){
    unsigned long long temp = 0;
    if(root){
        buffer.push_back('0');
        temp = storeHuffmanValue(root->left, buffer);
        buffer.pop_back();

        if(!root->left && !root->right){
            HuffmanValue[(unsigned char)root->character] = buffer;
            temp += buffer.size() * root->count;
        }

        buffer.push_back('1');
        temp += storeHuffmanValue(root->right, buffer);
        buffer.pop_back();
    }
    return temp;
}


string Huffman::Compress::generateHeader(const char padding){
    string header = "";
    unsigned char unique = 255;

    for(int i = 0; i < 256; ++i){
        if(HuffmanValue[i].size()){
            header.push_back(i);
            header.push_back(HuffmanValue[i].size());
            header += HuffmanValue[i];
            ++unique;
        }
    }
    char value = unique;
    return value + header + (char)padding;

}

void Huffman::Compress::compressFile(const char* filename, const unsigned long long fileSize, const unsigned long long predictedFileSize){
    // calculate number of bits needed to pad the compressed data to make it a multiple of 8 bits and ensure padding value in range of 0 - 7 bits.
    const char padding = (8 - ((predictedFileSize)&(7)))&(7);
    const string header = generateHeader(padding);

    int header_i = 0;
    const int headerLen = header.size();

    FILE* inptr = fopen(filename, "rb");
    FILE* outptr = fopen((string(filename)+".tabs").c_str(), "wb");

    while(header_i < headerLen){
        fputc(header[header_i++], outptr);
    }

    unsigned char ch, fch = 0;
    char counter = 7;
    unsigned long long size = 0, i;

    while(size != fileSize){
        ch = fgetc(inptr);
        i = 0;
        const string &huffmanStr = HuffmanValue[ch];
        while(huffmanStr[i] != '\0'){
            fch = fch | ((huffmanStr[i] - '0') << counter);
            counter = (counter + 7) & 7;
            if(counter == 7){
                fputc(fch, outptr);
                fch ^= fch;
            }
            ++i;
        }
        ++size;

        if((size * 100 / fileSize) > ((size-1)*100/fileSize)){
            printf("\r%lld%% complete ", (size * 100 / fileSize));
        }
    }

    if(fch) fputc(fch, outptr);

    cout << endl;
    fclose(inptr);
    fclose(outptr);
}