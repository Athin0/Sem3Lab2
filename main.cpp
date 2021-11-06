#include <iostream>
#include "ArraySequence.h"
#include "Person.h"
#include "Tree.h"
#include "Dictionary.h"
#include "Histogram.h"
#include "Comparators.h"

int GetIntFromPerson(Person men) {
    return men.GetBirthYear();
}

int main() {
    int arr1[] = {1, 2, 3, 4, 7};
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

    Dictionary<int, Person> dictionary(arr1, name, 3, cmp);
    dictionary.Print();

    Histogram<Person> *a = new Histogram<Person>(GetIntFromPerson, cmp);
    for (int i = 0; i < personsArr.GetLength(); i++)
        a->Add(personsArr[i]);
    auto b = a->even_partition(1987, 2056, 2);
    b->Print();

    cout << personsArr;
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