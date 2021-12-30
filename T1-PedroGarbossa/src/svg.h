#ifndef __SVG_H
#define __SVG_H

//Cria a tag inicial de um svg para o arquivo com o nome recebido, recebe o nome do SVG, nao retorna nada! Caso nao seja possivel criar o 
//arquivo retorna NULL!
void iniciaSvg(char arq[]);

//Cria a tag final de um svg para o arquivo com o nome recebido, recebe o nome do SVG, nao retorna nada! Caso nao seja possivel abrir o 
//arquivo retorna NULL!
void finalizaSvg(char arq[]);

//Cria uma linha entre dois pontos com a cor selecionada no arquivo svg, recebe coordenadas x,y, uma cor e o nome do SVG, nao retorna nada! 
//Caso nao seja possivel abrir o arquivo retorna NULL!
void criaLinha(double x1, double y1, double x2, double y2, char cor[], char svg[]);

//Cria um retangulo a partir do ponto x y e da altura e largura, no arquivo svg, recebe coordenadas x,y, duas cores e o nome do SVG, 
//nao retorna nada! Caso nao seja possivel abrir o arquivo retorna NULL!
void criaRetangulo(double largura, double altura, double x, double y, char cor1[], char cor2[], char svg[]);

//Cria uma boundingBox a partir do ponto x,y e da altura e largura fornecida, recebe os parametros e cria a bounding box
//com contorno tracejado, da cor informada, nao retorna nada! Caso nao seja possivel abrir o arquivo retorna NULL!
void criaBoundingBox(double x, double y,double largura, double altura, char cor1[], char svg[]);

//Cria um circulo no SVG, recebe coordenadas x e y, raio, cores de preenchimento e de contorno, e o nome do SVG nao retorna nada!
//Caso nao seja possivel abrir o arquivo retorna NULL!
void CriaPontinho(double x,double y, double raio,char Contorno[],char Preenchimento[],char svg[]);

//Cria um texto a partir do ponto x e y, recebe o texto, x,y e o nome do svg, no arquivo svg escreve o texto passado! Caso 
//nao seja possivel abrir o arquivo retorna NULL!
void TextoSvg(float x, float y, char texto[], char svg[]);

/*Insere no arquivo passado um grafico com ate no maximo 1000 no eixo x e y, percorre o RelatorioTemporario.Txt lendo o numero de visitas 
e tamanho da lista, recebe o nome do arquivo txt temporario, nome do svg do grafico e o titulo do grafico, nao retorna nada! Caso nao 
consiga abrir o arquivo txt retornara NULL, caso nao consiga abrir o svg retorna NULL!*/
void GeraGrafico1000(char txt[],char svg[],char titulo[]);

/*Insere no arquivo passado um grafico com ate no maximo 5000 no eixo x e y, percorre o RelatorioTemporario.Txt lendo o numero de visitas e 
tamanho da lista, recebe o nome do arquivo txt temporario, nome do svg do grafico e o titulo do grafico, nao retorna nada! Caso nao consiga 
abrir o arquivo txt retornara NULL, caso nao consiga abrir o svg retorna NULL!*/
void GeraGrafico5000(char txt[],char svg[],char titulo[]);

/*Insere no arquivo passado um grafico com ate no maximo 10000 no eixo x e y, percorre o RelatorioTemporario.Txt lendo o numero de visitas e 
tamanho da lista, recebe o nome do arquivo txt temporario, nome do svg do grafico e o titulo do grafico, nao retorna nada! Caso nao consiga 
abrir o arquivo txt retornara NULL, caso nao consiga abrir o svg retorna NULL!*/
void GeraGrafico10000(char txt[],char svg[],char titulo[]);

/*Insere no arquivo passado um grafico com ate no maximo 100.000 no eixo x e y, percorre o RelatorioTemporario.Txt lendo o numero de visitas e 
tamanho da lista, recebe o nome do arquivo txt temporario, nome do svg do grafico e o titulo do grafico, nao retorna nada! Caso nao consiga 
abrir o arquivo txt retornara NULL, caso nao consiga abrir o svg retorna NULL!*/
void GeraGrafico100k(char txt[],char svg[],char titulo[]);

/*Insere no arquivo passado um grafico com ate no maximo 1.000.000 no eixo x e y, percorre o RelatorioTemporario.Txt lendo o numero de visitas e 
tamanho da lista, recebe o nome do arquivo txt temporario, nome do svg do grafico e o titulo do grafico, nao retorna nada! Caso nao consiga 
abrir o arquivo txt retornara NULL, caso nao consiga abrir o svg retorna NULL!*/
void GeraGrafico1Miao(char txt[],char svg[],char titulo[]);

/*Insere no arquivo passado um grafico com ate no maximo 50.000.000 no eixo x e y, percorre o RelatorioTemporario.Txt lendo o numero de visitas e 
tamanho da lista, recebe o nome do arquivo txt temporario, nome do svg do grafico e o titulo do grafico, nao retorna nada! Caso nao consiga 
abrir o arquivo txt retornara NULL, caso nao consiga abrir o svg retorna NULL!*/
void GeraGrafico10Miao(char txt[],char svg[],char titulo[]);

/*Inicia o comando que inverte verticalmente os desenhos do svg, recebe o nome do svg e a coordenada y, nao retorna nada! Caso nao consiga 
abrir o arquivo svg retornara NULL, caso nao consiga abrir o svg retorna NULL!*/
void IniciaInversao(char svg[],double coordenadaY);

/*Insere a tag final do comando que inverte verticalmente os desenhos do svg, recebe o nome do svg, nao retorna nada! Caso nao consiga 
abrir o arquivo svg retornara NULL, caso nao consiga abrir o svg retorna NULL!*/
void FinalizaInversao(char svg[]);

/*Insere uma linha traceja nas coordenadas desejada, recebe o nome do svg e as coordenada x1,y1,x2,y2, cor do traço, nao retorna nada! Caso
nao consiga  abrir o arquivo txt retornara NULL, caso nao consiga abrir o svg retorna NULL!*/
void LinhaTracejada(double x1, double y1, double x2, double y2, char cor[], char svg[]);

#endif