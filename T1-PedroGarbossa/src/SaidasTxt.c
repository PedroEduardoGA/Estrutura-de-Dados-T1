#include <stdio.h>
#include "saidasTxt.h"

void CriaArquivo(char arquivo[])
{
    FILE *arq;
    
    arq = fopen(arquivo, "w");
    if (arq == NULL){ 
        printf("Nao foi possivel Criar o Txt!");
        return;
    }
    fprintf(arq, "Saida TXT:\n");
    
    fclose(arq);
}

void CriaLinha(char arquivo[],char TipoConsulta[],int pos,char ID[],double x,double y,double larg, double alt,char Contorno[],char prenche[])//recebe nome do txt, o tipo consulta e a linha q sera escrita
{
	FILE* arq;
	
    arq = fopen(arquivo, "a");
     if (arq == NULL){
        printf("Nao foi possivel Abrir o arquivo Txt!");
        return;
    }
    fprintf(arq,"%s:\nRetangulo[%d]-Id: %s X= %lf Y= %lf Largura= %lf Altura= %lf Contorno: %s Preenchimento: %s\n",TipoConsulta,pos,ID,x,y,larg,alt,Contorno,prenche);
    fclose(arq);
}

void LinhaBBi(char arquivo[],char ID[],char CorPrenchi[],char CorConto[],char tipoConsulta[])
{   
    FILE* arq;
	
    arq = fopen(arquivo, "a");
     if (arq == NULL){
        printf("Nao foi possivel Abrir o arquivo Txt!");
        return;
    }
    fprintf(arq, "%s:\nId: %s Cores Originais-Preenchimento: %s e Contorno: %s\n",tipoConsulta,ID,CorPrenchi,CorConto);
    fclose(arq);
}

void LinhaTP(char arquivo[],char Id1[],char Id2[],char tipoConsulta[])
{
    FILE* arq;
	
    arq = fopen(arquivo, "a");
     if (arq == NULL){
        printf("Nao foi possivel Abrir o arquivo Txt!");
        return;
    }
    fprintf(arq, "%s:\nId= %s sobreposto com Id=%s\n",tipoConsulta,Id1,Id2);
    fclose(arq);
}

void IdInexiste(char arquivo[],char IDE[],char TipoConsulta[])
{
    FILE* arq;
	
    arq = fopen(arquivo, "a");
     if (arq == NULL){
        printf("Nao foi possivel Abrir o arquivo Txt!");
        return;
    }
    
    fprintf(arq, "%s:\nRetangulo com ID:%s Nao Encontrado!\n",TipoConsulta,IDE);
    
    fclose(arq);
}

void RemoveuRetan(char arquivo[],char IDE[],char Tipo[])//Da funcao DR, reporta id dos retangulos removidos!
{
    FILE* arq;
	
    arq = fopen(arquivo, "a");
     if (arq == NULL){
        printf("Nao foi possivel Abrir o arquivo Txt!");
        return;
    }
    
    fprintf(arq, "%s:\nRetanguloID:%s removido!\n",Tipo,IDE);
    
    fclose(arq);
}

//ArquivosColeta
void CriaColeta(int Visits, int Tamanhu)
{
    FILE *arq;
    
    arq = fopen("RelatorioTemp.txt", "w");
    if (arq == NULL){ 
        printf("Nao foi possivel Criar o Txt!");
        return;
    }
    fprintf(arq, "%d %d\n",Visits,Tamanhu);
    
    fclose(arq);
}

void InsereDados(int Visits, int Tamanhu)
{
    FILE* arq;
	
    arq = fopen("RelatorioTemp.txt", "a");
     if (arq == NULL){
        printf("Nao foi possivel Abrir o arquivo Txt!");
        return;
    }
    
    fprintf(arq, "%d %d\n",Visits,Tamanhu);
    fclose(arq);
}