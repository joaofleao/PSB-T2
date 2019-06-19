#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 1000
#define length(array) (sizeof(array)/sizeof(*(array)))

typedef struct Node {//////////////////////////////////////////////////////////////////////////////////////////define nodo
    int frequencia;
    char txt;
    struct Node *esquerda;
    struct Node *direita;
    struct Node *pai;
} Node;

typedef struct NodeList{///////////////////////////////////////////////////////////////////////////////////////define nodo de lista
    Node *n;
    struct NodeList *proximo;
} NodeList;

typedef struct List {//////////////////////////////////////////////////////////////////////////////////////////define lista
    NodeList   *head;
    int         elementos;
} List;

int main(){////////////////////////////////////////////////////////////////////////////////////////////////////main
    printf("\nRunning\n\n");

    readiFileAndCount();

    printf("\nDone\n\n");
    return 1;  
} 

void readiFileAndCount() {////////////////////////////////////////////////////////////////////////////////////ler e montar lista
    Node *createNode(int frequencia, char txt, Node *esquerda, Node *direita, Node *pai);
    NodeList *createNodeList (Node *obj);
    List *createList();
    char *printNode(Node* novo);

    List *lista = createList();
    
    
    FILE* file = fopen("test.txt","r");
    if(file == NULL) return NULL;
    fseek(file, 0, SEEK_END);
    long int size = ftell(file);
    rewind(file);
    char* content = calloc(size + 1, 1);
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
            insereLista(createNodeList(createNode(counts[i], c, NULL, NULL, NULL)), lista);
          //  printf("%c - %d\n", c, counts[i]);
        }
    }
    printf("List Size: %d\nSmallest Node: %s\n", lista->elementos, printNode(lista->head->n));

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

Node *createNode(int frequencia, char txt, Node *esquerda, Node *direita, Node *pai) {//////////////////////////////cria nodo
    Node *novo;
    if ( ( novo = malloc(sizeof(*novo)) ) == NULL ) return NULL;
    novo->frequencia = frequencia;
    novo->txt = txt;
    novo->esquerda = esquerda;
    novo->direita = direita;
    novo->pai = pai;
    return novo;
}
char *printNode(Node* novo) {//////////////////////////////////////////////////////////////////////////////////////////printa nodo
    const char base_string[] = "base_string";
    char print [1000];
    
    if (novo->esquerda==NULL) sprintf(print, "%s%d, %c", base_string, novo->frequencia, novo->txt);
    else sprintf(print, "%s%d, %c, <{%d, %c}, >{%d, %c}, ^{%d, %c}", base_string, 
    novo->frequencia, 
    novo->txt, 
    novo->esquerda->frequencia, 
    novo->esquerda->txt, 
    novo->direita->frequencia, 
    novo->direita->txt,
    novo->pai->frequencia,
    novo->pai->txt);
    return print;
}