/*!
 * \file estacionamento.h
 * \brief Declaração das estruturas e funções relacionadas ao estacionamento.
 * \authores
 * \date 20/03/2024
 */

#ifndef UNTITLED2_ESTACIONAMENTO_H
#define UNTITLED2_ESTACIONAMENTO_H

#include "dataHora.h"
#include <malloc.h>
#include <stdio.h>

#define ZERO 0
#define ONE 1
#define TAM_HORA 4
#define TAM_DIA 96
#define TAM_MIN 15

/*!
 * \struct Carro
 * \brief Estrutura do tipo nó de uma lista encadeada de carros.
 */
typedef struct Carro {
    DataHora dataHoraEntrada; //!< Data e hora de entrada
    DataHora dataHoraSaida; //!< Data e hora de saída
    char *matricula; //!< Matrícula do carro
    int Historico; //!< 0 atual, 1 histórico
    struct Carro *prox; //!< Próximo carro na lista encadeada
} Carro;

/*!
 * \struct Estacionamento
 * \brief Estrutura que representa um estacionamento armazenando a lista de carros.
 */
typedef struct Estacionamento {
    char* nome; //!< Nome do estacionamento
    int ocupacao; //!< Ocupação atual
    int capacidade; //!< Capacidade máxima
    float valorMinuto; //!< Valor por minuto
    float valorHora; //!< Valor por hora
    float valorDia; //!< Valor por dia
    Carro *carros; //!< Lista de carros no estacionamento
} Estacionamento;

/*!
 * \brief Inicializa um estacionamento.
 * \param nome Nome do estacionamento.
 * \param capacidade Capacidade máxima do estacionamento.
 * \param valorMinuto Valor por minuto de estacionamento.
 * \param valorHora Valor por hora de estacionamento.
 * \param valorDia Valor por dia de estacionamento.
 * \return O estacionamento inicializado.
 */
Estacionamento estacionamentoInit(char* nome, int capacidade, float valorMinuto, float valorHora, float valorDia);

/*!
 * \brief Calcula o preço de estacionamento para um determinado período.
 * \param minutosEntrada Minutos da entrada desde 0-0-0 00:00.
 * \param minutosSaida Minutos de saída desde 0-0-0 00:00.
 * \param estacionamento O estacionamento para o qual o preço está sendo calculado.
 * \return O preço calculado.
 */
float calcularPreco(int minutosEntrada, int minutosSaida, Estacionamento *estacionamento);

/*!
 * \brief Adiciona um carro ao estacionamento.
 * \param matricula Matrícula do carro a ser adicionado.
 * \param estacionamento O estacionamento onde o carro será adicionado.
 * \param dataHoraEntrada Data e hora de entrada do carro.
 */
void adicionarCarro(char *matricula, Estacionamento *estacionamento, DataHora dataHoraEntrada);

/*!
 * \brief Remove um carro do estacionamento.
 * \param estacionamento O estacionamento de onde o carro será removido.
 * \param matricula Matrícula do carro a ser removido.
 * \param dataHoraSaida Data e hora de saída do carro.
 */
void saidaCarro(Estacionamento *estacionamento, char *matricula, DataHora dataHoraSaida);



#endif //UNTITLED2_ESTACIONAMENTO_H
