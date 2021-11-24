//
// Created by arina on 03.11.2021.
//

#ifndef SEM3LAB2_TREE_H
#define SEM3LAB2_TREE_H

#include <iostream>
#include "ArraySequence.h"
//#include "Comparators.h"

bool cmpInt(int a, int b) {
    return a > b;
}

template<class T>
class BinaryTree {
private:
    struct Node {
        T key;
        int height = 1;
        Node *left = nullptr;
        Node *right = nullptr;

        explicit Node(T data) : key(data) {};


        int getDelta() {
            auto h1 = left == nullptr ? 0 : left->height;
            auto h2 = right == nullptr ? 0 : right->height;
            return h2 - h1;
        }

        void updateHeight() {
            int h1 = left == nullptr ? 0 : left->height;
            int h2 = right == nullptr ? 0 : right->height;
            height = (h1 > h2 ? h1 : h2) + 1;
        }

        Node *rotateLeft() {
            Node *res = right;
            right = res->left;
            res->left = this;
            updateHeight();
            res->updateHeight();

            return res;
        }

        Node *rotateRight() {
            Node *res = left;
            left = res->right;
            res->right = this;
            updateHeight();
            res->updateHeight();

            return res;
        }

        Node *balance() {
            updateHeight();
            auto delta = getDelta();
            if (delta < -1) {
                if (left != nullptr && left->getDelta() > 0)
                    left = left->rotateLeft();
                return rotateRight();
            }
            if (delta > 1) {
                if (right != nullptr && right->getDelta() < 0)
                    right = right->rotateRight();
                return rotateLeft();
            }
            return this;
        }
    };


    Node *root;

    bool (*cmp)(T, T);

    Node *DeleteNode(Node *node) {
        if (node != nullptr) {
            DeleteNode(node->left);
            DeleteNode(node->right);
            delete node;
        }
        return nullptr;
    }

    Node *InsertNonBalance(Node *node, T x) {
        if (node == nullptr) {
            node = new Node(x);
            return node;
        } else if (cmp(node->key, x))
            node->left = InsertNonBalance(node->left, x);
        else if (!(cmp(node->key, x)))
            node->right = InsertNonBalance(node->right, x);
        return node;
    }

    Node *Insert(Node *node, T x) {
        if (node == nullptr) {
            node = new Node(x);
            return node;
        } else if (cmp(node->key, x))
            node->left = Insert(node->left, x);
        else if (!(cmp(node->key, x)))
            node->right = Insert(node->right, x);

        node->updateHeight();
        int delta = node->getDelta();

        if (delta <= 1 && delta >= -1) {
            return node;
        }
        node = node->balance();
        return node;

    }

    Node *FindMin(Node *node) {
        if (node == nullptr)
            return nullptr;
        if (node->left == nullptr)
            return node;
        else
            return FindMin(node->left);
    }

    Node *FindMax(Node *node) {
        if (node == nullptr)
            return nullptr;
        if (node->right == nullptr)
            return node;
        else
            return FindMax(node->right);
    }

    Node *Remove(Node *node, T x) {
        Node *temp;
        if (node == nullptr)
            return nullptr;
        else if (cmp(node->key, x)) {
            node->left = Remove(node->left, x);
        } else if (!(cmp(node->key, x))) {
            node->right = Remove(node->right, x);
        } else if (node->left && node->right) {
            temp = FindMin(node->right);
            node->key = temp->key;
            node->right = Remove(node->right, node->key);
        } else {
            temp = node;
            if (node->left == nullptr)
                node = node->right;
            else if (node->right == nullptr)
                node = node->left;
            delete temp;
        }
        return node;
    }

/*
    void Print(Node *node) {
        if(node == nullptr)
            return;
        print(node->left);
        std::cout<<"/ \t";
        std::cout << node->key << " ";
        std::cout<<"\t|";
        GetStrGreatTree(node->right);
        std::cout<<"\n";
    }
*/


    std::string GetStrKey(Node *p, int level) const {
        if (!p)
            return std::string();

        std::string res;
        res += GetStrKey(p->right, level + 1);
        for (int i = 0; i < level; i++)
            res += "     ";

        res += to_string(p->key);
        res += '\n';
        res += GetStrKey(p->left, level + 1);

        return res;
    }

    void GetArr(Node *p, ArraySequence<T> *arr) {
        if (!p)
            return;
        GetArr(p->left, arr);
        arr->Append(p->key);
        GetArr(p->right, arr);
    }

    Node *FindNode(Node *node, T data) {
        if (node == nullptr) {
            return nullptr;
        } else if (cmp(node->key, data))
            return FindNode(node->left, data);
        else if (!(cmp(node->key, data)))
            return FindNode(node->right, data);
        else
            return node;
    };

    void InsertNode(Node *node) {
        if (node == nullptr) {
            return;
        }
        root = InsertNonBalance(root, node->key);
        InsertNode(node->left);
        InsertNode(node->right);
    }

    bool FindSubTree(Node *node, Node *nodeFind) {
        if (nodeFind == nullptr)
            return true;
        if (node == nullptr)
            return false;
        if (node->key != nodeFind->key)
            return false;
        return FindSubTree(node->left, nodeFind->left) &&
               FindSubTree(node->right, nodeFind->right);
    }


    void MapNode(Node *node, T(*func)(T)) {
        if (node == nullptr)
            return;
        MapNode(node->left, func);
        MapNode(node->right, func);
        node->key = func(node->key);
    }

    void MapNode(Node *node, T(*func)()) {
        if (node == nullptr)
            return;
        MapNode(node->left, func);
        MapNode(node->right, func);
        node->key = func(node->key);
    }

    void MapNode(Node *node, T(*func)(T, T), T elem) {
        if (node == nullptr)
            return;
        MapNode(node->left, func, elem);
        MapNode(node->right, func, elem);
        node->key = func(node->key, elem);
    }

    void WhereNode(Node *node, bool(func(T)), BinaryTree<T> &tree) {
        if (node == nullptr)
            return;
        if (func(node->key)) {
            tree.Insert(node->key);
        }
        WhereNode(node->left, func, tree);
        WhereNode(node->right, func, tree);
    }

public:

    //BinaryTree() {
    //    root = nullptr;
    //    cmp=cmpInt;
    //}

    explicit BinaryTree(bool (*cmp2)(T, T) = cmpInt) {
        root = nullptr;
        cmp = cmp2;
    }

    explicit BinaryTree(ArraySequence<T> &arraySequence, ArraySequence<T> &valArr, bool (*cmp2)(T, T) = cmpInt) {
        root = nullptr;
        cmp = cmp2;
        for (int i = 0; i < arraySequence.GetLength(); i++)
            Insert(arraySequence[i], valArr[i]);
    }

    explicit BinaryTree(ArraySequence<T> &arraySequence, bool (*cmp2)(T, T) = cmpInt) {
        root = nullptr;
        cmp = cmp2;
        for (int i = 0; i < arraySequence.GetLength(); i++)
            Insert(arraySequence[i]);
    }

    BinaryTree(const BinaryTree<T> &binaryTree, bool (*cmp2)(T, T) = cmpInt) {
        root = nullptr;
        cmp = cmp2;
        InsertNode(binaryTree.root);
    }

    explicit BinaryTree(T item, bool (*cmp2)(T, T) = cmpInt) {
        root = new Node(item);
        cmp = cmp2;
    }

    BinaryTree(T *arr, int len, bool (*cmp2)(T,
                                             T) = cmpInt) {                                                          // самый важный конструкор
        root = nullptr;
        cmp = cmp2;
        for (int i = 0; i < len; i++)
            Insert(i[arr]);
    }

    ~BinaryTree() {
        DeleteNode(root);
    }

    void Insert(T item) {
        root = Insert(root, item);
    }

    void Remove(T item) {
        root = Remove(root, item);
        ArraySequence<T> arr = GetKeyArray();
        auto *res = new BinaryTree<T>(arr, cmp);
        DeleteNode(root);
        root = res->root;
    }

    std::string GetStrGreatTree() const {
        auto res = std::string("\n") + GetStrKey(root, 0);
        res += '\n';
        return res;
    }

    bool Find(T item) {
        return FindNode(root, item);
    }

    T GetNode(T data) {
        return FindNode(root, data)->key;
    };

    BinaryTree *SubTree(T item) {
        auto *node = FindNode(root, item);
        auto *res = new BinaryTree<T>;
        res->InsertNode(node);
        return res;
    }

    bool FindSubTree(const BinaryTree<T> &binaryTree) {
        if (binaryTree.root == nullptr)
            return true;

        auto *node = FindNode(root, binaryTree.root->key);
        return FindSubTree(node, binaryTree.root);

    }

    std::string In_Str(int First, int Second, int Third) {
        auto *resArr = new ArraySequence<T>;
        In_Str_Key(root, resArr, First, Second, Third);
        std::string resStr("{");
        for (int i = 0; i < resArr->GetLength(); i++) {
            resStr += std::to_string(resArr->Get(i));
            if (i != resArr->GetLength() - 1)
                resStr += ", ";
        }
        resStr += "}";
        delete resArr;
        return resStr;
    }


    BinaryTree *Map(T(*func)(T, T), T elem) {
        auto *res = new BinaryTree<T>(*this);
        MapNode(res->root, func, elem);
        return res;
    }

    BinaryTree *Map(T(*func)(T)) {
        auto *res = new BinaryTree<T>(*this);
        MapNode(res->root, func);
        return res;
    }

    BinaryTree *Map(T(*func)()) {
        auto *res = new BinaryTree<T>(*this);
        MapNode(res->root, func);
        return res;
    }


    BinaryTree *Where(bool(*func)(T)) {
        auto *res = new BinaryTree<T>();
        WhereNode(this->root, func, *res);
        return res;
    }


    ArraySequence<T> GetKeyArray() {
        auto arr = new ArraySequence<T>;
        GetArr(root, arr);
        return *arr;
    }


    BinaryTree<T> &operator=(const BinaryTree<T> &binaryTree) {
        DeleteNode(root);
        root = nullptr;
        InsertNode(binaryTree.root);
        return *this;
    }

};


template<class T>
std::ostream &operator<<(std::ostream &cout, const BinaryTree<T> &binaryTree) {
    cout << binaryTree.GetStrGreatTree();
    return cout;
}

#endif //SEM3LAB2_TREE_H
