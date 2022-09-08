#include <stdio.h>
#include <stdlib.h>
#define TmCad 100

typedef struct Nodo{
    char Name[20];       // NOMBRE ORIIGINAL
    int TknNme;      // NOMBRE DEL TOKEN 
    int TA;              // TIMES APPEARED
    struct Nodo *Next;    // NODO SIGUIENTE
}Token;

int CarDif[] = {32, 10, };
void create(Token ** Tokens);
void display(Token * Tokens);
void delete_begin(Token ** Tokens);
void delete_all(Token ** Tokens);
void Read_File(char *);
void WriteToken(char*, char * Cad, int Tam, int*);
void InicCad(char * Cad, int Tam);
void PrintLCS(char **b, char *x, int i, int j);
void LCSLeng (char *x, char *y, int Xlen, int YLen);
void Compare();

int main(int argc, char const *argv[]){
    Token *Tokens;
    char sal;
    char NomFile[20];
    Tokens = (Token *)malloc(sizeof(Token));
    Tokens = NULL;

    
    //scanf("%c", &sal);
    //printf("Sas%csas, %d", sal, sal);
    /*for (int i = 0; i < 10; i++){
        create(&Tokens);
    }
    
    display(Tokens);
    delete_all(&Tokens);*/
    Read_File("Input.txt");

    Compare();

    return 0;
}

void Compare(){
    FILE *Input;
    FILE *Input2;
    char X[1024];
    char Y[1024];

    Input = fopen ( "Output1.txt", "r" );
	    if (Input == NULL) {
            fputs ("File error - Input1",stderr);
        exit (1);
    }

    fgets(X, 1024, Input);
    printf("1");   

    fclose(Input);

    Input2 = fopen ( "Output2.txt", "r" );
	    if (Input == NULL) {
            fputs ("File error - Input2",stderr);
        exit (1);
    }

    fgets(Y, 1024, Input);
    fclose(Input2);
    LCSLeng(X, Y, 1024, 1024);
    printf("2");   
}

void Read_File(char * FName){
    FILE *Input;
    char in[TmCad];
    char aux;
    int Entr = 0;
    int j = 0;

    InicCad(in, TmCad);

    Input = fopen ( "Input.txt", "r" );
	    if (Input == NULL) {
            fputs ("File error - Input",stderr);
        exit (1);
    }

    do{
        aux = fgetc( Input );

        if (aux != 9 && aux != 32 && aux != 10 && aux != 4 && aux != 40 && aux != 41 && aux != 44 && aux != 59){        //OPCIONES DE EXCLUSION
            in[j] = aux;
            j++;
        }else{
            WriteToken("Output.txt", in, j, &Entr);
            InicCad(in, TmCad);
            j = 0;
            Entr ++;
        }

    } while (aux != EOF);
    
    fclose(Input);
}

void WriteToken(char* Fname, char * Cad, int Tam, int *Entr){
    FILE *Output;
    int Sum = 0;
    char* salida;

    Output = fopen ( "Output.txt", "a" );
	    if (Output == NULL) {
            fputs ("File error - Output",stderr);
        exit (1);
    }
    for (int i = 0; i < Tam; i++){
        Sum += Cad[i];
    }

    Sum += Cad[0];
    Sum += Cad[Tam];

    printf("%x- ", Sum);
    printf("-");
    puts(Cad);
    fprintf(Output, "%x-", Sum);

    if((*Entr) == 10){
        fprintf(Output, "\n");
        (*Entr) = 0;
    }

    fclose(Output);
}


void InicCad(char * Cad, int Tam){

    for (int i = 0; i < Tam; i++){
        Cad[i] = 0;
    }
    
}

void LCSLeng (char *x, char *y, int Xlen, int YLen){
    int m = Xlen;
    int n = YLen;

    char b[m - 1][n - 1];
    char c[m][n];

    for (int  i = 0; i < m; i++){
        c[i][0] = 0;
    printf("1");   
    }
    for (int i = 0; i < n; i++){
        c[0][i] = 0;
    printf("-%d", i);   
    }
    
    for (int i = 0; i < m-1; i++){
        for (int j = 0; i < n-1; i++){
            if (x[i] == y[j]){
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 92;
            }else if(c[i - 1][j] >= c[i][ j - 1]){
                c[i][j] = c[i - 1][j];
                b[i][j] = '|';
            }else{
                c[i][j] = c[i][j - 1];
                b[i][j] = '-';
            }
        }
    }

    PrintLCS((char *)b, x, Xlen, YLen);
}
    //void PrintLCS(b, x, Xlen, YLen){
void PrintLCS(char **b, char *x, int i, int j){
    if(i == 0 || j == 0){
        
    }
    if(b[i][j] == 92){
        PrintLCS(b, x, i-1, j-1);
        puts(x);
    }else if(b[i][j] == '|'){
        PrintLCS(b, x, i-1, j);
    }else{
        PrintLCS(b, x, i, j-1);
    }
}

//------------------------------
void create(Token ** Tokens){
    Token *temp,*ptr;
    temp = (Token *)malloc(sizeof(Token));

    if(temp==NULL){
        printf("Out of Memory Space:\n");
        exit(0);
    }

    //scanf("%d", &temp->TknNme);
    //strcpy(temp->Name, Name);
    //temp->Name = Name;
    temp->TA = 0;
    temp->Next = NULL;
    
    if((*Tokens) == NULL){
        temp->TknNme = 42;
        (*Tokens) = temp;
    }
    else{
        //temp->TknNme = (*Tokens)->TknNme + 1;
        ptr = (*Tokens);
        while(ptr->Next != NULL){
            ptr = ptr->Next;
        }
        ptr->Next = temp;
    }
}

void delete_begin(Token ** Tokens){
    Token *ptr;

    if((*Tokens) == NULL){
        printf("nList is Empty:n");
        return;
    }
    else{
        ptr = (*Tokens);
        (*Tokens) = (*Tokens)->Next;
        printf("The deleted element is :\t%d\n", ptr->TknNme);
        free(ptr);
    }
}

void delete_all(Token ** Tokens){
    Token *ptr;

    while ((*Tokens) != NULL){
        ptr = (*Tokens);
        (*Tokens) = (*Tokens)->Next;
        printf("The deleted element is :\t%d\n", ptr->TknNme);
        free(ptr);
    }
}

void display(Token * Tokens){
    Token *ptr;

    if(Tokens == NULL){
        printf("List is empty:\n");
        return;
    }
    else{
        ptr = Tokens;
        printf("The List elements are:\n");
        while(ptr != NULL){
            //puts(ptr->Name);
            printf("%d -> ",ptr->TknNme);
            ptr=ptr->Next;
        }
    }
}