//
// Created by arina on 03.11.2021.
//

#ifndef SEM3LAB2_ARRAYSEQUENCE_H
#define SEM3LAB2_ARRAYSEQUENCE_H

#include "DynamicArray.h"

int MAX_INT = 3000;//INT32_MAX;
using std::cout;

int randomInt() {
    return rand() % MAX_INT;
}

template<class T>
class ArraySequence {
private:
    DynamicArray<T> dynamicArray;
public:
    class IndexOutOfRange {
    private:
        int length;
        int index;
    public:
        IndexOutOfRange(int length, int index) : length(length), index(index) {};

        IndexOutOfRange() : length(-1), index(-1) {};
    };


    ArraySequence() {
        dynamicArray = DynamicArray<T>();
    }


    ArraySequence(T *items, int count) {   //создание из массива
        dynamicArray = DynamicArray<T>(items, count);
    }

    ArraySequence(const DynamicArray<T> &array) {
        dynamicArray = array;
    }

    ArraySequence(const ArraySequence<T> &array) {
        dynamicArray = array.dynamicArray;
    }


    T GetFirst() {
        if (GetLength() == 0)
            throw IndexOutOfRange(GetLength(), 0);
        return dynamicArray.Get(0);
    }

    T GetLast() {
        if (GetLength() == 0)
            throw IndexOutOfRange(GetLength(), -1);
        return dynamicArray.Get(dynamicArray.GetLength() - 1);
    }

    T Get(int index) const {
        if (index < 0 || index >= GetLength())
            throw IndexOutOfRange(GetLength(), index);
        return dynamicArray.Get(index);
    }

    void Set(int index, T item) {
        if (index < 0 || index >= GetLength())
            throw IndexOutOfRange(GetLength(), index);
        dynamicArray.Set(index, item);
    }

    T &operator[](int index) {
        if (index < 0 || index >= GetLength())
            throw IndexOutOfRange(GetLength(), index);
        return dynamicArray[index];
    }


    ArraySequence<T> &operator=(ArraySequence<T> arraySequence) {
        dynamicArray = arraySequence.dynamicArray;
        return *this;
    }


    ArraySequence<T> *GetSubSequence(int startIndex, int endIndex) {
        if (startIndex < 0 || startIndex >= GetLength())
            throw IndexOutOfRange(GetLength(), startIndex);
        if (endIndex < 0 || endIndex > GetLength())
            throw IndexOutOfRange(GetLength(), endIndex);

        auto newArray = new ArraySequence<T>;
        for (int i = startIndex; i != endIndex; i++) {
            newArray->Append(dynamicArray[i]);
        }

        return newArray;
    }

    int GetLength() const {
        return dynamicArray.GetLength();
    }

    void Append(T item) {
        dynamicArray.Resize(dynamicArray.GetLength() + 1);
        dynamicArray.Set(dynamicArray.GetLength() - 1, item);
    }


    void Prepend(T item) {
        dynamicArray.Resize(dynamicArray.GetLength() + 1);
        for (int i = dynamicArray.GetLength() - 2; i >= 0; i--) {
            dynamicArray[i + 1] = dynamicArray[i];
        }
        dynamicArray.Set(0, item);
    }

    void Insert(T item, int index) {
        if (index < 0 || index >= dynamicArray.GetLength())
            throw IndexOutOfRange(dynamicArray.GetLength(), index);
        dynamicArray.Resize(dynamicArray.GetLength() + 1);
        for (int i = dynamicArray.GetLength() - 2; i >= index; i--) {
            dynamicArray[i + 1] = dynamicArray[i];
        }
        dynamicArray[index] = item;
    }


    ArraySequence<T> *Concat(ArraySequence<T> *sequence) {
        int start = dynamicArray.GetLength();
        dynamicArray.Resize(start + sequence->GetLength());

        for (int i = 0; i < sequence->GetLength(); i++) {
            dynamicArray[start + i] = (*sequence)[i];
        }
        return this;
    }

    void Reverse() {
        dynamicArray.Reverse();
    }

    T Pop() {
        if (dynamicArray.GetLength() == 0)
            throw IndexOutOfRange(0, -1);
        T item = dynamicArray[dynamicArray.GetLength() - 1];
        dynamicArray.Resize(dynamicArray.GetLength() - 1);
        return item;
    }

    T Pop(int index) {
        if (index < 0 || index >= dynamicArray.GetLength())
            throw IndexOutOfRange(dynamicArray.GetLength(), index);

        T item = dynamicArray[index];
        for (int i = index; i < dynamicArray.GetLength() - 1; i++) {
            dynamicArray[i] = dynamicArray[i + 1];
        }
        dynamicArray.Resize(dynamicArray.GetLength() - 1);
        return item;
    }

    ArraySequence<T> *copy() {
        return new ArraySequence<T>(*this);
    }

    ArraySequence<T> *empty() {
        return new ArraySequence<T>();
    }

    ArraySequence<T> RandonSequence(int count = 10) {
        for (int i = 0; i < count; i++) {
            this->Append(randomInt());
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, ArraySequence<T> &arraySequence) {
        return cout << arraySequence.dynamicArray;
    }

    friend std::ostream &operator<<(std::ostream &out, ArraySequence<T> *arraySequence) {
        return cout << arraySequence->dynamicArray;
    }

    bool operator==(ArraySequence<T> *arraySequence) {
        if (this->GetLength() != arraySequence->GetLength())
            return 0;
        for (int i = 0; i < arraySequence->GetLength(); i++) {
            if (this->Get(i) != arraySequence->Get(i))
                return 0;
        }
        return 1;
    }
};


#endif //SEM3LAB2_ARRAYSEQUENCE_H
