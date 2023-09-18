#include <stdio.h>
#include "System.h"

int main() {
    HashTable hash_table;
    int k = 20;
    initializeHashTable(&hash_table);
    loadStopWords(&hash_table, "dataset/stopwords.txt");
    processFile(&hash_table, "dataset/filosofia.txt");

    BinaryTreeNode* binaryTreeRoot = NULL;
    AVLTreeNode* avlTreeRoot = NULL;
    HuffmanTreeNode* huffmanTreeRoot = NULL;
    int treeSize = 0;

    Word* frequent_words[k];

    for (int i = 0; i < TABLE_SIZE; i++) {
        Word* palavra_atual = hash_table.table[i];
        while (palavra_atual != NULL) {
            if (palavra_atual->frequency > 0) {
                frequent_words[treeSize] = palavra_atual;
                binaryTreeRoot = insertIntoBinaryTree(binaryTreeRoot, palavra_atual);
                avlTreeRoot = insertIntoAVLTree(avlTreeRoot, palavra_atual);
                treeSize++;
                if (treeSize > k) {
                    binaryTreeRoot = deleteMinFromBinaryTree(binaryTreeRoot);
                    avlTreeRoot = deleteMinFromAVLTree(avlTreeRoot);
                    treeSize--;
                }
            }
            palavra_atual = palavra_atual->next;
        }
    }

    huffmanTreeRoot = buildHuffmanTree(frequent_words, k);
    char huffmanCode[MAX_WORD_LENGTH];
    huffmanCode[0] = '\0';


    printf("Top %d palavras mais frequentes (Árvore Binária):\n", k);
    printBinaryTreeInOrder(binaryTreeRoot);

    printf("\nTop %d palavras mais frequentes (Árvore AVL):\n", k);
    printAVLTreeInOrder(avlTreeRoot);
    printf("\nÁrvore de Huffman:\n");
   // printHuffmanTreeInOrder(huffmanTreeRoot);
 generateHuffmanCodes(huffmanTreeRoot, huffmanCode, 0);
    return 0;
}
