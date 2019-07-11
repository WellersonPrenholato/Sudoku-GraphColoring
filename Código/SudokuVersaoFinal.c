/*
AUTORES: WELLERSON PRENHOLATO E GUILHERME GONÇALVES
DISCIPLINA: TEORIA DOS GRAFOS
PROFESSORA: LUCIANA LEE
UNIVERSIDADE FEDERAL DO ESPÍRITO SANTO - UFES
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//Para sudoku 4x4
//#define V 16
//int ordem = 4;
//int matrizAdjacencia[16][16];

#define V 81//Número de vertices do grafo
int ordem = 9;
int matrizAdjacencia[81][81];
int cor[V];

int geraRaiz(int numero){ //Tira Raiz (Utilizado no desenvolvimento da matriz de adjacência, para encontrar as relacionamentos do quadrante)
    int auxiliar = numero/2;
    for(int n = 0; n <= auxiliar; n++){
       if((n*n) == numero)
           return n;
    }
    return 0;
}

void geraMatrizAdjacencia(){ //Gera a matriz de adjacências 
int numeroVertices = (ordem * ordem);
int raiz = geraRaiz(ordem);
    for (int i = 0; i <numeroVertices; i++){
        for(int j = 0; j < numeroVertices; j++){
            if(j >= (i/ordem)*ordem && j < (i/ordem)*ordem + ordem)
                matrizAdjacencia[i][j] = 1; //VERIFICA EM LINHA (REFERENTE A OUTRO QUADRANTE)
            else if(j%ordem == i%ordem)
                matrizAdjacencia[i][j] = 1; //VERIFICA COLUNA (REFERENTE A OUTRO QUADRANTE)
            else
                matrizAdjacencia[i][j] = 0; //CASO NAO ATENDA OS CASOS ANTERIORES
        }
    }

    for (int i = 0; i < numeroVertices; i++){
        for(int f = 0; f < raiz;f++){
            for(int k = 0; k < raiz; k++){
                if((i/ordem)%raiz == 0 )
                    for(int j =0; j < raiz; j ++){
                        matrizAdjacencia[i+ordem*f][(i/raiz)*raiz+j + ordem*k] = 1; //VERIFICA LINHA E COLUNA (DENTRO DO MESMO QUADRANTE)
                    }
            }
       }
    }

    //ENCONTRA A DIAGONAL PRINCIPAL
    for (int i=0; i<numeroVertices; i++){
        for(int j=0; j<numeroVertices; j++){
                if (i==j){
                    matrizAdjacencia[i][j] =3;
                }
            }
        }

}

  
void printSolution(int color[]); 
void printSolution2(int color[]); 

/* Uma função de utilidade para verificar se a atribuição de cor atual
é seguro para o vértice v, ou seja, verifica se a borda existe ou não
(isto é, representar graficamente [v][i] == 1). Se existir, verifique se a cor a ser
ser preenchido no novo vértice (c é enviado no parâmetro) já está
usado pelos vértices adjacentes (i -> adjtic vertices) ou não (isto é, cor [i] == c) */
int isSafe (int v, int grafo[V][V], int color[], int c) { 
    for (int i = 0; i < V; i++) 
        if (grafo[v][i]==1 && c == color[i]) 
            return 0; 
    return 1; 
} 

/* Uma função de utilidade recursiva para resolver o problema de coloração */
int grafoColoreRecursivo(int grafo[V][V], int m, int color[], int v) { //Matriz - Número de cores - Vetor de cores (Resposta) - Vértice
    
/* caso base: Se todos os vértices são atribuídos uma cor, então return 1 */
    if (v == V) 
        return 1; 
  
    //if utilizado para verificar a entrada dos dados, "bloqueando" a modificação das cores iniciais.
    if (color[v] != 0){
        if (grafoColoreRecursivo (grafo, m, color, v+1) == 1) {
            return 1; 
        }else {
            return 0;
        }
    }

    /* Considera vértice v e tente cores diferentes */
    for (int c = 1; c <= m; c++) { 
        /* Verifique se a atribuição da cor c a v é boa */
        if (isSafe(v, grafo, color, c)){
           //printSolution(color); //Para verificar mudança de cores
           color[v] = c; 
           
            /* Recorrente para atribuir cores ao resto dos vértices */
           if (grafoColoreRecursivo (grafo, m, color, v+1) == 1) {
                return 1; 
            }
            /* Se atribuir cor c, e não leva-lo a uma solução depois o mesmo é removido */
           color[v] = 0; 
        }
    }
     
/* Se nenhuma cor puder ser atribuída a este vértice, retorna 0 */
    return 0; 
} 


/* Esta função resolve o problema de coloração usando Backtracking.
  Utiliza principalmente grafoColoreRecursivo () para resolver o problema. 
  Devolve 0 se as m cores não podem ser atribuídas, caso contrário, retornam 1 e
  imprime atribuições de cores para todos os vértices. 
  Importante: Pode haver mais do que uma solução */
int grafoColore(int grafo[V][V], int m) { 
  
    // Chama grafoColoreRecursivo () para o vértice 0
    if (grafoColoreRecursivo(grafo, m, cor, 0) == 0) { 
      printf("\n*** NAO EXISTE SOLUCAO! ***"); 
      return 0; 
    } 
  
    // Apresenta a solução
    printf("\n*** SOLUCAO EXISTENTE! *** \n");
    printf("\n** MATRIZ DE SAIDA COM O NÚMERO MÍNIMO DE CORES = %d **", m); 
    printSolution2(cor); 
    return 1; 
} 

void printSolution2 (int color[]){
    int raiz = geraRaiz(ordem);
    for (int i = 0; i < V+1; i++){
        if (i%raiz == 0 && (i != 0)){
            printf("|");
        }
        if(i%ordem ==0){
            printf("\n");
        }
        if(i%(ordem*raiz) ==0){
            printf("---------------------------------------\n");
        }
        if (i <= V-1 ){
            printf(" %.2d ", color[i]); 
        }
      }

}

/*
void printSolution(int color[]){ 
    printf("Solucao Existente:\n"); 
    for (int i = 0; i < V; i++){
        if(i%9 ==0){
            cout << endl;
        }
      printf(" %.2d ", color[i]); 
      }
    printf("\n"); 
} */

int main (){

geraMatrizAdjacencia(); //Gera matriz de adjacência

//Leitura dos dados de entrada
for (int k=0; k<V; k++){
    scanf("%d", &cor[k]);
}

//Apresenta a matriz de entrada
printf("** MATRIZ DE ENTRADA **");
printSolution2(cor);

int m=ordem; //Número de cores
    //Chamada da função que resolve o problema
    grafoColore (matrizAdjacencia, m); 
    printf("\n");

    return 0;
}