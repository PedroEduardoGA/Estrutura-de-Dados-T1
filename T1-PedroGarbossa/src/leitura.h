#ifndef LEITURA_H_
#define LEITURA_H_
#include "Dinamica.h"
#include "ListaEstatica.h"

/* Funcao: LeituraGeo recebe 8 parametros: 
    "Lista" void pointer que uso pra apontar pra uma lista do tipo Dinamica!
    "ListaEst" void pointer que uso pra apontar pra uma lista do tipo Estatica!
    "bed" eh o diretorio caso informado o -e, entao sera passado pra bed o diretorio de entrada, caso nao seja informado o -e
    bed valera NULL!
    "nomeArq" eh o nome do arquivo geo informado logo apos o -f, caso nome do arquivo seja invalido retorna NULL!
    "dirSaida" eh o diretorio de saida informado apos o -o, diretorio sera usado pra produzir o svg inicial nesse diretorio!
    "tipoLista" eh o tipo de lista que sera usada, por padrao sera usada o tipo de lista dinamica, caso seja informado -lse a
    lista usada passa a ser a do tipo estatica, caso informado -ldd, sera usada a dinamica! Se tipo vale 0 -> lista dinamica, se 1 -> estatica
    "*nx" recebe o endereco de uma variavel que servira pra criar a estatica do tamanho de nx
    "first" serve pra saber se eh a primeira vez que o geo ta sendo acessado, caso seja 0 quer dizer que a lista escolhida foi estatica
    nesse caso abrira o geo, pegara o tamanho e atribuirá esse tamanho no endereco recebido em *nx!
    A funcao abre o arquivo .geo, le todos comandos e armazena na lista escolhida os parametros dos retangulos, como altura,
    id, largura, coordenada X e Y,e cores de preenchimento e contorno, insere no svg inicial os retangulos, svg inicial que sera criado 
    no diretorio de saida com o nome do arquivo geo informado Ex: nomegeo.svg! Caso nao seja possivel abrir o arquivo retorna NULL!
    Funcao nao retorna nada!*/
void LeituraGeo(Lista Dinamica,ListaEst Estatica,char* bed,char* nomeArq,char* dirSaida,int tipoLista,int *nx,int first);

/* Funcao: LeituraQry recebe 8 parametros: 
    "Lista" void pointer que uso pra apontar pra uma lista do tipo Dinamica!
    "din" -> lista dinamica "aux" -> lista auxiliar pra inserir bounding box caso haja consulta bbi
    "ListaEst" void pointer que uso pra apontar pra uma lista do tipo Estatica!
    "DiretorioEnt" eh o diretorio caso informado o -e, entao sera passado pra variavel o diretorio de entrada, caso nao seja informado o -e
    DiretorioEnt valera NULL!
    "nomeQry" eh o nome do arquivo qry informado logo apos o -q, caso nome do arquivo seja invalido retorna NULL!
    "diretSaida" eh o diretorio de saida informado apos o -o, diretorio sera usado pra produzir os .txt das consultas nesse diretorio!
    "tipoLista" eh o tipo de lista que sera usada, por padrao sera usada o tipo de lista dinamica, caso seja informado -lse a
    lista usada passa a ser a do tipo estatica, caso informado -ldd, sera usada a dinamica! Se tipo vale 0 -> lista dinamica, se 1 -> estatica
    "TxtSaida" recebera o nome do txt formatado como: nomegeo-nomeqry.txt
    A funcao abre o arquivo .qry, le todos comandos linha por linha e realiza a consulta, dependendo da consulta o efeito muda, as que tem b
    na primeira letra, vao armazenar em uma lista auxiliar parametros pra criacao de uma bounding box, as que tiverem d como a primeira letra
    vao remover retangulos desejaseis na lista que estiver sendo usada, para todas as outras o efeito eh um update na lista selecionada,
    cada consulta produz algum resultado no arquivo txt, no diretorio de saida com o nome Ex: nomegeo-nomeqry.txt! Caso nao seja possivel abrir 
    o arquivo retorna NULL! A Funcao nao retorna nada!*/
void LeituraQry(Lista din,Lista aux,ListaEst Estati,char* DiretorioEnt,char* nomeQry,char* diretSaida,int tipoLista,char* TxtSaida);

#endif