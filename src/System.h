#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#ifndef SYSTEM_H
#define SYSTEM_H

#define TABLE_SIZE 300000
#define MAX_WORD_LENGTH 50
#define k 20

typedef struct Word {
    char word[MAX_WORD_LENGTH];
    int frequency;
    struct Word* next;
} Word;

typedef struct HashTable {
    Word* table[TABLE_SIZE];
} HashTable;

typedef struct BinaryTreeNode {
    Word* word_node;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
} BinaryTreeNode;

typedef struct AVLTreeNode {
    Word* word_node;
    struct AVLTreeNode* left;
    struct AVLTreeNode* right;
    int height;
} AVLTreeNode;

typedef struct HuffmanTreeNode {
    char word[MAX_WORD_LENGTH];
    int frequency;
    struct HuffmanTreeNode* left;
    struct HuffmanTreeNode* right;
} HuffmanTreeNode;

HuffmanTreeNode* buildHuffmanTree(Word* words[], int word_count);
void generateHuffmanCodes(HuffmanTreeNode* root, char* code, int depth);
void printHuffmanTreeInOrder(HuffmanTreeNode* root);
AVLTreeNode* insertIntoAVLTree(AVLTreeNode* root, Word* word_node);
AVLTreeNode* deleteMinFromAVLTree(AVLTreeNode* root);
int getHeight(AVLTreeNode* node);
int getBalanceFactor(AVLTreeNode* node);
AVLTreeNode* rotateRight(AVLTreeNode* y);
AVLTreeNode* rotateLeft(AVLTreeNode* x);
AVLTreeNode* balanceAVLTree(AVLTreeNode* node);
void printAVLTreeInOrder(AVLTreeNode* root);
void initializeHashTable(HashTable* hash_table);
void loadStopWords(HashTable* hash_table, const char* stop_words_file);
unsigned long hashFunction(const char* str);
Word* createWordNode(const char* word);
void processFile(HashTable* hash_table, const char* input_file);
BinaryTreeNode* insertIntoBinaryTree(BinaryTreeNode* root, Word* word_node);
BinaryTreeNode* deleteMinFromBinaryTree(BinaryTreeNode* root);
void printBinaryTreeInOrder(BinaryTreeNode* root);
Word* findWord(HashTable* hash_table, const char* word);



#endif
