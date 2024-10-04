/*!
 * \file dataHora.c
 * \brief Implementação das funções relacionadas a data e hora.
 * \authores
 * \date 21/03/2024
 */

#include "dataHora.h"

//!<  Função para inicializar uma data e hora
DataHora dataHoraInit(int dia, int mes, int ano, int hora, int minuto) {
    DataHora dataHora; //!<  Cria uma struct DataHora
    dataHora.dia = dia; //!<  Inicializa o dia
    dataHora.mes = mes; //!<  Inicializa o mês
    dataHora.ano = ano; //!<  Inicializa o ano
    dataHora.hora = hora; //!<  Inicializa a hora
    dataHora.minuto = minuto; //!<  Inicializa o minuto
    return dataHora; //!<  Retorna a struct inicializada
}

DataHora dataHoraConversor(char *dataHoraStr) {
    DataHora dh;
    memset(&dh, ZERO, sizeof(DataHora)); // Inicializa a estrutura com zeros

    const char delimiters[] = "- :";
    char *token;
    char *saveptr; // Variável necessária para a função strtok_r

    char dataHoraCopy[strlen(dataHoraStr) + ONE];
    strcpy(dataHoraCopy, dataHoraStr);

    token = strtok_r(dataHoraCopy, delimiters, &saveptr);
    if (token == NULL) return dh;
    dh.dia = atoi(token);

    token = strtok_r(NULL, delimiters, &saveptr);
    if (token == NULL) return dh;
    dh.mes = atoi(token);

    if (dh.mes == TWO && dh.dia == MAX_DIAS_FEV) dh.dia = DIAS_FEV;

    token = strtok_r(NULL, delimiters, &saveptr);
    if (token == NULL) return dh;
    dh.ano = atoi(token);

    token = strtok_r(NULL, delimiters, &saveptr);
    if (token == NULL) return dh;
    dh.hora = atoi(token);

    token = strtok_r(NULL, delimiters, &saveptr);
    if (token == NULL) return dh;
    dh.minuto = atoi(token);

    return dh;
}


//!<  Função para converter uma data e hora para string
char *dataHoraToString(DataHora dataHora) {
    char *str = (char *) malloc( DATA_SIZE * sizeof(char)); //!<  "dd-mm-aa hh:mm\0"
    if (str == NULL) {
        printf("Erro ao alocar memória.\n"); //!<  Imprime uma mensagem de erro caso a alocação falhe
        exit(ONE);
    }
    sprintf(str, "%02d-%02d-%02d %02d:%02d", dataHora.dia, dataHora.mes, dataHora.ano, dataHora.hora,
            dataHora.minuto); //!<  Formata a string
    return str;
}

char *dataHoraToStringSemData(DataHora dataHora) {
    char *str = (char *) malloc(SIX * sizeof(char)); //!<  "hh:mm\0"
    if (str == NULL) {
        printf("Erro ao alocar memória.\n"); //!<  Imprime uma mensagem de erro caso a alocação falhe
        exit(ONE);
    }
    sprintf(str, "%02d:%02d", dataHora.hora, dataHora.minuto); //!<  Formata a string
    return str;
}

//!<  Função para converter uma data e hora para string sem a hora
char *dataHoraToStringSemHora(DataHora dataHora) {
    char *result = malloc(ELEVEN * sizeof(char)); //!<  Espaço suficiente para "DD-MM-AAAA\0"
    if (result != NULL) {
        sprintf(result, "%02d-%02d-%04d", dataHora.dia, dataHora.mes, dataHora.ano); //!<  Formata a string
    }
    return result;
}

//!<  Função para retornar a quantidade de dias em um mês
int diasNoMes(int mes) {
    switch (mes) {
        case TWO:
            return DIAS_FEV;
        case FOUR:
        case SIX:
        case NINE:
        case ELEVEN:
            return MES_TAM_MIN;
        default:
            return MES_TAM_MAX;
    }
}

//!<  Função para converter uma data e hora para dias
int dataEmDias(DataHora dataHora) {
    int dias = ZERO; //!<  Inicializa a variável dias

    for (int ano = ONE; ano < dataHora.ano; ano++) {
        dias += DIAS_ANO; //!<  Adiciona 365 dias para cada ano
    }
    for (int mes = ONE; mes < dataHora.mes; mes++) {
        dias += diasNoMes(mes); //!<  Adiciona a quantidade de dias em cada mês
    }
    dias += dataHora.dia - ONE; //!<  Adiciona a quantidade de dias no mês atual
    return dias;
}

//!<  Função para converter uma data e hora para minutos
int dataHoraParaMinutos(DataHora dataHora) {
    int minutos = ZERO;

    //!<  Adiciona minutos dos dias completos
    minutos += (dataHora.dia - ONE) * HORAS_DIA * MIN_HORA;

    //!<  Adiciona minutos das horas completas
    minutos += dataHora.hora * MIN_HORA;

    //!<  Adiciona minutos
    minutos += dataHora.minuto;

    //!<  Adiciona minutos dos meses completos

    for (int mes = ONE; mes < dataHora.mes; mes++) {
        minutos += diasNoMes(mes) * HORAS_DIA * MIN_HORA;
    }

    //!<  Adiciona minutos dos anos completos
    for (int ano = ONE; ano < dataHora.ano; ano++) {
        minutos += DIAS_ANO * HORAS_DIA * MIN_HORA; //!<  Não considera anos bissextos
    }

    return minutos;
}


//!< Função para verificar se uma data e hora é inválida
int isDataHoraValida(DataHora dataHora) {
    //!< Verifica se os valores de data e hora são inválidos
    if (dataHora.ano < ZERO || dataHora.mes < ONE || dataHora.mes > MAX_MES ||
        dataHora.hora < ZERO || dataHora.hora > MAX_DIA ||
        dataHora.minuto < ZERO || dataHora.minuto > MAX_HORA) {
        return ZERO; // Retorna ONE para indicar que a data e hora são inválidas
    }
    if (dataHora.dia> diasNoMes(dataHora.mes)) return ZERO; // Retorna 0 para indicar que a data e hora são inválidas
    //!< Verifica se o dia é inválido para o mês
    // Aqui você pode adicionar a lógica para verificar se o dia é inválido de acordo com o mês e o ano.
    // Como sua implementação original não inclui essa lógica, essa parte precisa ser ajustada.
    // No momento, estamos apenas retornando ZERO para indicar que a data e hora são válidas, mas isso não está correto.

    return ONE; // Retorna ZERO para indicar que a data e hora são válidas
}

