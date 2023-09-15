#include<stdio.h>
#include<stdlib.h>
#include<time.h>



typedef struct { //Cria uma struct de items para a mochila 
    int Limite; // Limite de peso
    int Quant ; // Quantidade de items 
    int *peso ; // vetor que ira ser alocado para os pesos 
    int *valor ;  // vetor que sera alocado para os valores
}item;  //  Nome do tipo criado  

/* Cabecalho das Funcoes */
void imprimir(item bagagem); // imprime os vetores peso e valor 
void abrir_arquivo(char *path, item *bagagem); // abre o arquivo.txt
void aloca_memoria(item *bagagem); // aloca memoria para o vetor peso e valor  e solubinaria
void libera_memoria(item *bagagem);
void imprime_vetor(int vetor[],item bagagem, int aux ,int pesomax);

int maior(int a , int b);// retorna o maior valor entre a e b 

void mochila_aleatoria(int PesoMax, item bagagem, int aux, int vezes); // Cria vetores binarios aleatorios e imprime o melhor deles depois da quantidade de vezes definida

void mochila_heurastica_menorpeso(int PesoMax,item bagagem, int aux);//Cria um vetor binario que preenche-se  primeiramente nas posicoes de menor peso ate que nao haja mais espaco na mochila, o imprimindo no final

void mochila_heurastica_maiorvalor(int PesoMax,item bagagem, int aux);//Cria um vetor binario que preenche-se  primeiramente nas posicoes de maior valor(beneficio) ate que nao haja mais espaco na mochila, o imprimindo no final

void mochila_heurastica_pesobeneficio(int PesoMax,item bagagem, int aux);//Cria um vetor binario que preenche-se  primeiramente nas posicoes de maior beneficio/peso ate que nao haja mais espaco na mochila, o imprimindo no final

int mochila_forca_bruta(int PesoMax, item bagagem, int aux);//Explora todos os subproblemas possiveis da mochila binaria e retorna o resultado da que possui maior beneficio