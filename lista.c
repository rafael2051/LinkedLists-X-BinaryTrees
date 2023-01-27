#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

//Lista sequencial

ListaSequencial * cria_lista_seq(int capacidade){

	// parametro capacidade ignorado pois o vetor a é alocado estaticamente como campo da struct 
	
	ListaSequencial * lista =  (ListaSequencial *) malloc (sizeof(ListaSequencial));
	lista->livre = 0;

	return lista;
}

void destroi_lista_seq(ListaSequencial * lista){

	free(lista);
}

int tamanho_seq(ListaSequencial * lista){

	return lista->livre;
}

void imprime_seq(char ** a, int tamanho){

	int i;

	printf("Lista: \n");

	for(i = 0; i < tamanho; i++){

		printf("Linha: %d ", i + 1);

		printf(" %s", a[i]);
		
		printf("\n");
	}

	printf("\n");
}

int busca_seq(ListaSequencial * lista, Elemento e){

	int i;

	for(i = 0; i < lista->livre; i++){

		if(lista->a[i] == e) return i;
	}

	return -1;
}

Boolean insere_seq(ListaSequencial * lista, Elemento e, int indice){

	int i;

	if(lista->livre < TAMANHO_MAXIMO && indice >= 0 && indice <= lista->livre){
		for(i = lista->livre; i > indice; i--){

			lista->a[i] = lista->a[i - 1];
		}

		lista->a[indice] = e;
		lista->livre++;

		return TRUE;
	}

	return FALSE;
}

Boolean remove_elemento_seq(ListaSequencial * lista, Elemento e){

	int i;
	int indice = busca_seq(lista, e);

	if(indice >= 0) {

		lista->livre--;

		for(i = indice; i < lista->livre; i++){

			lista->a[i] = lista->a[i + 1];
		}

		return TRUE;
	}
	return FALSE;
}

//Lista ligada

ListaLigada * cria_lista_ligada(){

	ListaLigada * lista =  (ListaLigada *) malloc (sizeof(ListaLigada));
	lista->primeiro = NULL;
	
		return lista;
}

ListaLigadaLinhas * cria_lista_ligada_linhas(){
	
	ListaLigadaLinhas * lista = (ListaLigadaLinhas *)malloc(sizeof(ListaLigadaLinhas));
	lista->primeiro = NULL;
	return lista;
}

void destroi_lista_ligada(ListaLigada * lista){

	No * p = lista->primeiro;
	No * tmp;

	while(p){
		
		tmp = p;
		p = p->proximo;
		free(tmp);
	}
	free(lista);
}

int tamanho_ligada(ListaLigada * lista){

	int tamanho = 0;

	No * p = lista->primeiro;
	
	while(p){
		
		tamanho++;
		p = p->proximo;
	}
	return tamanho;
}

void imprime_ligada(ListaLigada * lista){	
	No * p;
	printf("Lista: \n");

	for(p = lista->primeiro; p; p = p->proximo){		
		printf("Palavra: %s, ", p->valor);
		
		no_Linhas * aux;
		
		printf("linhas: ");
		for(aux = p->lista_nos_linhas->primeiro;aux;aux = aux->proximo){
			
			printf("%d, ", aux->linha);
		}
	
		printf("ocorrencias: %d", p->quantidade);
		
		printf("\n");		
	}
	printf("\n");
}

char * substitui_maiusculas(char * ponteiro){
	
	char * p = (char *)malloc(sizeof(char)* 50);
	strncpy(p, ponteiro, 50);
	for(int i = 0;p[i] != '\0';i++){
		if(p[i] >= 65 && p[i] <= 90)
			p[i] += 32;
	}
	return p;
}

No * busca_ligada(ListaLigada * lista, Elemento e){
	No * p = lista->primeiro;
	char* aux1;
	char* aux2;
	
	while(p){
		aux1 = substitui_maiusculas(p->valor);
		aux2 = substitui_maiusculas(e);
		
		if(strcmp(aux1, aux2) == 0){
			free(aux1);
			free(aux2);
			return p;	
		}
		free(aux1);
		free(aux2);
		p = p->proximo;      	
	}	
	return NULL;	
}

Boolean push(ListaLigada * lista, Elemento e, int indice){
	
	No * p;
	no_Linhas * ant;
	no_Linhas * prox;
	no_Linhas * aux;
	
	if((p = busca_ligada(lista, e))){
		p->quantidade++;
		for(aux = p->lista_nos_linhas->primeiro; aux; aux = aux->proximo){
			if (aux->linha == indice)
				return TRUE;
		}
		no_Linhas * novo_no_linha = (no_Linhas *)malloc(sizeof(no_Linhas));
		novo_no_linha->linha = indice;
		prox = p->lista_nos_linhas->primeiro;
		while(prox){
			ant = prox;
			prox = prox->proximo;
		}
		novo_no_linha->proximo = ant->proximo;
		ant->proximo = novo_no_linha;
		return TRUE;
	}
	No * novo = (No *)malloc(sizeof(No));
	Lista_Ligada_Linhas * novo_lista_linhas = (Lista_Ligada_Linhas *)malloc(sizeof(Lista_Ligada_Linhas));
	no_Linhas * novo_no_linhas = (no_Linhas *)malloc(sizeof(no_Linhas));
	novo_no_linhas->linha = indice;
	novo_no_linhas->proximo = NULL;
	novo_lista_linhas->primeiro = novo_no_linhas;
	
	novo->valor = e;
	novo->lista_nos_linhas = novo_lista_linhas;
	novo->quantidade = 1;
	novo->proximo = lista->primeiro;
	lista->primeiro = novo;
	return TRUE;
}

Boolean push_linha(ListaLigadaLinhas * lista, Elemento e, int indice){
	
	no_linha * novo = (no_linha *)malloc(sizeof(no_linha));
	if(novo){
		novo->valor = e;
		novo->linha = indice;
		novo->proximo = lista->primeiro;		
		lista->primeiro = novo;
		return TRUE;
	}
	return FALSE;
}

void imprime_linha(ListaLigadaLinhas * lista, int indice){
	
	no_linha * p;
	
	for(p = lista->primeiro; p; p = p->proximo){
		if(p->linha == indice) printf("%04d: %s\n", p->linha, p->valor);
	}
}