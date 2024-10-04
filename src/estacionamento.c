/*!
 * \file estacionamento.c
 * \brief Implementação das funções relacionadas ao estacionamento.
 * \authores
 * \date 20/03/2024
 */


#include "estacionamento.h"

//!<  Inicializa um estacionamento
Estacionamento estacionamentoInit(char *nome, int capacidade, float valorMinuto, float valorHora, float valorDia) {
    Estacionamento est;
    est.nome = strdup(nome); //!<  Aloca e copia o nome do estacionamento
    est.capacidade = capacidade; //!<  Define a capacidade do estacionamento
    est.valorMinuto = valorMinuto; //!<  Define o valor por minuto
    est.valorHora = valorHora; //!<  Define o valor por hora
    est.valorDia = valorDia; //!<  Define o valor por dia
    est.ocupacao = ZERO; //!<  Inicializa a ocupação como ZERO
    est.carros = NULL; //!<  Inicializa a lista de carros como NULL
    return est;
}

//!<  Adiciona um carro ao estacionamento
void adicionarCarro(char *matricula, Estacionamento *estacionamento, DataHora dataHoraEntrada) {
    Carro *carro = (Carro *) malloc(sizeof(Carro)); //!<  Aloca memória para o carro
    carro->matricula = strdup(matricula); //!<  Aloca e copia a matrícula do carro
    carro->dataHoraEntrada = dataHoraEntrada; //!<  Define a dataHoraEntrada do carro
    carro->dataHoraSaida = (DataHora) {ZERO}; //!<  Inicializa a dataHoraSaida com ZERO
    carro->Historico = ZERO; //!<  Inicializa como atual
    carro->prox = NULL; //!<  Inicializa o próximo como NULL

    //!<  Verifica se o estacionamento está cheio
    if (estacionamento->ocupacao >= estacionamento->capacidade) {
        printf("Estacionamento cheio!\n"); //!<  Exibe mensagem de erro
        return;
    }

    //!<  Caso a lista de carros do estacionamento esteja vazia
    if (estacionamento->carros == NULL) {
        estacionamento->carros = carro;
    } else {
        //!<  Percorre a lista até o último elemento
        Carro *temp = estacionamento->carros;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        //!<  Adiciona o novo carro após o último elemento
        temp->prox = carro;
    }

    estacionamento->ocupacao++;
}

//!<  Remove um carro do estacionamento
void saidaCarro(Estacionamento *estacionamento, char *matricula, DataHora dataHoraSaida) {
    Carro *atual = estacionamento->carros;

    //!<  Procurando o carro com a matrícula fornecida
    while (atual != NULL) {
        if (strcmp(atual->matricula, matricula) == ZERO && atual->Historico == ZERO) {
            //!<  Registrando a hora de saída do carro
            atual->dataHoraSaida = dataHoraSaida;
            atual->Historico = ONE; //!<  Adicionando ao histórico
            estacionamento->ocupacao--;
            return;
        }
        atual = atual->prox;
    }

    //!<  Se o carro não for encontrado, exibir mensagem
    printf("invalid vehicle exit.\n");

}

//!<  Calcula o preço de um carro
float calcularPreco(int minutosEntrada, int minutosSaida, Estacionamento *estacionamento) {
    int tempo = minutosSaida - minutosEntrada; //!<  Calcula o tempo de permanência
    float precoTotal = ZERO; //!<  Inicializa o preço total
    int flag = ZERO;
    if (tempo %TAM_MIN != ZERO){
        flag = ONE;
    }
    tempo = (int) tempo /TAM_MIN; //!<  tempo = intervalo de 15 minutos
    //!<  Calcula o preço total se tmepoo inferior a 1 hora
    if (tempo<TAM_HORA){
       return (tempo+flag)*estacionamento->valorMinuto;
    }
    if (((tempo-(tempo%TAM_HORA))%TAM_DIA == ZERO && tempo %TAM_HORA != ZERO) ||(( tempo)%TAM_DIA == ZERO && tempo+flag %TAM_HORA != ZERO)){
        precoTotal += ((tempo%TAM_DIA)+flag %TAM_HORA) * estacionamento->valorMinuto;
    } else {
        tempo +=  flag;
        precoTotal += estacionamento->valorMinuto*TAM_HORA; //!<  Adiciona o valor dos primeiros TAM_HORA intervalos de 15 min
        tempo -= TAM_HORA; //!<  Diminui o tempo restante
        precoTotal += (tempo % TAM_DIA) * estacionamento->valorHora;     //!<  Adiciona o valor das horas restantes
    }

    if (precoTotal> estacionamento->valorDia){
        precoTotal = estacionamento->valorDia;
    }
    tempo = (int) tempo / TAM_DIA; //!<  Calcula o número de dias
    precoTotal += tempo * estacionamento->valorDia; //!<  Adiciona o valor dos dias
    return precoTotal;
}





