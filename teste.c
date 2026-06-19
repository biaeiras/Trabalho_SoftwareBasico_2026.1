#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "cria_func.h"

/* ---------- Funções usadas nos testes ---------- */

int func_identidade_int(int x) {
    return x;
}

char *func_identidade_ptr(char *x) {
    return x;
}

int soma3(int a, int b, int c) {
    printf("soma3 recebeu: a=%d b=%d c=%d\n", a, b, c);
    return a + b + c;
}

int multiplica_por_2(int x) {
    return 2 * x;
}

/* ---------- Tipos das funções geradas ---------- */

typedef int   (*func_int_int)(int);
typedef int   (*func_int_void)(void);
typedef char *(*func_ptr_void)(void);
typedef int   (*func_2ints)(int, int);

int main(void) {
    unsigned char codigo[500];

    printf("==== TESTE 1: PARAM int ====\n");
    {
        DescParam params[1];
        func_int_int f;

        params[0].tipo_val = INT_PAR;
        params[0].orig_val = PARAM;

        cria_func(func_identidade_int, params, 1, codigo);
        f = (func_int_int) codigo;

        int resultado = f(42);

        printf("Esperado: 42 | Obtido: %d\n", resultado);
        assert(resultado == 42);

        printf("Teste 1 PASSOU!\n\n");
    }

    printf("==== TESTE 2: FIX int ====\n");
    {
        DescParam params[1];
        func_int_void f;

        params[0].tipo_val = INT_PAR;
        params[0].orig_val = FIX;
        params[0].valor.v_int = 42;

        cria_func(func_identidade_int, params, 1, codigo);
        f = (func_int_void) codigo;

        int resultado = f();

        printf("Esperado: 42 | Obtido: %d\n", resultado);
        assert(resultado == 42);

        printf("Teste 2 PASSOU!\n\n");
    }

    printf("==== TESTE 3: FIX ponteiro ====\n");
    {
        DescParam params[1];
        func_ptr_void f;

        char *msg = "teste ponteiro fixo";

        params[0].tipo_val = PTR_PAR;
        params[0].orig_val = FIX;
        params[0].valor.v_ptr = msg;

        cria_func(func_identidade_ptr, params, 1, codigo);
        f = (func_ptr_void) codigo;

        char *resultado = f();

        printf("Esperado: %s | Obtido: %s\n", msg, resultado);
        assert(strcmp(resultado, msg) == 0);

        printf("Teste 3 PASSOU!\n\n");
    }

    printf("==== TESTE 4: PARAM, FIX, PARAM ====\n");
    {
        DescParam params[3];
        func_2ints f;

        /*
           Queremos gerar uma função que recebe dois argumentos:
             f(3, 7)

           Mas chama:
             soma3(3, 10, 7)

           Ou seja:
             params[0] = PARAM
             params[1] = FIX 10
             params[2] = PARAM
        */

        params[0].tipo_val = INT_PAR;
        params[0].orig_val = PARAM;

        params[1].tipo_val = INT_PAR;
        params[1].orig_val = FIX;
        params[1].valor.v_int = 10;

        params[2].tipo_val = INT_PAR;
        params[2].orig_val = PARAM;

        cria_func(soma3, params, 3, codigo);
        f = (func_2ints) codigo;

        int resultado = f(3, 7);

        printf("Esperado: 20 | Obtido: %d\n", resultado);
        assert(resultado == 20);

        printf("Teste 4 PASSOU!\n\n");
    }

    printf("==== TESTE 5: IND int ====\n");
    {
        DescParam params[1];
        func_int_void f;

        int x = 21;

        /*
           IND significa que a função gerada não recebe esse parâmetro.
           Ela busca o valor atual da variável x.
        */

        params[0].tipo_val = INT_PAR;
        params[0].orig_val = IND;
        params[0].valor.v_ptr = &x;

        cria_func(multiplica_por_2, params, 1, codigo);
        f = (func_int_void) codigo;

        int resultado = f();

        printf("Esperado: 42 | Obtido: %d\n", resultado);
        assert(resultado == 42);

        x = 30;
        resultado = f();

        printf("Depois de mudar x:\n");
        printf("Esperado: 60 | Obtido: %d\n", resultado);
        assert(resultado == 60);

        printf("Teste 5 PASSOU!\n\n");
    }

    printf("Todos os testes passaram!\n");

    return 0;
}