//! Classe Fila.
/*!
    Codigo de uma classe Fila. Com todos os atributos e metodos
    necessarios para um bom funcionamento de uma estrutura de dados
    em formato Fila.
*/
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint> // std::size_t
#include <stdexcept> // C++ Exceptions

namespace structures {

template<typename T>
class ArrayQueue {
public:
    ArrayQueue();

    ArrayQueue(std::size_t max);

    ~ArrayQueue();

    void enqueue(const T& data);

    T dequeue();

    T& back();
    
    T& front();

    void clear();

    std::size_t size();

    std::size_t max_size();

    bool empty();

    bool full();

private:
    T* contents;
    std::size_t size_;/*!< variavel que indica o tamanho atual da fila (0 = 1 elemento)*/
    std::size_t max_size_; /*!< variavel que indica o tamanho maximo da fila*/

    const static auto DEFAULT_SIZE = 10u;
};


//! Construtor sem parametros.
/*!
    Gera uma fila utilizando um valor padrão de tamanho. Valor padrão = 10
*/
template <class T>
ArrayQueue<T>::ArrayQueue()
{
    max_size_ = DEFAULT_SIZE;
	contents = new T[max_size_];
	size_ = -1;
					 
}

//! Construtor com parametros.
/*!
    Gera uma fila utilizando um valor de entrada como tamanho.
*/
template <class T>
ArrayQueue<T>::ArrayQueue(std::size_t max)
{
	max_size_ = max;
	contents = new T[max_size_];
	size_ = -1;
}
//! destrutor.
/*!
    Desaloca a meoria do objeto em questao
*/
template <class T>
ArrayQueue<T>::~ArrayQueue()
{
	delete contents;
}
//! Verifica fila vazia.
/*!
    Metodo para verificar se a fila esta vazia. 
    Compara o tamanho da fila com -1.
    \return TRUE para fila vazia e FALSE para fila nao vazia
*/
template <class T>
bool ArrayQueue<T>::empty()
{
	return (size_ == -1); 
}
//! Verifica fila cheia.
/*!
    Metodo para verificar se a fila esta cheia. 
    Compara o tamanho da fila com o tamanho estipiulado ao instanciar o objeto.
    \return TRUE para fila cheia e FALSE para fila nao cheia
*/
template <class T>
bool ArrayQueue<T>::full()
{
	return (size_ +1 == max_size_ ); 
}
//! Metodo para desenfileirar.
/*!
    verifica se a fila esta vazia antes de proceder, caso a fila estaja vazia retorna um erro.
    Tem como parametro de retorno o item no inicio da fila.
    Subtrai 1 da variavel que indica o fim da fila apos retirar um item.
    Este metodo tambem move todos os elementos restantes uma posicao para frente da fila
    \return primeiro item da fila
    
*/
template <class T>
T ArrayQueue<T>::dequeue()
{
	if (empty())
	{
		throw std::out_of_range("fila vazia") ; 
	}
	else
	{
	    T out = contents[0];
	   
	   
       for (int i = 0; (i < size_ ) ; i++)
            {
    	        contents[i] = contents[i+1];
    	    }
    	    
		size_ -= 1;
		return (out);
	}	
}
//! metodo para enfileirar.
/*!
    verifica se a fila esta cheia antes de proceder, caso a fila estaja cheia retorna um erro.
    Tem como parametro de entrada o item a ser posto no fim da fila .
    soma 1 à variavel que indica o fim da fila ao adicionar um item.
    \param data a ser adicionado ao final da fila
*/
template <class T>
void ArrayQueue<T>::enqueue(const T& data)
{
	if (full())
	{
		throw std::out_of_range("fila cheia") ; 
	}
	else
	{
		size_ += 1;
		contents[size_] = data;
	}
	
};
//! Fim da fila.
/*!
    verifica se a fila esta vazia antes de proceder, caso a fila estaja vazia retorna um erro.
    Metodo que retorna o item no final da fila mas sem retirar nenuhm item
    \return Ultimo intem da fila
*/
template <class T>
T& ArrayQueue<T>::back()
{
	if (empty())
	{
		throw std::out_of_range("fila vazia") ;
	}
	else
	{		
		return (contents[size_]);
	}	
}
template <class T>
T& ArrayQueue<T>::front()
{
    if (empty())
    {
        throw std::out_of_range("fila vazia") ;
    }
    else
    {       
        return (contents[0]);
    }   
}
//! limpa a fila.
/*!
    Metodo para limpar a fila resetando o valor da variavel que indica o fim
*/
template <class T>
void ArrayQueue<T>::clear()
{
	size_ = -1;
}

//! Tamanho atual da fila.
/*!
    verifica o tamanho atual da fila
    \return variavel size_
*/
template <class T>
std::size_t ArrayQueue<T>::size()
{
	return (size_ +1);
}

//! Tamanho total da fila.
/*!
    verifica o tamanho maximo da fila
    \return variavel max_size_
*/
template <class T>
std::size_t ArrayQueue<T>::max_size()
{
	return max_size_;
}





}

#endif
