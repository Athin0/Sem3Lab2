//
// Created by arina on 25.11.2021.
//

#ifndef SEM3LAB2_FUNCTIONS_H
#define SEM3LAB2_FUNCTIONS_H


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

int GetInt(int down) {
    int k;
    k = GetInt();
    if (k < down) {
        cout << "Число вне диапозона. Повторите попытку\n";
        return GetInt(down);
    }
    return k;
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


#endif //SEM3LAB2_FUNCTIONS_H
