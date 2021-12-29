#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "meuconio.h"

//grava no arquivo binario
struct reg
{
	int quant=0;
	float frequencia;
	char palavra[50], simbolo, code[20];
};typedef struct reg Reg;

//arvore de huffman
struct tree
{
	float frequencia;
	char simbolo;
	struct tree *dir,*esq;
};typedef struct tree Tree;
//lista
struct lista
{
	Tree *campo;
	struct lista *prox,*ant;
};typedef struct lista Lista;

int BuscaPalavra(Reg *frase,int TL ,char palavra[50])
{
	int pos =0;
	while(pos<TL && stricmp(frase[pos].palavra,palavra)!=0)
		pos++;
	if(pos<TL)
		return pos;
	return -1;
}

Tree *CriaNo(float frequencia, char simbolo)
{
	Tree *arv = (Tree*)malloc(sizeof(Tree));
	arv->frequencia = frequencia;
	arv->simbolo = simbolo;
	arv->dir = arv->esq = NULL;
	return arv;
}

Lista *CriaCaixa(Reg info)
{
	Lista *aux = (Lista*)malloc(sizeof(Lista));
	aux->campo = CriaNo(info.frequencia,info.simbolo);
	aux->prox = NULL;
	aux->ant = NULL;
	return aux;
}

void InsereLista(Lista **L,Reg campo)
{
	Lista *aux,*pos;
	aux = CriaCaixa(campo);
	if(*L==NULL)
		*L = aux;
	else
	{
		if((*L)->campo->frequencia > campo.frequencia)
		{
			aux->prox = *L;
			(*L)->ant = aux;
			*L = aux;
		}
		else
		{
			pos = *L;
			while(pos->prox!=NULL && pos->campo->frequencia < campo.frequencia)
				pos = pos->prox;
			if(pos->prox==NULL)//Ultimo
			{
				pos->prox = aux;
				aux->ant = pos;
			}
			else
			{
				pos->prox->ant = aux;
				aux->prox = pos->prox;
				pos->prox = aux;
				aux->ant = pos;
			}
		}
	}
}

void InsereListaArv(Lista **L,Tree *no)
{
	Lista *aux,*pos;
	aux = (Lista*)malloc(sizeof(Lista));
	aux->campo=no;
	aux->ant = aux->prox = NULL;
	if(*L==NULL)
		*L = aux;
	else
	{
		if((*L)->campo->frequencia > aux->campo->frequencia)
		{
			aux->prox = *L;
			(*L)->ant = aux;
			*L = aux;
		}
		else
		{
			pos = *L;
			while(pos->prox!=NULL && pos->campo->frequencia < aux->campo->frequencia)
				pos = pos->prox;
			if(pos->prox==NULL)//Ultimo
			{
				pos->prox = aux;
				aux->ant = pos;
			}
			else
			{
				pos->prox->ant = aux;
				aux->prox = pos->prox;
				pos->prox = aux;
				aux->ant = pos;
			}
		}
	}
}

void InsereL(Lista **L,Reg *frase,int TL)
{
	int i=0;
	while(i<TL)
	{
		InsereLista(&*L,frase[i]);
		i++;
	}
}

void RemoveLista(Lista **L, Lista *exclui)
{
	
	Lista *Aux=*L;
	while(Aux != NULL && Aux != exclui)
		Aux=Aux->prox;
	if(Aux!=NULL)
	{
		if(Aux->ant ==NULL)//INICIO
		{
			*L=Aux->prox;
			(*L)->ant = NULL;
		}
		else
		{
			if(Aux->prox==NULL)//FINAL
			{
				Aux->ant->prox=NULL;
			}
			else//MEIO
			{
				Aux->ant->prox = Aux->prox;
				Aux->prox->ant = Aux->ant;
			}
		}
		free(Aux);
	}
}

void ArvHuffman(Lista *L,Tree **Arv)
{
	Lista *aux = L,*juncao;
	Tree *no;
	while(L->prox!=NULL)
	{
		if(aux->prox!=NULL)
			juncao = aux->prox;
		no = CriaNo(aux->campo->frequencia+juncao->campo->frequencia,'x');
		no->esq = aux->campo;
		no->dir = juncao->campo;
	
		InsereListaArv(&L,no);
		RemoveLista(&L,aux);
		RemoveLista(&L,juncao);
		
		aux = L;
		//ExibeLista(L);
		//printf("\n---------------------------------------------------------\n\n");	
	}
	*Arv = L->campo;
}

void ExibeLista(Lista *L)
{
	printf("Simbolo: %d\n\tFrequencia: %.3f\n\n",L->campo->simbolo,L->campo->frequencia);
	if(L->prox!=NULL)
		ExibeLista(L->prox);
}

void ExibeTree(Tree *raiz)
{
	if(raiz != NULL)
	{
		printf("Simbolo: %c\tFrequencia: %.3f\n",raiz->simbolo,raiz->frequencia);
		ExibeTree(raiz->esq);
		ExibeTree(raiz->dir);	
	}
}

void ExibeShow(Tree *raiz, int x, int y, int dist)
{
	 if(raiz != NULL)
    {
        gotoxy(x,y);
        printf("%c", raiz->simbolo);
        if(raiz->esq != NULL)
        {
            gotoxy(x-dist/2, y+1);
            printf("/");
        }
        if(raiz->dir != NULL)
        {
            gotoxy(x+dist/2, y+1);
            printf("\\");
        }
        ExibeShow(raiz->esq, x-dist, y+2, dist/2);
        ExibeShow(raiz->dir, x+dist, y+2, dist/2);
    }
}

