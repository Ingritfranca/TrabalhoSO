#include "chef.hpp" // Inclui a definição da classe Chef e Atendimento
#include <unistd.h> // Para fork, pipe, read, write, close
#include <sys/wait.h>// Para waitpid
#include <fcntl.h>// Para open
#include <cstring>// Para strerror

// Construtor responsável por criar o atendimento e iniciar o subprocesso chef
Atendimento::Atendimento(unsigned int chefId, unsigned int mesaId)
    : pid(-1), fd{-1, -1}, quemSou(), chefId(chefId)
{
    //Criação do pipe de comunicação entre pai e filho
    if (pipe(fd) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    //Criação do processo filho
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    //Se pid == 0 significa que é o processo filho
    if (pid == 0) { 
        quemSou = "Filho";
        //fecha o lado de escrita porque o filho só lê dados
        close(fd[1]);
        // O filho fica aguardando mensagens enviadas via pipe
        iniciar();
        //Finaliza o processo filho corretamente
        _exit(0);

    } else {
        //Caso contrário é o processo pai
        quemSou = "Pai";
        //O pai não precisa ler o pipe então fecha o lado de leitura
        close(fd[0]);
    }
}

//Destrutor responsável por encerrar o atendimento e esperar o processo filho terminar
Atendimento::~Atendimento() {
    if (quemSou == "Pai") {
        close(fd[1]); //fecha canal de escrita
        waitpid(pid, nullptr, 0); //espera o filho terminar normalmente
    }
}

//Envia um pedido do processo pai para o filho pelo pipe
void Atendimento::prepararPedido(const std::string &pedido) const {
    write(fd[1], pedido.c_str(), pedido.size() + 1);
}

//Processo filho recebe mensagens do pipe e escreve no arquivo formatado
void Atendimento::iniciar() {

    // Define o nome do arquivo do chef
    std::string filename = "ChefeCozinha_" + std::to_string(chefId) + ".txt";
    int file = open(filename.c_str(), O_CREAT | O_WRONLY | O_APPEND, 0666);

    // Cabeçalho
    dprintf(file, "ChefeCozinha_%u\n\n", chefId);

    bool mesaRegistrada = false;
    char buffer[256];

    //Loop para receber pedidos até receber fim
    while (true) {
        ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);
        if (n <= 0) break;

        buffer[n] = '\0';
        std::string msg(buffer);

        //Quando receber fim o processo encerra
        if (msg == "fim") {
            break;
        }

        //A primeira mensagem válida deve ser a mesa
        if (!mesaRegistrada && msg.rfind("mesa:", 0) == 0) {
            unsigned int mesa = std::stoi(msg.substr(5));
            dprintf(file, "Mesa %u:\n\n", mesa);
            mesaRegistrada = true;
            continue;
        }

        //Escreve os pedidos no arquivo 
        if (mesaRegistrada) {
            dprintf(file, "- %s\n", msg.c_str());
        }
    }

    //fecha o arquivo e o pipe
    close(file);
    close(fd[0]);
}

//Construtor só guarda o ID do chef
Chef::Chef(const unsigned int id) : id(id), atendimento(nullptr) {}

//Inicia um atendimento e já envia a identificação da mesa
void Chef::iniciarAtendimento(unsigned int mesa) {
    atendimento = new Atendimento(id, mesa);
    atendimento->prepararPedido("mesa:" + std::to_string(mesa)); 
}

//Envia os pedidos para o subprocesso chef
void Chef::prepararPedido(const std::string &pedido) {
    if (!atendimento) return;
    atendimento->prepararPedido(pedido);
}

//Finaliza o atendimento enviando o comando fim
void Chef::encerrarAtendimento() {
    if (atendimento) {
        atendimento->prepararPedido("fim");
        delete atendimento;
        atendimento = nullptr;
    }
}
