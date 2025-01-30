#ifndef UTILS_H
#define UTILS_H

#include "inscricao.h"

void limparBuffer();
void limparTela();
void mostrarCabecalho();
int isAnoBissexto(int ano);
int getDiasPorMes(int mes, int ano);
int validarData(TData data);
void lerString(char* destino, int tamanho, const char* mensagem); //const char usado para garantir que a mensagem não seja alterada 
int lerInteiro(const char* mensagem, int min, int max);
TData lerData(const char* mensagem);
int validarIdade(int idade);
int calcularIdade(TData dataNascimento, TData dataReferencia);
int validarCoerenciaDatas(TData dataNascimento, TData dataInscricao, int idadeInformada);
int verificarNomeDuplicado(TInscricao* inscricoes, int total, const char* nome);
#endif //UTILS_H