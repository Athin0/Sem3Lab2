//
// Created by arina on 06.11.2021.
//

#ifndef SEM3LAB2_COMPARATORS_H
#define SEM3LAB2_COMPARATORS_H

#include "Histogram.h"

bool cmp(Pair_for_dict<int, int> pair1, Pair_for_dict<int, int> pair2) {
    return pair1.key > pair2.key;
}

bool cmp(Pair_for_dict<int, Person> pair1, Pair_for_dict<int, Person> pair2) {
    return pair1.key > pair2.key;
}

bool cmp(int a, int b) {
    return a > b;
}

bool cmp(Person a, Person b) {
    return a.GetBirthYear() > b.GetBirthYear();
}


#endif //SEM3LAB2_COMPARATORS_H
