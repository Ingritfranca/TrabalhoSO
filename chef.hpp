#pragma once //Previne inclusões múltiplas do arquivo de cabeçalho
#include <string> //Para std::string
#include <unistd.h> //Para pid_t

//Esta classe representa um atendimento, o atendimento vai ter subprocesso vinculado a ele
class Atendimento final {
public:
    //Construtor da classe para criar um atendimento é necessário informar o ID do chef e da mesa
    Atendimento(unsigned int chefId, unsigned int mesaId);
    //Destrutor da classe ao chama-lo o subprocesso vinculado a este atendimento deve ser encerrado.
    ~Atendimento();

    void prepararPedido(const std::string &pedido) const;

private:
    //ID do processo (pid)
    unsigned int chefId;
    pid_t pid{-1};
    //Descritores de arquivo que guardam o número dos canais onde serão realizadas a comunicação entre processos
    //são dois inteiros, inicializados previamente com o valor -1
    int fd[2]{-1, -1};
    std::string quemSou;

    //Método chamado na inicialização do atendimento
    void iniciar();
};

class Chef {
public:
    explicit Chef(unsigned int id);

    void iniciarAtendimento(unsigned int mesa);

    void prepararPedido(const std::string &pedido);

    void encerrarAtendimento();

private:
    const unsigned int id;//ID do chef
    Atendimento *atendimento;
};
