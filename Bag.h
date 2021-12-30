//
// Created by arina on 10.11.2021.
//

#ifndef SEM3LAB2_BAG_H
#define SEM3LAB2_BAG_H

#include "Dictionary.h"

class object {
private:
    int weight = 0;
    int price = 0;
    int volume = 0;

public:
    object() {};

    object(int w, int p, int v) : weight(w), price(p), volume(v) {};

    int GetWeight() { return weight; }

    int GetPrice() { return price; }

    int GetVolume() { return volume; }

    friend
    std::ostream &operator<<(std::ostream &out, object object1) {
        return out << "{ weight: " << object1.GetWeight() << ",volume: " << object1.GetVolume() << ",price: "
                   << object1.GetPrice() << "}";
    }

    friend
    std::ostream &operator<<(std::ostream &out, object *object1) {
        return out << "{ weight: " << object1->GetWeight() << ",volume: " << object1->GetVolume() << ",price: "
                   << object1->GetPrice() << "}";
    }
};


class Bag {
public:
    int max_weight = 0;
    int max_volume = 0;
//Dictionary<int, int>* dictionary= nullptr;

public:
    Bag(int m_weight = 0, int m_volume = 0) : max_weight(m_weight), max_volume(m_volume) {};
};


bool rule_for_bag(ArraySequence<object *> *value, Bag bag) {
    int s_weight = 0, s_volume = 0;
    for (int i = 0; i < value->GetLength(); i++) {
        s_weight += value->Get(i)->GetWeight();
        s_volume += value->Get(i)->GetVolume();
        if (s_weight > bag.max_weight && s_volume > bag.max_volume) return false;
    }
    return true;
};


int GetSumPrice(ArraySequence<object *> *array_of_objects) {
    int price = 0;
    for (int i = 0; i < array_of_objects->GetLength(); i++) {
        price += array_of_objects->Get(i)->GetPrice();
    }
    return price;
}

#endif //SEM3LAB2_BAG_H
