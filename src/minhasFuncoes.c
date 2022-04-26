#include <stdio.h>
#include <stdlib.h>
#include "Lista_Criptografia.h"
/*

Até aqui só foram adaptadas as funçoes do André Backes.

Agora começam as funções da criptografia propriamente ditas.

Além disso, implementei funções para obter do usuário o
modo de operação, a mensagem e a chave.

*/

void recebe_modo(int* modo)
{
    int modo_aux = -1; //Para não haver imprevistos de iniciar com 0 ou 1

    scanf("%d", &modo_aux);

    *modo = modo_aux;
}

void recebe_mensagem(Lista* li_msg)
{
    /*
    OBS: Eu estava tendo um problema para ler as informações do usuario
    por causa do '\n' adicionado na tela devido ao usuario digitar o modo
    de opração e apertar um enter. Por isso, precisei adicionar uma variavel
    'i' para não considerar a primeira interação com o if(letra_msg == '\n')
    e assim o codigo poder funcionar corretamente.
    */

    char letra_msg; //auxiliar
    int i=0;

    while(scanf("%c", &letra_msg))
    {
        if(letra_msg == '\n' && i != 0) //Nao considera um '\n'
            break;

        if(i != 0) //Nao quero que insera o '\n' da OBS
            insere_lista_final(li_msg, letra_msg);

        i++;
    }
}

void recebe_chave(Lista* li_chave)
{
    char letra_chave; //auxiliar

    while(scanf("%c", &letra_chave))
    {
        if(letra_chave == '\n')
            break;

        insere_lista_final(li_chave, letra_chave);
    }
}

int calculo_deslocamento(Lista* li_chave)
{
    int deslocamento = 0;

    Elem* no_chave = *li_chave; //Copia o primeiro elemento da li_chave

    while(no_chave != NULL) //Enquanto nao acabar a lista
    {
        deslocamento = deslocamento ^ no_chave->dado; //'^' operador XOR bit a bit em C
        no_chave = no_chave->prox;                    //Continua a lista para saber o deslocamento da Cifra de César
    }

    deslocamento = deslocamento % 26; //Temos 26 letras no alfabeto

    return deslocamento;
}

int* cria_vetor_intervalos(Lista* li_chave)
{
    /*
    O objetivo desta função é facilitar a criação do vetor de intervalos e respeitar
    a modularização do programa (fazer os comando seguintes na main iria ficar incoerente)
    */

    int* intervalo;
    intervalo = (int*) malloc(tamanho_lista(li_chave)*sizeof(int));

    if(intervalo == NULL)
        exit(0);

    return intervalo;
}

void libera_vetor_intervalos(int* intervalos)
{
    if(intervalos != NULL)
        free(intervalos);
}

void imprime_lista_intervalos(Lista* li_chave, int* intervalos)
{
    int i;

    if(intervalos != NULL)
    {
        for(i=0; i<tamanho_lista(li_chave); i++)
        {
            printf("\nIntervalo[%d] = %d", i, intervalos[i]);
        }
        printf("\n"); //Elegância
    }
}

void calculo_intervalos(Lista* li_chave, int* intervalos, int deslocamento)
{
    int i=0;

    Elem* no_chave = *li_chave;

    while(no_chave != NULL)
    {
        intervalos[i] = (no_chave->dado - 97) ^ deslocamento;
        no_chave = no_chave->prox;

        if(intervalos[i] == 0)
            intervalos[i] = 1;

        i++;
    }
}

int inserir_chave_na_msg(Lista* li_msg, Lista* li_chave, int* intervalo)
{
    if(li_chave == NULL || li_msg == NULL || intervalo == NULL)
        return ERRO;

    //Cria nodos auxiliares

    Elem* no_msg;
    Elem* no_chave;

    no_msg = *li_msg;
    no_chave = *li_chave;

    if(no_msg == NULL || no_msg == NULL)
        return ERRO;

    int aux = 0;                                    //Auxilia para saber qual intervalo deve ser usado
    int percorrido = 0;                             //Quanto já andou na lista (será a posicao de insercao na lista msg)
    int caminhar = 0;                               //Quanto precisa caminhar para inserir char de chave (intervalo)
    int intervalo_size = tamanho_lista(li_chave);
    int aux2 = 0;                                   //Auxilia para saber se houve inserção ou nao

    while(no_msg != NULL)
    {
        aux2 = 0;

        //Se for possivel inserir:
        if(caminhar == intervalo[aux]) //Se ja caminhamos o necessario
        {
            if(insere_lista_posicao(li_msg, no_chave->dado, percorrido)) //Padrao de implementacao da funcao
            {
                caminhar = 0;
                aux2 = 1;    //Houve inserção
                aux++;       //Ja inseriu uma vez usando aquele intervalo! Vai para pŕoximo intervalo

                if(aux == intervalo_size) //Recomeça os intervalos!
                   aux = 0;

                if(no_chave->prox == NULL)//Se for o ultimo elemento da chave, recomeca a chave
                {
                    no_chave = *li_chave;
                }

                else
                {
                    no_chave = no_chave->prox; //Se inseriu, deve avançar na chave
                }
            }
        }

        else //A função insere posicao já avança o no_msg
        {
            no_msg = no_msg->prox;
        }

        percorrido++;

        if(aux2 == 0) //Para o caso de inserção.
            caminhar++;
    }

    return OK;
}

int aplica_lista_cesar(Lista* li_msg, int deslocamento)
{
    if(li_msg == NULL)
        return ERRO;

    Elem* no_msg;
    no_msg = *li_msg;

    if(no_msg == NULL)
        return ERRO;

    while(no_msg != NULL)
    {
        no_msg->dado = (((no_msg->dado - 97) + deslocamento) % 26) + 97;
        deslocamento++;

        if(no_msg->prox == NULL)
            break;

        no_msg = no_msg->prox;
    }

    return OK;
}

void imprime_saida(Lista* li_msg, int tamanho_msg, int tamamho_cript)
{
    //Imprime dados de saída

    printf("%d\n", tamanho_msg);
    printf("%d\n", tamamho_cript);

    Elem* no_msg = *li_msg;

    while(no_msg != NULL)
    {
        printf("%c", no_msg->dado);

        if(no_msg->prox == NULL) //Está no fim da lista
            break;

        no_msg = no_msg->prox;
    }
}

int cesar_reverso(Lista* li_msg, int deslocamento)
{
    int aux_deslocamento = deslocamento;
    char aux_dado;

    Elem* no_msg = *li_msg;

    if(no_msg == NULL)
        return ERRO;

    while(no_msg != NULL)
    {
        aux_dado = (no_msg->dado - 97) - (aux_deslocamento % 26);

        if(aux_dado < 0)
            no_msg->dado = aux_dado + 26 + 97;
        else
            no_msg->dado = aux_dado + 97;

        if(no_msg->prox == NULL) //Fim da lista
            break;

        no_msg = no_msg->prox;
        aux_deslocamento++;
    }

    return OK;
}

int retira_chave_da_msg(Lista* li_msg, Lista* li_chave, int* intervalo)
{
    if(li_chave == NULL || li_msg == NULL || intervalo == NULL)
        return ERRO;

    //Cria nodos auxiliares

    Elem* no_msg;

    no_msg = *li_msg;

    if(no_msg == NULL || no_msg == NULL)
        return ERRO;

    int aux = 0;                                   //Auxilia para saber qual intervalo deve ser usado
    int percorrido = 0;                            //Quanto já andou na lista (será a posicao de remocao da lista msg)
    int caminhar = 0;                              //Quanto precisa caminhar para remover char de chave (intervalo)
    int intervalo_size = tamanho_lista(li_chave);
    int aux2 = 0;                                  //Auxilia para saber se houve remoção ou nao

    while(no_msg != NULL)
    {
        aux2 = 0;

        //Se for possivel inserir:
        if(caminhar == intervalo[aux]) //A chave nao pode ser NULL. Se ja caminhamos o necessario
        {
            if(retira_lista_posicao(li_msg, percorrido+1)) //O "+1" é por causa de como implementei o retira_lista_posicao()
            {
                caminhar = 0;
                aux2 = 1;
                aux++;       //Ja removeu uma vez usando aquele intervalo!

                if(aux >= intervalo_size) //Recomeça os intervalos!
                    aux = 0;
            }
        }

        if(aux2 == 0)//Para o caso de remoção, o numero de elementos da lista diminui, nao acrescentando em "percorrido"
        {
            caminhar++;
            percorrido++;
        }

        no_msg = no_msg->prox;
    }

    return OK;
}




