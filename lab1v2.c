#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define nthreads 5
#define tam 10

typedef struct{
    int *a, *b;
} vet;

void *quad(void *arg){
    vet *args = (vet *) arg;
    *args->a = *args->a * *args->a;
    *args->b = *args->b * *args->b;
    free(arg);
    pthread_exit(NULL);
}

int verifica(int vetor1[], int vetor2[]){
    int i;
    for(i = 0; i < tam; i++){
        vetor1[i] = vetor1[i]/vetor2[i];
    }
    for(i = 0; i < tam; i++){
        if(vetor1[i] != vetor2[i]){
            return 0;
        }
    }
    return 1;
}



int main(){
    pthread_t tid_sistema[nthreads];
    vet *args;

    int vetor[tam]; //= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i, j, vetorcopia[tam];
    j = 0;

    for(i = 0; i <tam; i++){
        scanf("%d", &vetor[i]);
    }

    for(i = 0; i < tam; i++){
        vetorcopia[i] = vetor[i];
    }

    for(i = 0; i < nthreads ; i++){
        args = malloc(sizeof(vet));
        if(nthreads>tam){
            printf("O numero de threads nao deve ser maior que o tamanho do vetor");
            exit(-2);
        }
        if(args == NULL){
            printf("ERRO");
            exit(-1);
        }
        args->a = &vetor[j];
        args->b = &vetor[j+1];

        printf("Cria thread %d\n", i);
        if(pthread_create(&tid_sistema[i], NULL, quad, (void*) args)){
            printf("ERRO");
            exit(-1);
        }
        j = j + 2;
    }
    for (int i=0; i<nthreads; i++) {
        if (pthread_join(tid_sistema[i], NULL)) {
            printf("--ERRO: pthread_join() \n"); exit(-1);
    }
  }

    for(i = 0; i<tam; i++){
        printf("%d ", vetor[i]);
    }


    if(verifica(vetor, vetorcopia)){
        printf("\nO teste foi bem sucedido");
    }
    else{
        printf("\nO teste falhou");
    }

}
