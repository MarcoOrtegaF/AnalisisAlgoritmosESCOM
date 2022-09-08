/*
 Instituto Politécnico Nacional
 Escuela Superior de Cómputo
 Analisis de algoritmos
 Grupo: 3CV11
 Profesor: Benjamín Luna Benoso
 Alumno Hernández Ramírez Alan
 		Ortega Flores Marco Antonio
 Práctica No. 2
 @@@@@ Determinacion experimental de la complejidad temporal de un algoritmo @@@@@
*/

#include<stdio.h>
#include<stdlib.h>

void principal();
int perfectos(int, int*);
void mostrarPerfectos(int);

int main (){
	principal();
	system("pause");
	return 0;
}

void mostrarPerfectos(int n){
	int i,contador=0;  
    int cnt = 0;
	FILE *fp;

	fp = fopen ( "CoorPer.txt", "a" );      //CAMBIAR Extencion Excel
	    if (fp==NULL) {
            fputs ("File error",stderr);
        exit (1);
    }

	printf("\n\nLos %d numeros perfectos son: ",n);
	for(i=1;contador<n;i++){
		if(perfectos(i, &cnt)==1){
			printf("%d,",i);
			fprintf(fp, "%d,", i);
            fprintf(fp, "%d\n", cnt);
			cnt = 0;
			contador++;
		}
	}
	fclose(fp);
	printf("\n\n");
}

int perfectos(int m, int *cnt){
	int contador=0; (*cnt)++;  //INICIALIZACION
	int suma=0;	(*cnt)++;  //INICIALIZACION

	(*cnt)++;  //INICIALIZACION
	for(contador=1;contador<m-1;contador++ ){
		(*cnt)++;  //CONDICION
		if (m%contador==0){
			(*cnt)++;  //IF TRUE
			(*cnt)++;  //IGUAL A
			(*cnt)++;  //SUMA
			suma=suma+contador;
		}
			(*cnt)++;  //I++
	}
		
	if(suma==m){
			(*cnt)++;  //IF TRUE
			(*cnt)++;  //RETURN
			return 1;
		}
	else{
		(*cnt)++;  //IF FALSE
		(*cnt)++;  //RETURN
			return 0;
		}
	
}

void principal()
	{
		int n;
		printf("Este programa muestra los numeros perfectos.\n\n");
		printf("Ingrese la cantidad de numeros perfectos que desea ver  ");
		scanf("%d",&n);
		mostrarPerfectos(n);
	}
