#include "cria_func.h"

void cria_func (void* f, DescParam params[], int n, unsigned char codigo[]){
    int indice = 0; 

    //prologo: 
//      <minha_instrucao>:
//    0:   55                      push   %rbp
//    1:   48 89 e5                mov    %rsp,%rbp

    codigo[indice++] = 0x55; 
    codigo[indice++] = 0x48;
    codigo[indice++] = 0x89;
    codigo[indice++] = 0xe5;   
    //agora está no indice = 4 

    //Para não perder os valores passados pela função %rdi, %rdi e %rdx ( estamos lidando com inteiro) passamos para outros registradores
    // não são callee-saved 

//     0000000000000000 <minha_instrucao>:
//    0:   49 89 f8                mov    %rdi,%r8
//    3:   49 89 f1                mov    %rsi,%r9
//    6:   49 89 d2                mov    %rdx,%r10
    

    // movendo para %r8
    codigo[indice++] = 0x49;
    codigo[indice++] = 0x89;
    codigo[indice++] = 0xf8; 

    // movendo para %r9 

    codigo[indice++] = 0x49;
    codigo[indice++] = 0x89;
    codigo[indice++] = 0xf1; 

    // movendo para %r10 

    codigo[indice++] = 0x49;
    codigo[indice++] = 0x89;
    codigo[indice++] = 0xd2; 


    //Verificar os parâmetros fix e colocar no espaço certo 
    
    for(int  i = 0; i < n; i++){
        if(params[i].orig_val == FIX){

             if(params[i].tipo_val == INT_PAR){

                //     0000000000000000 <minha_instrucao>:
                //    0:   bf 00 00 00 00          mov    $0x0,%edi
                //    5:   be 00 00 00 00          mov    $0x0,%esi
                //    a:   ba 00 00 00 00          mov    $0x0,%edx

                if (i == 0){
                //se i = 0 significa que é o primeiro parâmetro e precisa ir para %rdi
                //agora precisa passar o valor repassado nos registradores certos 
                codigo[indice++] = 0xbf; 
            
                }

                if (i == 1){
                    //i = 1 significa que é o segundo parâmetro e precisa ir pra %esi
                    codigo[indice++] = 0xbe; 
                }

                if (i == 2){
                    //i = 2 significa que é o terceiro parâmetro e precisa ir pra o %edx

                    codigo[indice++] = 0xba; 
                }

                *(int*)&codigo[indice] = params[i].valor.v_int; 
                indice += 4; 

                
            
            }

            if(params[i].tipo_val == PTR_PAR){
                // 0000000000000000 <minha_instrucao>:
                //     0:   48 bf 00 00 00 00 00    movabs $0x0,%rdi
                //     7:   00 00 00 
                //     a:   48 be 00 00 00 00 00    movabs $0x0,%rsi
                //     11:   00 00 00 
                //     14:   48 ba 00 00 00 00 00    movabs $0x0,%rdx
                //     1b:   00 00 00 

                 if (i == 0){
                    //se i = 0 significa que é o primeiro parâmetro e precisa ir para %rdi
                    //agora precisa passar o valor repassado nos registradores certos 
                    codigo[indice++] = 0x48;
                    codigo[indice++] = 0xbf; 
            
                }

                if (i == 1){
                    //i = 1 significa que é o segundo parâmetro e precisa ir pra %esi
                    codigo[indice++] = 0x48;
                    codigo[indice++] = 0xbe; 
                }

                if (i == 2){
                    //i = 2 significa que é o terceiro parâmetro e precisa ir pra o %edx
                    codigo[indice++] = 0x48;
                    codigo[indice++] = 0xba; 
                }

                *(void**)&codigo[indice] = params[i].valor.v_ptr; 
                indice += 8; 
            }
        }
            
    }




    //    movabsq $0x1122334455667788, %rax
    // call *%rax
    // leave
    // ret
    //chamada da função original 
    //movendo o valor do endereço da função para rax 
    codigo[indice++] = 0x48;
    codigo[indice++] = 0xb8;

    //Problema : codigo[] é char e o endereço da função original é ponteiro
    //então dá erro fazendo codigo[indice] = f 
    //void indicando que é um ponteiro apontando para outro ponteiro assim ele sabe que mede 8 bytes
    *(void**)&codigo[indice] = f ; 


    //ajustando o indice 

    indice+= 8; 

    //chamando a função 

    codigo[indice++] = 0xff;
    codigo[indice++] = 0xd0;

    
    //leave 
    codigo[indice++] = 0xc9;

    //ret 
    codigo[indice++] = 0xc3;
    
}