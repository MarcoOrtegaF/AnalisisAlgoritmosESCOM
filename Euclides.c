#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NOc 1000

int Euclides(int, int, int *);
int fibonacci(int);

int main(int argc, char const *argv[]){
    int n, m, R;
    int cnt = 0;
    FILE *fp;

    srand (time(NULL));


    for (int i = 0; i < NOc; i++){
        R = rand() % (NOc);
        n = R;//fibonacci(R);
        R = rand() % (NOc);
        m = R;//fibonacci(R + 1);

        printf("n-%d, m-%d --- %d \n NoP %d\n", n, m, Euclides(n, m, &cnt), cnt);
        
        fp = fopen ( "fichero2.ods", "a" );      //CAMBIAR Extencion Excel
	        if (fp==NULL) {
                fputs ("File error",stderr);
                exit (1);
            }
        fprintf(fp, "%d\t", i);
        fprintf(fp, "%d\n", cnt);

        fclose(fp);
    }
    
    return 0;
}

int Euclides(int n, int m, int *cnt){
    int r = 0;(*cnt)++;  //INICIALIZACION

    //(*cnt)++;  //INICIALIZACION
    while (n != 0){
        (*cnt)++; //CONDICION
        r = m%n;    (*cnt)++; //CONDICION
        m = n;      (*cnt)++; //CONDICION
        n = r;      (*cnt)++; //CONDICION
    }
    (*cnt)++; //RETURN
    return m;
}

int fibonacci(int n){
    int a = 0;
    int b = 1;
    int r;

    for (int i = 0; i < n; i++){
        r = a + b;
        a = b;
        b = r;
    }
    
    return r;
}