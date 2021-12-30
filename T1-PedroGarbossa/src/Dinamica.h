#ifndef _DINAMICA_H
#define _DINAMICA_H
//Cabecalho da lista dinamica, ao referir-se a lista, quero dizer lista duplamente encadeada dinamica!

typedef void* No; //void pointer
typedef void* Lista; //void pointer

//Cria uma lista vazia, retorna uma lista vazia, nao recebe nada como parametro!
Lista Create();

//Insere os parametros dos retangulos, necessita de uma lista para insercao dos parametros, retorna a lista com as informacoes!
void insert(Lista l, char IdRect[70], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura);

//Imprimi todos elementos da lista, precisa de uma lista com pelo menos 1 elemento, nao retorna nada!
void print(Lista l);

//Pega o tamanho atual da lista, precisa de uma lista como parametro, retorna o tamanho da lista!
int Tamanho(Lista l);

//Desaloca a memoria da lista, recebe uma lista, nao retorna nada!
void liberalist(Lista l);

//Remove o elemento com id informado, precisa de uma lista e um id, nao retorna nada!
void RemoveElemento(Lista l, char id[]);

//Insere os parametros, apos tal posicao, necessita de uma lista e as informacoes que serao inseridas, e uma posicao para ser 
//inserido apos ela, nao retorna nada!
void InsereAfter(Lista L,char IdRect[70], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura, int i);

//Insere os parametros, anteriormente tal posicao, necessita de uma lista e as informacoes que serao inseridas, e uma posicao para 
//ser inserido anterior a ela, nao retorna nada!
void InsereBefore(Lista L,char IdRect[70], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura, int i);

//Pega o numero de visitas dos nohs da lista, recebe uma lista e retorna a quantidade de visitas que a mesma teve!
int Visitas(Lista l);

//Pega o ultimo noh da lista, recebe uma lista, retorna o ultimo noh da lista, caso a lista esteja vazia, retorna NULL!
No GetLast(Lista L);

//Pega o primeiro noh da lista, recebe uma lista, retorna o primeiro noh da lista caso a lista esteja vazia, retorna NULL!
No GetFirst(Lista L);

//Pega o noh posterior a posicao informada da lista, recebe uma lista, retorna o noh posterior da posicao, caso a posicao seja maior
//que o tamanho da lista retorna NULL, caso a lista esteja vazia, retorna NULL!
No GetNext(Lista L,int pos);

//Pega o noh anterior a posicao informada da lista, recebe uma lista, retorna o noh anterior da posicao, caso a posicao seja maior
//que o tamanho da lista retorna NULL, caso posicao seja 0 retorna NULL, pois o eh o elemento anterior do primeiro noh, caso a lista 
//esteja vazia, retorna NULL!
No GetPrevious(Lista L, int pos);

//Pega o noh do elemento com Id igual ao informado, recebe uma lista e um Id, retorna o noh com Id informado, caso Id nao exista na lista
//retorna NULL, caso a lista esteja vazia, retorna NULL!
No GetElemento(Lista L,char IdRect[70]);

//==========FuncoesDasConsultas que Envolvem Lista Dinamica==============///
/*Altera a cor dos retangulos que estiverem sobreposto entre si, recebe uma lista de retangulos e o nome do arquivo Txt de saida,
no arquivo Txt de saida escreve o Id dos retangulos que tiverem sobreposicao, e altera a cor na lista dos retangulos que tiverem
sobreposicao, as cores mudadas, eh resultado de um sorteio realizado, nao retorna nada!*/
void tp(Lista L,char txt[]);

/*Altera a cor dos retangulos que estiverem sobreposto entre si, dentro da area do retangulo informado, recebe uma lista de retangulos 
e o nome do arquivo Txt de saida, no arquivo Txt de saida escreve o Id dos retangulos que tiverem sobreposicao, e altera a cor na lista 
dos retangulos que tiverem sobreposicao, as cores mudadas, eh resultado de um sorteio realizado, nao retorna nada!*/
void tpr(Lista l,char txt[],double x1,double y1,double larg,double alt);

/*Remove todos retangulos que tiverem o ponto X,Y como ponto interno, recebe uma lista, coordenadas X e Y e o nome do arquivo TXT de saida
no arquivo TXT sera escrito o ID dos retangulos removidos, sera removido da lista o retangulo que tiver X e Y como ponto interno,
nao  retorna nada!*/
void Dpi(Lista L,double X, double Y,char txt[]);

/*Remove todos retangulos que tiverem dentro do retangulo informado, recebe uma lista, o Id de um retangulo  e o nome do arquivo TXT de 
saida, no arquivo TXT sera escrito o ID dos retangulos removidos, sera removido da lista os retangulos que estiver dentro do retangulo ID,
nao retorna nada!*/
void dr(Lista L, char Ide[70],char txt[]);

/*Armazena em uma lista auxiliar as coordenadas de um retangulo, sem preenchimento e com tracejado vermelho e coordenadas para um circulo
com coordenadas x e y, recebe a lista L de retangulos, uma lista auxiliar, coordenadas x e y, e o nome do TXT de saida, no TXT eh escrito
os id's e as cores originais de preenchimento e de contorno do retangulo para qual o ponto x e y eh interno, nao retorna nada!*/
void bbi(Lista L,Lista auxi,double x, double y,char txt[]);

/*Armazena em uma lista auxiliar as coordenadas de um retangulo, sem preenchimento e com tracejado vermelho, recebe a lista L de retangulos,
uma lista auxiliar, Id do retangulo, e o nome do TXT de saida, no TXT eh escrito os id's e as cores originais de preenchimento e de contorno
do retangulo que estiver dentro do retangulo com Id passado, nao retorna nada!*/
void bbid(Lista L,Lista auxilia,char ID[],char txt[]);

/*Reporta os dados dos k elementos posteriores se k>0 ou elementos anteriores se k<0, do retangulo ID, recebe a lista de retangulos, ID do
retangulo, um k e o nome do arquivo TXT de saida, se o ID nao existir sera escrito no TXT, se K for maior que o tamanho da lista, sera
informado no terminal, sera inserido os dados dos retangulos no arquivo TXT, nao retorna nada!*/
void iid(Lista l,char ide[], int ka, char txt[]);

/*Reporta os dados dos k elementos posteriores se k>0 ou elementos anteriores se k<0, do retangulo ID e remove da lista estes elementos,
recebe a lista de retangulos, ID do retangulo, um k e o nome do arquivo TXT de saida, se o ID nao existir sera escrito no TXT, 
se K for maior que o tamanho da lista, sera informado no terminal, sera inserido os dados dos retangulos no arquivo TXT, nao retorna nada!*/
void diid(Lista l,char ide[],int ka, char txt[]);

/*Insere no arquivo SVG das consultas todos os retangulos existentes na lista, recebe a lista de retangulos e o nome do arquivo SVG final
a funcao percorre a lista inserindo os retangulos com as coordenadas e cores armazenadas na lista, nao retorna nada!*/
void SvgQry(Lista L, char nomeSvG[]);

/*Insere no arquivo SVG das consultas os boundingbox e os pontos, recebe a lista de retangulos e o nome do arquivo SVG final
a funcao percorre a lista inserindo os retangulos com as coordenadas e os insere os circulos caso tenha havido consulta bbi,
nao retorna nada!*/
void SvgBounding(Lista auxilia,char svg[]);

/*Insere em uma lista auxiliar as coordenadas para criacao de uma boundingBox, recebe a lista auxiliar, os parametros da bounding box,
tambem armazena um circulo quando a altura informada for 0, nao retorna nada!*/
void BoundingBox(Lista l, char IdRect[70], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura);

#endif
