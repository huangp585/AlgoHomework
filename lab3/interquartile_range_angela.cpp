#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>

using namespace std;

/* �� treap �Ӱ�(tree + heap) ******
 * key: BST���ʽ�A���l��key <= root��key < �k�l��key
 * pri: heap���ʽ�A�̤j���broot�Apri�O�Φbmerge���ɭ����L�i�H�������
 */
class node
{
public:
    node* l, * r;
    int key, pri, size;

    node(int k) :l(NULL), r(NULL), key(k), pri(rand()), size(1) {};
    void up()  // ��s size
    {
        size = 1;
        if (l) size = size + l->size;
        if (r) size = size + r->size;
    }
};

/* treap ��Ӯ֤ߤu��: merge & split */
// merge���ɭԡAa���Ҧ�key <= b���Ҧ�key
node* merge(node* a, node* b)
{
    if (a == NULL) return b;  // *���n�g��==
    if (b == NULL) return a;

    if (a->pri > b->pri)  // merge��a�Oroot
    {
        a->r = merge(a->r, b);  // a��key���p�󵥩�b��key�A�ҥH�X�֫�a->l���|��
        a->up();  // renew size
        return a;
    }
    else  // merge��b�Oroot
    {
        b->l = merge(a, b->l);
        b->up();  // renew size
        return b;
    }
}

// split����Aa��key�� < k�Ab��key�� >= k
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
            split(s->r, a->r, b, k);  // s�����l��Mroot�|�Q����a�Aa���k���٤��T�w�A�n�~���
        }
        else
        {
            b = s;
            split(s->l, a, b->l, k);
        }
        s->up();  // ��s�������ƶq(a��b�u���@�ӷ|�ܡA�ܪ����ӴN�Os��)
    }
}

// ��treap���J�s�Ʀr
void insert(node*& rt, int k)
{
    node* a, * b;
    split(rt, a, b, k);  // ��������Aa��key���p��k�Ab��key���j�󵥩�k
    rt = merge(a, merge(new node(k), b));  // ��T��treap�X��
}

// �M���k�p����
double findKSmall(node* rt, int k)
{
    if (rt->l == NULL)
    {
        if (k == 1) return rt->key;
        return findKSmall(rt->r, k - 1);
    }

    if (rt->l->size == k - 1) return rt->key;

    if (rt->l->size >= k)  // �����l��h��
    {
        return findKSmall(rt->l, k);
    }
    else //���k�l��h��
    {
        return findKSmall(rt->r, k - (rt->l->size) - 1);
    }
}

// �M���k�j����
double findKBig(node* rt, int k)
{
    if (rt->r == NULL)
    {
        if (k == 1) return rt->key;
        return findKBig(rt->l, k - 1);
    }

    if (rt->r->size == k - 1) return rt->key;

    if (rt->r->size >= k)  // ���k�l��h��
    {
        return findKBig(rt->r, k);
    }
    else //�����l��h��
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

        // �������ƶq = 2n �άO 2n + 1
        if (n % 2 == 1)  // n�O�_��
        {
            k = n / 2;  // n = 2k + 1
            Q1 = findKSmall(rt, k + 1);
            Q3 = findKBig(rt, k + 1);
        }
        else  // n�O����
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