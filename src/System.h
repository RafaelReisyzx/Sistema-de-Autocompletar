#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#ifndef SYSTEM_H
#define SYSTEM_H

#define TABLE_SIZE 300000
#define MAX_WORD_LENGTH 50

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

void initializeHashTable(HashTable* hash_table);
void loadStopWords(HashTable* hash_table, const char* stop_words_file);
unsigned long hashFunction(const char* str);
Word* createWordNode(const char* word);
void processFile(HashTable* hash_table, const char* input_file);
BinaryTreeNode* insertIntoBinaryTree(BinaryTreeNode* root, Word* word_node);
BinaryTreeNode* deleteMinFromBinaryTree(BinaryTreeNode* root);
void printBinaryTreeInOrder(BinaryTreeNode* root);



#endif
