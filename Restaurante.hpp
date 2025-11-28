#pragma once  
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include "chef.hpp"
#include "Mesa.hpp"

//Estrutura que guarda pedidos quando não tem chef disponível 
struct PedidoPendente {
    unsigned int mesaId;
    std::string item;
};

class Restaurante {
public:
    //Diz quantos chefs e mesas existem
    Restaurante(int numChefs, int numMesas);
    //Liberar memória quando o programa fechar
    ~Restaurante();
    //Função chamada quando uma mesa faz um pedido
    void processarPedido(unsigned int mesaId, const std::string& item);
    //Função usada quando a mesa já comeu, pagou e vai embora
    void finalizarMesa(unsigned int mesaId);

private:
    //Vetor com todos os chefs cada um é tipo um processo separado
    std::vector<Chef*> chefs;
    //Todas as mesas do restaurante
    std::vector<Mesa> mesas;
    //Pilha onde guardo os chefs livres
    std::stack<int> chefsLivres;
    //Fila para guardar pedidos quando todos os chefs estão ocupados
    std::queue<PedidoPendente> filaEspera;
};
