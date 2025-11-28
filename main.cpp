#include <iostream>
#include <string>
#include <algorithm> //Para usar funções de limpeza de string
#include "Restaurante.hpp"

//Função auxiliar paraque vai remover espaços antes e depois da string
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (std::string::npos == first) return "";
    size_t last = std::string::npos;
    last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

int main() {
    int numChefs, numMesas;

    //Lê a configuração inicial
    if (!(std::cin >> numChefs >> numMesas)) {
        return 0;
    }
    //Instancia o restaurante
    Restaurante restaurante(numChefs, numMesas);
    std::string token;
   
    //Loop principal de leitura
    //O cin >> token lê a primeira palavra, pode ser o número da mesa ou fim
    while (std::cin >> token) {
        //verifica se é o comando de encerramento
        if (token == "FIM") {
            break;
        }
        //se não for fim é o ID da mesa, converte string para int
        int mesaId = std::stoi(token);
        //lê o resto da linha
        std::string restoDaLinha;
        std::getline(std::cin, restoDaLinha);
        //limpa espaços extras
        std::string pedido = trim(restoDaLinha);

        //Verifica se é fim de pedido da mesa ou um prato novo [cite: 22]
        if (pedido == "fim") {
            restaurante.finalizarMesa(mesaId);
        } else {
        //Envia o pedido 
            restaurante.processarPedido(mesaId, pedido);
        }
    }

    return 0;
}