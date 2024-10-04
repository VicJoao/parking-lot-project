/*!
 * \file dataHora.h
 * \brief Declaração das estruturas e funções relacionadas a data e hora.
 * \authores
 * \date 21/03/2024
 */

#ifndef UNTITLED2_DATAHORA_H
#define UNTITLED2_DATAHORA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZERO 0
#define ONE 1
#define DIAS_FEV 28
#define MAX_DIAS_FEV 28
#define MES_TAM_MIN 30
#define MES_TAM_MAX 31
#define FOUR 4
#define NINE 9
#define MIN_HORA 60
#define HORAS_DIA 24
#define DIAS_ANO 365
#define MAX_HORA 59
#define MAX_DIA 23
#define ELEVEN 11
#define MAX_MES 12
#define DATA_SIZE 17
#define SIX 6
#define TWO 2


/*!
 * \struct DataHora
 * \brief Estrutura que representa uma data e hora.
 */
typedef struct DataHora {
    int dia; //!< Dia
    int mes; //!< Mês
    int ano; //!< Ano
    int hora; //!< Hora
    int minuto; //!< Minuto
} DataHora; //!< Data e hora com dia, mês, ano, hora e minuto

/*!
 * \brief Inicializa uma data e hora.
 * \param dia Dia.
 * \param mes Mês.
 * \param ano Ano.
 * \param hora Hora.
 * \param minuto Minuto.
 * \return A data e hora inicializada.
 */
DataHora dataHoraInit(int dia, int mes, int ano, int hora, int minuto);

/*!
 * \brief Converte uma string para uma data e hora.
 * \param dataHora String contendo a data e hora no formato "dd/mm/yyyy hh:mm".
 * \return A data e hora convertida.
 */
DataHora dataHoraConversor(char *dataHora);

/*!
 * \brief Converte uma data e hora para minutos.
 * \param dataHora A data e hora a ser convertida.
 * \return Os minutos correspondentes à data e hora.
 */
int dataHoraParaMinutos(DataHora dataHora);

/*!
 * \brief Converte uma data e hora para string.
 * \param dataHora A data e hora a ser convertida.
 * \return A string representando a data e hora no formato "dd/mm/yyyy hh:mm".
 */
char *dataHoraToString(DataHora dataHora);

/*!
 * \brief Converte uma data e hora para dias.
 * \param dataHora A data e hora a ser convertida.
 * \return O número de dias correspondentes à data e hora.
 */
int dataEmDias(DataHora dataHora);

/*!
 * \brief Converte uma data e hora para string sem a data.
 * \param dataHora A data e hora a ser convertida.
 * \return A string representando a hora no formato "hh:mm".
 */
char *dataHoraToStringSemData(DataHora dataHora);

/*!
 * \brief Converte uma data e hora para string sem a hora.
 * \param dataHora A data e hora a ser convertida.
 * \return A string representando a data no formato "dd/mm/yyyy".
 */
char *dataHoraToStringSemHora(DataHora dataHora);

/*!
 * \brief Verifica se uma data e hora é válida.
 * \param dataHora A data e hora a ser verificada.
 * \return 1 se for válida, 0 caso contrário.
 */
int isDataHoraValida(DataHora dataHora);

#endif //UNTITLED2_DATAHORA_H
