
# Descrição do algoritmo


# Regras Propostas

Neste trabalho, o objetivo é criar um sistema que possibilite a funcionalidade de autocompletar
e oferecer sugestões de palavras aos usuários. Para atingir essa finalidade, adotaremos a
estrutura da árvore binária como base. A seguir, é apresentado os passos necessários para a
implementação.
- Passo 1: Coleta de Dados
Iniciamos solicitando ao usuário um arquivo denominado input.data, contendo uma lista de
palavras. Cada palavra nesse arquivo será considerada como termo de pesquisa para o sistema.
- Passo 2: Modelo de Dados - Árvores Binárias
Utilizaremos um conjunto de árvores binárias para construir nosso sistema. Essas árvores
serão criadas a partir de textos previamente fornecidos (disponíveis em textos.zip). O objetivo
é estabelecer uma relação entre as palavras dos textos e as palavras de pesquisa.
- Passo 3: Sugestões de Palavras Relevantes
Para cada palavra no arquivo input.data, percorreremos as árvores binárias para identificar as
palavras mais relevantes e próximas à palavra de pesquisa. Priorizaremos palavras frequentes
e associadas ao termo de pesquisa.
- Passo 4: Resultados e Análises
Os resultados da análise serão apresentados em um arquivo chamado output.data. Esse arquivo conterá as relações entre as palavras pesquisadas e cada arquivo de texto. Além disso,
a relevância de cada palavra será calculada com base em sua frequência nos textos. Para tal,
utilize o trabalho recentemente realizado, o contador de palavras.
** Abordagem de Implementação **
A abordagem consistirá em três etapas diferentes:
1. **Árvore Binária Padrão**: Implementaremos uma árvore binária tradicional, selecionando as palavras mais relevantes e relacionadas à pesquisa em cada texto. A relevância de uma palavra será determinada por sua frequência e proximidade à palavra de
pesquisa.
2. **Codificação de Huffman**: Exploraremos o uso do código de Huffman para otimizar
a árvore binária padrão. Calcularemos códigos para cada palavra e reorganizaremos a
estrutura da árvore com base nesses códigos. Avaliaremos se essa abordagem oferece
vantagens em relação à anterior.
3. **Árvore AVL**: Implementaremos uma árvore AVL e repetiremos o processo de análise.
Compararemos o tempo médio de processamento entre a construção da estrutura e a
geração de saída em comparação com as abordagens anteriores.


Ao concluir esta tarefa, teremos uma compreensão mais aprofundada das diferentes implementações das árvores binárias e sua influência no sistema de autocompletar e sugestões de
palavras. A análise comparativa nos permitirá avaliar a eficácia de cada abordagem em termos
de desempenho e funcionalidade.


# Funções 

1.initializeHashTable(HashTable* hash_table)
```
void initializeHashTable(HashTable* hash_table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table->table[i] = NULL;
    }
}
```
2.loadStopWords(HashTable* hash_table, const char* stop_words_file)
```
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
```
3.hashFunction(const char* str)
```
unsigned long hashFunction(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % TABLE_SIZE;
}
```
4.createWordNode(const char* word)
```
Word* createWordNode(const char* word) {
    Word* new_word = (Word*)malloc(sizeof(Word));
    if (new_word != NULL) {
        strcpy(new_word->word, word);
        new_word->frequency = 1;
        new_word->next = NULL;
    }
    return new_word;
}
```
5.processFile(HashTable* hash_table, const char* input_file)
```
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
```
6.insertIntoBinaryTree(BinaryTreeNode* root, Word* word_node)
```
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
```
7.findMinBinaryTree(BinaryTreeNode* root)
```
BinaryTreeNode* findMinBinaryTree(BinaryTreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    while (root->left != NULL) {
        root = root->left;
    }

    return root;
}
```
8.deleteMinFromBinaryTree(BinaryTreeNode* root)
```
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
```
9.printBinaryTreeInOrder(BinaryTreeNode* root)
```
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
```
10.createAVLTreeNode(Word* word_node)
```
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
```
11. getHeight(AVLTreeNode* node)
```
int getHeight(AVLTreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}
```
12.getBalanceFactor(AVLTreeNode* node)
```
int getBalanceFactor(AVLTreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}
```
13.rotateRight(AVLTreeNode* y)
```
AVLTreeNode* rotateRight(AVLTreeNode* y) {
    AVLTreeNode* x = y->left;
    AVLTreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}
```
14.rotateLeft(AVLTreeNode* x)
```
AVLTreeNode* rotateLeft(AVLTreeNode* x) {
    AVLTreeNode* y = x->right;
    AVLTreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}
```
15.balanceAVLTree(AVLTreeNode* node)
```
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
```
16.insertIntoAVLTree(AVLTreeNode* root, Word* word_node)
```
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
```
17.findMinAVLTree(AVLTreeNode* root)
```
    AVLTreeNode* findMinAVLTree(AVLTreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    while (root->left != NULL) {
        root = root->left;
    }

    return root;

```
18.deleteMinFromAVLTree(AVLTreeNode* root)
```
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
```
19.printAVLTreeInOrder(AVLTreeNode* root)
```
void printAVLTreeInOrder(AVLTreeNode* root) {
    if (root != NULL) {
        printAVLTreeInOrder(root->left);
        printf("%s %d\n", root->word_node->word, root->word_node->frequency);
        printAVLTreeInOrder(root->right);
    }

```
20.createHuffmanNode(Word* word_node)
```
HuffmanNode* createHuffmanNode(Word* word_node) {
    HuffmanNode* newNode = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    if (newNode != NULL) {
        newNode->word_node = word_node;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}
```
21.insertIntoHuffmanTree(HuffmanNode* root, Word* word_node)
```
HuffmanNode* insertIntoHuffmanTree(HuffmanNode* root, Word* word_node) {
    if (root == NULL) {
        return createHuffmanNode(word_node);
    }

    if (word_node->frequency < root->word_node->frequency) {
        root->left = insertIntoHuffmanTree(root->left, word_node);
    } else {
        root->right = insertIntoHuffmanTree(root->right, word_node);
    }

    return root;
}
```
22.findMinHuffmanTree(HuffmanNode* root)
```
HuffmanNode* findMinHuffmanTree(HuffmanNode* root) {
    if (root == NULL) {
        return NULL;
    }

    while (root->left != NULL) {
        root = root->left;
    }

    return root;
}
```
23.deleteMinFromHuffmanTree(HuffmanNode* root)
```
HuffmanNode* deleteMinFromHuffmanTree(HuffmanNode* root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->left == NULL) {
        HuffmanNode* rightChild = root->right;
        free(root);
        return rightChild;
    }

    root->left = deleteMinFromHuffmanTree(root->left);

    return root;
}
```
24.printHuffmanTreeInOrder(HuffmanNode* root)
```
void printHuffmanTreeInOrder(HuffmanNode* root) {
    if (root != NULL) {
        printHuffmanTreeInOrder(root->left);
        printf("%s %d\n", root->word_node->word, root->word_node->frequency);
        printHuffmanTreeInOrder(root->right);
    }
}
```
25.destroyHuffmanTree(HuffmanNode* root)
```
void destroyHuffmanTree(HuffmanNode* root) {
    if (root != NULL) {
        destroyHuffmanTree(root->left);
        destroyHuffmanTree(root->right);
        free(root);
    }
}
```

# Funcionamento

# Arquivos

## CódigoFonte

1. **main.c**
Este arquivo contém a função principal onde são chamadas as demais funções.
2. **Topk.h**
Este arquivo de cabeçalho declara as funções que serão usadas e define as estruturas usadas no algoritmo:
  
3. **Topk.c**
Este arquivo de origem contém as implementações das funções declaradas em System.h.
## Entrada

# Conclusão:


# Compilação e Execução

A estrutura disponibilizada possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

Em resumo, para executar o programa, você precisa navegar até o diretório raiz do projeto e executar o comando make para compilar o programa e, em seguida, 
executar o comando make run para executá-lo.Se você precisar limpar a compilação anterior, pode usar o comando make clean antes de executar a compilação.
