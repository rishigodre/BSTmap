#pragma once
#include <bits/stdc++.h>

// this implementation is very slow because the tree is not balanced
// can not scale beyond 1e4 characters lol
// also does not have individual node deletion capabilities
template <typename KeyType, typename ValueType>
class node
{
public:
    KeyType key;
    ValueType value;
    node<KeyType, ValueType> *left, *right;
    node(KeyType keyVal, ValueType Val)
    {
        key = keyVal;
        value = Val;
        left = NULL;
        right = NULL;
    }
};

template <typename KeyType, typename ValueType>
class my_map
{
private:
    node<KeyType, ValueType> *head;
    size_t SIZE;

public:
    // constructor initializes the values of the data members
    my_map()
    {
        head = NULL;
        SIZE = 0;
    }
    // checks wether the map is empty or not
    bool is_empty()
    {
        return this->head == NULL;
    }
    // return the adress of the head node
    node<KeyType, ValueType> *begin()
    {
        return this->head;
    }
    // returns the size of the map
    size_t size()
    {
        return SIZE;
    }
    // inserts elements to the map can also be done with the array subscript operator
    // array subscript operaror references this insert function
    void insert(KeyType toInsertKey, ValueType toInsertVal = ValueType())
    {
        node<KeyType, ValueType> *tempNode = new node(toInsertKey, toInsertVal);
        node<KeyType, ValueType> *tempHead = this->head;
        if (head == NULL)
        {
            ++SIZE;
            head = tempNode;
            return;
        }
        while (tempHead != NULL)
        {
            if (tempHead->key == toInsertKey)
            {
                tempHead->value = toInsertVal;
                break;
            }
            if (tempHead->key > toInsertKey)
            {
                if (tempHead->left == NULL)
                {
                    tempHead->left = tempNode;
                    ++SIZE;
                    break;
                }
                tempHead = tempHead->left;
                continue;
            }
            if (tempHead->key < toInsertKey)
            {
                if (tempHead->right == NULL)
                {
                    tempHead->right = tempNode;
                    ++SIZE;
                    break;
                }
                tempHead = tempHead->right;
            }
        }
    }
    // prints out the map in ascending order
    void print()
    {
        if (this->head == NULL)
        {
            std::cout << "map is empty" << std::endl;
            return;
        }
        std::function<void(node<KeyType, ValueType> *)> print = [&](node<KeyType, ValueType> *tempHead)
        {
            if (tempHead == NULL)
                return;
            print(tempHead->left);
            std::cout << tempHead->key << " : " << tempHead->value << std::endl;
            print(tempHead->right);
        };
        print(this->head);
    }
    // for debugging
    void bfs()
    {
        std::queue<node<KeyType, ValueType> *> bfsQueue;
        node<KeyType, ValueType> *tempHead = this->head;
        bfsQueue.push(tempHead);
        while (bfsQueue.size())
        {
            std::cout << bfsQueue.front()->key << " : " << bfsQueue.front()->value << " ";
            if (bfsQueue.front()->left != NULL)
                bfsQueue.push(bfsQueue.front()->left);
            if (bfsQueue.front()->right != NULL)
                bfsQueue.push(bfsQueue.front()->right);
            bfsQueue.pop();
        }
        std::cout << std::endl;
    }
    // checks if a value is in the map or not
    bool init(KeyType toCheck)
    {
        node<KeyType, ValueType> *tempHead = this->head;
        while (tempHead != NULL)
        {
            if (tempHead->key == toCheck)
            {
                break;
            }
            if (tempHead->key > toCheck)
            {
                tempHead = tempHead->left;
                continue;
            }
            if (tempHead->key < toCheck)
            {
                tempHead = tempHead->right;
            }
        }
        return tempHead != NULL;
    }
    // returns node pointer of the value toFind
    node<KeyType, ValueType> *find(KeyType toFind)
    {
        node<KeyType, ValueType> *tempHead = this->head;
        while (tempHead != NULL)
        {
            if (tempHead->key == toFind)
            {
                break;
            }
            if (tempHead->key > toFind)
            {
                tempHead = tempHead->left;
                continue;
            }
            if (tempHead->key < toFind)
            {
                tempHead = tempHead->right;
            }
        }
        return tempHead;
    }
    // overloaded the array subscript operator so that it behaves like a normal map
    // references the insert method
    ValueType &operator[](KeyType toInsert)
    {
        node<KeyType, ValueType> *tempHead = this->head;
        while (tempHead != NULL)
        {
            if (tempHead->key == toInsert)
            {
                break;
            }
            if (tempHead->key > toInsert)
            {
                tempHead = tempHead->left;
                continue;
            }
            if (tempHead->key < toInsert)
            {
                tempHead = tempHead->right;
            }
        }
        if (tempHead == NULL)
        {
            insert(toInsert);
        }
        return find(toInsert)->value;
    }
    // memory safe deletion of the map
    void clear()
    {
        std::function<void(node<KeyType, ValueType> *)> destroy = [&](node<KeyType, ValueType> *tempHead)
        {
            if (tempHead == NULL)
                return;
            destroy(tempHead->left);
            delete tempHead;
            destroy(tempHead->right);
        };
        destroy(this->head);
        this->head = NULL;
    }
    ~my_map()
    {
        clear();
        SIZE = 0;
        delete this->head;
    }
};