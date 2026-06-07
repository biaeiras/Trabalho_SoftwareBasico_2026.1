#include <stdio.h>
#include <assert.h> 
#include "cria_func.h"

int func_identidade(int x){
    return x; 

}

int func_identidade_ptr(char* x){
    return x; 

}

//typedef int (*func_ptr) (int x);

typedef char * (*func_ptr) (void);

int main (void) {
    DescParam params[2];
    func_ptr f_retorno;
    int i;
    unsigned char codigo[500];

    //Teste 1 
    // params[0].tipo_val = INT_PAR; 
    // params[0].orig_val = PARAM;   

    //Teste2 - FIX Inteiro 
    // params[0].tipo_val = INT_PAR;
    // params[0].orig_val = FIX;  
    // params[0].valor.v_int = 42; 

    //Teste3 - FIX ponteiro
    char * msg = "teste ponteiro fixo";
    params[0].tipo_val = PTR_PAR;
    params[0].orig_val = FIX;  
    params[0].valor.v_ptr = msg;


    //cria_func(func_identidade, params, 1, codigo);
    cria_func(func_identidade_ptr, params, 1, codigo);
    f_retorno = (func_ptr) codigo;   

    // int resultado = f_retorno(42);

    // printf("Esperado: 42 | Obtido: %d\n", resultado);
    // assert(resultado == 42); 

    // printf("Teste 1 PASSOU com sucesso!\n");


    // int resultado = f_retorno(0);

    // printf("Esperado: 42 | Obtido: %d\n", resultado);
    // assert(resultado == 42); 

    // printf("Teste 2 PASSOU com sucesso!\n");


    char * resultado = f_retorno();

    printf("Esperado: teste ponteiro fixo | Obtido: %s\n", resultado);
    assert(strcmp(resultado, "teste ponteiro fixo") == 0);

    printf("Teste 3 PASSOU com sucesso!\n");
    return 0;

}