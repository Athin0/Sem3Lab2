//
// Created by arina on 20.11.2021.
//

#ifndef SEM3LAB2_MENUBAG_H
#define SEM3LAB2_MENUBAG_H

#include "ArraySequence.h"
#include "Bag.h"
#include "functions.h"
#include "N-tree.h"


object *EnterObject() {
    cout << "Введите вес объекта:";
    int weight = GetInt(0);
    cout << "Введите объем объекта:";
    int volume = GetInt(0);
    cout << "Введите ценность объекта:";
    int price = GetInt(0);

    auto temp_object = new object(weight, price, volume);
    return temp_object;
}

object *EnterObjectRand() {
    int weight = randomInt();
    int volume = randomInt();
    int price = randomInt();
    auto temp_object = new object(weight, price, volume);
    return temp_object;
}

template<class T>
ArraySequence<T *> *EnterElements() {
    auto array = new ArraySequence<T *>();
    cout << "\n Введите количество объектов:";
    int n = GetInt(0);
    //int n=4;
    for (int i = 0; i < n; i++) {
        auto object_temp = EnterObjectRand();
        array->Append(object_temp);
    }
    return array;
}


Bag EnterBag() {
    cout << "Введите максимально допустимый вес рюкзака:";
    int m_weight = GetInt(0);
    cout << "Введите объем рюкзака:";
    int m_volume = GetInt(0);

    return *(new Bag(m_weight, m_volume));
}

Dictionary<int, ArraySequence<object *> *> GetDecisions(ArraySequence<object *> *arrayObjects, Bag *bag) {
    NTree<object> tree(rule_for_bag);
    tree.Add(arrayObjects, bag);
    return Decision(tree);
};

template<class TKey, class TElem>
KeyValuePair<TKey, TElem> GetBestDecision(Dictionary<TKey, TElem> &dict) {
    auto arr = dict.Get();
//    KeyValuePair<TKey, TElem> ans = arr.Get(arr.GetLength() - 1);
    return arr.Get(arr.GetLength() - 1);
    //return ;
};

void menuBag() {
    auto objects = EnterElements<object>();
    cout << objects << "\n";
    auto bag = EnterBag();
    Dictionary<int, ArraySequence<object *> *> array = GetDecisions(objects, &bag);
    cout << "\n Answer\n " << array;
    auto bestDecision = GetBestDecision(array);
    cout << "\n Best Decision\n " << bestDecision;

}

#endif //SEM3LAB2_MENUBAG_H


