#include <stdio.h>
#include "System.h"

int main() {
    const char* input_files[] = {
        "dataset/filosofia.txt",
        "dataset/filosofia2.txt",
        "dataset/globalizacao.txt",
        "dataset/politica.txt",
        "dataset/ti.txt",
        "dataset/ti2.txt"
    };

    int k = 20;
    FILE* output_file = fopen("dataset/output.data", "w");
    if (output_file == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 1;
    }

    for (int file_index = 0; file_index < 6; file_index++) {
        HashTable hash_table;
        initializeHashTable(&hash_table);
        loadStopWords(&hash_table, "dataset/stopwords.data");
        processFile(&hash_table, input_files[file_index]);

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
        fprintf(output_file, "Arquivo: %s\n", input_files[file_index]);
        fprintf(output_file, "Top %d palavras mais frequentes (Árvore Binária):\n", k);
        printBinaryTreeInOrderToFile(binaryTreeRoot, output_file);

        fprintf(output_file, "\nTop %d palavras mais frequentes (Árvore AVL):\n", k);
        printAVLTreeInOrderToFile(avlTreeRoot, output_file);

        fprintf(output_file, "\nÁrvore de Huffman:\n");
        generateHuffmanCodesToFile(huffmanTreeRoot, huffmanCode, 0, output_file);
        fprintf(output_file, "\n==============================\n");
    }

    fclose(output_file);

    return 0;
}
