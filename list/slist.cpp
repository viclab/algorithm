//实现带表头单链表及其基本操作
//Thu Jul 17 06:33:32 PDT 2014
#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

typedef struct LinkNode{
    int data;
    LinkNode * next;
}*LinkList;

//创建单链表
LinkList CreateList(int *arr, int n);

//打印单链表
void PrintList(LinkList head);

//倒序打印单链表
void PrintListReverse(LinkList head);

//新建链表节点
LinkNode* CreateNode(int value);

//删除链表中某个节点
//时间复杂度要求:O(1)
void DeleteNodeExist(LinkList head, LinkNode* node);

//删除链表中数据为给定某值的节点
void DeleteNodeWithValue(LinkList head, int value);

//获得链表中倒数第K个节点
LinkNode* GetLastKNode(LinkList head, int k);

//反转链表
LinkList ReverseList(LinkList head);

//合并两个已排序链表
LinkList MergeList(LinkList aHead, LinkList bHead);

int main()
{
    int a[] = {1, 3, 5, 7};
    int b[] = {2, 4, 6, 8};
    LinkList aList = CreateList(a, sizeof(a) / sizeof(int));
    LinkList bList = CreateList(b, sizeof(b) / sizeof(int));
    
    //PrintList(aList);
    //PrintListReverse(aList);
    //ReverseList(aList);
    //PrintList(aList);
    //cout << GetLastKNode(aList, 2)->data;
    ReverseList(aList);
    ReverseList(bList);
    PrintList(aList);
    PrintList(bList);

    LinkList cList = MergeList(aList, bList);
    PrintList(cList);
    DeleteNodeWithValue(cList, 8);
    PrintList(cList);
    LinkNode *pos = cList;
    while(pos->next != NULL)
        pos = pos->next;
    DeleteNodeExist(cList, pos);
    PrintList(cList);

    return 0;
}



//头插法创建单链表
LinkList CreateList(int *arr, int n)
{
    assert(arr != NULL && n > 0);
    LinkNode *head = new LinkNode;
    LinkNode *newNode;
    head->next = NULL;
    for (int i=0; i<n; ++i) {
        newNode = new LinkNode;
        newNode->data = *(arr + i);
        newNode->next = head->next;
        head->next = newNode;
    }

    return head;
}
    


//打印单链表
void PrintList(LinkList head)
{
    cout << "打印单链表" << endl;
    LinkNode *pos = head->next;
    while (pos != NULL)
    {
        cout << pos->data << " ";
        pos = pos->next;
    }
    cout << endl;
}

//倒序打印单链表
void PrintListReverse(LinkList head)
{
    stack<LinkNode *> st;
    LinkNode *pos = head->next;
    while (pos != NULL)
    {
        st.push(pos);
        pos = pos->next;
    }
    
    cout << "逆向打印单链表" << endl;
    while (!st.empty())
    {
        cout << st.top()->data << " ";
        st.pop();
    }
    cout << endl;
}
    

//删除链表中某个节点
//时间复杂度要求:O(1)
void DeleteNodeExist(LinkList head, LinkNode* node)
{
    assert(head->next != NULL && node != NULL);
    LinkNode *behind = node->next;
    if (behind == NULL)
    {
        LinkNode *prev = head;
        while (prev->next != node)
            prev = prev->next;
        prev->next = behind;
        delete node;
        return;
    }
    node->data = behind->data;
    node->next = behind->next;
    delete behind;
}

//删除链表中数据为给定某值的节点
void DeleteNodeWithValue(LinkList head, int value)
{
    assert(head->next != NULL);
    LinkNode *ahead, *behind;
    ahead = head;
    behind = ahead->next;
    while (behind != NULL && behind->data != value)
    {
        ahead = behind;
        behind = behind->next;
    }
    if (behind != NULL && behind->data == value)
    {
        ahead->next = behind->next;
        delete behind;
    }
}


//获得链表中倒数第K个节点
LinkNode* GetLastKNode(LinkList head, int k)
{
    assert(head->next != NULL && k > 1);
    LinkNode *ahead, *behind;
    ahead = behind = head;
    while (k-- > 1 && ahead->next != NULL)
        ahead = ahead->next;
    if (k!=1 && NULL == ahead->next)
        return NULL;
    while (ahead->next != NULL)
    {
        ahead = ahead->next;
        behind = behind->next;
    }
    return behind;
}
        
    

//反转链表
LinkList ReverseList(LinkList head)
{
    assert(head->next != NULL);

    LinkNode *p, *q;
    q = head->next;
    head->next = NULL;
    while (q != NULL)
    {
        p = q;
        q = q->next;
        p ->next = head->next;
        head->next = p;
    }
    return head;
}


//合并两个已排序链表
LinkList MergeList(LinkList aHead, LinkList bHead)
{
    assert(aHead->next != NULL && bHead->next != NULL);
    LinkNode *p, *q, *r, *i;
    i = aHead;
    r = bHead;
    p = i->next;
    q = r->next;
    while (p!=NULL && q!=NULL) {
        if (p->data >=  q->data) {
            r = q;
            q = q->next;
            r->next = p;
            i->next = r;
        }
        else {
            i = p;
            p = p->next;
        }
    }

    if (p == NULL)
        i->next = q;
    delete bHead;
    return aHead;
}

