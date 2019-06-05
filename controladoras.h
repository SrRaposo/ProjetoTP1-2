#ifndef CONTROLADORAS_H_INCLUDED
#define CONTROLADORAS_H_INCLUDED

#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <stdexcept>

#include "dominios.h"
#include "interfaces.h"

class CntrAAutenticacao:public IAAuteuticacao{

    private:
        ISAutenticacao *controladora_servico;
        IAUsuario *controladora_usuario;

    public:
        void executar();

        void setCSAutenticacao(ISAutenticacao *controladora_servico){
            this->controladora_servico = controladora_servico;
        }

        void setCAUsuario(IAUsuario *controladora_usuario){
            this->controladora_usuario = controladora_usuario;
        }
};

class CntrAUsuario:public IAUsuario{

    private:
        const static int DESCADASTRAR_USUARIO = 1;
        const static int COMPRAR_INGRESSO = 2;
        const static int CADASTRAR_EVENTO = 3;
        const static int DESCADASTRAR_EVENTO = 4;
        const static int ALTERAR_EVENTO = 5;
        const static int RETORNAR = 6;

        ISUsuario *controladora_servico;

    public:
        void executar(std::string cpf, std::string senha);

        void setCSUsuario(ISUsuario *controladora_servico){
            this->controladora_servico = controladora_servico;
        }
};

#endif