#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTAM 5
typedef struct sAluno{
  char nome[100];
  int idade;
}Aluno;

typedef struct sLista{
	Aluno info[MAXTAM];
	int ultimo;
}Lista;

void inicializar( Lista* lista ){
	lista->ultimo = -1;
}

int listaCheia( Lista* lista ){
	if( lista->ultimo == ( MAXTAM - 1 ) )
		return 1;
	return 0;
}

int ListaVazia( Lista* lista ){
	if( lista->ultimo == -1 )
		return 1;
	return 0;
}

//INSERIR
int inserirNoInicio( Lista* lista, Aluno novo ){
	if( listaCheia(lista) ){
		printf("\n Erro: Lista cheia.");
		return 0;
	}
	lista->ultimo++;
	int i;
	for( i = lista->ultimo; i >= 1; i-- ){
		lista->info[i]= lista->info[i-1];
	}
	lista->info[0] = novo;
	return  1;
}

int inserirNoFim( Lista* lista, Aluno novo ){
	if( listaCheia(lista) ){
		return 0;
	}
	lista->ultimo++;
	int pos = lista->ultimo;
	lista->info[pos] = novo;
	return 1;
}

int inserirNaPosicao( Lista* lista, int posicao, Aluno novo ){
	if( listaCheia(lista) ){
		printf("\n Erro: Lista cheia.");
		return 0;
	}
	lista->ultimo++;
	int i;
	for( i = lista->ultimo; i > posicao; i-- ) {
		lista->info[i]= lista->info[i-1];
	}
	lista->info[posicao] = novo;
	return  1;
}

//REMOVER
Aluno removerNoInicio( Lista* lista ){
	Aluno removido;
	if ( ListaVazia ( lista ) ){
		removido.idade = -1;
		return removido;
	}
	removido = lista->info[0];
	int i;
	for( i = 0; i < lista->ultimo; i++ ){
		lista->info[i] = lista->info[i+1];
	}
	lista->ultimo--;
	return removido;
}

Aluno removerNoFim( Lista* lista ){
	Aluno removido;
	if( ListaVazia( lista ) ){
		removido.idade = -1;
		return removido;
	}
	removido = lista->info[lista->ultimo];
	lista->ultimo--;
	return removido;
}

Aluno removerNaPosicao( Lista* lista, int posicao ){
	Aluno removido;
  	if( ListaVazia( lista ) ){
		removido.idade = -1;
		return removido;
	}
  	removido = lista->info[posicao];
  	int i;
	for( i = posicao; i <= lista->ultimo; i++ ){
		lista->info[i]= lista->info[i+1];
	}
  	lista->ultimo--;
  	return removido;
}

//EXTRAS
int pesquisarElemento( Lista* lista, Aluno novo ){
	if( ListaVazia( lista ) ){
		return -1;
	}
	int i;
	for (i = 0; i <= lista->ultimo; i++ ){
		if(lista->info[i].nome == novo.nome){
		 	return i;//posição do elemento
		}
	}
}


//IMPRIMIR
void imprimirLista(Lista* lista){
	printf("Imprimir Lista\n");
	if( ListaVazia(lista) ){
		printf("\n A sua lista esta vazia!\n\n");
		return;
	}
	int i;
	for (i = 0; i <= lista->ultimo; i++ ){
		printf("%d - %s\n", i+1,lista->info[i].nome);
	}
	printf("\n");	
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
					printf("\n Erro: Lista cheia.");
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
					printf("\n Erro: Lista cheia.");
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
					printf("\n Erro: Lista cheia.");
				}
				break;
			case 4:// Remover no inicio
				a = removerNoInicio(&lista);
				if(a.idade != -1){
					printf("ELEMENTO REMOVIDO: %s\n", a.nome);
					printf("Tudo certo :)\n");
				}else{
					printf("\n Erro: Lista Vazia :(");
				}
				break;
			case 5:// Remover no final
				a = removerNoFim(&lista);
				if(a.idade != -1){
					printf("ELEMENTO REMOVIDO: %s\n", a.nome);
					printf("Tudo certo :)\n");
				}else{
					printf("\n Erro: Lista Vazia :(");
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
					printf("\n Erro: Lista Vazia :(");
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
