#include<stdio.h>
#include<time.h>
#include"funcoes.h"


void main(void){
    int PesoMax,valor;
    int NumeroItem;
    item bagagem;
    int vezes1 = 1250;
    int vezes2 = 2500;
    int vezes3 = 5000;
    
    abrir_arquivo("arquivo.txt",&bagagem);
    imprimir(bagagem);
    
    PesoMax = bagagem.Limite;
    NumeroItem = bagagem.Quant;

    srand(time(NULL));
    clock_t tx,ty,tz,tk,tw,tv,tg;
   
    //Mochila Forca Bruta
    tx = clock();
    printf("\nMochila Forca Bruta\n");
    valor = mochila_forca_bruta(PesoMax,bagagem,NumeroItem);
    //printf("\nBeneficio = %d",valor);
    tx = clock() - tx;
    printf("\nTempo em milisegundos %lf\n",((tx) /(double) (CLOCKS_PER_SEC / 1000)));

    //Mochila Maior Valor
    ty = clock();
    printf("\nMochila Maior Valor\n");
    mochila_heurastica_maiorvalor(PesoMax,bagagem,NumeroItem);
    ty = clock() - ty;
    printf("\nTempo em milisegundos %lf\n",((ty) /(double) (CLOCKS_PER_SEC / 1000)));
    
    //Mochila Beneficio%Pesos
    printf("\nMochila Peso Beneficio\n");
    tz = clock();
    mochila_heurastica_pesobeneficio(PesoMax,bagagem,NumeroItem);
    tz = clock() - tz;
    printf("\nTempo em milisegundos %lf\n",((tz) /(double) (CLOCKS_PER_SEC / 1000)));
    
    //Mochila Menor Peso
    tk = clock();
    printf("\nMochila Menor Peso\n");
    mochila_heurastica_menorpeso(PesoMax, bagagem,NumeroItem);
    tk = clock() - tk;
    printf("\nTempo em milisegundos %lf\n",((double)(tk) / (CLOCKS_PER_SEC / 1000)));
    
    //Mochila Aleatoria
    tw = clock();
    printf("\nMochila Aleatoria: %d vezes \n",vezes1);
    mochila_aleatoria(PesoMax,bagagem, NumeroItem,vezes1);
    tw = clock() - tw;
    printf("\nTempo em milisegundos %lf\n",((tw) /(double) (CLOCKS_PER_SEC / 1000)));

    //Mochila Aleatoria
    tv = clock();
    printf("\nMochila Aleatoria: %d vezes \n",vezes2);
    mochila_aleatoria(PesoMax,bagagem, NumeroItem,vezes2);
    tv = clock() - tv;
    printf("\nTempo em milisegundos %lf\n",((tv) /(double) (CLOCKS_PER_SEC / 1000)));

//Mochila Aleatoria
    tg = clock();
    printf("\nMochila Aleatoria: %d vezes \n",vezes3);
    mochila_aleatoria(PesoMax,bagagem, NumeroItem,vezes3);
    tg = clock() - tg;
    printf("\nTempo em milisegundos %lf\n",((tg) /(double) (CLOCKS_PER_SEC / 1000)));


  
    libera_memoria(&bagagem);
}