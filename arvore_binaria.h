#define FALSE 0
#define TRUE 1

#define INDEFINIDO -1
#define ESQUERDO 0
#define DIREITO 1

typedef char * Elemento;
typedef int Boolean;

char * substitui_maiusculas_arvore(char * ponteiro);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////// Funções e estruturas usadas para armazenar em memória as linhas do arquivo txt. /////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _no_arvore_linhas {

	Elemento valor;
	int valChar;
	int linha;
	struct _no_arvore_linhas * esq;
	struct _no_arvore_linhas * dir;
	struct _no_arvore_linhas * colisao;

} No_arvore_linhas;

typedef struct _arvore_linhas{

	No_arvore_linhas * raiz;

} Arvore_linhas;

Arvore_linhas * cria_arvore_linhas();
void imprime_linhas(Arvore_linhas * arvore);

No_arvore_linhas * busca_bin_linhas(Arvore_linhas * arvore, Elemento e);
Boolean insere_ord_linhas(Arvore_linhas * arvore, Elemento e, int p_valChar, int p_linha, int * p_valCharLinhaRef);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////// Funções e estruturas usadas para armazenar em memória as palavras do arquivo txt. /////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct _linha{
	int valor_linha;
	int valCharLinha;
	struct _linha * prox;
} Linha;

typedef struct {
	Linha * primeiro;
} Lista_linhas_aux;


typedef struct _no_colisao {

	Elemento valor;
	Lista_linhas_aux * linhas;
	int quantidade;
	struct _no_colisao * proximo;

} No_palavra_colisao;

typedef struct {
	
	No_palavra_colisao * primeiro;

} ListaLigada_palavra_colisao;

ListaLigada_palavra_colisao * cria_lista_colisao();

Lista_linhas_aux * cria_lista_linhas(int p_linha, int p_valCharLinhaRef);

void insere_lista_colisao(ListaLigada_palavra_colisao * lista_colisao, Elemento e, int p_linha, int p_valCharLinhaRef);

typedef struct _no_arvore_palavras {
	
	Elemento valor;
	float valChar;
	struct _no_arvore_palavras * colisao;
	Lista_linhas_aux * linhas;
	int quantidade;
	struct _no_arvore_palavras * esq;
	struct _no_arvore_palavras * dir;
	
} No_arvore_palavras;

typedef struct _arvore_palavras {
	
	No_arvore_palavras * raiz;
} Arvore_palavras;

Arvore_palavras * cria_arvore_palavras();
void imprime_palavras(Arvore_palavras * arvore);

No_arvore_palavras * busca_bin_palavras(Arvore_linhas * arvore, Elemento e);
Boolean insere_ord_palavras(Arvore_palavras * arvore, Elemento e, float p_valChar, int p_linhas, int p_valCharLinha);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////// Funções usadas tanto para armazenar as linhas quanto as palavras do arquivo txt. ////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int somaValChar(Elemento);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// Funções usada para buscar uma palavra na arvore que armazena as palavras/////////////////////
//////////////////// e as respectivas linhas que contém essas palavras. //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
No_arvore_palavras * busca_bin_palavra_arvore(Arvore_palavras * arvore, Elemento e);
Boolean imprime_linha_bin(Arvore_linhas * arvore, int p_valChar, int p_linha);


