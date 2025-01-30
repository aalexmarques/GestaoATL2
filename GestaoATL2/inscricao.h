//inscricao.h
#ifndef INSCRICAO_H //vai fazer antes do pré-processamento...
#define INSCRICAO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// constantes
#define MAX_NOME 50
#define MAX_INSCRICOES 100
#define IDADE_MINIMA 6
#define IDADE_MAXIMA 12
#define ANO_MINIMO 2013
#define ANO_MAXIMO 2025
#define PATH "./Bin/inscricoes.bin"

// Enum regime alimentar
typedef enum {
    SEM_REFEICOES,
    MEIA_PENSAO,
    PENSAO_COMPLETA
} TipoRegimeAlimentar;

typedef struct {
    int dia, mes, ano;
} TData;

typedef struct {
    int id;
    char nome[MAX_NOME];
    int idade;
    TData dataNascimento;
    TipoRegimeAlimentar regimeAlimentar;
    TData dataInscricao;
    float valor;
} TInscricao;

// protótipos
TInscricao lerInscricao(int id, TInscricao* inscricoes, int totalInscricoes);
void mostrarInscricao(TInscricao inscricao);
void gravarInscricoes(TInscricao* inscricoes, int total);
int lerInscricoes(TInscricao* inscricoes, int* idCounter);
void listarInscricoes(TInscricao* inscricoes, int total);
void gerarEstatisticas(TInscricao* inscricoes, int total);
void removerInscricao(TInscricao* inscricoes, int* total, int id);
void ordenarInscricoesPorValor(TInscricao* inscricoes, int total);
float calcularValorTotal(TInscricao* inscricoes, int total);

#endif // INSCRICAO_H
