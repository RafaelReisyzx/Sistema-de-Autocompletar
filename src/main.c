#include <stdio.h>
#include "System.h"

int main() {
    HashTable hash_table;
    int k = 20;
    initializeHashTable(&hash_table);
    loadStopWords(&hash_table, "dataset/stopwords.txt");
    processFile(&hash_table, "dataset/filosofia.txt");
    
    BinaryTreeNode* root = NULL;
    int treeSize = 0;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        Word* palavra_atual = hash_table.table[i];
        while (palavra_atual != NULL) {
            if (palavra_atual->frequency > 0) {
                root = insertIntoBinaryTree(root, palavra_atual);
                treeSize++;
                if (treeSize > k) {
                    root = deleteMinFromBinaryTree(root);
                    treeSize--;
                }
            }
            palavra_atual = palavra_atual->next;
        }
    }

    printf("Top %d palavras mais frequentes:\n", k);
    printBinaryTreeInOrder(root);
    
    return 0;
}
