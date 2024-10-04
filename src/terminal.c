/*!
 * \file dterminal.c
 * \brief Implementação das funções relacionadas ao terminal.
 * \author
 * \date 20/03/2024
 */

#include "terminal.h"

//!<  Função para inicializar um estacionamento
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//!<  Função auxiliar para verificar o tamanho da matrícula
int isValidLength(const char *matricula) {
    return strlen(matricula) == Max_MATRICULA;
}

//!<  Função auxiliar para remover os hífens da matrícula
void removeHyphens(char *matricula) {
    char *src = matricula, *dst = matricula;
    while (*src) {
        if (*src != '-') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

//!<  Função auxiliar para verificar se a matrícula contém pares de caracteres válidos
int isValidCharPairs(const char *matricula) {
    int letras = ZERO, digitos = ZERO;

    for (int i = ZERO; i < MAX_PAIR; i += PAIR) {
        if (isupper(matricula[i])) {
            if (!isupper(matricula[i + ONE])) {
                return ZERO;
            }
            letras++;
        } else if (isdigit(matricula[i])) {
            if (!isdigit(matricula[i + ONE])) {
                return ZERO;
            }
            digitos++;
        } else {
            return ZERO; // Caractere inválido
        }
    }

    return letras > ZERO && digitos > ZERO && letras <= TRIO && digitos <= TRIO;
}

//!<  Função para verificar a validade de uma matrícula
int checkMatricula(const char *matricula) {
    if (!isValidLength(matricula)) {
        return ZERO;
    }

    char *matriculaCopy = strdup(matricula);
    if (matriculaCopy == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    removeHyphens(matriculaCopy);

    int isValid = isValidCharPairs(matriculaCopy);

    free(matriculaCopy);

    return isValid;
}


//!<  Função para inicializar um estacionamento
Comand *comandInit(char *comand) {
    Comand *comand1 = (Comand *) malloc(sizeof(Comand)); //!<  Aloca memória para a estrutura Comand
    if (comand1 == NULL) {
        //!<  Falha na alocação de memória
        return NULL;
    }

    comand1->cmd = comand[ZERO];
    //!<  Verifica se o comando é 'q' (quit)
    if (comand1->cmd == 'q') {
        comand1->arg = NULL;
        return comand1;
    }

    char *space_ptr = strchr(comand, ' '); //!<  Procura o primeiro espaço na string
    if (space_ptr == NULL) {
        //!<  Não há argumento após o comando
        comand1->arg = NULL;
    } else {
        //!<  Há argumento após o comando
        char *arg = space_ptr + ONE; //!<  Avança para o próximo caractere após o espaço
        int size = strlen(arg); //!<  Tamanho do argumento
        //!<  Aloca memória para o argumento
        if (size == ZERO) {
            comand1->arg = NULL; //!<  String vazia
        } else {
            comand1->arg = (char *) malloc(sizeof(char) * (size + ONE)); //!<  +1 para o caractere nulo
            //!<  Verifica se a alocação de memória foi bem-sucedida
            if (comand1->arg == NULL) {
                free(comand1);
                return NULL;
            }
            strcpy(comand1->arg, arg);
        }
    }

    return comand1;
}

//!<  Função para inicializar um estacionamento
void printEstacionamentos(Terminal *terminal) {
    for (int i = ZERO; i < terminal->estacionamentosSize; ++i) {
        printf("%s %d %d\n", terminal->estacionamentos[i].nome, terminal->estacionamentos[i].capacidade,
               terminal->estacionamentos[i].capacidade - terminal->estacionamentos[i].ocupacao);
    }
}

//!< extrai o nome entre aspas duplas
char *extrairNome(char *token) {
    int startPos = -ONE;
    int endPos = -ONE;

    //!<  Encontra a primeira aspa dupla
    for (int i = ZERO; i < (int) strlen(token); i++) {
        if (token[i] == '"') {
            startPos = i + ONE;
            break;
        }
    }

    //!<  Encontra a próxima aspa dupla a partir da posição encontrada anteriormente
    for (int i = startPos; i < (int) strlen(token); i++) {
        if (token[i] == '"') {
            endPos = i;
            break;
        }
    }

    if (startPos != -ONE && endPos != -ONE) {
        char *nome = (char *) malloc(endPos - startPos + ONE); //!<  Aloca memória para o texto entre as aspas
        if (nome == NULL) {
            perror("Falha na alocação de memória");
            exit(EXIT_FAILURE);
        }
        strncpy(nome, token + startPos, endPos - startPos); //!<  Copia o valor entre as aspas para a variável nome
        nome[endPos - startPos] = '\0'; //!<  Adiciona o terminador de string

        //!<  Remove o valor entre as aspas do token original
        memmove(token + startPos - ONE, token + endPos + ONE, strlen(token) - endPos);

        return nome;
    } else {
        return NULL; //!<  Se não encontrar aspas, retorna NULL
    }
}

//!< Função auxiliar para verificar se o estacionamento já existe
int estacionamentoExiste(const char *nomeParque, const Terminal *terminal) {
    for (int i = ZERO; i < terminal->estacionamentosSize; ++i) {
        if (strcmp(terminal->estacionamentos[i].nome, nomeParque) == ZERO) {
            printf("%s: parking already exists.\n", nomeParque);
            return ONE;
        }
    }
    return ZERO;
}

//!< Função auxiliar para verificar a capacidade do estacionamento
int capacidadeValida(int capacidade) {
    if (capacidade <= ZERO) {
        printf("%d: invalid capacity.\n", capacidade);
        return ZERO;
    }
    return ONE;
}

//!< Função auxiliar para verificar se os custos são válidos
int custosValidos(float valor15, float valor15Apos1Hora, float valorMaxDiario) {
    if (valor15 <= ZERO || valor15Apos1Hora <= ZERO || valorMaxDiario <= ZERO ||
        valor15Apos1Hora <= valor15 || valorMaxDiario <= valor15Apos1Hora) {
        printf("invalid cost.\n");
        return ZERO;
    }
    return ONE;
}

//!< Função auxiliar para verificar o limite de estacionamentos
int limiteEstacionamentos(const Terminal *terminal) {
    if (terminal->estacionamentosSize >= MAX_ESTACIONAMENTOS) {
        printf("too many parks.\n");
        return ONE;
    }
    return ZERO;
}

//!< Função auxiliar para criar um estacionamento
void criarEstacionamento(const char *nomeParque, int capacidade, float valor15, float valor15Apos1Hora,
                         float valorMaxDiario, Terminal *terminal) {
    Estacionamento estacionamento = estacionamentoInit((char *) nomeParque, capacidade, valor15, valor15Apos1Hora,
                                                       valorMaxDiario);
    //!< Adiciona o estacionamento ao vetor de estacionamentos
    terminal->estacionamentos[terminal->estacionamentosSize] = estacionamento;
    terminal->estacionamentosSize++;
}

//!< Função principal para criar um estacionamento
void createEstacionamento(char *arg, Terminal *terminal) {
    //!< Se não há argumentos, imprime os estacionamentos existentes
    if (arg == NULL) {
        printEstacionamentos(terminal);
        return;
    }

    char *nomeParque;
    char *token;
    //!< Verifica se o argumento começa com aspas
    if (arg[ZERO] == '"') {
        nomeParque = extrairNome(arg);
        token = strtok(arg, DELIMITTERS);

    } else {
        token = strtok(arg, DELIMITTERS);
        nomeParque = token;
        token = strtok(NULL, DELIMITTERS);
    }

    int capacidade = atoi(token);
    token = strtok(NULL, DELIMITTERS);
    float valor15 = atof(token);
    token = strtok(NULL, DELIMITTERS);
    float valor15Apos1Hora = atof(token);
    token = strtok(NULL, DELIMITTERS);
    float valorMaxDiario = atof(token);

    //!< Verificações separadas
    if (estacionamentoExiste(nomeParque, terminal) ||
        !capacidadeValida(capacidade) ||
        !custosValidos(valor15, valor15Apos1Hora, valorMaxDiario) ||
        limiteEstacionamentos(terminal)) {
        return;
    }

    //!< Cria o estacionamento
    criarEstacionamento(nomeParque, capacidade, valor15, valor15Apos1Hora, valorMaxDiario, terminal);
}


//!< Função auxiliar para verificar se o nome do parque está entre aspas
char *extrairNomeParque(char *arg, char **matricula, char **data, char **hora) {
    if (arg[ZERO] == '"') {
        char *nome = extrairNome(arg);
        char *token = strtok(arg, DELIMITTERS);
        *matricula = token;
        *data = strtok(NULL, DELIMITTERS);
        *hora = strtok(NULL, DELIMITTERS);
        return nome;
    }
    return NULL;
}

//!< Função auxiliar para obter os tokens de entrada
void obterTokens(char *arg, char **nomeParque, char **matricula, char **data, char **hora) {
    const char delimiters[] = DELIMITTERS;
    char *token = strtok(arg, delimiters);
    *nomeParque = token;
    token = strtok(NULL, delimiters);
    *matricula = token;
    token = strtok(NULL, delimiters);
    *data = token;
    token = strtok(NULL, delimiters);
    *hora = token;
}

//!< Função auxiliar para verificar a validade da matrícula
int verificarMatricula(char *matricula) {
    int responseM = checkMatricula(matricula);
    if (responseM == ZERO) {
        printf("%s: invalid licence plate.\n", matricula);
    }
    return responseM;
}

//!< Função auxiliar para transformar a data e hora em um objeto DataHora
DataHora obterDataHora(char *data, char *hora) {
    char *dataHora = (char *) malloc(strlen(data) + strlen(hora) + PAIR);
    strcpy(dataHora, data);
    strcat(dataHora, " ");
    strcat(dataHora, hora);
    DataHora carroDataHora = dataHoraConversor(dataHora);
    return carroDataHora;
}

//!< Função auxiliar para verificar se a data do carro é posterior à data do terminal
int verificarDataPosterior(DataHora carroDataHora, DataHora terminalDataHora) {
    int dataCarro = dataHoraParaMinutos(carroDataHora);
    int dataTerminal = dataHoraParaMinutos(terminalDataHora);
    if (dataCarro < dataTerminal) {
        printf("invalid date.\n");
        return ZERO;
    }
    if (!isDataHoraValida(carroDataHora)) {
        printf("invalid date.\n");
        return ZERO;
    }
    return ONE;
}

//!< Função auxiliar para procurar pelo estacionamento correspondente ao nome fornecido
int encontrarEstacionamento(Terminal *terminal, char *nomeParque) {
    for (int i = ZERO; i < terminal->estacionamentosSize; ++i) {
        if (strcmp(terminal->estacionamentos[i].nome, nomeParque) == ZERO) {
            return i;
        }
    }
    printf("%s: no such parking.\n", nomeParque);
    return -ONE;
}

//!< Função auxiliar para verificar se o estacionamento está cheio
int verificarEstacionamentoCheio(Estacionamento *estacionamento) {
    if (estacionamento->ocupacao >= estacionamento->capacidade) {
        printf("%s: parking is full.\n", estacionamento->nome);
        return ONE;
    }
    return ZERO;
}

int verificaCarroEstacionado(Terminal *terminal, char *matricula) {
    for (int i = ZERO; i < terminal->estacionamentosSize; ++i) {
        Carro *carro = terminal->estacionamentos[i].carros;
        while (carro != NULL) {
            if (strcmp(carro->matricula, matricula) == ZERO && carro->Historico == ZERO) {
                printf("%s: invalid vehicle entry.\n", matricula);
                return ZERO;
            }
            carro = carro->prox;
        }
    }
    return ONE;
}

//!< Função auxiliar para adicionar um carro ao estacionamento
void adicionarCarroAoEstacionamento(char *matricula, Estacionamento *estacionamento, DataHora carroDataHora) {
    adicionarCarro(matricula, estacionamento, carroDataHora);
    printf("%s %d\n", estacionamento->nome,
           estacionamento->capacidade - estacionamento->ocupacao);
}

//!< Função principal para a entrada de carros no terminal
void entradaDeCarro(char *arg, Terminal *terminal) {
    char *nomeParque = NULL;
    char *matricula = NULL;
    char *data = NULL;
    char *hora = NULL;

    nomeParque = extrairNomeParque(arg, &matricula, &data, &hora);
    if (!nomeParque) {
        obterTokens(arg, &nomeParque, &matricula, &data, &hora);
    }
    DataHora carroDataHora = obterDataHora(data, hora);

    if (verificaCarroEstacionado(terminal, matricula) == ZERO || verificarMatricula(matricula) == ZERO ||
        !verificarDataPosterior(carroDataHora, terminal->dataHora)) {
        return;
    }

    int p = encontrarEstacionamento(terminal, nomeParque);
    if (p == -ONE) {
        return;
    }

    if (verificarEstacionamentoCheio(&terminal->estacionamentos[p])) {
        return;
    }
    terminal->dataHora = carroDataHora;
    adicionarCarroAoEstacionamento(matricula, &terminal->estacionamentos[p], carroDataHora);
}


//!< Função auxiliar para encontrar o carro no estacionamento e calcular o valor a pagar para a saída de carro
void processarSaidaCarro(Estacionamento *parque, char *matricula, DataHora carroDataHora) {
    Carro *carro = parque->carros;
    while (carro != NULL) {
        if (strcmp(carro->matricula, matricula) == ZERO && carro->Historico == ZERO) {
            float valor = calcularPreco(dataHoraParaMinutos(carro->dataHoraEntrada), dataHoraParaMinutos(carroDataHora),
                                        parque);
            printf("%s %s %s %.2f\n", carro->matricula, dataHoraToString(carro->dataHoraEntrada),
                   dataHoraToString(carroDataHora), valor);
            //!<  Remove o carro do estacionamento
            saidaCarro(parque, matricula, carroDataHora);
            return;
        }
        carro = carro->prox;
    }
}

//!< Função auxiliar para encontrar o estacionamento correspondente ao nome fornecido para a saída de carro
Estacionamento *encontrarEstacionamentoSaida(Terminal *terminal, char *nomeParque) {
    for (int i = ZERO; i < terminal->estacionamentosSize; ++i) {
        if (strcmp(terminal->estacionamentos[i].nome, nomeParque) == ZERO) {
            return &terminal->estacionamentos[i];
        }
    }
    printf("%s: no such parking.\n", nomeParque);
    return NULL;
}

//!< Função auxiliar para verificar se o carro está estacionado
int verificarCarroEstacionado(Estacionamento *parque, char *matricula) {
    Carro *carro = parque->carros;
    while (carro != NULL) {
        if (strcmp(carro->matricula, matricula) == ZERO && carro->Historico == ZERO) {
            return ONE;
        }
        carro = carro->prox;
    }
    printf("%s: invalid vehicle exit.\n", matricula);
    return ZERO;
}

//!< Função principal para a saída de carros do terminal
void saidaDeCarro(char *arg, Terminal *terminal) {
    char *nomeParque = NULL;
    char *matricula = NULL;
    char *data = NULL;
    char *hora = NULL;

    nomeParque = extrairNomeParque(arg, &matricula, &data, &hora);
    if (!nomeParque) {
        obterTokens(arg, &nomeParque, &matricula, &data, &hora);
    }

    int responseM = verificarMatricula(matricula);
    if (responseM == ZERO) {
        return;
    }


    DataHora carroDataHora = obterDataHora(data, hora);
    if (!verificarDataPosterior(carroDataHora, terminal->dataHora)) {
        return;
    }

    Estacionamento *parque = encontrarEstacionamentoSaida(terminal, nomeParque);
    if (parque == NULL) {
        return;
    }

    if (!verificarCarroEstacionado(parque, matricula)) {
        return;
    }

    processarSaidaCarro(parque, matricula, carroDataHora);
}


//!<  Função para comparar dois estacionamentos por nome
int compararEstacionamentos(const void *a, const void *b) {
    Estacionamento *est1 = (Estacionamento *) a;
    Estacionamento *est2 = (Estacionamento *) b;
    return strcmp(est1->nome, est2->nome);
}

//!< Função auxiliar para ordenar os estacionamentos por ordem alfabética
void ordenarEstacionamentos(Terminal *terminal) {
    for (int i = ONE; i < terminal->estacionamentosSize; ++i) {
        Estacionamento key = terminal->estacionamentos[i];
        int j = i - ONE;
        while (j >= ZERO && compararEstacionamentos(&terminal->estacionamentos[j], &key) > ZERO) {
            terminal->estacionamentos[j + ONE] = terminal->estacionamentos[j];
            j = j - ONE;
        }
        terminal->estacionamentos[j + ONE] = key;
    }
}

//!< Função auxiliar para listar os carros de um estacionamento
void listarCarros(Estacionamento *estacionamentos, int estacionamentosSize, char *matricula) {
    int flag = ZERO;
    for (int i = ZERO; i < estacionamentosSize; ++i) {
        Carro *carro = estacionamentos[i].carros;
        while (carro != NULL) {
            if (strcmp(carro->matricula, matricula) == ZERO) {
                if (carro->Historico == ONE) {
                    printf("%s %s %s\n", estacionamentos[i].nome,
                           dataHoraToString(carro->dataHoraEntrada),
                           dataHoraToString(carro->dataHoraSaida));
                    flag = ONE;
                } else {
                    printf("%s %s\n", estacionamentos[i].nome,
                           dataHoraToString(carro->dataHoraEntrada));
                    flag = ONE;
                }
            }
            carro = carro->prox;
        }
    }
    if (flag == ZERO) {
        printf("%s: no entries found in any parking.\n", matricula);
    }
}

//!< Função principal para listar os carros de um estacionamento
void listaDeParques(char *arg, Terminal *terminal) {
    ordenarEstacionamentos(terminal);

    const char delimiters[] = DELIMITTERS;
    char *token = strtok(arg, delimiters);
    char *matricula = token;

    int responseM = checkMatricula(matricula);
    if (responseM == ZERO) {
        printf("%s: invalid licence plate.\n", matricula);
        return;
    }

    listarCarros(terminal->estacionamentos, terminal->estacionamentosSize, matricula);
}


//!<  Função auxiliar para trocar dois carros de posição
void trocarCarros(Carro *a, Carro *b) {
    Carro temp = *a;
    *a = *b;
    *b = temp;
}

//!<  Função auxiliar para particionar o array de carros
int particionar(Carro *carros, int inicio, int fim) {
    int pivo = dataHoraParaMinutos(carros[fim].dataHoraSaida);
    int i = inicio - ONE;

    for (int j = inicio; j < fim; ++j) {
        if (dataHoraParaMinutos(carros[j].dataHoraSaida) <= pivo) {
            ++i;
            trocarCarros(&carros[i], &carros[j]);
        }
    }
    trocarCarros(&carros[i + ONE], &carros[fim]);
    return i + ONE;
}

//!<  Função Quicksort para ordenar o array de carros pela data de saída
void quicksort(Carro *carros, int inicio, int fim) {
    if (inicio < fim) {
        int pi = particionar(carros, inicio, fim);
        quicksort(carros, inicio, pi - ONE);
        quicksort(carros, pi + ONE, fim);
    }
}

//!< Função para checar se a data é válida
int checarDataValidaComData(Estacionamento *estacionamento, DataHora data) {
    int maiorData = ZERO;
    Carro *temp = estacionamento->carros;
    while (temp != NULL) {
        if (dataHoraParaMinutos(temp->dataHoraSaida) > maiorData) {
            maiorData = dataHoraParaMinutos(temp->dataHoraSaida);
        }
        temp = temp->prox;
    }
    if (dataHoraParaMinutos(data) > maiorData) {
        printf("Data inválida.\n");
        return ZERO;
    }
    return ONE;
}

//!< Função para contar carros no histórico para uma data específica
int contarCarrosHistoricoComData(Estacionamento *estacionamento, DataHora data) {
    int tamanho = ZERO;
    for (Carro *carro = estacionamento->carros; carro != NULL; carro = carro->prox) {
        if (carro->Historico == ONE && dataEmDias(carro->dataHoraSaida) == dataEmDias(data)) {
            tamanho++;
        }
    }
    return tamanho;
}

//!< Função para copiar carros no histórico para uma data específica
Carro *copiarCarrosHistoricoComData(Estacionamento *estacionamento, DataHora data, int tamanho) {
    Carro *copiaCarros = malloc(tamanho * sizeof(Carro));
    int index = ZERO;
    for (Carro *carro = estacionamento->carros; carro != NULL; carro = carro->prox) {
        if (carro->Historico == ONE && dataEmDias(carro->dataHoraSaida) == dataEmDias(data)) {
            copiaCarros[index++] = *carro;
        }
    }
    return copiaCarros;
}

//!< Função principal para imprimir a faturação de um estacionamento para uma data específica
void printFacturacaoDataComData(Estacionamento *estacionamento, DataHora data) {
    if (!checarDataValidaComData(estacionamento, data)) {
        return;
    }

    int tamanho = contarCarrosHistoricoComData(estacionamento, data);
    if (tamanho == ZERO) {
        return;
    }

    Carro *copiaCarros = copiarCarrosHistoricoComData(estacionamento, data, tamanho);

    quicksort(copiaCarros, ZERO, tamanho - ONE);

    for (int i = ZERO; i < tamanho; ++i) {
        Carro *carro = &copiaCarros[i];
        float valor = calcularPreco(dataHoraParaMinutos(carro->dataHoraEntrada),
                                    dataHoraParaMinutos(carro->dataHoraSaida), estacionamento);
        printf("%s %s %.2f\n", carro->matricula, dataHoraToStringSemData(carro->dataHoraSaida), valor);
    }

    free(copiaCarros);
}


//!< Função para contar carros no histórico
int contarCarrosHistorico(Estacionamento *estacionamento) {
    int tamanho = ZERO;
    for (Carro *carro = estacionamento->carros; carro != NULL; carro = carro->prox) {
        if (carro->Historico == ONE) {
            tamanho++;
        }
    }
    return tamanho;
}

//!< Função para criar uma cópia dos carros no histórico
Carro *copiarCarrosHistorico(Estacionamento *estacionamento, int tamanho) {
    Carro *copiaCarros = malloc(tamanho * sizeof(Carro));
    int index = ZERO;
    for (Carro *carro = estacionamento->carros; carro != NULL; carro = carro->prox) {
        if (carro->Historico == ONE) {
            copiaCarros[index++] = *carro;
        }
    }
    return copiaCarros;
}

//!< Função para liberar a memória alocada para os carros copiados
void liberarCarrosCopiados(Carro *copiaCarros) {
    free(copiaCarros);
}

//!< Função para ordenar os carros pelo horário de saída
void ordenarCarrosPorHoraDeSaida(Carro *copiaCarros, int tamanho) {
    quicksort(copiaCarros, ZERO, tamanho - ONE);
}

//!< Função para imprimir a faturação agrupada por data
void imprimirFaturacaoPorData(Carro *copiaCarros, int tamanho, Estacionamento *estacionamento) {
    DataHora dataAtual = copiaCarros[ZERO].dataHoraSaida;
    float totalPorData = ZERO;
    for (int i = ZERO; i < tamanho; ++i) {
        Carro *carro = &copiaCarros[i];
        if (dataEmDias(carro->dataHoraSaida) != dataEmDias(dataAtual)) {
            printf("%s %.2f\n", dataHoraToStringSemHora(dataAtual), totalPorData);
            totalPorData = ZERO;
            dataAtual = carro->dataHoraSaida;
        }
        totalPorData += calcularPreco(dataHoraParaMinutos(carro->dataHoraEntrada),
                                      dataHoraParaMinutos(carro->dataHoraSaida), estacionamento);
    }
    printf("%s %.2f\n", dataHoraToStringSemHora(dataAtual), totalPorData);
}

//!< Função principal para imprimir a faturação de um estacionamento sem data
void printFacturacaoSemData(Estacionamento *estacionamento) {
    int tamanho = contarCarrosHistorico(estacionamento);
    if (tamanho == ZERO) {
        printf("Não há carros no histórico.\n");
        return;
    }

    Carro *copiaCarros = copiarCarrosHistorico(estacionamento, tamanho);

    ordenarCarrosPorHoraDeSaida(copiaCarros, tamanho);

    imprimirFaturacaoPorData(copiaCarros, tamanho, estacionamento);

    liberarCarrosCopiados(copiaCarros);
}

//!<  Função para imprimir a faturação de um estacionamento
void facturacaoEstacionamento(char *arg, Terminal *terminal) {
    //!<  Consome entrada
    char *nomeParque;
    char *token;
    int i = ZERO;
    int p;
    if (arg[ZERO] == '"') {
        nomeParque = extrairNome(arg);
        i = ONE;
    }
    const char delimiters[] = DELIMITTERS;
    token = strtok(arg, delimiters);
    if (i == ZERO) {
        nomeParque = token;
        token = strtok(NULL, delimiters);
    }
    //!< checa se o parque existe
    p = encontrarEstacionamento(terminal, nomeParque);
    if (p == -ONE) {
        return;
    }
    //!< checa se pode consumir data
    if (token == NULL) {
        printFacturacaoSemData(&terminal->estacionamentos[p]);
    } else {
        //!< consome data
        char *data = token;
        token = strtok(NULL, delimiters);
        printFacturacaoDataComData(&terminal->estacionamentos[p], dataHoraConversor(data));
    }
}

//!<  Função para remover um estacionamento
void removerEstacionamento(char *arg, Terminal *terminal) {
    //!<  Entrada <nome-parque>
    //!<  Consome entrada
    char *nomeParque;
    char *token;
    int i = ZERO;
    int p;
    if (arg[ZERO] == '"') {
        nomeParque = extrairNome(arg);
        i = ONE;
    }
    const char delimiters[] = DELIMITTERS;
    token = strtok(arg, delimiters);
    if (i == ZERO) {
        nomeParque = token;
        token = strtok(NULL, delimiters);
    }
    //!< checa se o parque existe
    p = encontrarEstacionamento(terminal, nomeParque);
    if (p == -ONE) {
        return;
    }
    //!< remove o parque
    for (i = p; i < terminal->estacionamentosSize - ONE; ++i) {
        terminal->estacionamentos[i] = terminal->estacionamentos[i + ONE];
    }
    terminal->estacionamentosSize--;
    for (i = ZERO; i < terminal->estacionamentosSize; ++i) {
        printf("%s\n", terminal->estacionamentos[i].nome);
    }
}

//!<  Função para trocar dois carros de posição
int comandSwitcher(Comand *comand, Terminal *terminal) {
    //!<  comands p q s v e f r
    switch (comand->cmd) {
        case 'p':
            createEstacionamento(comand->arg, terminal);
            break;
        case 'q':
            return ZERO;
        case 's':
            saidaDeCarro(comand->arg, terminal);
            break;
        case 'v':
            listaDeParques(comand->arg, terminal);
            break;
        case 'e':
            entradaDeCarro(comand->arg, terminal);
            break;
        case 'f':
            facturacaoEstacionamento(comand->arg, terminal);
            break;
        case 'r':
            removerEstacionamento(comand->arg, terminal);
            break;
        default:
            printf("Comando inválido[%c > %s]\n", comand->cmd, comand->arg);
    }
    return ONE;
}

//!<  Função para inicializar um terminal
Terminal *terminalInit() {
    Terminal *terminal = (Terminal *) malloc(sizeof(Terminal));
    terminal->estacionamentos = (Estacionamento *) malloc(MAX_ESTACIONAMENTOS * sizeof(Estacionamento));
    terminal->estacionamentosSize = ZERO;
    terminal->comandAtual.cmd = ' ';
    terminal->comandAtual.arg = " ";
    terminal->dataHora = dataHoraInit(ZERO, ZERO, ZERO, ZERO, ZERO);
    return terminal;
}

//!<  Função para executar o loop do terminal
int terminalNextLoop(Terminal *terminal) {
    char comand[MAX_COMAND_SIZE];
    fgets(comand, sizeof(comand), stdin); //!<  Lê a linha inteira, incluindo espaços
    terminal->comandAtual = *comandInit(comand);
    int response = comandSwitcher(&terminal->comandAtual, terminal);
    if (response == ZERO) {
        return ONE; //!<  Indica que o loop deve ser encerrado
    }
    return ZERO; //!<  Indica que o loop deve continuar
}

