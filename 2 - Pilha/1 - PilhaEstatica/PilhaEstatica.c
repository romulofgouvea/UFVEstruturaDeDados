#include <stdio.h>
#include <stdlib.h> 
#include<conio.h>
#include<string.h>

#define MAX_TAM 5
typedef struct sAluno{
  char nome[100];
  int idade;
}Aluno;

typedef struct sPilha{
	Aluno info[MAX_TAM];
	int ultimo;
}Pilha;

void inicializar( Pilha* pilha ){
	pilha->ultimo=-1;
}

int pilhaVazia( Pilha* pilha ){
	if (pilha->ultimo==-1)
		return 1;
	return 0;
}

int pilhaCheia( Pilha* pilha ){
	if (pilha ->ultimo == (MAX_TAM-1))
		return 1;
	return 0;
}

Aluno criarElemento(char nome[], int idade){
	Aluno e;
	strcpy(e.nome, nome);
	e.idade = idade;
	return e;
}

int push( Pilha* pilha, Aluno aluno ){
	if ( pilhaCheia( pilha ) ){
		return 0;
	}
	pilha->info[pilha->ultimo+1] = aluno;
	pilha->ultimo++;
	return 1;
}

Aluno pop( Pilha* pilha ){
	Aluno removido = criarElemento("", -1);
	if ( pilhaVazia( pilha ) ){
		return removido;	
	}
	removido = pilha->info[pilha->ultimo];
	pilha->ultimo--;
	return removido;
}

Aluno topoDaPilha( Pilha* pilha ){
	Aluno removido= criarElemento("",-1);
	if ( pilhaVazia( pilha ) ){
		return removido;
	}
	return pilha->info[pilha->ultimo];
}

void imprimirAluno( Pilha* pilha ){
	if (!pilhaVazia( pilha )){
		printf("\nNome: %s - Idade: %d.", pilha->info[pilha->ultimo].nome, pilha->info[pilha->ultimo].idade);
	}
}

void imprimirPilhaDel( Pilha* pilha ){
	while( pilha->ultimo != -1 ){
		imprimirAluno( pilha );
		pop( pilha );
	}
}

void imprimirTodos( Pilha* pilha ){
	Pilha aux;
	inicializar(&aux);
	
	while( pilha->ultimo != -1 ){
		imprimirAluno( pilha );
		push(&aux, pop( pilha ));
	}
	
	while( aux.ultimo != -1 ){
		push(pilha, pop(&aux));
	}
	printf("\n");	
}

void imprimirInvertido( Pilha* pilha ){
	Pilha aux;
	aux.ultimo = -1;
	while( pilha->ultimo != -1 ){
		push( &aux, pop( pilha ) );
	}
	while( aux.ultimo != -1 ){
		imprimirAluno( &aux );
		push( pilha, pop(&aux) );
	}
}



void Menu (){
    printf("\n::INSERIR\n");
    printf("  [1] - Empilhar\n");
    
    printf("\n::REMOVER\n");
    printf("  [2] - Desenpilhar\n");
    
    printf("\n::MOSTRAR\n");
    printf("  [3] - Topo\n");
    printf("  [4] - Imprimir\n\n");
    
    printf("::SAIR\n");
    printf("  [0] - Sair\n\n");
}

int main(){
	Aluno e;
	Pilha pilha;
	inicializar(&pilha);
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
				printf("-------  EMPILHANDO  ------\n\n");
				printf("Digite o nome: ");
				scanf("%s", e.nome);				
				printf("Digite o idade: ");
				scanf("%d", &e.idade);			
				if( push(&pilha, e) ){
					printf("\nAluno inserido :)\n");
				}else{
					printf("\nOcorreu um erro :(");
				}
				break;
			case 2:	
				printf("-------  DESEMPILHANDO  ------\n\n");
				e = pop( &pilha );
				if(e.idade != -1){
					printf("\nAluno retirado: %s\n",e.nome);
				}else{
					printf("\nPilha Vazia :(\n");
				}
				break;
			case 3:	
				e = topoDaPilha( &pilha );
				if(e.idade != -1){
					printf("\nO topo eh Nome: %s - Idade: %d\n", e.nome, e.idade);
				}else{
					printf("\nPilha Vazia :(\n");
				}
				break;
			case 4:
				imprimirTodos( &pilha );
				break;
			default:
				printf("Opcao invalida!");
		}
		imprimirTodos( &pilha );
		printf("\n");
	}while(1);
	return 0;
}

