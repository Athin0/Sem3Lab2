//
// Created by arina on 05.11.2021.
//

#ifndef SEM3LAB2_HISTOGRAM_H
#define SEM3LAB2_HISTOGRAM_H

#include "Dictionary.h"

//вывод гистограммы

template<class T>
class Histogram {
private:
    Dictionary<int, int> *dict;

    int (*Get_int_value)(T);

    bool (*cmp)(KeyValuePair<int, int>, KeyValuePair<int, int>);

public:
    Histogram(int (*Get_int_value)(T),
              bool (*cmp)(KeyValuePair<int, int>, KeyValuePair<int, int>)) {
        dict = new Dictionary<int, int>(cmp);
        this->cmp = cmp;
        this->Get_int_value = Get_int_value;
    }

    Histogram(ArraySequence<T> array, int (*Get_int_value)(T),
              bool (*cmp)(KeyValuePair<int, int>, KeyValuePair<int, int>)) {
        dict = new Dictionary<int, int>(cmp);
        this->cmp = cmp;
        this->Get_int_value = Get_int_value;
        this->Add(array);
    }

    ~Histogram() {
        delete dict;
    }

    void Add(T human) {
        int int_value = Get_int_value(human);
        if (dict->ContainsKey(int_value)) {
            int count = dict->Get(int_value);
            dict->Remove(int_value);
            count++;                      //Set
            //dict->Get(int_value);
            dict->Add(int_value, count);
        } else {
            dict->Add(int_value, 1);
        }
    }

    void Add(ArraySequence<T> array) {
        for (int i = 0; i < array.GetLength(); i++)
            this->Add(array[i]);
    }

    int Get_count(T human) {
        int int_value = Get_int_value(human);
        if (dict->ContainsKey(int_value))
            return dict->Get(int_value);
        return 0;
    }

    int Get_count_int(int value) {
        if (dict->ContainsKey(value))
            return dict->Get(value);
        return 0;
    }

    Dictionary<int, int> even_partition(int min, int max, int range) {
        Dictionary<int, int> even_dict(cmp);
        int j = min, summary_count = 0;
        if (dict->ContainsKey(min))
            even_dict.Add(min, dict->Get(min));
        for (int i = min; i < max; i++) {
            if (dict->ContainsKey(i)) {
                summary_count += dict->Get(i);
            }
            if ((i - min) % range == 0) {
                even_dict.Add(j, summary_count);
                j = j + range;
                summary_count = 0;
            }
        }
        if (dict->ContainsKey(max))
            summary_count += dict->Get(max);
        even_dict.Add(max, summary_count);
        return even_dict;
    }

    Dictionary<int, int> even_partition(int range) {
        int min = dict->FindMin();
        int max = dict->FindMax();
        Dictionary<int, int> even_dict(cmp);
        int j = min, summary_count = 0;
        for (int i = min; i < max; i++) {
            if (dict->ContainsKey(i)) {
                summary_count += dict->Get(i);
            }
            if ((i - min) % range == 0) {
                even_dict.Add(j, summary_count);
                j = j + range;
                summary_count = 0;
            }
        }
        if (dict->ContainsKey(max))
            summary_count += dict->Get(max);
        even_dict.Add(max, summary_count);
        return even_dict;
    }


    Dictionary<int, int> uneven_partition(ArraySequence<int> &seq) {
        Dictionary<int, int> uneven_dict(cmp);
        int summary_count = 0;
        for (int i = seq.GetFirst(), j = 1; i < seq.GetLast(); i++) {
            if (i <= seq.Get(j)) {
                if (dict->ContainsKey(i)) {
                    summary_count += dict->Get(i);
                }
            } else {
                uneven_dict.Add(seq.Get(j), summary_count);
                j++;
                summary_count = 0;
            }
        }
        //if (dict->ContainsKey(seq.GetLast()))
        //    summary_count += dict->Get(seq.GetLast());
        uneven_dict.Add(seq.GetLast(), summary_count);
        return uneven_dict;
    }

    void print() {
        dict->print();
    }

    Dictionary<int, int> GetDictionary() {
        return *this->dict;
    }
};

template<class T>
std::ostream &operator<<(std::ostream &out, Histogram<T> &diction) {
    diction.print();
    return out;
};
#endif //SEM3LAB2_HISTOGRAM_H
