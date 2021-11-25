//
// Created by arina on 04.11.2021.
//

#ifndef SEM3LAB2_DICTIONARY_H
#define SEM3LAB2_DICTIONARY_H

#include "Tree.h"


template<class TKey, class TElem>
struct Pair_for_dict {
    Pair_for_dict() = default;

    TKey key;
    TElem element;

    string to_string(Pair_for_dict &pair) {
        return (pair.key + " - " + pair.element);
    }

    Pair_for_dict(TKey key, TElem element) : key(key), element(element) {};

    explicit Pair_for_dict(TKey key) : key(key) {};

    TKey GetKey() {
        return key;
    }

    TKey GetElem() {
        return element;
    }

    friend std::ostream &operator<<(std::ostream &out, Pair_for_dict<TKey, TElem> pair) {
        return cout << pair.key << "-" << pair.element;
    };

};



template<class TKey, class TElem>
class Dictionary {
private:
    BinaryTree<Pair_for_dict<TKey, TElem>> *tree;

    bool (*cmp)(Pair_for_dict<TKey, TElem>, Pair_for_dict<TKey, TElem>);

public:
    Dictionary() {
    }

    Dictionary(TKey key, TElem element, bool (*cmp)(Pair_for_dict<TKey, TElem>, Pair_for_dict<TKey, TElem>)) {
        Pair_for_dict<TKey, TElem> initial(key, element);
        this->tree = new BinaryTree<Pair_for_dict<TKey, TElem>>(initial, cmp);
        this->cmp = cmp;
    }


    explicit Dictionary(bool (*cmp)(Pair_for_dict<TKey, TElem>, Pair_for_dict<TKey, TElem>)) {
        this->tree = new BinaryTree<Pair_for_dict<TKey, TElem>>(cmp);
        this->cmp = cmp;
    }

    //Dictionary(ArraySequence<TKey> array, bool (*cmp)(Pair_for_dict<TKey, TElem>, Pair_for_dict<TKey, TElem>)) {
    //    this->tree = new BinaryTree<Pair_for_dict<TKey, TElem>>(cmp);
    //    this->cmp = cmp;
    //}

    Dictionary(TKey *key, TElem *element, int num,
               bool (*cmp)(Pair_for_dict<TKey, TElem>, Pair_for_dict<TKey, TElem>)) {
        this->tree = new BinaryTree<Pair_for_dict<TKey, TElem>>(cmp);
        this->cmp = cmp;
        for (int i = 0; i < num; i++) {
            this->Add(key[i], element[i]);
        }
    }


    ~Dictionary() {
        delete tree;
    }

    int Count() {
        return tree->Check_count();
    }

    TElem Get(TKey input_key) {
        Pair_for_dict<TKey, TElem> pair_for_search;
        pair_for_search.key = input_key;
        if (tree->Find(pair_for_search))
            return (tree->GetNode(pair_for_search)).GetElem();
    }

    bool ContainsKey(TKey input_key) {
        Pair_for_dict<TKey, TElem> pair_for_search;
        pair_for_search.key = input_key;
        return tree->Find(pair_for_search);
    }

    void Add(TKey input_key, TElem input_element) {
        Pair_for_dict<TKey, TElem> for_add_pair(input_key, input_element);
        tree->Insert(for_add_pair);
    }


    void Add(Pair_for_dict<TKey, TElem> for_add_pair) {
        tree->Insert(for_add_pair);
    }

    void Remove(TKey input_key) {
        Pair_for_dict<TKey, TElem> for_remove_pair;
        for_remove_pair.key = input_key;
        tree->Remove(for_remove_pair);
    }


    void print() {
        auto arr = tree->GetKeyArray();
        for (int i = 0; i < arr.GetLength(); i++)
            cout << arr.Get(i) << "\n";
    }

    ArraySequence<Pair_for_dict<TKey, TElem>> Get() {
        return tree->GetKeyArray();
    }

    TKey FindMin() {

        return tree->FindMinInTree().key;
    }

    TKey FindMax() {
        return tree->FindMaxInTree().key;
    }
};

template<class T, class K>
std::ostream &operator<<(std::ostream &out, Dictionary<T, K> &diction) {
    diction.print();
    return out;
};


#endif //SEM3LAB2_DICTIONARY_H
