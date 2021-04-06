#pragma once
#ifndef UNION_H
#define UNION_H
#include <iostream>
using namespace std;

template <typename T>
struct UNode
{
    T data;
    int parent;
};

template <typename T>
class Union
{
private:
    int size;   //the number of the node
    UNode <T>* sets;
public:
    Union();
    Union(T set[], int S);
    virtual ~Union();
    int Find_Root(T e) const;
    int Find_height(T e,int maxheight=1,int height=1) const ; // 求树的高度
    T GetElem(int p) const;
    int GetOrder(T e) const;
    bool Differ(T a, T b);
    void Mix(T a, T b);  //合并等价类
    void Display();  //显示
    void Height_Mix(T a, T b); // 按照树高合并
    void Node_Mix(T a, T b); // 按照结点合并
};
template <typename T>
void Union<T> ::Node_Mix(T a, T b)
{

    int order1 = Find_Root(a);
    int order2 = Find_Root(b);
    if (sets[order1].parent <= sets[order2].parent)
        Mix(a, b);
    else Mix(b, a);
}

template <typename T>
int Union<T> ::Find_height (T e,int maxheight,int height) const
{
    for (int i = 0; i < size; i++)
    {
        if (sets[sets[i].parent].data == e && sets[i].parent>0)
        {
            height++;
            if (maxheight <= height) maxheight = height;
            maxheight = Find_height(sets[i].data,maxheight,height);
            height--;
        }
    }
    return maxheight;
}
template <typename T>
void Union<T> ::Height_Mix(T a, T b)
{
    int height1 = Find_height(a);
    int height2 = Find_height(b);
    if (height1 >= height2)
        Mix(a, b);
    else Mix(b, a);
}

template<typename T>
void Union<T> ::Display()
{
    int j;
    for (j = 0; j < size; j++)
    {
        cout << "parent :" << sets[j].parent << "  " << "data :" << sets[j].data;
        cout << endl;
    }
}

template<typename T>
void Union<T> ::Mix(T a, T b)
{
    int a1 = Find_Root(a);
    int b1 = Find_Root(b);
    if (a1 == -1 || b1 == -1 || a1==b1) return; // 元素不存在
    else
    {
        sets[a1].parent += sets[b1].parent;
        sets[b1].parent = a1;
    }
}

template <typename T>
bool Union<T> :: Differ(T a,T b)
{
    int a1 = Find_Root(a);
    int b1 = Find_Root(b);
    if (a1 == b1) return true;
    else return false;
}

template <typename T>
int Union<T> ::GetOrder(T e) const
{
    int p = 0;
    while (p < size && sets[p].data != e)
        p++;
    if (p < size)
        return p;   
    else return -1;  
}

template <typename T>
T Union <T> ::GetElem(int p) const    
{
    if (p < size)
        return sets[p];
    else
        return NULL;
}

template <typename T>
Union <T> :: ~Union()
{
    delete [] sets;
}

template <typename T>
Union <T> ::Union(T set[], int S)
{
    size = S;
    int p = 0;
    sets = new UNode<T>[size];
    while (p < size)
    {
        sets[p].data = set[p];
        sets[p].parent = -1;
        p++;
    }
}

template <typename T>
Union <T> ::Union()
{
    size = 0;
    sets = NULL;
}

template <typename T>
int Union <T> ::Find_Root(T e) const
{
    int p = 0;
    while (p < size && sets[p].data != e)
        p++;
    if (p >= size)
        return -1; 
    else
    {
        while (sets[p].parent > 0)
            p = sets[p].parent;
        return p;
    }
}
#endif
