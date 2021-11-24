//
// Created by arina on 07.11.2021.
//

#ifndef SEM3LAB2_N_TREE_H
#define SEM3LAB2_N_TREE_H

#include "Comparators.h"
#include "ArraySequence.h"
#include "Bag.h"
#include "Dictionary.h"

template<class T>
class Node {
private:
    ArraySequence<Node *> children;
    ArraySequence<T> value;

    bool (*rule)(ArraySequence<T> value, Bag bag);

public:

//    Node() {
//children= nullptr;
//value= nullptr;
//};

    Node(bool (*rule)(ArraySequence<T> value, Bag bag)) : rule(rule) {};

    void AddToNode(ArraySequence<T> *elements, Bag *bag) {
        for (int i = 0; i < elements->GetLength(); i++) {
            auto node = new Node<T>(rule);
            node->value = value;
            node->value.Append(elements->Get(i));
            if (rule((node->value), *bag)) {
                children.Append(node);
            } else
                delete node;
        }
    };

    void Add(ArraySequence<T> *elements, Bag *bag) {
        if (!children.GetLength()) {
            for (int i = 0; i < elements->GetLength(); i++) {
                auto node = new Node<T>(rule);
                node->value = value;
                node->value.Append(elements->Get(i));
                if (rule((node->value), *bag)) {
                    children.Append(node);
                } else
                    delete node;
            }
        }
        for (int i = 0; i < children.GetLength(); i++) {
            children.Get(i)->AddToNode(elements, bag);
            children.Get(i)->Add(elements, bag);
        }
    };

    void print(int n = 0) {

        for (int k = 0; k < n; k++)
            cout << "      ";
        cout << value << " \n";

        for (int i = 0; i < children.GetLength(); i++) {
            children.Get(i)->print(n + 1);
        }
    };

    friend std::ostream &operator<<(std::ostream &out, Node<T> *ntree) {
        return cout << ntree->value;
    };

    friend std::ostream &operator<<(std::ostream &out, Node<T> ntree) {
        return cout << ntree.value;
    };

    void GetArray(ArraySequence<ArraySequence<T>> *array) {
        if (children.GetLength() == 0) {
            array->Append(value);
            return;
        }
        for (int i = 0; i < children.GetLength(); i++)
            children.Get(i)->GetArray(array);
    }
};


template<class T>
class NTree {
private:
    Node<T> *root;
public:
    NTree(bool (*rule)(ArraySequence<T> value, Bag bag)) {
        root = new Node<T>(rule);
    }

    void Add(ArraySequence<T> *elements, Bag *bag) {
        root->Add(elements, bag);
    };

    ArraySequence<ArraySequence<T>> Get() {
        ArraySequence<ArraySequence<T>> array;
        root->GetArray(&array);
        return array;
    }

    friend std::ostream &operator<<(std::ostream &out, NTree<T> ntree) {
        ntree.root->print();
        return out;
    };

    friend std::ostream &operator<<(std::ostream &out, NTree<T> *ntree) {
        ntree->root->print();
        return out;
    };
};

bool cmpObjectsArray(Pair_for_dict<int, ArraySequence<object>> pair1, Pair_for_dict<int, ArraySequence<object>> pair2) {
    return pair1.key > pair2.key;
}


template<class T>
Dictionary<int, ArraySequence<T>> Decision(NTree<T> ntree) {
    Dictionary<int, ArraySequence<T>> decision(cmpObjectsArray);
    ArraySequence<ArraySequence<T>> array = ntree.Get();
    for (int i = 0; i < array.GetLength(); i++) {
        decision.Add(GetSumPrice(array.Get(i)), array.Get(i));
    }
    return decision;
}

#endif //SEM3LAB2_N_TREE_H
