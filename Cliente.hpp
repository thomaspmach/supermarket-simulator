/* Copyright <Bruno Motta> <Thomas Machado>
 * linked_stack.h
 */
#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <cstdint>
#include <stdexcept>
#include <string>
#include <stdlib.h>


namespace structures {

class Cliente {
 private:
 	int gasto_;
 	int produtos_;
 	int chegada_;
 	int saida_;
 	bool por_produto_; // true = cliente do tipo por produto
 	bool cheque_;


 	void gerar_produtos(){
 		produtos_ = std::rand()%99 + 2; // qnt de produtos
 		gasto_ = 0;
 		for (int i = 0; i < produtos_; ++i)
 		{
			gasto_ = gasto_ + (std::rand()%90 + 1);
 		}

 	}
 	void set_cheque(){
 		int i = std::rand()%100;

 		if (i < 20){
 			cheque_ = true;

 		} else {
 			cheque_ = false;
 		}
 	}
 	void tipo(){
 		int i = std::rand()%100;

 		if (i >= 50){
 			por_produto_ = true;

 		} else {
 			por_produto_ = false;
 		}
 	}

 public:
 	//! Construtor
	/*!
    Gera um cliente gerando todos seus atributors necessários
    \param chegada , hora de chegada em segundos
	*/
 	Cliente(int chegada) {

 		chegada_ = chegada;
 		gerar_produtos();
 		tipo();
 		set_cheque();

 	}
    Cliente(){
    }
 	//! destrutor
	/*!
    deleta as coisa tudo, mas não sei como ainda
	*/
 //	~Cliente() {
  //
 //	}
 	//! destrutor
 	int saida(){
 		return saida_;
 	}
 	void saida(int tempo){
 		saida_ = tempo;
 	}
 	int gasto(){
 		return gasto_;
 	}
 	bool por_produto(){
 		return por_produto_;
 	}
 	int produtos(){
 		return produtos_;
 	}
 	bool cheque(){
 		return cheque_;
 	}
    int chegada(){
        return chegada_;
    }



};

} // fim do namespace


#endif
