#include "inscricao.h"
#include "utils.h"

TInscricao lerInscricao(int id, TInscricao* inscricoes, int totalInscricoes) {
    TInscricao inscricao;
    inscricao.id = id;

    do {
        lerString(inscricao.nome, MAX_NOME, "Nome da crianca: ");
        if (verificarNomeDuplicado(inscricoes, totalInscricoes, inscricao.nome)) {
            printf("Já existe uma criança com este nome. Por favor, use um nome diferente.\n");
            continue;
        }
        else if (strlen(inscricao.nome) == 0) {
            printf("Por favor preencha o campo.\n"); //garante que a string não esteja vazia 
            continue;
        }
        break;
    } while (1);

    inscricao.idade = lerInteiro("Idade da crianca: ", IDADE_MINIMA, IDADE_MAXIMA);

    inscricao.dataNascimento = lerData("Data de nascimento (dd/mm/aaaa): ");

    printf("Regime alimentar:\n");
    printf("0 - Sem refeicoes\n");
    printf("1 - Meia pensao\n");
    printf("2 - Pensao completa\n");
    inscricao.regimeAlimentar = lerInteiro("Escolha o regime: ", 0, 2);

    inscricao.dataInscricao = lerData("Data de inscricao (dd/mm/aaaa): ");

    if (!validarCoerenciaDatas(inscricao.dataNascimento, inscricao.dataInscricao, inscricao.idade)) {
        printf("Erro: Inconsistência entre datas e idade informada.\n");
        inscricao.id = -1;
        return inscricao;
    }

    float valores[] = { 100.0, 150.0, 200.0 };
    inscricao.valor = valores[inscricao.regimeAlimentar];

    return inscricao;
}

void mostrarInscricao(TInscricao inscricao) {
    const char* regimes[] = { "Sem refeicoes", "Meia pensao", "Pensao completa" };
    printf("\n=== Dados da Inscrição ===\n");
    printf("ID: %d\n", inscricao.id);
    printf("Nome: %s\n", inscricao.nome);
    printf("Idade: %d anos\n", inscricao.idade);
    printf("Data de Nascimento: %02d/%02d/%d\n",
        inscricao.dataNascimento.dia,
        inscricao.dataNascimento.mes,
        inscricao.dataNascimento.ano);
    printf("Regime Alimentar: %s\n", regimes[inscricao.regimeAlimentar]);
    printf("Data de Inscrição: %02d/%02d/%d\n",
        inscricao.dataInscricao.dia,
        inscricao.dataInscricao.mes,
        inscricao.dataInscricao.ano);
    printf("Valor: %.2f $\n", inscricao.valor);
}

void gravarInscricoes(TInscricao* inscricoes, int total) {
    FILE* fp = fopen(PATH, "wb");
    if (!fp) {
        perror("Erro ao abrir o arquivo para gravacao");
        return;
    }

    if (fwrite(inscricoes, sizeof(TInscricao), total, fp) != total) {
        perror("Erro na gravação dos dados");
        fclose(fp);
        return;
    }

    fclose(fp);
    printf("Inscricoes gravadas com sucesso.\n");

}


int lerInscricoes(TInscricao* inscricoes, int* idCounter) {
    FILE* fp = fopen(PATH, "rb");
    if (!fp) {
        printf("Nenhum arquivo de inscrições encontrado.\n");
        return 0;
    }

    int total = 0;
    *idCounter = 1;

    while (fread(&inscricoes[total], sizeof(TInscricao), 1, fp) == 1) {
        if (inscricoes[total].id >= *idCounter) {
            *idCounter = inscricoes[total].id + 1;
        }
        total++;
        if (total >= MAX_INSCRICOES) {
            printf("Aviso: Limite máximo de inscrições atingido.\n");
            break;
        }
    }

    fclose(fp);
    return total;
}

void listarInscricoes(TInscricao* inscricoes, int total) {
    if (total == 0) {
        printf("Nenhuma inscrição encontrada.\n");
        return;
    }

    printf("\n=== Lista de Todas as Inscrições ===\n");
    for (int i = 0; i < total; i++) {
        mostrarInscricao(inscricoes[i]);
        printf("\n");
    }
    printf("Total de inscrições: %d\n", total);
}

void gerarEstatisticas(TInscricao* inscricoes, int total) {
    if (total == 0) {
        printf("Não há inscrições para gerar estatísticas.\n");
        return;
    }

    int totalPorRegime[3] = { 0 };
    float valorTotal = 0;
    float valorMedio = 0;
    int idadeMaisComum = 0;
    int contIdade[13] = { 0 };

    for (int i = 0; i < total; i++) {
        totalPorRegime[inscricoes[i].regimeAlimentar]++;
        valorTotal += inscricoes[i].valor;
        contIdade[inscricoes[i].idade]++;
    }

    int maxCont = 0;
    for (int i = IDADE_MINIMA; i <= IDADE_MAXIMA; i++) {
        if (contIdade[i] > maxCont) {
            maxCont = contIdade[i];
            idadeMaisComum = i;
        }
    }

    valorMedio = valorTotal / total;

    printf("\n=== Estatísticas do ATL ===\n");
    printf("Total de inscrições: %d\n", total);
    printf("Valor total arrecadado: %.2f $\n", valorTotal);
    printf("Valor médio por inscrição: %.2f $\n", valorMedio);
    printf("\nDistribuição por regime alimentar:\n");
    printf("- Sem refeições: %d (%.1f%%)\n", totalPorRegime[0], (float)totalPorRegime[0] / total * 100);
    printf("- Meia pensão: %d (%.1f%%)\n", totalPorRegime[1], (float)totalPorRegime[1] / total * 100);
    printf("- Pensão completa: %d (%.1f%%)\n", totalPorRegime[2], (float)totalPorRegime[2] / total * 100);
    printf("\nIdade mais comum: %d anos (%d crianças)\n", idadeMaisComum, maxCont);
}

void removerInscricao(TInscricao* inscricoes, int* total, int id) {
    // Procurar a inscrição com o ID especificado
    for (int i = 0; i < *total; i++) {
        if (inscricoes[i].id == id) {
            for (int j = i; j < *total - 1; j++) {
                inscricoes[j] = inscricoes[j + 1];
                inscricoes[j].id = id++;
            }
            (*total)--;
            printf("O aniversaiante foi removido com sucesso!\n");
            return;
        }
    }
    printf("O aniversariante nao foi encontrado\n");
}

void ordenarInscricoesPorValor(TInscricao* inscricoes, int total) {
    // Usando bubble sort para ordenar por valor (decrescente)
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (inscricoes[j].valor < inscricoes[j + 1].valor) {
                // Trocar posições
                TInscricao temp = inscricoes[j];
                inscricoes[j] = inscricoes[j + 1];
                inscricoes[j + 1] = temp;
            }
        }
    }

    printf("\nInscrições ordenadas por valor (decrescente):\n");
    listarInscricoes(inscricoes, total);
}

float calcularValorTotal(TInscricao* inscricoes, int total) {
    float valorTotal = 0.0f;
    for (int i = 0; i < total; i++) {
        valorTotal += inscricoes[i].valor;
    }
    return valorTotal;
}