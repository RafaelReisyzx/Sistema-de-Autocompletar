
# Descrição do algoritmo
O programa de análise de texto representa uma ferramenta sofisticada para a análise de documentos textuais. Utilizando uma série de algoritmos inteligentes, este software inicia sua operação carregando uma lista de stopwords, que consistem em palavras comuns que são desconsideradas no processo de contagem de frequência. Em seguida, ele procede a analisar o arquivo de texto, realizando operações como a remoção de pontuações e a conversão de todas as letras para minúsculas, a fim de garantir uma análise precisa e abrangente. Durante esse processo, o programa calcula a frequência de cada palavra e as armazena em estruturas de dados como árvores binárias e árvores AVL, permitindo uma ordenação eficiente e uma rápida recuperação das palavras mais frequentes. Além disso, uma árvore de Huffman é construída, proporcionando uma representação compacta das palavras com maior frequência por meio de códigos Huffman. Os resultados são elegantemente apresentados em um arquivo de saída, tornando-os prontamente acessíveis para análise subsequente. Este programa não apenas simplifica a identificação das palavras-chave mais relevantes em um corpus de texto.

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

Esta função é responsável por inicializar uma tabela de hash. Ela recebe como parâmetro um ponteiro para a estrutura HashTable. A função percorre todas as posições da tabela de hash e inicializa cada uma delas com um valor nulo. Essa etapa é importante para garantir que a tabela de hash esteja pronta para armazenar dados.
```
void initializeHashTable(HashTable* hash_table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table->table[i] = NULL;
    }
}
```
2.loadStopWords(HashTable* hash_table, const char* stop_words_file)

Esta função carrega palavras de parada (stop words) de um arquivo e as insere na tabela de hash. Ela recebe como parâmetros um ponteiro para a estrutura HashTable e o caminho para o arquivo contendo as stop words. A função abre o arquivo em modo de leitura, lê cada linha (representando uma stop word), remove quaisquer caracteres de quebra de linha, calcula o hash da palavra e insere a palavra na tabela de hash com uma frequência de -1 (indicando que é uma stop word).
Isso é útil em tarefas de análise de texto, onde é comum remover palavras de parada (como "a", "e", "o", etc.) que não contribuem significativamente para a análise.
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

Esta função implementa uma função de hash simples para converter uma string em um valor de hash. Ela recebe como parâmetro uma string str. A função utiliza o algoritmo de hash chamado "djb2", que é uma função de dispersão amplamente utilizada. O algoritmo itera por cada caractere da string, atualizando o valor de hash com base no caractere atual.
A função retorna um valor de hash (um número inteiro sem sinal longo) que representa a string. Esse valor de hash é usado para indexar a tabela de hash, permitindo um acesso eficiente aos dados armazenados.
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

Esta função cria um novo nó de palavra (Word) a partir de uma string word fornecida como parâmetro. Ela aloca dinamicamente memória para um novo nó de palavra, copia a string word para o campo word da estrutura e inicializa a frequência como 1. O nó de palavra criado é então retornado como resultado da função. Essa função é usada para criar novos nós de palavra ao processar e inserir palavras na tabela de hash.
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

Esta função  é responsável pelo processamento e inserção de palavras na tabela de hash. Ele é executado dentro da função processFile, que lê um arquivo de texto e extrai palavras para inserção na tabela de hash. O código realiza as seguintes etapas:
Transforma todas as letras da palavra em minúsculas usando a função tolower. Isso garante que as palavras sejam tratadas como maiúsculas ou minúsculas, independentemente de como foram escritas no arquivo.
Calcula o hash da palavra usando a função hashFunction para determinar a posição na tabela de hash onde a palavra será inserida.
Verifica se a palavra já existe na tabela de hash. Se a palavra já estiver na tabela, sua frequência é incrementada.
Se a palavra não estiver na tabela, um novo nó de palavra é criado usando a função createWordNode e inserido na tabela de hash.
Este trecho de código é fundamental para a construção da tabela de hash que mantém o controle das frequências das palavras no arquivo de entrada.
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

Esta função insere um novo nó de palavra em uma árvore binária de busca. Ela recebe como parâmetros um ponteiro para o nó raiz da árvore (root) e um ponteiro para o nó de palavra que deseja inserir (word_node).
Se o nó raiz for nulo, isso significa que a árvore está vazia, e um novo nó é criado com word_node como seu conteúdo e retornado como raiz da árvore.
Se o nó raiz não for nulo, a função compara a frequência do word_node com a frequência do nó atual.
Se a frequência do word_node for menor, a função chama recursivamente insertIntoBinaryTree para inserir o nó na subárvore esquerda.
Se a frequência do word_node for maior ou igual, a função chama recursivamente insertIntoBinaryTree para inserir o nó na subárvore direita.
A função retorna o nó raiz atualizado após a inserção.
Essa função é usada para construir uma árvore binária de busca onde os nós estão ordenados por frequência. É útil para encontrar as palavras mais frequentes em ordem de frequência.
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
7.void generateHuffmanCodesToFile(HuffmanTreeNode* root, char* code, int depth, FILE* output_file)

Esta função gera os códigos Huffman para as palavras presentes na árvore Huffman e escreve esses códigos em um arquivo de saída. Ela é uma função recursiva que percorre a árvore Huffman e, à medida que avança, constrói o código binário para cada palavra. A função recebe os seguintes parâmetros:
HuffmanTreeNode* root: O nó raiz da árvore Huffman.
char* code: O código parcial sendo construído enquanto a função percorre a árvore.
int depth: A profundidade atual na árvore, usado para rastrear o número de bits no código.
FILE* output_file: Um ponteiro para o arquivo de saída onde os códigos Huffman serão escritos.
A função percorre a árvore de forma recursiva, movendo-se para a esquerda quando um bit 0 é encontrado e para a direita quando um bit 1 é encontrado. Quando alcança uma folha da árvore (representando uma palavra), ela escreve o código binário resultante no arquivo de saída.
```
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
```
8.deleteMinFromBinaryTree(BinaryTreeNode* root)

Esta função remove o nó com a menor chave (palavra com menor frequência) de uma árvore binária de busca e retorna a raiz atualizada da árvore. Ela é usada para manter a árvore equilibrada após a remoção de um nó. Os parâmetros da função são:
BinaryTreeNode* root: O nó raiz da árvore binária de busca.
A função realiza o seguinte procedimento:
Verifica se o nó atual (root) é nulo. Se for, retorna nulo, indicando que não há mais nós para remover.
Verifica se o nó à esquerda de root é nulo. Se for, isso significa que root é o nó com a menor chave na subárvore e pode ser removido.
Se o nó à esquerda não for nulo, a função chama recursivamente deleteMinFromBinaryTree(root->left) para encontrar o nó com a menor chave na subárvore esquerda.
Atribui o resultado dessa chamada (root->left) ao nó à esquerda de root, removendo assim o nó com a menor chave.
Retorna root, que é a raiz atualizada da árvore após a remoção.
Isso garante que, após a execução da função, a árvore binária de busca ainda seja uma árvore válida e equilibrada.
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
9.void printBinaryTreeInOrder(BinaryTreeNode* root);

Esta função realiza uma travessia em ordem de uma árvore binária de busca e imprime os nós na ordem correta. Ela é usada para imprimir as palavras da árvore em ordem alfabética (ou em ordem crescente de chave). Os parâmetros da função são:
BinaryTreeNode* root: O nó raiz da árvore binária de busca.
A função segue o seguinte procedimento:
Verifica se o nó atual (root) não é nulo.
Se não for nulo, chama recursivamente printBinaryTreeInOrder(root->left) para imprimir todos os nós na subárvore esquerda (com chaves menores).
Em seguida, imprime as informações do nó atual, que incluem a palavra e sua frequência.
Finalmente, chama recursivamente printBinaryTreeInOrder(root->right) para imprimir todos os nós na subárvore direita (com chaves maiores).
Essa função garante que os nós da árvore sejam impressos em ordem crescente com base em suas chaves (palavras). Ela é útil para listar todas as palavras em ordem alfabética juntamente com suas frequências.
```
void printBinaryTreeInOrderToFile(BinaryTreeNode* root, FILE* output_file) {
    if (root != NULL) {
        printBinaryTreeInOrderToFile(root->left, output_file);
        fprintf(output_file, "%s %d\n", root->word_node->word, root->word_node->frequency);
        printBinaryTreeInOrderToFile(root->right, output_file);
    }
}
```
10.HuffmanTreeNode* buildHuffmanTree(Word* words[], int word_count);

Esta função constrói a árvore Huffman a partir de uma lista de palavras e suas frequências. Ela utiliza o algoritmo de construção de árvore de Huffman para criar uma árvore binária de busca balanceada onde as palavras mais frequentes estão próximas à raiz da árvore. A função recebe os seguintes parâmetros:
Word* words[]: Um array de ponteiros para estruturas Word, onde cada estrutura contém uma palavra e sua frequência.
int word_count: O número total de palavras no array.
A função segue os passos típicos do algoritmo de Huffman:
Inicializa um array de ponteiros HuffmanTreeNode* nodes[] para representar os nós iniciais da árvore Huffman.
Para cada palavra na lista de palavras, cria um nó Huffman correspondente e preenche o nodes[] com esses nós iniciais.
Enquanto houver mais de um nó no nodes[], a função itera para encontrar os dois nós com as frequências mais baixas e combina-os em um novo nó.
O novo nó é inserido de volta no nodes[], e os nós originais são removidos.
O processo é repetido até que reste apenas um nó no nodes[], que é a raiz da árvore Huffman.
No final, a função retorna o nó raiz da árvore Huffman construída.


```
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
```
11. getHeight(AVLTreeNode* node)

Esta função calcula a altura de um nó em uma árvore AVL. A altura de um nó é a distância entre o nó e a folha mais distante que está descendendo desse nó. Os parâmetros da função são:
AVLTreeNode* node: O nó para o qual a altura será calculada.
O procedimento da função é o seguinte:
Verifica se o nó atual (node) é nulo. Se for, isso significa que a altura é 0, pois não há nenhum nó abaixo desse ponto.
Caso contrário, retorna a altura armazenada no campo height do nó. O campo height é atualizado durante as operações de inserção e exclusão para manter a propriedade de balanceamento da árvore AVL.
```
int getHeight(AVLTreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}
```
12.getBalanceFactor(AVLTreeNode* node)

Esta função calcula o fator de balanceamento de um nó em uma árvore AVL. O fator de balanceamento de um nó é a diferença entre as alturas de suas subárvores esquerda e direita. Os parâmetros da função são:
AVLTreeNode* node: O nó para o qual o fator de balanceamento será calculado.
O procedimento da função é o seguinte:
Verifica se o nó atual (node) é nulo. Se for, isso significa que o fator de balanceamento é 0, pois não há subárvores esquerda ou direita.
Caso contrário, calcula o fator de balanceamento subtraindo a altura da subárvore direita da altura da subárvore esquerda (getHeight(node->left) - getHeight(node->right)).
```
int getBalanceFactor(AVLTreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}
```
13.rotateRight(AVLTreeNode* y)

Esta função realiza uma rotação para a direita em torno do nó y em uma árvore AVL. As rotações são operações utilizadas para manter ou restaurar o balanceamento da árvore AVL após a inserção ou exclusão de nós. Os parâmetros da função são:
AVLTreeNode* y: O nó em torno do qual a rotação será realizada.
O procedimento da função é o seguinte:
Cria um novo nó x que é a subárvore esquerda de y.
Atualiza a subárvore esquerda de x para ser a subárvore direita de y.
Atualiza a subárvore esquerda de y para ser x.
Atualiza as alturas de y e x com base nas alturas de suas subárvores esquerda e direita.
Retorna o novo nó x, que agora se tornou o nó pai de y na rotação.
Essa rotação é usada quando há um desequilíbrio à esquerda em um nó da árvore AVL.
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

Esta função realiza uma rotação para a esquerda em torno do nó x em uma árvore AVL. Assim como a função rotateRight, as rotações são operações utilizadas para manter ou restaurar o balanceamento da árvore AVL. Os parâmetros da função são:
AVLTreeNode* x: O nó em torno do qual a rotação será realizada.
O procedimento da função é o seguinte:
Cria um novo nó y que é a subárvore direita de x.
Atualiza a subárvore direita de y para ser a subárvore esquerda de x.
Atualiza a subárvore direita de x para ser y.
Atualiza as alturas de x e y com base nas alturas de suas subárvores esquerda e direita.
Retorna o novo nó y, que agora se tornou o nó pai de x na rotação.
Essa rotação é usada quando há um desequilíbrio à direita em um nó da árvore AVL.

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

Esta função desempenha um papel crucial na manutenção do balanceamento de uma árvore AVL (Árvore Binária de Busca Balanceada). Ela recebe como parâmetro um ponteiro para um nó da árvore AVL e verifica se o nó ou qualquer um de seus descendentes diretos está desequilibrado. Se um desequilíbrio é detectado, a função executa as rotações necessárias para restaurar o equilíbrio da árvore.
A primeira etapa da função calcula o fator de equilíbrio do nó atual. O fator de equilíbrio é definido como a diferença entre a altura da subárvore esquerda e a altura da subárvore direita do nó. Um fator de equilíbrio positivo indica um desequilíbrio para a esquerda, enquanto um fator de equilíbrio negativo indica um desequilíbrio para a direita.
A função então verifica dois casos de desequilíbrio:
Caso de desequilíbrio à esquerda: Se o fator de equilíbrio for maior que 1, significa que a subárvore esquerda é mais alta do que a subárvore direita. Neste caso, a função verifica se o desequilíbrio ocorre na subárvore esquerda da subárvore esquerda (rotação dupla à direita) e, se necessário, realiza uma rotação à esquerda seguida de uma rotação à direita para equilibrar a árvore.
Caso de desequilíbrio à direita: Se o fator de equilíbrio for menor que -1, significa que a subárvore direita é mais alta do que a subárvore esquerda. Neste caso, a função verifica se o desequilíbrio ocorre na subárvore direita da subárvore direita (rotação dupla à esquerda) e, se necessário, realiza uma rotação à direita seguida de uma rotação à esquerda para equilibrar a árvore.
Após as rotações, a função retorna o novo nó raiz da subárvore, que agora está balanceada. Se não houver desequilíbrio ou se nenhum ajuste for necessário, a função retorna o nó original sem modificação.
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

Esta função é responsável por inserir um novo nó contendo uma palavra em uma árvore AVL (Árvore Binária de Busca Balanceada). Ela recebe como parâmetros um ponteiro para o nó raiz da árvore AVL e um ponteiro para o nó de palavra que será inserido. A função realiza a inserção de maneira a manter a propriedade de balanceamento da árvore AVL.
A inserção começa comparando a frequência da palavra a ser inserida com a frequência do nó atual na árvore. Se a frequência da palavra for menor, a função chama a si mesma recursivamente para inserir a palavra na subárvore esquerda do nó atual. Caso contrário, a palavra é inserida na subárvore direita. Após a inserção, a altura do nó atual é atualizada para refletir a altura da subárvore mais alta entre suas subárvores esquerda e direita, mais 1.
Por fim, a função verifica se o balanceamento da árvore foi afetado pela inserção e, se necessário, realiza rotações para reequilibrar a árvore. A função balanceAVLTree é chamada para fazer essa verificação e ajuste. Após todos esses passos, a função retorna a raiz da árvore AVL atualizada.
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
17.void generateHuffmanCodes(HuffmanTreeNode* root, char* code, int depth);

A função generateHuffmanCodes é usada para gerar os códigos de Huffman para os nós de uma árvore de Huffman. Ela recebe como parâmetros um ponteiro para o nó raiz da árvore de Huffman, uma string code que armazena temporariamente o código atualmente construído e a profundidade depth na árvore. A função percorre a árvore de forma recursiva, construindo os códigos de Huffman para cada nó folha (representando uma palavra) com base na profundidade e na posição do nó na árvore. Os códigos gerados são úteis para a compactação de informações.

```
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

```
18.deleteMinFromAVLTree(AVLTreeNode* root)

A função deleteMinFromAVLTree é usada para remover o nó com a menor chave (neste caso, a palavra com a menor frequência) de uma árvore AVL. Ela é uma parte importante do processo de manutenção da árvore AVL após inserções e exclusões. A função percorre a árvore até encontrar o nó mais à esquerda, que tem a menor chave. Em seguida, ela remove esse nó da árvore e realiza as rotações e ajustes necessários para manter a propriedade de árvore AVL. Após a remoção, a função retorna a raiz atualizada da árvore.
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
19.printAVLTreeInOrderToFile(AVLTreeNode* root, FILE* output_file);

Assim como a função printBinaryTreeInOrderToFile, esta função também imprime os nós de uma árvore, mas no caso, de uma árvore AVL, em ordem (in-order) em um arquivo de saída especificado. Ela percorre a árvore de forma recursiva, visitando primeiro o nó esquerdo, depois imprimindo os dados do nó atual (a palavra e sua frequência) no arquivo de saída e, por fim, visitando o nó direito. Isso permite que os resultados da análise de texto da árvore AVL sejam registrados em um arquivo de saída.

```
void printAVLTreeInOrderToFile(AVLTreeNode* root, FILE* output_file) {
    if (root != NULL) {
        printAVLTreeInOrderToFile(root->left, output_file);
        fprintf(output_file, "%s %d\n", root->word_node->word, root->word_node->frequency);
        printAVLTreeInOrderToFile(root->right, output_file);
    }
}

```
20.printBinaryTreeInOrderToFile(BinaryTreeNode* root, FILE* output_file);

Esta função é similar à função printAVLTreeInOrderToFile, mas é usada para imprimir os nós de uma árvore binária em ordem (in-order) em um arquivo de saída específico. Ela segue o mesmo princípio de percorrer a árvore recursivamente e registrar os resultados no arquivo de saída.
Todas essas funções desempenham papéis importantes na geração e na apresentação de resultados da análise de texto. Elas permitem que os resultados sejam registrados em arquivos e também garantem que as estruturas de árvore (tanto AVL quanto binária) sejam manipuladas e impressas de maneira adequada, fornecendo informações valiosas sobre as palavras mais frequentes em um texto.

```
void printBinaryTreeInOrderToFile(BinaryTreeNode* root, FILE* output_file) {
    if (root != NULL) {
        printBinaryTreeInOrderToFile(root->left, output_file);
        fprintf(output_file, "%s %d\n", root->word_node->word, root->word_node->frequency);
        printBinaryTreeInOrderToFile(root->right, output_file);
    }
}
```

# Funcionamento

O programa de análise de texto foi desenvolvido para processar arquivos de texto e identificar as palavras mais frequentes, utilizando diferentes estruturas de dados, como árvores binárias, árvores AVL e árvores de Huffman. O programa realiza as seguintes etapas:

Carregamento de Stopwords: Antes de processar o arquivo de texto, o programa carrega uma lista de stopwords (palavras comuns que geralmente são ignoradas em análises de texto) de um arquivo específico. As stopwords não são incluídas nas estatísticas.

Processamento do Arquivo de Texto: O programa lê um arquivo de texto e processa cada palavra, ignorando pontuações e convertendo todas as letras para minúsculas. Ele calcula a frequência de cada palavra e a armazena em uma tabela hash.

Construção de Árvores: O programa constrói três tipos de árvores com as palavras mais frequentes encontradas:

Árvore Binária: Uma árvore binária de busca onde as palavras são inseridas com base em sua frequência.
Árvore AVL: Uma árvore binária de busca balanceada (Árvore AVL) que mantém o equilíbrio para garantir um desempenho eficiente.
Árvore de Huffman: Uma árvore de Huffman é construída com base nas frequências das palavras.
Geração de Códigos Huffman: O programa gera os códigos de Huffman para as palavras com base na árvore de Huffman construída.

Saída de Resultados: Os resultados são impressos em um arquivo de saída, que inclui as palavras mais frequentes nas árvores binária e AVL, bem como os códigos de Huffman para as palavras.

# Conclusão:

O programa de análise de texto é uma ferramenta poderosa para identificar as palavras mais frequentes em um conjunto de documentos. Ele utiliza estruturas de dados eficientes para armazenar e processar os dados, e gera códigos de Huffman para as palavras mais frequentes, o que pode ser útil em aplicações de compressão de texto.

# Compilação e Execução

A estrutura disponibilizada possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

Em resumo, para executar o programa, você precisa navegar até o diretório raiz do projeto e executar o comando make para compilar o programa e, em seguida, 
executar o comando make run para executá-lo.Se você precisar limpar a compilação anterior, pode usar o comando make clean antes de executar a compilação.
