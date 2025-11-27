#pragma once

class Mesa {
public:
    //Construtor padrão
    Mesa() : id(0), chefResponsavel(-1) {}
    //Construtor com ID
    Mesa(unsigned int id) : id(id), chefResponsavel(-1) {}
    //Diz quem é o chef cuidando desta mesa 
    int getChef() const {
        return chefResponsavel;
    }
    //Define um chef para a mesa
    void alocarChef(int chefId) {
        chefResponsavel = chefId;
    }
    //Libera a mesa 
    void liberar() {
        chefResponsavel = -1;
    }
    //Verifica se a mesa está ocupada 
    bool estaSendoAtendida() const {
        return chefResponsavel != -1;
    }

private:
    unsigned int id;
    int chefResponsavel; //Guarda o ID do chef -1 = livre
};