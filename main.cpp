
#include <iostream>
#include "menuBag.h"

#include "menuHistogram.h"
#include "FibQueue.h"

int main() {
    //menuHistogram();
    //menuBag();
    FibHeap<int> a(cmp);
    for (int i = 0; i < 30; i++) {
        a.add(i * 31 + 2);
    }
    a.extractMin();
    printFibQueue(&a);
    a.Deletion(64);
    printFibQueue(&a);
    return 0;
}




//bool rule(ArraySequence<Person> value) {
//    if (value.GetLength() <= 1) return true;
//    for (int i = 0; i < value.GetLength(); i++) {
//        for (int j = i + 1; j < value.GetLength(); j++)
//            if ((value.Get(i).GetBirthYear() != value.Get(j).GetBirthYear()) || (value.Get(i) == value.Get(j)))
//                return false;
//    }
//    return true;
//};


/*
 * int arr1[] = {1, 2, 3, 4, 7};
    int arr2[] = {1, 2, 3, 4, 7};

    Person man1("Arur", 2003);
    Person man2("Rey", 1987);
    Person man3("Wey", 2003);
    Person name[] = {man1, man2, man3};
    ArraySequence<Person> personsArr(name, 3);
    string names[] = {"Artemida", "Ares", "Aid", "Neptun", "Zeus", "Gera", "Athina", "Germes", "Dionis", "Afrodita",
                      "Gefest"};
    int years[] = {2002, 2001, 2005, 2002, 2056, 2004, 2002, 2006, 1998, 1990, 2001};
    for (int i = 0; i < 11; i++) {
        Person man(names[i], years[i]);
        personsArr.Append(man);
    }

     int time[] = {2000, 2005, 2017, 2090};
    ArraySequence<int> timeArr(time, 4);

    Dictionary<int, Person> dictionary(arr1, name, 3, cmp);

    Histogram<Person> *a = new Histogram<Person>(GetIntFromPerson, cmp);
    for (int i = 0; i < personsArr.GetLength(); i++)
        a->Add(personsArr[i]);
    auto b = a->uneven_partition(timeArr);
    b->print();

    Node<Person> desidetree(rule);
    desidetree.Add(personsArr);
    desidetree.print();
    cout << personsArr;


 */

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