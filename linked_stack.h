/* Copyright <Bruno Motta> <Thomas Machado>
 * linked_stack.h
 */
#include <cstdint>
#include <stdexcept>

#include "./linked_list.h"


namespace structures {
    //! Classe pilha encadeada
    /*!
    pilha encadeada com todas as propriedades básicas, heradada de lista encadeada
    */
template<typename T>
class LinkedStack : public LinkedList<T>{
 public:
    //! Construtor
    /*!
    Gera uma pilha encadeada
    */
    LinkedStack() {
       typename LinkedList<T>::LinkedList();
    }
    //! Destrutor
    /*!
    desaloca memória da pilha
    */
    ~LinkedStack() {
        clear();
    }
    //! Limpa pilha
    /*!
    Limpa a pilha
    */
    void clear() {
        LinkedList<T>::clear();
    }
    //! metodo para adicionar no inicio.
    /*!
    adiciona um item no inicio da lista (apontado pela cabeca)
    \param item a ser adicionado no inicio da lista
    */
    void push(const T& data) {
        LinkedList<T>::push_front(data);
    }
    //! Metodo para desempilhar
    /*!
    verifica se a lista esta vazia antes de proceder, caso a lista estaja vazia retorna um erro.
    Tem como parametro de retorno o item no inicio da lista.
    Subtrai 1 da variavel que indica o final ao retirar um item.
    \return o primeiro item da lista
    */
    T pop() {
       return LinkedList<T>::pop_front();
    }
    //! Metodo para verificar o dado em uma posicao.
    /*!
    Nao modifica nem retira nenhum dado

    \param posicao a ser pesquisada
    \return o dado na posicao
    */
    T& top() const {
       return LinkedList<T>::at(0);
    }
    //! Verifica lista vazia.
    /*!
    Metodo para verificar se a lista esta vazia. 
    Compara o tamanho da lista com 0.
    \return TRUE para lista vazia e FALSE para lista nao vazia
    */
    bool empty() const {
      return  LinkedList<T>::empty();
    }
    //! Tamanho atual da lista.
    /*!
    verifica o tamanho atual da lista
    \return variavel size_
    */
    std::size_t size() const {
       return LinkedList<T>::size();
    }
    //! nó
    typename LinkedList<T>::Node* head{nullptr};
    //! Tamanho
    std::size_t size_{0u};
};

}  // namespace structures


