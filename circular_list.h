/* Copyright <Bruno Motta>
 * circular_list.h
 */
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>


namespace structures {
    //! Classe lista circular-encadeada
    /*!
    Lista circular-encadeada com todas as propriedades básicas
    */
template<typename T>
class CircularList {
 public:
    //! Construtor
    /*!
    Gera uma lista encadeada
    */
    CircularList() {
        head = nullptr;
        size_ = 0;
    }
    //! Destrutor
    /*!
    desaloca memória da lista
    */
    ~CircularList() {
        clear();
    }
    //! Limpa lista
    /*!
    Limpa a lista
    */
    void clear() {
        Node *index, *anterior;
        index = head;
        for (int i = 0 ; i < size_ ; i ++) {
            anterior = index;
            index = index->next();
            delete anterior;
        }

        head = nullptr;
        size_ = 0;
    }
    //! metodo para adicionar no fim.
    /*!
    Utiliza a funcao adiciona com parametro tamanho da lista
    \param data a ser adicionado ao final da lista
    */
    void push_back(const T& data) {
        insert(data, size_);
    }
    //! metodo para adicionar no inicio.
    /*!
    adiciona um item no inicio da lista (apontado pela cabeca)
    \param data a ser adicionado no inicio da lista
    */
    void push_front(const T& data) {
        Node *novo;
        novo = new Node(data, head);
        if (novo == (nullptr)) {
            throw std::out_of_range("lista cheia");
        }
        if (empty()) {
            head = novo;
            novo->next(novo);
            size_++;
        } else {
            Node *anterior;
            anterior = head;
            int i = 0;
            int index = size();
            while ( i < index - 1 ) {
                anterior = anterior->next();
                i++;
            }
            novo->next(anterior->next());
            anterior->next(novo);
            head = novo;
            size_++;
        }
    }
    //! Metodo para inserir na posicao.
    /*!
    Verifica se a lista esta cheia antes de proceder, caso a lista estaja vazia retorna um erro.
    Verifica se a posição é válida, se a posição não for válida retorna um erro.
    Procura a posicao, desloca todos os itens, que estariam a cima, uma posicao para cima 
    e insere o dado na posicao desejada.
    
    \param data a ser colocado, posicao
    */
    void insert(const T& data, std::size_t index) {
        if (index > size_ || index < 0) {
            throw std::out_of_range("posicao incorreta");
        }
        if (empty()) {  // lista vazia
            Node *novo;
            novo = new Node(data);
            head = novo;
            size_++;
            novo->next(novo);
        } else if (index == 0) {
            push_front(data);
        } else {
            Node *novo;
            Node *anterior;
            novo = new Node(data);
            anterior = head;
            int i = 0;
            while ( i < index - 1 ) {
                anterior = anterior->next();
                i++;
            }
            novo->next(anterior->next());
            anterior->next(novo);
            size_++;
        }
    }
    //! Metodo para inserir em ordem.
    /*!
    Verifica se a lista esta cheia antes de proceder, caso a lista estaja vazia retorna um erro.
    Procura a posicao correta comparando os dados em cada posicao.
    e insere o dado na posicao correta, segundo a ordem crescente.
    
    \param data a ser colocado, posicao
    */
    void insert_sorted(const T& data) {
        Node *atual;
        int index;
        if (empty()) {
            return push_front(data);
        } else {
            atual = head;
            index = 0;

            while (index < size_ - 1 && data > atual->data()) {
                atual = atual->next();
                index++;
            }
            if (data > atual->data()) {
                insert(data, index+1);
            } else {
                insert(data, index);
            }
        }
    }
    //! Metodo para verificar o dado em uma posicao.
    /*!
    Nao modifica nem retira nenhum dado

    \param index a ser pesquisada
    \return o dado na posicao
    */
    T& at(std::size_t index) {
        if (index < 0 || index > size_) {
            throw std::out_of_range("posicao invalida");
        }

        Node *atual;
        atual = head;

        auto i = 0;
        while (i < index) {
            atual = atual->next();
            i++;
        }

        return atual->data();
    }
    //! Metodo para verificar o dado em uma posicao. (const)
    /*!
    Nao modifica nem retira nenhum dado

    \param index a ser pesquisada
    \return o dado na posicao
    */
    const T& at(std::size_t index) const {
        if (index < 0 || index > size_) {
            throw std::out_of_range("posicao invalida");
        }

        Node *atual;
        atual = head;

        auto i = 0;
        while (i < index) {
            atual = atual->next();
            i++;
        }

        return atual->data();
    }
    //! Metodo para retirar da posicao.
    /*!
    verifica se a lista esta vazia antes de proceder, caso a lista estaja vazia retorna um erro.
    Verifica se a posição é válida, se a posição não for válida retorna um erro.
    salva o item em uma variavel de retorno e desloca todos os itens a cima da posicao
    uma posicao para baixo.
    Subtrai 1 da variavel que indica o final ao retirar um item.
    \return item a ser retirado da posicao
    */
    T pop(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("lista vazia");
        } else {
            Node *anterior, *eliminar;
            T retorno;

            if (index > size_-1 || index < 0) {
                throw std::out_of_range("Erro posicao.");
            } else if (index == 0) {
                return(pop_front());
            } else if (index == size_) {
                return(pop_back());
            } else {
                anterior = head;

                for (int i = 0; i < index - 1 ; i++) {
                    anterior = anterior->next();
                }

                eliminar = anterior->next();

                retorno = eliminar->data();
                anterior->next(eliminar->next());

                delete eliminar;
                size_--;
                return retorno;
            }
        }
    }
    //! Metodo para retirar do fim.
    /*!
    reutiliza a funcao pop com o parametro do tamanho da lista -1
    */
    T pop_back() {
        return pop(size_ - 1);
    }
    //! Metodo para retirar do inicio.
    /*!
    verifica se a lista esta vazia antes de proceder, caso a lista estaja vazia retorna um erro.
    Tem como parametro de retorno o item no inicio da lista.
    Subtrai 1 da variavel que indica o final ao retirar um item.
    \return o primeiro item da lista
    */
    T pop_front() {
        if (empty()) {
            throw std::out_of_range("lista vazia");
        } else {
            Node *saida;
            T retorno;

            saida = head;
            retorno = saida->data();

            head = saida->next();
            delete saida;
            size_--;


            return retorno;
        }
    }
    //! Remove item especifico da lista
    /*!
        verifica se um item existe na lista
        verifica a posicao do item
        remove o item

        \param data a ser removido
    */
    void remove(const T& data) {
        pop(find(data));
    }
    //! Verifica lista vazia.
    /*!
    Metodo para verificar se a lista esta vazia. 
    Compara o tamanho da lista com 0.
    \return TRUE para lista vazia e FALSE para lista nao vazia
    */
    bool empty() const {
        return (size_ == 0);
    }
    //! Metodo para verificar item na lista
    /*!
    verifica se um item existe na lista

    \return TRUE para item existente , FALSE se o item nao existe
    */
    bool contains(const T& data) const {
        Node *dado;

        if (empty()) {
            throw std::out_of_range("lista vazia");
        } else {
            dado = head;
            for (int index = 0; index <= size_ - 1; index++) {
                if (dado->data() == data) {
                    return true;
                }
                dado = dado->next();
            }
            return false;
        }
    }
    //! Metodo para procurar um item.
    /*!
    Percorre a lista procurando o dado comparando-o com a amostra.
    \return a posicao do intem procurado
    */
    std::size_t find(const T& data) const {
        Node *dado;
        dado = head;
        if (empty()) {
            throw std::out_of_range("lista vazia");
        } else {
            for (int index = 0; index < size_ ; index++) {
                if (dado->data() == data) {
                    return index;
                }
                dado = dado->next();
            }
           return size_;
        }
    }
    //! Metodo para procurar um item.
    /*!
    Percorre a lista procurando o dado comparando-o com a amostra.
    \return a posicao do intem procurado
    */
    std::size_t size() const {
        return size_;
    }

 private:
    // Elemento
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        // getter: dado
        T& data() {
            return data_;
        }

        // getter const: dado
        const T& data() const {
            return data_;
        }

        // getter: próximo
        Node* next() {
            return next_;
        }

        // getter const: próximo
        const Node* next() const {
            return next_;
        }
        // setter: próximo
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };
    //  fim da classe do elemento

    Node* end() {
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }
    //  atributos da classe  lista

    Node* head{nullptr};  // _dados
    std::size_t size_{0u};  // _tamanho
    // fim dos atributos da lista
};  // fim da classe lista

}  // namespace structures

#endif



