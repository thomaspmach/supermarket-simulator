/* Copyright <Bruno Motta> <Thomas Machado>
 * linked_stack.h
 */
#ifndef SUPERMERCADO_HPP
#define SUPERMERCADO_HPP

#include <cstdint>
#include <stdexcept>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "./circular_list.h"
#include "./Cliente.hpp"
#include "./Caixa.hpp"

namespace structures {

class Supermercado {
 private:
 	int tmp_prox_cliente_;
 	int tmp_med_cliente_;
 	int relogio_;  // contador
 	int tempo_total_;
 	int n_de_caixas_;
 	int n_de_desistentes_;
 	int faturamento_desistente_;
 	int T_; // numero de comparacao da fila para adicionar caixa
 	structures::CircularList<Caixa> caixas{};
    std::string nome_;
 	

 public:
 	//! Construtor
	/*!
    Gera um cliente gerando todos seus atributors necessários
	*/
 	Supermercado () {
        ler_arquivo();
        
        
 		n_de_desistentes_ = 0;
 		faturamento_desistente_ = 0;
        relogio_ = 0;



 	}
 	void simular(){
 		while(relogio_ < tempo_total_){

 			bool novo_caixa_ = true;

 			verificar_caixas(novo_caixa_);
            
            
            

 			// verifica se precisa adicionar cliente
 			if (tmp_prox_cliente_ == relogio_)
 			{
 				novo_cliente();
 			}
 			// verifica necessidade de um novo caixa
 			if (novo_caixa_)
 			{
 				novo_caixa();
 			}

 			relogio_++;

 		}

 	}

 	void novo_cliente(){
 		Cliente* cliente = new Cliente(relogio_);
        Caixa* caixa_atual_;
        Caixa* caixa_aux_;
        caixa_atual_ = &caixas.at(0);
        caixa_aux_ = &caixas.at(0);

 		if (filas_cheias())
 		{
 			n_de_desistentes_ = n_de_desistentes_ + 1;
 			faturamento_desistente_ = faturamento_desistente_ + cliente->gasto()*3;

 		} else {

	 		if (cliente->por_produto()) // escolhe fila por produto
	 		{
	 			caixa_atual_ = &caixas.at(0);
                caixa_aux_ = &caixas.at(0);

	 			for (int i = 1; i < n_de_caixas_; ++i)
	 			{
	 				caixa_aux_ = &caixas.at(i);
	 				
	 				if (caixa_atual_->produtos() > caixa_aux_->produtos() )
	 				{
	 					caixa_atual_ = caixa_aux_;
	 				}
	 			}

	 			
	 		} else {  // escolhe fila por pessoas

                caixa_atual_ = &caixas.at(0);
                caixa_aux_ = &caixas.at(0);


	 			for (int i = 1; i < n_de_caixas_; ++i)
	 			{
	 				caixa_aux_ = &caixas.at(i);
                    
	 				
	 				if (caixa_atual_->tamanho() > caixa_aux_->tamanho() )
	 				{
	 					caixa_atual_ = caixa_aux_;
	 				}
	 			}
	 		}
            
            if (caixa_atual_->tamanho() > 15)
            {
                n_de_desistentes_ = n_de_desistentes_ + 1;
                faturamento_desistente_ = faturamento_desistente_ + cliente->gasto()*3;
            }
            else
            {
               caixa_atual_->add_cliente(*cliente);
            }
            
            tmp_prox_cliente_ = relogio_ + tmp_med_cliente_;

	 	}	

 	}
 	void ler_arquivo(){
        std::ifstream ifs;
        ifs.open("./config.txt");
        
        if (ifs.is_open()) {
            char linha[40];
            
            ifs.getline(linha,40); //le nome
            nome_ = linha;
            
            ifs >> tempo_total_; //tempo total de simulacao
            tempo_total_ = tempo_total_*3600;
            
            ifs >> tmp_med_cliente_;
            
            ifs >> T_;
            
            ifs >> n_de_caixas_;
            
            Caixa* caixa_atual_ ;
            int ef;
            int sal;
            std::string id;
            
            for (int i = 0; i < n_de_caixas_; i++) {
                
                ifs >> id;
                ifs >> ef;
                ifs >> sal;
                
                caixa_atual_ = new Caixa(id, ef, sal);
                caixas.push_back(*caixa_atual_);
                
            }
            
            while (!ifs.eof()) {
                ifs >> linha;
            }
            
            
        }
        else
        {
            std::cout << "Nao foi possivel abrir..." << std::endl;
        }

 	}

 	void novo_caixa(){

 		

 		int eficiencia = std::rand()%3 + 1; // numero entre 1 e 3
 		int salario = 1600; // salario minimo dobrado (sobre_hora) ~POG
        Caixa* caixa_atual_ ;
        caixa_atual_ = new Caixa("extra", eficiencia, salario);

 		caixas.push_back(*caixa_atual_);
 		n_de_caixas_++;


 	}
 	void verificar_caixas(bool& novo_caixa){

 		Caixa* caixa_atual_;

 		for (int i = 0; i < n_de_caixas_; ++i)
 			{
 				caixa_atual_ = &caixas.at(i);
                int saida_ = caixa_atual_->prox_saida();

 				if (saida_ <= relogio_ && saida_ > 0)
 				{
 					caixa_atual_->pass_cliente();
 				}

 				if (caixa_atual_->tamanho() < T_ )
 				{
 					novo_caixa = false;
 				}
 			}
 	}
 	bool filas_cheias(){
 		Caixa* caixa_atual_;
 		bool cheio = true;

 		for (int i = 0; i < n_de_caixas_; ++i)
 			{
 				caixa_atual_ = &caixas.at(i);

 				if (caixa_atual_->tamanho() < 10 )
 				{
 					cheio = false;
 				}

 			}

 		return cheio;

 	}
    void results(){
        Caixa* caixa_atual_;
        int fat_total_ = 0;
        int total_de_clientes_ = 0;
        
        std::cout<<"Nome: " << nome_ << std::endl;
        
        for (int i = 0; i < n_de_caixas_; ++i)
        {
            caixa_atual_ = &caixas.at(i);
            
            fat_total_ += caixa_atual_->faturamento();
            total_de_clientes_ += caixa_atual_->atendimentos();
            
            std::cout<<"Caixa: " << caixa_atual_->id() << std::endl;
            std::cout<<"Eficiencia: " << caixa_atual_->eficiencia() << std::endl;
            std::cout<<" // Faturamento = " << caixa_atual_->faturamento();
            std::cout<<" // Lucro = " << caixa_atual_->faturamento()-caixa_atual_->salario();
            std::cout<<" // Faturamento/cliente = " << caixa_atual_->faturamento()/(caixa_atual_->atendimentos()) << std::endl;
        }
        total_de_clientes_ = total_de_clientes_/n_de_caixas_; // media de clientes por caixa
        
        std::cout<<" // Faturamento total = " << fat_total_ << std::endl;
        std::cout<<" // Faturamento/caixa = " << fat_total_/n_de_caixas_ << std::endl;
        std::cout<<" // Tempo médio de permanência na fila = " << tempo_total_/(total_de_clientes_) << std::endl;
        std::cout<<" // Clientes atendidos = " << total_de_clientes_*n_de_caixas_ << std::endl;
        std::cout<<" // Clientes desistentes = " << n_de_desistentes_ << std::endl;
        std::cout<<" // Faturamento Desistente = " << faturamento_desistente_ << std::endl;
        
        
    }
 	
};

} // fim do namespace


#endif
