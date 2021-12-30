#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"
#include "Dinamica.h"
#include "svg.h"
#include "saidasTxt.h"
#include "ListaEstatica.h"
//Exemplo de entrada dinamica ./progrdin -f arquivo.geo -q subdiretorio/arquivo.qry -o diretorioSaida
//Exemplo de entrada estatica ./progrest -f arquivo.geo -q subdiretorio/arquivo.qry -o diretorioSaida
char *Tratamento(char arq[])
{
    char *auxiliar = strrchr(arq,'/');//procura pela primeira ocorrencia da / e retorna a string posterior a /
    if (auxiliar == NULL) // se eh nulo nao foi encontrada nenhuma /
    {
        return strtok(arq,".");//se encontro retorna a string posterior a / formatada, ou seja sem a extensao
    }
    return strtok(&auxiliar[1],".");//caso nao tenha /, retornara a string atenrior ao "."
}

int main(int argc, char* argv[])
{
    char* diretorioEntrada=NULL;
    char* geo=NULL;
    char* qry=NULL;
    char* diretorioSaida=NULL;
    char* SvgConsulta=NULL;
    char* TXT=NULL;
    char* nomeSvgGrafico=NULL;
    char* TituloSvgGrafico=NULL;
    char* SVG=NULL;

    int tipoLista=0;//indica tipo de lista, 0 -> dinamica(padrao) e 1 -> estatica(caso seja passado -lse)
    int Consulta=0;//indica se ha arquivo .qry, 0 -> nao foi passado -q, 1 -> foi passado -q arquivo.qry
    int Coleta=0;//indica se eh pra haver coleta de dados, 0 -> nao foi passado -cb, 1 -> foi passado -cb
    int iniciarColeta=0;//indica se eh pra haver inicio da coleta de dados, 0 -> nao foi passado -ib, 1 -> foi passado -ib
    int FinalizaColeta=0;//indica se eh pra haver a finalizacao de coleta de dados, 0 -> nao foi passado -fb, 1 -> foi passado -fb
    int TamanhoLista,QtdVisitas;// tamanho e quantida de visitas

    int i=1;
    while(i < argc)//Parametros faltando -ib -cb -fb arq titulo //[Remover]
    {
        if(strcmp("-e",argv[i])==0)//se as string são iguais retorna 0, depois do -e vem o path caso exista
        {
            i++;
            diretorioEntrada= (char *) malloc((strlen(argv[i])+1)*sizeof(char));
            sprintf(diretorioEntrada, "%s", argv[i]); //Sprintf copia o valor de argv para diretorioEntrada
    
        }else if(strcmp("-f", argv[i]) == 0)
            {
            
                ++i; //A proxima string vai ser o nome do arquivo .geo:
                geo= (char *) malloc((strlen(argv[i])+1)*sizeof(char));
                sprintf(geo, "%s", argv[i]);//Copia o nome do arq .geo pra geo

            }else if(strcmp("-q", argv[i]) == 0)
                {

                    ++i;  //A proxima string vai ser o nome do arquivo .qry:
                    Consulta=1;//Indica que vai haver consultas
                    qry= (char *) malloc((strlen(argv[i])+1)*sizeof(char));
                    sprintf(qry, "%s", argv[i]);//Copia o nome do arq qry para variavel qry


                }else if(strcmp("-o", argv[i]) == 0)
                    {

                        ++i;  //A proxima string vai ser o nome do diretorio de arquivos de saida:
                        diretorioSaida= (char *) malloc((strlen(argv[i])+1)*sizeof(char));
                        sprintf(diretorioSaida, "%s", argv[i]);//copia pra diretorio saida o diretorio de saida

                    }else if(strcmp("-lse", argv[i])==0)//Argumento que indica que a lista usada sera a estatica
                        {
                          tipoLista=1;//1 indica q a lista é estatica
                        }else if(strcmp("-ldd", argv[i])==0)//Argumento que indica que a lista usada sera a dinamica
                            {
                            tipoLista=0;//0 indica q a lista é dinamica
                            }

        if(strcmp("-ib",argv[i])==0)
        {
            printf("\nInciando coleta de dados!\n");
            iniciarColeta=1;
        }

        if(strcmp("-cb",argv[i])==0)
        {
            printf("\nContinuando coleta de dados!\n");
            Coleta=1;//Sendo 1 indica que havera coleta de dados!
            //no final da main escrever no relatorio.txt lista->visitas e lista->size 
        }

        if(strcmp("-fb",argv[i])==0)
        {
            printf("\nFinalizando coleta de dados!\n");
            ++i;
            nomeSvgGrafico= (char *) malloc((strlen(argv[i])+1)*sizeof(char));
            sprintf(nomeSvgGrafico, "%s", argv[i]);
            ++i;
            TituloSvgGrafico= (char *) malloc((strlen(argv[i])+1)*sizeof(char));
            sprintf(TituloSvgGrafico, "%s", argv[i]);
            FinalizaColeta=1; 
        }
        i++;
    }
  
    Lista ListaDinamica;
    Lista auxiliar;//Lista do tipo dinamica auxiliar, serve pra armazenar a bounding box e o ponto x quando ha consulta bbi
    ListaEst Estatica;
    ListaEst EstatiTemp= InicializaLista(1);//cria uma estatica temporaria
    int eneX;

    if(diretorioSaida==NULL)//caso nao seja informado diretorio de saida programa eh encerrado
    {
        printf("\nErro! Diretorio de saida nao foi informado!");
        return 0;
    }

    if(geo==NULL)//caso nao seja informado um arquivo geo programa eh encerrado
    {
        printf("\nErro! Arquivo .geo nao foi informado!");
        return 0;
    }

    if(tipoLista==1)
    {
        LeituraGeo(ListaDinamica,EstatiTemp,diretorioEntrada,geo,diretorioSaida,tipoLista,&eneX,0);//vai abrir o geo so pra pegar o tamanho da estatica
        if(eneX==0)//depois de pegar o tamanho da estatica, verifica se nx =0 se eh nao ha espaco pra inserir elementos e retorna!
        {
            printf("\nTamanho invalido da Estatica!");
            LiberaEstatica(EstatiTemp);
            return 0;
        }
        Estatica= InicializaLista(eneX);
        auxiliar= Create();//Cria uma lista auxiliar para armazenar consulta que envolve bounding box caso haja
        LeituraGeo(ListaDinamica,Estatica,diretorioEntrada,geo,diretorioSaida,tipoLista,&eneX,1);
        LiberaEstatica(EstatiTemp);//Estatica temporara eh desalocada
    }

    if(tipoLista==0)
    {
        ListaDinamica= Create();
        auxiliar= Create();
        LeituraGeo(ListaDinamica,EstatiTemp,diretorioEntrada,geo,diretorioSaida,tipoLista,&eneX,1);
    }

    if(tipoLista==0)//Pra guardar os tamanhos originais da lista pra inserir no grafico quando houver -ib ou -cb ou -fb
        TamanhoLista=Tamanho(ListaDinamica);
    else
        TamanhoLista=TamanhoEst(Estatica);
    
    if(Consulta==1)
    {
        char* QRYSemExtensao=NULL;
        char* aux=NULL;//Variavel temporaria pra ser passado pro nome do arquivo txt o nome de qry sem a extensao .qry
        aux= (char *) malloc((strlen(qry)+1)*sizeof(char));
        
        strcpy(aux,qry);//copiado pra variavel aux o nome passado apos o -q
        QRYSemExtensao= Tratamento(aux);//qry sem extensao recebera so o nome do qry
    
        TXT= (char *) malloc((strlen(QRYSemExtensao)+strlen(geo)+strlen(diretorioSaida)+7) * sizeof(char));
        sprintf(TXT, "%s/%s-%s.txt",diretorioSaida,geo,QRYSemExtensao);//Concantena nome do arquivo txt de saida
        
        SvgConsulta= (char *) malloc((strlen(QRYSemExtensao)+strlen(geo)+strlen(diretorioSaida)+7) * sizeof(char));//7 pra caber o / e o .svg/0
        sprintf(SvgConsulta, "%s/%s-%s.svg",diretorioSaida,geo,QRYSemExtensao);//Concantena nome do arquivo svg de saida

        CriaArquivo(TXT);
        iniciaSvg(SvgConsulta);//vai iniciar o svg final com as consultas

        LeituraQry(ListaDinamica,auxiliar,Estatica,diretorioEntrada,qry,diretorioSaida,tipoLista,TXT);
        free(aux);//free da variavel temporaria

        if(tipoLista==0)//Gera svg final da dinamica!
            SvgQry(ListaDinamica,SvgConsulta);//nessa funcao SvgQry eu percorro a lista inteira escrevendo os retangulos existentes na lista nesse svg: svgconsulta

        if(tipoLista==1)//Gera svg final da estatica!
            SvgQryEst(Estatica,SvgConsulta);

        if(Tamanho(auxiliar)!=0)//se o tamanho da auxiliar eh diferente de 0 indica que ha lista auxiliar
        {
            SvgBounding(auxiliar,SvgConsulta);//insere a bounding box no svg
            liberalist(auxiliar);//lista auxiliar eh liberada
        }  
        finalizaSvg(SvgConsulta);//finaliza o svg final
        free(qry);
        free(TXT);
        free(SvgConsulta);
    }//free das variaveis!
    
    if(iniciarColeta==1)//Se foi dado o comando -ib vai ser inicializado um arquivo txt com nome "RelatorioTemp" no diretorio atual!
    {
        if(tipoLista==0)
        {
            QtdVisitas=Visitas(ListaDinamica);
            CriaColeta(QtdVisitas,TamanhoLista);
        }

        if(tipoLista==1)
        {
            QtdVisitas=QtVisitasEst(Estatica);
            CriaColeta(QtdVisitas,TamanhoLista);
        }
    }

    if(Coleta==1)
    {
        if(tipoLista==0)
        {
            QtdVisitas=Visitas(ListaDinamica);
            InsereDados(QtdVisitas,TamanhoLista);
        }

        if(tipoLista==1)
        {
            QtdVisitas=QtVisitasEst(Estatica);
            InsereDados(QtdVisitas,TamanhoLista);
        }
    }

    if(FinalizaColeta==1)
    {
        SVG= (char *) malloc((strlen(nomeSvgGrafico)+strlen(diretorioSaida)+6) * sizeof(char));//6 pra caber o / e o .svg/0
        sprintf(SVG, "%s/%s.svg",diretorioSaida,nomeSvgGrafico);
        iniciaSvg(SVG);
        
        if(tipoLista==0)
        {
            QtdVisitas=Visitas(ListaDinamica);
            InsereDados(QtdVisitas,TamanhoLista);
        }

        if(tipoLista==1)
        {
            QtdVisitas=QtVisitasEst(Estatica);
            InsereDados(QtdVisitas,TamanhoLista); 
        }
       
        if(QtdVisitas <= 1000)
            GeraGrafico1000("RelatorioTemp.txt",SVG,TituloSvgGrafico);
    

        if((QtdVisitas >= 1000)&&(QtdVisitas < 5000))
            GeraGrafico5000("RelatorioTemp.txt",SVG,TituloSvgGrafico);
    

        if((QtdVisitas >= 5000)&&(QtdVisitas < 10000))
            GeraGrafico10000("RelatorioTemp.txt",SVG,TituloSvgGrafico);
    

        if((QtdVisitas >= 10000)&&(QtdVisitas < 100000))
            GeraGrafico100k("RelatorioTemp.txt",SVG,TituloSvgGrafico);
    

        if((QtdVisitas >= 100000)&&(QtdVisitas < 10000000))
            GeraGrafico1Miao("RelatorioTemp.txt",SVG,TituloSvgGrafico);
    

        if(QtdVisitas >= 10000000)
            GeraGrafico10Miao("RelatorioTemp.txt",SVG,TituloSvgGrafico);
        
        finalizaSvg(SVG);//finaliza svg do grafico
        free(SVG);
        free(nomeSvgGrafico);
        free(TituloSvgGrafico);
        
        remove("RelatorioTemp.txt");//exclui o arquivo de relatorio que era temporario no diretorio atual!
    }
    free(geo);
    free(diretorioEntrada);
    free(diretorioSaida);
    if(tipoLista==0)//Se a lista eh dinamica, a lista eh liberada
        liberalist(ListaDinamica);

    if(tipoLista==1)//Se a lista eh estatica, a lista eh liberada
        LiberaEstatica(Estatica);

    return 0;
}