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
    int cont;
}Lista;

void inicializar( Lista** lista ){
	(*lista) = NULL;
}

int ListaVazia(Lista **lista){
  if ( (*lista) == NULL )
  	return 1;
  return 0;
}

Celula* criarCelula(){
	return (Celula*) malloc (sizeof(Celula));
}

//INSERIR
int inserirNoInicio( Lista** lista, Aluno novo ){
	Celula* nova = criarCelula();
	nova->info = novo;
	nova->next = NULL;
	nova->cont = 0;
	if ( ListaVazia( (*lista ) ){
		(*lista) = nova;
		return 1;
	}
	nova->next = (*lista);
  	(*lista) = nova;
	return  1;
}

int inserirNoFim( Lista** lista, Aluno novo ){
	Celula* nova = criarCelula();
	nova->info = novo;
	nova->next = NULL;
	nova->cont = 0;
	if ( ListaVazia( (*lista ) ){
		(*lista) = nova;
		return 1;
	}
	Celula* aux = (*lista);
	while( aux->next != NULL ){
		aux = aux->next;
	}
	aux->next = nova;
	return 1;
}

int inserirNaPosicao( Lista** lista, int posicao, Aluno novo ){

	return  1;
}

int inserirOrdenado(Lista **lista, aluno n){
	Celula* nova = criarCelula();
	nova->info = novo;
	nova->next = NULL;
	nova->cont = 0;
	
	if ( ListaVazia( (*lista ) ){
		(*lista) = nova;
		return 1;
	}
	Celula* ant;
	Celula* aux = (*lista);
  
	while (aux != NULL && aux->cont > nova->cont){
		ant = aux;
		aux = aux->next;
	}
	if (aux == (*lista)){
		nova->next = (*lista);
		(*lista) = nova;
		return 1;
	}
	nova->next = aux;
	ant->next = nova;
	return 1;
}

//REMOVER
Aluno removerNoInicio( Lista** lista ){
	if ( ListaVazia( (*lista ) ){
		return NULL;
	}
	Aluno removido;
	Celula* aux = (*lista);
	(*lista) = (*lista)->next;
	removido = aux->info;
	free(aux);
	return removido;
}

Aluno removerNoFim( Lista** lista ){
	if ( ListaVazia( (*lista ) ){
		return NULL;
	}
	Aluno removido;
	Celula* ant = NULL;
	Celula* aux = (*lista);
	while( aux->next != NULL ){
		ant = aux;
		aux = aux->next;
	}
	ant->next = NULL;
	removido = aux->info;
	free(aux);
	return removido;
}

Aluno removerNaPosicao( Lista** lista, int posicao ){
	Aluno removido;

  	return removido;
}

//IMPRIMIR
void imprimirLista(Lista** lista){
	celula *aux = (*lista);
	int i = 1;
	while (aux != NULL){
		printf("%d - %s",i,aux->info.nome);
		i++;
		aux = aux->next;
	}
}

void Menu (){
	//---------MENU---------//
    printf("::INSERIR\n");
    printf("  [1] - Inserir no Inicio\n");
    printf("  [2] - Inserir no Final\n");
    printf("  [3] - Inserir na Posicao K\n\n");
    printf("::REMOVER\n");
    printf("  [4] - Remover no Inicio\n");
    printf("  [5] - Remover no Final\n");
    printf("  [6] - Remover na Posicao K\n\n");
    printf("::MOSTRAR\n");
    printf("  [7] - Mostrar Lista\n\n");
    printf("::SAIR\n");
    printf("  [0] - Sair\n");
}

int main (){
	Lista lista;
	Aluno a;
	int option,posicaoK;
	
	inicializar(&lista);
	
	do{
		Menu();
		printf("\nDigite uma opcao valida: ");
		scanf("%d", &option);
		fflush(stdin);
		system("cls");
		switch(option){
			case 0:
				return 0;
			case 1:// Inserir no Inicio
				printf("Digite o nome do aluno: ");
		   		fflush(stdin);
		   		gets(a.nome);
		   		printf("Digite a idade do aluno: ");
		   		scanf("%d", &a.idade);
				if(inserirNoInicio(&lista, a)){
					printf("Tudo certo :)");
				}else{
					printf("\n Ocorreu um erro :(\n");
				}
				break;
			case 2:// Inserir no final
				printf("Digite o nome do aluno: ");
		   		fflush(stdin);
		   		gets(a.nome);
		   		printf("Digite a idade do aluno: ");
		   		scanf("%d", &a.idade);
				if(inserirNoFim(&lista, a)){
					printf("Tudo certo :)");
				}else{
					printf("\n Ocorreu um erro :(\n");
				}
			    break;
			case 3:// Inerir na posicao K
				printf("Digite o nome do aluno: ");
		   		fflush(stdin);
		   		gets(a.nome);
		   		printf("Digite a idade do aluno: ");
		   		scanf("%d", &a.idade);
		   		imprimirLista(&lista);
				printf("Digite a posicao para insercao: ");
	   			scanf("%d", &posicaoK);
				if(inserirNaPosicao(&lista,posicaoK-1, a)){
					printf("Tudo certo :)");
				}else{
					printf("\n Ocorreu um erro :(\n");
				}
				break;
			case 4:// Remover no inicio
				a = removerNoInicio(&lista);
				if(a != NULL){
					printf("ELEMENTO REMOVIDO: %s\n", a.nome);
					printf("Tudo certo :)\n");
				}else{
					printf("\n Lista Vazia :(\n");
				}
				break;
			case 5:// Remover no final
				a = removerNoFim(&lista);
				if(a != NULL){
					printf("ELEMENTO REMOVIDO: %s\n", a.nome);
					printf("Tudo certo :)\n");
				}else{
					printf("\n Lista Vazia :(\n");
				}
				
				break;

			case 6:// Remover na posicao K
				printf("Digite a posicao para remover: ");
	   			scanf("%d", &posicaoK);
	   			a = removerNaPosicao(&lista,posicaoK-1);
				if(a.idade != -1){
					printf("ELEMENTO REMOVIDO: %s\n", a.nome);
					printf("Tudo certo :)\n");
				}else{
					printf("\n Lista Vazia :(\n");
				}
				break;
			case 7:// Mostrar Lista
				imprimirLista(&lista);
				break;
					
			default:
				printf("Opcao invalida\n");
				break;
		}
		imprimirLista(&lista);
	}while(1);	
	return 0;
}
