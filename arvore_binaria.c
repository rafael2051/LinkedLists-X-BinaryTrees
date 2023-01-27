#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "arvore_binaria.h"

//////////////////////////////////////////////////////////////////////////////
// Funções auxiliares tanto para armazenar e buscar as palavras e as linhas //
//////////////////////////////////////////////////////////////////////////////

char * substitui_maiusculas_arvore(char * ponteiro){
	
	char * p = (char *)malloc(sizeof(char)* 50);
	strncpy(p, ponteiro, 50);
	for(int i = 0;p[i] != '\0';i++){
		if(p[i] >= 65 && p[i] <= 90)
			p[i] += 32;
	}
	return p;
}

int somaValChar(char * ponteiro){
	int soma = 0;
	for(int  i = 0; ponteiro[i] != '\0'; i++)
		soma += ponteiro[i];
	return soma;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Implementações específicas para a árvore que vai armazenar as linhas do arquivo txt //
/////////////////////////////////////////////////////////////////////////////////////////

Arvore_linhas * cria_arvore_linhas(){
	Arvore_linhas * arvore = (Arvore_linhas *) malloc (sizeof(Arvore_linhas));
	arvore->raiz = NULL;	
	return arvore;
}

void imprime_rec_linhas(No_arvore_linhas * no){
	// percurso in-ordem para a impressão dos elementos

	if(no){
		imprime_rec_linhas(no->esq);
		printf("%s\tLinha: %d, ValChar: %d\n", no->valor, no->linha, no->valChar);
		imprime_rec_linhas(no->dir);
	}
}

void imprime_linhas(Arvore_linhas * arvore){

	printf("Linhas na arvore: \n");
	imprime_rec_linhas(arvore->raiz);
	printf("\n");
}

No_arvore_linhas * busca_bin_rec_linhas(No_arvore_linhas * no, Elemento e){

	if(no){

		if(no->valor == e) return no;
		if(e < no->valor) return busca_bin_rec_linhas(no->esq, e);
		return busca_bin_rec_linhas(no->dir, e);
	}

	return NULL;
}

No_arvore_linhas * busca_bin_linhas(Arvore_linhas * arvore, Elemento e){
	
	return busca_bin_rec_linhas(arvore->raiz, e);	
}

Boolean insere_ord_rec_linhas(No_arvore_linhas * raiz, No_arvore_linhas * novo, int * p_valCharLinhaRef){

	if(novo->valChar != raiz->valChar){

		if(novo->valChar < raiz->valChar){

			if(raiz->esq) return insere_ord_rec_linhas(raiz->esq, novo, p_valCharLinhaRef);
			else raiz->esq = novo;
		}
		else{
			if(raiz->dir) return insere_ord_rec_linhas(raiz->dir, novo, p_valCharLinhaRef);
			else raiz->dir = novo;
		}
	
		return TRUE;
	}
	else{
		No_arvore_linhas * p = raiz->colisao;
		while(p){
			p = p->colisao;
		}
		p = novo;
	}
	return FALSE;
}

Boolean insere_ord_linhas(Arvore_linhas * arvore, Elemento e, int p_valChar, int p_linha, int * p_valCharLinhaRef){

	No_arvore_linhas * novo = (No_arvore_linhas *) malloc(sizeof(No_arvore_linhas));
	
	novo->valor = e;
	novo->valChar = p_valChar;
	novo->linha = p_linha;
	*p_valCharLinhaRef = p_valChar;
	
	novo->esq = novo->dir = novo->colisao = NULL;

	if(arvore->raiz) return insere_ord_rec_linhas(arvore->raiz, novo, p_valCharLinhaRef);
		
	arvore->raiz = novo;
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////
// Implementações específicas para a árvore que vai armazenar as palavras do arquivo txt //
///////////////////////////////////////////////////////////////////////////////////////////
Arvore_palavras * cria_arvore_palavras(){
	
	Arvore_palavras * arvore = (Arvore_palavras *)malloc(sizeof(Arvore_palavras));
	arvore->raiz = NULL;
	return arvore;
}

void imprime_rec_palavras(No_arvore_palavras * no){
	
	// percurso in-ordem para a impressão dos elementos	

	if(no){
		Linha * linha_aux = no->linhas->primeiro;
		imprime_rec_palavras(no->esq);
		printf("Palavra: %s, valChar: %f, linhas: ", no->valor, no->valChar);
		
		while(linha_aux){
			printf("%d, ", linha_aux->valor_linha);
			printf("valCharLinha: %d", linha_aux->valCharLinha);
			linha_aux = linha_aux->prox;
		}
		
		printf("quantidade: %d\n", no->quantidade);
		imprime_rec_palavras(no->dir);
	}
}

void imprime_palavras(Arvore_palavras * arvore){
	printf("Palavras na arvore: \n");
	imprime_rec_palavras(arvore->raiz);
	printf("\n");
}

///////////////////////////////////////////////
// Funções auxiliares para o caso de colisão //
///////////////////////////////////////////////


Boolean insere_ord_rec_palavras(No_arvore_palavras * raiz, No_arvore_palavras * novo){

	if(novo->valChar != raiz->valChar){

		if(novo->valChar < raiz->valChar){

			if(raiz->esq) return insere_ord_rec_palavras(raiz->esq, novo);
			else raiz->esq = novo;
		}
		else{
			if(raiz->dir) return insere_ord_rec_palavras(raiz->dir, novo);
			else raiz->dir = novo;
		}
	
		return TRUE;
	}
	return FALSE;
}

No_arvore_palavras * busca_colisao(No_arvore_palavras * no, Elemento e){
	if(no){
		char * aux1 = substitui_maiusculas_arvore(no->valor);
		char * aux2 = substitui_maiusculas_arvore(e);
		if(strcmp(aux1, aux2) == 0){
			free(aux1);
			free(aux2);
			return no;
			}
		else{
			free(aux1);
			free(aux2);
			return busca_colisao(no->esq, e);
		}
	}
	return NULL;
}

No_arvore_palavras * busca_bin_rec_palavras_aux(No_arvore_palavras * no, float p_valChar){
	
	if(no){
		if(no->valChar == p_valChar) return no;
		
		if(p_valChar < no->valChar) return busca_bin_rec_palavras_aux(no->esq, p_valChar);
		return busca_bin_rec_palavras_aux(no->dir, p_valChar);
	}

	return NULL;
}

No_arvore_palavras * busca_bin_palavras_aux(Arvore_palavras * arvore, float p_valChar){
	return busca_bin_rec_palavras_aux(arvore->raiz, p_valChar);	
}

Boolean insere_ord_palavras(Arvore_palavras * arvore, Elemento e, float p_valChar, int p_linha, int p_valCharLinhaRef){
	
	No_arvore_palavras * no;
	Linha * ant;
	Linha * proximo;
	
	if( (no = busca_bin_palavras_aux(arvore, p_valChar)) ){
		char * aux1 = substitui_maiusculas_arvore(no->valor);
		char * aux2 = substitui_maiusculas_arvore(e);
		
		if(strcmp(aux1, aux2) == 0){
			free(aux1);
			free(aux2);
			no->quantidade++;
			Linha * linha_aux;
			
			for(linha_aux = no->linhas->primeiro; linha_aux; linha_aux = linha_aux->prox){
				if(linha_aux->valor_linha == p_linha)
					return TRUE;
			}
			
			Linha * nova_linha = (Linha *)malloc(sizeof(Linha));
			nova_linha->valor_linha = p_linha;
			nova_linha->valCharLinha = p_valCharLinhaRef;
			proximo = no->linhas->primeiro;
			while(proximo){
				ant = proximo;
				proximo = proximo->prox;
			}
			nova_linha->prox = NULL;
			ant->prox = nova_linha;
			return TRUE;
		}		
		else{
			free(aux1);
			free(aux2);
			No_arvore_palavras * no_busca_colisao;
			
			if( (no_busca_colisao = busca_colisao(no->colisao, e)) ){
				no_busca_colisao->quantidade++;
				Linha * linha_aux_colisao;
			
				for(linha_aux_colisao = no_busca_colisao->linhas->primeiro; linha_aux_colisao; linha_aux_colisao = linha_aux_colisao->prox){
					if(linha_aux_colisao->valor_linha == p_linha)
						return TRUE;
				}
				
				Linha * nova_linha_colisao = (Linha *)malloc(sizeof(Linha));
				nova_linha_colisao->valor_linha = p_linha;
				nova_linha_colisao->valCharLinha = p_valCharLinhaRef;
				proximo = no_busca_colisao->linhas->primeiro;
				while(proximo){
					ant = proximo;
					proximo = proximo->prox;
				}
				nova_linha_colisao->prox = NULL;
				ant->prox = nova_linha_colisao;
				return TRUE;
			}
			else{
				No_arvore_palavras * novo_no_colisao = (No_arvore_palavras *) malloc(sizeof(No_arvore_palavras));
				Lista_linhas_aux * novo_lista_linhas = (Lista_linhas_aux *)malloc(sizeof(Lista_linhas_aux));
				Linha * nova_linha = (Linha *)malloc(sizeof(Linha));
				nova_linha->valor_linha = p_linha;
				nova_linha->valCharLinha = p_valCharLinhaRef;
				nova_linha->prox = NULL;
				novo_lista_linhas->primeiro = nova_linha;
		
				novo_no_colisao->valor = e;
				novo_no_colisao->valChar = p_valChar;
//				novo->lista_colisao = cria_lista_colisao();
				novo_no_colisao->colisao = NULL;
				novo_no_colisao->linhas = novo_lista_linhas;
				novo_no_colisao->quantidade = 1;
				novo_no_colisao->esq = no->colisao;
				no->colisao = novo_no_colisao;
			}
		}
			
	}
	else{
		
		No_arvore_palavras * novo = (No_arvore_palavras *) malloc(sizeof(No_arvore_palavras));
		Lista_linhas_aux * novo_lista_linhas = (Lista_linhas_aux *)malloc(sizeof(Lista_linhas_aux));
		Linha * nova_linha = (Linha *)malloc(sizeof(Linha));
		nova_linha->valor_linha = p_linha;
		nova_linha->valCharLinha = p_valCharLinhaRef;
		nova_linha->prox = NULL;
		novo_lista_linhas->primeiro = nova_linha;
		
		novo->valor = e;
		novo->valChar = p_valChar;
//		novo->lista_colisao = cria_lista_colisao();
		novo->colisao = NULL;
		novo->linhas = novo_lista_linhas;
		novo->quantidade = 1;
		novo->esq = NULL;
		novo->dir = NULL;
	
		if(arvore->raiz) return insere_ord_rec_palavras(arvore->raiz, novo);
			
		arvore->raiz = novo;
		return TRUE;
	}
}
////////////////////////////////////////////////////////////////////////////////////
// Implementações específicas para realizar a busca de uma palavra no arquivo txt //
////////////////////////////////////////////////////////////////////////////////////


No_arvore_palavras * busca_bin_rec_palavra_arvore(No_arvore_palavras * no, float p_valChar, Elemento e){
	
	if(no){
		if(no->valChar == p_valChar){
			char * aux1 = substitui_maiusculas_arvore(no->valor);
			char * aux2 = substitui_maiusculas_arvore(e);
			if(strcmp(aux1, aux2) == 0){
				free(aux1);
				free(aux2);
				return no;
			}
			else{
				return busca_colisao(no->colisao, e);
			}
		}
		
		if(p_valChar < no->valChar) return busca_bin_rec_palavra_arvore(no->esq, p_valChar, e);
		return busca_bin_rec_palavra_arvore(no->dir, p_valChar, e);
	}

	return NULL;
}

No_arvore_palavras * busca_bin_palavra_arvore(Arvore_palavras * arvore, Elemento e){
	char * aux = substitui_maiusculas_arvore(e);
	float valChar = (float)somaValChar(aux);
	free(aux);
	return busca_bin_rec_palavra_arvore(arvore->raiz, valChar, e);
}

Boolean imprime_linha_bin_rec(No_arvore_linhas * raiz, int p_valChar, int p_linha){
	if(raiz){
		if(raiz->valChar == p_valChar){
			if(raiz->linha == p_linha)
				printf("%04d: %s\n", raiz->linha, raiz->valor);
			else
				return imprime_linha_bin_rec(raiz->colisao, p_valChar, p_linha);
			return TRUE;
		}
		else{
			if(p_valChar < raiz->valChar)
				return imprime_linha_bin_rec(raiz->esq, p_valChar, p_linha);
			else
				return imprime_linha_bin_rec(raiz->dir, p_valChar, p_linha);
		}
	}
	return FALSE;
}

Boolean imprime_linha_bin(Arvore_linhas * arvore, int p_valChar, int p_linha){
	No_arvore_linhas * p = arvore->raiz;
	
	if(p)
		return imprime_linha_bin_rec(p, p_valChar, p_linha);
	return FALSE;
}
