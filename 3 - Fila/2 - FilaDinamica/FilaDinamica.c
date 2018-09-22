#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sAluno{
  char nome[100];
  int idade;
}Aluno;

typedef struct sCelula{
	Aluno info;
	struct sCelula *next;
}Celula;

typedef struct sFila{
	Celula* ini;
	Celula* fim;
}Fila;

void inicializar( Fila* fila ){
     fila->ini = NULL;
     fila->fim = NULL;
}

int filaVazia( Fila* fila ){
	if( fila->ini == NULL && fila->fim == NULL )
		return 1;
	return 0;
}

Celula* criarCelula(){
	return (Celula*) malloc (sizeof(Celula));
}

Aluno criarElemento(char nome[], int idade){
	Aluno e;
	strcpy(e.nome, nome);
	e.idade = idade;
	return e;
}

int inserirNaFila( Fila* fila , Aluno inserido){
    Celula *nova = criarCelula();
    if( nova == NULL ){ return 0; }
    nova->info = criarElemento( inserido.nome, inserido.idade );
    nova->next = NULL;
    if( fila->ini == NULL && fila->fim == NULL ){
        fila->ini = nova;
        fila->fim = nova;
        return 1;
	}	
	fila->fim->next = nova;
	fila->fim = nova;
    return 1;
}

Aluno removerNaFila( Fila* fila ){
    Aluno removido = criarElemento("",-1);
    if( fila->ini == NULL && fila->fim == NULL ){return removido;}
    if( fila->ini == fila->fim ){
    	removido =  criarElemento(fila->fim->info.nome,fila->fim->info.idade);
        fila->ini = NULL;
        fila->fim = NULL;
        return removido;
	}
	Celula* removida = fila->ini;
	removido = criarElemento(fila->ini->info.nome,fila->ini->info.idade);
    fila->ini = fila->ini->next;
    return removido;
}

void Menu (){
    printf("\n::INSERIR\n");
    printf("  [1] - Enfileirar\n");
    
    printf("\n::REMOVER\n");
    printf("  [2] - Desenfileirar\n");
    
    printf("\n::MOSTRAR\n");
    printf("  [3] - Imprimir\n\n");
    
    printf("::SAIR\n");
    printf("  [0] - Sair\n\n");
}

void imprimirTodos( Fila* fila ){
	printf("Imprimir fila:\n");
  	if( filaVazia( fila ) ){
		return;
	}
	Fila aux;
	inicializar(&aux);	
	while ( !filaVazia( fila ) ){
		printf("Nome: %s - %d\n",(fila->ini)->info.nome,(fila->ini)->info.idade);
		inserirNaFila(&aux, removerNaFila(fila));
	}
	while ( !filaVazia(&aux) ){
		inserirNaFila(fila, removerNaFila(&aux));
	}
}

int main(){
	Aluno e;
	Fila fila;
	inicializar(&fila);
	int option;
	do{
		Menu();
		printf("Digite uma opcao: ");
		scanf("%d", &option);
		fflush(stdin);
		system("cls");
		switch (option){
			case 0:
				return;
			case 1:
				printf("-------  ENFILEIRANDO  ------\n\n");
				printf("Digite o nome: ");
				scanf("%s", e.nome);				
				printf("Digite o idade: ");
				scanf("%d", &e.idade);			
				if( inserirNaFila(&fila, e) ){
					printf("\nAluno inserido :)\n");
				}else{
					printf("\nOcorreu um erro :(");
				}
				break;
			case 2:
				printf("-------  DESENFILEIRANDO  ------\n\n");
				e = removerNaFila( &fila );
				if(e.idade != -1){
					printf("\nAluno retirado: %s\n",e.nome);
				}else{
					printf("\nfila Vazia :(\n");
				}
				imprimirTodos( &fila );
				break;
			case 3:
				imprimirTodos( &fila );
				break;
			default:
				printf("Opcao invalida!");
		}
		printf("\n");
	}while(1);
	return 0;
}
