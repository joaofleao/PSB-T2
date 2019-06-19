#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 1000
#define length(array) (sizeof(array)/sizeof(*(array)))

int main(){
    printf("\nRunning\n\n");

    readiFileAndCount();
    test();


    printf("\nDone\n\n");
    return 1;  
} 

void readiFileAndCount() {
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
            printf("%c - %d\n", c, counts[i]);
        }
    }
    

}
typedef struct Node {
    int frequencia;
    char txt;
    struct Node *esquerda;
    struct Node *direita;
    struct Node *pai;
} Node;
typedef struct List{
    Node *n;
    struct List *proximo;
} List;

int test() {
    char chars[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int ints[] = {5, 4, 3, 3, 2, 1};
    List *listOfNodes;
    for (int i =0; i<length(chars);i++) {
        listOfNodes->n = createNode(ints[i], chars[i], NULL, NULL, NULL);
    } 
    

    //printNode(); 
    return 1;
}
void createNode(int frequencia, char txt, Node *esquerda, Node *direita, Node *pai) {
    Node *novo;
    if ( ( novo = malloc(sizeof(*novo)) ) == NULL ) return NULL;
    novo->frequencia = frequencia;
    novo->txt = txt;
    novo->esquerda = esquerda;
    novo->direita = direita;
    novo->pai = pai;

}
void printNode(Node* novo) {
    if (novo->esquerda==NULL) printf("%d, %c", novo->frequencia, novo->txt);
    else printf("%d, %c, <{%d, %c}, >{%d, %c}, ^{%d, %c}", 
    novo->frequencia, 
    novo->txt, 
    novo->esquerda->frequencia, 
    novo->esquerda->txt, 
    novo->direita->frequencia, 
    novo->direita->txt,
    novo->pai->frequencia,
    novo->pai->txt);
}