//
// Created by arina on 25.11.2021.
//

#ifndef SEM3LAB2_MENUHISTOGRAM_H
#define SEM3LAB2_MENUHISTOGRAM_H

#include "Person.h"
#include "Histogram.h"
#include "ArraySequence.h"


int GetInt() {
    while (true) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
    {
        int k;
        std::cin >> k;

        if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        } else {
            std::cin.ignore(32767, '\n'); // удаляем лишние значения
            return k;
        }
    }
}

int GetInt(int down, int up) {
    int k;
    k = GetInt();
    if (k < down || k > up) {
        cout << "Число вне диапозона. Повторите попытку\n";
        return GetInt(down, up);
    }
    return k;
}


ArraySequence<Person> GetPersonArray() {
    cout << "Для автоматического создания данных людей выберите 0,\n"
            " Для ручного ввода данных людей 1:";
    int n = GetInt(0, 1);
    cout << "Введите количество людей:";
    int count_of_people = GetInt();
    ArraySequence<Person> personArray;
    if (n) {
        Person person;
        for (int i = 0; i < count_of_people; i++) {
            person = createPerson();
            personArray.Append(person);
        }
    } else if (!n) {
        string names[] = {"Artemida", "Ares", "Aid", "Neptun", "Zeus", "Gera", "Athina", "Germes", "Dionis", "Afrodita",
                          "Gefest"};
        int years[] = {2002, 2001, 2005, 2002, 2056, 2004, 2002, 2006, 1998, 1990, 2001};
        for (int i = 0; i < count_of_people; i++) {
            Person man(names[i % 11], randomInt());  //years[i%11]
            personArray.Append(man);
        }
    }
    return personArray;
}

Dictionary<int, int> GetHistogram(ArraySequence<Person> PersonArray) {
    Histogram<Person> *a = new Histogram<Person>(GetIntFromPerson, cmp);
    for (int i = 0; i < PersonArray.GetLength(); i++)
        a->Add(PersonArray[i]);

    cout << "Выберите: \n "
            "1)равномерное разбиение,\n "
            "2)неравномерное разбиение"
         << endl;
    int n = GetInt(1, 2);
    if (n == 1) {
        cout << "Введите диапазон разбиения:";
        int range = GetInt();
        return a->even_partition(range);
    } else {
        ArraySequence<int> timeArr1;
        cout << "Количество промежутков разбиения";
        int countOfInterval = GetInt();

        cout << "Укажите сами промежутки разбиения разбиения:";
        for (int i = 0; i < countOfInterval + 1; i++) {
            int number = GetInt();
            timeArr1.Append(number);
        }
        return a->uneven_partition(timeArr1);

    }
}

void menuHistogram() {
    auto PersonArray = GetPersonArray();
    cout << PersonArray << endl;
    auto b = GetHistogram(PersonArray);
    cout << b;

}

#endif //SEM3LAB2_MENUHISTOGRAM_H
