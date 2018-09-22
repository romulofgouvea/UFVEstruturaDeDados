#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sAluno{
  char nome[100];
  int idade;
}Aluno;

typedef struct sCelula{
  Aluno info;
  struct sCelula* prox;
}Celula;

typedef struct sPilha{
    Celula* topo;
    int tam;
}Pilha;

void inicializar( Pilha* pilha ){
  pilha->topo = NULL;
  pilha->tam = 0;
}

int pilhaVazia( Pilha* pilha ){
  if ( pilha->topo == NULL )
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

int push( Pilha* pilha, Aluno a){
  Celula* nova = criarCelula();
  Celula* auxTopo = pilha->topo; 
  if (nova == NULL){
  	return 0;
  }
  nova->info = a;
  nova->prox = auxTopo;
  pilha->topo = nova;
  pilha->tam++;
  return 1;
}

Aluno pop( Pilha* pilha ){
  Aluno invalido = criarElemento("",-1);
  if ( pilha->topo == NULL ){
      return invalido; 
  }
  Celula* removida = pilha->topo; 
  Aluno itemRemovido = removida->info; 
  pilha->topo = removida->prox;
  pilha->tam--;
  free(removida); 
  return itemRemovido;
}

//IMPRIMIR
void imprimirTodos( Pilha* pilha ){
	printf("Imprimindo Pilha\n");
	if (pilha->topo==NULL){
	  return;
	}
	Pilha pilha2;
	inicializar(&pilha2);
	Aluno temp;
	do {
		Celula* cell = pilha->topo; 
		printf("%s - %d\n", cell->info.nome,cell->info.idade);
		push(&pilha2, pop( pilha ));
	}while(pilha->topo!= NULL);

	do{
		push(pilha, pop(&pilha2));
	}while(pilha2.topo != NULL);
}

Aluno topoDaPilha( Pilha* pilha ){
	Aluno removido= criarElemento("",-1);
	if ( pilhaVazia( pilha ) ){
		return removido;
	}
	Celula* cell = pilha->topo; 
	return cell->info;
}

void Menu (){
    printf("\n::INSERIR\n");
    printf("  [1] - Enfileirar\n");
    
    printf("\n::REMOVER\n");
    printf("  [2] - Desenfileirar\n");
    
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
					printf("\nOcorreu um erro :(\n");
				}
				break;
			case 2:	
				printf("-------  DESEMPILHANDO  ------\n\n");
				imprimirTodos( &pilha );
				e = pop( &pilha );
				if(e.idade != -1){
					printf("\nAluno retirado: %s\n",e.nome);
				}else{
					printf("\nPilha Vazia :(\n");
				}
				imprimirTodos( &pilha );
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
				printf("\nOpcao invalida!\n");
		}
		printf("\n");
	}while(1);
	return 0;
}








