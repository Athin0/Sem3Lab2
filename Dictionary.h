//
// Created by arina on 04.11.2021.
//

#ifndef SEM3LAB2_DICTIONARY_H
#define SEM3LAB2_DICTIONARY_H

#include "Tree.h"


template<class TKey, class TElem>
struct KeyValuePair {       //KeyValuePair
    KeyValuePair() = default;

    TKey key;
    TElem element;

    std::string to_string(KeyValuePair &pair) {
        return (pair.key + " - " + pair.element);
    }

    KeyValuePair(TKey key, TElem element) : key(key), element(element) {};

    explicit KeyValuePair(TKey key) : key(key) {};

    TKey GetKey() {
        return key;
    }

    TKey GetElem() {
        return element;
    }


};

template<class TKey, class TElem>
std::ostream &operator<<(std::ostream &out, KeyValuePair<TKey, TElem> pair) {
    return cout << pair.key << "-" << pair.element;
};


template<class TKey, class TElem>
class Dictionary {
private:
    BinaryTree<KeyValuePair<TKey, TElem>> *tree;

    bool (*cmp)(KeyValuePair<TKey, TElem>, KeyValuePair<TKey, TElem>);

public:
    Dictionary() {
    }

    Dictionary(TKey key, TElem element, bool (*cmp)(KeyValuePair<TKey, TElem>, KeyValuePair<TKey, TElem>)) {
        KeyValuePair<TKey, TElem> initial(key, element);
        this->tree = new BinaryTree<KeyValuePair<TKey, TElem>>(initial, cmp);
        this->cmp = cmp;
    }


    explicit Dictionary(bool (*cmp)(KeyValuePair<TKey, TElem>, KeyValuePair<TKey, TElem>)) {
        this->tree = new BinaryTree<KeyValuePair<TKey, TElem>>(cmp);
        this->cmp = cmp;
    }

    //Dictionary(ArraySequence<TKey> array, bool (*cmp)(KeyValuePair<TKey, TElem>, KeyValuePair<TKey, TElem>)) {
    //    this->tree = new BinaryTree<KeyValuePair<TKey, TElem>>(cmp);
    //    this->cmp = cmp;
    //}

    Dictionary(TKey *key, TElem *element, int num,
               bool (*cmp)(KeyValuePair<TKey, TElem>, KeyValuePair<TKey, TElem>)) {
        this->tree = new BinaryTree<KeyValuePair<TKey, TElem>>(cmp);
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
        KeyValuePair<TKey, TElem> pair_for_search;
        pair_for_search.key = input_key;
        if (tree->Find(pair_for_search))
            return (tree->GetNode(pair_for_search)).GetElem();
        return TElem();
    }

    bool ContainsKey(TKey input_key) {
        KeyValuePair<TKey, TElem> pair_for_search;
        pair_for_search.key = input_key;
        return tree->Find(pair_for_search);
    }

    void Add(TKey input_key, TElem input_element) {
        KeyValuePair<TKey, TElem> for_add_pair(input_key, input_element);
        tree->Insert(for_add_pair);
    }


    void Add(KeyValuePair<TKey, TElem> for_add_pair) {
        tree->Insert(for_add_pair);
    }

    void Remove(TKey input_key) {
        KeyValuePair<TKey, TElem> for_remove_pair;
        for_remove_pair.key = input_key;
        tree->Remove(for_remove_pair);
    }


    void print() {
        auto arr = tree->GetKeyArray();
        for (int i = 0; i < arr.GetLength(); i++)
            cout << arr.Get(i) << "\n";
    }

    ArraySequence<KeyValuePair<TKey, TElem>> Get() {
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
