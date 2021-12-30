#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"
#include "Dinamica.h"
#include "svg.h"
#include "ListaEstatica.h"

void LeituraGeo(Lista Dinamica,ListaEst Estatica, char* bed,char* nomeArq,char* dirSaida,int tipoLista,int *nx,int first)
{
    //TipoLista = 0 -> Lista duplamente encadeada, dinamica.
    //TipoLista = 1 -> Lista simplesmente encadeada, estatica.
    char *pathFile=NULL;
    char *svg=NULL;

    if (bed != NULL)
    {
        pathFile= (char *) malloc((strlen(bed)+strlen(nomeArq)+2) * sizeof(char));
        sprintf(pathFile, "%s/%s", bed, nomeArq);
    }else//Se for nulo
        {
            pathFile= (char *) malloc((strlen(nomeArq)+1)*sizeof(char));
            strcpy(pathFile,nomeArq);//Se nao tiver o -e, vai ser copiado pra pathFile somente o nome do geo, ja que vai estar no mesmo diretorio
        }

    FILE* ArqGeo = fopen(pathFile, "r");
    if(ArqGeo == NULL)
    {
        printf("Nao foi possivel abrir o geo!\n");
        return;
    }
    char copy_linha[150];
    char linha[150];
    char lixo[3];//Nessa variavel vai o inicio dos comandos, como r,cc,cp
    
    if(first==1)//se first == 1, se lista eh estatica eh a segunda vez que vem no geo, agora pra inserir retangulos, se lista dinamica eh a primeira e unica vez que vem
    {
        strtok(nomeArq, ".");//Formata o nome do Geo, tirando o .geo para inserir no arquivo svg inicial

        svg= (char *) malloc((strlen(dirSaida)+strlen(nomeArq)+6) * sizeof(char));//6-> 5 por causa do / .svg + 1 do /0
        sprintf(svg, "%s/%s.svg",dirSaida,nomeArq);//Vai copiar pra svg o diretoriosaida /nome do geo.svg
        iniciaSvg(svg);
    }
    int TamanhoEstatica=0;
    if(first==0)  
        *nx=TamanhoEstatica;
    
    char ID[70];
    char CorPrenche[30];
    char CorBord[30];
    double Px;
    double Py;
    double Largu;
    double Altu;   

    //é copiado pra linha cada linha do geo, ate o gets ser nulo
    while (fgets(linha, sizeof(linha), ArqGeo) != NULL)//varre o arquivo linha por linha
    {
        sprintf(copy_linha, "%s", linha);

        if (strcmp(strtok(linha, " "), "cc") == 0)//separa a linha no espaco e compara o comando
        { 
            //a parte do strtok procura na linha pelo primeiro espaco em branco
            //Depois compara pra ver se eh cc
            sscanf(copy_linha, "%s %s", lixo, CorBord);//pra lixo vai a parte do comando como cc 
            
            if(strcmp(CorBord,"@")==0)//se o caractere de cor for @ indica que nao eh pra ter cor!
                strcpy(CorBord,"none"); //eh copiado pra variavel corBord none, no svg quando tem none nao eh feito colorimento 
        }

        if (strcmp(strtok(linha, " "), "cp") == 0)
        {
            sscanf(copy_linha, "%s %s", lixo, CorPrenche);
            
            if(strcmp(CorPrenche,"@")==0)//se o caractere de cor for @ indica que nao eh pra ter cor!
                strcpy(CorPrenche,"none");
        }

        if (strcmp(strtok(linha, " "), "nx") == 0)
        {
            
            sscanf(copy_linha, "%s %d", lixo, &TamanhoEstatica);
            if((tipoLista==1)&&(first==0))
            {
                *nx=TamanhoEstatica;//vai ser modificado no conteudo do endereco que foi passado como nx o valor do tamanho
                fclose(ArqGeo);//fecha o geo
                free(pathFile);//da free no path
                return;//retorna pra main pra criar a lista estatica com o devido tamanho
            }
        }

        if (strcmp(strtok(linha, " "), "r") == 0)
        {
            sscanf(copy_linha, "%s %s %lf %lf %lf %lf",lixo, ID, &Px, &Py, &Largu, &Altu);
            criaRetangulo(Largu, Altu, Px, Py, CorBord, CorPrenche, svg);//Cria o retangulo e seus parametros no svg
            
           
            if(tipoLista==0)
                insert(Dinamica,ID,CorPrenche,CorBord,Px,Py,Largu,Altu);
            if(tipoLista==1)
            {
                TamanhoEstatica=*nx;
                InsereValor(Estatica,ID,CorPrenche, CorBord,Px, Py, Largu,Altu,TamanhoEstatica);
            }
                
        }
    }
    finalizaSvg(svg);//finaliza o svg inicial
    fclose(ArqGeo);//Fecha o geo, apos inserir na lista escolhida todos os retangulos
    free(svg);//free do nome do svg
    free(pathFile);//free do path
}

void LeituraQry(Lista din,Lista aux,ListaEst Estati,char* DiretorioEnt,char* nomeQry,char* diretSaida,int tipoLista,char* TxtSaida)
{
    //TipoLista = 0 -> Lista duplamente encadeada, dinamica.
    //TipoLista = 1 -> Lista simplesmente encadeada, estatica.
    char* pathQry=NULL;
    if (DiretorioEnt != NULL)
    {
        pathQry= (char *) malloc((strlen(nomeQry)+strlen(DiretorioEnt)+2) * sizeof(char));//2-> 1 pro / e 1 pro \0
        sprintf(pathQry, "%s/%s", DiretorioEnt, nomeQry);//Insere uma / entre o diretorio e o nome do qry 
    }
    else
        {
            pathQry= (char *) malloc((strlen(nomeQry)+1)*sizeof(char));
            strcpy(pathQry,nomeQry);//Se nao tiver o -e, vai ser copiado pra pathQry somente o nome do qry, ja que vai estar no mesmo diretorio
        }

    FILE* ArqQry = fopen(pathQry, "r");
    if(ArqQry == NULL)
    {
        printf("Nao foi possivel abrir o Qry!\n");
        return;
    }
    char CopiaLinha[150];
    char linha[150];
    char lixo[3];//Nessa variavel vai o inicio dos comandos, como tp, tpr, bbi, etc...

    //Variaveis do QRY
    char IDretan[100];
    int k;
    double Pontox;
    double Pontoy;
    double Largur;
    double Altul;

    while (fgets(linha, sizeof(linha), ArqQry) != NULL)//varre o arquivo linha por linha
    {
        sprintf(CopiaLinha, "%s", linha);//Copia tudo da linha pro CopiaLinha
        
        if ((strcmp(linha,"tp") == 0) || (strcmp(linha, "tp\n") == 0))//Se na linha estiver escrito tp vai entrar aki -> tp = update
        {  
            if(tipoLista==0)
                tp(din,TxtSaida);
            else
                tpEst(Estati,TxtSaida);
        }
        
        //strtok pega a linha e manda pra var linha a primeira string antes do espaco em branco
        if (strcmp(strtok(linha, " "), "tpr") == 0)//-> tpr = update
        {
            sscanf(CopiaLinha, "%s %lf %lf %lf %lf", lixo, &Pontox, &Pontoy, &Largur, &Altul );
            if(tipoLista==0)
                tpr(din,TxtSaida,Pontox,Pontoy,Largur,Altul);
            else
                tprEst(Estati,TxtSaida,Pontox,Pontoy,Largur,Altul);
        }

        if (strcmp(strtok(linha, " "), "dpi") == 0)//-> dpi = remove
        {
            sscanf(CopiaLinha, "%s %lf %lf",lixo, &Pontox, &Pontoy);
            if(tipoLista==0)
                Dpi(din,Pontox,Pontoy,TxtSaida);
            else
                DpiEst(Estati,Pontox,Pontoy,TxtSaida); 
        }

        if (strcmp(strtok(linha, " "), "dr") == 0)//-> dr = remove
        {
            sscanf(CopiaLinha, "%s %s ",lixo, IDretan);
            if(tipoLista==0)
                dr(din,IDretan,TxtSaida);
            else
                drEst(Estati,IDretan,TxtSaida);
        }

        if (strcmp(strtok(linha, " "), "bbi") == 0)//-> bbi = update e bounding box
        {
            sscanf(CopiaLinha, "%s %lf %lf",lixo, &Pontox, &Pontoy);
            if(tipoLista==0)
                bbi(din,aux,Pontox,Pontoy,TxtSaida);
            else
                bbiEst(Estati,aux,Pontox,Pontoy,TxtSaida);
        }

        if (strcmp(strtok(linha, " "), "bbid") == 0)//-> bbid = update e bounding box
        {
            sscanf(CopiaLinha, "%s %s",lixo, IDretan);
            if(tipoLista==0)
                bbid(din,aux,IDretan,TxtSaida);
            else    
                bbidEst(Estati,aux,IDretan,TxtSaida);
        }

        if (strcmp(strtok(linha, " "), "iid") == 0)//So falta fazer pra quando for lista estatica //-> iid = report
        {
            sscanf(CopiaLinha, "%s %s %d",lixo, IDretan, &k);
            if(tipoLista==0)
                iid(din,IDretan,k,TxtSaida);
            else
                iidEst(Estati,IDretan,k,TxtSaida);
        }

        if (strcmp(strtok(linha, " "), "diid") == 0)//-> diid = remove
        {
            sscanf(CopiaLinha, "%s %s %d",lixo, IDretan, &k);
            if(tipoLista==0)
                diid(din,IDretan,k,TxtSaida);
            else
                diidEst(Estati,IDretan,k, TxtSaida);
        }
        //Fim leitura .qry   
    }
    fclose(ArqQry);//Fecha o qry, apos ler e realizar as consultas
    free(pathQry);//free no path do qry
}