#ifndef _LISTAESTATICA_H
#define _LISTAESTATICA_H
#include "Dinamica.h"
//Cabecalho da lista Estatica simplesmente encadeada, quando me refirir a lista quero dizer Lista Estatica!
//Incluso o dinamica.h para ser reconhecido o void pointer Lista, que tem na funcao BBi e BBid

typedef void* TipoItem;//Void Pointer
typedef void* ListaEst;//Void Pointer

/*Cria uma lista vazia com o tamanho informado! Recebe o tamanho e alloca memoria para tamanho*item, e alloca memoria pra estrutura da lista,
Nao retorna nada!*/
ListaEst InicializaLista(int Tamanho);

/*Libera a memoria que foi allocada pra comportar a lista, recebe a lista e da free nos lista->item que libera toda memoria dos nohs e
da free na lista, que libera a memoria da lista! Nao retorna nada!*/
void LiberaEstatica(ListaEst L);

/*Verifica se a lista esta vazia, recebe a lista e compara o lista->primeiro com o lista->ultimo, se as posicoes forem iguais, significa
que a lista esta vazia e retorna 1, caso contrario indica que a lista nao esta vazia e retorna 0!*/
int Vazia (ListaEst L);

/*Pega a posicao do elemento com id igual ao ide que eh passado, recebe a lista, um id de retangulo, e o endereco de variaveis de parametros,
percorre a lista comparando o id do item[x] com o ide que eh passado, se for igual retorna a posicao, e o conteudo das variaveis que foi
informado o endereco sao alterados para os valores do item[posicao], caso o id seja invalido retorna -2 ja que o retangulo com aquele id, 
nao existe na lista!*/
int GetPosicaoElemento(ListaEst L,char Ide[70],double *X,double *Y,double *Largu,double *Altu);

/*Insere os parametros na posicao livre da lista, recebe a lista e os parametros do retangulo e o tamanho maximo que a lista suporta,
se o tamanho atual da lista for igual ao tamanho maximo, sera informado que a lista esta cheia, caso contrario, sera inserido os valores
na lista, nao retorna nada!*/
void InsereValor(ListaEst L,char Id[80],char Cor1[30], char Cor2[30],double X, double Y, double largura, double altura,int Tamanho);

/*Imprime a lista no terminal, recebe a lista e percorre a mesma até que .prox seja -1, nao retorna nada!*/
void Imprime (ListaEst Li);

/*Pega o tamaho total atual da lista, recebe a lista e retorna o valor inteiro de Lista->size!
Se a quantidade for 0 significa que a lista esta vazia!*/
int TamanhoEst(ListaEst L);

/*Remove da lista o elemento da posicao p, recebe a lista e uma posicao p que deve ser valida! Percorre a lista a procura do elemento na posicao
desejada, quando encontrado ha um rearranjo dos apontadores dos elementos anteirores e proximos, nao retorna nada!*/
void RemoveElemen(ListaEst L,int p);

/*Pega a quantidade total de visitas que os nohs da lista foram acessados, recebe a lista e retorna o valor inteiro de Lista->visitas!
Se a quantidade for 0 significa que nao ha elementos na lista!*/
int QtVisitasEst(ListaEst L);

//ConsultasEstatica
/*Altera a cor dos retangulos que estiverem sobreposto entre si, recebe uma lista de retangulos e o nome do arquivo Txt de saida,
no arquivo Txt de saida escreve o Id dos retangulos que tiverem sobreposicao, e altera a cor na lista dos retangulos que tiverem
sobreposicao, as cores mudadas, eh resultado de um sorteio realizado, nao retorna nada!*/
void tpEst(ListaEst L,char txt[]);

/*Altera a cor dos retangulos que estiverem sobreposto entre si, dentro da area do retangulo informado, recebe uma lista de retangulos 
e o nome do arquivo Txt de saida, no arquivo Txt de saida escreve o Id dos retangulos que tiverem sobreposicao, e altera a cor na lista 
dos retangulos que tiverem sobreposicao, as cores mudadas, eh resultado de um sorteio realizado, nao retorna nada!*/
void tprEst(ListaEst l,char txt[],double x1,double y1,double larg,double alt);

/*Remove todos retangulos que tiverem o ponto X,Y como ponto interno, recebe uma lista, coordenadas X e Y e o nome do arquivo TXT de saida
no arquivo TXT sera escrito o ID dos retangulos removidos, sera removido da lista o retangulo que tiver X e Y como ponto interno,
nao  retorna nada!*/
void DpiEst(ListaEst L,double X, double Y,char txt[]);

/*Remove todos retangulos que tiverem dentro do retangulo informado, recebe uma lista, o Id de um retangulo  e o nome do arquivo TXT de 
saida, no arquivo TXT sera escrito o ID dos retangulos removidos, sera removido da lista os retangulos que estiver dentro do retangulo ID,
nao retorna nada!*/
void drEst(ListaEst L, char Ide[70],char txt[]);

/*Armazena em uma lista dinamica auxiliar as coordenadas de um retangulo, sem preenchimento e com tracejado vermelho e coordenadas para um circulo
com coordenadas x e y, recebe a lista L de retangulos, uma lista dinamica auxiliar, coordenadas x e y, e o nome do TXT de saida, no TXT eh escrito
os id's e as cores originais de preenchimento e de contorno do retangulo para qual o ponto x e y eh interno, nao retorna nada!*/
void bbiEst(ListaEst L,Lista auxi,double x, double y,char txt[]);

/*Armazena em uma lista dinamica auxiliar as coordenadas de um retangulo, sem preenchimento e com tracejado vermelho, recebe a lista L de retangulos,
uma lista dinamica auxiliar, Id do retangulo, e o nome do TXT de saida, no TXT eh escrito os id's e as cores originais de preenchimento e de contorno
do retangulo que estiver dentro do retangulo com Id passado, nao retorna nada!*/
void bbidEst(Lista L,Lista auxilia,char ID[],char txt[]);

/*Reporta os dados dos k elementos posteriores se k>0 ou elementos anteriores se k<0, do retangulo ID, recebe a lista de retangulos, ID do
retangulo, um k e o nome do arquivo TXT de saida, se o ID nao existir sera escrito no TXT, se K for maior que o tamanho da lista, sera
informado no terminal, sera inserido os dados dos retangulos no arquivo TXT, nao retorna nada!*/
void iidEst(ListaEst li,char ide[],int ka, char txt[]);

/*Reporta os dados dos k elementos posteriores se k>0 ou elementos anteriores se k<0, do retangulo ID e remove da lista estes elementos,
recebe a lista de retangulos, ID do retangulo, um k e o nome do arquivo TXT de saida, se o ID nao existir sera escrito no TXT, 
se K for maior que o tamanho da lista, sera informado no terminal, sera inserido os dados dos retangulos no arquivo TXT, nao retorna nada!*/
void diidEst(ListaEst li,char ide[],int ka, char txt[]);

/*Insere no arquivo SVG das consultas todos os retangulos existentes na lista estatica, recebe a lista de retangulos e o nome do arquivo SVG final
a funcao percorre a lista estatica inserindo os retangulos com as coordenadas e cores armazenadas na lista, nao retorna nada!*/
void SvgQryEst(ListaEst Li, char nomeSvG[]);

//Nao sao usados!
/*Insere elementos no Item anterior a posicao informada, recebe a lista estatica, os parametros, uma posicao que deve ser valida, e o tamanho
maximo permitido da lista, os dados serao inseridos no Item anterior a pos, nao retorna nada!*/
void InsereBeforeEst(ListaEst L,double X, double Y, double largura, double altura,int pos, int Tamanho);

/*Insere elementos no Item depois da posicao informada, recebe a lista estatica, os parametros, uma posicao que deve ser valida, e o tamanho
maximo permitido da lista, os dados serao inseridos no Item imediatamente posterior a pos, nao retorna nada!*/
void InsereAfterEst(ListaEst L,double X, double Y, double largura, double altura,int pos, int Tamanho);

/*Pega a posicao anterior a posicao informada, recebe a lista estatica, e uma posicao que deve ser valida, sera percorrido
a lista ate o item[x].prox != pos, retorna posicao do elemento anterior a posicao informada!*/
int GetPreviousEst(ListaEst L, int pos);

/*Pega a posicao a ultima posicao da lista, recebe a lista estatica, sera retornado lista->ultimo, retorna posicao do ultimo elemento 
da lista! Se a posicao for -1 indica que a lista esta vazia*/
int GetLastEst(ListaEst L);

/*Pega a posica do primeiro item da lista, recebe a lista estatica,sera retornado lista->primeiro, retorna posicao do primeiro elemento 
da lista! Se a posicao for -1 indica que a lista esta vazia*/
int GetFirstEst(ListaEst L);

/*Pega a posicao do item posterior a posicao informada, recebe a lista estatica, e uma posicao que deve ser valida, sera retornado o
lista->item[pos].prox, que eh a posicao do elemento imediamente posterior da posicao informada! Retorna posicao do elemento posterior 
a posicao informada!*/
int GetNextEst(ListaEst L, int pos);

#endif