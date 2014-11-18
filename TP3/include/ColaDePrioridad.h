#ifndef HEAP_H
#define HEAP_H 1

template <typename T>
class Heap {
private:
    class Node {
    public:
        Node(const T &data) : data(data), parent(nullptr), left(nullptr), right(nullptr)
        { };

        T data;
        Node *parent;
        Node *left;
        Node *right;
    };

    const T &remove(Node *);
    void up(Node *);
    void down(Node *);

    Node *head;
    Node *last;
    unsigned int _size;
public:
    class Iterator {
        friend class Heap;
    private:
        Iterator(Node *node) : node(node) { }

        Node *node;
    };

    Heap() : _size(0), head(nullptr), last(nullptr) { }

    Heap<T>::Iterator push(const T &);
    const T &pop();
    const T &pop(const Iterator &);
    unsigned int size() const;
};

#endif
