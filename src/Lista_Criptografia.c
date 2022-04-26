#include <stdio.h>
#include <stdlib.h>
#include "Lista_Criptografia.h" //inclui os Protótipos

Lista* cria_lista()
{
    Lista* li;

    li = (Lista*) malloc(sizeof(Lista));

    if(li != NULL)
        *li = NULL;

    return li;
}

void libera_lista(Lista* li)
{
    if(li != NULL)
    {
        Elem* no;

        while((*li) != NULL)
        {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }

        free(li);
    }
}

int insere_lista_final(Lista* li, char dt)
{
    Elem *no;

    if (li == NULL)
        return ERRO;

    no = (Elem*) malloc(sizeof(Elem));

    if (no == NULL)
        return ERRO;

    no->dado = dt;
    no->prox = NULL;

    if ((*li) == NULL)//lista vazia: insere início
    {
        *li = no;
    }
    else
    {
        Elem *aux;
        aux = *li;

        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }

        aux->prox = no;
    }

    return OK;
}

int insere_lista_inicio(Lista* li, char dt)
{
    Elem* no;

    if (li == NULL)
        return ERRO;

    no = (Elem*) malloc(sizeof(Elem));

    if (no == NULL)
        return ERRO;

    no->dado = dt;
    no->prox = (*li);
    *li = no;

    return OK;
}

int insere_lista_ordenada(Lista* li, char dt)
{
    if (li == NULL)
        return ERRO;

    Elem *no = (Elem*) malloc(sizeof(Elem));

    if (no == NULL)
        return ERRO;

    no->dado = dt;

    if ((*li) == NULL)//lista vazia: insere início
    {
        no->prox = NULL;
        *li = no;

        return OK;
    }

    else
    {
        Elem *ant, *atual = *li;

        while (atual != NULL && atual->dado < dt)
        {
            ant = atual;
            atual = atual->prox;
        }

        if (atual == *li)//insere início
        {
            no->prox = (*li);
            *li = no;
        }

        else
        {
            no->prox = atual;
            ant->prox = no;
        }

        return OK;
    }
}

int remove_lista(Lista* li, char dt)
{
    if(li == NULL)
        return ERRO;

    if((*li) == NULL)//lista vazia
        return ERRO;

    Elem *ant, *no = *li;

    while(no != NULL && no->dado != dt)
    {
        ant = no;
        no = no->prox;
    }

    if(no == NULL) //não encontrado
        return ERRO;

    if(no == *li) //remover o primeiro?
        *li = no->prox;

    else
        ant->prox = no->prox;

    free(no);

    return OK;
}

int remove_lista_inicio(Lista* li)
{
    if(li == NULL)
        return ERRO;

    if((*li) == NULL) //lista vazia
        return ERRO;

    Elem *no = *li;
    *li = no->prox;

    free(no);

    return OK;
}

int remove_lista_final(Lista* li)
{
    if(li == NULL)
        return ERRO;

    if((*li) == NULL) //lista vazia
        return ERRO;

    Elem *ant, *no = *li;

    while(no->prox != NULL)
    {
        ant = no;
        no = no->prox;
    }

    if(no == (*li)) //remover o primeiro?
        *li = no->prox;

    else
        ant->prox = no->prox;

    free(no);

    return OK;
}

int tamanho_lista(Lista* li)
{
    if(li == NULL)
        return ERRO;

    int cont = 0;

    Elem* no = *li;

    while(no != NULL)
    {
        cont++;
        no = no->prox;
    }

    return cont;
}

int lista_cheia(Lista* li)
{
    return 0;
}

int lista_vazia(Lista* li)
{
    if(li == NULL)
        return OK;

    if(*li == NULL)
        return OK;

    return ERRO;
}

void imprime_lista(Lista* li)
{
    if(li == NULL)
        return;

    Elem* no = *li;

    while(no != NULL)
    {
        printf("Dado: %c # %p - %p\n",no->dado,no,no->prox);
        no = no->prox;
    }

    printf("-------------- FIM LISTA -----------------\n");
}

int insere_lista_posicao(Lista* li, char letra, int posicao)
{
    if (li == NULL)
        return ERRO;

    Elem *no = (Elem*) malloc(sizeof(Elem));

    if (no == NULL)
        return ERRO;

    int i=0;
    no->dado = letra;

    if ((*li) == NULL)//lista vazia: insere início
    {
        no->prox = NULL;
        *li = no;

        return OK;
    }

    else
    {
        Elem *ant;
        Elem* atual = *li; //Atual aponta para o primeiro

        while (atual != NULL && i < posicao) //Enquanto nao chega na posicao e nem no fim da lista
        {
            ant = atual;
            atual = atual->prox;
            i++;
        }

        if (atual == *li) //insere início
        {
            no->prox = (*li);
            *li = no;
        }

        else
        {
            no->prox = atual;
            ant->prox = no;
        }

        return OK;
    }
}

int retira_lista_posicao(Lista* li, int posicao)
{
    if (li == NULL)
        return ERRO;

    int i=0; //Contador para a posição

    Elem* ant;
    Elem* atual = *li; //ATUAL APONTA PARA O PRIMEIRO DA LISTA!!!

    if(atual == NULL) //Lista vazia
        return ERRO;

    while (atual != NULL && i < posicao - 1) //Enquanto "atual" nao chega na posicao e nem no fim da lista
    {
        ant = atual;
        atual = atual->prox;
        i++;
    }

    if(i == 0)//Remove primeiro elemento da lista
    {
        *li = atual->prox; //Movo o inicio para o segundo da lista
        free(atual); //Excluo o primeiro
    }

    else if(i == tamanho_lista(li)) //Remove o ultimo elemento
    {
        ant->prox = NULL; //O anterior do ultimo é o penultimo, que se torna o ultimo
        free(atual);
    }

    else
    {
        ant->prox = atual->prox; //Vou "pular o atual"

        free(atual); //Excluo o no da posicao "posicao
    }

    return OK;
}






