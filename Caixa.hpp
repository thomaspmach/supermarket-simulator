/* Copyright <Bruno Motta> <Thomas Machado>
 * linked_stack.h
 */
#ifndef CAIXA_HPP
#define CAIXA_HPP

#include <cstdint>
#include <stdexcept>
#include <string>
#include <stdlib.h>

#include "./array_queue.h"
#include "./Cliente.hpp"

namespace structures {

class Caixa {

 private:
 	std::string id_; // como definir um id?
 	int eficiencia_;  // 1-bom ; 2-médio ; 4-ruim  segundos/produto
 	int tempo_cheque;  // 10-bom ; 25-médio ; 60-ruim segundos
 	int salario_;
    structures::ArrayQueue<Cliente> fila{20u};
 	int produtos_;  // total de produtos na fila
 	int atendimentos_;
 	int tempo_medio_atendimento_;
 	int faturamento_;  //faturamento real
 	int fat_med_cliente_; // faturamento médio por cliente
 	int temp_saida_;  // tempo da saída do ultimo cliente

 public:
 	//! Construtor
	/*!
    Gera um cliente gerando todos seus atributors necessários
	*/
 	Caixa(std::string id, int eficiencia, int salario ) {

 		id_ = id;
 		eficiencia_ = eficiencia;
 		if (eficiencia_ == 3)
 		{
 			eficiencia_ = 4;
 			tempo_cheque = 60;
 		}
 		if (eficiencia_ == 2)
 		{
 			tempo_cheque = 25;
 		}
 		if (eficiencia_ == 1)
 		{
 			tempo_cheque = 10;
 		}
 		salario_ = salario;
 		produtos_ = 0;
 		atendimentos_ = 0;
 		tempo_medio_atendimento_ = 0;
 		faturamento_ = 0;
 		fat_med_cliente_ = 0;
 		temp_saida_ = 0;

 	}
 	int tamanho(){
 		return fila.size();
 	}
 	void add_cliente(Cliente cliente){
 		Cliente cliente_ = cliente;

 		

 		produtos_ += cliente_.produtos();
        
        if (fila.empty())
        {
            temp_saida_ = cliente_.chegada() + eficiencia_*cliente_.produtos();
        }
        else
        {
            temp_saida_ += eficiencia_*cliente_.produtos();
        }

 		if (cliente_.cheque())
 		{
 			temp_saida_ += tempo_cheque;
 		}
        
        
 		cliente_.saida(temp_saida_);
        fila.enqueue(cliente_);


 	}
 	void pass_cliente(){

 		Cliente cliente_ = fila.dequeue();

 		atendimentos_++;
 		faturamento_ += cliente_.gasto();
 		fat_med_cliente_ = faturamento_/atendimentos_;


 	}
 	int prox_saida(){
        
        if (fila.empty())
        {
            return -1;
        }
        else
        {
 		Cliente cliente_ = fila.front();
 		return cliente_.saida();
        }
 	}
 	bool cheio(){
 		return fila.full();
 	}
 	int produtos(){
 		return produtos_;
 	}
    int faturamento(){
        return faturamento_;
    }
    std::string id(){
        return id_; 
    }
    int atendimentos(){
        return atendimentos_;
    }
    int salario(){
        return salario_;
    }
    int eficiencia(){
        return eficiencia_;
    }


 
 	
};

} // fim do namespace


#endif
