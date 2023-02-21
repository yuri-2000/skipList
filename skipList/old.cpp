//#include <iostream>
//#include <vector>
//#include <time.h>
//#include <random>
//#include <chrono> //处理时间
//#include <set>
//#include <functional>
//#include <unordered_map>
//#include <openssl/sha.h>
//#include <string>
//#include<cstdlib>
//
//using namespace std;
//
//const int MAX_LEVEL = 4;  // 跳表的最大层数
//
//#define _CRT_SECURE_NO_WARNINGS 1
//
//
//
//
//class Skiplist {
//private:
//    struct Node {
//        int key;
//        int height;
//        Node* prev;
//        Node* next;
//        Node* down;
//        Node* top;
//        string hash;
//        Node() : key(0), prev(nullptr), next(nullptr), down(nullptr), top(nullptr), hash("") {}
//    };
//public:
//    Node* head;
//    Node* tail;
//    int level;
//    int size;
//public:
//    void bindNewNode(Node* x, Node* p);
//    void delNode(Node* x);
//    Node* searchNode(int key);
//public:
//    Skiplist() : head(new Node), level(1), size(0)
//    {
//        head->key = INT_MIN; srand(static_cast<int>(3));
//    }
//    ~Skiplist() { delete head; }
//    void insert(int key, int l, bool isRandom);
//    void remove(int key);
//    bool search(int key) { return (searchNode(key) != nullptr); }
//    void showSkiplist();
//    void showRootHash();
//    int getLevel() { return level; }
//    int getSize() { return size; }
//    Node* getCommon(vector<Node*> low, vector<Node*> high);
//    Node* rangeQuery(int low, int high);
//    vector<Node*> searchQuery(int key);
//    void generateVO(int low, int high);
//    void generateSkiplist();
//    void updateHash();
//    void updatePoint();
//    string praseVO(string VO);
//    // 哈希函数，使用 std::hash<int> 计算节点的哈希值
//    size_t hashNode(Node* node);
//};
//
//
//void Skiplist::updateHash() {
//    Node* p = tail;
//    Node* t = p;
//    Node* checkPoint = head;
//    // 取得最底层head
//    while (checkPoint->down != NULL) {
//        checkPoint = checkPoint->down;
//    }
//
//    // 从后向前遍历
//
//    while (t != checkPoint) {
//        do
//        {
//            if (p->next != NULL) {
//                if (p->down != NULL) {
//                    p->hash = p->down->hash + p->next->hash;
//                }
//                else {
//                    p->hash = to_string(p->key) + p->next->hash;
//                }
//            }
//            else if (p == t) {
//                p->hash = to_string(p->key);
//            }
//            else {
//                p->hash = p->down->hash;
//            }
//            p = p->top;
//        } while (p != NULL);
//
//        // 自后向前
//        t = t->prev;
//        p = t;
//    }
//
//    // 计算 root hash
//    while (p != NULL) {
//        if (p->next != NULL) {
//            if (p->down != NULL) {
//                p->hash = p->down->hash + p->next->hash;
//            }
//            else {
//                p->hash = p->next->hash;
//            }
//        }
//        else if (p->down == NULL) {
//            p->hash = "";
//        }
//        else {
//            p->hash = p->down->hash;
//        }
//
//        p = p->top;
//    }
//}
//
////绑定新节点
//void Skiplist::bindNewNode(Node* x, Node* p) {
//    if (!x->next) {
//        x->next = p;
//        p->prev = x;
//    }
//    else {
//        p->next = x->next;
//        x->next->prev = p;
//        p->prev = x;
//        x->next = p;
//    }
//}
//
//
////插入节点
//void Skiplist::insert(int key, int l, bool isRandom) {
//    Node* p = new Node;
//    int t = 0;
//    p->key = key;
//
//    Node* x = head;
//    while (1) { //find the prev node of p, which represents the right insert place
//        if (x->key <= key) {
//            if (x->next)
//                x = x->next;
//            else if (x->down)
//                x = x->down;
//            else break;
//        }
//        else if (x->prev->down)
//            x = x->prev->down;
//        else {
//            x = x->prev;
//            break;
//        }
//    }
//    bindNewNode(x, p);
//
//    // 记录最后一个插入的节点
//    Node* last_inserted = p;
//
//    int levelnum = 1;
//    while (rand() % 2 && levelnum < MAX_LEVEL && isRandom) {  //扔硬币，然后根据硬币的结果判断是否需要上一层
//        levelnum++;
//        Node* highp = new Node;
//        highp->key = key;
//        while (!x->top && x->prev)
//            x = x->prev;
//        if (x->top) {
//            x = x->top;
//            bindNewNode(x, highp);
//            highp->down = p;
//            p->top = highp;
//        }
//        else { //已经在顶部，添加一个哨兵
//            Node* top = new Node;
//            x = top;
//            top->key = INT_MIN;
//            top->down = head;
//            head->top = top;
//            head = top;
//            bindNewNode(top, highp);
//            highp->down = p;
//            p->top = highp;
//            ++level;
//        }
//        p = highp;
//    }
//
//    if (!isRandom && l >= 1) {
//        l--;
//        Node* highp = new Node;
//        highp->key = key;
//        while (!x->top && x->prev)
//            x = x->prev;
//        if (x->top) {
//            x = x->top;
//            bindNewNode(x, highp);
//            highp->down = p;
//            p->top = highp;
//        }
//        else { //已经在顶部，添加一个哨兵
//            Node* top = new Node;
//            x = top;
//            top->key = INT_MIN;
//            top->down = head;
//            head->top = top;
//            head = top;
//            bindNewNode(top, highp);
//            highp->down = p;
//            p->top = highp;
//            ++level;
//        }
//        p = highp;
//    }
//    ++size;
//
//    // 更新 tail 的值为最后一个插入的节点
//    tail = last_inserted;
//}
//
//
////pri 删除某节点
//void Skiplist::delNode(Node* x) {
//    if (!x->next) { //node x is the last one
//        if (x->prev == head && head->down) { //x is not at the bottom and x is the last one of this level
//            head = head->down;
//            head->top = nullptr;
//            delete x->prev;
//            --level;
//        }
//        else
//            x->prev->next = nullptr;
//    }
//    else {
//        x->prev->next = x->next;
//        x->next->prev = x->prev;
//    }
//    delete x;
//}
//
//
////移除某节点
//void Skiplist::remove(int key) {
//    Node* x = searchNode(key);
//    if (x) {
//        if (x->next == nullptr && x == tail) tail = x->prev;
//        while (x->down) {
//            Node* y = x->down;
//            delNode(x);
//            x = y;
//        }
//        delNode(x);
//        --size;
//    }
//}
//
////查找节点
//vector<Skiplist::Node*> Skiplist::searchQuery(int key) {
//    Node* x = head;
//    int i = 0;
//    vector<Node*> pathArr;
//    while (1) { //找到p的前一节点，它表示正确的插入位置
//        if (x->key == key) {
//            pathArr.push_back(x);
//            i++;
//            if (x->down) {
//                x = x->down;
//            }
//            return pathArr;
//        }
//        else if (x->key < key) {
//            if (x->next && x->next->key <= key) {
//                pathArr.push_back(x);
//                i++;
//                x = x->next;
//            }
//            else if (x->down) {
//                pathArr.push_back(x);
//                i++;
//                x = x->down;
//            }
//            else
//                return pathArr;
//        }
//        else if (x->prev->down) {
//            x = x->prev->down;
//        }
//        else {
//            return pathArr;
//        }
//    }
//}
//
////查找序列
//Skiplist::Node* Skiplist::rangeQuery(int low, int high) {
//    Node* res = head;
//    int i = 0;
//    vector<Node*> l = searchQuery(low);
//    vector<Node*> h = searchQuery(high);
//    res = getCommon(l, h);
//
//    if (res->key != -2147483648) cout << "Common: " << res->key << endl;
//    else cout << "Common: Root" << endl;
//
//    return res;
//
//}
//
////查找节点
//Skiplist::Node* Skiplist::searchNode(int key) {
//    Node* x = head;
//    int i = 0;
//    Node* pathArr[10];
//    while (1) { //找到p的前一节点，它表示正确的插入位置
//        if (x->key == key) {
//            pathArr[i] = x;
//            i++;
//            cout << x->key << "已找到";
//            if (x->down) {
//                x = x->down;
//                cout << x->key << " ??";
//            }
//            return x;
//        }
//        else if (x->key < key) {
//            if (x->next && x->next->key <= key) {
//                pathArr[i] = x;
//                i++;
//                x = x->next;
//                cout << x->key << "=>";
//            }
//            else if (x->down) {
//                pathArr[i] = x;
//                i++;
//                x = x->down;
//                cout << x->key << "=>";
//            }
//            else
//                return nullptr;
//        }
//        else if (x->prev->down) {
//            x = x->prev->down;
//            cout << "回溯到下一行" << endl;
//        }
//        else {
//            return nullptr;
//        }
//    }
//}
//
////将跳表样式规格化
//void Skiplist::generateSkiplist() {
//    cout << "****************************************************************" << endl;
//    //第一行
//    int arr[10];
//    Node* firstNode = head;
//    int n = 0;
//    while (firstNode->next || n < 10) {
//        if (firstNode->next) {
//            firstNode = firstNode->next;
//            arr[n] = firstNode->key;
//        }
//        else {
//            arr[n] = -1;
//        }
//        n++;
//    }
//    bool isFlag = false;
//    for (int i = 1; i <= 10; i++) {
//        for (int j = 0; j < 10; j++) {
//            if (arr[j] == i) {
//                cout << arr[j] << "    ";
//                isFlag = false;
//                break;
//            }
//            else {
//                isFlag = true;
//            }
//        }
//        if (isFlag) {
//            cout << "     ";
//        }
//    }
//    cout << endl;
//
//    //第二行
//    int arr2[10];
//    int a = 0;
//    Node* secondNode = head->next->down;
//    while (secondNode->prev) {
//        secondNode = secondNode->prev;
//    }
//    while (secondNode->next) {
//        arr2[a] = secondNode->next->key;
//        secondNode = secondNode->next;
//        a++;
//    }
//    for (int i = 1; i <= 10; i++) {
//        for (int j = 0; j < 10; j++) {
//            if (arr2[j] == i) {
//                cout << arr2[j] << "    ";
//                isFlag = false;
//                break;
//            }
//            else {
//                isFlag = true;
//            }
//        }
//        if (isFlag) {
//            cout << "     ";
//        }
//    }
//    cout << endl;
//
//    //第三行
//    int arr3[10];
//    int b = 0;
//    Node* thirdNode = head->next->down->down;
//    if (thirdNode != NULL) {
//        while (thirdNode->prev) {
//            thirdNode = thirdNode->prev;
//        }
//        while (thirdNode->next) {
//            arr3[b] = thirdNode->next->key;
//            thirdNode = thirdNode->next;
//            b++;
//        }
//        for (int i = 1; i <= 10; i++) {
//            for (int j = 0; j < 10; j++) {
//                if (arr3[j] == i) {
//                    cout << arr3[j] << "    ";
//                    isFlag = false;
//                    break;
//                }
//                else {
//                    isFlag = true;
//                }
//            }
//            if (isFlag) {
//                cout << "     ";
//            }
//        }
//        cout << endl;
//    }
//
//    //第四行
//    int arr4[10];
//    int c = 0;
//    if (head->next->down->down->down != NULL) {
//        Node* fourNode = head->next->down->down->down;
//        while (fourNode->prev) {
//            fourNode = fourNode->prev;
//        }
//        while (fourNode->next) {
//            arr4[c] = fourNode->next->key;
//            fourNode = fourNode->next;
//            c++;
//        }
//        for (int i = 1; i <= 10; i++) {
//            for (int j = 0; j < 10; j++) {
//                if (arr4[j] == i) {
//                    cout << arr4[j] << "    ";
//                    isFlag = false;
//                    break;
//                }
//                else {
//                    isFlag = true;
//                }
//            }
//            if (isFlag) {
//                cout << "     ";
//            }
//        }
//        cout << endl;
//    }
//
//    cout << "****************************************************************" << endl;
//}
//
//void Skiplist::updatePoint() {
//    Node* p = head;
//    // 取得最底层head
//    while (p->down != NULL) {
//        p = p->down;
//    }
//    Node* t = p;
//    // 遍历整个跳表
//    while (t != NULL) {
//        p = t;
//        t = p->next;
//        do {
//            if (p->next != NULL && p->next->top != NULL) p->next = NULL;
//            p = p->top;
//        } while (p != NULL);
//    }
//}
//
////显示构建好的跳表
//void Skiplist::showSkiplist() {
//    int i = 1;
//    Node* x = head, * y = head;
//    while (y) {
//        x = y;
//        cout << "第" << i << "层:root   ";
//        while (x) {
//            if (x->prev != nullptr)
//                cout << x->key << ' ';
//            x = x->next;
//        }
//        cout << endl;
//        y = y->down;
//        i++;
//    }
//}
//
////显示hash
//void Skiplist::showRootHash() {
//    cout << "Root Hash: " << head->hash << endl;;
//}
//
//Skiplist::Node* Skiplist::getCommon(vector<Node*> low, vector<Node*> high) {
//    Node* res = NULL;
//    int num = 0;
//    if (low.size() > high.size()) num = high.size();
//    else num = low.size();
//    for (int i = 0; i < num; i++) {
//        if (low[i] == high[i]) {
//            res = low[i];
//            continue;
//        }
//        else {
//            res = low[i - 1];
//            break;
//        }
//    }
//
//    return res;
//}
//
//void Skiplist::generateVO(int low, int high) {
//    Node* temp = new Node;
//    Node* voFirst = head;
//    Node* oneVo = voFirst->next;
//    Node* secondVo = temp;
//    Node* thirdVo = temp;
//    Node* fourVo = temp;
//    Node* second = oneVo->down;
//    Node* third = temp;
//    Node* four = temp;
//    //第二行第一个节点
//    if (!second->prev) {
//        secondVo->key = second->key;
//    }
//    else {
//        while (second->prev) {
//            second = second->prev;
//        }
//        if (second) {
//            secondVo = second->next;
//        }
//    }
//    //第三行第一个节点
//    if (oneVo->down->down) {
//        third = oneVo->down->down;
//    }
//    else {
//        thirdVo->key = -1;
//    }
//    if (!third->prev) {
//        thirdVo->key = third->key;
//    }
//    else {
//        while (third->prev) {
//            third = third->prev;
//        }
//        if (third) {
//            thirdVo = third->next;
//        }
//    }
//    //第四行第一个节点
//    if (oneVo->down->down->down) {
//        four = oneVo->down->down->down;
//    }
//    else {
//        fourVo->key = -1;
//    }
//    if (!four->prev) {
//        fourVo->key = four->key;
//    }
//    else {
//        while (four->prev) {
//            four = four->prev;
//        }
//        if (four) {
//            fourVo = four->next;
//        }
//        else {
//            fourVo->key = -1;
//        }
//    }
//
//    cout << "第一行第一个节点值：" << oneVo->key << " " << "第二行第一个节点值：" << secondVo->key << " " << "第三行第一个节点值：" << thirdVo->key << " " << "第四行第一个节点值：" << fourVo->key << endl;
//
//    //查找客户输入的查找范围的节点
//    Node* searchQuaryNode = nullptr;
//    if (fourVo->key != -1) {
//        searchQuaryNode = fourVo;
//    }
//    else if (thirdVo->key != -1) {
//        searchQuaryNode = thirdVo;
//    }
//    else if (secondVo->key != -1) {
//        searchQuaryNode = secondVo;
//    }
//    Node* nodeArr[10]; //节点数组，用来存放客户查询节点的范围内的节点以及两边的节点
//    //将数组初始化
//    for (int i = 0; i < 10; i++) {
//        nodeArr[i] = new Node;
//        nodeArr[i]->key = -1;
//    }
//    int e = 0;
//    while (searchQuaryNode->next) {
//        if (searchQuaryNode->key < low) {
//            searchQuaryNode = searchQuaryNode->next;
//        }
//        else if (searchQuaryNode->key == low) {
//            nodeArr[e] = searchQuaryNode->prev;
//            e++;
//            nodeArr[e] = searchQuaryNode;
//            e++;
//            searchQuaryNode = searchQuaryNode->next;
//        }
//        else if (searchQuaryNode->next && searchQuaryNode->key > low && searchQuaryNode->key <= high) {
//            nodeArr[e] = searchQuaryNode;
//            searchQuaryNode = searchQuaryNode->next;
//            e++;
//        }
//        else if (searchQuaryNode->key == high + 1) {
//            nodeArr[e] = searchQuaryNode;
//            e++;
//            break;
//        }
//    }
//    int len = sizeof(nodeArr) / sizeof(nodeArr[0]);
//    cout << "完整范围: ";
//    for (int i = 0; i < len; i++) {
//        if (nodeArr[i]->key != -1) {
//            cout << nodeArr[i]->key << "    ";
//        }
//    }
//    cout << endl;
//}
//
//string Skiplist::praseVO(string VO) {
//    vector<int> v1;
//    vector<int> v2;
//    string res = "";
//    for (int i = 0; i < VO.size(); i++) {
//        if (VO[i] == '[') {
//            v1.push_back(i);
//        }
//        if (VO[i] == ']') {
//            v2.push_back(i);
//            res += VO.substr(v1.back() + 1, i - v1.back());
//            v1.pop_back();
//        }
//    }
//
//    return res;
//}
////using NodeMap = std::unordered_map<int, Node*>;
////
////// 哈希函数，使用 std::hash<int> 计算节点的哈希值
////size_t hashNode(const Node* node) {
////    std::hash<int> hasher;
////    return hasher(node->key);
////}
//
//
//
//int main()
//{
//    Skiplist L;
//    vector<int> l = { 1, 1, 1, 1, 4, 1, 1, 3, 1, 4 };
//
//    for (int i = 1; i <= 10; i++)
//    {
//        //     Node* node = new Node{ i };
//        //    //cout << hashNode(node) << endl;
//        //    cout << "节点" << i << "的hash值为: " << hashNode(node) << endl;
//
//        L.insert(i, l[i - 1], true);
//    }
//
//    cout << "原始跳表:" << endl;
//    L.showSkiplist();
//    cout << "跳表大小:" << L.getSize() << endl;
//    cout << "跳表层数 :" << L.getLevel() << endl;
//    cout << "________________________" << endl;
//
//    L.generateSkiplist();
//    L.updatePoint();
//    L.updateHash();
//    L.showRootHash();
//    L.rangeQuery(2, 5);
//    L.generateVO(2, 5);
//
//
//
//    //cout << "插入新节点 客户控制台输入 :" << endl;
//    //int insertNode;
//    //cin >> insertNode;
//    //cout << endl;
//    //L.insert(insertNode);
//    //L.showSkiplist();
//    //cout << "跳表大小:" << L.getSize() << endl;
//    //cout << "________________________" << endl;
//
//
//    //cout << "删除节点 客户控制台输入 :" << endl;
//    //int deleteNode;
//    //cin >> deleteNode;
//    //cout << endl;
//    //L.remove(deleteNode);
//    //L.showSkiplist();
//    //cout << "跳表大小:" << L.getSize() << endl;
//    //cout << "________________________" << endl;
//
//
//    //cout << "查找节点 客户控制台输入 :" << endl;
//    //int inp;
//    //cin >> inp;
//    //cout << endl;
//    //if (L.search(inp) == 1) {
//    //    cout << "该节点存在跳表里;" << endl;
//    //}
//    //else {
//    //    cout << "该节点不在跳表里;" << endl;
//    //}
//    //cout << "________________________" << endl;
//
//    return 0;
//}
//
//
