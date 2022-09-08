/*
 Instituto Politécnico Nacional
 Escuela Superior de Cómputo
 Analisis de algoritmos
 Grupo: 3CV11
 Profesor: Benjamín Luna Benoso
 Práctica No. 2
 @@@@@ Determinacion experimental de la complejidad temporal de un algoritmo @@@@@
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NoCas 45

int FiboIte(int, int*);
int FiboRec(unsigned long int, int, int, int, int, int*);

int main(int argc, char const *argv[]){
    FILE *fp;
    int i = 1;
    int Opc = 0;   
    int cnt = 0;

    fp = fopen ( "Coord.txt", "a" );      //CAMBIAR Extencion Excel
	    if (fp==NULL) {
            fputs ("File error",stderr);
        exit (1);
    }

    scanf("%d", &Opc);
    switch(Opc){
        case 1:
            while(i < NoCas){
                FiboIte(i, &cnt);
                fprintf(fp, "%d,", i);//FiboIte(i, &cnt));
                fprintf(fp, "%d\n", cnt);
                cnt = 0;
                i ++;
            }

        case 2:
            while(i < NoCas){
                FiboRec(0, i, 0, 0, 1, &cnt);
                fprintf(fp, "%d,", i);
                fprintf(fp, "%d\n", cnt);
                //cnt = 0;
                i ++;
            }
            
    }


    fclose(fp);
    return 0;
}

int FiboIte(int n, int *cnt){  //SERIE DE FIBONACCI ITRERATIVA
    unsigned long int a = 1;  (*cnt)++;  //INICIALIZACION
    unsigned long int b = 1;  (*cnt)++;  //INICIALIZACION
    unsigned long int Fib = 0;  (*cnt)++;  //INICIALIZACION

    if(n == 1 || n == 2){
        Fib = 1;
    }else{
        (*cnt)++;  //INICIALIZACION
        for (int i = 1; i < n; i++){
            (*cnt)++;  //CONDICION
            Fib = b;        (*cnt)++;  //CONDICION
            b += a;          (*cnt)++;  //CONDICION
            a = Fib;         (*cnt)++;  //CONDICION
            (*cnt)++;  //I+1 DEL FOR
        }
    }
    

    printf("%ld \n", b);
    return b;
}

int FiboRec(unsigned long int Fib, int n, int i, int a, int b, int *cnt){  //SERIE DE FIBONACCI RECURSIVA

    if(i < n){
        (*cnt)++;  //CONDICION
        //printf("%ld \n", Fib);  (*cnt)++;  //PRINT
        Fib = a + b;            (*cnt)++;  //OPERACION
        a = b;                  (*cnt)++;  //OPERACION
        b = Fib;                (*cnt)++;  //OPERACION
        (*cnt)++;  //LLAMADA FUNCION
        FiboRec(Fib, n, i+1, a, b, cnt);
    }else{
        printf("%ld \n", Fib);
        return Fib;
    }
        
}
