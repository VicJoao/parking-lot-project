/*!
 * \file terminal.h
 * \brief Declaração das estruturas e funções relacionadas ao terminal.
 * \authores
 * \date 20/03/2024
 */

#ifndef UNTITLED2_TERMINAL_H
#define UNTITLED2_TERMINAL_H

#include "estacionamento.h"
#include "dataHora.h"
#include <stdio.h>
#include <ctype.h>

#define ONE 1
#define PAIR 2
#define TRIO 3
#define MAX_PAIR 6
#define MAX_COMAND_SIZE 10000
#define Max_MATRICULA 8
#define  MAX_ESTACIONAMENTOS 20
#define DELIMITTERS " \n\t"
#define ZERO 0


/*!
 * \struct Comand
 * \brief Estrutura que representa um comando.
 */
typedef struct Comand {
    char cmd; //!< Comando
    char *arg; //!< Argumento do comando
} Comand;

/*!
 * \struct Terminal
 * \brief Estrutura que representa um terminal.
 */
typedef struct Terminal {
    DataHora dataHora; //!< Data e hora atual
    Estacionamento *estacionamentos; //!< Lista de estacionamentos
    int estacionamentosSize; //!< Tamanho da lista de estacionamentos
    Comand comandAtual; //!< Comando atual
} Terminal;

/*!
 * \brief Inicializa um comando.
 * \param comand O comando a ser inicializado.
 * \return O ponteiro para o comando inicializado.
 */
Comand *comandInit(char *comand);

/*!
 * \brief Executa um comando.
 * \param comand O comando a ser executado.
 * \param terminal O terminal onde o comando será executado.
 * \return O resultado da execução do comando.
 */
int comandSwitcher(Comand *comand, Terminal *terminal);

/*!
 * \brief Inicializa um terminal.
 * \return O ponteiro para o terminal inicializado.
 */
Terminal *terminalInit();

/*!
 * \brief Executa o próximo loop do terminal.
 * \param terminal O terminal onde o próximo loop será executado.
 * \return O resultado da execução do próximo loop.
 */
int terminalNextLoop(Terminal *terminal);

/*!
 * \brief Desaloca um terminal.
 * \param terminal O terminal a ser desalocado.
 */
void desalocarTerminal(Terminal *terminal);

#endif //UNTITLED2_TERMINAL_H
