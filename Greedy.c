/*
 Instituto Politécnico Nacional
 Escuela Superior de Cómputo
 Analisis de algoritmos
 Grupo: 3CV11
 Profesor: Benjamín Luna Benoso
 Alumno Hernández Ramírez Alan
 		Ortega Flores Marco Antonio
 Práctica No. 5
*/

#include <stdio.h>
#include <stdlib.h>
#include<time.h>

void Principal();
void llenarConjunto(int *X,int n);
void mostrarConjunto(int *X, int n);
void seleccionVoraz(int n, int *X, int *Y, int r);
void imprimirResultados(int t, int ct);
int ct;

int main(){
		system("color F0");
		printf("\n\t\t\t\t\tPractica 5: Algoritmos Voraces\n\n");
		Principal();
		return 0;
}

void Principal(){ 	
	int r, tam;
 	int *C= NULL, *S= NULL;
  	r=30;
 	
 	for(tam=0; tam<=50; tam++){
		C = (int *) malloc (sizeof(int) * (tam+1));
		S = (int *) malloc (sizeof(int) * (tam+1));
		
		if (C == NULL)
			printf("Ocurrio un error");
			
		if (S == NULL)
			printf("Ocurrio un error");
		
		llenarConjunto(C, tam+1);
		ct = 0;
		
		printf("r = %d \n", r);
		printf("Conjunto Candidatos [%d]:\n", tam+1);
		mostrarConjunto(C, tam+1);
		printf("Conjunto solucion [%d]:\n ", tam+1);
		seleccionVoraz(tam+1, C, S, r);
		printf("\n");
		imprimirResultados(tam, ct);
		
		free(C);
		free(S);
	}	
}

void llenarConjunto(int *X, int n)
{    
	int i;
	for(i=0; i<n; i++){
		if(i==0){
			X[i]=0;
		}
		else{
			X[i]= X[i-1] + rand() % (10);
			if(X[i-1]==X[i]){
				X[i]= X[i-1] + 10;
			}
		}
	}
}

void mostrarConjunto(int *X, int n){
	ct++;
	int i;
	for(i=0; i<n; i++){
		ct++; //for
		ct++;
		printf(" %d ", X[i]);
	}
	ct++;  //fin for
	
	printf("\n");
	ct++;
}

void seleccionVoraz(int n, int *X, int *Y, int r){
	ct++;
	int i, fSel, aux=0;
	ct++;
	fSel=X[0] + r;
	
	for(i=0; i<n; i++){
		ct++;
		ct++;
		
		if(X[i]==0){
			ct++; 
			Y[aux]=X[i];
			ct++;
			aux++;
		}
		ct++;
		if(X[i]>fSel){
			ct++;
			Y[aux]= X[i-1];
			ct++;
			fSel= X[i-1] + r;
			ct++;
			aux++;
		}
		ct++;
		if(X[n-1]<fSel && i==n-1){
			ct++;
			Y[aux]=X[i];
			ct++;
			aux++;
		}		
	}
	ct++;
	ct++;
	mostrarConjunto(Y, aux);
}
	
void imprimirResultados(int t, int ct){
	FILE *pf = fopen("Granjero.csv","at");
	fprintf(pf,"%d,%d\n",t,ct);
	fclose(pf);
}


