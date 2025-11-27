#include <string>  //Para std::string
#include <vector>  //Para o mapa_mesas
#include <queue>  //Para a fila de chefs e fila de espera
#include <sstream> //Para std::stringstream (parsear linhas)

class Restaurante {
    public:
        Restaurante(int capacidadeMesa, int filaEspera, int filachefs){
            this->capcidadeMesa = capacidadeMesa;
            this->filaEspera = filaEspera;
            this->filaChefs = filachefs;
        }
        ~Restaurante() 

        

    private:
        int capcidadeMesa;
        int filaEspera;
        int filaChefs;
        std::vector<std::string> mapa_mesas; // Mapa das mesas do restaurante
        std::queue<std::string> fila_espera; // Fila de espera dos clientes
        std::queue<std::string> fila_chefs;  // Fila dos chefs disponíveis
}

