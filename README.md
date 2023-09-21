
# Descrição do algoritmo


# Regras Propostas


# Funções 

```
void initializeHashTable(HashTable* hash_table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table->table[i] = NULL;
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




# Sistema-de-Autocompletar

1-codificação huffman
2-input+output
