#include <stdio.h>
#include <stdlib.h>
#define TAML 4
#define TAMC 4

typedef struct sCell{
	int linha, coluna;
	int info;
	struct sCell *proxlin;
	struct sCell *proxcol;
}celula;

typedef struct sMat{
	celula *linha[TAML];
	celula *coluna[TAMC];
}matriz_esparsa;

celula *criarCelula(){
	return (celula*)malloc(sizeof(celula));
}

void inicializar(matriz_esparsa *matriz){
	int i;
	for ( i = 0; i < TAML; ++i)          //VAI EM TODAS AS LINHAS APONTANDO PRA NULL
		matriz->linha[i] = NULL;
	for ( i = 0; i < TAMC; ++i)
		matriz->coluna[i] = NULL;		//VAI EM TODAS AS COLUNAS APONTANDO PRA NULL

}

int vazia(matriz_esparsa *matriz){

	int i;
	for (int i = 0; i < TAML; ++i)
	{
		if (matriz->linha[i] != NULL)
			return 0;
	}
	return 1;
}

int inserirLinha(matriz_esparsa *matriz, celula *no, int lin, int col, int elemento){

	celula **lista = &matriz->linha[lin];          //CRIO UMA VARIAVEL LISTA, PARA FICAR MAIS INTUITIVO COM A LISTA JA CONHECIDA
	celula *aux = *lista;
	celula *ant;

	if (*lista == NULL)                            //NAO TEM ELEMENTOS NAQUELA LINHA -  equivalente à lista vazia
	{
		*lista = no;
		no->proxcol = NULL;
		return 1;
	}

	if (col < aux->coluna)						   //O ELEMENTO QUE QUERO INSERIR PERTENCE A UMA COLUNA ANTERIOR A PRIMEIRA JA INSERIDA - equivalente a inserir no inicio
	{
		no->proxcol = *lista;
		*lista = no;
		return 1;
	}

	while(aux!= NULL && aux->coluna <= col){       //PERCORRENDO A LISTA PRA ACHAR A POSICAO(COLUNA) QUE DEVE SER INSERIDO - equivalente a inserir na posicao K
		if (aux->coluna == col)					   //CASO JA EXISTA UM NO NAQUELA COORDENADA
		{
			aux->info = elemento;				   //SIMPLESMENTE SUBSTITUI O INFO
			return 1;
		}
		ant = aux;
		aux = aux->proxcol;
	}

	no->proxcol = ant->proxcol;
	ant->proxcol = no;
	return 1;

}

int inserirColuna(matriz_esparsa *matriz, celula *no, int lin, int col, int elemento){

	celula **lista = &matriz->coluna[col];
	celula *aux = *lista;
	celula *ant;

	if (*lista == NULL)
	{
		*lista = no;
		no->proxlin = NULL;
		return 1;
	}

	if (lin < aux->linha)
	{
		no->proxlin = *lista;
		*lista = no;
		return 1;
	}

	while(aux != NULL && aux->linha <= lin){
		if (aux->linha == lin)
		{
			aux->info = elemento;
			free(no);
			return 1;
		}
		ant = aux;
		aux = aux->proxlin;
	}

	no->proxlin = ant->proxlin;
	ant->proxlin = no;
	return 1;

}

int remover(matriz_esparsa *matriz, int lin, int col){
	lin = lin-1;
	col = col-1;

	celula *removida;
	celula *aux = matriz->linha[lin];
	celula *ant;
	//printf("%d\n", aux->info);

	while (aux != NULL && aux->coluna != col){
		ant = aux;
		aux = aux->proxcol;
	}

	if (aux == NULL) return 0;

	if(aux == matriz->linha[lin]) 
		matriz->linha[lin] = aux->proxcol;
	else
		ant->proxcol = aux->proxcol;

	removida = aux;

	celula *aux2 = matriz->coluna[col];

	while (aux != NULL && aux2->linha != lin){
		ant = aux2;
		aux2 = aux2->proxlin;
	}

	if (aux == NULL) return 0;

	if(aux == matriz->coluna[col]) 
		matriz->coluna[col] = aux->proxcol;
	else
		ant->proxlin = aux->proxlin;

	free(removida);
	return 1;

}

int inserir(matriz_esparsa *matriz, int elemento, int lin, int col){

	if(lin > TAML || col > TAMC)
		return 0;

	lin = lin-1; 									//NA PROGRAMACAO OS INDICES COMECAM COM ZERO, MAS O USUARIO PARTE DO PRINCIPIO QUE A MATRIZ COMECA NO (1,1)
	col = col-1;

	if (elemento ==  0)
		return 0;

	celula *no = criarCelula();
	no->info = elemento;
	no->linha = lin;
	no->coluna = col;

	inserirLinha(matriz, no, lin, col, elemento);
	inserirColuna(matriz, no, lin, col, elemento);

	return 1;
}


void imprimir(matriz_esparsa *matriz){           //IMPRIME SOMENTE OS ELEMENTOS DA MATRIZ
	
	int i, j;
	celula *aux;
	for (i = 0; i < TAML; ++i)
	{
		aux = matriz->linha[i];

		while(aux != NULL){
			printf("%d ", aux->info);

			aux = aux->proxcol;
		}
		printf("\n");
	}

}

void imprimir2(matriz_esparsa *matriz)			//IMPRIME TODA A MATRIZ, COMPLETANDO COM 0 
{
	int i, j;
	celula *aux;
	for (int i = 0; i < TAML; ++i)
	{
		aux = matriz->linha[i];
		for (int j = 0; j < TAMC; ++j)
		{
			if (aux != NULL && aux->linha == i && aux->coluna == j)
			{
				printf("%d ",aux->info );
				aux = aux->proxcol;
			}
			else 
				printf("0 ");
		}
		printf("\n");
	}
	printf("\n");
}

int main(){
	
	matriz_esparsa matriz;
	inicializar(&matriz);
	int escolha, elemento, linha, coluna;

	do
	{
		printf("1 - Inserir elemento na matriz\n");
		printf("2 - Remover elemento na matriz\n");
		printf("3 - Imprimir matriz\n");
		printf("4 - Sair\n");

		scanf("%d", &escolha);

		switch(escolha){
			case 1:
				printf("Digite o elemento para ser inserido: ");
				scanf("%d", &elemento);
				printf("Digite a linha: ");
				scanf("%d", &linha);
				printf("Digite a coluna: ");
				scanf("%d", &coluna);
				inserir(&matriz, elemento, linha, coluna);
				break;

			case 2:
				printf("Digite a linha para remover: ");
				scanf("%d", &linha);
				printf("Digite a coluna para remover: ");
				scanf("%d", &coluna);
				remover(&matriz, linha, coluna);
				break;

			case 3: 
				imprimir2(&matriz);
				break;
		}

		printf("\e[H\e[2J");
		imprimir2(&matriz);

	} while (escolha != 4);

	return 0;
}

//by Vitor Alcantra
