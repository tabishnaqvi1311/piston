#include <iostream>
#include "../include/display.h"
#include "../include/huffman.h"
using namespace std;

int main(int argc, char *argv[]){

    if(argc != 3) {
        Display::Help();
        exit(-1);
    }

    const char* option = argv[1];
    const char* filename = argv[2];
    long long fileSize, predictedFileSize;

    if(string(option) == "-a" || string(option) == "-archive"){
        fileSize = Huffman::Utility::getFileSize(filename);
        auto charCountMap = Huffman::Compress::parseFile(filename, fileSize);
        Huffman::Node* const root = Huffman::Compress::generateHuffmanTree(charCountMap);

        string buffer = "";
        predictedFileSize = Huffman::Compress::storeHuffmanValue(root, buffer);

        printf("original file size: %lld bytes\n", fileSize);
        // round up to nearest whole amount of bytes and divide by 8;
        printf("compressed file size: %lld bytes\n", (predictedFileSize+7)>>3);

        Huffman::Compress::compressFile(filename, fileSize, predictedFileSize);

        cout << "compression complete";
    }
    else if(string(option) == "-x" || string(option) == "-unarchive"){
        fileSize = Huffman::Utility::getFileSize(filename);
        Huffman::Decompress::decompress(filename, fileSize, predictedFileSize);   
    }
    else if(string(option) == "-h" || string(option) == "-help"){
        Display::Help();
        exit(-1);
    }
    else {
        cout << "Bad option :(" <<  endl << "Check usage with -h flag";
    }

    return 0;
}