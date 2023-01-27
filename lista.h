#define FALSE 0
#define TRUE 1
#define TAMANHO_MAXIMO 1000

typedef int Boolean;
typedef char * Elemento;

//Lista sequencial

typedef struct {

	Elemento a[TAMANHO_MAXIMO];
	int livre;

} ListaSequencial;


ListaSequencial * cria_lista_seq(int n);
void destroi_lista_seq(ListaSequencial * lista);
int tamanho_seq(ListaSequencial * lista);
void imprime_seq(char ** a, int tamanho);
int busca_seq(ListaSequencial * lista, Elemento e);
Boolean insere_seq(ListaSequencial * lista, Elemento e, int indice);
Boolean remove_elemento_seq(ListaSequencial * lista, Elemento e);

//Lista ligada

typedef struct no_linhas{
	int linha;
	struct no_linhas * proximo;
}no_Linhas;

typedef struct {
	no_Linhas * primeiro;
}Lista_Ligada_Linhas;

typedef struct _no_ {

	Elemento valor;
	Lista_Ligada_Linhas * lista_nos_linhas;
	int quantidade;
	struct _no_ * proximo;

} No;

typedef struct {
	
	No * primeiro;

} ListaLigada;

typedef struct no_l {
	
	Elemento valor;
	int linha;
	struct no_l * proximo;
	
} no_linha;

typedef struct {
	
	no_linha * primeiro;
	
} ListaLigadaLinhas;

ListaLigada * cria_lista_ligada();
ListaLigadaLinhas * cria_lista_ligada_linhas();
void destroi_lista_ligada(ListaLigada * lista);
int tamanho_ligada(ListaLigada * lista);
void imprime_ligada(ListaLigada * lista);
No * busca_ligada(ListaLigada * lista, Elemento e);
Boolean push(ListaLigada * lista, Elemento e, int indice);
Boolean push_linha(ListaLigadaLinhas * lista, Elemento e, int indice);
void imprime_linha(ListaLigadaLinhas * lista, int indice);