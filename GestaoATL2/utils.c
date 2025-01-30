#include "utils.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Stackoverflow... Os #ifdef, #else, #endif são diretivas de pre-possecamento, significa que vêm antes da compilação necessario para este caso
void limparTela() {
#ifdef _WIN32 // este limpa a tela para sistemas Windows 
    system("cls");
#else //Este aqui vai limpar a tela para sistmas Unix tipo linux ou MacOS
    system("clear");
#endif // vai terminar a condicao de pre-processamento
}

void mostrarCabecalho() {
    printf("=====================================\n");
    printf("    Gestão de ATL - Agosto 2025    \n");
    printf("=====================================\n");
}

int isAnoBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int getDiasPorMes(int mes, int ano) {
    int dias[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (mes == 2 && isAnoBissexto(ano)) return 29;
    return dias[mes - 1];
}

int validarData(TData data) {
    if (data.ano < ANO_MINIMO || data.ano > ANO_MAXIMO) return 0;
    if (data.mes < 1 || data.mes > 12) return 0;
    if (data.dia < 1 || data.dia > getDiasPorMes(data.mes, data.ano)) return 0;
    return 1;
}

void lerString(char* destino, int tamanho, const char* mensagem) {
    printf("%s", mensagem);
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = 0; //localiza a posição de "\n" no código e transforma em nulo
}

int lerInteiro(const char* mensagem, int min, int max) {
    int valor;
    do {
        printf("%s", mensagem);
        if (scanf("%d", &valor) != 1) {
            limparBuffer();
            printf("Por favor, insira um número válido.\n");
            continue;
        }
        limparBuffer();
        if (valor < min || valor > max) {
            printf("O valor deve estar entre %d e %d.\n", min, max);
            continue;
        }
        break;
    } while (1);
    return valor;
}

TData lerData(const char* mensagem) {
    TData data;
    do {
        printf("%s", mensagem);
        if (scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano) != 3) {
            limparBuffer();
            printf("Formato inválido. Use dd/mm/aaaa.\n");
            continue;
        }
        limparBuffer();
        if (!validarData(data)) {
            printf("Data inválida.\n");
            continue;
        }
        break;
    } while (1);
    return data;
}

int validarIdade(int idade) {
    return idade >= IDADE_MINIMA && idade <= IDADE_MAXIMA;
}

int calcularIdade(TData dataNascimento, TData dataReferencia) {
    int idade = dataReferencia.ano - dataNascimento.ano;
    if (dataReferencia.mes < dataNascimento.mes ||
        (dataReferencia.mes == dataNascimento.mes && dataReferencia.dia < dataNascimento.dia)) {
        idade--;
    }
    return idade;
}

int validarCoerenciaDatas(TData dataNascimento, TData dataInscricao, int idadeInformada) {
    int idadeCalculada = calcularIdade(dataNascimento, dataInscricao);
    return idadeCalculada == idadeInformada;
}

int verificarNomeDuplicado(TInscricao* inscricoes, int total, const char* nome) {
    for (int i = 0; i < total; i++) {
        if (_stricmp(inscricoes[i].nome, nome) == 0) { //sim, funciona pq estamos a incluir inscricoes.h em utils.h
            return 1;
        }
    }
    return 0;
}