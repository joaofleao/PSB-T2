#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 #define MAXCHAR 10000000

#define length(array) (sizeof(array)/sizeof(*(array)))

typedef struct Node {//////////////////////////////////////////////////////////////////////////////////////////define nodo
    int frequencia;
    char txt;
    struct Node *esquerda;
    struct Node *direita;
    int codigo;
} Node;

typedef struct NodeList{///////////////////////////////////////////////////////////////////////////////////////define nodo de lista
    Node *n;
    struct NodeList *proximo;
} NodeList;

typedef struct List {//////////////////////////////////////////////////////////////////////////////////////////define lista
    NodeList *head;
    int elementos;
} List;

int main(){////////////////////////////////////////////////////////////////////////////////////////////////////main
    char *printList(List *lista);
    char *printTree(Node *novo);
    bool pegaCodigo(Node *n, int c, char *buffer, int tamanho, bool option);
    List *createList();
    printf("\nRunning\n\n");

    List *lista = createList();
    readiFileAndCount(lista);
    //printf("List Size: %d\nList Content: %s\n", lista->elementos, printList(lista));
    int tamanho = lista->elementos;
    createTree(lista);
    
    Node *caminhamento;
    if ( ( caminhamento = malloc(sizeof(*caminhamento)) ) == NULL ) return NULL;


    FILE *final = fopen("final.txt", "r");
    if (!final){
        printf("Erro ao abrir arquivo\n");
        return;
    } 
    char total[100000] = {0};
    int j = 0;
    for (int i = 0; j<tamanho; i++) {
        char buffer[1024] = {0};
        
        if (pegaCodigo(lista->head->n, i, buffer, 0, true)) {
            sprintf(total, "%s{%s} - ", total,  buffer);
            j++;
        }
        
    }
    fclose(final);
    // printf("%s\n", total);


    // printf("List Size: %d\nList Content: %s\n", lista->elementos, printList(lista));
    translateAndPrint(total, lista);


    //printf("Tree: %s\n", printTree(lista->head->n));

    //createCodes(lista);
    
    // printf("Dicionario: %s\n", printDictionary(d));

    printf("\nDone\n\n");
    return 1;  
} 
void translateAndPrint(char *total, List *lista) {
    bool pegaCodigo(Node *n, int c, char *buffer, int tamanho, bool option);
    FILE *file;
    file = fopen("test.txt", "r");
    int c;
    while ((c = fgetc(file)) != EOF){
        char buffer[1024] = {0};
        pegaCodigo(lista->head->n, ((char)c), buffer, 0, false);
        
        sprintf(total, "%s%s ", total,  buffer);
    }
    fclose(file);

    FILE *final;
    
    final = fopen("final.txt", "w");    

    if (file == NULL){
    printf("error");
    return;
    }
    fprintf(final, "%s", total);
    fclose(final);

}
bool pegaCodigo(Node *n, int c, char *buffer, int tamanho, bool option){
    // Caso base da recursão:
    // Se o nó for folha e o seu valor for o buscado, colocar o caractere terminal no buffer e encerrar

    if (!(n->esquerda || n->direita) && n->codigo == c && option){
        buffer[tamanho] = ' ';
        buffer[tamanho+1] = '=';
        buffer[tamanho+2] = ' ';
        buffer[tamanho+3] = n->txt;
        buffer[tamanho+4] = '\0';
        
        return true;
    }
    else if (!(n->esquerda || n->direita) && n->codigo == c && !option){
        buffer[tamanho] = ' ';
        buffer[tamanho+4] = '\0';
        
        return true;
    }
    else{
        bool encontrado = false;
        // Se existir um nó à esquerda
        if (n->esquerda){
            // Adicione '0' no bucket do buffer correspondente ao 'tamanho' nodeAtual
            buffer[tamanho] = '0';
            
            // fazer recursão no nó esquerdo
            encontrado = pegaCodigo(n->esquerda, c, buffer, tamanho + 1, option);
        }
        if (!encontrado && n->direita){
            buffer[tamanho] = '1';
            encontrado = pegaCodigo(n->direita, c, buffer, tamanho + 1, option);
        }
        if (!encontrado){
            buffer[tamanho] = '\0';
        }
        return encontrado;
    }
}

void createTree(List *lista) {
    NodeList *menor(List *lista);
    Node *createNode(int frequencia, char txt, Node *esquerda, Node *direita, int codigo);
    NodeList *createNodeList (Node *obj);

    while (lista->elementos>1) {
        Node *minor = menor(lista)->n;
        Node *major = menor(lista)->n;
        Node *tree = createNode(minor->frequencia+major->frequencia, NULL, major, minor, NULL);
    
        insereLista(createNodeList(tree), lista);
    }

}
NodeList *menor(List *lista) {
    NodeList *menor = lista->head;
    lista->head = lista->head->proximo;
    lista->elementos--;
    return menor;
}
void readiFileAndCount(List *lista) {////////////////////////////////////////////////////////////////////////////////////ler e montar lista
    Node *createNode(int frequencia, char txt, Node *esquerda, Node *direita, int codigo);
    NodeList *createNodeList (Node *obj);
       
    FILE *file = fopen("test.txt","r");
    if(file == NULL) return NULL;
    fseek(file, 0, SEEK_END);
    long int size = ftell(file);
    rewind(file);
    char *content = calloc(size + 1, 1);
    fread(content,1,size,file);
    int counts[256] = { 0 };
    int i;
    size_t len = strlen(content);
    for (i = 0; i < len; i++) {
        counts[(int)(content[i])]++;
    }
    
    for (i = 0; (i < 256); i++) {
        if (counts[i]!=0) {
            char c = i; 
            insereLista(createNodeList(createNode(counts[i], c, NULL, NULL, i)), lista);
            
        }
    }
}
 
void insereLista(NodeList *b, List *lista){//////////////////////////////////////////////////////////////////////////////////insere na lista
     
    if (!lista->head){ //coloca no começo se vazia
        lista->head = b;
    }

   else if (b->n->frequencia < lista->head->n->frequencia){ //se for maior a frequencia adiciona como head
        b->proximo = lista->head;
        lista->head = b;

    }
    else { //vai ate posicao certa e adiciona nela
        NodeList *aux = lista->head->proximo;
        NodeList *aux2 = lista->head;

        while (aux && aux->n->frequencia <= b->n->frequencia){
            aux2 = aux;
            aux = aux2->proximo;
        }
        aux2->proximo = b;
        b->proximo = aux;
    }
    lista->elementos++;
}

List *createList() {/////////////////////////////////////////////////////////////////////////////////////////////////cria lista
    List *lista;
    if ( ( lista = malloc(sizeof(*lista)) ) == NULL ) return NULL;
    lista->elementos = 0;
    lista->head = NULL;
    return lista;
}

NodeList *createNodeList (Node *obj) {////////////////////////////////////////////////////////////////////////////////cria nodo de lista
    NodeList *nodo;
    if ( ( nodo = malloc(sizeof(*nodo)) ) == NULL ) return NULL;
    nodo->n = obj;
    nodo->proximo = NULL;
    return nodo;
}

Node *createNode(int frequencia, char txt, Node *esquerda, Node *direita, int codigo) {//////////////////////////////cria nodo
    Node *novo;
    if ( ( novo = malloc(sizeof(*novo)) ) == NULL ) return NULL;
    novo->frequencia = frequencia;
    novo->txt = txt;
    novo->esquerda = esquerda;
    novo->direita = direita;
    novo->codigo = codigo;
    
    return novo;
}

char *printTree(Node *node) {//////////////////////////////////////////////////////////////////////////////////////////printa nodo
    char *print = (char *) malloc(sizeof(char) * MAXCHAR);
    char *printNode(Node *node);
    if (!node->esquerda) return printNode(node);
    sprintf(print, "[%s< %s >%s]", printTree(node->esquerda),printNode(node), printTree(node->direita));
    
    return print;
}
char *printNode(Node *node) {//////////////////////////////////////////////////////////////////////////////////////////printa nodo
    char *print = (char *) malloc(sizeof(char) * MAXCHAR);

    sprintf(print, "{%c, %d}", node->txt, node->frequencia);

    return print;
}

char *printList(List *lista) {//////////////////////////////////////////////////////////////////////////////////////////printa nodo
    char *print = (char *) malloc(sizeof(char) * MAXCHAR);
    print[0] = '\0';
    NodeList *item = lista->head;
    if (!item) return "Lista Vazia";
    while(item){
        sprintf(print, "%s%s, ", print, printNode(item->n));
        item = item->proximo;
    }
    return print;
}
