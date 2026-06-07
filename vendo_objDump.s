/*.global minha_instrucao

minha_instrucao:

    pushq %rbp

    movq %rsp, %rbp*/

/*.global minha_instrucao
minha_instrucao:
    movabsq $0x1122334455667788, %rax
    call *%rax
    leave
    ret */ 

/*.global minha_instrucao
    minha_instrucao:
        movq %rdi, %r8
        movq %rsi, %r9
        movq %rdx, %r10
*/ 

.global minha_instrucao
    minha_instrucao:
        movabsq $valor, %rdi
        movabsq  $valor, %rsi
        movabsq  $valor, %rdx


/*.global minha_instrucao
    minha_instrucao:
        # Se o primeiro parâmetro recebido tiver que ir para o 1º, 2º ou 3º da original:
        movl %r8d, %edi
        movl %r8d, %esi
        movl %r8d, %edx

        # Se o segundo parâmetro recebido tiver que ir para o 1º, 2º ou 3º da original:
        movl %r9d, %edi
        movl %r9d, %esi
        movl %r9d, %edx
*/