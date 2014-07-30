//二叉树及其常用操作
//Thu Jul 17 06:40:24 PDT 2014
#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;

typedef struct BTreeNode {
    int value;
    BTreeNode *lchild;
    BTreeNode *rchild;
}*BTree;

//函数：根据所给数据创建二叉排序树
BTree CreateBinaryTree(int *arr, int n);

//向二叉排序树中插入元素-递归
BTree InsertBTreeRecursion(BTree &root, int val);

//向二叉排序树中插入元素-非递归
void InsertBinaryTree(BTree *root, int val);

//函数：二叉树遍历-前序遍历
void PreOrderTraversal(BTree root);

//函数：二叉树遍历-中序遍历
void InOrderTraversal(BTree root);

//函数：二叉树遍历-后序遍历
void PostOrderTraversal(BTree root);

//函数：二叉树遍历-前序遍历(非递归方式)
void PreOrderNonrecursive(BTree root);

//函数：二叉树遍历-中序遍历(非递归方式)
void InOrderNonrecursive(BTree root);

//函数：二叉树遍历-后序遍历(非递归方式)
void PostOrderNonrecursive(BTree root);

int main()
{
    int a[] = {7, 2, 8, 3, 6, 4, 5, 1};
    int n = sizeof(a) / sizeof(a[0]);
    BTree bt = CreateBinaryTree(a, n);

    cout << "前序遍历：";
    PreOrderTraversal(bt);
    cout << endl;

    cout << "中序遍历：";
    InOrderTraversal(bt);
    cout << endl;

    cout << "后序遍历：";
    PostOrderTraversal(bt);
    cout << endl;

    cout << "非递归前序：";
    PreOrderNonrecursive(bt);
    cout << endl;

    cout << "非递归中序：";
    InOrderNonrecursive(bt);
    cout << endl;

    cout << "非递归后序：";
    PostOrderNonrecursive(bt);
    cout << endl;
    return 0;
}

//函数：根据所给数据创建二叉排序树
BTree CreateBinaryTree(int *arr, int n)
{
    assert(arr != NULL && n > 0);
    BTree root = NULL;
    for (int i=0; i<n; ++i)
        //InsertBinaryTree(&root, *(arr+i));
        InsertBTreeRecursion(root, *(arr+i));
    return root;
}

//向二叉排序树中插入元素-递归
BTree InsertBTreeRecursion(BTree &root, int val)
{
    if (root == NULL) {
        root = new BTreeNode;
        root->value = val;
        root->lchild = root->rchild = NULL;
    } 
    else if (val < root->value) 
        root->lchild = InsertBTreeRecursion(root->lchild, val);
    else if (val > root->value)
        root->rchild = InsertBTreeRecursion(root->rchild, val);

    return root;
}


//向二叉排序树中插入元素-非递归
void InsertBinaryTree(BTree *root, int val)
{

    BTreeNode *newNode = new BTreeNode();
    newNode->value = val;
    newNode->lchild = newNode->rchild = NULL;

    BTreeNode *pre, *cur;
    pre = NULL;
    cur = *root;
    while (cur != NULL)
    {
        pre = cur;
        if (val < cur->value)
            cur = cur->lchild;
        else
            cur = cur->rchild;
    }

    if (NULL == pre)
        *root = newNode;
    else if (val < pre->value)
        pre->lchild = newNode;
    else
        pre->rchild = newNode;

    //下面为早先实现的一个版本，可以实现，但代码不够简介
    //BTreeNode *node = new BTreeNode;
    //node->value = val;
    //node->lchild = node->rchild = NULL;
    //if (*root == NULL)
    //{
    //    *root = node;
    //    return;
    //}

    //BTreeNode *bp = *root;
    //while (bp->value > val && bp->lchild != NULL
    //        || bp->value < val && bp->rchild != NULL) {
    //    if (bp->value > val)
    //        bp = bp->lchild;
    //    else
    //        bp = bp->rchild;
    //}

    //if (bp->value > val) 
    //    bp->lchild = node;
    //else
    //    bp->rchild = node;

}
    


//函数：二叉树遍历-前序遍历
void PreOrderTraversal(BTree root)
{
    if (root != NULL)
    {
        cout << root->value << "\t";
        PreOrderTraversal(root->lchild);
        PreOrderTraversal(root->rchild);
    }
}

//函数：二叉树遍历-中序遍历
void InOrderTraversal(BTree root)
{
    if (root != NULL)
    {
        InOrderTraversal(root->lchild);
        cout << root->value << "\t";
        InOrderTraversal(root->rchild);
    }
}

//函数：二叉树遍历-后序遍历
void PostOrderTraversal(BTree root)
{
    if (root != NULL)
    {
        PostOrderTraversal(root->lchild);
        PostOrderTraversal(root->rchild);
        cout << root->value << "\t";
    }
}

//函数：二叉树遍历-前序遍历(非递归方式)
void PreOrderNonrecursive(BTree root)
{
    assert(root != NULL);
    stack<BTreeNode *> st;
    BTreeNode *pn;
    st.push(root);
    while (!st.empty()) {
        pn = st.top();
        st.pop();
        cout << pn->value << "\t";
        if (pn->rchild != NULL)
            st.push(pn->rchild);
        if (pn->lchild != NULL)
            st.push(pn->lchild);
    }
}
    

//函数：二叉树遍历-中序遍历(非递归方式)
//思路：对于任一节点P
//  1.若其左孩子不为空，则将P入栈并将P的左孩子置为当前的P，然后对P执行同样处理
//  2.若其左孩子为空，则取栈顶元素，并进行出栈操作，访问该栈顶节点，然后将P置为该节点的右孩子
//  3.直到P为NULL并且栈为空则遍历结束
void InOrderNonrecursive(BTree root)
{
    //assert(root != NULL);
    stack<BTreeNode *> st;
    BTreeNode *pn = root;

    while (pn != NULL || !st.empty()) {
        while (pn != NULL) {
            st.push(pn);
            pn = pn->lchild;
        }

        if (!st.empty()) {
            pn = st.top();
            st.pop();
            cout << pn->value << "\t";
            pn = pn->rchild;
        }
    }
}

//函数：二叉树遍历-后序遍历(非递归方式)
//思路：对于这样的节点：
//          （1）叶节点
//          （2）左孩子或右孩子都已被访问过
void PostOrderNonrecursive(BTree root)
{
    stack<BTreeNode *> st;
    st.push(root);
    BTreeNode *pn, *pre = NULL;

    while (!st.empty()) {
        pn = st.top();

        if ((pn->lchild == NULL && pn->rchild == NULL)
                || (pre != NULL &&
                    (pre == pn->lchild || pre == pn->rchild))) {
            cout << pn->value << "\t";
            st.pop();
            pre = pn;
        } else {
            if (pn->rchild != NULL)
                st.push(pn->rchild);
            if (pn->lchild != NULL)
                st.push(pn->lchild);
        }
    }
}

