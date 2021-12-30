#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dinamica.h"
#include "saidasTxt.h"
#include "svg.h"
#include "Sorteador.h"

typedef struct N{ //Onde guarda infos como, cor borda, preenchimento...
    char IdRect[70];
    char CorPrenche[30];
    char CorBord[30];
    double PontoX;
    double PontoY;
    double Largura;
    double Altura;

    struct N *ant;
    struct N *prox;
}no;

typedef struct L{
    no *primeiro; //primeiro elemento da list
    no *ultimo;   //ultimo elemento da list
    int size;
    int visitas;
}list;

Lista Create()//Aloca uma list
{
    list* lista = (list*) malloc(sizeof(list));//alloca, cria variavel e faz cast de list* lista
    //lista do tipo [primeiro][ultimo] 
    lista->primeiro= NULL;
    lista->ultimo= NULL;
    lista->size=0;
    lista->visitas=0;

    return lista;//retorna uma lista sem no interno
}

void insert(Lista l, char IdRect[70], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura)//info é o que passa pra inserir na lista e l eh uma lista!
{
    no* node = (no*) malloc(sizeof(no));//faz cast de node com no e eh alocado struct do tipo no-node tem [*ant][informacao][*prox]
    list* lista = (list*) l;//cast de list com l, cria variavel lista do tipo [primeiro][ultimo]

    strcpy(node->IdRect,IdRect);//Copia pra variavel id da lista o id do retangulo!
    strcpy(node->CorPrenche,Prenche);
    strcpy(node->CorBord,Borda);
  
    node->PontoX= PontoX;
    node->PontoY= PontoY;
    node->Largura= Largura;
    node->Altura= Altura;

    if(lista->primeiro==NULL)//Verifica se ja existe um no da lista, se for null vai ser criado o primeiro no
    {
        node->ant=NULL;//o campo [ant] do primeiro no recebe NULL pois eh o primeiro no da lista
        
        lista->primeiro=node;
        //lista eh do tipo [primeiro][ultimo] que apontam para o primeiro no e o ultimo no da lista
        
    }else//se ja existe um no
        {
            lista->ultimo->prox= node;//vai armazenar no campo [prox] do ultimo no o endereco para o no atual
            node->ant =lista->ultimo;//vai armazenar no campo[ant]do no atual o endereco para o no anterior
        }
    lista->visitas++;
    lista->size++;
    node->prox=NULL;//vai armazenar no campo [proximo]do no atual o NULL
    lista->ultimo=node;//o [ultimo] de lista recebe o endereco do no atual criado
}

void print(Lista l)
{
    list* lista = (list*) l;//Cast da variavel lista com list*
    no* node= lista->primeiro;//struct node recebe endereco para o primeiro no da lista
    
    int i=0;
    while(node!=NULL)//enquanto nao chega no ultimo no vai imprimindo
    {
        printf("\n[%d] ID: %s",i,node->IdRect);
        printf("PontoX= %lf, PontoY= %lf, Larg= %lf, Alt= %lf",node->PontoX,node->PontoY,node->Largura,node->Altura);
        printf("CorPrenchi-> %s e CorBorda-> %s",node->CorPrenche,node->CorBord);
        node= node->prox;//percorre todos os nos da lista
        i++;
    }
}

int Tamanho(Lista l)//Novo
{
    list *lista = (list *) l;//faz cast de l com a struct de list e nomeia l de lista
    
    if(lista->primeiro == NULL) 
        return 0;
    
    return lista->size;
}

int Visitas(Lista l)
{
    list *lista = (list *) l;//faz cast de l com a struct de list e nomeia l de lista

    return lista->visitas;
}

void RemoveElemento(Lista l, char id[])
{
    list *lista = (list *) l;//faz cast de l com a struct de list e nomeia l de lista
    no *node = lista->primeiro;//criado um node do tipo no, que aponta pro primeiro elemento da lista
    no *aux;

    while((strcmp(node->IdRect,id)!=0)&&(node!=NULL))//Quando encontrar o elemento vai parar no noh em que o elemento se encontra
    {
        if(node->ant!=NULL)
            aux=node;//aux recebe noh anterior

        lista->visitas++;
        node = node->prox;// atribui a node o proximo noh
    }

    if(strcmp(node->IdRect,id)!=0)//id nao existe na lista
        return;

    if(lista->primeiro == node)//elemento eh o primeiro da lista eh o primeiro noh da lista tratamento diferente
    {
        
        if(node->prox == NULL)//indica que esse eh o unico noh da lista
        {
            lista->primeiro=NULL;
            lista->ultimo=NULL;
        
            free(node);
            lista->size--;
            return;
        }
        aux=node->prox;//aux eh o segundo elemento da lista
        aux->ant=NULL;
        lista->primeiro=aux;//Primeiro elemento da lista vai apontar para o proximo
    
        free(node);
        lista->size--;
        return;
    }

    if(lista->ultimo == node)//elemento eh o ultimo da lista
    {
        //eh o primeiro noh da lista tratamento diferente
        aux=node->ant;//aux eh o noh anterior
        aux->prox=NULL;
        lista->ultimo=aux;//Ultimo elemento da lista vai apontar para o anterior
        
        free(node);
        lista->size--;
        return;
    }

    if(strcmp(node->IdRect,id)==0)
    {
        aux->prox=node->prox;//Campo proximo do noh anterior vai receber o proximo noh do atual
        node->prox->ant=aux;//Campo anterior do proximo noh vai receber o noh aux
        free(node);
    
        lista->size--;
        return;
    }
    return;
}

void liberalist(Lista l)
{
    list *lista = (list *) l;//faz cast de l com a struct de list
    no *node = lista->primeiro;//criado um node do tipo no, que aponta pro primeiro elemento da lista
    no *aux;//criado um aux do tipo no

    while(node != NULL)
    {
        aux = node;//atribui a aux o valor de node atual
        node = node->prox;// atribui a node o proximo noh

        free(aux);//free no noh atual de aux
    }
    free(node);
    free(lista);//libera a malloc da lista
}

void InsereAfter(Lista L,char IdRect[70], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura, int i)
{
    list *lista = (list *) L;//faz cast de l com a struct de list e nomeia l de lista
    no *node=lista->primeiro;
    int x=0;

    if((i>=lista->size)||(i<0))
    {
        printf("\nPosicao inexistente!");
        return;
    }

    while (x<i)
    {
        node=node->prox;
        x++;
    }

    no* aux= (no*) malloc(sizeof(no));
    strcpy(aux->IdRect,IdRect);//Copia pra variavel id da lista o id do retangulo!
    strcpy(aux->CorPrenche,Prenche);
    strcpy(aux->CorBord,Borda);

    aux->PontoX= PontoX;
    aux->PontoY= PontoY;
    aux->Largura= Largura;
    aux->Altura= Altura;//aux eh o novo q sera inserido
    aux->prox=node->prox;//prox de aux recebe o endereco do proximo do noh
    node->prox=aux;
    aux->ant=node;
    if(i==(lista->size - 1))//se i for a ultima posicao da lista
        lista->ultimo=aux;

    lista->size++;
}

void InsereBefore(Lista L,char IdRect[70], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura, int i)
{
    list *lista = (list *) L;//faz cast de l com a struct de list e nomeia l de lista
    no *node=lista->primeiro;
    int x=0;

    if((i>=lista->size)||(i<0))
    {
        printf("\nPosicao inexistente!");
        return;
    }
    while (x<i)
    {
        node=node->prox;
        x++;
    }

    if(node==lista->primeiro)//caso queira inserir antes do primeiro elemento
    {
        no* aux= (no*) malloc(sizeof(no));
        strcpy(aux->IdRect,IdRect);//Copia pra variavel id da lista o id do retangulo!
        strcpy(aux->CorPrenche,Prenche);
        strcpy(aux->CorBord,Borda);

        aux->PontoX= PontoX;
        aux->PontoY= PontoY;
        aux->Largura= Largura;
        aux->Altura= Altura;//aux eh o novo q sera inserido
        aux->ant=node->ant;
        node->ant=aux;
        aux->prox=node;
        lista->size++;
        lista->primeiro=aux;
        
        return;
    }

    if(node==lista->ultimo)//caso queira inserir antes do primeiro elemento
    {
        no* aux= (no*) malloc(sizeof(no));
        strcpy(aux->IdRect,IdRect);//Copia pra variavel id da lista o id do retangulo!
        strcpy(aux->CorPrenche,Prenche);
        strcpy(aux->CorBord,Borda);

        aux->PontoX= PontoX;
        aux->PontoY= PontoY;
        aux->Largura= Largura;
        aux->Altura= Altura;//aux eh o novo q sera inserido
        aux->prox=node;//prox de aux recebe o endereco do noh atual
        aux->ant=node->ant;
        node->ant->prox=aux;
        node->ant=aux;
        lista->size++;
        
        return;
    }    
    no* aux= (no*) malloc(sizeof(no));
    strcpy(aux->IdRect,IdRect);//Copia pra variavel id da lista o id do retangulo!
    strcpy(aux->CorPrenche,Prenche);
    strcpy(aux->CorBord,Borda);

    aux->PontoX= PontoX;
    aux->PontoY= PontoY;
    aux->Largura= Largura;
    aux->Altura= Altura;//aux eh o novo q sera inserido
    //Trocas
    aux->prox=node;//prox de aux recebe o endereco do noh atual
    aux->ant=node->ant;
    node->ant->prox=aux;
    node->ant=aux;
    
    lista->size++;
}

No GetLast(Lista L)
{
    list *lista = (list *) L;
    if(lista->size==0)
        return NULL;

    return lista->ultimo;
}

No GetFirst(Lista L)
{
    list *lista = (list *) L;
    if(lista->size==0)
        return NULL;

    return lista->primeiro;
}

No GetNext(Lista L,int pos)
{
    list *lista = (list *) L;
    no* node= lista->primeiro;

    int x=0;
    if(lista->size==0)
        return NULL;

    while((x<pos)&&(node!=NULL))
    {
        lista->visitas++;
        node=node->prox;
        x++;
    }
    return node->prox;
}

No GetPrevious(Lista L, int pos)
{
    list *lista = (list *) L;
    no* node= lista->primeiro;
    if(node==NULL)//lista vazia
        return NULL;

    int x=0;
    while((x<pos)&&(node!=NULL))
    {
        lista->visitas++;
        node=node->prox;
        x++;
    }
    return node->ant;
}

No GetElemento(Lista L,char IdRect[70])//Util
{
    list *lista = (list *) L;
    no* node= lista->primeiro;

    lista->visitas++;
    if(node==NULL)//lista vazia
        return NULL;

    while((strcmp(node->IdRect,IdRect)!=0)&&(node!=NULL))
    {
        lista->visitas++;
        node=node->prox;
    }
    if(strcmp(node->IdRect,IdRect)!=0)
        return NULL;

    return node;
}
//============FuncoesDeConsulta============
void iid(Lista l,char ide[],int ka, char txt[])//Sem saida SVG
{
    list *lista = (list *) l;//Cria uma variavel lista que recebe conteudo de list*
    no *node= lista->primeiro;//Cria variavel node do tipo no e atribui o primeiro noh da lista
    
    lista->visitas++;
    int i=0,k;
    int achei=0;
    k=ka;
    if(k < 0)
        k=k*-1;
    
    if(k >= lista->size)
    {
        printf("\nErro na Consulta iid o valor de K eh maior que  o tamanho da lista!\n");
        return;
    }

    while((node!=NULL)&&(strcmp(node->IdRect,ide)!=0))//Anda pela lista ate achar o id desejado ou acabar a lista
    {
        lista->visitas++;
        node= node->prox;//percorre todos os nos da lista 
    }
    
    if(node!=NULL)
    {
       if(strcmp(node->IdRect,ide)==0)//ve se o id do noh atual eh o id passado
            achei=1; 
    }
    
    if(achei==0)//se achei eh 0 eh porque o id informado nao foi encontrado!
    {
        IdInexiste(txt,ide,"iid");
        return;
    }

    if(ka<0)
    {
        CriaLinha(txt,"iid",i,node->IdRect,node->PontoX,node->PontoY,node->Largura,node->Altura,node->CorBord,node->CorPrenche);
        i--;
        while((node->ant!=NULL)&&(i>=ka))
        {
            
            node= node->ant; 
            lista->visitas++;
            CriaLinha(txt,"iid",i,node->IdRect,node->PontoX,node->PontoY,node->Largura,node->Altura,node->CorBord,node->CorPrenche);
            i--;
        }
        //Percorreu a lista de tras pra frente
    }else
        {
            CriaLinha(txt,"iid",i,node->IdRect,node->PontoX,node->PontoY,node->Largura,node->Altura,node->CorBord,node->CorPrenche);
            i++;
            while((node->prox!=NULL)&&(i<=ka))
            {
                
                node= node->prox; 
                lista->visitas++;
                CriaLinha(txt,"iid",i,node->IdRect,node->PontoX,node->PontoY,node->Largura,node->Altura,node->CorBord,node->CorPrenche);
                i++;
            }
        }//Fimelse
    //FinalFuncaoiid
}

void tp(Lista L,char txt[])
{
    list *lista = (list *) L;//Cria uma variavel lista que recebe conteudo de list*
    no *node1= lista->primeiro;
    no *node2;
    char Cores[30];
    double x2_node1,y2_node1,x2_node2,y2_node2;

    if(node1!=NULL)
        node2=node1->prox;

    if(node2==NULL)
        return;

    while(node1->prox!=NULL)
    {   
        x2_node1=node1->PontoX+node1->Largura;
        y2_node1=node1->PontoY+node1->Altura;
        while(node2!=NULL)
        {
            
            x2_node2=node2->PontoX+node2->Largura;
            y2_node2=node2->PontoY+node2->Altura; 
            if((node1->PontoX < x2_node2)&&(x2_node1 > node2->PontoX)&&(node1->PontoY < y2_node2)&&(y2_node1 > node2->PontoY))
            {
                //Entrou tem sobreposicao
                strcpy(Cores,Sorteio());
                strtok(Cores," ");//Formata a string
                strcpy(node1->CorPrenche,Cores);
                strcpy(node2->CorPrenche,Cores);
                LinhaTP(txt,node1->IdRect,node2->IdRect,"tp");
            }
            lista->visitas++;
            node2=node2->prox;
        }
        lista->visitas++;
        node1=node1->prox;
        node2=node1->prox;
    }
    return;
}

void tpr(Lista l,char txt[],double x1,double y1,double larg,double alt)
{
    double X2,Y2;//x1 eh x passado, x2=x1+largura, y1 eh y passado, y2=y1+altura
    double x2_node1,y2_node1,x2_node2,y2_node2;
    char Cores[30];
    list *lista = (list *) l;//Cria uma variavel lista que recebe conteudo de list*
    no *node1= lista->primeiro;
    no *node2;

    X2= x1+larg;//Vai calcular o x2 do retangulo passado como parametro
    Y2= y1+alt;//Vai calcular o x2 do retangulo passado como parametro
    if(node1!=NULL)
        node2=node1->prox;

    if(node2==NULL)
        return;

    while(node1->prox!=NULL)
    {   
        x2_node1=node1->PontoX+node1->Largura;//x2 do no anterior
        y2_node1=node1->PontoY+node1->Altura;//y2 do no anterior
        while(node2!=NULL)
        {
            x2_node2=node2->PontoX+node2->Largura;//x2 do no atual
            y2_node2=node2->PontoY+node2->Altura; //y2 do no atual
            if((node1->PontoX >= x1)&&(x2_node1 < X2)&&(node1->PontoY >= y1)&&(y2_node1 < Y2) && (node2->PontoX >= x1)&&(x2_node2 < X2)&&(node2->PontoY >= y1)&&(y2_node2 < Y2))//verifica se os retangulos estao dentro do retangulo
            {
                if((node1->PontoX < x2_node2)&&(x2_node1 > node2->PontoX)&&(node1->PontoY < y2_node2)&&(y2_node1 > node2->PontoY))//sobreposicao
                {
                //Entrou tem sobreposicao
                strcpy(Cores,Sorteio());
                strtok(Cores," ");//Formata a string
                strcpy(node1->CorPrenche,Cores);
                strcpy(node2->CorPrenche,Cores);
                LinhaTP(txt,node1->IdRect,node2->IdRect,"tpr");
                }
            }
            lista->visitas++;
            node2=node2->prox;
        }
        lista->visitas++;
        node1=node1->prox;
        node2=node1->prox;
    }
    return;
}

void dr(Lista L, char Ide[70],char txt[])
{
    list *lista = (list *) L;
    no* aux;

    aux=GetElemento(lista,Ide);//Vai pegar o noh do retangulo que possuir o id passado!
    if(aux==NULL)
        return;

    double x,y,w,h,x2,y2,Xr2,Yr2;

    x=aux->PontoX;//Parametros do retangulo ID passado!
    y=aux->PontoY;
    w=aux->Largura;
    h=aux->Altura;
    x2= x+w;//Vai calcular o x2 do retangulo passado como parametro
    y2= y+h;//Vai calcular o y2 do retangulo passado como parametro

    aux=lista->primeiro;
    while(aux!=NULL)
    {
        Xr2=aux->PontoX+aux->Largura;
        Yr2=aux->PontoY+aux->Altura;
        if((aux->PontoX >= x)&&(Xr2 < x2)&&(aux->PontoY >= y)&&(Yr2 < y2))//Se verdade esta inteiramente dentro do retangulo passado
        {
            //Achou um inteiramente dentro do retangulo passado
            RemoveuRetan(txt,aux->IdRect,"dr");
            RemoveElemento(lista,aux->IdRect);//ta acessando lixo        
        }
        lista->visitas++;
        aux= aux->prox; 
    }
}

void bbi(Lista L,Lista auxi,double x, double y,char txt[])
{
    list *lista = (list *) L;
    no *node= lista->primeiro;

    double x2_node,y2_node,menorX1,menorY1,maiorX2,maiorY2;
    double Xr,Yr,Wr,Hr;
    char corAux[30];
    
    menorX1=node->PontoX;
    menorY1=node->PontoY;
    maiorX2=node->PontoX+node->Largura;
    maiorY2=node->PontoY+node->Altura;;

    while(node!=NULL)
    {   
        Xr=node->PontoX;
        Yr=node->PontoY;
        Wr=node->Largura;
        Hr=node->Altura;
        x2_node=node->PontoX+node->Largura;//x2 do retangulo atual
        y2_node=node->PontoY+node->Altura;//y2 do retangulo atual
        if((x>Xr)&&(x< Xr+Wr)&&(y> Yr)&&(y< Yr+Hr))//Se verdade ponto X e Y sao internos do retangulo
        {
            //Achou um retangulo que tem X e Y passados como ponto interno!
            LinhaBBi(txt,node->IdRect,node->CorPrenche,node->CorBord,"bbi");

            strcpy(corAux,node->CorBord);//atribui a cor de contorno pra uma variavel aux
            strcpy(node->CorBord,node->CorPrenche);//troca a cor de contorno com a de preenchimento
            strcpy(node->CorPrenche,corAux);//troca a cor de preechimento com a cor de contorno original
            if(node->PontoX < menorX1)
                menorX1=node->PontoX;
            
            if(node->PontoY < menorY1)
                menorY1=node->PontoY;

            if(x2_node > maiorX2)
                maiorX2= x2_node;

            if(y2_node > maiorY2)
                maiorY2= y2_node;  
        }
        lista->visitas++;
        node= node->prox; 
    }
    insert(auxi,"bbi","none","red",menorX1,menorY1,maiorX2-menorX1,maiorY2-menorY1);
    insert(auxi,"p","red","black",x,y,4,0);
}

void bbid(Lista L,Lista auxilia,char ID[],char txt[])
{
    list *listaAux = (list *) auxilia;
    list *lista = (list *) L;
    no* aux;

    double X,Y,X2,Y2,auxX2,auxY2,LargBB,AltBB;
    char corAux[30];
    aux=GetElemento(lista,ID);

    if(aux==NULL)
        return;
    
    X=aux->PontoX;
    Y=aux->PontoY;
    X2= X+aux->Largura;//Vai calcular o x2 do retangulo passado como parametro
    Y2= Y+aux->Altura;
    LargBB=aux->Largura;
    AltBB=aux->Altura;

    aux=lista->primeiro;
    while(aux!=NULL)
    {   
        auxX2=aux->PontoX+aux->Largura;
        auxY2=aux->PontoY+aux->Altura;
        if((aux->PontoX >= X)&&(auxX2 < X2)&&(aux->PontoY >= Y)&&(auxY2 < Y2))//criterio pra saber se retangulo analisado ta dentro do id
        {
            //Achou um retangulo que tem X e Y passados como ponto interno!
            LinhaBBi(txt,aux->IdRect,aux->CorPrenche,aux->CorBord,"bbid");

            strcpy(corAux,aux->CorBord);//atribui a cor de contorno pra uma variavel aux
            strcpy(aux->CorBord,aux->CorPrenche);//troca a cor de contorno com a de preenchimento
            strcpy(aux->CorPrenche,corAux);//troca a cor de preechimento com a cor de contorno original
        }
        lista->visitas++;
        aux= aux->prox; 
    }
    insert(listaAux,"bbid","none","red",X,Y,LargBB,AltBB);   
}

void Dpi(Lista L,double X, double Y,char txt[])
{
    list *lista = (list *) L;
    no *node= lista->primeiro;
    double Xr,Wr,Yr,Hr;//x,y,w,h dos retangulos analisados

    while(node!=NULL)
    {   
        Xr=node->PontoX;
        Yr=node->PontoY;
        Wr=node->Largura;
        Hr=node->Altura;
        if((X>Xr)&&(X< Xr+Wr)&&(Y> Yr)&&(Y< Yr+Hr))//Se verdade ponto X e Y sao internos do retangulo
        {
            //Achou um retangulo que tem X e Y passados como ponto interno!
            RemoveuRetan(txt,node->IdRect,"dpi");
            RemoveElemento(lista,node->IdRect);       
        }
        lista->visitas++;
        node= node->prox; 
    }
}

void diid(Lista l,char ide[],int ka, char txt[])//
{
    list *lista = (list *) l;//Cria uma variavel lista que recebe conteudo de list*
    no *node= lista->primeiro;//Cria variavel node do tipo no e atribui o primeiro noh da lista
    
    int i=0;
    int achei=0;
    int k;
    k=ka;
    if(k < 0)
        k=k*-1;
    
    if(k >= lista->size)
    {
        printf("\nErro na Consulta diid o valor de K eh maior que  o tamanho da lista!\n");
        return;
    }

    while((node!=NULL)&&(strcmp(node->IdRect,ide)!=0))//Anda pela lista ate achar o id desejado ou acabar a lista
    {
        lista->visitas++;
        node= node->prox;//percorre todos os nos da lista 
    } 
    
    if(node!=NULL)
    {
       if(strcmp(node->IdRect,ide)==0)//ve se o id do noh atual eh o id passado
            achei=1; 
    }
    
    if(achei==0)//se achei eh 0 eh porque o id informado nao foi encontrado!
    {
        IdInexiste(txt,ide,"diid");
        return;
    }

    if(ka<0)
    {
        CriaLinha(txt,"diid",i,node->IdRect,node->PontoX,node->PontoY,node->Largura,node->Altura,node->CorBord,node->CorPrenche);
        i--;
        while((node->ant!=NULL)&&(i>=ka))
        {
            node= node->ant; 
            lista->visitas++;
           
            CriaLinha(txt,"diid",i,node->IdRect,node->PontoX,node->PontoY,node->Largura,node->Altura,node->CorBord,node->CorPrenche);
            RemoveElemento(lista,node->IdRect);
            i--;
        }
        //Percorreu a lista de tras pra frente
    }else
        {
            CriaLinha(txt,"diid",i,node->IdRect,node->PontoX,node->PontoY,node->Largura,node->Altura,node->CorBord,node->CorPrenche);
            i++;
            while((node->prox!=NULL)&&(i<=ka))
            {
                node= node->prox; 
                lista->visitas++;

                CriaLinha(txt,"diid",i,node->IdRect,node->PontoX,node->PontoY,node->Largura,node->Altura,node->CorBord,node->CorPrenche);
                RemoveElemento(lista,node->IdRect);
                i++;
            }
            //fimwhile
        }
    //FinalFuncaodiid
}

void SvgQry(Lista L, char nomeSvG[])//Funcao que gera o svg final, pos consultas!
{
    list *lista = (list *) L;
    no *node= lista->primeiro;
    while(node!=NULL)
    {
        criaRetangulo(node->Largura,node->Altura,node->PontoX,node->PontoY,node->CorBord,node->CorPrenche,nomeSvG);
        lista->visitas++;
        node=node->prox;
    }
}

void SvgBounding(Lista auxilia,char svg[])
{
    list *lista = (list *) auxilia;//Cria uma variavel lista que recebe conteudo de list*
    no *node= lista->primeiro;
    while(node!=NULL)
    {
        if(node->Altura!=0)
            criaBoundingBox(node->PontoX,node->PontoY,node->Largura,node->Altura,node->CorBord,svg);
        else
            CriaPontinho(node->PontoX,node->PontoY,node->Largura,node->CorBord,node->CorPrenche,svg);

        lista->visitas++;
        node=node->prox;
    }
}

void BoundingBox(Lista l, char IdRect[70], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura)//info é o que passa pra inserir na lista e l eh uma lista!
{
    no* node = (no*) malloc(sizeof(no));//faz cast de node com no e eh alocado struct do tipo no-node tem [*ant][informacao][*prox]
    list* lista = (list*) l;//cast de list com l

    strcpy(node->IdRect,IdRect);//Copia pra variavel id da lista o id do retangulo!
    strcpy(node->CorPrenche,Prenche);
    strcpy(node->CorBord,Borda);
  
    node->PontoX= PontoX;
    node->PontoY= PontoY;
    node->Largura= Largura;
    node->Altura= Altura;

    if(lista->primeiro==NULL)//Verifica se ja existe um no da lista, se for null vai ser criado o primeiro no
    {
        node->ant=NULL;//o campo [ant] do primeiro no recebe NULL pois eh o primeiro no da lista
        
        lista->primeiro=node;
        //lista eh do tipo [primeiro][ultimo] que apontam para o primeiro no e o ultimo no da lista
        
    }else//se ja existe um no
        {
            lista->ultimo->prox= node;//vai armazenar no campo [prox] do ultimo no o endereco para o no atual
            node->ant =lista->ultimo;//vai armazenar no campo[ant]do no atual o endereco para o no anterior
        }
    
    lista->size++;
    node->prox=NULL;//vai armazenar no campo [proximo]do no atual o NULL
    lista->ultimo=node;//o [ultimo] de lista recebe o endereco do no atual criado
}