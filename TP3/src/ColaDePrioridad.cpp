#include "../include/ColaDePrioridad.h"

template <typename T>
typename Heap<T>::Iterator Heap<T>::push(const T &data)
{
    Node *tmp = new Heap<T>::Node(data);

    if (this->size() == 0) {
        this->head = tmp;
    }
    else if (this->size() == 1) {
        tmp->parent = this->head;
        this->head->left = tmp;
    }
    else {
        if (this->last->parent->left == this->last) {
            tmp->parent = this->last->parent;
            this->last->parent->right = tmp;
        }
        else {
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
    // TODO: this should be implemented correctly.
    return Heap<T>::Iterator(this, this->last);
}

template <typename T>
const T &Heap<T>::pop()
{
    return remove(this->head);
}

template <typename T>
const T &Heap<T>::pop(const Heap<T>::Iterator &i)
{
    return remove(i.node);
}

template <typename T>
void Heap<T>::up(Heap<T>::Node *node)
{
    while (node->parent != nullptr && node->parent->data < node->data) {
        T tmp = node->parent->data;
        node->parent->data = node->data;
        node->data = tmp;
        node = node->parent;
    }
}

template <typename T>
void Heap<T>::down(Heap<T>::Node *node)
{
    while ((node->left != nullptr && node->data < node->left->data) ||
            (node->right != nullptr && node->right->data < node->data)) {
        if (node->left != nullptr) {
            T tmp = node->left->data;
            node->left->data = node->data;
            node->data = tmp;
            node = node->left;
        }
        else {
            T tmp = node->right->data;
            node->right->data = node->data;
            node->data = tmp;
            node = node->right;
        }
    }
}


// TODO: limpieza de memoria
template <typename T>
const T &Heap<T>::remove(Heap<T>::Node *node)
{
    const T &tmp = node->data;

    if (this->size() == 1) {
        this->last = nullptr;
        this->head = nullptr;
    }
    else {
        node->data = this->last->data;

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
        }
        else {
            this->last = this->last->parent->left;
            this->last->parent->right = nullptr;
        }

        down(node);
    }

    --this->_size;

    return tmp;
}

template <typename T>
unsigned int Heap<T>::size() const
{
    return this->_size;
}
