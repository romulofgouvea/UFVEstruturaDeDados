#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_TAM 5

typedef struct sAluno{
  char nome[100];
  int idade;
}Aluno;

typedef struct sDeque{
	Aluno info[MAX_TAM];
 	int ultimo;
 	int cabecalho;
}Deque;

void inicializar( Deque* deque ){
 	deque->ultimo = 0;
 	deque->cabecalho = 0;
 }
 
 int dequeVazio(Deque *deque){
 	if(deque->ultimo == deque->cabecalho)
 		return 1;
 	return 0;
 }
 
int dequeCheio( Deque* deque ){
 	int proxi = (deque->ultimo + 1) % MAX_TAM;
	if(proxi == deque->cabecalho)
		return 1;
	return 0;
 }

Aluno criarAluno( char nome[], int idade ){
	Aluno e;
	strcpy(e.nome, nome);
	e.idade = idade;
	return e;
}

//Funções
int inserirNoInicio( Deque* deque, Aluno elemento ){
 	if( dequeCheio( deque ) ){ return 0; }
 	deque->info[deque->cabecalho] = elemento;
 	deque->cabecalho = ( MAX_TAM + (deque->cabecalho - 1) ) % MAX_TAM;
 	return 1;
 }
 
int inserirNoFim(Deque *deque, Aluno elemento){
	if ( dequeCheio( deque ) ){ return 0; }
	deque->info[deque->ultimo] = elemento;
	deque->ultimo = (deque->ultimo + 1) % MAX_TAM;
	return 1; 
}

Aluno removerNoInicio(Deque *deque){
	Aluno vazio = criarAluno("",-1);
	if( dequeVazio( deque ) ){ return vazio; }
	vazio = deque->info[deque->cabecalho];
	deque->cabecalho = (deque->cabecalho + 1) % MAX_TAM;
	return vazio;
}

Aluno removerNoFim(Deque *deque){
 	Aluno vazio = criarAluno("",-1);
	if( dequeVazio( deque ) ){return vazio; }
	vazio =  deque->info[deque->ultimo];
	deque->ultimo = (MAX_TAM + (deque->ultimo - 1)) % MAX_TAM;
	return vazio;
 }

//IMPRIMIR
void imprimirTodos(Deque *deque){
	Deque deque2;
	inicializar( &deque2 );
	if( dequeVazio( deque ) ){
		printf(" O deque esta vazio\n");
	}
	Aluno a = criarAluno("",-1);
	while( !dequeVazio( deque ) ){
		//a = removeNoInicio( &deque );
		printf("Nome: %s - %d\n", a.nome, a.idade);
	    //i//nserirNoFim( &deque2, a );
	}
//	while( !dequeVazio( &deque2 ) ){
//		inserirfim(deque, removerinicio(&deque2));
//	}
}

void Menu (){
    printf("\n::INSERIR\n");
    printf("  [1] - Inserir No Inicio\n");
    printf("  [2] - Inserir No Fim\n");
    
    printf("\n::REMOVER\n");
    printf("  [3] - Remover No Inicio\n");
    printf("  [4] - Remover No Fim\n");
    
    printf("\n::MOSTRAR\n");
    printf("  [5] - Imprimir\n\n");
    
    printf("::SAIR\n");
    printf("  [0] - Sair\n\n");
}

int main(){
	Aluno e;
	Deque deque;
	inicializar(&deque);
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
				printf("Digite o nome: ");
				scanf("%s", e.nome);				
				printf("Digite o idade: ");
				scanf("%d", &e.idade);			
				if( inserirNoInicio(&deque, e) ){
					printf("\nAluno inserido :)\n");
				}else{
					printf("\nOcorreu um erro :(");
				}
				break;
			case 2:
				printf("Digite o nome: ");
				scanf("%s", e.nome);				
				printf("Digite o idade: ");
				scanf("%d", &e.idade);			
				if( inserirNoFim(&deque, e) ){
					printf("\nAluno inserido :)\n");
				}else{
					printf("\nOcorreu um erro :(");
				}
				break;
			case 3:
				e = removerNoInicio( &deque );
				if(e.idade != -1){
					printf("\nAluno retirado: %s\n",e.nome);
				}else{
					printf("\nDeque Vazio :(\n");
				}
				imprimirTodos( &deque );
				break;
			case 4:
				e = removerNoFim( &deque );
				if(e.idade != -1){
					printf("\nAluno retirado: %s\n",e.nome);
				}else{
					printf("\nDeque Vazio :(\n");
				}
				imprimirTodos( &deque );
				break;
			case 5:
				imprimirTodos( &deque );
				break;
			default:
				printf("Opcao invalida!");
		}
		printf("\n");
	}while(1);
	return 0;
}
