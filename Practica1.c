#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Inic(int *, int);
void Imp(int *, int);
int Algoritmo(int *, int, int *);

int main(int argc, char const *argv[]){
    FILE *fp;
    int n = 0;
    int *A;
    int cnt = 0;

    printf("Ingrese el tam\n");
    /*scanf("%d", &n);
    
    if (n%2 != 0){
        printf("El tamano no es permitido\n");
        return 0;   
    }*/

    A = malloc(n * sizeof(int));

    
    while(n <= 500){
        if(n%2 == 0){
            
            Inic(A, n);
            //Imp(A, n);
            cnt = 0;

            Algoritmo(A, n, &cnt);

	        fp = fopen ( "fichero.ods", "a" );      //CAMBIAR Extencion Excel
	        if (fp==NULL) {
                fputs ("File error",stderr);
                exit (1);
            }
            
            fprintf(fp, "%d\t", n);
            fprintf(fp, "%d\n", cnt);

            //fclose(fp);
            
            printf("\n(%d, %d) \n", n, cnt);
        }
        n++;
    }
    
    return 0;
}

void Inic(int *A, int n){
    
    for (int i = 0; i < n; i++){
        //A[i] = rand() % (3*n);
        A[i] = i;       //PEOR CASO
    }
    
}

void Imp(int *A, int n){
    printf("\n");

    for (int i = 0; i < n; i++){
        if(i == n/2){
            printf("//-");
        }
        printf("[%d]-", A[i]);

    }

    printf("\n");
}

int Algoritmo(int *A, int n, int *cnt){
    (*cnt)++;  //INICIALIZACION
    for (int i = 0; i < n/2; i++){
        (*cnt)++; //CONDICION
        (*cnt)++; //INICIALIZACION 
        for (int j = n/2; j < n; j++){
            (*cnt)++; //CONDICION
            if(A[i] == A[j]){
                (*cnt)++; //CONDICION
                (*cnt)++; //PRINT
                printf("\nDato %d, Posiciones %d y %d\n", A[i], i, j);
                (*cnt)++; //RETURN
                return 1;
            }
            (*cnt)++; //ELSE
            (*cnt)++; //INCREMENTO j
        }
        (*cnt)++; //n+1 PARA FOR j
        (*cnt)++; //INCREMENTO i
    }
    (*cnt)++; //n+1 PARA FOR i
    (*cnt)++; //RETURN
    return 0;
}
