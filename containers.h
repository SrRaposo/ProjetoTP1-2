#ifndef CONTAINERS_H_INCLUDED
#define CONTAINERS_H_INCLUDED

#include "dominios.h"
#include "entidades.h"

#include <list>
#include <algorithm>

using namespace std;

// Declaração de classe container de usuários.

class ContainerCartao{

    private:
        //dado principal
        list<Cartao_de_Credito> LCartao; //lista de cartoes de credito

        //relacoes de grafo
        list<Usuario*> LPUsuario;   //Usuario do cartao

        //referencias pra containers
        ContainerUsuario *PCUsuario; //ponteiro pra container de usuario

    public:

        Cartao_de_Credito* incluir(std::string numerostr, std::string codigostr, std::string datastr) throw(runtime_error){

            Cartao_de_Credito cartaoNew;

            Numero_de_cartao_de_credito numeroNew;
            Codigo_de_seguranca codigoNew;
            Data_de_validade dataNew;

            numeroNew.Set(numerostr);
            codigoNew.Set(codigostr);
            dataNew.Set(datastr);

            cartaoNew.Set(numeroNew);
            cartaoNew.Set(codigoNew);
            cartaoNew.Set(dataNew);

            LCartao.push_back(cartaoNew);

            return (*cartaoNew);
        };

        void remover(Cartao_de_Credito input){
            LCartao.remove(input);
        };

        //grafo
        void linkUsuario(Usuario *input){
            LPUsuario.push_back(input);
        };

        void removerLinkUsuario(Usuario *input){
            LPUsuario.remove(input);
        };

        //set referencias pra containers
        void setCUsuario(ContainerUsuario *input){
            this->PCUsuario = input;
        };


};

class ContainerUsuario{

    private:
        //dado principal
        list<Usuario> LUsuario;

        //relacoes de grafo
        list<Cartao_de_Credito*>    LPCartao;  //Cartao do usuario
        list<list<Evento*>>         LLPEvento;//Eventos de cada usuario (no max 5)
        list<list<Ingresso*>>       LLPIngresso;//Ingressos do usuario

        //referencias pra containers
        ContainerCartao     *PCCartao;
        ContainerEvento     *PCEvento;
        ContainerIngresso   *PCIngresso;

    public:

        //basicas

        //retorna usuario para facilitar linkar containers na controladora
        Usuario* incluir(std::string cpfstr, std::string senhastr) throw(runtime_error){

            Usuario usuarioNew;

            Cpf cpfNew;
            Senha senhaNew;

            cpfNew.Set(cpfstr);
            senhaNew.Set(senhastr);

            usuarioNew.Set(cpfNew);
            usuarioNew.Set(senhaNew);

            LUsuario.push_back(usuarioNew);
            
            return *usuarioNew;
        };

        void remover(Usuario input){
            LUsuario.remove(input);
        };

        bool pesquisar(std::string cpfInput, std::string senhaInput){
            
            list<Usuario>::iterator it = LUsuario.begin();

            for(; it != LUsuario.end(); ++it)
            {
                if ((*it).GetCpf() == cpfInput && (*it).GetSenha() == senhaInput )
                    return true;
            }
            return false;
        };

        Usuario* retornar(std::string cpf, std::string senha){

            list<Usuario>::iterator it = LUsuario.begin();
            for(; it != LUsuario.end(); ++it)
            {
                if ((*it).GetCpf() == cpfInput && (*it).GetSenha() == senhaInput )
                    return (&*it);
            }
            return NULL;
        };

        //links de grafo do sistema

        void linkCartao(Cartao_de_Credito* input){
            LPCartao.push_back(input);
        };

        Cartao_de_Credito* removerLinkCartao(Usuario* input){
            list<Usuario>::iterator itU = LUsuario.begin();
            list<*Cartao_de_Credito>::iterator itC = LPCartao.begin();
            list<*Cartao_de_Credito>::iterator aux;

            for(; itU != LUsuario.end(); ++itU)
            {
                if (&*itU == &*input)
                    aux = itC;
                    LPCartao.remove(itC);
                    return(&*aux);
                ++itC;
            }
        };



        //set containers

        void setCCartao(ContainerCartao *input)
        {
            this->PCCartao = input;
        };
        void setCEvento(ContainerEvento *input)
        {
            this->PCEvento = input;
        };
        void setCIngresso(ContainerIngresso *input)
        {
            this->PCIngresso = input;
        };

};

class ContainerEvento{

    private:
        //dado principal
        list<Evento> LEvento;   //lista de eventos

        //relacoes de grafo
        list<list<*Apresentacao>> LLPApresentacao;   //no max 10 por evento
        list<*Usuario> LPUsuario;                   //lista de ponteiro pra usuario;

        //referencias pra containers
        ContainerApresentacao *PCApresentacao   //ponteiro pra container de apresentacao
        ContainerUsuario *PCUsuario;            //ponteiro pra container de usuario

        public;

        //set referencias pra containers
        void setCApresentacao(ContainerApresentacao *input)
        {
            this->PCApresentacao = input;
        };
        void setCUsuario(ContainerUsuario *input)
        {
            this->PCUsuario = input;
        };
};

class ContainerApresentacao{

    private:
        //dado principal
        list<Apresentacao> LApresentacao;   //lista de apresentacao

        //relacoes de grafo
        list<*Evento> LPEvento;              //lista de ponteiro pra usuario;
        list<list<*Ingresso>> LLPIngresso;   //no max 250 por apresentacao

        //referencias pra containers
        ContainerEvento *PCEvento           //ponteiro pra container de evento
        ContainerIngresso *PCIngresso;      //ponteiro pra container de ingresso

        public;

        //set referencias pra containers
        void setCEvento(ContainerEvento *input)
        {
            this->PCEvento = input;
        };
        void setCApresentacao(ContainerIngresso *input)
        {
            this->PCIngresso = input;
        };
};

class ContainerIngresso{
    private:
        //dado principal
        list<Ingresso> LIngresso;   //lista de eventos

        //relacoes de grafo
        list<*Usuario> LPUsuario;             //Usuario do ingresso
        list<*Apresentacao> LPApresentacao;   //Apresentacao do ingresso

        //referencias pra containers
        ContainerApresentacao *PCApresentacao   //ponteiro pra container de apresentacao
        ContainerUsuario *PCUsuario;            //ponteiro pra container de usuario

        public;

        //set referencias pra containers
        void setCUsuario(ContainerUsuario *input)
        {
            this->PCUsuario = input;
        };
        void setCApresentacao(ContainerApresentacao *input)
        {
            this->PCApresentacao = input;
        };
};


#endif // CONTROLADORAS_H_INCLUDED