#include "funcoes.h"

int maior(int a , int b){ //Funcao que compara 2 numeros e retorna o de maior valor 
    if (a > b){
        return a;
    }else{
        return b;
    }
}

int mochila_forca_bruta(int PesoMax, item bagagem, int aux){ //Paramentros: Pesomaixmo , struct que contem as informacoes as dos items, aux = Numero de Items
    int x,y; // variaveis de auxilio contadoras
    int matriz[aux+1][PesoMax+1];  // matriz solucao que ira alocar os maiores valores(beneficios) para determinado peso;
    for(x=0; x <= aux; x++){ //percorre o eixo x da matriz                                                                                                                                                                                      // A funcao mochila binaria funciona preenchendo uma matriz[aux+1][Pesomax+1] de forma qua as melhores solucoes possiveis do
        for(y =0; y <= PesoMax; y++){ //percorre o eixo y da matriz
            if(x == 0 || y==0){// x = quantidade de itens disponiveis ,y = peso                                                                                                                                                                 // problema da mochila binaria sejam calculadas, ou seja os pontos da matriz representam subproblemas no qual um limite de peso y
                matriz[x][y] = 0;  //como nao possui x ou y nao tera como inserir item beneficio = 0                                                                                                                                            // e colocado e as melhores combinacoes de uma quantidade de elementos x e comparada,descobrindo o melhor valor do intervalo definido, ate que o limite y de peso seja o maximo e
            }else{//prenche um ponto da matriz caso o peso do item x seja <= peso y                                                                                                                                                             // e quantidade de items x anilisado tambem seja maximo,ou seja ate o ultimo ponto do vetor ,que ira reprenstar a melhor combinacao de valor maximo,
                    if(bagagem.peso[x-1] <= y){//caso item x tenho o peso <= y, ele pega o valor(beneficio) do item x e soma (caso tenha espaco ou item ) com o melhor beneficio calculado anteriormente da matriz[x-1][y-peso do item],esse resultado
                     matriz[x][y] = maior(bagagem.valor[x-1]+ matriz[x-1][y-bagagem.peso[x-1]],matriz[x-1][y]);// ele verifica se e maior , que o melhor resultado da matriz[x-1][y] (matriz que possui outra combinacao de itens,porem mesmo peso),caso sim atribui valor calculado ao ponto , caso nao atribiu o outro valor.
                }else{
                    matriz[x][y] = matriz[x-1][y];// caso o valor do item x seja maior q o peso y , a combinacao de maior beneficio dos itens anteriores calculada e atribuida.
                }
            }
        }
        
    } // retorna o ultimo ponto da matriz , que representa o maior valor(beneficio) possivel
    return matriz[aux][PesoMax];
}

void mochila_heurastica_maiorvalor(int PesoMax,item bagagem, int aux){ //Paramentros: Pesomaixmo , struct que contem as informacoes as dos items, aux = Numero de Items
    int *vetor = (int*) calloc(aux,sizeof(int));
    int maior;          //A funcao heurastica de maior valor funciona procurando o item de maior valor(benefico) disponivel no vetor, quando localizado
    int x,y;            //o valor e salvo, e esse valor salvo e feito uma procura dele no vetor afim de localizar sua posicao ou posicoes no vetor,
    int i = 0;          //para que um vetor auxiliar binaria seja feito salvando essas posicoes , depois e feito novamente com todos os  proximo maior valor ,ate 
    int regula = PesoMax;// que o vetor binario atinja o capacidade maxima , deixando de incluir novos items.
    int jafoi= 5000;
    while( i < aux){            
        maior = 0;                
        for(x=0; x < aux; x++){ //percorre o vetor 
            if (bagagem.valor[x] > maior && bagagem.valor[x] < jafoi){ // verfica se o item x possui o maior valor
                maior = bagagem.valor[x]; //define o maior valor 
            }
        }
        for(y=0; y < aux; y++){// percorre o vetor
            if(bagagem.valor[y] == maior){ // verifica se o item y e igual ao maior valor
                if(regula - bagagem.peso[y] >= 0){//verifica se a mochila tem espaco
                    vetor[y] = 1; // altera o vetor binario
                    regula = regula - bagagem.peso[y];// diminui o pesomax da mochila pois foi inserido um item
                }
                
            } 
        }
        jafoi = maior; // salva o maior valor utilizado para nao ser repetido
        i++;
    }
    //imprime_vetor(vetor,bagagem, aux, PesoMax);
    free(vetor);
}

void mochila_heurastica_pesobeneficio(int PesoMax,item bagagem, int aux){//Paramentros: Pesomaixmo , struct que contem as informacoes as dos items, aux = Numero de Items
    int *vetor = (int*) calloc(aux,sizeof(int));
    float meio = 0;
    int x,y;             //A funcao heurastica de maior pesobeneficio funciona procurando o item que a divisao do beneficio/peso disponivel no vetor seja a maior, quando localizado
    float z,w;          //o valor e salvo, e esse valor salvo e feito uma procura dele no por items que possuam o valor da relacao fim de localizar sua posicao ou posicoes no vetor,
    float m,n,k,l;      //para que um vetor auxiliar binaria seja feito salvando essas posicoes , depois e feito novamente com todos os  proximos maior valor que e menor que os ja utilizado valor ,ate 
    int i = 0;          // que o vetor binario atinja o capacidade maxima de peso , deixando de incluir novos items.
    int regula = PesoMax;
    float jafoi= 100;
    while( i < aux){//repete a quantidade de numero de items 
        meio = 0;
        for(x=0; x < aux; x++){//percorre os vetores  peso e valor, calculando a relacao beneficio/peso
            m = bagagem.valor[x];
            n = bagagem.peso[x];
            z = m/n;
            if (z > meio && z < jafoi){ // caso a relacao beneficio peso do item x seja a maior ela e salva
                meio = z;
            }
        }
        for(y=0; y < aux; y++){//percorre os vetores  peso e valor, calculando a relacao beneficio/peso
            k = bagagem.valor[y];
            l = bagagem.peso[y];
            w = k/l;
            if(w == meio){ // caso a relacao seja igual a maior definida anteriormente verifica se o item pode ser inserido no vetor binario
                if(regula - bagagem.peso[y] >= 0){ // verifica se o vetor binario possui capacidade para receber o item
                    vetor[y] = 1; // caso sim altera a posicao para 1 
                    regula = regula - bagagem.peso[y]; //diminui a capacidade da mochila pois o item foi inserido
                }
                
            } 
        }
        jafoi = meio; // valor maior utilizado na iteracao 
        i++;
    }
    //imprime_vetor(vetor,bagagem, aux, PesoMax);
    free(vetor);
}
    
void mochila_heurastica_menorpeso(int PesoMax,item bagagem, int aux){//Paramentros: Pesomaixmo , struct que contem as informacoes as dos items, aux = Numero de Items
    int *vetor = (int*) calloc(aux,sizeof(int));
    int menor;                       //A funcao heurastica de maior valor funciona procurando o item de memnor peso  disponivel no vetor, quando localizado
    int x,y;                        //o valor e salvo, e esse valor salvo e feito uma procura dele no vetor afim de localizar sua posicao ou posicoes dos items no vetor,
    int i = 0;                      //para que um vetor auxiliar binaria seja feito salvando essas posicoes , depois e feito novamente com todos os  proximos menores pesos que e maior que os ja utilizado ,ate 
    int regula = PesoMax;           // que o vetor binario atinja o capacidade maxima de peso , deixando de incluir novos items.
    int jafoi=0;
    while( i < aux){// repete a quantidade de numero de itens 
        menor = 500;
        for(x=0; x < aux; x++){// percorre todo vetor 
            if (bagagem.peso[x]<menor && bagagem.peso[x] > jafoi){ //verifica peso do item x e o menor peso
                menor = bagagem.peso[x];
            }
        }
        for(y=0; y < aux; y++){// percorre todo vetor 
            if(bagagem.peso[y] == menor){ // verifca se o item y possui peso = ao menor peso
                if(regula - bagagem.peso[y] >= 0){
                    vetor[y] = 1; //muda o vetor binario
                    regula = regula - bagagem.peso[y]; // diminui a capacidade da mochila , pois inseriu um item
                }
                
            } 
        }
        jafoi = menor;// salva o menor valor utilizado para nao ser repetido
        i++;
    }
    //imprime_vetor(vetor,bagagem, aux, PesoMax);
    free(vetor);
}

int verifica_vetor(int PesoMax, item bagagem, int vetor[],int aux){//Parametros: Pesomaximo,struct que possui descricao dos items, vetor binario, numero de items
    int somapeso = 0;
    int x;
    for(x=0;x < aux; x++){          // A funcao tem como objetivo ler um vetor binario e verificar se a somatoria do peso dos items selecionados  possui um peso maior que a 
        if (vetor[x] == 1){         // capacidade da mochila , caso tenha um peso menor retornara 1 , caso tenha ultrapassado 0.
            somapeso = somapeso + bagagem.peso[x];
        }
    }
    
    if(somapeso > PesoMax){
        return 0;
    }else{
        
        return 1;
    }
}

int calcula_valor(item bagagem, int vetor[], int aux){//Parametros struct dos item, vetor binario ,numero de items
    int x; 
    int somavalor = 0;
    //ler todas as posicoes do vetor 
    for (x=0; x <aux ;x++){
        if(vetor[x] == 1) // caso o vetor tenha valor = 1 , considera o item inserido e realiza a somatoria do seu valor 
            somavalor = somavalor + bagagem.valor[x];
    }
    //retorna a somatoria dos valor(beneficios) do vetor 
    return somavalor;
}

int calcula_peso(item bagagem, int vetor[], int aux){//Parametros struct dos item, vetor binario ,numero de items
    int x; 
    int somapeso = 0;
    //ler todas as posicoes do vetor 
    for (x=0; x <aux ;x++){
        if(vetor[x] == 1){ // caso o vetor tenha valor = 1 , considera o item inserido e realiza a somatoria do seu peso
            somapeso = somapeso + bagagem.peso[x];
        }
    }
    //retorna a somatoria do peso
    return somapeso;
}

void mochila_aleatoria(int PesoMax, item bagagem, int aux, int vezes){//Parametros:PesoMax, struct dos items, numero de items, quantidade de repeticoes
    int i=0;
    int vetor[aux];
    int verifica;
    int valor1;
    int x,z;
    int maiorvalor = 0;
    int maiorvetor[aux];
    srand( (unsigned)time(NULL) );
    
        
    while(i < vezes){ // o programa ira rodar quantas vezes foi definido 
        
        for(x = 0; x < aux; x++){//percorre todo um vetor e preenche ele de forma aleatoria com 0 -1
            vetor[x] = rand() % 2;
        }  
        
        verifica = verifica_vetor(PesoMax,bagagem,vetor,aux);//verifica se o vetor gerado possui peso <=PesoMax
        
        if (verifica == 1){//Caso o vetor tenha peso adequado  calcula a somatoria do  valor(beneficio) que possui
            valor1 = calcula_valor(bagagem,vetor,aux);
            if(valor1 > maiorvalor){//Caso o a somatoria do vetor aleatoria seja maior que a de um outro vetor aleatorio ja feito
                maiorvalor = valor1;//o vetor passa a ser o maiorvetor aleatorio feito, e seu vetor binario e salvo
                for(z=0;z<aux;z++){
                    maiorvetor[z] = vetor[z];
                }
            }
        }
        i++;
    }
    //quando o limite de repeticoes e atingido imprime o maior vetor gerado
    //imprime_vetor(maiorvetor,bagagem, aux, PesoMax);
}

void imprime_vetor(int vetor[],item bagagem, int aux ,int pesomax){//Parametros: vetor binario, struct dos items , numero de items ,Peso Maximo
    int x,y,z;
    int somapeso = 0;
    printf("\nO Peso Maximo = %d",pesomax);// imprime o peso maximo
    printf("\nO vetor solucao = ");
    for(x = 0; x< aux; x++){ // percorre o vetor binario e o imprime 
        printf("%d",vetor[x]);
    }
    printf("\nPeso total = %d",calcula_peso(bagagem,vetor,aux)); // imprime a somatoria dos pesos do vetor binario  
    
    printf("\nValor total = %d",calcula_valor(bagagem,vetor,aux)); // imprime a somatoria dos valores do vetor binario
   
}

    
void aloca_memoria(item *bagagem){
    bagagem->peso =(int*) malloc(bagagem->Quant*sizeof(int)); //aloca memoria para para os pesos, conforme a quantidade de itens
    bagagem->valor =(int*) malloc(bagagem->Quant*sizeof(int)); // aloca memoria para para os valores, conforme a quantidade de itens
    if (bagagem->peso == NULL) {
        printf ("Nao alocado peso!\n");
        exit (EXIT_FAILURE);
    }
    if (bagagem->valor == NULL) {
        printf ("Nao alocado valor !\n");
        exit (EXIT_FAILURE);
   }
}
void libera_memoria(item *bagagem){
    free(bagagem->peso);
    free(bagagem->valor);
}


void imprimir(item bagagem){
    printf("Numero de Itens = %d\n",bagagem.Quant);
    printf("Capacidade da Mochila  = %d\n",bagagem.Limite);
    for(int i = 0; i<bagagem.Quant;i++)
        printf("%d ",bagagem.peso[i]);
    printf("\n");
    for(int i = 0; i<bagagem.Quant;i++)
        printf("%d ",bagagem.valor[i]);    
        
}

void abrir_arquivo(char *path, item *bagagem){
     // criando a variável ponteiro para o arquivo
    FILE *pont_arq;
    int valor; //variável para leitura de cada valor
    
    //abrindo o arquivo para leitura - ceminho do arquivo em path e modo r(ead)
    pont_arq = fopen(path, "r");
    
    // verificando se arquivo foi aberto com sucesso
    if (pont_arq == NULL){
        printf("ERRO! O arquivo não foi aberto!\n");
        exit (EXIT_FAILURE);
    }
    // o primero valor lido é o valor do peso maximo da mochila
    fscanf(pont_arq,"%d",&valor);
    bagagem-> Limite = valor;
    
    
    // o segundo valor lido e a quantidade de items 
    fscanf(pont_arq,"%d",&valor);
    bagagem->Quant=valor;
    aloca_memoria(bagagem);
    

    // se existem na valores, este vaores vão ser lidos sequencialmente
    for(int i = 0; i<bagagem->Quant;i++){
        fscanf(pont_arq,"%d",&valor);// lê os valores sequentemente da linha, um por um    
        bagagem->peso[i]=valor;// atrivui cada valor lido a posição do vetor que é retornado por endereço de memoria
    }
    for(int i = 0; i<bagagem->Quant;i++){
        fscanf(pont_arq,"%d",&valor);// lê os valores sequentemente da linha, um por um    
        bagagem->valor[i]=valor;// atrivui cada valor lido a posição do vetor que é retornado por endereço de memoria
    }
      // fechando arquivo - Nunca se esqueça!
     fclose(pont_arq);
    
    //FIM :)
}