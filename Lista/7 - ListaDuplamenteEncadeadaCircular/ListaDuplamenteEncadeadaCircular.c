#include <stdio.h>
#include <stdlib.h>

typedef struct sAluno{
  char nome[100];
  int idade;
}Aluno;

typedef struct sCelula{
    Aluno info;
    struct sCelula *ant;
    struct sCelula *next;
    int cont;
}Lista;

void inicializar( Lista** lista ){
	(*lista) = NULL;
}

int listaVazia(Lista* lista){
  if ( lista == NULL){
    return 1;
  }
  return 0;
}

Lista* criarCelula(){
	return (Lista*) malloc (sizeof(Lista));
}

int inserirNoInicio( Lista** lista, Aluno inserido ){
  Lista* novaCelula = criarCelula();
  if ( novaCelula == NULL ){
    return 0;
  }
  novaCelula->info = inserido;
  novaCelula->next = NULL;
  if ( listaVazia(*lista) ){
    (*lista) = novaCelula;
    novaCelula->ant = novaCelula;
    novaCelula->next = novaCelula;
    return 1;
  }
  novaCelula->next = (*lista)->next;
  novaCelula->ant = (*lista);
  novaCelula->next->ant = novaCelula;
  (*lista)->next = novaCelula;
  return 1;
}

int inserirNoFim( Lista** lista, Aluno inserido ){
	if ( listaVazia(*lista) ){
	 	return inserirNoInicio(lista,inserido);
	}
	if(inserirNoInicio(lista,inserido)){
		(*lista) = (*lista)->next;	
	}
	
	return 1;
}

Aluno removerNoInicio( Lista** lista ){
	Aluno removido;
	if ( listaVazia(*lista) ){
		removido.idade = -1;
	 	return removido;
	}
	Lista *removida = (*lista)->next;
	removido = removida->info;
	if ( (*lista)->next == (*lista) ){
		(*lista) = NULL; 
		free(removida);
		return removido;
	}
	(*lista)->next = removida->next;
	removida->next->ant = (*lista);
	
	free(removida);
	return removido;
}

Aluno removerNoFim( Lista** lista ){
  	Aluno removido;
	if ( listaVazia(*lista) ){
		removido.idade = -1;
	 	return removido;
	}
  	(*lista) = (*lista)->ant;
  	return removerNoInicio(lista);
}


//IMPRIMIR
void imprimirImpar( Lista** lista ){
	if ( listaVazia(*lista) ){
		return;
	}
	Lista *aux = (*lista)->next;
	do{
		if (aux->info.idade %2 != 0){
		   printf("Aluno: %s, idade: %d e impar.\n", aux->info.nome, aux->info.idade);
		}
		aux= aux->next;
	}while( aux != (*lista)->next );
}

void imprimirMaisVelho( Lista** lista ){
	if ( listaVazia(*lista) ){
		return;
	}
	Lista *aux = (*lista)->next;
	Lista *aluno;
	int maior = -99999;
	do{
		if (aux->info.idade > maior){
		  aluno = aux;
		  maior = aux->info.idade;
		}
		aux= aux->next;
	}while( aux != (*lista)->next );
	printf("Aluno: %s é o maior com %d anos.\n", aluno->info.nome, aluno->info.idade);
}

void imprimirLista( Lista** lista ){
	if( listaVazia( *lista ) ){
		printf("Lista Vazia!\n");
		return;
	}
	Lista* aux = (*lista);
	printf("\n");
	do{
		aux = aux->next;
		printf("%s - %d\n", aux->info.nome,aux->info.idade);	
	}while(aux != (*lista));
	printf("\n");
}

//EXTRA
void liberarLista( Lista** lista ){
	if ( listaVazia(*lista) ){
		printf("Lista Vazia!\n");
		return;
	}
	Lista *removida;
	while ( (*lista)->next != (*lista) ){
		removida = (*lista)->next; // Removida aponta para o primeiro item
		(*lista)->next = removida->next; // Mudo o ponteiro da lista
		free(removida);
	}
	removida = (*lista);
	free(removida);
	(*lista) = NULL;
}

void Menu (){
	//---------MENU---------//
    printf("::INSERIR\n");
    printf("  [1] - Inserir no Inicio\n");
    printf("  [2] - Inserir no Final\n");
    
    printf("::REMOVER\n");
    printf("  [3] - Remover no Inicio\n");
    printf("  [4] - Remover no Final\n");
    
    printf("::MOSTRAR\n");
    printf("  [5] - Mostrar Alunos com idade impar\n\n");
    printf("  [6] - Mostrar Aluno mais velho\n\n");
    printf("  [7] - Mostrar Lista\n\n");
    printf("::SAIR\n");
    printf("  [8] - Liberar Lista\n");
    printf("  [0] - Sair\n");
}

int main (){
	Lista* lista;
	Aluno a;
	int option;
	
	inicializar(&lista);
	
	do{
		Menu();
		printf("\nDigite uma opcao: ");
		scanf("%d", &option);
		fflush(stdin);
		system("cls");
		switch(option){
			case 0:
				liberarLista(&lista);
				return 0;
			case 1:// Inserir no Inicio
				printf("Digite o nome do aluno: ");
		   		fflush(stdin);
		   		gets(a.nome);
		   		printf("Digite a idade do aluno: ");
		   		scanf("%d", &a.idade);
				if(inserirNoInicio(&lista, a)){
					printf("Tudo certo :)\n");
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
			case 3:// Remover no inicio
				a = removerNoInicio(&lista);
				if(a.nome){
					printf("ELEMENTO REMOVIDO: %s\n", a.nome);
					printf("Tudo certo :)\n");
				}else{
					printf("\n Lista Vazia :(\n");
				}
				break;
			case 4:// Remover no final
				a = removerNoFim(&lista);
				if(a.nome){
					printf("ELEMENTO REMOVIDO: %s\n", a.nome);
					printf("Tudo certo :)\n");
				}else{
					printf("\n Lista Vazia :(\n");
				}
				break;
			case 5:// Mostrar impar
				imprimirImpar(&lista);
				break;
			case 6:// Mostrar mais velho
				imprimirMaisVelho(&lista);
				break;
			case 7:// Mostrar Lista
				imprimirLista(&lista);
				break;
			case 8:// Mostrar Lista
				liberarLista(&lista);
				break;
			default:
				printf("Opcao invalida\n");
				break;
		}
		imprimirLista(&lista);
	}while(1);	
	return 0;
}








