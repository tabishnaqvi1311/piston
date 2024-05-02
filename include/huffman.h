#pragma once
#include <string>
#include <map>
using namespace std;

namespace Huffman {
    extern string HuffmanValue[256];

    struct Node {
        char character;
        long long count;
        Node* left;
        Node* right;

        Node(long long count){
            this->character = 0;
            this->count = count;
            this->left = this->right = nullptr;
        }

        Node(char character, long long count){
            this->character = character;
            this->count = count;
            this->left = this->right = nullptr;
        }
    };

    namespace Utility{
        unsigned long long getFileSize(const char* filename);

        // void inorderTraversal(Node* root, string value);
    }

    namespace Compress{
        map<char, unsigned long long> parseFile(const char* filename, unsigned long long fileSize);
        Node* combineNodes(Node* a, Node* b);
        vector<Node*> sortByCharCount(const map<char, unsigned long long>& charCountMap);
        Node* generateHuffmanTree(const map<char, unsigned long long>& charCountMap);
        unsigned long long storeHuffmanValue(const Node* root, string& buffer);
        string generateHeader(const char padding);
        void compressFile(const char* filename, const unsigned long long fileSize, const unsigned long long predictedFileSize);
    }
}