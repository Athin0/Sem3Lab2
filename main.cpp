#include <iostream>
#include "ArraySequence.h"
#include "Person.h"
#include "Tree.h"
#include "Dictionary.h"

bool cmp(Pair_for_dict<int, int> pair1, Pair_for_dict<int, int> pair2) {
    return pair1.key > pair2.key;
}

bool cmp(Pair_for_dict<int, Person> pair1, Pair_for_dict<int, Person> pair2) {
    return pair1.key > pair2.key;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 7};
    int arr2[] = {1, 2, 3, 4, 7};
    int arr[] = {1, 2, 3, 4, 7};
    Person man1("Arur", 2003);
    Person man2("Rey", 1987);
    Person man3("Wey", 2000);
    Person name[] = {man1, man2, man3};

    Dictionary<int, Person> dictionary(arr1, name, 3, cmp);
    dictionary.Print();
    return 0;
}

//int arr[]={1,2,3,4,7};
//    ArraySequence<int> a(arr,5);
//    ArraySequence<int> b;
//    b.RandonSequence();
//    a.Concat(&b);
//    cout<<a;
//



//    BinaryTree<int> numbers(arr,5);
//    cout<<tree;
//    cout<< numbers;