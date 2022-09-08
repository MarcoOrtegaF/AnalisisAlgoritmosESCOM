#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BMP.h"

void traslacion(int i, int j, int i1, int j1, BMP * imagen, int n);
void rotacionClasica(BMP *, BMP * , int *);
void rotacionBaseM(int i, int j, int i1, int j1, unsigned char ** matriz, int n);
void rota90GradosDivide(int i, int j, int i1, int j1, BMP * imagen, int n, int*);

int main(int argc, char const *argv[]){
    BMP img;
    int Opc;
    int cnt = 0;
    //char IMAGEN[55];
    //char IMAGEN [] = {'m', 'o', 'n', 'a', 'l', 'i', 's', 'a', '5', '1', '2', '.', 'b', 'm', 'p'};         //CAMBIAR VARIABLE PARA PROBAR DIFERENTE BMP
    char IMAGEN [] = {'7', '.', 'b', 'm', 'p'};
	//char IMAGEN_OUT[] = {'m', 'o', 'n', 'a', 'l', 'i', 's', 'a', '5', '1', '.', 'b', 'm', 'p'};

    abrirImagen(&img, IMAGEN);

    printf("Elija una opcion\n\n1-Rotar Divide y Venceras\n2-Rotar con matrices\n");
    //scanf("%d", &Opc);
    Opc = 1;
    switch (Opc){
        case 1:
            printf("Rotando...\n");
            rota90GradosDivide(0,0,img.alto,img.ancho,&img,img.alto, &cnt);
            printf("\nCantidad de pasos = %d\n", cnt);
        break;
        case 2:
            printf("Rotando...\n");
            rotacionClasica(&img, &img, &cnt);
            printf("\nCantidad de pasos = %d\n", cnt);
        break;
    }

    guardarImagen(&img, IMAGEN);
    return 0;
}

void abrirImagen(BMP* imagen, char* ruta) {
    FILE *archivo; //Puntero FILE para el archivo de imágen a abrir
    int i, j, k, resto;
    unsigned char R, B, G, var;

    //Abrir el archivo de imágen
    archivo = fopen(ruta, "rb+");
    if (!archivo) {
        //Si la imágen no se encuentra en la ruta dada
        printf("La imágen %s no se encontro\n", ruta);
        exit(1);
    }

    //Leer la cabecera de la imagen y almacenarla en la estructura global img
    fseek(archivo, 0, SEEK_SET);
    fread(&imagen->bm, sizeof (char), 2, archivo);
    fread(&imagen->tamano, sizeof (int), 1, archivo);
    fread(&imagen->reservado, sizeof (int), 1, archivo);
    fread(&imagen->offset, sizeof (int), 1, archivo);
    fread(&imagen->tamanoMetadatos, sizeof (int), 1, archivo);
    fread(&imagen->alto, sizeof (int), 1, archivo);
    fread(&imagen->ancho, sizeof (int), 1, archivo);
    fread(&imagen->numeroPlanos, sizeof (short int), 1, archivo);
    fread(&imagen->profundidadColor, sizeof (short int), 1, archivo);
    fread(&imagen->tipoCompresion, sizeof (int), 1, archivo);
    fread(&imagen->tamanoEstructura, sizeof (int), 1, archivo);
    fread(&imagen->pxmh, sizeof (int), 1, archivo);
    fread(&imagen->pxmv, sizeof (int), 1, archivo);
    fread(&imagen->coloresUsados, sizeof (int), 1, archivo);
    fread(&imagen->coloresImportantes, sizeof (int), 1, archivo);

    //Validar ciertos datos de la cabecera de la imágen	
    if (imagen->bm[0] != 'B' || imagen->bm[1] != 'M') {
        printf("La imagen debe ser un bitmap.\n");
        exit(1);
    }
    if (imagen->profundidadColor != 24) {
        printf("La imagen debe ser de 24 bits.\n");
        exit(1);
    }

    //*********************************************************************************************************
    //Colocar el cursor en el byte (offset) donde comienzan los datos de la imagen
    //*********************************************************************************************************
    fseek(archivo, imagen->offset, SEEK_SET);

    //*********************************************************************************************************
    //Reservar memoria para el arreglo que tendra los planos RGB de la imagen (Arreglo de tamaño "img.ancho X img.alto")
    //*********************************************************************************************************
    imagen->pixelR = malloc(imagen->alto * sizeof (char *));
    imagen->pixelG = malloc(imagen->alto * sizeof (char *));
    imagen->pixelB = malloc(imagen->alto * sizeof (char *));
    for (i = 0; i < imagen->alto; i++) {
        imagen->pixelR[i] = malloc(imagen->ancho * sizeof (char));
        imagen->pixelG[i] = malloc(imagen->ancho * sizeof (char));
        imagen->pixelB[i] = malloc(imagen->ancho * sizeof (char));
    }

    //*********************************************************************************************************
    //Padding (Bytes necesarios para que el Pad row alcance a ser multiplo de 4 Bytes)		
    //*********************************************************************************************************
    resto = (imagen->ancho * 3) % 4;
    if (resto != 0)
        resto = 4 - resto;

    //*********************************************************************************************************
    //Pasar la imágen a el arreglo reservado en escala de grises
    //*********************************************************************************************************
    //Iterar a través de las filas de píxeles, teniendo en cuenta que los datos comienza en la esquina inferior izquierda de la imagen BMP
    for (i = imagen->alto - 1; i >= 0; i--) {
        for (j = 0; j < imagen->ancho; j++) {
            fread(&B, sizeof (char), 1, archivo); //Byte Blue del pixel
            fread(&G, sizeof (char), 1, archivo); //Byte Green del pixel
            fread(&R, sizeof (char), 1, archivo); //Byte Red del pixel
            imagen->pixelR[i][j] = R;
            imagen->pixelG[i][j] = G;
            imagen->pixelB[i][j] = B;
        }

        //Padding (Bytes necesarios para que el Pad row alcance a ser multiplo de 4 Bytes)		
        for (k = 1; k <= resto; k++) {
            fread(&var, sizeof (char), 1, archivo); //Leer los pixeles de relleno (Padding)
        }
    }
    //Cerrrar el archivo
    fclose(archivo);
}

/**
 * Función encargada de rotar una imagen usando el algoritmo clásico
 * @param imagenOriginal La imagen original a ser tratada
 * @param imagenTratada Estructura en el que se guardará la imagen tratada
 */
void rotacionClasica(BMP *imagenOriginal, BMP * imagenTratada, int *cnt) {
    int i;                      (*cnt)++;  //DECLARACION
    int j;                      (*cnt)++;  //DECLARACION
    int n = imagenOriginal->alto;   (*cnt)++;  //DECLARACION

    (*cnt)++;  //INICIALIZACION
    for (i = 0; i < n; i++) {   
        (*cnt)++;  //CONDICION
        (*cnt)++;  //INICIALIZACION
        for (j = 0; j < n; j++) {   
            (*cnt)++;  //CONDICION
            imagenTratada->pixelR[j][n - 1 - i] = imagenOriginal->pixelR[i][j];         (*cnt)++;  //IGUALDAD
            imagenTratada->pixelG[j][n - 1 - i] = imagenOriginal->pixelG[i][j];         (*cnt)++;  //IGUALDAD
            imagenTratada->pixelB[j][n - 1 - i] = imagenOriginal->pixelB[i][j];         (*cnt)++;  //IGUALDAD
        }
        (*cnt)++; //INCREMENTO j
    }
    (*cnt)++; //INCREMENTO I
}

/**
 * Función encargada de rotar una imagen la cantidad de grados especificada mediante el uso de un algoritmo con la técnica 
 * divide y vencerás
 * @param i El inicio del rango a tratar
 * @param j El inicio del rango a tratar
 * @param i1 El final del rango a tratar
 * @param j1 El final del rango a tratar
 * @param imagen La imagen original a ser tratada
 * @param n El tamaño del problema
 */
void rota90GradosDivide(int i, int j, int i1, int j1, BMP * imagen, int n, int* cnt) {
    (*cnt)++;  //IF
    if (n > 1) { 
        (*cnt)++;  //IF TRUE
        rota90GradosDivide(i, j, (n / 2) + i, (n / 2) + j, imagen, n / 2, cnt);              (*cnt)++;  //LLAMADA
        rota90GradosDivide(i + (n / 2), j, n + i, (n / 2) + j, imagen, n / 2, cnt);          (*cnt)++;  //LLAMADA
        rota90GradosDivide(i + (n / 2), j + (n / 2), n + i, n + j, imagen, n / 2, cnt);      (*cnt)++;  //LLAMADA
        rota90GradosDivide(i, j + (n / 2), (n / 2) + i, n + j, imagen, n / 2, cnt);          (*cnt)++;  //LLAMADA
    }
    traslacion(i, j, i1, j1, imagen, n / 2);   (*cnt)++;  //FUNC
}

void traslacion(int i, int j, int i1, int j1, BMP * imagen, int n) {
    if (i < i1 - n) {
        rotacionBaseM(i, j, i1, j1, imagen->pixelB, n);
        rotacionBaseM(i, j, i1, j1, imagen->pixelR, n);
        rotacionBaseM(i, j, i1, j1, imagen->pixelG, n);
        traslacion(i + 1, j, i1, j1, imagen, n);
    }
}

/**
 * Función que aplica el algoritmo de rotación recursivo a una matriz de caracteres de forma individual
 * @param i El inicio del rango a tratar
 * @param j El inicio del rango a tratar
 * @param i1 El final del rango a tratar
 * @param j1 El final del rango a tratar
 * @param matriz La matriz a rotar
 * @param n El tamaño del problema
 */
void rotacionBaseM(int i, int j, int i1, int j1, unsigned char ** matriz, int n) {
    if (j < j1 - n) {
        char px = matriz[i][j];
        matriz[i][j] = matriz[i + n][j];
        matriz[i + n][j] = matriz[i + n][j + n];
        matriz[i + n][j + n] = matriz[i][j + n];
        matriz[i][j + n] = px;
        rotacionBaseM(i, j + 1, i1, j1, matriz, n);
    }
}

void guardarImagen(BMP *imagen, char *ruta) {
    FILE *archivo; //Puntero FILE para el archivo de imágen a abrir

    int i, j, k, resto, var;

    //Abrir el archivo de imágen
    archivo = fopen(ruta, "wb+");
    if (!archivo) {
        //Si la imágen no se encuentra en la ruta dada
        printf("La imágen %s no se pudo crear\n", ruta);
        exit(1);
    }
    //Leer la cabecera de la imagen y almacenarla en la estructura global img
    fseek(archivo, 0, SEEK_SET);
    fwrite(&imagen->bm, sizeof (char), 2, archivo);
    fwrite(&imagen->tamano, sizeof (int), 1, archivo);
    fwrite(&imagen->reservado, sizeof (int), 1, archivo);
    fwrite(&imagen->offset, sizeof (int), 1, archivo);
    fwrite(&imagen->tamanoMetadatos, sizeof (int), 1, archivo);
    fwrite(&imagen->alto, sizeof (int), 1, archivo);
    fwrite(&imagen->ancho, sizeof (int), 1, archivo);
    fwrite(&imagen->numeroPlanos, sizeof (short int), 1, archivo);
    fwrite(&imagen->profundidadColor, sizeof (short int), 1, archivo);
    fwrite(&imagen->tipoCompresion, sizeof (int), 1, archivo);
    fwrite(&imagen->tamanoEstructura, sizeof (int), 1, archivo);
    fwrite(&imagen->pxmh, sizeof (int), 1, archivo);
    fwrite(&imagen->pxmv, sizeof (int), 1, archivo);
    fwrite(&imagen->coloresUsados, sizeof (int), 1, archivo);
    fwrite(&imagen->coloresImportantes, sizeof (int), 1, archivo);

    //*********************************************************************************************************
    //Colocar el cursor en el byte (offset) donde comienzan los datos de la imagen
    //*********************************************************************************************************
    fseek(archivo, imagen->offset, SEEK_SET);

    //*********************************************************************************************************
    //Pasar la imágen del arreglo reservado en escala de grises a el archivo (Deben escribirse los valores BGR)
    //*********************************************************************************************************
    resto = (imagen->ancho * 3) % 4; //Padding (Bytes necesarios para que el Pad row alcance a ser multiplo de 4 Bytes)		
    if (resto != 0)
        resto = 4 - resto;

    //Iterar a través de las filas de píxeles, teniendo en cuenta que los datos comienza en la esquina inferior izquierda de la imagen BMP
    for (i = imagen->alto - 1; i >= 0; i--) {
        for (j = 0; j < imagen->ancho; j++) {
            //Ecribir los 3 bytes BGR al archivo BMP, en este caso todos se igualan al mismo valor (Valor del pixel en la matriz de la estructura imagen)
            fwrite(&imagen->pixelB[i][j], sizeof (char), 1, archivo); //Escribir el Byte Blue del pixel 
            fwrite(&imagen->pixelG[i][j], sizeof (char), 1, archivo); //Escribir el Byte Green del pixel
            fwrite(&imagen->pixelR[i][j], sizeof (char), 1, archivo); //Escribir el Byte Red del pixel
        }

        //Padding (Bytes necesarios para que el Pad row alcance a ser multiplo de 4 Bytes)		
        for (k = 1; k <= resto; k++)
            fwrite(&var, sizeof (char), 1, archivo); //Escribir los pixeles de relleno		
    }
    //Cerrrar el archivo
    fclose(archivo);

    printf("\nGuadado con exito...\n");
}

