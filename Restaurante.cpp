#include "Restaurante.hpp"
#include <iostream>

Restaurante::Restaurante(int numChefs, int numMesas) {
    //Inicializa o vetor de mesas com -1 
    //O tamanho é numMesas + 1 para podermos usar índice 1 como Mesa 1
    mesaChef.resize(numMesas + 1, -1);
    for (int i = 0; i < numChefs; ++i) {
        chefs.push_back(new Chef(i + 1)); //IDs 1 a N
        chefsLivres.push(i); //Todos começam livres
    }
}

Restaurante::~Restaurante() {
    for (auto c : chefs) delete c;
    chefs.clear();
}

void Restaurante::processarPedido(unsigned int mesaId, const std::string& item) {
    
    //A mesa já tem um chef exclusivo?
    //Verificação O(1) usando o vetor
    if (mesaChef[mesaId] != -1) {
        int idChef = mesaChef[mesaId];
        //Envia direto para o chef que já está lá
        chefs[idChef]->prepararPedido(item);
        return;
    }

    // A mesa não tem chef. Tem chef livre? 
    //Verificação O(1) olhando a pilha
    if (!chefsLivres.empty()) {
        //Pega um chef livre em O(1)
        int idChef = chefsLivres.front();
        chefsLivres.pop();

        //Associa esse chef à mesa 
        mesaChef[mesaId] = idChef;

        //Inicia o processo e manda o pedido
        chefs[idChef]->iniciarAtendimento(mesaId);
        chefs[idChef]->prepararPedido(item);
        
        std::cout << "Chef " << idChef + 1 << " alocado para Mesa " << mesaId << " [O(1)]" << std::endl;
        return;
    }

    //Tudo ocupado vai para a lista de espera 
    std::cout << "Sem chefs! Pedido da Mesa " << mesaId << " foi para a fila de espera." << std::endl;
    filaEspera.push({mesaId, item});
}

void Restaurante::finalizarMesa(unsigned int mesaId) {
    //Verifica O(1) quem estava atendendo
    int idChef = mesaChef[mesaId];  
    if (idChef != -1) {
        //Manda o chef parar
        chefs[idChef]->encerrarAtendimento();
        //Libera a mesa
        mesaChef[mesaId] = -1; 
        //Devolve o chef para a pilha de livres O(1)
        chefsLivres.push(idChef);
        std::cout << "Mesa " << mesaId << " finalizada. Chef " << idChef + 1 << " livre." << std::endl;
        // Se tem gente na fila, já pega esse chef que acabou de liberar e bota pra trabalhar
        if (!filaEspera.empty()) {
            PedidoPendente proximo = filaEspera.front();
            filaEspera.pop();  
            //Chama recursivamente para processar o da fila
            processarPedido(proximo.mesaId, proximo.item);
        }
    }
}