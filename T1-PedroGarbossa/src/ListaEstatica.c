#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaEstatica.h"
#include "saidasTxt.h"
#include "svg.h"
#include "Sorteador.h"
#include "Dinamica.h"
//Inlcui o dinamica.h pra quando houver consulta BBi ou BBid armazenar em uma lista auxiliar as coordenadas da bounding box!

typedef struct node{//Define a estrutra do no, aqui eh armazenado as informacoes
    char ID[80];
    char CorPrenchimento[30];
    char CorContor[30];
    double PX;
    double PY;
    double Largura;
    double Altura;
    int prox;
}Noh;//Nomeia essa estrutura como Noh

typedef struct list{//Define uma estrutura da lista, armazena um vetor de noh com MaxTam
    Noh *Item;//crio um vetor com nome Item do tipo struct de noh 
    int Taman,Primeiro, Ultimo,QtdVisitas;
}Estatica;//Nomeia essa estrutura como Estatica

ListaEst InicializaLista(int Tamanho)//Em uso!
{
    Estatica* lista = (Estatica*)malloc(sizeof(Estatica));//Casting e alloca espaco pra uma variavel lista da struct Estatica
    lista->Item= (Noh*)malloc(Tamanho*sizeof(Noh));
    
    lista->Primeiro=-1;
    lista->Ultimo=0;
    lista->Taman=0;
    lista->QtdVisitas=0;

    return lista;//Retorna a lista vazia
}

void LiberaEstatica(ListaEst L)//Em uso!
{   
    Estatica* Lista = (Estatica*) L;
    free(Lista->Item);
    free(Lista);
}

int Vazia (ListaEst L)//Verifica se a lista esta vazia Em uso!
{
    Estatica* Lista = (Estatica*) L;
    
    if(Lista->Primeiro == Lista->Ultimo)//Compara se o primeiro elemento eh igual ao ultimo
        return 1;//se for volta 1 dizendo que a lista eh vazia
    else
        return 0;//senao volta 0 dizendo q a lista nao eh vazia
}

int QtVisitasEst(ListaEst L)//Em uso!
{
    Estatica* Lista = (Estatica*) L;
    return Lista->QtdVisitas;
}

int GetPosicaoElemento(ListaEst L,char Ide[70],double *X,double *Y,double *Largu,double *Altu)//Em uso!
{
    Estatica* lista = (Estatica*) L;
    int pos;
    pos=lista->Primeiro;
    while((lista->Item[pos].prox != -1)&&(strcmp(lista->Item[pos].ID,Ide)!=0))
    {
        pos=lista->Item[pos].prox;
        lista->QtdVisitas++;
    }
        
    if(strcmp(lista->Item[pos].ID,Ide)!=0)
        return -2;//-2 indica posicao inexistente, isso sera retornado quando o ID nao existir na lista!

    *X= lista->Item[pos].PX;
    *Y= lista->Item[pos].PY;
    *Largu= lista->Item[pos].Largura;
    *Altu= lista->Item[pos].Altura;

    return pos;
}

void InsereBeforeEst(ListaEst L,double X, double Y, double largura, double altura,int pos, int Tamanho)//insere elemento antes da posicao
{
    Estatica* lista = (Estatica*) L;//Nao esta sendo usada!
    int x;
    if (lista->Taman > Tamanho-1)
    {
        printf ("Lista esta cheia!\n");
        return;
    }
    if(pos==0)
    {
        printf("\nPosicao invalida, impossivel inserir em posicoes menores que 0!");
        return;
    }
    x=lista->Primeiro;
    while(lista->Item[x].prox!=pos)
        x=lista->Item[x].prox;//pega elemento anterior ao pos

    lista->Item[x].PX=X;
    lista->Item[x].PY=Y;
    lista->Item[x].Largura=largura;
    lista->Item[x].Altura=altura;
    lista->Item[x].prox=pos;
    lista->Taman++;
}

void InsereAfterEst(ListaEst L,double X, double Y, double largura, double altura,int pos, int Tamanho)//insere elemento antes da posicao
{
    Estatica* lista = (Estatica*) L;//Nao esta sendo usada!
    int x,y;
    if (lista->Taman > Tamanho-1)
    {
        printf ("Lista esta cheia!\n");
        return;
    }
    
    if(pos== lista->Taman-1)
    {
        printf("\nPosicao invalida, impossivel inserir em posicoes maiores que o fim da lista!");
        return;
    }
    x=lista->Primeiro;
    while(lista->Item[x].prox!=pos)
        x=lista->Item[x].prox;//pega elemento anterior ao pos

    x=lista->Item[x].prox;//elemento do pos
    x=lista->Item[x].prox;
    y=lista->Item[x].prox;
    lista->Item[x].PX=X;
    lista->Item[x].PY=Y;
    lista->Item[x].Largura=largura;
    lista->Item[x].Altura=altura;
    lista->Item[x].prox=y;
    lista->Taman++;
}

void InsereValor(ListaEst L,char Id[80],char Cor1[30], char Cor2[30],double X, double Y, double largura, double altura,int Tamanho)
{
    Estatica* lista = (Estatica*) L;
    //Em uso!
    if (lista->Taman > Tamanho-1)
        return;
    //Se ultimo elemento da lista for indice maior ou igual ao tamanho qr dizer q a lista ta cheia
    //Cor1 - Preenche e Cor2 - Contorno
    strcpy(lista->Item[lista->Taman].ID,Id);
    strcpy(lista->Item[lista->Taman].CorPrenchimento,Cor1);
    strcpy(lista->Item[lista->Taman].CorContor,Cor2);
    lista->Item[lista->Taman].PX=X;
    lista->Item[lista->Taman].PY=Y;
    lista->Item[lista->Taman].Largura=largura;
    lista->Item[lista->Taman].Altura=altura;

    if(lista->Primeiro == -1)//eh o primeiro elemento da lista
        lista->Primeiro=0;
    else
        lista->Item[lista->Taman-1].prox=lista->Taman;
    
    lista->Item[lista->Taman].prox=-1;
    lista->Ultimo=lista->Taman;
    lista->Taman++;
    lista->QtdVisitas++;
}

void Imprime (ListaEst Li)//Nao eh usado
{
    Estatica* L = (Estatica*) Li;
    if(Vazia (L)==1)
    {
        printf("\nLista Vazia!");
        return;
    }
    int x= L->Primeiro;
    
    //printf ("\nL Estatica: ");
    while( x!= L->Taman)//imprime do primeiro elemento ao ultimo da lista 
    {
        printf ("\n[%d] CorPren: %s e CorBord: %s, X= %lf e Y= %lf, Larg= %lf e Altu= %lf ", x,L->Item[x].CorPrenchimento,L->Item[x].CorContor,L->Item[x].PX,L->Item[x].PY,L->Item[x].Largura,L->Item[x].Altura);//imprime o valor da posicao x da lista
        L->QtdVisitas++;
        x=L->Item[x].prox;
        if(x == -1)
            break;
    }
}

int TamanhoEst(ListaEst L)//Em uso!
{
    Estatica* Lista = (Estatica*) L;//Estatica typedef da struct da lista
    return Lista->Taman;
}

void RemoveElemen(ListaEst L,int p)//Em uso!
{
    Estatica* Lista = (Estatica*) L;
    int x;
    
    if(p < 0)
        return;
    
    if(Lista->Ultimo == Lista->Primeiro)//Só tem um elemento na lista
    {
        Lista->Primeiro=-1;
        Lista->Ultimo=-1;
    }else if(p == Lista->Primeiro)//Se a posicao eh o primeiro noh
        {
            Lista->Primeiro=Lista->Item[p].prox;
        }else if(Lista->Ultimo != p)
            {
                x=Lista->Primeiro;
                while (Lista->Item[x].prox != p)
                {
                    x=Lista->Item[x].prox;
                    Lista->QtdVisitas++;
                }  
                Lista->Item[x].prox=Lista->Item[p].prox;
            }
            else if(Lista->Ultimo == p)//se p eh a ultima posicao
                {
                    x=Lista->Primeiro;
                    while (Lista->Item[x].prox != p)
                    {
                        x=Lista->Item[x].prox;
                        Lista->QtdVisitas++;
                    }
                        
                    Lista->Ultimo=x;
                    Lista->Item[x].prox=-1;
                }
    Lista->Taman--;
}

int GetFirstEst(ListaEst L)
{
    Estatica* Lista = (Estatica*) L;//Nao esta sendo usada!
    return Lista->Primeiro;
}

int GetLastEst(ListaEst L)
{
    Estatica* Lista = (Estatica*) L;//Nao esta sendo usada!
    return Lista->Ultimo;
}

int GetPreviousEst(ListaEst L, int pos)
{
    Estatica* Lista = (Estatica*) L;//Nao esta sendo usada!
    int x;
    x=Lista->Primeiro;
    if(x==pos)
    {
        return -1;
    }else
        {
            while(Lista->Item[x].prox != pos)
                x=Lista->Item[x].prox;

            return x;
        }
}

int GetNextEst(ListaEst L, int pos)
{
    Estatica* Lista = (Estatica*) L;//Nao esta sendo usada!
    return Lista->Item[pos].prox;
}

//==============FuncoesConsultas================
void tpEst(ListaEst L,char txt[])
{
    Estatica* Lista = (Estatica*) L;
    int x= Lista->Primeiro;//x esta no primeiro item da lista
    int y;
    
    if(Lista->Item[x].prox == -1)
        return;

    y=Lista->Item[x].prox;//y esta a um item na frente de x

    char Cores[30];

    double x2_node1,y2_node1,x2_node2,y2_node2;

    while(Lista->Item[x].prox != -1)
    {   
        x2_node1=Lista->Item[x].PX+Lista->Item[x].Largura;
        y2_node1=Lista->Item[x].PY+Lista->Item[x].Altura;
        while(y != -1)
        {
            
            x2_node2=Lista->Item[y].PX+Lista->Item[y].Largura;
            y2_node2=Lista->Item[y].PY+Lista->Item[y].Altura;
            if((Lista->Item[x].PX < x2_node2)&&(x2_node1 > Lista->Item[y].PX)&&(Lista->Item[x].PY < y2_node2)&&(y2_node1 > Lista->Item[y].PY))
            {
                //Entrou tem sobreposicao
                strcpy(Cores,Sorteio());
                strtok(Cores," ");//Formata a string
                strcpy(Lista->Item[x].CorPrenchimento,Cores);
                strcpy(Lista->Item[y].CorPrenchimento,Cores);
                LinhaTP(txt,Lista->Item[x].ID,Lista->Item[y].ID,"tp");
            }
            Lista->QtdVisitas++;
            y=Lista->Item[y].prox;
            if(y == -1)//Caso seja ultimo elemento
                break;
        }
        Lista->QtdVisitas++;
        x=Lista->Item[x].prox;
        y=Lista->Item[x].prox;
    }
    return;
}

void tprEst(ListaEst l,char txt[],double x1,double y1,double larg,double alt)
{
    double X2,Y2;//x1 eh x passado, x2=x1+largura, y1 eh y passado, y2=y1+altura
    double x2_node1,y2_node1,x2_node2,y2_node2;
    
    char Cores[30];
    Estatica* Lista = (Estatica*) l;
    int x= Lista->Primeiro;//x esta no primeiro item da lista
    int y;
    
    if(Lista->Item[x].prox == -1)//Qr dizer só tem um elemento na lista
        return;

    y=Lista->Item[x].prox;//y esta a um item na frente de x

    X2= x1+larg;//Vai calcular o x2 do retangulo passado como parametro
    Y2= y1+alt;//Vai calcular o x2 do retangulo passado como parametro
    while(Lista->Item[x].prox != -1)
    {   
        x2_node1=Lista->Item[x].PX+Lista->Item[x].Largura;
        y2_node1=Lista->Item[x].PY+Lista->Item[x].Altura;
        while(y != -1)
        {
            x2_node2=Lista->Item[y].PX+Lista->Item[y].Largura;
            y2_node2=Lista->Item[y].PY+Lista->Item[y].Altura;
            if((Lista->Item[x].PX >= x1)&&(x2_node1 < X2)&&(Lista->Item[x].PY >= y1)&&(y2_node1 < Y2) && (Lista->Item[y].PX >= x1)&&(x2_node2 < X2)&&(Lista->Item[y].PY >= y1)&&(y2_node2 < Y2))//verifica se os retangulos estao dentro do retangulo
            {
                if((Lista->Item[x].PX < x2_node2)&&(x2_node1 > Lista->Item[y].PX)&&(Lista->Item[x].PY < y2_node2)&&(y2_node1 > Lista->Item[y].PY))//sobreposicao
                {
                //Entrou tem sobreposicao
                strcpy(Cores,Sorteio());
                strtok(Cores," ");//Formata a string
                strcpy(Lista->Item[x].CorPrenchimento,Cores);
                strcpy(Lista->Item[y].CorPrenchimento,Cores);
                LinhaTP(txt,Lista->Item[x].ID,Lista->Item[y].ID,"tpr");
                }
            }
            Lista->QtdVisitas++;
            y=Lista->Item[y].prox;
            if(y == -1)//Caso seja ultimo elemento
                break;
        }
        Lista->QtdVisitas++;
        x=Lista->Item[x].prox;
        y=Lista->Item[x].prox;
    }
}

void DpiEst(ListaEst L,double X, double Y,char txt[])
{
    Estatica* Lista = (Estatica*) L;
    int x= Lista->Primeiro;
    double Xr,Wr,Yr,Hr;//x,y,w,h dos retangulos analisados
    int pos;
    double xt,yt,wt,ht;

    while(x != -1)
    {   
        Xr=Lista->Item[x].PX;
        Yr=Lista->Item[x].PY;
        Wr=Lista->Item[x].Largura;
        Hr=Lista->Item[x].Altura;
        if((X>Xr)&&(X< Xr+Wr)&&(Y> Yr)&&(Y< Yr+Hr))//Se verdade ponto X e Y sao internos do retangulo
        {
            //Achou um retangulo que tem X e Y passados como ponto interno!
            pos=GetPosicaoElemento(Lista,Lista->Item[x].ID,&xt,&yt,&wt,&ht);
            if(pos == -2)//significa que o ID informado nao existe
                return;

            RemoveuRetan(txt,Lista->Item[x].ID,"dpi");
            RemoveElemen(Lista,pos);     
        }
        Lista->QtdVisitas++;
        x=Lista->Item[x].prox;
        if(x == -1)//Caso seja ultimo elemento
                break;
    }
}

void drEst(ListaEst L, char Ide[70],char txt[])
{
    Estatica* Lista = (Estatica*) L;
    int i= Lista->Primeiro;
    int pos;
    double x,y,w,h,x2,y2,Xr2,Yr2;;
    double xt,yt,wt,ht;

    pos=GetPosicaoElemento(Lista,Ide,&x,&y,&w,&h);//Vai pegar as informacoes do item com o id passado e sua posicao
    if(pos == -2)//ID informado nao existe na lista!
        return;

    x2= x+w;//Vai calcular o x2 do retangulo passado como parametro
    y2= y+h;//Vai calcular o y2 do retangulo passado como parametro

    while(i != -1)
    {
        Xr2=Lista->Item[i].PX+Lista->Item[i].Largura;
        Yr2=Lista->Item[i].PY+Lista->Item[i].Altura;
        if((Lista->Item[i].PX >= x)&&(Xr2 < x2)&&(Lista->Item[i].PY >= y)&&(Yr2 < y2))//Se verdade esta inteiramente dentro do retangulo passado
        {
            //Achou um inteiramente dentro do retangulo passado
            RemoveuRetan(txt,Lista->Item[i].ID,"dr");
            pos=GetPosicaoElemento(Lista,Lista->Item[i].ID,&xt,&yt,&wt,&ht);
            if(pos == -2)//significa que o ID informado nao existe
                return;

            RemoveElemen(Lista,pos);//remove o elemento da posicao         
        }
        Lista->QtdVisitas++;
        i= Lista->Item[i].prox;
        if(i == -1)//Caso seja ultimo elemento
                break;
    }
}

void bbiEst(ListaEst L,Lista auxi,double x, double y,char txt[])
{
    Estatica* Lista = (Estatica*) L;
    int i= Lista->Primeiro;

    double x2_node,y2_node,menorX1,menorY1,maiorX2,maiorY2;
    double Xr,Yr,Wr,Hr;
    char corAux[30];
    
    if( i == -1)//Significa que a lista esta vazia
        return;

    menorX1=Lista->Item[i].PX;
    menorY1=Lista->Item[i].PY;
    maiorX2=Lista->Item[i].PX+Lista->Item[i].Largura;
    maiorY2=Lista->Item[i].PY+Lista->Item[i].Altura;

    while(i != -1)
    {   
        Xr=Lista->Item[i].PX;
        Yr=Lista->Item[i].PY;
        Wr=Lista->Item[i].Largura;
        Hr=Lista->Item[i].Altura;
        x2_node=Lista->Item[i].PX+Lista->Item[i].Largura;//x2 do retangulo atual
        y2_node=Lista->Item[i].PY+Lista->Item[i].Altura;//y2 do retangulo atual
        if((x>Xr)&&(x< Xr+Wr)&&(y> Yr)&&(y< Yr+Hr))//Se verdade ponto X e Y sao internos do retangulo
        {
            //Achou um retangulo que tem X e Y passados como ponto interno!
            LinhaBBi(txt,Lista->Item[i].ID,Lista->Item[i].CorPrenchimento,Lista->Item[i].CorContor,"bbi");

            strcpy(corAux,Lista->Item[i].CorContor);//atribui a cor de contorno pra uma variavel aux
            strcpy(Lista->Item[i].CorContor,Lista->Item[i].CorPrenchimento);//troca a cor de contorno com a de preenchimento
            strcpy(Lista->Item[i].CorPrenchimento,corAux);//troca a cor de preechimento com a cor de contorno original

            if(Lista->Item[i].PX < menorX1)
                menorX1=Lista->Item[i].PX;
            
            if(Lista->Item[i].PY < menorY1)
                menorY1=Lista->Item[i].PY;

            if(x2_node > maiorX2)
                maiorX2= x2_node;

            if(y2_node > maiorY2)
                maiorY2= y2_node;  
        }
        Lista->QtdVisitas++;
        i= Lista->Item[i].prox;
        if(i == -1)//Caso seja ultimo elemento
                break;
    }
    BoundingBox(auxi,"bbi","none","red", menorX1, menorY1, maiorX2-menorX1,maiorY2-menorY1);
    BoundingBox(auxi,"ponto","red","black", x, y,4,0);
}

void bbidEst(Lista L,Lista auxilia,char ID[],char txt[])
{
    Estatica* Lista = (Estatica*) L;
    int i= Lista->Primeiro;
    int pos;

    if(i == -1)
        return;

    double X,Y,LargBB,AltBB;//X e Y, Larg e Alt sao os parametros do retangulo ID
    double auxX2,auxY2,X2,Y2;//X2 e Y2 eh do retangulo ID passado
    char corAux[30];
    pos=GetPosicaoElemento(Lista,ID,&X,&Y,&LargBB,&AltBB);

    if(pos == -2)
        return;
    
    X2= X+LargBB;//Vai calcular o x2 do retangulo passado como parametro
    Y2= Y+AltBB;

    while(i != -1)
    {   
        auxX2=Lista->Item[i].PX+Lista->Item[i].Largura;
        auxY2=Lista->Item[i].PY+Lista->Item[i].Altura;
        if((Lista->Item[i].PX >= X)&&(auxX2 < X2)&&(Lista->Item[i].PY >= Y)&&(auxY2 < Y2))//criterio pra saber se retangulo analisado ta dentro do id
        {
            //Achou um retangulo que tem X e Y passados como ponto interno!
            LinhaBBi(txt,Lista->Item[i].ID,Lista->Item[i].CorPrenchimento,Lista->Item[i].CorContor,"bbid");

            strcpy(corAux,Lista->Item[i].CorContor);//atribui a cor de contorno pra uma variavel aux
            strcpy(Lista->Item[i].CorContor,Lista->Item[i].CorPrenchimento);//troca a cor de contorno com a de preenchimento
            strcpy(Lista->Item[i].CorPrenchimento,corAux);//troca a cor de preechimento com a cor de contorno original
        }
        Lista->QtdVisitas++;
        i= Lista->Item[i].prox; 
        if(i == -1)//Caso seja ultimo elemento
                break;
    }  
    BoundingBox(auxilia,"bbid","none","red",X,Y, LargBB,AltBB);
}

void iidEst(ListaEst li,char ide[],int ka, char txt[])//Sem saida SVG
{
    Estatica* L = (Estatica*) li;
    int pos,percorri;
    double xt,yt,wt,ht;

    if( Vazia(L)==1)
        return;
    
    pos=GetPosicaoElemento(L,ide,&xt,&yt,&wt,&ht);//pos vai receber a posicao que se enconra o elemento ide
    if(pos==-2)//se posicao = -2 quer dizer que o elemento ide nao foi encontrado!
    {
        IdInexiste(txt,ide,"iid");
        return;
    }

    int i,k;
    k=ka;
    percorri=0;
    if(k < 0)
        k=k*-1;

    if(k >= L->Taman)//verifica se k n eh maior que tamanho da lista
    {
        printf("\nErro na Consulta iid o valor de K eh maior que  o tamanho da lista!\n");
        return;
    }

    if((pos == L->Primeiro)&&( ka < 0))
    {
        printf("\nImpossivel reportar id anterior ao primeiro elemento da lista!");
        return;
    }

    if((pos == L->Ultimo)&&( ka > 0))
    {
        printf("\nImpossivel reportar id do proximo ao ultimo elemento da lista!");
        return;
    }

    i=pos;
    while(percorri <= k)//k vai ser um valor positivo e percorri vai reportas k vezes os dados
    {
        if(percorri == 0)//Pra reportar parametros do retangulo ID !
        {
            CriaLinha(txt,"iid",i,L->Item[i].ID,L->Item[i].PX,L->Item[i].PY,L->Item[i].Largura,L->Item[i].Altura,L->Item[i].CorContor,L->Item[i].CorPrenchimento);
            percorri++;
        }
        
        if(ka<0)
        {
            i=L->Primeiro;
            while((L->Item[i].prox != pos)&&(i != -1))//vai ate o elemento anterior a posicao do atual
            {
                i=L->Item[i].prox;
                L->QtdVisitas++;
            }
            pos=i;
            CriaLinha(txt,"iid",i,L->Item[i].ID,L->Item[i].PX,L->Item[i].PY,L->Item[i].Largura,L->Item[i].Altura,L->Item[i].CorContor,L->Item[i].CorPrenchimento);
            percorri++;
            //Percorreu a lista procurando o elemento anterior
        }else
            {
                i=L->Item[pos].prox;
                while((i != -1)&&(percorri <= k))
                {
                    CriaLinha(txt,"iid",i,L->Item[i].ID,L->Item[i].PX,L->Item[i].PY,L->Item[i].Largura,L->Item[i].Altura,L->Item[i].CorContor,L->Item[i].CorPrenchimento);
                    percorri++;
                    L->QtdVisitas++;
                    i=L->Item[i].prox;
                    if(i == -1)//Caso seja ultimo elemento
                        break;
                }
                //pra chegar aki vai ter reportados os elementos proximos de item[id] k vezes!
            }
    }
    //FinalFuncaoiid
}

void diidEst(ListaEst li,char ide[],int ka, char txt[])//Sem saida SVG
{
    Estatica* L = (Estatica*) li;

    int pos,percorri;
    double xt,yt,wt,ht;

    if( Vazia(L)==1)   
        return;

    pos=GetPosicaoElemento(L,ide,&xt,&yt,&wt,&ht);//pos vai receber a posicao que se enconra o elemento ide
    if(pos==-2)//se posicao = -2 quer dizer que o elemento ide nao foi encontrado!
    {
        IdInexiste(txt,ide,"diid");
        return;
    }

    int i,k,aux,fixa;
    k=ka;
    percorri=0;
    if(k < 0)
        k=k*-1;

    if(k >= L->Taman)//verifica se k n eh maior que tamanho da lista
    {
        printf("\nErro na Consulta diid o valor de K eh maior que  o tamanho da lista!\n");
        return;
    }

    if((pos == L->Primeiro)&&( ka < 0))
    {
        printf("\nImpossivel reportar id anterior ao primeiro elemento da lista!");
        CriaLinha(txt,"diid",pos,L->Item[pos].ID,L->Item[pos].PX,L->Item[pos].PY,L->Item[pos].Largura,L->Item[pos].Altura,L->Item[pos].CorContor,L->Item[pos].CorPrenchimento);
        return;
    }

    if((pos == L->Ultimo)&&( ka > 0))
    {
        printf("\nImpossivel reportar id do proximo ao ultimo elemento da lista!");
        CriaLinha(txt,"diid",pos,L->Item[pos].ID,L->Item[pos].PX,L->Item[pos].PY,L->Item[pos].Largura,L->Item[pos].Altura,L->Item[pos].CorContor,L->Item[pos].CorPrenchimento);
        return;
    }

    i=pos;
    while(percorri <= k)//k vai ser um valor positivo e percorri vai reportas k vezes os dados
    {
        if(percorri == 0)//Pra reportar parametros do retangulo ID !
        {
            CriaLinha(txt,"diid",i,L->Item[i].ID,L->Item[i].PX,L->Item[i].PY,L->Item[i].Largura,L->Item[i].Altura,L->Item[i].CorContor,L->Item[i].CorPrenchimento);
            percorri++;
        }
        
        if(ka<0)
        {
            fixa=pos;
            i=L->Primeiro;
            while((L->Item[i].prox != fixa)&&(i != -1))//vai ate o elemento anterior a posicao do atual
            {
                i=L->Item[i].prox;
                L->QtdVisitas++;
            }
            CriaLinha(txt,"diid",i,L->Item[i].ID,L->Item[i].PX,L->Item[i].PY,L->Item[i].Largura,L->Item[i].Altura,L->Item[i].CorContor,L->Item[i].CorPrenchimento);
            RemoveElemen(L,i);
            percorri++;
        }else
            {
                i=L->Item[pos].prox;
                while((i != -1)&&(percorri <= k))
                {
                    CriaLinha(txt,"diid",i,L->Item[i].ID,L->Item[i].PX,L->Item[i].PY,L->Item[i].Largura,L->Item[i].Altura,L->Item[i].CorContor,L->Item[i].CorPrenchimento);
                    percorri++;
                    aux=i;
                    L->QtdVisitas++;
                    i=L->Item[i].prox;
                    if(i == -1)//Caso seja ultimo elemento
                        break;
                    RemoveElemen(L,aux);
                }
                //pra chegar aki vai ter reportados os elementos proximos de item[id] k vezes!
            }
    }
    //FinalFuncaoDiid
}

void SvgQryEst(ListaEst Li, char nomeSvG[])//Funcao que gera o svg final, pos consultas!
{
    Estatica* L = (Estatica*) Li;
    int x= L->Primeiro;
    while(x != -1)
    {
        criaRetangulo(L->Item[x].Largura,L->Item[x].Altura,L->Item[x].PX,L->Item[x].PY,L->Item[x].CorContor,L->Item[x].CorPrenchimento,nomeSvG);
        L->QtdVisitas++;
        x=L->Item[x].prox;
        if(x == -1)//Caso seja ultimo elemento
                break;
    }
}