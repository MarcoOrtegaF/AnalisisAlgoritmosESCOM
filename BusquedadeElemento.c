/*
 Instituto Politécnico Nacional
 Escuela Superior de Cómputo
 Analisis de algoritmos
 Grupo: 3CV11
 Profesor: Benjamín Luna Benoso
        Alumno Hernández Ramírez Alan
 		Ortega Flores Marco Antonio
 Práctica No. 3
 @@@@@ Busqueda de un elemento en un arreglo en bloques de 3 en 3 @@@@@
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int Div1(int, int, int, int *);
int Div2(int, int, int, int *);
int Div3(int, int, int, int *);
void Inic(int *, int);
void Imp(int *, int);
int Algoritmo(int *, int, int, int *);
int AlgoritmoRec(int *, int, int, int, int, int, int *);


int main(int argc, char const *argv[]){
    int opc = 0;
    int cnt = 0;
    int n = 50;      //NUMERO QUE BUSCAMOS
    int Tam = 3;
    int *A;
    FILE *fp;
    
    fp = fopen ( "Coord.txt", "a" );      //CAMBIAR Extencion Excel
	    if (fp==NULL) {
            fputs ("File error",stderr);
        exit (1);
    }

    scanf("%d",&opc);


    switch(opc){
        case 1:
            printf("D1: %d\n", Div1(10000, 25, 0, &cnt));
            printf("%d\n", cnt);
        break;
        case 2:
            printf("D2: %d\n", Div2(10000, 25, 0, &cnt));
            printf("%d\n", cnt);
        break;
        case 3:
            printf("D3: %d\n", Div3(10000, 25, 0, &cnt));
            printf("%d\n", cnt);
        break;
        case 4:                             //ALGORITMO DE BUSQUEDA ITERATIVO
            for (int i = 3; i < 300; i+=3){
                Tam = i;
                A = malloc(Tam * sizeof(int));

                Inic(A, Tam);
                Imp(A, Tam);
                printf("\nNum %d, Index: %d", (3*Tam)+1, Algoritmo(A, (3*Tam)+1, Tam, &cnt) + 1);        //PEOR CASO ES 3N+1
                printf("\nTam %d\tCnt %d\n", Tam, cnt);
                fprintf(fp, "%d,", Tam);          //ALG TAMANIO, CNT
                fprintf(fp, "%d\n", cnt);
                cnt = 0;
                free(A);
            }
            
        break;
        case 5:                             //ALGORITMO DE BUSQUEDA RECURSIVO
            for (int i = 3; i < 300; i+=3){
                Tam = i;
                A = malloc(Tam * sizeof(int));
                Inic(A, Tam);
                Imp(A, Tam);
                int lim = Tam/3;
                int i = lim;
                int j = lim;
                printf("\nIndex: %d\n", AlgoritmoRec(A, (3*Tam)+1, Tam, i, j, lim, &cnt) + 1);
                fprintf(fp, "%d,", Tam);          //ALG TAMANIO, CNT
                fprintf(fp, "%d\n", cnt);
                cnt = 0;
                free(A);
            }
        break;
    }
        
    fclose(fp);
    return 0;
}

int Div1(int n, int div, int res, int *cnt){
    int q = 0;              (*cnt)++;  //INICIALIZACION
                            //(*cnt)++;  //INICIALIZACION
    while (n >= div){       (*cnt)++;  //CONDICION
        n = n-div;          (*cnt)++;  //OPERACION
        q = q+1;            (*cnt)++;  //OPERACION
    }

    res = n;                (*cnt)++;  //OPERACION
                            (*cnt)++;  //RETURN
    return q;
}

int Div2(int n, int div, int res, int *cnt){
    int dd = div;       (*cnt)++;  //INICIALIZACION
    int q = 0;          (*cnt)++;  //INICIALIZACION
    int r = n;          (*cnt)++;  //INICIALIZACION


    while (dd <= n){    (*cnt)++;  //CONDICION
        dd = 2*dd;      (*cnt)++;  //OPERACION
    }                   (*cnt)++;  //WHILE FALSE
    while (dd > div){   (*cnt)++;  //CONDICION
        dd = dd/2;      (*cnt)++;  //OPERACION
        q = 2*q;        (*cnt)++;  //OPERACION
        if ( dd<= r){   
                        (*cnt)++;  //IF TRUE
            r = r-dd;   (*cnt)++;  //OPERACION
            q = q+1;    (*cnt)++;  //OPERACION
        }
                        (*cnt)++;  //IF FALSE
                        (*cnt)++;  //WHILE FALSE
    }
                        (*cnt)++;  //RETURN
    return q;
}

int Div3(int n, int div, int res, int *cnt){
    int q = 0;          (*cnt)++;  //INICIALIZACION

    if (div > n){
                        (*cnt)++;  //IF TRUE
                        (*cnt)++;  //RETURN
        return 0;
    }else{
                        (*cnt)++;  //IF FALSE
                        (*cnt)++;  //OPERACION DENTRO DEL RETURN
                        (*cnt)++;  //RETURN
        return 1 + Div3(n-div, div, res, cnt);
    }
                        (*cnt)++;  //RETURN
    return q;
}


void Inic(int *A, int n){
    srand (getpid());
    
    for (int i = 0; i < n; i++){
        A[i] = 0;
    }

    for (int i = 0; i < n; i++){
        A[i] = rand() % (3*n);
        //A[i] = i;       //PEOR CASO
    }
    
}

void Imp(int *A, int n){
    printf("\n");
    int j = 1;

    for (int i = 0; i < n; i++){
        if(i == (j * (n/3))){
            printf("//-");
            j ++;
        }
        printf("[%d]-", A[i]);

    }

    printf("\n");
}

int Algoritmo(int *A, int n, int Tam, int *cnt){
    int lim = Tam/3;            (*cnt)++;  //INICIALIZACION
    int i = lim;                (*cnt)++;  //INICIALIZACION
    int j = lim;                (*cnt)++;  //INICIALIZACION

    (*cnt)++;  //CONDICION
    while (i < 2*lim){  

        if (A[i] == n){
            (*cnt)++;  //IF TRUE
            (*cnt)++;  //RETURN
            return i;
        }else (*cnt)++;  //IF FALSE 
        if (A[j + i] == n){       
            (*cnt)++;  //IF TRUE
            (*cnt)++;  //RETURN
            return j + i;
        }else  (*cnt)++;  //IF TRUE
        if (A[i - j] == n){ 
            (*cnt)++;  //IF TRUE
            (*cnt)++;  //RETURN
            return i - j;
        }
        i ++;           (*cnt)++;  //++
        //printf("\ncnt %ls", cnt);
    }
    
    (*cnt)++;  //RETURN
    return -1;
}

int AlgoritmoRec(int *A, int n, int Tam, int i, int j, int lim, int *cnt){

    if(i < 2*lim ){
        (*cnt)++;  //IF TRUE
        if (A[i] == n){
            (*cnt)++;  //IF TRUE
            (*cnt)++;  //RETURN
            return i;
        }else (*cnt)++;  //IF FALSE
        if (A[j + i] == n){
            (*cnt)++;  //IF TRUE
            (*cnt)++;  //RETURN
            return j + i;
        }else (*cnt)++;  //IF FALSE
        if (A[i - j] == n){
            (*cnt)++;  //IF TRUE
            (*cnt)++;  //RETURN
            return i - j;
        }
        (*cnt)++;  //++
        i ++;
        (*cnt)++;  //FUNCION
        AlgoritmoRec(A, n, Tam, i, j, lim, cnt);
    }else
        (*cnt)++;  //IF FALSE
        (*cnt)++;  //RETURN
        return -1;
}
