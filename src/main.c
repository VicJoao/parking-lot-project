/*!
 * \file main.c
 * \brief Implementação do programa principal.
 * \authores
 * \date 19/03/2024
 */

#include "terminal.h"
#define TRUE 0

/*!
 * \brief Função principal do programa.
 * \return Retorna 0 em caso de sucesso.
 */
int main() {
    Terminal *terminal = terminalInit(); //!< Inicializa um terminal
    int resp = TRUE; //!< Resposta do loop
    while (resp == TRUE) {
        resp = terminalNextLoop(terminal); //!< Executa o próximo loop do terminal
    }
    free(terminal); //!< Desaloca o terminal
    return TRUE; //!< Retorna 0 em caso de sucesso
}
