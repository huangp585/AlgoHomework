#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>

using namespace std;

/* 用 treap 來做(tree + heap) ******
 * key: BST的性質，左子樹的key <= root的key < 右子樹的key
 * pri: heap的性質，最大的在root，pri是用在merge的時候讓他可以近似平衡
 */
class node
{
public:
    node* l, * r;
    int key, pri, size;

    node(int k) :l(NULL), r(NULL), key(k), pri(rand()), size(1) {};
    void up()  // 更新 size
    {
        size = 1;
        if (l) size = size + l->size;
        if (r) size = size + r->size;
    }
};

/* treap 兩個核心工具: merge & split */
// merge的時候，a的所有key <= b的所有key
node* merge(node* a, node* b)
{
    if (a == NULL) return b;  // *不要寫反==
    if (b == NULL) return a;

    if (a->pri > b->pri)  // merge後a是root
    {
        a->r = merge(a->r, b);  // a的key都小於等於b的key，所以合併後a->l不會變
        a->up();  // renew size
        return a;
    }
    else  // merge後b是root
    {
        b->l = merge(a, b->l);
        b->up();  // renew size
        return b;
    }
}

// split之後，a的key都 < k，b的key都 >= k
void split(node* s, node*& a, node*& b, int k)
{
    if (s == NULL)
    {
        a = NULL;
        b = NULL;
    }
    else
    {
        if (s->key < k)
        {
            a = s;
            split(s->r, a->r, b, k);  // s的左子樹和root會被分到a，a的右邊還不確定，要繼續分
        }
        else
        {
            b = s;
            split(s->l, a, b->l, k);
        }
        s->up();  // 更新全部的數量(a跟b只有一個會變，變的那個就是s的)
    }
}

// 往treap插入新數字
void insert(node*& rt, int k)
{
    node* a, * b;
    split(rt, a, b, k);  // 分完之後，a的key都小於k，b的key都大於等於k
    rt = merge(a, merge(new node(k), b));  // 把三個treap合併
}

// 尋找第k小的數
double findKSmall(node* rt, int k)
{
    if (rt->l == NULL)
    {
        if (k == 1) return rt->key;
        return findKSmall(rt->r, k - 1);
    }

    if (rt->l->size == k - 1) return rt->key;

    if (rt->l->size >= k)  // 往左子樹去找
    {
        return findKSmall(rt->l, k);
    }
    else //往右子樹去找
    {
        return findKSmall(rt->r, k - (rt->l->size) - 1);
    }
}

// 尋找第k大的數
double findKBig(node* rt, int k)
{
    if (rt->r == NULL)
    {
        if (k == 1) return rt->key;
        return findKBig(rt->l, k - 1);
    }

    if (rt->r->size == k - 1) return rt->key;

    if (rt->r->size >= k)  // 往右子樹去找
    {
        return findKBig(rt->r, k);
    }
    else //往左子樹去找
    {
        return findKBig(rt->l, k - (rt->r->size) - 1);
    }
}

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);

    int num;
    cin >> num;
    cout << "0\n";

    node* rt = new node(num);

    while (cin >> num)
    {
        if (num == 0) break;

        insert(rt, num);

        int n = (rt->size) / 2, k;
        double Q1, Q3, IQR;

        // 全部的數量 = 2n 或是 2n + 1
        if (n % 2 == 1)  // n是奇數
        {
            k = n / 2;  // n = 2k + 1
            Q1 = findKSmall(rt, k + 1);
            Q3 = findKBig(rt, k + 1);
        }
        else  // n是偶數
        {
            k = n / 2;  // n = 2k
            Q1 = (findKSmall(rt, k) + findKSmall(rt, k + 1)) / 2.0;
            Q3 = (findKBig(rt, k) + findKBig(rt, k + 1)) / 2.0;
        }


        IQR = Q3 - Q1;
        if (abs(IQR - (int)IQR) < 0.00000001) cout << (int)IQR << '\n';
        else cout << fixed << setprecision(1) << IQR << '\n';
    }

    return 0;
}