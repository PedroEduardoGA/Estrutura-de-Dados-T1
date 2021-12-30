# Projeto T1 - Estrutura de Dados I
*Projeto desenvolvido na disciplina de Estrutura de Dados I, projeto desenvolvido usando o sistema operacional Windows 7, para o funcionamento todos os arquivos.c e arquivos.h são compilados executando o comando make no terminal, então o makefile será executado realizando a compilação de todos os códigos e gerando 2 executáveis para o projeto: **progrdin**
e **progrest**, para utilizar o projeto é necessário informar parâmetros de entrada via argumentos pela linha de comando no terminal, cmd ou PowerShell, exemplo:*

### ./progrdin -e DiretórioEntrada -f nome_arquivo.geo -q SubDiretório/nome_arquivo.qry -o DiretórioSaida

*Em resumo o projeto recebe um arquivo .geo que contém coordenadas para geração de retângulos e um arquivo .qry que contém consultas para serem realizadas com estes dados informados no arquivo .geo, o projeto utiliza as seguintes estruturas de dados: **Lista Dinâmica** e **Lista Estática**, o programa recebe como argumento da linha de comando o tipo de lista que será usado, caso o usuário não informe nenhum desses argumentos, será utilizado por padrão a **Lista dinâmica**, o projeto gera no diretório de saída arquivos .svg e .txt para mostrar os resultados das consultas realizadas ao longo da execução.*
---
*No arquivo.geo temos como argumentos:*
- **nx** (Usado para informar o tamanho a ser alocado para a lista estática)
- **cc** (Informa a cor de borda do(s) retângulo(s))
- **cp** (Informa a cor de preenchimento do(s) retângulo(s)) e por fim 
- **r** (Informa as coordenadas e as dimensões de um retângulo)  
*Após a leitura do .geo os retângulos informados são inseridos na lista (Dinâmica/Estática) e é gerado um arquivo .svg inicial que contém os retângulos desenhados.*

*No arquivo.qry temos 8 consultas:*
- **tp** (Indica para o programa trocar a cor de todos retângulos que estiverem em sobreposição)
- **tpr** (Informa coordenadas x e y e dimensões de largura e altura de uma região e indica para o programa trocar de todos retângulos que estiverem em sobreposição dentro da região informada)
- **dpi** (Informa uma coordenada x,y e o programa removerá todos os retângulos que tiver essa coordenada como ponto interno)
- **dr** (Informa o id de um retângulo e o programa removerá todos os retângulos que estiverem inteiramente contidos neste retângulo que foi informado)
- **bbi** (Informa uma região(Coordenadas x,y e dimensões de largura e altura) e o programa trocará entre as cores de borda e preenchimento de todos retângulos que estiverem dentro da região informada e desenhara uma bounding box para representar esta região)
- **bbid** (Informa um id de um retângulo e o programa vai realizar a mesma ação da consulta *bbi* porém a região será o retângulo informado)
- **iid** (Passa o id de um retângulo e um K que será usado para reportar os dados dos retângulos anteriores ao retângulo id se k<0 ou reportar os dados dos retângulos posteriores caso o k>0)
- **diid** (Passa o id de um retângulo e um K que será usado para remover os retângulos anteriores ao retângulo id se k<0 ou remover os retângulos posteriores caso o k>0)

### Resumo dos Parâmetros do programa:
|  Argumento  | Opcional  |    Descrição   |
| :---         |     :---:      |          ---: |
| -e diretórioEntrada   | Sim     | Informa o caminho para o diretório de entrada(Caso exista) que contém os arquivos de entrada do programa    |
| -f nome_arquivo.geo    | Não      | Informa o nome do arquivo.geo que contém os dados iniciais para execução do programa      |
| -q Subdir/nome_arquivo.qry   | Sim    | Informa o subdiretório(Caso esteja em um) e o nome do arquivo.qry que contém os parâmetros de consulta para ser utilizado com um arquivo.geo informado posteriormente    |
| -o diretórioSaída   | Não     | Informa o caminho para o diretório de saída que será usado para armazenas os arquivos gerados ao longo da execução do programa    |
| -ldd    | Sim      | Indica para o programa que será usado a estrutura de dados da lista dinâmica na execução do programa      |
| -lse    | Sim      | Indica para o programa que será usado a estrutura de dados da lista estática na execução do programa      |
| -ib    | Sim     | Indica para o programa que deve ser iniciado a coleta de dados, como quantidade de acessos as listas e cria um arquivo "RelatorioTemp.txt" que será usado para contabilizar estes dados     |
| -cb    | Sim     | Indica para o programa que deve ser continuada a coleta de dados, atenção argumento deve ser utilizado caso tenha sido usado previamente em outra execução o -ib, os dados são contabilizados em um arquivo "RelatorioTemp.txt" temporário criado no diretório corrente     |
| -fb nome_arquivo.svg titulo_grafico   | Sim     | Indica para o programa que deve ser finalizado a coleta de dados, ao final desta execução será gerado um arquivo.svg com o nome do arquivo informado no argumento contendo um gráfico com os dados coletados ao longo das execuções em que foi utilizado o comando -cb, o gráfico terá como título o titulo também informado no argumento e por fim exclui o arquivo temporário que havia sido criado     | 


