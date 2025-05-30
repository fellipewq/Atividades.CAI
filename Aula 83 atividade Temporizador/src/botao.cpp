#include "botao.h"

/**
 * @brief construtor da classe botao
 * 
 * @param p Numero do pino digital ao qual o botao esta conectado
 */
botao::botao(uint8_t p) : pino(p) {}

/**
 * @brief Inicializa o botao
 * 
 * Configura o pino como entrada. O modo pull-up padrao
 * 
 */
void botao::begin()
{
    pinMode(pino, INPUT_PULLUP);
    estadoAtual = digitalRead(pino);
    estadoAnterior = estadoAtual;
    estadoConfimado = estadoAtual;
        tempoInicioEstado = millis();

}

 /**
 * @brief Define o tempo de filtro (debounce) para estabilizar as leituras do botao
 * 
 * @param tempo Tempo de debounce em millissegundos
 */
void botao::configuraFiltro(unsigned long tempo)
{
    tempoFiltro = tempo;
}

/**
 * @brief Atualiza o estado interno do botao
 * 
 * Deve ser chamada frequentemente dentro do loop principal
 * Detecta mudancas de estado e aciona as flags internas de
 * eventos (pressionado, solto e mudanca de estado)
 */
void botao::update()
{
    unsigned long agora = millis();
    estadoAtual = digitalRead(pino);
    flagAlteracao = false;
    flagPressionado = false;
    flagSolto = false;

    if(estadoAtual != estadoAnterior)
        tempoUltimaMudanca = agora;

    if((agora - tempoUltimaMudanca) > tempoFiltro)
    {
        if(estadoAtual != estadoConfimado)
        {
            estadoConfimado = estadoAtual;
            duracaoEstado = agora - tempoInicioEstado;
            tempoInicioEstado = agora;
            flagAlteracao = true;

            if(!estadoAtual)//*Botao Pressionado
            {
                flagPressionado = true;
            }
            else //*Botao solto
            {
                flagSolto = true;
            }
        }
    }
estadoAnterior = estadoAtual;
}

/**
 * @brief Verifica se o botao acabou de ser pressionado
 * 
 * @return true se ouver uma transicao para o estado para o estado pressionado
 * na ultima atualizacao.
 */
bool botao::pressionado(){
    return flagPressionado;
}

/**
 * @brief Verifica se o botao acabou de ser solto
 * 
 * @return true se ouver uma transicao para o estado para o estado solto
 * na ultima atualizacao.
 */
bool botao::solto(){
    return flagSolto;
}

/**
 * @brief Verifica se houve uma mudanca de estado no botao
 * 
 * @return true se o estado do botao mudou (pressionado ou solto)
 * na ultima atualizacao
 */
bool botao::alteracaoEstado()
{
    return flagAlteracao;
}

/**
 * @brief Retorna a duracao em millissegundos do ultimo estadomantido (pressionado ou solto)
 * 
 * @return Tempo em millissegundos que o botao permaneceu no ultimo estado 
 */
unsigned long botao::duracaoUltimoEstado()
{
    return duracaoEstado;
}

