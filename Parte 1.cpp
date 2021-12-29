#include "func.h"

void Frequencia(Reg *frase,int TL)
{
	int i;
	float total =0;
	for(i=0; i<TL;i++)
		total+= frase[i].quant;
	for(i=0; i<TL; i++)
	{
		frase[i].frequencia = frase[i].quant / total;	
		frase[i].simbolo = i+33;
	}
}

void OrdenaV(Reg *frase, int TL)
{
	Reg aux;
	int i;
	while(TL>0)
	{
		for(i=0;i<TL-1;i++)
			if(frase[i].frequencia>frase[i+1].frequencia)
			{
				aux = frase[i];
				frase[i] = frase[i+1];
				frase[i+1] = aux;				
			}
		TL--;
	}
}

void DesmembraFrase(Reg *frase, char *palavras, int *TL)
{
	int i=0,j,busca;
	char info[50];
	*TL = 0;
	while(palavras[i]!= '\0')
	{
		j=0;
		while(palavras[i] != ' ' && palavras[i]!= '\0')
		{
			info[j]= palavras[i];
			i++;
			j++;
		}
		info[j] = '\0';
		busca=BuscaPalavra(frase,*TL,info);
		if(busca!=-1)
			frase[busca].quant++;
		else
		{
			strcpy(frase[*TL].palavra,info);
			frase[*TL].quant++;
			*TL = *TL + 1;
		}
		info[0]='\0';
		i++;
	}
	Frequencia(&*frase,*TL);
	OrdenaV(&*frase,*TL);
}

void Codifica(char *codif, int TL, Reg *frase, char *palavras)
{
	int i=0,j,busca;
	char info[50];
	while(palavras[i]!= '\0')
	{
		j=0;
		while(palavras[i] != ' ' && palavras[i]!= '\0')
		{
			info[j]= palavras[i];
			i++;
			j++;
		}
		info[j] = '\0';
		busca=BuscaPalavra(frase,TL,info);
		if(busca!=-1)
		{
			strcat(codif,frase[busca].code);
		}
		i++;
	}
}

void CriaCod(Tree *H, Reg *vet, int TL, char *cod,char *conc)
{
	char temp[10];
	int i;
	if(H!=NULL)
	{
		if(H->simbolo!='x')
		{
			strcat(cod,conc);
			i=0;
			while(i<TL && H->simbolo!=vet[i].simbolo)
				i++;
			if(i<TL)
				strcpy(vet[i].code,cod);
		}
		else
		{
			strcat(cod,conc);
			strcpy(temp,cod);
			CriaCod(H->esq,vet,TL,cod,"0");
			strcpy(cod,temp);
			CriaCod(H->dir,vet,TL,cod,"1");
		}	
	}
}

void GravaTabela(Reg *frase,int TL)
{
	FILE * bin = fopen("TabelaArv.dat","wb");
	int i=0;
	while(i<TL)
	{
		fwrite(&frase[i],sizeof(Reg),1,bin);
		i++;
	}
	fclose(bin);
}

void GravaFraseCodif(char codif[500])
{
	FILE *txt = fopen("FraseCodificada.txt","w");
	fprintf(txt,"%s",codif);
	fclose(txt);
}

int main()
{
	Reg frase[50];
	Lista *L=NULL;
	int TL=0,i;
	char palavras[500] = "amo como ama o amor nao conheco nenhuma outra razao para amar senao amar que queres que te diga alem de que te amo se o que quero dizer-te e que te amo";
	char codif[500], xar[10],c[2];
	xar[0] = '\0';
	codif[0]='\0';
	Tree *Arv = NULL;
	DesmembraFrase(frase,palavras,&TL);
	InsereL(&L,frase,TL);
	ArvHuffman(L,&Arv);
	CriaCod(Arv,frase,TL,xar,c);
	Codifica(codif,TL,frase,palavras);
	GravaTabela(frase,TL);
	GravaFraseCodif(codif);
	textcolor(10);
	printf("\n\n\tTabela gerada com sucesso!\n\tFrase gerada com sucesso!\n\nobs: execute o programa 2 para decodifica-la.");
	textcolor(7);
	
	return 1;
}

