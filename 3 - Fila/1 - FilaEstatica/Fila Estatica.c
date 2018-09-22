#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM 5
typedef struct sAluno{
  char nome[100];
  int idade;
}Aluno;

typedef struct sFila{
	Aluno info[MAX_TAM];
	int ini, fim;
}Fila;

void inicializar( Fila* fila ){
  fila->ini=0;
  fila->fim=0;
}

int filaVazia( Fila* fila ){
  if( fila->ini == fila->fim )
    return 1;
  return 0;
}

int filaCheia( Fila* fila ){
  int prox = ( fila-> fim+1 ) % MAX_TAM;	   
  if (prox == fila->ini)
    return 1;
  return 0;
}

Aluno criarElemento(char nome[], int idade){
	Aluno e;
	strcpy(e.nome, nome);
	e.idade = idade;
	return e;
}

int inserirNaFila( Fila* fila , Aluno elem ){
	if ( filaCheia( fila ) ){
		return 0;
	}
	fila->info[fila->fim].idade = elem.idade;
  	strcpy(fila->info[fila->fim].nome, elem.nome);
	int prox = ( fila->fim+1 ) % MAX_TAM;
	fila->fim = prox;
	return 1;
}

Aluno removerNaFila( Fila* fila ){
  	Aluno rem = criarElemento("",-1);
	if ( filaVazia( fila ) ){
		return rem;
	}
	int prox = ( fila->ini+1 ) % MAX_TAM;
	rem = fila->info[fila->ini];
	fila->ini = prox;
	return rem;
}

void imprimirTodos( Fila* fila ){
	printf("Imprimir fila:\n");
  	if( filaVazia( fila ) ){
		return;
	}
	Fila aux;
	inicializar(&aux);	
	while ( !filaVazia(fila) ){
		printf("Nome: %s - %d\n",fila->info[fila->ini].nome,fila->info[fila->ini].idade);
		inserirNaFila(&aux, removerNaFila(fila));
	}
	while ( !filaVazia(&aux) ){
		inserirNaFila(fila, removerNaFila(&aux));
	}
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

int main (){
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
