//
// Created by arina on 07.11.2021.
//

#ifndef SEM3LAB2_N_TREE_H
#define SEM3LAB2_N_TREE_H

#include "Comparators.h"
#include "ArraySequence.h"

template<class T>
class Node {
private:
    ArraySequence<Node> children;
    ArraySequence<T> value;

    bool (*rule)(ArraySequence<T> value);

public:

    ~Node() {
        //delete children;
        //delete value;
    };

    Node() {};

    Node(bool (*rule)(ArraySequence<T> value)) : rule(rule) {};

    void AddToNode(ArraySequence<T> elements) {
        for (int i = 0; i < elements.GetLength(); i++) {
            auto node = new Node<T>();
            node->value = this->value;
            node->value.Append(elements.Get(i));
            if (rule(node->value)) {
                this->children.Append(*node);
            } else
                delete node;
        }
    };

    void Add(ArraySequence<T> elements) {
        if (!children.GetLength()) {
            for (int i = 0; i < elements.GetLength(); i++) {
                auto node = new Node<T>();
                node->value.Append(elements.Get(i));
                if (rule(node->value)) {
                    this->children.Append(*node);
                } else
                    delete node;
            }

        }
        for (int i = 1; i < children.GetLength(); i++) {
            children.Get(i).AddToNode(elements);
            children.Get(i).Add(elements);
        }
    };

    void print() {
        cout << value << "  ";
        for (int i = 0; i < children.GetLength(); i++) {
            children.Get(i).print();
        }
        cout << "\n";
    };
};


template<class T>
class NTree {
private:
    Node<T> *root;
public:
    NTree(bool (*rule)(ArraySequence<T> value)) {
        root = new Node<T>(rule);
    }
};

#endif //SEM3LAB2_N_TREE_H
