/*
Ao usar o gcc utilizar este comando no root folder "diret�rio raiz" para compilar todos os
    gcc -fdiagnostics-color=always -g src/main.c src/inscricao.c src/utils.c -o build/main.exe
    compilador | diagnostico (erros e avisos) | -g para debug | todos os codigos a serem compilados | -o vai compilar cada um dos files em ficheiros objeto| gera o a build final/executavel que � o main.exe

    a explica��o para n�o ser poss�vel compilar atrav�s somente tdo main.c � pq este depende das functions e "defines" que inserirmos na inscircao e utils
*/
#include "inscricao.h"
#include "utils.h"

int menu() {
    limparTela();
    mostrarCabecalho();
    printf("\nMENU\n");
    printf("[1] Inserir Inscri��o de uma Crian�a\n");
    printf("[2] Mostrar Inscri��o de uma Crian�a\n");
    printf("[3] Gravar Lista de Inscri��es no Ficheiro\n");
    printf("[4] Ler Lista de Inscri��es do Ficheiro e Mostrar\n");
    printf("[5] Listar todas as Inscri��es Inseridas\n");
    printf("[6] Gerar Estat�sticas\n");
    printf("[7] Listar Inscri��o por N�mero de Identifica��o\n");
    printf("[8] Remover Inscri��o por N�mero de Identifica��o\n");
    printf("[9] Ordenar Inscri��es por Valor\n");
    printf("[10] Calcular Valor Total das Inscri��es\n");
    printf("[0] Sair\n");
    return lerInteiro("Escolha uma op��o: ", 0, 10);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    TInscricao inscricoes[MAX_INSCRICOES];
    int totalInscricoes = 0;
    int idCounter = 1;


    // caregar dados existentes do ficheiro, se houver...
    totalInscricoes = lerInscricoes(inscricoes, &idCounter);

    while (1) {
        int opcao = menu();
        limparTela();
        mostrarCabecalho();

        switch (opcao) {
        case 1: // Inserir Inscri��o
            if (totalInscricoes < MAX_INSCRICOES) {
                TInscricao novaInscricao = lerInscricao(idCounter, inscricoes, totalInscricoes);
                if (novaInscricao.id != -1) { // verifica se a inscri��o foi valida
                    inscricoes[totalInscricoes] = novaInscricao;
                    totalInscricoes++;
                    idCounter++;
                    printf("\nInscri��o realizada com sucesso!\n");
                    printf("Nota: As inscri��es s� ser�o salvas ao selecionar a op��o 3.\n");
                }
            }
            else {
                printf("Limite m�ximo de inscri��es atingida.\n");
            }
            break;

        case 2: // Mostrar Inscri��o por nome
            if (totalInscricoes > 0) {
                TInscricao inscricao;
                int encontrado = 0;
                lerString(inscricao.nome, MAX_NOME, "Nome da crianca: ");
                for (int i = 0; i < totalInscricoes; i++) {
                    if (strcmp(inscricoes[i].nome, inscricao.nome) == 0) {
                        mostrarInscricao(inscricoes[i]);
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Inscri��o com Nome %s n�o encontrada.\n", inscricao.nome);
                }
            }
            else {
                printf("Nenhuma inscri��o dispon�vel para mostrar.\n");
            }
            break;

        case 3: // Gravar Inscri��es
            gravarInscricoes(inscricoes, totalInscricoes);
            break;

        case 4: // Ler Inscri��es do Ficheiro e Mostrar
            totalInscricoes = lerInscricoes(inscricoes, &idCounter);
            listarInscricoes(inscricoes, totalInscricoes);
            break;

        case 5: // Listar Todas as Inscri��es
            listarInscricoes(inscricoes, totalInscricoes);
            break;

        case 6: // Gerar Estat�sticas
            gerarEstatisticas(inscricoes, totalInscricoes);
            break;

        case 7: // Mostrar Inscri��o
            if (totalInscricoes > 0) {
                int id = lerInteiro("Insira o ID da inscri��o a mostrar: ", 1, idCounter - 1);
                int encontrado = 0;
                for (int i = 0; i < totalInscricoes; i++) {
                    if (inscricoes[i].id == id) {
                        mostrarInscricao(inscricoes[i]);
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Inscri��o com ID %d n�o encontrada.\n", id);
                }
            }
            else {
                printf("Nenhuma inscri��o dispon�vel para mostrar.\n");
            }
            break;

        case 8: // Remover Inscri��o
            if (totalInscricoes > 0) {
                int id = lerInteiro("Insira o ID da inscri��o a remover: ", 1, idCounter - 1);
                removerInscricao(inscricoes, &totalInscricoes, id);
            }
            else {
                printf("Nenhuma inscri��o dispon�vel para remover.\n");
            }
            break;

        case 9: // Ordenar por Valor
            if (totalInscricoes > 0) {
                ordenarInscricoesPorValor(inscricoes, totalInscricoes);
            }
            else {
                printf("Nenhuma inscri��o dispon�vel para ordenar.\n");
            }
            break;

        case 10: // Calcular Valor Total
            if (totalInscricoes > 0) {
                float valorTotal = calcularValorTotal(inscricoes, totalInscricoes);
                printf("\nValor total de todas as inscri��es: %.2f $\n", valorTotal);
            }
            else {
                printf("Nenhuma inscri��o dispon�vel para calcular o valor total.\n");
            }
            break;

        case 0: // Sair
            printf("Programa encerrado. At� logo!\n");
            return 0;

        default:
            printf("Op��o inv�lida. Tente novamente.\n");
            break;
        }

        printf("\nPressione Enter para continuar...");
        getchar();
    }

    return 0;
}