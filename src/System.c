#include "System.h"
void initializeHashTable(HashTable* hash_table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table->table[i] = NULL;
    }
}

void loadStopWords(HashTable* hash_table, const char* stop_words_file) {
    FILE* file = fopen(stop_words_file, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de stopwords.\n");
        exit(1);
    }

    char word[MAX_WORD_LENGTH];
    while (fgets(word, MAX_WORD_LENGTH, file)) {
        word[strcspn(word, "\r\n")] = '\0'; 
        unsigned long hash = hashFunction(word);
        Word* new_word = createWordNode(word);
        new_word->frequency = -1; 
        new_word->next = hash_table->table[hash];
        hash_table->table[hash] = new_word;
    }

    fclose(file);
}

unsigned long hashFunction(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % TABLE_SIZE;
}

Word* createWordNode(const char* word) {
    Word* new_word = (Word*)malloc(sizeof(Word));
    if (new_word != NULL) {
        strcpy(new_word->word, word);
        new_word->frequency = 1;
        new_word->next = NULL;
    }
    return new_word;
}

void processFile(HashTable* hash_table, const char* input_file) {
    FILE* file = fopen(input_file, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        exit(1);
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF) {
        word[strcspn(word, ".,!?;-—/\()")] = '\0'; 
        for (int i = 0; word[i]; i++) {
            word[i] = tolower(word[i]); 
        }

        if (strlen(word) > 0) {
            unsigned long hash = hashFunction(word);
            Word* palavra_atual = hash_table->table[hash];
            Word* palavra_anterior = NULL;

            while (palavra_atual != NULL) {
                if (strcmp(palavra_atual->word, word) == 0) {
                    if (palavra_atual->frequency > 0) {
                        palavra_atual->frequency++;
                    }
                    break;
                }
                palavra_anterior = palavra_atual;
                palavra_atual = palavra_atual->next;
            }

            if (palavra_atual == NULL) {
                Word* new_word = createWordNode(word);
                if (new_word != NULL) {
                    if (palavra_anterior == NULL) {
                        hash_table->table[hash] = new_word;
                    } else {
                        palavra_anterior->next = new_word;
                    }
                }
            }
        }
    }

    fclose(file);
}

BinaryTreeNode* insertIntoBinaryTree(BinaryTreeNode* root, Word* word_node) {
    if (root == NULL) {
        BinaryTreeNode* newNode = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
        newNode->word_node = word_node;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (word_node->frequency < root->word_node->frequency) {
        root->left = insertIntoBinaryTree(root->left, word_node);
    } else {
        root->right = insertIntoBinaryTree(root->right, word_node);
    }

    return root;
}

BinaryTreeNode* findMinBinaryTree(BinaryTreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    while (root->left != NULL) {
        root = root->left;
    }

    return root;
}

BinaryTreeNode* deleteMinFromBinaryTree(BinaryTreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->left == NULL) {
        BinaryTreeNode* rightChild = root->right;
        free(root);
        return rightChild;
    }

    root->left = deleteMinFromBinaryTree(root->left);
    return root;
}

void printBinaryTreeInOrder(BinaryTreeNode* root) {
    if (root != NULL) {
        printBinaryTreeInOrder(root->left);
        printf("%s %d\n", root->word_node->word, root->word_node->frequency);
        printBinaryTreeInOrder(root->right);
    }
}
