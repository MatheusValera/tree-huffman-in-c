#include "func.h"

void PegaArq(char *code,Reg *Rec, int *TL)
{
	char xar[2];
	FILE *dat = fopen("TabelaArv.dat","rb");
	if(dat != NULL)
	{
		fread(&Rec[*TL], sizeof(Reg), 1, dat);
		while(!feof(dat))
		{
			*TL = *TL+1;
			fread(&Rec[*TL], sizeof(Reg), 1, dat);
		}		
	}
	fclose(dat);
	FILE *txt = fopen("FraseCodificada.txt","r");
	if(txt != NULL)
	{
		fscanf(txt,"%c",&xar);
		while(!feof(txt))
		{
			strcat(code,xar);
			fscanf(txt,"%c",&xar);
		}		
	}
	fclose(txt);
}

void ExibeReg(Reg *Rec, int TL)
{
	int i;
	for(i=0; i<TL; i++)
		printf("Palavra: %s\n\tCode: %s\tSimbolo: %c\n\n",Rec[i].palavra,Rec[i].code,Rec[i].simbolo);
	
	printf("%d",TL);
}

void Decodifica(Tree *Arv, Reg *Rec, char *code, char *frase, int TL)
{
	int i, j, tam = strlen(code);
	Tree *aux;
	for(i=0;i<tam;i++)
	{
		aux = Arv;
		while(aux->simbolo == 'x')
		{
			if(code[i] == '0')
				aux = aux->esq;
			else
				aux = aux->dir;
			i++;
		}
		i--;
		j=0;
		while(j < TL && aux->simbolo != Rec[j].simbolo)
			j++;
		if(j<TL)
		{
			strcat(frase,Rec[j].palavra);
			strcat(frase," ");
		}		
	}
}

int main(void)
{
	int i,TL=0;
	char code[500],frase[500];
	Reg Rec[100];
	Tree *Arv=NULL;
	Lista *L=NULL;
	textcolor(7);
	PegaArq(code,Rec,&TL);
	InsereL(&L,Rec,TL);
	ArvHuffman(L,&Arv);
	Decodifica(Arv,Rec,code,frase,TL);
	textcolor(3);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\nFrase codificada: %s\n",code);
	textcolor(6);
	printf("\nFrase decodificada: %s\n",frase);
	//ExibeReg(Rec,TL); opcional
	gotoxy(50,1);printf("ARVORE DE HUFFMAN");
	ExibeShow(Arv,58,3,32);
	getch();
	return 1;
}
