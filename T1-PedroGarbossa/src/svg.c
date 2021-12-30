#include <stdio.h>
#include "svg.h"

void iniciaSvg(char arq[])//recebe nome do svg
{
    FILE *arquivo;
    
    arquivo = fopen(arq, "w");
    if (arquivo == NULL)
    { 
        printf("Nao foi possivel criar o arquivo svg!");
        return;
    }
    fprintf(arquivo, "<svg xmlns='http://www.w3.org/2000/svg'>");//Link para visualizacao na web
    
    fclose(arquivo);
}

void finalizaSvg(char arq[])//recebe nome do svg
{
	FILE* arquivo;
	
    arquivo = fopen(arq, "a");
    if (arquivo == NULL)
    {
        printf("Nao foi possivel Abrir o arquivo svg para finaliza-lo!");
        return;
    }
    fprintf(arquivo, "\n</svg>");
    
    fclose(arquivo);
}

void criaLinha(double x1, double y1, double x2, double y2, char cor[], char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o svg para criacao da linha!");
        return;
	}
	fprintf(arq, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:%s\" />\n", x1, y1, x2, y2, cor);//cria uma linha de x1,y1 ate x2,y2
    fclose(arq);
}

void criaRetangulo(double largura, double altura, double x, double y, char cor1[], char cor2[], char svg[])//Cor2 Preenche
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o o svg pra criar um retangulo!");
        return;
	}
	fprintf(arq, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" />\n", x, y, largura, altura, cor2, cor1);
    fclose(arq);
}

void CriaPontinho(double x,double y, double raio,char Contorno[],char Preenchimento[],char svg[])
{   
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o svg pra criar um circulo!");
        return;
	}
	fprintf(arq, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"1\" fill=\"%s\"/>\n",x,y,raio,Contorno,Preenchimento);
    fclose(arq);
}

void criaBoundingBox(double x, double y,double largura, double altura, char cor1[], char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o svg para criar a bounding box!");
        return;
	}
	fprintf(arq, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"none\" stroke=\"%s\" fill-opacity=\"0\" stroke-width=\"2\" stroke-dasharray=\"5\" />\n",x, y, largura, altura, cor1);
    fclose(arq);
}

void TextoSvg(float x, float y, char texto[], char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if(arq == NULL)
    {
        printf("Nao foi possivel abrir o svg pra criacao de texto!");
    }
    fprintf(arq, "\n\t<text x=\"%f\" y=\"%f\" fill=\"black\">%s</text>", x, y, texto);
    fclose(arq);
}

void GeraGrafico1000(char txt[],char svg[],char titulo[])//grafico vai de 50 em 50
{
    char linha[30],coordenada[20];
    double visitou,tamanhoList;
    float x,y,escala;

    IniciaInversao(svg,1150.0);
    criaLinha(0.0,0.0, 1000.0, 0.0,"black",svg);
    criaLinha(0.0,0.0, 0.0, 1000.0,"black",svg);

    FILE* ArqTXT = fopen(txt, "r");
    if(ArqTXT == NULL)
    {
        printf("Nao foi possivel abrir o Txt Temporario!\n");
        return;
    }

    while (fgets(linha, sizeof(linha), ArqTXT) != NULL)
    {
        sscanf(linha, "%lf %lf", &visitou, &tamanhoList );
        CriaPontinho(tamanhoList,visitou,2.5,"red","black",svg);
        LinhaTracejada(0.0,visitou,tamanhoList, visitou,"black",svg);
        LinhaTracejada(tamanhoList,0.0,tamanhoList,visitou,"black",svg);
    }
    FinalizaInversao(svg);

    escala= 1000.0;
    x=0.0;
    y=0.0;
    while(x <= escala)
    {
        sprintf(coordenada, "%.0f", x);
        TextoSvg(x,1170.0,coordenada,svg);
        CriaPontinho(x,1150.0,2.0,"black","black",svg);
        x+=50.0;
    }

    escala= 1150.0;//escala eh o numero maximo de visitas permitido + 150!
    x=150.0;//150 por padrao pra ficar abaixo da folha do svg
    y=1000.0;
    while(x <= escala)
    {
        sprintf(coordenada, "%.0f", y);
        TextoSvg(-30.0,x,coordenada,svg);
        CriaPontinho(0.0,x,2.0,"black","black",svg);
        y-=50.0;
        x+=50.0;
    }
    TextoSvg(-15.0,130.0,"Visitas",svg);
    TextoSvg(960.0,1200.0,"Tamanho",svg);
    TextoSvg(400.0,1190.0,titulo,svg);
    fclose(ArqTXT);
}

void GeraGrafico5000(char txt[],char svg[],char titulo[])//grafico vai de 500 em 500
{
    char linha[30],coordenada[20];
    double visitou,tamanhoList;
    float x,y,escala;

    IniciaInversao(svg,5150.0);
    criaLinha(0.0,0.0, 5000.0, 0.0,"black",svg);
    criaLinha(0.0,0.0, 0.0, 5000.0,"black",svg);

    FILE* ArqTXT = fopen(txt, "r");
    if(ArqTXT == NULL)
    {
        printf("Nao foi possivel abrir o Txt Temporario!\n");
        return;
    }

    while (fgets(linha, sizeof(linha), ArqTXT) != NULL)//varre o arquivo temporario pegando as coordenadas dos pontos
    {
        sscanf(linha, "%lf %lf", &visitou, &tamanhoList );
        CriaPontinho(tamanhoList,visitou,3.0,"red","black",svg);//cria o ponto
        LinhaTracejada(0.0,visitou,tamanhoList, visitou,"black",svg);//cria uma linha tracejada ate o ponto
        LinhaTracejada(tamanhoList,0.0,tamanhoList,visitou,"black",svg);
    }
    FinalizaInversao(svg);

    escala= 5000.0;
    x=0.0;
    while(x <= escala)
    {
        sprintf(coordenada, "%.0f", x);
        TextoSvg(x,5170.0,coordenada,svg);
        CriaPontinho(x,5150.0,2.0,"black","black",svg);
        x+=500.0;
    }

    escala= 5150.0;//escala eh o numero maximo de visitas permitido + 150!
    x=150.0;//150 por padrao pra ficar abaixo da folha do svg
    y=5000.0;
    while(x <= escala)
    {
        sprintf(coordenada, "%.0f", y);
        TextoSvg(-35.0,x,coordenada,svg);
        CriaPontinho(0.0,x,2.0,"black","black",svg);
        y-=500.0;
        x+=500.0;
    }
    TextoSvg(-15.0,130.0,"Visitas",svg);
    TextoSvg(4600.0,5200.0,"Tamanho",svg);
    TextoSvg(1500.0,5200.0,titulo,svg);
    fclose(ArqTXT);
}

void GeraGrafico10000(char txt[],char svg[],char titulo[])//grafico vai de 1000 em 1000
{
    char linha[30],coordenada[20];
    double visitou,tamanhoList;
    float x,y,escala;

    IniciaInversao(svg,10150.0);
    criaLinha(0.0,0.0, 10000.0, 0.0,"black",svg);
    criaLinha(0.0,0.0, 0.0, 10000.0,"black",svg);

    FILE* ArqTXT = fopen(txt, "r");
    if(ArqTXT == NULL)
    {
        printf("Nao foi possivel abrir o Txt Temporario!\n");
        return;
    }

    while (fgets(linha, sizeof(linha), ArqTXT) != NULL)//varre o arquivo temporario pegando as coordenadas dos pontos
    {
        sscanf(linha, "%lf %lf", &visitou, &tamanhoList );
        CriaPontinho(tamanhoList,visitou,3.0,"red","black",svg);//cria o ponto
        LinhaTracejada(0.0,visitou,tamanhoList, visitou,"black",svg);//cria uma linha tracejada ate o ponto
        LinhaTracejada(tamanhoList,0.0,tamanhoList,visitou,"black",svg);
    }
    FinalizaInversao(svg);

    escala= 10000.0;
    x=0.0;
    while(x <= escala)
    {
        sprintf(coordenada, "%.0f", x);
        TextoSvg(x,10170.0,coordenada,svg);//coordenada y eh escala + 170
        CriaPontinho(x,10150.0,2.0,"black","black",svg);
        x+=1000.0;
    }

    escala= 10150.0;//escala eh o numero maximo de visitas permitido + 150!
    x=150.0;//150 por padrao pra ficar abaixo da folha do svg
    y=10000.0;
    while(x <= escala)
    {
        sprintf(coordenada, "%.0f", y);
        TextoSvg(-45.0,x,coordenada,svg);
        CriaPontinho(0.0,x,2.0,"black","black",svg);
        y-=1000.0;
        x+=1000.0;
    }
    TextoSvg(-15.0,130.0,"Visitas",svg);
    TextoSvg(9600.0,10200.0,"Tamanho",svg);
    TextoSvg(5600.0,10220.0,titulo,svg);//titulo eh insreido na coordena x= meio e y= escala+200
    fclose(ArqTXT);
}

void GeraGrafico100k(char txt[],char svg[],char titulo[])//grafico vai de 10.000 em 10.000
{
    char linha[30],coordenada[20];
    double visitou,tamanhoList;
    float x,y,escala;

    IniciaInversao(svg,100150.0);
    criaLinha(0.0,0.0, 100000.0, 0.0,"black",svg);
    criaLinha(0.0,0.0, 0.0, 100000.0,"black",svg);

    FILE* ArqTXT = fopen(txt, "r");
    if(ArqTXT == NULL)
    {
        printf("Nao foi possivel abrir o Txt Temporario!\n");
        return;
    }

    while (fgets(linha, sizeof(linha), ArqTXT) != NULL)//varre o arquivo temporario pegando as coordenadas dos pontos
    {
        sscanf(linha, "%lf %lf", &visitou, &tamanhoList );
        CriaPontinho(tamanhoList,visitou,3.0,"red","black",svg);//cria o ponto
        LinhaTracejada(0.0,visitou,tamanhoList, visitou,"black",svg);//cria uma linha tracejada ate o ponto
        LinhaTracejada(tamanhoList,0.0,tamanhoList,visitou,"black",svg);
    }
    FinalizaInversao(svg);

    escala= 100000.0;
    x=0.0;
    while(x <= escala)
    {
        sprintf(coordenada, "%.0f", x);
        TextoSvg(x,100170.0,coordenada,svg);//coordenada y eh escala + 170
        CriaPontinho(x,100150.0,2.0,"black","black",svg);
        x+=10000.0;
    }

    escala= 100150.0;//escala eh o numero maximo de visitas permitido + 150!
    x=150.0;//150 por padrao pra ficar abaixo da folha do svg
    y=100000.0;
    while(x <= escala)
    {
        sprintf(coordenada, "%.0f", y);
        TextoSvg(-50.0,x,coordenada,svg);
        CriaPontinho(0.0,x,2.0,"black","black",svg);
        y-=10000.0;
        x+=10000.0;
    }
    TextoSvg(-15.0,130.0,"Visitas",svg);
    TextoSvg(96000.0,100200.0,"Tamanho",svg);
    TextoSvg(55600.0,100220.0,titulo,svg);//titulo eh insreido na coordena x= meio e y= escala+200
    fclose(ArqTXT);
}

void GeraGrafico1Miao(char txt[],char svg[],char titulo[])//grafico vai de 25.000 em 25.000
{
    char linha[30],coordenada[20];
    double visitou,tamanhoList;
    float x,y,escala;

    IniciaInversao(svg,1000150.0);
    criaLinha(0.0,0.0, 1000000.0, 0.0,"black",svg);
    criaLinha(0.0,0.0, 0.0, 1000000.0,"black",svg);

    FILE* ArqTXT = fopen(txt, "r");
    if(ArqTXT == NULL)
    {
        printf("Nao foi possivel abrir o Txt Temporario!\n");
        return;
    }

    while (fgets(linha, sizeof(linha), ArqTXT) != NULL)//varre o arquivo temporario pegando as coordenadas dos pontos
    {
        sscanf(linha, "%lf %lf", &visitou, &tamanhoList );
        CriaPontinho(tamanhoList,visitou,3.0,"red","black",svg);//cria o ponto
        LinhaTracejada(0.0,visitou,tamanhoList, visitou,"black",svg);//cria uma linha tracejada ate o ponto
        LinhaTracejada(tamanhoList,0.0,tamanhoList,visitou,"black",svg);
    }
    FinalizaInversao(svg);

    escala= 1000000.0;
    x=0.0;
    while(x <= escala)
    {
        sprintf(coordenada, "%.0f", x);
        TextoSvg(x,1000170.0,coordenada,svg);//coordenada y eh escala + 170
        CriaPontinho(x,1000150.0,2.0,"black","black",svg);
        x+=25000.0;
    }

    escala= 1000150.0;//escala eh o numero maximo de visitas permitido + 150!
    x=150.0;//150 por padrao pra ficar abaixo da folha do svg
    y=1000000.0;
    while(x <= escala)
    {
        sprintf(coordenada, "%.0f", y);
        TextoSvg(-65.0,x,coordenada,svg);
        CriaPontinho(0.0,x,2.0,"black","black",svg);
        y-=25000.0;
        x+=25000.0;
    }
    TextoSvg(-15.0,130.0,"Visitas",svg);
    TextoSvg(960000.0,1000200.0,"Tamanho",svg);
    TextoSvg(550600.0,1000220.0,titulo,svg);//titulo eh insreido na coordena x= meio e y= escala+200
    fclose(ArqTXT);
}

void GeraGrafico10Miao(char txt[],char svg[],char titulo[])//Grafico de 10 milhoes até 50 milhoes, percorre de 100.000 em 100.000
{
    char linha[30],coordenada[20];
    double visitou,tamanhoList;
    float x,y,escala;

    IniciaInversao(svg,50000150.0);
    criaLinha(0.0,0.0, 50000000.0, 0.0,"black",svg);
    criaLinha(0.0,0.0, 0.0, 50000000.0,"black",svg);

    FILE* ArqTXT = fopen(txt, "r");
    if(ArqTXT == NULL)
    {
        printf("Nao foi possivel abrir o Txt Temporario!\n");
        return;
    }

    while (fgets(linha, sizeof(linha), ArqTXT) != NULL)//varre o arquivo temporario pegando as coordenadas dos pontos
    {
        sscanf(linha, "%lf %lf", &visitou, &tamanhoList );
        CriaPontinho(tamanhoList,visitou,3.0,"red","black",svg);//cria o ponto
        LinhaTracejada(0.0,visitou,tamanhoList, visitou,"black",svg);//cria uma linha tracejada ate o ponto
        LinhaTracejada(tamanhoList,0.0,tamanhoList,visitou,"black",svg);
    }
    FinalizaInversao(svg);

    escala= 50000000.0;//continuar
    x=0.0;
    while(x <= escala)
    {
        sprintf(coordenada, "%.0f", x);
        TextoSvg(x,50000170.0,coordenada,svg);//coordenada y eh escala + 170
        CriaPontinho(x,50000150.0,4.0,"black","black",svg);
        x+=100000.0;
    }

    escala= 50000150.0;//escala eh o numero maximo de visitas permitido + 150!
    x=150.0;//150 por padrao pra ficar abaixo da folha do svg
    y=50000000.0;
    while(x <= escala)
    {
        sprintf(coordenada, "%.0f", y);
        TextoSvg(-85.0,x,coordenada,svg);
        CriaPontinho(0.0,x,4.0,"black","black",svg);
        y-=100000.0;
        x+=100000.0;
    }
    TextoSvg(-15.0,130.0,"Visitas",svg);
    TextoSvg(47000000.0,50000200.0,"Tamanho",svg);
    TextoSvg(3000600.0,50000220.0,titulo,svg);//titulo eh insreido na coordena x= meio e y= escala+200
    fclose(ArqTXT);
}

void IniciaInversao(char svg[],double coordenadaY)//inverte o que estiver dentro do <g> verticalmente
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo do Grafico!");
        return;
	}
	fprintf(arq,"\n\t<g id=\"g666\" transform=\"matrix(1,0,0,-1,0,%lf)\" >",coordenadaY);

    fclose(arq);
}

void FinalizaInversao(char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo do Grafico!");
        return;
	}
	fprintf(arq,"\n</g>");

    fclose(arq);
}

void LinhaTracejada(double x1, double y1, double x2, double y2, char cor[], char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo de saida");
        return;
	}
	fprintf(arq, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-dasharray=\"5,5\"/>\n", x1, y1, x2, y2, cor);
    fclose(arq);
}