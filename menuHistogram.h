//
// Created by arina on 25.11.2021.
//

#ifndef SEM3LAB2_MENUHISTOGRAM_H
#define SEM3LAB2_MENUHISTOGRAM_H

#include "Person.h"
#include "Histogram.h"
#include "ArraySequence.h"
#include "functions.h"
#include "Comparators.h"
#include "fstream"

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::string;
using std::cin;

const char *PATH_FILE = "C:\\Users\\arina\\mommy\\Projects\\Gist\\Sem3Lab4\\file0.txt";
const char *PATH_FILE_TO = "C:\\Users\\arina\\mommy\\Projects\\Gist\\Sem3Lab4\\fileTO.txt";

ifstream fin; //откуда
ofstream fout; //куда


Person createPersonFile() {
    string name;
    int year;
    fin >> name;
    fin >> year;
    return *(new Person(name, year));
}

Person createPersonToFile() {
    string name;
    int year;
    cout << "Enter name: ";
    cin >> name;
    fout << name << ' ';
    cout << "Enter Birthday year: ";
    cin >> year;
    fout << year;
    fout << endl;
    return *(new Person(name, year));
}

template<class T>
Dictionary<T, T> makeHistogram(string path) {
    fin.open(path);
    if (fin.is_open()) {

        //создание массива людей
        int n;
        fin >> n;   //Для автоматического создания данных людей выберите 0,
        // Для ручного ввода данных людей 1:";
        int count_of_people;
        fin >> count_of_people; // "Введите количество людей:";
        ArraySequence<Person> personArray;
        if (n) {    //ввод руками
            Person person;
            for (int i = 0; i < count_of_people; i++) {
                person = createPersonFile();
                personArray.Append(person);
            }
        } else if (!n) {   //ввод автоматический
            string names[] = {"Artemida", "Ares", "Aid", "Neptun", "Zeus", "Gera", "Athina", "Germes", "Dionis",
                              "Afrodita",
                              "Gefest"};
            int years[] = {2002, 2001, 2005, 2002, 2056, 2004, 2002, 2006, 1998, 1990, 2001};
            for (int i = 0; i < count_of_people; i++) {
                Person man(names[i % 11], randomInt());  //years[i%11]
                personArray.Append(man);
            }
        }
        //return personArray;


        //Создание гистограммы

        auto PersonArray = personArray;
        Histogram<Person> *a = new Histogram<Person>(GetIntFromPerson, cmp);
        for (int i = 0; i < PersonArray.GetLength(); i++)
            a->Add(PersonArray[i]);
        while (true) {
            //cout << "Выберите: \n "
            //        "0)вывести гистограмму, \n "
            //        "1)равномерное разбиение,\n "
            //        "2)неравномерное разбиение"
            //     << endl;
            int n;
            fin >> n;
            if (n == 0) {
                return a->GetDictionary();
            } else if (n == 1) {
                //cout << "Введите диапазон разбиения:";
                int range;
                fin >> range;
                return a->even_partition(range);
            } else {
                ArraySequence<int> timeArr1;
                //cout << "Количество промежутков разбиения";
                int countOfInterval;
                fin >> countOfInterval;

                //cout << "Укажите сами промежутки разбиения разбиения:";
                for (int i = 0; i < countOfInterval + 1; i++) {
                    int number;
                    fin >> number;
                    timeArr1.Append(number);
                }
                return a->uneven_partition(timeArr1);

            }
        }


        fin.close();     // закрываем файл

    } else {
        std::cout << " Что-то пошло не так в чтении файла" << std::endl;
    }
}


/*
ArraySequence<Person> GetPersonArray() {
    cout << "Для автоматического создания данных людей выберите 0,\n"
            " Для ручного ввода данных людей 1:";
    int n = GetInt(0, 1);
    cout << "Введите количество людей:";
    int count_of_people = GetInt();
    ArraySequence<Person> personArray;
    if (n) {    //ввод руками
        Person person;
        for (int i = 0; i < count_of_people; i++) {
            person = createPerson();
            personArray.Append(person);
        }
    } else if (!n) {   //ввод автоматический
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
    while (true) {
        cout << "Выберите: \n "
                "0)вывести гистограмму, \n "
                "1)равномерное разбиение,\n "
                "2)неравномерное разбиение"
             << endl;
        int n = GetInt(0, 2);
        if (n == 0) {
            return a->GetDictionary();
        } else if (n == 1) {
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
}

void menuHistogram() {
    auto PersonArray = GetPersonArray();
    cout << PersonArray << endl;
    while (true) {
        auto b = GetHistogram(PersonArray);
        cout << b;
        cout << "Чтобы выйти 0, иначе продолжить:";
        int n = GetInt();
        if (n == 0) return;
    }

    //Dictionary<int,int> b = makeHistogram<int>(PATH_FILE);
    //cout << b;
}
*/
ArraySequence<Person> *GetPersonArray() {
    fout.open(PATH_FILE_TO);
    if (fout.is_open()) {
        cout << "Для автоматического создания данных людей выберите 0,\n"
                " Для ручного ввода данных людей 1:";
        int n = GetInt(0, 1);
        fout << n << endl;
        cout << "Введите количество людей:";
        int count_of_people = GetInt();
        fout << count_of_people << endl;
        auto personArray = new ArraySequence<Person>;
        if (n) {    //ввод руками
            Person person;
            for (int i = 0; i < count_of_people; i++) {
                person = createPersonToFile();
                personArray->Append(person);
            }
        } else if (!n) {   //ввод автоматический
            string names[] = {"Artemida", "Ares", "Aid", "Neptun", "Zeus", "Gera", "Athina", "Germes", "Dionis",
                              "Afrodita",
                              "Gefest"};
            int years[] = {2002, 2001, 2005, 2002, 2056, 2004, 2002, 2006, 1998, 1990, 2001};
            for (int i = 0; i < count_of_people; i++) {
                Person man(names[i % 11], randomInt());  //years[i%11]
                personArray->Append(man);
            }
        }

        return personArray;
    } else {
        std::cout << " Что-то пошло не так в чтении файла GetPersonArray " << std::endl;
        return nullptr;
    }
}

Dictionary<int, int> GetHistogram(ArraySequence<Person> *PersonArray) {
    if (fout.is_open()) {
        Histogram<Person> *a = new Histogram<Person>(GetIntFromPerson, cmp);
        for (int i = 0; i < PersonArray->GetLength(); i++)
            a->Add(PersonArray->Get(i));
        while (true) {
            cout << "Выберите: \n "
                    "0)вывести гистограмму, \n "
                    "1)равномерное разбиение,\n "
                    "2)неравномерное разбиение"
                 << endl;
            int n = GetInt(0, 2);
            fout << n << endl;
            if (n == 0) {
                return a->GetDictionary();
            } else if (n == 1) {
                cout << "Введите диапазон разбиения:";
                int range = GetInt();
                fout << range << endl;
                return a->even_partition(range);
            } else {
                ArraySequence<int> timeArr1;
                cout << "Количество промежутков разбиения";
                int countOfInterval = GetInt();
                fout << countOfInterval << endl;
                cout << "Укажите сами промежутки разбиения разбиения:";
                for (int i = 0; i < countOfInterval + 1; i++) {
                    int number = GetInt();
                    fout << number << endl;
                    timeArr1.Append(number);
                }
                return a->uneven_partition(timeArr1);

            }
        }
        fout.close();     // закрываем файл
    } else {
        std::cout << " Что-то пошло не так в чтении файла GetHistogram " << std::endl;
        return Dictionary<int, int>();
    }
}

void menuHistogram() {
    auto PersonArray = GetPersonArray();
    cout << PersonArray << endl;
    while (true) {
        auto b = GetHistogram(PersonArray);
        cout << b;
        cout << "Чтобы выйти 0, иначе продолжить:";
        int n = GetInt();
        if (n == 0) return;
    }

    Dictionary<int, int> b = makeHistogram<int>(PATH_FILE);
    cout << b;
}

#endif //SEM3LAB2_MENUHISTOGRAM_H
