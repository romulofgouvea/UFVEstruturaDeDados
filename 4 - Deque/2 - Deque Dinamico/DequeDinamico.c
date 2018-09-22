#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct sAluno{
  char nome[100];
  int idade;
}Aluno;

typedef struct sCelula{
  Aluno info;
  struct sCelula *prox, *ante;
}Celula;

typedef struct sDeque{
	Celula *inicio, *fim;
}Deque;

void inicializar (Deque *deque){
	deque->inicio = NULL;
	deque->fim = NULL;
 }

int dequeVazio(Deque *deque){
	if (deque->inicio == NULL && deque->fim == NULL)
		return 1;
	return 0;
}

Celula* criarcelula(){
	return (Celula*)malloc(sizeof(Celula));
}

Aluno criarAluno( char nome[], int idade ){
	Aluno e;
	strcpy(e.nome, nome);
	e.idade = idade;
	return e;
}

int inserirNoInicio( Deque* deque, Aluno novo ){
	Celula *novacelula = criarcelula();
	if(novacelula == NULL){ return 0; }
	novacelula->info = novo;
	novacelula->prox = NULL;
	novacelula->ante = NULL;
	if( dequeVazio( deque ) ){
		deque->inicio = novacelula;
		deque->fim = novacelula;
		return 1;
	}
	novacelula->prox = deque->inicio;
	deque->inicio->ante = novacelula;
	deque->inicio = novacelula;
	return 1;
}
	
int inserirNoFim( Deque *deque, Aluno novo ){
	Celula *novacelula = criarcelula();
	if (novacelula == NULL){ return 0; }
	novacelula->info = novo;
	novacelula->prox = NULL;
	novacelula->ante = NULL; 
	if ( dequeVazio( deque ) ){
		deque->inicio = novacelula;
		deque->fim = novacelula;
		return 1;
	}
	novacelula->ante = deque->fim;
	deque->fim->prox = novacelula;
	deque->fim = novacelula;
	return 1;
}
	
Aluno removerNoInicio( Deque *deque ){
	Aluno vazio = criarAluno("",-1);
	if ( dequeVazio( deque ) ){
		return vazio;
	}
	Celula *aux = deque->inicio;
	vazio = aux->info;
	if(deque->inicio == deque->fim){
		inicializar(deque);
		free(aux);
		return vazio;
	}
	deque->inicio = deque->inicio->prox;
	deque->inicio->ante  = NULL;
	free (aux);
	return vazio;
}

Aluno removerNoFim( Deque *deque ){
	Aluno vazio = criarAluno("",-1);
	if(dequeVazio(deque)){ return vazio; }
	Celula* aux = deque->fim;
	vazio = aux->info;
	if(deque->inicio == deque->fim){
		inicializar(deque);
		free(aux);
		return vazio;
	}
	deque->fim = deque->fim->ante;
	deque->fim->prox = NULL;
	free(aux);
	return vazio;
}
	
void imprimirTodos( Deque *deque ){
	Aluno aux = criarAluno("",-1);
	Deque deque2;
	inicializar( &deque2 );
	if( dequeVazio( deque ) ){
		printf("\nDeque Vazio :(\n");
		return;
	}
	while ( !dequeVazio( deque ) ){
		aux = removerNoInicio( deque );
		printf("Nome: %s - %d\n", aux.nome, aux.idade);
		inserirNoFim( &deque2, aux );
	}
	while ( !dequeVazio( &deque2 ) ){
		inserirNoFim( deque, removerNoInicio( &deque2 ) );
	}
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
}

