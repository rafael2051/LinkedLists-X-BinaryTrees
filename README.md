Tipo de programa: command-line interface.

Esse programa basicamente carrega um arquivo de texto e armazena cada linha e cada palavra do arquivo em
uma estrutura de dados, dentre duas opções possíveis: lista ou árvore. Cada linha e cada palavra é armazenada
em uma struct que possui informações como: a string em si que corresponde à linha ou palavra, no caso da linha
o índice, no caso da palavra a quantidade de ocorrências dessa palavra no texto, todas as linhas em que essa palavra
aparece no texto, e outras informações necessárias. Depois de construída a estrutura de dados, é possível 
ao usuário buscar por uma palavra específica no texto, sem diferenciação de letras maiúsculas e minúsculas, e, caso
a palavra exista no texto, será mostrada a quantidade de ocorrências dessa palavra no texto e serão imprimidas
todas as linhas em que essa palavra aparece. Também será imprimida a quantidade de tempo para realizar a busca
por essa palavra. Caso a palavra não exista no texto, será imprimida a mensagem "Palavra '<palavra digitada>' não encontrada".

O propósito principal desse programa é comparar a eficiência entre listas e árvores binárias de busca, tanto para
armazenar a informação, quanto para recuperar. Após o arquivo ser carregado, também será impressa a quantidade
de tempo para armazenar as linhas e palavras do texto na estrutura de dados selecionada. Neste projeto, há uma
pasta chamada info que possui um relatório com experimentos realizados em que foram usados arquivos txt cada
vez maiores para comparar as duas estruturas de dados. Neste relatório será possível observar como árvores binárias
de busca são absurdamente mais eficiências que listas para armazenar e recuperar informação em larga escala.
A seguir, existem mais informações sobre os códigos fontes, e instruções de como compilar e executar o programa
no terminal, como carregar um arquivo de texto, e como realizar buscas por palavras específicas.

Após a execução do programa, caso o arquivo tenha sido carregado, o executável entrará em um loaping
que aguarda o usuário digitar alguma coisa. Para encerrar esse loaping, basta digitar "fim" que a execução do programa
terminará.




/*****************************************************************************************************************************/

Este programa possui 5 códigos fontes: main.c, que contém a função main; lista.h, que contém as estruturas
utilizadas para carregar o arquivo em uma estrutura de lista e os protótipos da funções principais que 
armazenam as linhas e palavras do arquivo de texto em listas e também permitem a recuperação dessas
informações; lista.c, que contém as funções declaradas em lista.h além de funções adicionais necessárias 
para realizar o armazenamento e recuperação das linhas e palavras do arquivo de texto; arvore_binaria.h, 
que contém as estruturas utilizadas para carregar o arquivo em uma árvore binária de busca e os protótipos
das funções principais que armazenam as linhas e palavras do arquivo de texto em árvores binárias 
de busca e também permitem permitem a recuperação dessas informações; e arvore_binaria.c, que contém
as funções declaradas em arvore_binaria.h além  de funções adicionais necessárias para realizar
o armazenamento e recuperação das linhas e palavras do arquivo de texto.

/*****************************************************************************************************************************/



Para compilar os códigos fontes deste projeto, abra o terminal do seu computador (seja o 
sistema operacional windows, linux ou mac), vá até o diretório onde se encontram
os arquivos fonte, e digite o seguinte comando:

"gcc main.c lista.c arvore_binaria.c -o test"

Este comando irá compilar os três arquivos fonte, incuindo os headers, e transformar
o código em C em um arquivo objeto, que será usado para criar um executável, neste caso,
chamado de "test". Você pode dar o nome que quiser ao executável, basta substituir
test por qualquer outro nome.

Para executar: depois de compilado, digite o seguinte comando:

"test <arquivo-texto.txt> lista"

Esse comando deve ser usado para carregar o arquivo texto usando listas
como estrutura de de armazenamento.
Caso deseje utilizar a estrutura árvore binária de busca para carregar o arquivo
e realizar as buscas, digite:

"test <arquivo-texto.txt> arvore"

Exemplos:

/*****************************************************************************************************************************/

Para utilizar listas:

test texto.txt lista		

test sample.txt lista			

test 5000.txt lista		

test bible.txt lista		

test In-Search-Of-Lost-Time.txt lista	

/*****************************************************************************************************************************/

Para utilizar árvores: 

test texto.txt arvore		

test sample.txt arvore			

test 5000.txt arvore

test bible.txt arvore		

test In-Search-Of-Lost-Time.txt arvore

/*****************************************************************************************************************************/

Para buscar uma palavra:
busca <palavra>

Exemplos:

busca god

busca the

busca in

busca are

busca he

busca is

busca she

busca him

busca thy

busca thou

/*****************************************************************************************************************************/

Parace encerrar o a execução do programa, basta digitar "fim" na linha de comando.

Na pasta sample foram incluídos 9 arquivos de texto para testar o programa e realizar  o armazenamento
em memória de cada linha e cada palavra do arquivo txt na estrutura de dados selecionada pelo usuário:

texto.txt (13 linhas)

sample.txt (66 linhas)

new.txt (440 linhas)

2021.txt (2021 linhas)

3000.txt (3000 linhas)

5000.txt (5000 linhas)

biblia-em-txt.txt (32369 linhas)

bible.txt (100182 linhas)

In-Search-Of-Lost-Time (109888 linhas)
