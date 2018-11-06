#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct snode{
  int info;
  struct snode *esq, *dir;
}no;


/////////////////////////////////////////////////
void inicializar(no **raiz){
  (*raiz) =NULL;
}
/////////////////////////////////////////////////
int vazia(no **raiz){
  if ((*raiz) == NULL){
    return 1;
  }
  return 0;
}
/////////////////////////////////////////////////
int inserir(no **raiz, int elem){
  if ((*raiz) != NULL){
    if (elem < (*raiz)->info){
      return inserir(&(*raiz)->esq, elem);
	}else{
      return inserir(&(*raiz)->dir, elem);
	}
  }
  no *novo = (no*) malloc (sizeof(no));
  if (novo == NULL){return 0;}
  novo->esq = NULL;
  novo->dir = NULL;
  novo->info = elem;
  (*raiz)=novo;
  return 1;
}

/////////////////////////////////////////////////
void ordem(no **raiz){
  if ((*raiz) != NULL){
    ordem(&(*raiz)->esq);
    printf("%d-", (*raiz)->info);
    ordem(&(*raiz)->dir);
  }
}

void PreOrdem(no **raiz){
  if ((*raiz) != NULL){
    printf("%d-", (*raiz)->info);
    ordem(&(*raiz)->esq);
    ordem(&(*raiz)->dir);
  }
}

void PosOrdem(no **raiz){
  if ((*raiz) != NULL){
    ordem(&(*raiz)->esq);
    ordem(&(*raiz)->dir);
    printf("%d-", (*raiz)->info);
  }
}

void printFolhaOrdem(no **raiz){
  if ((*raiz)!= NULL){
    //Ando esquerda
    printFolhaOrdem(&(*raiz)->esq);
    //vejo se é uma folha
    if ((*raiz)->dir == NULL && (*raiz)->esq==NULL){
      printf("%d-", (*raiz)->info);
	}
    //Ando direita
    printFolhaOrdem(&(*raiz)->dir);
  }
}
/////////////////////////////////////////////////


////////////////////PESQUISA NO E RETORNA A POSICAO DO ELEMENTO
no* pesquisaNo(no **raiz, int procurado){
  if ((*raiz) != NULL){
    //achei?
	if ((*raiz)->info == procurado){
      return (*raiz);
	}
	
	//Nao achei, entao anda
	if (procurado < (*raiz)->info){
      return pesquisaNo(&(*raiz)->esq, procurado);
	}else{
      return pesquisaNo(&(*raiz)->dir, procurado);
	} 
  }
  //Nao encontrou o item :/
  return NULL;
  
}

////////////////////PESQUISA NO E RETORNA 1 se achar, ou 0 se nao achar
int pesquisaNoInt(no **raiz, int procurado){
  // Nao existe
  if ((*raiz)== NULL){
    return 0;
  }
  
  // Achei
  if ((*raiz)->info == procurado){
    return 1;
  }
  
  // Ando para posicao correta
  if (procurado < (*raiz)->info ){
    return pesquisaNoInt(&(*raiz)->esq, procurado);
  }else{
    return pesquisaNoInt(&(*raiz)->dir, procurado);
  }
}


////////////////////PESQUISA NO E RETORNA o numero de itens procurado:
int pesquisaSomatorio(no **raiz, int procurado){
  if ((*raiz) == NULL){
    return 0;
  }
  
  // Achei
  if ((*raiz)->info == procurado){
    return 1+ pesquisaSomatorio(&(*raiz)->dir, procurado);
  }
  
  // Nao achei, ANDE!
  if (procurado < (*raiz)->info){
    return pesquisaSomatorio(&(*raiz)->esq, procurado);
  }else{
    return pesquisaSomatorio(&(*raiz)->dir, procurado);
  }
}



/////////////////////////////////////////////////////////////////////////////
int retornaNumeroDePares(no **raiz){
  if ((*raiz)==NULL){
    return 0;
  }
  //Vejo se é um numero par
  int ret=0;
  if ((*raiz)->info %2 == 0){
    ret = 1;
  }
  
  //Somatorio
  return ret + retornaNumeroDePares(&(*raiz)->esq) + retornaNumeroDePares(&(*raiz)->dir);
}



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// R E M O V  E R //////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
no *maiorElemento(no **raiz){
  if ((*raiz)->dir != NULL){
    return maiorElemento(&(*raiz)->dir);
  }
  no *aux = (*raiz);
  // o código abaixo é para ajuda durant a remoção.
  if ((*raiz)->esq != NULL){
    (*raiz) = (*raiz)->esq;
  }else{
 	(*raiz)=NULL;
  }
  return aux;
}


//Void porque sim! se essa @#%#$ for int, vai ser uma #%#@#$ fazer isso!
void remover(no **raiz, int procurado){
  // Nao tem item
  if ((*raiz)==NULL){
    printf("Item nao existente!\n");
    return; 
  }

  // Vejo se o procurado é menor
  if (procurado < (*raiz)->info){
    remover(&(*raiz)->esq, procurado);
  }else
    if (procurado > (*raiz)->info){
      remover(&(*raiz)->dir, procurado);
	}
    else{
      ////////// ENCONTREI O VALOR //////////
      no *aux = (*raiz);
      
      // Caso 1: Sem filhos
      if ((*raiz)->esq == NULL && (*raiz)->dir==NULL){
        free(aux);
        (*raiz)= NULL;
        return;
	  }
      
      // Caso 2, somente o filho direito:
      if ((*raiz)->esq == NULL){
        aux = (*raiz);
        (*raiz) = (*raiz)->dir;
        free(aux);
        return;
	  }
	  
	  //Caso 2, somente o filho esquerdo:
	  if ((*raiz)->dir == NULL){
	    aux = (*raiz);
	    (*raiz) = (*raiz)->esq;
	    free(aux);
	    return;
	  }
      
      // CASO 3: ocaso mortal da morte!
      // Nesse caso, tem 2 filhos, um de cada lado!!!
      // Entao para colocar no seu lugar posso:
	  // pegar o maior da parte esquerda ou
	  // pegar o menor da parte direita.
      aux = maiorElemento(&(*raiz)->esq);
      aux->esq = (*raiz)->esq;
      aux->dir = (*raiz)->dir;
      free ((*raiz));
      *raiz = aux;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// R E M O V  E R //////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////



int main (){
  no *arvore;
  inicializar(&arvore);

  inserir(&arvore, 3);
  inserir(&arvore, 2);
  inserir(&arvore, 1);
  inserir(&arvore, 4);
  inserir(&arvore, 5);
  
  printFolhaOrdem(&arvore);
  
  
  system("pause");
  return 0;
}

//By Gabriel ALves
