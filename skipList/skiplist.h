#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <chrono> //����ʱ��
#include <set>
#include <functional>
#include <unordered_map>
#include <openssl/sha.h>
#include <string>
#include <stack>
#include <csv_operate.h>

using namespace std;

const int MAX_LEVEL = 4;  // �����������

#define _CRT_SECURE_NO_WARNINGS 1


class Skiplist {
public:
    struct Node {
        int key;
        string hash;
        string RorH;
        int levelNode;
        int levelNodeNum;
        Node* prev;
        Node* next;
        Node* down;
        Node* top;
        Node() : key(0), hash(""), RorH(""), levelNode(1), levelNodeNum(1), prev(nullptr), next(nullptr), down(nullptr), top(nullptr) {}
    };
public:
    Node* head;
    Node* tail;
    int level;
    int size;
    int levelNode;
    int levelNodeNum;
public:
    void bindNewNode(Node* x, Node* p);
    void delNode(Node* x);
    Node* searchNode(int key);
public:
    Skiplist() : head(new Node), level(1), size(0), levelNode(1), levelNodeNum(1)
    {
        head->key = INT_MIN; srand(static_cast<int>(4)); //time(0);
    }
    ~Skiplist() { delete head; }
    void insert(int key);
    void remove(int key);
    bool search(int key) { return (searchNode(key) != nullptr); }
    void showSkiplist();
    int getLevel() { return level; }
    int getSize() { return size; }
    void generateVO(int low, int high); //����vo
    void generateSkiplist(); //��������
    void findminparent(int low, int high); //������С�������Ƚڵ�
    void getLevelNodeNum();
    void getLevelNodeNum_1(Node* node);
    void vocoutparenthesis(); //��VO�����ŵ���ʽ���
    void updatePoint();
    void updateHash();
    void downUpdataLevelNode(Node* node, int n);
    vector<Skiplist::Node*> getSon(Node* node, vector<Node*>v1);
    vector<Skiplist::Node*> getFather(Node* node);
    void getRes(int high);
    void praseVO(string voStr);

    // ��ϣ������ʹ�� std::hash<int> ����ڵ�Ĺ�ϣֵ
    size_t hashNode(Node* node);
};