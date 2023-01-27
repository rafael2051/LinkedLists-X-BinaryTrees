#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lista.h"
#include "arvore_binaria.h"

#define TAMANHO 1000

int conta_char(char * str){
	int cont = 1;
	for(int i = 0;str[i] != '\0';i++)
		cont++;
	return cont + 1;
}

void substitui_hifen(char * ponteiro){
	for(int i = 0;ponteiro[i] != '\0';i++){
		if(ponteiro[i] == '-' || ponteiro[i] == '/')
			ponteiro[i] = ' ';
	}
}

void tira_char_especial(char * ponteiro){
	for(int i = 0;ponteiro[i] != '\0'; i++){
		if(ponteiro[i] < 64 || ponteiro[i] > 122 || ponteiro[i] == 91 ||  ponteiro[i] == 92 || ponteiro[i] ==  93 || ponteiro[i] ==  94 || ponteiro[i] ==  95 || ponteiro[i] ==  96)
			if(ponteiro[i] != 39)
				ponteiro[i] = '\0';
	}
}

char * strsep(char ** stringp, const char *delim) {
    char * rv = * stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}

char * create_path(char * file_name){
	char * path = (char *)malloc(sizeof(char) * 100);
	char * ref;
	int i;
	strncpy(path, "sample\\", 100);
	ref = strrchr(path, '\\');
	*ref++;
	for(i = 0;file_name[i] != '\0';i++, *ref++)
	{
		*ref = file_name[i];
	}
	*ref = '\0';
	printf("%s\n", path);
	path = realloc(path, strlen(path) + 1);
	path[strlen(path)] = '\0';
	return path;
}

int main(int argc, char ** argv){                                  
	
	FILE * in;
	char * linha;
	char * copia_ponteiro_linha;
	char * quebra_de_linha;
	char * palavra;
	no_Linhas * aux_linhas;
	clock_t t;	
	int contador_linha;
	int soma_val_char_linha;
	float soma_val_char_palavra;
	int valCharLinhaRef;
	char * palavra_aux;
	Linha * aux_linhas_;
	char * path = create_path(argv[1]);
	
	in = fopen(path, "r");
	int quant_char;
	
	if(in){
		
		if(argc == 3){
			
			
			//Implementação do código com estrutura de dados do tipo lista
			
			if(strcmp(argv[2], "lista") == 0)
			{
				
			printf("Tipo de indice: '%s'\n", argv[2]);
			
			printf("Arquivo texto: '%s'\n", argv[1]);
			
			ListaLigadaLinhas * lista_linhas = cria_lista_ligada_linhas();
			
			ListaLigada * lista_palavra = cria_lista_ligada();
			
			char * ponteiro;

			contador_linha = 0;
 			linha = (char *) malloc((TAMANHO + 1) * sizeof(char));
 			
 			t = clock();

			while(in && fgets(linha, TAMANHO, in)){
			
				if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;


				// fazemos uma copia do endereço que corresponde ao array de chars 
				// usado para armazenar cada linha lida do arquivo pois a função 'strsep' 
				// modifica o endereço do ponteiro a cada chamada feita a esta função (e 
				// não queremos que 'linha' deixe de apontar para o inicio do array).

				copia_ponteiro_linha = linha;
				
				printf(">>>>> Inserindo linha %d na lista...\n", contador_linha + 1);
				quant_char = conta_char(linha);
				printf("%d caracteres na linha %d\n", quant_char, contador_linha + 1);
				ponteiro = (char*) malloc(sizeof(char) * quant_char);
				if(ponteiro == NULL) {
					printf("ERRO: Memoria Insuficiente!\n");
					system("pause");
					exit(1);
				}
				strncpy(ponteiro, copia_ponteiro_linha, quant_char);
				printf("Linha %d: %s\n", contador_linha + 1, ponteiro);
				push_linha(lista_linhas, ponteiro, contador_linha + 1);
				
				substitui_hifen(copia_ponteiro_linha);

				while( (palavra = strsep(&copia_ponteiro_linha, " ")) ){

				// antes de guardar a palavra em algum tipo de estrutura usada
				// para implementar o índice, será necessário fazer uma copia
				// da mesma, uma vez que o ponteiro 'palavra' aponta para uma 
				// substring dentro da string 'linha', e a cada nova linha lida
				// o conteúdo da linha anterior é sobreescrito.
				
				
					tira_char_especial(palavra);
				
					
					quant_char = conta_char(palavra);
					ponteiro = (char *) malloc(sizeof(char) * quant_char);
					if(ponteiro == NULL){
						printf("ERRO: Memoria Insuficiente!\n");
						system("pause");
						exit(1);
					}
					
					strncpy(ponteiro, palavra, quant_char);
					push(lista_palavra, ponteiro, contador_linha + 1);	

				}

			contador_linha++;
			}
			
			t = clock() - t;
			
			printf("Numero de linhas no arquivo: %d\n", contador_linha);
			
			//imprime_ligada(lista_palavra);
			
			printf("Tempo para carregar o arquivo e construir o indice: %lfms\n", ((double)t));
			
			
			
			//Ponteiro para char teste que vai receber 'busca palavra' digitado pelo usuário
			char * teste = (char *)malloc(sizeof(char) * 100);
			char * copia_ponteiro_teste = teste;
			char * busca;
			No * p;
			printf("> ");
			gets(teste);
			
			while(strcmp(teste, "fim") != 0){
				t = clock();
				busca = strsep(&copia_ponteiro_teste, " ");
				if(strcmp(busca, "busca") == 0){
					busca = strsep(&copia_ponteiro_teste, " ");
						if((p = busca_ligada(lista_palavra, busca))){
						printf("Existem %d ocorrencias da palavra '%s' na(s) seguintes(s) linha(s):\n", p->quantidade, busca);
						for(aux_linhas = p->lista_nos_linhas->primeiro;aux_linhas; aux_linhas = aux_linhas->proximo){
							imprime_linha(lista_linhas, aux_linhas->linha);
						}
						t = clock() - t;
						printf("Tempo de busca: %lf ms\n", ((double)t));
					}
					else{
						printf("Palavra '%s' nao encontrada.\n", busca);
						t = clock() - t;
						printf("Tempo de busca: %lf ms\n", ((double)t));
					}
				}
				else{
					printf("Opcao invalida\n");
				}
				printf("> ");
				gets(teste);
				copia_ponteiro_teste = teste;
			}

			return 0;
		
			}
			//Implementação do código com estrutura de dados do tipo árvore
			
			else if(strcmp(argv[2], "arvore") == 0){
				printf("Tipo de indice: '%s'\n", argv[2]);
				
				printf("Arquivo texto: '%s'\n", argv[1]);
				
				Arvore_linhas * arvore_linhas = cria_arvore_linhas();
				Arvore_palavras * arvore_palavras = cria_arvore_palavras();
				
				char * ponteiro;

				contador_linha = 0;
 				linha = (char *) malloc((TAMANHO + 1) * sizeof(char));
 			
 				t = clock();
 				
 				while(in && fgets(linha, TAMANHO, in)){
 					
					
			
					if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;
					
					printf(">>>>> Inserindo linha %d na lista...\n", contador_linha + 1);
					copia_ponteiro_linha = linha;
					quant_char = conta_char(linha);
					printf("%d caracteres na linha %d\n", quant_char, contador_linha + 1);
					ponteiro = (char*) malloc(sizeof(char) * quant_char);
					if(ponteiro == NULL){
						printf("ERRO: Memoria Insuficiente!\n");
						system("pause");
						exit(1);
					}
					strncpy(ponteiro, copia_ponteiro_linha, quant_char);
					printf("Linha %d: %s\n", contador_linha + 1, ponteiro);
					
					soma_val_char_linha = somaValChar(ponteiro);
					
					
					insere_ord_linhas(arvore_linhas, ponteiro, soma_val_char_linha, contador_linha + 1, &valCharLinhaRef);
					
					
					substitui_hifen(copia_ponteiro_linha);
					
					
					while( (palavra = strsep(&copia_ponteiro_linha, " ")) ){
						
						tira_char_especial(palavra);
						
						quant_char = conta_char(palavra);
						ponteiro = (char *) malloc(sizeof(char) * quant_char);
						if(ponteiro == NULL){
							printf("ERRO: Memoria Insuficiente!\n");
							system("pause");
							exit(1);
						}
						strncpy(ponteiro, palavra, quant_char);
						
						palavra_aux = substitui_maiusculas_arvore(palavra);
						soma_val_char_palavra = (float)somaValChar(palavra_aux);
						free(palavra_aux);				
						insere_ord_palavras(arvore_palavras, ponteiro, soma_val_char_palavra, contador_linha + 1, valCharLinhaRef);
					}
					
 					contador_linha++;
 					
				}
				
				printf("Numero de linhas no arquivo: %d\n", contador_linha);
				
				t = clock() - t;
				
				printf("Tempo para carregar o arquivo e construir o indice: %lfms\n", ((double)t));	
				
				char * teste = (char *)malloc(sizeof(char) * 100);
				char * copia_ponteiro_teste = teste;
				char * busca;
				No_arvore_palavras * p;
				printf("> ");
				gets(teste);
				
				while(strcmp(teste, "fim") != 0){
					t = clock();
					busca = strsep(&copia_ponteiro_teste, " ");
					if(strcmp(busca, "busca") == 0){
						busca = strsep(&copia_ponteiro_teste, " ");
							if((p = busca_bin_palavra_arvore(arvore_palavras, busca))){
							printf("Existem %d ocorrencias da palavra '%s' na(s) seguintes(s) linha(s):\n", p->quantidade, busca);
							for(aux_linhas_ = p->linhas->primeiro;aux_linhas_; aux_linhas_ = aux_linhas_->prox){
								imprime_linha_bin(arvore_linhas, aux_linhas_->valCharLinha, aux_linhas_->valor_linha);
							}
							t = clock() - t;
							printf("Tempo de busca: %lf ms\n", ((double)t));
						}
						else{
							printf("Palavra '%s' nao encontrada.\n", busca);
							t = clock() - t;
							printf("Tempo de busca: %lf ms\n", ((double)t));
						}
					}
					else{
						printf("Opcao invalida\n");
					}
					printf("> ");
					gets(teste);
					copia_ponteiro_teste = teste;
				}
			}
			else{
				printf(">>>>> Estrutura de dados invalida!\n");
				printf(">>>>> Fim do programa!\n");
				return 1;
			}
		
		}
		
		else{
			printf(">>>>> Argumentos insuficientes!\n");
			printf(">>>>> Fim do programa\n");
			return 1;
		}

		
	}
	
	else{
		
	printf(">>>>> Nao foi possivel abrir o arquivo!\n");
	printf(">>>>> Fim do programa!\n");
	return 1;

	}	
}