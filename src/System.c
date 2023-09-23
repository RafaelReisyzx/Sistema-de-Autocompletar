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

int max(int a, int b) {
    return (a > b) ? a : b;
}

AVLTreeNode* createAVLTreeNode(Word* word_node) {
    AVLTreeNode* newNode = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
    if (newNode != NULL) {
        newNode->word_node = word_node;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
    }
    return newNode;
}

int getHeight(AVLTreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalanceFactor(AVLTreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

AVLTreeNode* rotateRight(AVLTreeNode* y) {
    AVLTreeNode* x = y->left;
    AVLTreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLTreeNode* rotateLeft(AVLTreeNode* x) {
    AVLTreeNode* y = x->right;
    AVLTreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLTreeNode* balanceAVLTree(AVLTreeNode* node) {
    if (node == NULL) {
        return node;
    }

    int balance = getBalanceFactor(node);

    // Caso de desequilíbrio à esquerda
    if (balance > 1) {
        if (getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    // Caso de desequilíbrio à direita
    if (balance < -1) {
        if (getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

AVLTreeNode* insertIntoAVLTree(AVLTreeNode* root, Word* word_node) {
    if (root == NULL) {
        return createAVLTreeNode(word_node);
    }

    if (word_node->frequency < root->word_node->frequency) {
        root->left = insertIntoAVLTree(root->left, word_node);
    } else {
        root->right = insertIntoAVLTree(root->right, word_node);
    }

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    return balanceAVLTree(root);
}

AVLTreeNode* findMinAVLTree(AVLTreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    while (root->left != NULL) {
        root = root->left;
    }

    return root;
}

AVLTreeNode* deleteMinFromAVLTree(AVLTreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->left == NULL) {
        AVLTreeNode* rightChild = root->right;
        free(root);
        return rightChild;
    }

    root->left = deleteMinFromAVLTree(root->left);

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    return balanceAVLTree(root);
}

void printAVLTreeInOrder(AVLTreeNode* root) {
    if (root != NULL) {
        printAVLTreeInOrder(root->left);
        printf("%s %d\n", root->word_node->word, root->word_node->frequency);
        printAVLTreeInOrder(root->right);
    }
}

HuffmanTreeNode* buildHuffmanTree(Word* words[], int word_count) {
    HuffmanTreeNode* nodes[word_count];

    for (int i = 0; i < word_count; i++) {
        nodes[i] = (HuffmanTreeNode*)malloc(sizeof(HuffmanTreeNode));
        strcpy(nodes[i]->word, words[i]->word);
        nodes[i]->frequency = words[i]->frequency;
        nodes[i]->left = NULL;
        nodes[i]->right = NULL;
    }

    while (word_count > 1) {
        int min1 = 0;
        int min2 = 1;

        if (nodes[min1]->frequency > nodes[min2]->frequency) {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        for (int i = 2; i < word_count; i++) {
            if (nodes[i]->frequency < nodes[min1]->frequency) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->frequency < nodes[min2]->frequency) {
                min2 = i;
            }
        }

        HuffmanTreeNode* newNode = (HuffmanTreeNode*)malloc(sizeof(HuffmanTreeNode));
        newNode->frequency = nodes[min1]->frequency + nodes[min2]->frequency;
        newNode->left = nodes[min1];
        newNode->right = nodes[min2];

        nodes[min1] = newNode;
        nodes[min2] = nodes[word_count - 1];

        word_count--;
    }

    return nodes[0];
}

void generateHuffmanCodes(HuffmanTreeNode* root, char* code, int depth) {
    if (root->left == NULL && root->right == NULL) {
        printf("%s %d - Huffman Code: %s\n", root->word, root->frequency, code);
    }

    if (root->left != NULL) {
        code[depth] = '0';
        code[depth + 1] = '\0';
        generateHuffmanCodes(root->left, code, depth + 1);
    }

    if (root->right != NULL) {
        code[depth] = '1';
        code[depth + 1] = '\0';
        generateHuffmanCodes(root->right, code, depth + 1);
    }
}

void printHuffmanTreeInOrder(HuffmanTreeNode* root) {
    if (root != NULL) {
        printHuffmanTreeInOrder(root->left);
        printf("%s %d\n", root->word, root->frequency);
        printHuffmanTreeInOrder(root->right);
    }
}

void printBinaryTreeInOrderToFile(BinaryTreeNode* root, FILE* output_file) {
    if (root != NULL) {
        printBinaryTreeInOrderToFile(root->left, output_file);
        fprintf(output_file, "%s %d\n", root->word_node->word, root->word_node->frequency);
        printBinaryTreeInOrderToFile(root->right, output_file);
    }
}

void printAVLTreeInOrderToFile(AVLTreeNode* root, FILE* output_file) {
    if (root != NULL) {
        printAVLTreeInOrderToFile(root->left, output_file);
        fprintf(output_file, "%s %d\n", root->word_node->word, root->word_node->frequency);
        printAVLTreeInOrderToFile(root->right, output_file);
    }
}

void generateHuffmanCodesToFile(HuffmanTreeNode* root, char* code, int depth, FILE* output_file) {
    if (root->left == NULL && root->right == NULL) {
        fprintf(output_file, "%s %d - Huffman Code: %s\n", root->word, root->frequency, code);
    }

    if (root->left != NULL) {
        code[depth] = '0';
        code[depth + 1] = '\0';
        generateHuffmanCodesToFile(root->left, code, depth + 1, output_file);
    }

    if (root->right != NULL) {
        code[depth] = '1';
        code[depth + 1] = '\0';
        generateHuffmanCodesToFile(root->right, code, depth + 1, output_file);
    }
}
