/*
Tipo abstrato de dado do tipo lista dinâmica encadeada retirada da wiki
do professor F. Osorio, porem modificada.
*/

#ifndef LISTA_CRIPTOGRAFIA_H
#define LISTA_CRIPTOGRAFIA_H

#define FALSO      0
#define VERDADEIRO 1

#define OK         1
#define ERRO       0

//Definição do tipo lista
struct elemento
{
    char dado;
    struct elemento *prox;
};

typedef struct elemento Elem;

typedef struct elemento* Lista; //Definicao de um ponteiro para o tipo Elem

Lista* cria_lista();
void libera_lista(Lista* li);
int insere_lista_final(Lista* li, char dt);
int insere_lista_inicio(Lista* li, char dt);
int insere_lista_ordenada(Lista* li, char dt);
int remove_lista(Lista* li, char dt);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
int lista_cheia(Lista* li);
void imprime_lista(Lista* li);
int insere_lista_posicao(Lista* li, char letra, int posicao);
int retira_lista_posicao(Lista* li, int posicao);

//Minhas funções
void recebe_modo(int* modo);
void recebe_mensagem(Lista* li_msg);
void recebe_chave(Lista* li_chave);
int calculo_deslocamento(Lista* li_chave);
int* cria_vetor_intervalos(Lista* li_chave);
void libera_vetor_intervalos(int* intervalos);
void imprime_lista_intervalos(Lista* li_chave, int* intervalos);
void calculo_intervalos(Lista* li_chave, int* intervalos, int deslocamento);
int inserir_chave_na_msg(Lista* li_msg, Lista* li_chave, int* intervalo);
int aplica_lista_cesar(Lista* li_msg, int deslocamento);
void imprime_saida(Lista* li_msg, int tamanho_msg, int tamamho_cript);
int cesar_reverso(Lista* li_msg, int deslocamento);
int retira_chave_da_msg(Lista* li_msg, Lista* li_chave, int* intervalo);

#endif // LISTA_CRIPTOGRAFIA_H
