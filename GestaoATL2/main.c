/*
Ao usar o gcc utilizar este comando no root folder "diretório raiz" para compilar todos os
    gcc -fdiagnostics-color=always -g src/main.c src/inscricao.c src/utils.c -o build/main.exe
    compilador | diagnostico (erros e avisos) | -g para debug | todos os codigos a serem compilados | -o vai compilar cada um dos files em ficheiros objeto| gera o a build final/executavel que é o main.exe

    a explicação para não ser possível compilar através somente tdo main.c é pq este depende das functions e "defines" que inserirmos na inscircao e utils
*/
#include "inscricao.h"
#include "utils.h"

int menu() {
    limparTela();
    mostrarCabecalho();
    printf("\nMENU\n");
    printf("[1] Inserir Inscrição de uma Criança\n");
    printf("[2] Mostrar Inscrição de uma Criança\n");
    printf("[3] Gravar Lista de Inscrições no Ficheiro\n");
    printf("[4] Ler Lista de Inscrições do Ficheiro e Mostrar\n");
    printf("[5] Listar todas as Inscrições Inseridas\n");
    printf("[6] Gerar Estatísticas\n");
    printf("[7] Listar Inscrição por Número de Identificação\n");
    printf("[8] Remover Inscrição por Número de Identificação\n");
    printf("[9] Ordenar Inscrições por Valor\n");
    printf("[10] Calcular Valor Total das Inscrições\n");
    printf("[0] Sair\n");
    return lerInteiro("Escolha uma opção: ", 0, 10);
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
        case 1: // Inserir Inscrição
            if (totalInscricoes < MAX_INSCRICOES) {
                TInscricao novaInscricao = lerInscricao(idCounter, inscricoes, totalInscricoes);
                if (novaInscricao.id != -1) { // verifica se a inscrição foi valida
                    inscricoes[totalInscricoes] = novaInscricao;
                    totalInscricoes++;
                    idCounter++;
                    printf("\nInscrição realizada com sucesso!\n");
                    printf("Nota: As inscrições só serão salvas ao selecionar a opção 3.\n");
                }
            }
            else {
                printf("Limite máximo de inscrições atingida.\n");
            }
            break;

        case 2: // Mostrar Inscrição por nome
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
                    printf("Inscrição com Nome %s não encontrada.\n", inscricao.nome);
                }
            }
            else {
                printf("Nenhuma inscrição disponível para mostrar.\n");
            }
            break;

        case 3: // Gravar Inscrições
            gravarInscricoes(inscricoes, totalInscricoes);
            break;

        case 4: // Ler Inscrições do Ficheiro e Mostrar
            totalInscricoes = lerInscricoes(inscricoes, &idCounter);
            listarInscricoes(inscricoes, totalInscricoes);
            break;

        case 5: // Listar Todas as Inscrições
            listarInscricoes(inscricoes, totalInscricoes);
            break;

        case 6: // Gerar Estatísticas
            gerarEstatisticas(inscricoes, totalInscricoes);
            break;

        case 7: // Mostrar Inscrição
            if (totalInscricoes > 0) {
                int id = lerInteiro("Insira o ID da inscrição a mostrar: ", 1, idCounter - 1);
                int encontrado = 0;
                for (int i = 0; i < totalInscricoes; i++) {
                    if (inscricoes[i].id == id) {
                        mostrarInscricao(inscricoes[i]);
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Inscrição com ID %d não encontrada.\n", id);
                }
            }
            else {
                printf("Nenhuma inscrição disponível para mostrar.\n");
            }
            break;

        case 8: // Remover Inscrição
            if (totalInscricoes > 0) {
                int id = lerInteiro("Insira o ID da inscrição a remover: ", 1, idCounter - 1);
                removerInscricao(inscricoes, &totalInscricoes, id);
            }
            else {
                printf("Nenhuma inscrição disponível para remover.\n");
            }
            break;

        case 9: // Ordenar por Valor
            if (totalInscricoes > 0) {
                ordenarInscricoesPorValor(inscricoes, totalInscricoes);
            }
            else {
                printf("Nenhuma inscrição disponível para ordenar.\n");
            }
            break;

        case 10: // Calcular Valor Total
            if (totalInscricoes > 0) {
                float valorTotal = calcularValorTotal(inscricoes, totalInscricoes);
                printf("\nValor total de todas as inscrições: %.2f $\n", valorTotal);
            }
            else {
                printf("Nenhuma inscrição disponível para calcular o valor total.\n");
            }
            break;

        case 0: // Sair
            printf("Programa encerrado. Até logo!\n");
            return 0;

        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
        }

        printf("\nPressione Enter para continuar...");
        getchar();
    }

    return 0;
}