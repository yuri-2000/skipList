#include <skiplist.h>

//using namespace std;
//
//const int MAX_LEVEL = 4;  // �����������
//
//#define _CRT_SECURE_NO_WARNINGS 1


//class Skiplist {
//public:
//    struct Node {
//        int key;
//        string hash;
//        string RorH;
//        int levelNode;
//        int levelNodeNum;
//        Node* prev;
//        Node* next;
//        Node* down;
//        Node* top;
//        Node() : key(0), hash(""), RorH(""), levelNode(1), levelNodeNum(1), prev(nullptr), next(nullptr), down(nullptr), top(nullptr) {}
//    };
//public:
//    Node* head;
//    Node* tail;
//    int level;
//    int size;
//    int levelNode;
//    int levelNodeNum;
//public:
//    void bindNewNode(Node* x, Node* p);
//    void delNode(Node* x);
//    Node* searchNode(int key);
//public:
//    Skiplist() : head(new Node), level(1), size(0), levelNode(1), levelNodeNum(1)
//    {
//        head->key = INT_MIN; srand(static_cast<int>(5)); //time(0);
//    }
//    ~Skiplist() { delete head; }
//    void insert(int key);
//    void remove(int key);
//    bool search(int key) { return (searchNode(key) != nullptr); }
//    void showSkiplist();
//    int getLevel() { return level; }
//    int getSize() { return size; }
//    void generateVO(int low, int high); //����vo
//    void generateSkiplist(); //��������
//    void findminparent(int low, int high); //������С�������Ƚڵ�
//    void getLevelNodeNum();
//    void getLevelNodeNum_1(Node* node);
//    void vocoutparenthesis(); //��VO�����ŵ���ʽ���
//    void updatePoint();
//    void updateHash();
//    void downUpdataLevelNode(Node* node, int n);
//    vector<Skiplist::Node*> getSon(Node* node, vector<Node*>v1);
//    vector<Skiplist::Node*> getFather(Node* node);
//    void getRes(int high);
//    void praseVO(string voStr);
//
//    // ��ϣ������ʹ�� std::hash<int> ����ڵ�Ĺ�ϣֵ
//    size_t hashNode(Node* node);
//};


//���½ڵ�
void Skiplist::bindNewNode(Node* x, Node* p) {
    if (!x->next) {
        x->next = p;
        p->prev = x;
    }
    else {
        p->next = x->next;
        x->next->prev = p;
        p->prev = x;
        x->next = p;
    }
}


//����ڵ�
void Skiplist::insert(int key) {
    Node* p = new Node;
    p->key = key;

    Node* x = head;
    while (1) { //find the prev node of p, which represents the right insert place
        if (x->key <= key) {
            if (x->next)
                x = x->next;
            else if (x->down)
                x = x->down;
            else break;
        }
        else if (x->prev->down)
            x = x->prev->down;
        else {
            x = x->prev;
            break;
        }
    }
    bindNewNode(x, p);
    Node* last_inserted = p; // ��¼���һ������Ľڵ�
    int levelnum = 1;
    while (rand() % 2 && levelnum < MAX_LEVEL) {  //��Ӳ�ң�Ȼ�����Ӳ�ҵĽ���ж��Ƿ���Ҫ��һ��
        levelnum++;
        Node* highp = new Node;
        highp->key = key;
        //highp->levelNode = x->levelNode + 1;
        while (!x->top && x->prev)
            x = x->prev;
        if (x->top) {
            x = x->top;
            //highp->levelNode = x->levelNode + 1;
            bindNewNode(x, highp);
            highp->down = p;
            p->top = highp;
        }
        else { //�Ѿ��ڶ��������һ���ڱ�
            Node* top = new Node;
            x = top;
            top->key = INT_MIN;
            top->down = head;
            head->top = top;
            head = top;
            //highp->levelNode = x->levelNode + 1;
            bindNewNode(top, highp);
            highp->down = p;
            p->top = highp;
            ++level;
        }
        p = highp;
    }
    ++size;
    // ���� tail ��ֵΪ���һ������Ľڵ�
    tail = last_inserted;
}


//pri ɾ��ĳ�ڵ�
void Skiplist::delNode(Node* x) {
    if (!x->next) { //node x is the last one
        if (x->prev == head && head->down) { //x is not at the bottom and x is the last one of this level
            head = head->down;
            head->top = nullptr;
            delete x->prev;
            --level;
        }
        else
            x->prev->next = nullptr;
    }
    else {
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }
    delete x;
}


//�Ƴ�ĳ�ڵ�
void Skiplist::remove(int key) {
    Node* x = searchNode(key);
    if (x) {
        if (x->next == nullptr && x == tail) tail = x->prev;
        while (x->down) {
            Node* y = x->down;
            delNode(x);
            x = y;
        }
        delNode(x);
        --size;
    }
}

//���ҽڵ�
Skiplist::Node* pathArr[15];
Skiplist::Node* Skiplist::searchNode(int key) {
    int i = 0;
    Node* x = head;
    pathArr[i] = x;
    i++;
    cout << "ͷ��㿪ʼ����:" << x->key << "(" << x->levelNodeNum << ")" << "=>";
    //��ʼ������
    for (int i = 0; i < 15; i++) {
        pathArr[i] = new Node;
        pathArr[i]->key = -1;
    }
    while (1) { //�ҵ�p��ǰһ�ڵ㣬����ʾ��ȷ�Ĳ���λ��
        if (x->key == key) {
            while (x->down) {
                pathArr[i] = x;
                i++;
                cout << x->key << "(" << x->down->levelNodeNum << ")" << "=>";
                x = x->down;
            }
            if (!x->down) {
                cout << x->key << "(" << x->levelNodeNum << ")" << "���ҵ�" << endl;
            }
            return x;
        }
        else if (x->key < key) {
            if (x->next && x->next->key <= key) {
                pathArr[i] = x;
                i++;
                x = x->next;
                cout << x->key << "(" << x->levelNodeNum << ")" << "=>";
            }    
            else if (x->down) {
                pathArr[i] = x;
                i++;
                x = x->down;
                cout << x->key << "(" << x->levelNodeNum << ")" << "=>";
            }    
            else
                return nullptr;
        }
        else if (x->prev->down) {
            x = x->prev->down;
            cout << x->key << "(" << x->levelNodeNum << ")" << "=>";
        }
        else {
            return nullptr;
        }
    }
}


//��������ʽ���
void Skiplist::generateSkiplist() {
    //��һ��
    Node* arr[10];
    //��ʼ������
    for (int i = 0; i < 10; i++) {
        arr[i] = new Node;
        arr[i]->key = -1;
    }
    Node* firstNode = head;
    int n = 0;
    while (firstNode->next || n < 10) {
        if (firstNode->next){
            firstNode = firstNode->next;
            arr[n] = firstNode;
        }
        n++;
    }
    bool isFlag = false;
    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (arr[j]->key == i) {
                cout << arr[j]->key << "    ";
                isFlag = false;
                break;
            }else {
                isFlag = true;
            }
        }
        if (isFlag) {
            cout << "     ";
        }
    }
    cout << endl;

    //�ڶ���
    Node* arr2[10];
    //��ʼ������
    for (int i = 0; i < 10; i++) {
        arr2[i] = new Node;
        arr2[i]->key = -1;
    }
    int a = 0;
    Node* secondNode = head->next->down;
    while (secondNode->prev) {
        secondNode = secondNode->prev;
    }
    while (secondNode->next) {
        arr2[a]->key = secondNode->next->key;
        secondNode = secondNode->next;
        a++;
    }
    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (arr2[j]->key == i) {
                cout << arr2[j]->key << "    ";
                isFlag = false;
                break;
            }
            else {
                isFlag = true;
            }
        }
        if (isFlag) {
            cout << "     ";
        }
    }
    cout << endl;

    //������
    Node* arr3[10];
    //��ʼ������
    for (int i = 0; i < 10; i++) {
        arr3[i] = new Node;
        arr3[i]->key = -1;
    }
    int b = 0;
    Node* thirdNode = nullptr;
    if (head->next->down->down) {
        thirdNode = head->next->down->down;
        while (thirdNode->prev) {
            thirdNode = thirdNode->prev;
        }
        while (thirdNode->next) {
            arr3[b]->key = thirdNode->next->key;
            thirdNode = thirdNode->next;
            b++;
        }
        for (int i = 1; i <= 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (arr3[j]->key == i) {
                    cout << arr3[j]->key << "    ";
                    isFlag = false;
                    break;
                }
                else {
                    isFlag = true;
                }
            }
            if (isFlag) {
                cout << "     ";
            }
        }
        cout << endl;
    }
    

    //������
    Node* arr4[10];
    //��ʼ������
    for (int i = 0; i < 10; i++) {
        arr4[i] = new Node;
        arr4[i]->key = -1;
    }
    int c = 0;
    Node* fourNode = nullptr;
    if (head->next->down->down) {
        if (head->next->down->down->down) {
            fourNode = head->next->down->down->down;
            while (fourNode->prev) {
                fourNode = fourNode->prev;
            }
            while (fourNode->next) {
                arr4[c]->key = fourNode->next->key;
                fourNode = fourNode->next;
                c++;
            }
            for (int i = 1; i <= 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (arr4[j]->key == i) {
                        cout << arr4[j]->key << "    ";
                        isFlag = false;
                        break;
                    }
                    else {
                        isFlag = true;
                    }
                }
                if (isFlag) {
                    cout << "     ";
                }
            }
            cout << endl;
        }
    }
}


//��ʾ�����õ�����
Skiplist::Node* voArr[15]; //ȫ�����飬�洢��������Ľڵ���Ϣ
int vo = 0; //ȫ�ֱ��������ȫ������voArr
Skiplist::Node* rangeArr[10]; //ȫ�����飬�洢��Χ�ڵĽڵ���Ϣ
void Skiplist::showSkiplist() {
    //��voArr�����ʼ��
    for (int i = 0; i < 15; i++) {
        voArr[i] = new Node;
        voArr[i]->key = 999;
    }

    int i = 1;
    Node* x = head, * y = head;
    while (y) {
        x = y;
        cout << "��" << i << "��:root   ";
        while (x) {
            if (x->prev != nullptr)
                cout << x->key << "(" << x->levelNodeNum << ")" << ' ';
            x = x->next;
        }
        cout << endl;
        y = y->down;
        i++;
    }
}




Skiplist::Node* firstNode = nullptr; //ȫ�֣���һ�е�һ���ڵ�/
Skiplist::Node* secondNode = nullptr;//ȫ�֣��ڶ��е�һ���ڵ�
Skiplist::Node* thirdNode = nullptr; //ȫ�֣������е�һ���ڵ�
Skiplist::Node* fourNode = nullptr; //ȫ�֣������е�һ���ڵ�
Skiplist::Node* quaryLastNode = nullptr; //������Χ�����һ���ڵ�
void Skiplist::generateVO(int low, int high) {

    //�������ʼ��
    for (int i = 0; i < 10; i++) {
        rangeArr[i] = new Node;
        rangeArr[i]->key = -1;
    }

    Node* temp = new Node;
    Node* voFirst = head;
    Node* oneVo = voFirst->next; //��һ�еĵ�һ���ڵ�
    firstNode = oneVo;
    Node* secondVo = temp; //�ڶ��еĵ�һ���ڵ�
    Node* thirdVo = temp; //�����еĵ�һ���ڵ�
    Node* fourVo = temp; //�����еĵ�һ���ڵ�
    Node* second = oneVo->down;
    Node* third = temp;
    Node* four = temp;
    //�ڶ��е�һ���ڵ�
    if (!second->prev) {
        secondVo->key = second->key;
    }
    else {
        while (second->prev) {
            second = second->prev;
        }
        if (second) {
            secondVo = second->next;
        }
    }
    secondNode = secondVo;
    //�����е�һ���ڵ�
    if (oneVo->down->down) {
        third = oneVo->down->down;
    }
    else {
        thirdVo->key = -1;
    }
    if (!third->prev) {
        thirdVo->key = third->key;
    }
    else {
        while (third->prev) {
            third = third->prev;
        }
        if (third) {
            thirdVo = third->next;
        }
    }
    thirdNode = thirdVo;
    //�����е�һ���ڵ�
    if (oneVo->down->down->down) {
        four = oneVo->down->down->down;
    }
    else {
        fourVo->key = -1;
    }
    if (!four->prev) {
        fourVo->key = four->key;
    }
    else {
        while (four->prev) {
            four = four->prev;
        }
        if (four) {
            fourVo = four->next;
        }
        else {
            fourVo->key = -1;
        }
    }
    fourNode = fourVo;

    cout << "��һ�е�һ���ڵ�ֵ��" << oneVo->key << " " << "�ڶ��е�һ���ڵ�ֵ��" << secondVo->key << " " << "�����е�һ���ڵ�ֵ��" << thirdVo->key << " " << "�����е�һ���ڵ�ֵ��" << fourVo->key << endl;


    //���ҿͻ�����Ĳ��ҷ�Χ�Ľڵ�
    Node* searchQuaryNode = nullptr;
    if (fourVo->key != -1) {
        searchQuaryNode = fourVo;
    }
    else if (thirdVo->key != -1) {
        searchQuaryNode = thirdVo;
    }
    else if (secondVo->key != -1) {
        searchQuaryNode = secondVo;
    }
    Node* nodeArr[10]; //�ڵ����飬������ſͻ���ѯ�ڵ�ķ�Χ�ڵĽڵ��Լ����ߵĽڵ�
    //�������ʼ��
    for (int i = 0; i < 10; i++) {
        nodeArr[i] = new Node;
        nodeArr[i]->key = -1;
    }
    int e = 0;
    while (searchQuaryNode->next) {
        if (searchQuaryNode->key < low) {
            searchQuaryNode = searchQuaryNode->next;
        }else if (searchQuaryNode->key == low) {
            nodeArr[e] = searchQuaryNode->prev;
            e++;
            nodeArr[e] = searchQuaryNode;
            e++;
            searchQuaryNode = searchQuaryNode->next;
        }else if (searchQuaryNode->next && searchQuaryNode->key > low && searchQuaryNode->key <= high) {
            nodeArr[e] = searchQuaryNode;
            searchQuaryNode = searchQuaryNode->next;
            e++;
        }else if (searchQuaryNode->key == high + 1) {
            nodeArr[e] = searchQuaryNode;
            quaryLastNode = searchQuaryNode;
            e++;
            break;
        }
    }
    if (!searchQuaryNode->next) {
        nodeArr[e] = searchQuaryNode;
    }
    int len = sizeof(nodeArr) / sizeof(nodeArr[0]);
    cout << "������Χ: ";
    int m = 0;
    for (int i = 0; i < len; i++) {
        if (nodeArr[i]->key != -1) {
            rangeArr[m] = nodeArr[i];
            m++;
            cout << nodeArr[i]->key << "    ";
            cout << "R" << nodeArr[i]->key << "    ";
            voArr[vo] = nodeArr[i];
            voArr[vo]->RorH = "R";
            vo++;
        }       
    }
    cout << endl;
}


Skiplist::Node* CommonNode = nullptr;
//������֧Ѱ����С��������
void Skiplist::findminparent(int low, int high) {
    Node* firstArr[15];
    Node* secondArr[15];
    Node* allNode[15]; //����·�������Ĳ���
    Node* firstExtComArr[15]; //��һ��·���������� ��󹫹��ڵ�ǰ��Ĳ���
    Node* secondExtComArr[15]; //�ڶ���·���������� ��󹫹��ڵ�ǰ��Ĳ���
    //�������ʼ��
    for (int i = 0; i < 15; i++) {
        firstArr[i] = new Node;
        firstArr[i]->key = -1;
        secondArr[i] = new Node;
        secondArr[i]->key = -1;
        allNode[i] = new Node;
        allNode[i]->key = -1;
        firstExtComArr[i] = new Node;
        firstExtComArr[i]->key = -1;
        secondExtComArr[i] = new Node;
        secondExtComArr[i]->key = -1;
    }
    Node* maxNode = nullptr; //����·���������ֵ����ڵ�
    int i, j, k = 0;
    searchNode(low - 1);
    for (int i = 0; i < 15; i++) {
        firstArr[i] = pathArr[i];
    }
    //�������ʼ��
    for (int i = 0; i < 15; i++) {
        pathArr[i] = new Node;
        pathArr[i]->key = -1;
    }
    searchNode(high + 1);
    for (int i = 0; i < 15; i++) {
        secondArr[i] = pathArr[i];
    }
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (firstArr[i]->key == secondArr[j]->key && firstArr[i]->key != -1 && firstArr[i]->levelNodeNum == secondArr[j]->levelNodeNum) {
                allNode[k] = firstArr[i];
                k++;
            }
        }
    }
    maxNode = allNode[0];
    for (int i = 0; i < 10; i++) {
        if (allNode[i]->key >= maxNode->key && allNode[i]->key != -1) {
            maxNode = allNode[i];
        }
    }
    CommonNode = maxNode;

    //��һ��·���������� ��󹫹��ڵ�ǰ��Ĳ���
    int m = 0;
    for (int i = 0; i < 15; i++) {
        if (firstArr[i]->key < maxNode->key && firstArr[i]->key != -1) {
            firstExtComArr[m] = firstArr[i];
            m++;
        }
    }

    //�ڶ���·���������� ��󹫹��ڵ�ǰ��Ĳ���
    int n = 0;
    for (int i = 0; i < 15; i++) {
        if (firstArr[i]->key < maxNode->key && firstArr[i]->key != -1) {
            secondExtComArr[n] = firstArr[i];
            n++;
        }
    }

    cout << "��Χ����С��������Ϊ�ڵ�:" << maxNode->key << "(" << maxNode->levelNodeNum << ")" << endl;
    if (maxNode->down && maxNode->key != -2147483648) {
        cout << "R" << maxNode->key << endl;
    }

    //������Χ��һ���ڵ�ǰ��Ĳ��ֵ����߶�
    Node* underNode = nullptr; //���²�������Χ�ĵ�һ���ڵ�
    int preMaxLevel = 1;
    if (fourNode) {
        underNode = fourNode;
    }
    else if (thirdNode) {
        underNode = thirdNode;
    }
    else {
        underNode = secondNode;
    }
    while (underNode->next->key < low) {
            if (underNode->levelNode > preMaxLevel) {
                preMaxLevel = underNode->levelNode;
            }
        underNode = underNode->next;
    }

    //������Χǰ��Ĳ���
    //�����õ�������Χ�ڵ����߶�
    int maxLevel = 1;
    Node* maxLevelNode = nullptr;
    for (int i = 0; i < 10; i++) {
        if (rangeArr[i]->levelNode > maxLevel) {
            maxLevel = rangeArr[i]->levelNode;
            maxLevelNode = rangeArr[i];
        }
    }

    if (CommonNode->key == -2147483648 && preMaxLevel <= maxLevel) {
        if (maxLevelNode->key > low - 1) {
            maxLevelNode = maxLevelNode->prev;
            while (maxLevelNode->prev && maxLevelNode->prev->levelNode >= maxLevelNode->levelNode) {
                cout << "R" << maxLevelNode->prev->key;
                maxLevelNode = maxLevelNode->prev;
                voArr[vo] = maxLevelNode->prev;
                voArr[vo]->RorH = "R";
                vo++;
            }
            Node* temp = nullptr;
            while (maxLevelNode->prev) {
                if (maxLevelNode->prev->prev->levelNode >= maxLevelNode->prev->levelNode && maxLevelNode->prev->prev->key != -2147483648) {
                    maxLevelNode = maxLevelNode->prev;
                }
                else {
                    temp = maxLevelNode->prev;
                    break;
                }
            }
            while (temp->prev) {
                if (temp->prev->levelNode >= maxLevelNode->levelNode && temp->prev->key != -2147483648) {
                    maxLevelNode = temp;
                }
                temp = temp->prev;
            }
            cout << "H" << maxLevelNode->prev->key;
            voArr[vo] = maxLevelNode->prev;
            voArr[vo]->RorH = "H";
            vo++;
        }
    }
    else if (CommonNode->key != -2147483648) {
        Node* minQuaryNode = nullptr;
        while (maxLevelNode->key > low - 1) {
            maxLevelNode = maxLevelNode->prev;
        }
        minQuaryNode = maxLevelNode;
        int isFlag = 1;
        while (minQuaryNode->prev && minQuaryNode->key > CommonNode->key) {
            if (minQuaryNode->levelNode <= minQuaryNode->prev->levelNode && isFlag == 1) {
                cout << "R" << minQuaryNode->prev->key;
                voArr[vo] = minQuaryNode->prev;
                voArr[vo]->RorH = "R";
                vo++;
            }
            else {
                isFlag = 0;
            }
            if (minQuaryNode->levelNode <= minQuaryNode->prev->levelNode && isFlag == 0) {
                cout << "H" << minQuaryNode->prev->key;
                voArr[vo] = minQuaryNode->prev;
                voArr[vo]->RorH = "H";
                vo++;
            }
            minQuaryNode = minQuaryNode->prev;
        }
        
    }
    cout << endl;
}


//��ȡĿ��ڵ�Ķ�Ӧnext����������ѭ��
vector<Skiplist::Node*> Skiplist::getSon(Node* node, vector<Node*>v1) {
    while (node) {
        if (node->next) v1.push_back(node->next);
        node = node->down;
    }

    return v1;
}


// ��ȡĿ��ڵ�Ķ�Ӧpre��������ǰѭ��
vector<Skiplist::Node*> Skiplist::getFather(Node* node) {
    vector<Node*> res;
    int h = node->levelNode;
    int k = node->key;
    while (node->key > CommonNode->key) {
        if (node->prev->levelNode > h or node->prev->levelNode == h && node->prev->levelNode > 0) {
            Node* t = node->prev;
            while (t->top) t = t->top;
            while (t && t->levelNodeNum <= CommonNode->levelNodeNum) {
                if (t->next && t->next->levelNode >= h) {
                    res.push_back(t);
                    break;
                }
                t = t->down;
            }
            h = node->prev->levelNode;
        }
        node = node->prev;
    }

    return res;
}


void Skiplist::getRes(int highnum) {
    Node* high = nullptr;
    if (quaryLastNode->key = highnum) {
        high = quaryLastNode;
    }
    else {
        for (int i = 0; i < 10; i++) {
            if (fourNode->next && fourNode->key != highnum) {
                fourNode = fourNode->next;
            }
            else {
                high = fourNode;
            }
        }
    }
    vector<Node*> res;
    vector<Node*> temp;
    vector<Node*> v1;
    vector<Node*> t = getFather(high);

    //cout << "father:";
    for (int i = t.size() - 1; i >= 0; i--) {
        //cout << t[i]->key << "(" << t[i]->levelNodeNum << ") ";
        v1 = getSon(t[i], v1);
    }
    //cout << endl;



    for (int i = v1.size() - 1; i >= 0; i--) {
        if (v1[i]->levelNode > high->levelNode && v1[i]->key > high->key) res.push_back(v1[i]);
        else if (v1[i]->key == high->key) {
            temp = getSon(v1[i], temp);
            for (int j = temp.size() - 1; j >= 0; j--) res.push_back(temp[j]);
        }
        else continue;
    }


    // ���������
    //cout << "v1:";
    //for (int i = v1.size() - 1; i >= 0; i--) {
    //    cout << v1[i]->key << "(" << v1[i]->levelNodeNum << ") ";
    //}
    //cout << endl;

    cout << "res:";
    for (int i = 0; i < res.size(); i++) {
        cout << res[i]->key << "-";
        res[i]->RorH = "H";
        voArr[vo] = res[i];
        vo++;
    }
    cout << endl;
}


//��ÿ���ڵ�Ĳ�����ֵ
void Skiplist::getLevelNodeNum() {
    Node* forthFirstNode = nullptr;
    if (fourNode) {
        forthFirstNode = fourNode;
    }
    else if (thirdNode) {
        forthFirstNode = thirdNode;
    }
    else {
        forthFirstNode = secondNode;
    }
    getLevelNodeNum_1(forthFirstNode);
    getLevelNodeNum_1(forthFirstNode->prev);
    while (forthFirstNode->next) {
        getLevelNodeNum_1(forthFirstNode->next);
        forthFirstNode = forthFirstNode->next;
    }
}
//�������²�ڵ��ȡ��ض�����Ϣ
void Skiplist::getLevelNodeNum_1(Node* node) {
    int i = 1;
    while (node->top) {
        i++;
        node->top->levelNodeNum = i ;
        node = node->top;
        if (!node->top) {
            node->levelNode = i;
            downUpdataLevelNode(node, i);
        }
    }
}

//���±�������ÿ�����ڵ�ֵ
void Skiplist::downUpdataLevelNode(Node* node, int n) {
    while (node->down) {
        node->down->levelNode = n;
        node = node->down;
    }
}


//��VO�����ŵ���ʽ���
string voStr;
int flag = 0; //��ǣ���¼�������ٰ����ŵĺ�һ�����ŵ�λ��
void Skiplist::vocoutparenthesis() {
    //��������Ľڵ㰴��keyֵ��С��������
    sort(voArr, voArr + 10, [](Node* a, Node* b) {
        return a->key < b->key;
        });

    
    int i = 0;
    while (voArr[i]->key != 999) {
        Node* node = voArr[i];
        string ss = "";
        vector<int> left;
        vector<int> right;
        bool isEnd = true;

        // ������
        if (node->RorH == "H") {
            while (node->top && node->levelNodeNum <= CommonNode->levelNodeNum) {
                node = node->top;
                if (node->next)
                {
                    ss += "[";
                    isEnd = false;
                }
            }
            ss += voArr[i]->hash;
        }
        else {
            while (node && node->levelNodeNum <= CommonNode->levelNodeNum) {
                if (node->next) 
                {
                    ss += "[";
                    isEnd = false;
                    }
                node = node->top;
            }
            ss += to_string(voArr[i]->key);
        }

        // ������
        if (isEnd) {
            Node* node = voArr[i];
            // ����left
            while (node->key != CommonNode->key)
            {
                while (node->top) node = node->top;
                if (node->prev)
                {
                    node = node->prev;
                    left.push_back(node->levelNodeNum);
                }
            }

            // ����right
            if (voArr[i + 1]->key != 999)
            {
                // ���ܻ������
                node = voArr[i + 1];
                right.push_back(node->levelNode);
                while (node) {
                    while (node->top) node = node->top;
                    if (node->next) right.push_back(node->levelNodeNum);
                    node = node->next;
                }
            }

            for (int i = right.size(); i > 0; i--) {
                if (right.back() > left.back()) right.pop_back();
            }
            for (int num = left.size() - right.size(); num > 0; num--) {
                ss += "]";
            }
        }
        else ss += ",";


        voStr += ss;
        i++;
    }

    cout << voStr << endl;
    praseVO(voStr);
}


// ����hash
void Skiplist::updateHash() {
    Node* p = tail;
    Node* t = p;
    Node* checkPoint = head;
    // ȡ����ײ�head
    while (checkPoint->down != NULL) {
        checkPoint = checkPoint->down;
    }

    // �Ӻ���ǰ����

    while (t != checkPoint) {
        do
        {
            if (p->next != NULL) {
                if (p->down != NULL) {
                    p->hash = p->down->hash + p->next->hash;
                }
                else {
                    p->hash = to_string(p->key) + p->next->hash;
                }
            }
            else if (p == t) {
                p->hash = to_string(p->key);
            }
            else {
                p->hash = p->down->hash;
            }
            p = p->top;
        } while (p != NULL);

        // �Ժ���ǰ
        t = t->prev;
        p = t;
    }

    // ���� root hash
    while (p != NULL) {
        if (p->next != NULL) {
            if (p->down != NULL) {
                p->hash = p->down->hash + p->next->hash;
            }
            else {
                p->hash = p->next->hash;
            }
        }
        else if (p->down == NULL) {
            p->hash = "";
        }
        else {
            p->hash = p->down->hash;
        }

        p = p->top;
    }
    
}

//����ָ��
void Skiplist::updatePoint() {
    Node* p = head;
    // ȡ����ײ�head
    while (p->down != NULL) {
        p = p->down;
    }
    Node* t = p;
    // ������������
    while (t != NULL) {
        p = t;
        t = p->next;
        do {
            if (p->next != NULL && p->next->top != NULL) p->next = NULL;
            p = p->top;
        } while (p != NULL);
    }
}

void Skiplist::praseVO(string voStr) {
    stack<char> stk;
    stack<char> temp;
    string res;

    for (int i = 0; i < voStr.size(); i++) {
        if (voStr[i] == ']') {
            while (stk.top() != '[') {
                if (stk.top() != ',') temp.push(stk.top());
                stk.pop();
            }
            stk.pop();

            while (!temp.empty()) {
                stk.push(temp.top());
                temp.pop();
            }

       }
        else {
            stk.push(voStr[i]);
        }
    }
    
    cout << "root hash:" << CommonNode->hash << endl;

    while (!stk.empty()) {
        res = stk.top() + res;
        stk.pop();
    }
    cout << "ջ�е�Ԫ�أ�" << res  << endl;

    if (res == CommonNode->hash) cout << "��֤�ɹ�����";

    cout << endl;
}


using NodeMap = std::unordered_map<int, Skiplist::Node*>;

// ��ϣ������ʹ�� std::hash<int> ����ڵ�Ĺ�ϣֵ
size_t hashNode(const Skiplist::Node* node) {
    std::hash<int> hasher;
    return hasher(node->key);
}


int main()
{
    //write_csv();
    //std::vector<int> ages;
    //std::vector<int> ids25 = get_id_from_csv("25.csv");
    //std::vector<int> ids18 = get_id_from_csv("18.csv");
    //std::vector<int> ids33 = get_id_from_csv("33.csv");

    //ages.push_back(get_age_from_csv("25.csv"));
    //ages.push_back(get_age_from_csv("18.csv"));
    //ages.push_back(get_age_from_csv("33.csv"));
    //std::sort(ages.begin(), ages.end());

    //std::vector<std::vector<int>> id_age;
    //id_age.push_back(ids25);
    //id_age.push_back(ids18);
    //id_age.push_back(ids33);

    //sort_all_ages(id_age);

    Skiplist L;

    //Skiplist L0;
    //Skiplist L1;
    //Skiplist L2;
    //std::vector<Skiplist> skip_lists;
    //skip_lists.push_back(L0);
    //skip_lists.push_back(L1);
    //skip_lists.push_back(L2);
    //int count = 0;

    for (int i = 1; i <= 10; i++)
    {
        Skiplist::Node* node = new Skiplist::Node{};
        node->key = i;
        //cout << hashNode(node) << endl;
        L.insert(i);
    }
    cout << "ԭʼ����:" << endl;
    L.showSkiplist();
    cout << "�����С:" << L.getSize() << endl;
    cout << "������� :" << L.getLevel() << endl;

    //Skiplist::Node* bot = L.head;
    //while (bot->down) bot = bot->down;

    //while (!id_age.empty()) {
    //    for (const auto& id : id_age.back())
    //    {
    //        Skiplist::Node* node = new Skiplist::Node{};
    //        node->key = id;
    //        //cout << hashNode(node) << endl;
    //        skip_lists[count].insert(id);
    //    }
    //    bot->next->down = skip_lists[count].head;
    //    bot = bot->next;
    //    id_age.pop_back();
    //    count += 1;
    //}

    while (1) {
        cout << "________________________" << endl;

        cout << "++++++++++++++++++++++++" << endl;
        L.generateSkiplist();
        cout << "++++++++++++++++++++++++" << endl;
        cout << "��������Ҫ��ѯ�ķ�Χ:��Χͷ:";
        int low, high;
        cin >> low;
        cout << "��������Ҫ��ѯ�ķ�Χ:��Χβ:";
        cin >> high;
        L.generateVO(low, high);
        L.getLevelNodeNum();
        L.findminparent(low, high);
        L.updatePoint();
        L.updateHash();
        L.getRes(high + 1);
        L.vocoutparenthesis();
    }
    
    //L.getLevelNodeNum();
    //L.showSkiplist();

   /* cout << "���ҽڵ� �ͻ�����̨���� :" << endl;
    int inp;
    cin >> inp;
    cout << endl;
    if (L.search(inp) == 1) {
        cout << "�ýڵ����������;" << endl;
    }
    else {
        cout << "�ýڵ㲻��������;" << endl;
    }
    cout << "________________________" << endl;


    cout << "�����½ڵ� �ͻ�����̨���� :" << endl;
    int insertNode;
    cin >> insertNode;
    cout << endl;
    L.insert(insertNode);
    L.showSkiplist();
    cout << "�����С:" << L.getSize() << endl;
    cout << "________________________" << endl;


    cout << "ɾ���ڵ� �ͻ�����̨���� :" << endl;
    int deleteNode;
    cin >> deleteNode;
    cout << endl;
    L.remove(deleteNode);
    L.showSkiplist();
    cout << "�����С:" << L.getSize() << endl;
    cout << "________________________" << endl;*/

    return 0;
}


