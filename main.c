#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 1000
#define length(array) (sizeof(array)/sizeof(*(array)))

typedef unsigned char byte;

typedef struct Node {//////////////////////////////////////////////////////////////////////////////////////////define nodo
    int frequencia;
    char txt;
    struct Node *esquerda;
    struct Node *direita;
    struct Node *father;
    char bit;
    bool marked;
} Node;

typedef struct NodeList{///////////////////////////////////////////////////////////////////////////////////////define nodo de lista
    Node *n;
    struct NodeList *proximo;
} NodeList;

typedef struct Word{///////////////////////////////////////////////////////////////////////////////////////define palavras de dicionario
    byte cod;
    struct Word *proximo;
    char meaning;
} Word;

typedef struct Dictionary{///////////////////////////////////////////////////////////////////////////////////////define o dicionario a ser usado
    Word *head;
    int elementos;
} Dictionary;

typedef struct List {//////////////////////////////////////////////////////////////////////////////////////////define lista
    NodeList *head;
    int elementos;
} List;

int main(){////////////////////////////////////////////////////////////////////////////////////////////////////main
    char *printList(List *lista);
    char *printTree(Node *novo);
    List *createList();
    Dictionary *createCodes(List *lista, int number);

    printf("\nRunning\n\n");

    List *lista = createList();
    readiFileAndCount(lista);

    printf("List Size: %d\nList Content: %s\n", lista->elementos, printList(lista));
    int number = lista->elementos;
    createTree(lista);
    createCodes(lista, number);
   
    printf("List Size: %d\nList Content: %s\n", lista->elementos, printList(lista));

    printf("\nDone\n\n");
    return 1;  
} 
Dictionary *createCodes(List *lista, int number) {////////////////////////////////////////////////////transforma a arvore em uma lista de codigos, retorna lista de codigos 
    char *printDictionary(Dictionary *dicionario);
    char *printWord(Word *word);
    Dictionary *d;
    if ( ( d = malloc(sizeof(*d)) ) == NULL ) return NULL;
    Word *w;
    if ( ( w = malloc(sizeof(*w)) ) == NULL ) return NULL;
    Node *x;
    if ( ( x = malloc(sizeof(*x)) ) == NULL ) return NULL;
    d->head = w;
    d->elementos = 0;

    //printf("teste0: %s\n", txt);
    while (!lista->head->n->direita->marked){
        x = lista->head->n;
        char *txt = (char *) malloc(sizeof(char) * 100);
        int test = 0;
        txt[0] = '\0';

        while(x->esquerda) {
            x = x->esquerda;
            sprintf(txt, "%s%s", txt, "0");
            test++;
        }
        w->meaning = x->txt;
        w->cod = txt;
        printf("txt%s", txt);
        w = w->proximo;
        txt[test-1] = '\0';
        d->elementos++;
        x->marked = true;
        x = x->father;
        
        if (x->esquerda->marked && x->direita->marked) {
            x = x->father;
            x->marked = true;
        } 
        x = x->direita;
        sprintf(txt, "%s%s", txt, "1");
        test++;
     printf("head%s", printWord(d->head));

    }

    printf("Dicionário:%s", printDictionary(d));

    return d;
}

void createTree(List *lista) {////////////////////////////////////////////////////cria a arvore e acaba com a lista com somente um item (raiz)
    NodeList *menor(List *lista);
    Node *createNode(int frequencia, char txt, Node *esquerda, Node *direita);
    NodeList *createNodeList (Node *obj);

    while (lista->elementos>1) {
        Node *minor = menor(lista)->n;
        Node *major = menor(lista)->n;
        Node *tree = createNode(minor->frequencia+major->frequencia, '.', major, minor);
        minor->father = tree;
        major->father = tree;
        major->bit = '0';
        minor->bit = '1';
        
    }
}
NodeList *menor(List *lista) {////////////////////////////////////////////////////////////////////////////////////popa o menor numero da lista 
    NodeList *menor = lista->head;
    lista->head = lista->head->proximo;
    lista->elementos--;
    return menor;
}
void readiFileAndCount(List *lista) {////////////////////////////////////////////////////////////////////////////////////ler e montar lista
    Node *createNode(int frequencia, char txt, Node *esquerda, Node *direita);
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
            //printf("%c - %d\n", c, counts[i]);
            insereLista(createNodeList(createNode(counts[i], c, NULL, NULL)), lista);
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

Node *createNode(int frequencia, char txt, Node *esquerda, Node *direita) {//////////////////////////////cria nodo
    Node *novo;
    if ( ( novo = malloc(sizeof(*novo)) ) == NULL ) return NULL;
    novo->frequencia = frequencia;
    novo->txt = txt;
    novo->esquerda = esquerda;
    novo->direita = direita;
    novo->marked = false;
    return novo;
}

char *printWord(Word *word) {//////////////////////////////////////////////////////////////////////////////////////////printa palavra
    char *print = (char *) malloc(sizeof(char) * 1000000);
    
    sprintf(print, "{%c = %s}", word->meaning, word->cod);
    
    return print;
}

char *printDictionary(Dictionary *dicionario) {//////////////////////////////////////////////////////////////////////////////////////////printa dicionario
    char *printWord(Word *word);
    char *print = (char *) malloc(sizeof(char) * 1000000);
    print[0] = '\0';
    Word *item = dicionario->head;
    if (!item) return "Lista Vazia";
    for (int i = 0; item; i++) {
        sprintf(print, "%s{%s}, ", print, printWord(item));
        item = item->proximo;
    }
    return print;
}

char *printTree(Node *node) {//////////////////////////////////////////////////////////////////////////////////////////printa nodo
    char *print = (char *) malloc(sizeof(char) * 1000000);
    
    sprintf(print, "%d, %c, {%d, %c}< >{%d, %c}", node->frequencia, node->txt, node->esquerda->frequencia, node->esquerda->txt, node->direita->frequencia, node->direita->txt);
    
    return print;
}
char *printNode(Node *node) {//////////////////////////////////////////////////////////////////////////////////////////printa nodo
    char *print = (char *) malloc(sizeof(char) * 1000000);

    sprintf(print, "%d, %c", node->frequencia, node->txt);

    return print;
}

char *printList(List *lista) {//////////////////////////////////////////////////////////////////////////////////////////printa nodo
    char *print = (char *) malloc(sizeof(char) * 1000000);
    print[0] = '\0';
    NodeList *item = lista->head;
    if (!item) return "Lista Vazia";
    for (int i = 0; item; i++) {
        sprintf(print, "%s{%s}, ", print, printNode(item->n));
        item = item->proximo;
    }
    return print;
}