//
// Created by arina on 27.12.2021.
//

#ifndef SEM3LAB2_FIBQUEUE_H
#define SEM3LAB2_FIBQUEUE_H

#include <iostream>
#include <string.h>

using namespace std;

//const int SIZE = 31;
//const int INF = 1e9;
const int ERROR = -100000;
#define MIN_POOSIBLE_VALUE -1


//const int MAX_VERTEXES = 1e4 + 2;
//int dist[MAX_VERTEXES];

template<class T>
struct node {
    node *parent;
    node *child;
    node *left;
    node *right;
    int degree;
    bool mark;
    T key;

    node(T Key) : parent(nullptr), child(nullptr), left(this), right(this), degree(0), mark(false), key(Key) {}

    void internal_delete(bool delete_row) {
        if (child) {
            child->internal_delete(true);
            delete child;
        }
        if (delete_row) {
            node *cur = right;
            while (cur != this) {
                node *next = cur->right;
                cur->internal_delete(false);
                delete cur;
                cur = next;
            }
        }
    }
};

//bool (*cmpPtr)(node<T> *, node<T> *)

//template<class T>
//bool cmp(node<T> *a, node<T> *b) {
//    return dist[a->key] < dist[b->key];
//}

template<class T>
bool cmp(node<T> *a, node<T> *b) {
    return a->key < b->key;
}


template<class T>
class FibHeap {
    node<T> *min;
    int rootsAmount;
    int NumberOFNodes;

    bool (*less)(node<T> *a, node<T> *b);

    //cmpPtr<T> less;
    struct Empty {
        string str;

        Empty(string str = "") : str(str) {}
    };


public:
    FibHeap(bool (*less)(node<T> *a, node<T> *b)) : min(nullptr), rootsAmount(0), less(cmp),
                                                    NumberOFNodes(0) {}

    ~FibHeap() {
        if (!min) return;
        min->internal_delete(true);
        delete min;
    }

    node<T> *Add(T key) {
        node<T> *Node = new node<T>(key);
        add(Node, &min);
        NumberOFNodes++;
        //consolidate();
        return Node;
    }

    T GetMin() {
        return min->key;
    }

    void UnionFibHeap(FibHeap &fb) {
        unionRoot(fb.min, fb.rootsAmount);
        if (!min || (fb.min && less(fb.min, min)))
            min = fb.min;
        fb.clear();
    }

    T ExtractMin() {
        node<T> *res = min;
        if (res) {
            childsToRoot(res);
            removeRoot(res);
            if (res->right == res)
                min = nullptr;
            else {
                min = min->right;
                consolidate();
            }
        }
        T ans = res ? res->key : ERROR;
        delete res;
        return ans;
    }
// Функция для поиска данного узла  и изменения его значения

    node<T> *FindAndChange(node<T> *vert, T old_val, T val) {
        node<T> *found = nullptr;
        node<T> *temp = vert;
        temp->mark = true;
        node<T> *found_ptr = nullptr;
        if (temp->key == old_val) {
            found_ptr = temp;
            temp->mark = false;
            found = found_ptr;
            decreaseKey(found, val);
        }
        if (found_ptr == nullptr) {
            if (temp->child != nullptr)
                FindAndChange(temp->child, old_val, val);
            if ((temp->right)->mark != true)
                FindAndChange(temp->right, old_val, val);
        }
        temp->mark = false;
        return found_ptr;
    }

// Удаление узла из кучи
    void Deletion(T val) {
        if (min == nullptr)
            throw Empty("The heap is empty");
        else {
            // Уменьшаем значение узла до минимума
            auto a = FindAndChange(min, val, MIN_POOSIBLE_VALUE);
            // Вызов функции Extract_min для
            // удаляем минимальное значение узла, равное 0
            ExtractMin();
        }
    }

    node<T> *GetPtrMin() {
        return min;
    }

private:
    bool empty() {
        return !rootsAmount;
    }

    void removeChild(node<T> *Node) {
        Node->parent->degree--;
        Node->parent->child = Node->right == Node ? nullptr : Node->right;
        killLRlinks(Node);
        add(Node, &min);
        Node->mark = false;
    }  //перенос в корень ОДНОГО Node

    void cascadingCut(node<T> *cur) {
        node<T> *par = cur->parent;
        if (par && par->degree) {
            if (!par->mark)
                par->mark = true;
            else {
                removeChild(cur);
                cascadingCut(par);
            }
        }
    }

    void clear() {
        min = nullptr;
        rootsAmount = 0;
    }

    void unionRoot(node<T> *Node, int nodes_amount) {
        if (Node == nullptr) return;
        if (min == nullptr) {
            min = Node;
            rootsAmount = nodes_amount;
        } else {
            node<T> *L = Node->left;
            node<T> *R = min->right;
            min->right = Node;
            Node->left = min;
            L->right = R;
            R->left = L;
            rootsAmount += nodes_amount;
        }
    }

    void killLRlinks(node<T> *Node) {
        if (Node->left != Node) {
            Node->right->left = Node->left;
            Node->left->right = Node->right;
        }
    }

    void add(node<T> *Node, node<T> **bro, node<T> *par = nullptr) {
        if (*bro == nullptr) {
            *bro = Node;
            Node->left = Node;
            Node->right = Node;
        } else {
            Node->right = (*bro)->right;
            Node->right->left = Node;
            Node->left = *bro;
            (*bro)->right = Node;
        }

        if (less(Node, *bro))
            *bro = Node;

        if (*bro == min) {
            rootsAmount++;
            Node->parent = nullptr;
        }
        if (par) {
            par->degree++;
            Node->parent = par;
        }
    }

    void removeRoot(node<T> *Node) {
        killLRlinks(Node);
        rootsAmount--;
    }

    void insertRootAsChildOtherRoot(node<T> *newChild, node<T> *par) {
        removeRoot(newChild);
        add(newChild, &par->child, par);
        newChild->mark = false;
    } //что-то делает

    void consolidate() {
        ArraySequence<node<T> *> A;
        for (int i = 0; i < NumberOFNodes; i++)
            A.Append(nullptr);
        node<T> *x = min;
        int init_roots = rootsAmount;
        int max_degree = 0;
        for (int i = 0; i < init_roots; ++i) {
            int d = x->degree;
            node<T> *next = x->right;
            while (A[d]) {
                node<T> *y = A[d];
                if (less(y, x))
                    swap(x, y);           // корень x <y  дальше работаем c x
                insertRootAsChildOtherRoot(y, x);   //вставляем y в x
                A[d++] = nullptr;
            }
            A[d] = x;
            max_degree = max(max_degree, d);
            x = next;
        }
        min = nullptr;
        rootsAmount = 0;
        for (int i = 0; i <= max_degree; ++i) {
            if (A[i]) {
                add(A[i], &min);
            }
        }
    }

    void childsToRoot(node<T> *Node) {
        while (Node->child)
            removeChild(Node->child);
    }



// Функция для уменьшения значения узла в куче
    void decreaseKey(node<T> *found, int val) {
        if (min == nullptr)
            throw Empty("min");
        if (found == nullptr)
            throw Empty("found");
        found->key = val;
        node<T> *temp = found->parent;
        if (temp != nullptr && found->key < temp->key) {
            removeChild(found);    //выкидывает found в корни
            cascadingCut(temp);    //помечаем вершину из которой удалили
        }
        if (found->key < min->key)
            min = found;

    }

};


template<class T>
void printArrayNode(node<T> *child) {
    node<T> *ptr = child;
    if (ptr == nullptr)
        return;
    else {
        cout << "Child of " << child->parent->key << ": ";
        do {
            cout << ptr->key;
            ptr = ptr->right;
            if (ptr != child) {
                cout << "-->";
            }
        } while (ptr != child && ptr->right != nullptr);
        cout << endl;
    }
    ptr = child;
    do {
        printArrayNode(ptr->child);
        ptr = ptr->right;
    } while (ptr != child && ptr->right != nullptr);
}

template<class T>
void printFibQueue(FibHeap<T> *fq) {
    node<T> *ptr = fq->GetPtrMin();
    if (ptr == nullptr)
        cout << "The Heap is Empty" << endl;
    else {
        cout << "The root nodes of Heap are: " << endl;
        do {
            cout << ptr->key;
            ptr = ptr->right;
            if (ptr != fq->GetPtrMin()) {
                cout << "-->";
            }
        } while (ptr != fq->GetPtrMin() && ptr->right != nullptr);
        cout << endl;
        //     << "The heap has " << fq->rootsAmount << " nodes" << endl;
    }
    do {
        printArrayNode(ptr->child);
        ptr = ptr->right;
    } while (ptr != fq->GetPtrMin() && ptr->right != nullptr);

    cout << endl;

}


#endif //SEM3LAB2_FIBQUEUE_H
