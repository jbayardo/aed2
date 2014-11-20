#include "ColaDePrioridad.h"
#include <assert.h>

/*
* TODO: copy constructor. verificar que el algoritmo de borrado esta bien. escribir tests. verificar que bajar esta bien.
*/

template <typename T>
Heap<T>::~Heap() {
    // Usar una lista como stack para borrar.
}

template <typename T>
typename Heap<T>::Iterator Heap<T>::push(const T &data) {
    Node *tmp = new Heap<T>::Node(data);

    if (this->size() == 0) {
        this->head = tmp;
    } else if (this->size() == 1) {
        tmp->parent = this->head;
        this->head->left = tmp;
    } else {
        if (this->last->parent->left == this->last) {
            tmp->parent = this->last->parent;
            this->last->parent->right = tmp;
        } else {
            Node *cur = this->last;

            while (cur->parent != nullptr && cur->parent->left != cur) {
                cur = cur->parent;
            }

            if (cur->parent != nullptr) {
                cur = cur->parent->right;
            }

            while (cur->left != nullptr) {
                cur = cur->left;
            }

            tmp->parent = cur;
            cur->left = tmp;
        }
    }

    this->last = tmp;
    ++this->_size;

    up(this->last);
    return Heap<T>::Iterator(this, this->last);
}

template <typename T>
const T &Heap<T>::pop() {
    return remove(this->head);
}

template <typename T>
const T &Heap<T>::pop(const Heap<T>::Iterator &i) {
    assert(i.heap == this);

    return remove(i.node);
}

template <typename T>
void Heap<T>::up(Heap<T>::Node *node) {
    while (node->parent != nullptr && node->parent->data < node->data) {
        T tmp = node->parent->data;
        node->parent->data = node->data;
        node->data = tmp;
        node = node->parent;
    }
}

template <typename T>
void Heap<T>::down(Heap<T>::Node *node) {
    while ((node->left != nullptr && node->data < node->left->data) ||
        (node->right != nullptr && node->right->data < node->data)) {
        if (node->left != nullptr) {
            T tmp = node->left->data;
            node->left->data = node->data;
            node->data = tmp;
            node = node->left;
        } else {
            T tmp = node->right->data;
            node->right->data = node->data;
            node->data = tmp;
            node = node->right;
        }
    }
}


template <typename T>
const T &Heap<T>::remove(Heap<T>::Node *node) {
    // Pre: node esta en la estructura
    const T &tmp = node->data;

    if (this->size() == 1) {
        delete this->head;
        this->last = nullptr;
        this->head = nullptr;
    } else {
        node->data = this->last->data;
        Node *tmp = this->last;

        if (this->last->parent->left == this->last) {
            Node *cur = this->last;

            while (cur->parent != nullptr && cur->parent->right != cur) {
                cur = cur->parent;
            }

            if (cur->parent != nullptr) {
                cur = cur->parent->left;
            }

            while (cur->right != nullptr) {
                cur = cur->right;
            }

            this->last->parent->left = nullptr;
            this->last = cur;
        } else {
            this->last = this->last->parent->left;
            this->last->parent->right = nullptr;
        }

        if (node->data < node->parent->data) {
            down(node);
        } else {
            up(node);
        }

        delete tmp;
    }

    --this->_size;

    return tmp;
}

template <typename T>
unsigned int Heap<T>::size() const {
    return this->_size;
}
