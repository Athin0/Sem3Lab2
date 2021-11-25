//
// Created by arina on 03.11.2021.
//

#ifndef SEM3LAB2_PERSON_H
#define SEM3LAB2_PERSON_H

#include "string"

struct Person {
private:
    string FirstName = "";
    string MiddleName = "";
    string LastName = "";
    int BirthYear = 0;
public:
    Person(string First, string Middle, string Last, int Year) : FirstName(First), MiddleName(Middle), LastName(Last),
                                                                 BirthYear(Year) {};

    Person(string First, string Last, int Year) : FirstName(First), LastName(Last), BirthYear(Year) {};

    Person(string First, int Year) : FirstName(First), BirthYear(Year) {};

    Person() = default;;

    ~Person() = default;;

    string GetFirstName() {
        return FirstName;
    };

    string GetMiddleName() {
        return MiddleName;
    };

    string GetLastName() {
        return LastName;
    };

    string GetFullName() {
        return (FirstName + " " + MiddleName + " " + LastName);
    };

    string GetFIO() {
        return (FirstName + " " + MiddleName[0] + "." + LastName[0] + ".");
    };

    int GetBirthYear() {
        return BirthYear;
    };

    int Getyear(int year) {
        return (year - BirthYear);
    }

    void SetFirstName(string name) {
        this->FirstName = name;
    }

    void SetMiddleName(string name) {
        this->MiddleName = name;
    }

    void SetLastName(string name) {
        this->LastName = name;
    }

    void SetBirthYear(int year) {
        this->BirthYear = year;
    }

    bool operator==(const Person another) {
        if (FirstName != another.FirstName) return false;
        if (MiddleName != another.MiddleName) return false;
        if (LastName != another.LastName) return false;
        if (BirthYear != another.BirthYear) return false;
        return true;
    }

    bool operator!=(const Person another) {
        if (FirstName != another.FirstName) return true;
        if (MiddleName != another.MiddleName) return true;
        if (LastName != another.LastName) return true;
        if (BirthYear != another.BirthYear) return true;
        return false;
    }
};

std::ostream &operator<<(std::ostream &out, Person person) {
    return out << "{" << person.GetFullName() << ", " << person.GetBirthYear() << "}";
}

string to_string(Person &person) {
    return person.GetFullName();
}

//
//std::ostream &operator>>(std::ostream &in, Person person) {
//    string name;
//    int year;
//    cout << "Enter name: ";
//    cin >> name;
//    cout << endl;
//    cout << "Enter Birthday year: ";
//    cin >> year;
//    cout << endl;
//    person.SetFirstName(name);
//    person.SetBirthYear(year);
//    return in;
//}


Person createPerson() {
    string name;
    int year;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter Birthday year: ";
    cin >> year;
    return *(new Person(name, year));
}


int GetIntFromPerson(Person men) {
    return men.GetBirthYear();
}


#endif //SEM3LAB2_PERSON_H

