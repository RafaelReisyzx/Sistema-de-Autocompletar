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
    HuffmanNode* huffmanTreeRoot = NULL;
    int treeSize = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        Word* palavra_atual = hash_table.table[i];
        while (palavra_atual != NULL) {
            if (palavra_atual->frequency > 0) {
                binaryTreeRoot = insertIntoBinaryTree(binaryTreeRoot, palavra_atual);
                avlTreeRoot = insertIntoAVLTree(avlTreeRoot, palavra_atual);
                huffmanTreeRoot = insertIntoHuffmanTree(huffmanTreeRoot, palavra_atual); // Adicione a palavra à árvore de Huffman
                treeSize++;
                if (treeSize > k) {
                    binaryTreeRoot = deleteMinFromBinaryTree(binaryTreeRoot);
                    avlTreeRoot = deleteMinFromAVLTree(avlTreeRoot);
                    huffmanTreeRoot = deleteMinFromHuffmanTree(huffmanTreeRoot); // Remova a palavra da árvore de Huffman
                    treeSize--;
                }
            }
            palavra_atual = palavra_atual->next;
        }
    }

    printf("Top %d palavras mais frequentes (Árvore Binária):\n", k);
    printBinaryTreeInOrder(binaryTreeRoot);

    printf("\nTop %d palavras mais frequentes (Árvore AVL):\n", k);
    printAVLTreeInOrder(avlTreeRoot);

    printf("\nTop %d palavras mais frequentes (Árvore de Huffman):\n", k);
    printHuffmanTreeInOrder(huffmanTreeRoot); 

    destroyHuffmanTree(huffmanTreeRoot); 

    return 0;
}
