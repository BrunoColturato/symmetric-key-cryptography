#include <stdio.h>
#include <stdlib.h>
#include "Lista_Criptografia.h"

int main()
{
    Lista* li_msg;        //Lista para a mensagem digitada
    Lista* li_chave;      //Lista para a chave digitada

    li_msg = cria_lista();
    li_chave = cria_lista();

    int modo;

    recebe_modo(&modo);
    recebe_mensagem(li_msg);
    recebe_chave(li_chave);

    int deslocamento = calculo_deslocamento(li_chave);

    int* intervalos;
    intervalos = cria_vetor_intervalos(li_chave);
    calculo_intervalos(li_chave, intervalos, deslocamento);

    int tamanho_msg = tamanho_lista(li_msg); //Tamanho da mensagem digitada

    //Modo de encriptar
    if(modo == 0)
    {
        inserir_chave_na_msg(li_msg, li_chave, intervalos);

        aplica_lista_cesar(li_msg, deslocamento);
    }

    //Modo de decriptar
    if(modo == 1)
    {
        cesar_reverso(li_msg, deslocamento);

        retira_chave_da_msg(li_msg, li_chave, intervalos);
    }

    int tamanho_cript = tamanho_lista(li_msg); //Tamanho da mensagem criptografada

    imprime_saida(li_msg, tamanho_msg, tamanho_cript);

    //Libera espaços de memoria alocados
    libera_vetor_intervalos(intervalos);
    libera_lista(li_msg);
    libera_lista(li_chave);

    return 0;
}
