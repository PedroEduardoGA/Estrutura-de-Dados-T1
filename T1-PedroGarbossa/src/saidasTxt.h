#ifndef _SAIDASTXT_H
#define _SAIDASTXT_H

/*Cria o arquivo TXT caso haja consultas, recebe o nome do arquivo TXT, nao retorna nada! Caso nao seja possivel criar o arquivo, retornara NULL!*/
void CriaArquivo(char arquivo[]);

/*Cria uma linha no arquivo TXT, recebe o nome do arquivo TXT, os parametros do retangulo, o tipo de consulta como "iid", a posicao do retangulo
e as cores do retangulo linha contem todas as informacoes passadas, nao retorna nada!Caso nao seja possivel abrir o arquivo, retornara NULL!*/
void CriaLinha(char arquivo[],char TipoConsulta[],int pos,char ID[],double x,double y,double larg, double alt,char Contorno[],char prenche[]);

/*Cria uma linha no arquivo TXT, dizendo que o ID nao existe na lista, recebe o nome do arquivo TXT, um ID e o tipoconsulta, 
nao retorna nada!Caso nao seja possivel abrir o arquivo, retornara NULL!*/
void IdInexiste(char arquivo[],char IDE[],char TipoConsulta[]);

/*Cria uma linha no arquivo TXT, dizendo as cores originiais dos retangulos ID, recebe o nome do arquivo TXT, um ID, cor de prenchimento e
a cor de contorno e o tipoconsulta, nao retorna nada!Caso nao seja possivel abrir o arquivo, retornara NULL!*/
void LinhaBBi(char arquivo[],char ID[],char CorPrenchi[],char CorConto[],char tipoConsulta[]);

/*Cria uma linha no arquivo TXT, dizendo que o retangulo ID foi removido, recebe o nome do arquivo TXT, um ID e o tipo, nao retorna nada!
Caso nao seja possivel abrir o arquivo, retornara NULL!*/
void RemoveuRetan(char arquivo[],char IDE[],char Tipo[]);

/*Cria uma linha no arquivo TXT, dizendo que o ID1 esta sobreposto com ID2, recebe o nome do arquivo TXT, dois ID's e o tipoconsulta, 
nao retorna nada! Caso nao seja possivel abrir o arquivo, retornara NULL!*/
void LinhaTP(char arquivo[],char Id1[],char Id2[],char tipoConsulta[]);

/*Cria o arquivo RelatorioTemp.txt no diretorio atual caso haja comando -ib, sera inserido a quantidade de visitas da lista e o tamanho da
lista final usada, recebe um int que representa a qtd de visitas e um int tamanho que eh o tamanho final da lista, nao retorna nada! Caso
nao seja possivel criar o arquivo, retornara NULL!*/
void CriaColeta(int Visits, int Tamanhu);

/*Insere quantidade de visitas e o tamanho no RelatorioTemp.txt no diretorio atual caso tenha sido criado o arquivo, funcao sera chamada
quando houver o comando -cb, sera inserido a quantidade de visitas da lista e o tamanho da lista final usada, recebe um int que representa 
a qtd de visitas e um int tamanho que eh o tamanho final da lista, nao retorna nada! Caso nao seja possivel abrir o arquivo, retornara NULL!*/
void InsereDados(int Visits, int Tamanhu);

#endif
