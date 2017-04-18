//!  Copyright [2017] <Copyright relldaXY>"
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! Class LinkedList
/*!
 *  this is a list linked by reference. It has functions like push, pop, insert 
 *  and some like that. 
*/
class LinkedList {
 public:
    LinkedList() {
        head = NULL;
        size_ = -1;
    }
    ~LinkedList() {
        clear();
    }
    //! method clear
    /*!
        While the list is empty is false the elements go out from list
    */
    void clear() {
        while (!empty()) {
            pop_front();
        }
        size_ = -1;
    }
    //! method push_back.
    /*!
        put elements to back from list.
    */
    void push_back(const T& data) {
        insert(data, size_+1);
    }
    //! method push_front.
    /*!
        put elements to front from list.
    */
    void push_front(const T& data) {
        Node* newNode = new Node(data, NULL);
        if (newNode == NULL) {
            throw std::out_of_range("Full list");
        } else {
            if (empty()) {
                head = newNode;
                size_++;
            } else {
                newNode -> next(head);
                head = newNode;
                size_++;
            }
        }
    }
    //! method insert.
    /*!
        insert to list by index.
    */
    void insert(const T& data, std::size_t index) {
        if (index > (size_+1)|| index < 0) {
            throw std::out_of_range("Invalid index");
        } else if (index == 0) {
            push_front(data);
        } else {
            Node *previous, *newNode;
            newNode = new Node(data, NULL);
            if (newNode == NULL) {
                throw std::out_of_range("Full memory");
            }
            previous = head;
            for (int i = 1; i < index; i++) {
                previous = previous->next();
            }
            newNode = new Node(data, NULL);
            newNode->next(previous->next());
            previous->next(newNode);
            size_++;
        }
    }
    //! method insert.
    /*!
        insert and sort to list.
    */
    void insert_sorted(const T& data) {
        Node *current;
        int pos = 0;
        if (empty()) {
            push_front(data);
        } else {
            current = head;
            while (current->next() != NULL && data > current->data()) {
                current = current->next();
                pos++;
            }
            if (data > current->data()) {
                insert(data, (size_+1) );
            } else {
                insert(data, pos);
            }
        }
    }
    //! method at.
    /*!
        return data by index.
    */
    T& at(std::size_t index) {
        Node* previousNode;
        if (index < 0 || index > size_) {
            throw std::out_of_range("Invalid index");
        } else {
            if (index == 0) {
                return head -> data();
            } else {
                previousNode = head;
            for (int i = 1; i <= index; i++) {
                previousNode = previousNode->next();
            }
            return previousNode->data();
            }
        }
    }
    //! method pop.
    /*!
        pop itens by index.
    */
    T pop(std::size_t index) {
        Node* previousNode, *deleteNode;
        T data;
        if (index < 0 || index > size_) {
            throw std::out_of_range("Invalid index");
        } else {
        if (index == 0) {
            return pop_front();
        } else {
            previousNode = head;
            for (int i = 1; i < index; i++) {
                previousNode = previousNode -> next();
            }
            deleteNode = previousNode -> next();
            data = deleteNode -> data();
            previousNode -> next(deleteNode->next());
            size_--;
            delete deleteNode;
            return data;
        }
        }
    }
    //! method pop_back.
    /*!
        pop the last element from list.
    */
    T pop_back() {
       if (size_== -1) {
            throw std::out_of_range("Empty list");
       } else {
           return pop(size_);
       }
    }
    //! method pop_front.
    /*!
        pop the first element from list
    */
    T pop_front() {
        if (empty()) {
            throw std::out_of_range("Empty List");
        } else {
            Node* quitNode;
            T data;
            data = head->data();
            quitNode = head;
            head = quitNode->next();
            delete quitNode;
            size_--;
            return data;
        }
    }
    //! method remove.
    /*!
        remove an element from list
    */
    void remove(const T& data) {
        Node *previousNode, *deleteNode;
        int index = find(data);
        if (empty()) {
            throw std::out_of_range("List empty");
        } else if (index == 0) {
            pop_front();
        } else if (index == 1 && size()== 2) {
            T dataAux = pop_front();
            pop_front();
            push_front(dataAux);
        } else {
            previousNode = head;
            for (int i = 1; i < index; i++) {
                previousNode = previousNode->next();
            }
            deleteNode = previousNode->next();
            previousNode->next(deleteNode->next());
            delete deleteNode;
            size_--;
        }
    }
    //! method empty.
    /*!
        to know if the list is empty.
    */
    bool empty() const {
        return size_ == -1;
    }
    //! method contains.
    /*!
        verify is data is in the list.
    */
    bool contains(const T& data) const {
        Node *current;
        if (empty()) {
            throw std::out_of_range("Empty list");
        } else {
            current = head;
            while (current->next() != NULL) {
                if (current->data() == data) {
                    return true;
                } else {
                    current = current->next();
                }
            }
            return false;
        }
    }
    //! method find.
    /*!
        get the index of data from list.
    */
    std::size_t find(const T& data) const {
        Node* dataNode;
        if (empty()) {
            throw std::out_of_range("Empty list");
        } else {
            dataNode = head;
            for (int i = 0; i <= size_ ; i++) {
                if (dataNode->data() == data) {
                    return i;
                } else {
                    dataNode = dataNode->next();
                }
            }
        }
        return size();
    }
    //! method size.
    /*!
        return the number of elements.
    */
    std::size_t size() const {
        return (size_+1);
    }

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {   // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
