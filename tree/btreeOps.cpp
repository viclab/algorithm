//二叉树常用操作
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

//向二叉排序树中插入元素-非递归
void InsertBinaryTree(BTree *root, int val);

//函数：二叉树遍历-前序遍历
void PreOrderTraversal(BTree root);

//函数：二叉树遍历-中序遍历
void InOrderTraversal(BTree root);

//函数：二叉树遍历-后序遍历
void PostOrderTraversal(BTree root);

//函数：重建二叉树，依据前序遍历结果和中序遍历结果
void BuildBTreeWithInorderPreOrder(int pre[], int in[], int n);

//函数：判断二叉树的后序遍历是否合法
bool IsPostOrderValid(int post[], int n);

//函数：二叉树中和为某值的路径
void FindPathWithSum(BTree root, int expectedSum);

//函数：将二叉树转化成双向链表
BTreeNode* ConvertNode(BTree root);

//函数：求二叉树深度
int TreeDepth(BTree root);

//函数：判断二叉树是否平衡二叉树
bool IsAVLTree(BTree root);

//求二叉树第K层节点个数
int GetNodeNumKthLevel(BTree root);

//求二叉树中两个节点的最大距离
int GetMaxDistance(BTree root);

//判断一颗二叉树是否为完全二叉树
bool IsCompleteTree(BTree root);

//求一个二叉树中两个节点最低公共祖先节点
BTreeNode* GetLCANode(BTree root);

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

//函数：重建二叉树，依据前序遍历结果和中序遍历结果
//思路：1.从前序系列中取第一个元素x，再在中序序列中找到这个元素x
//      2.以x为界，以x的值新建根节点root，x左边即为左子树(记节点数为ln),x右边即为右子树(记节点数为rn)
//      3.在前序序列中x后，前ln个节点即为左子树，后rn个节点即为右子树
//      4.设置root的左右孩子分别为1、2、3步递归调用左右子树序列后的返回值
BTreeNode* BuildBTreeWithInorderPreOrder(int pre[], int in[], int n)
{
    assert(pre != NULL && in != NULL && n > 0);
    return Construct(pre, pre + n - 1, in, in + n - 1);
}

BTreeNode* Construct(int *preStart, int *preEnd, int *inStart, int *inEnd)
{
    int rootVal = *preStart;
    BTreeNode *root = new BTreeNode();
    root->value = rootVal;
    root->lchild = root->rchild = NULL;

    //定义递归出口：当前序、中序序列中都仅有一个元素时，递归返回该节点
    if (preStart == preEnd)
    {
        if (inStart == inEnd && *preStart == *inStart)
            return root;
        else
            throw "Invalid Input.";
    }

    //在中序序列中查找根节点
    int *pos = inStart;
    while (pos <= inEnd && *pos != rootVal)
        ++pos;
    if (pos == inEnd && *pos != rootVal)
        throw "Invalid Input.";

    int leftLength = pos - inStart;
    int *leftPreEnd = preStart + leftLength;
    
    //构建左子树
    if (leftLength > 0)
    {
        root->lchild = Construct(preStart + 1, leftPreEnd, inStart, pos - 1);
    }
    //构建右子树
    if (leftLength < preEnd - preStart)
    {
        root->rchild = Construct(leftPreEnd + 1, preEnd, pos + 1, inEnd);
    }

    return root;
}

//函数：判断二叉树的后序遍历是否合法
bool IsPostOrderValid(int post[], int n)
{
    assert(post != NULL && n > 0);
    
    //取序列最后一个元素作为根
    int root = post[n-1];
    
    //扫描序列，比根小作为左子树
    int leftLength, rightLength;
    int *lend = post;
    while(lend <= post + n - 1 && *lend < root)
        ++lend;
    leftLength = lend - post;
    
    //比根大作为右子树
    int *rend = lend;
    while(rend <= post + n - 1)
    {
        if (*rend < root)
            return false;
        ++rend;
    }
    rightLength = n - leftLength - 1;
    
    //判断左子树是否二叉搜索树
    bool left = true;
    if (leftLength > 0)
        left = IsPostOrderValid(post, leftLength);

    //判断左子树是否二叉搜索树
    bool right = true;
    if (rightLength > 0)
        left = IsPostOrderValid(rend, rightLength);

    return left && right;

}

//函数：二叉树中和为某值的路径
void FindPathWithSum(BTree root, int expectedSum)
{
    assert(root != NULL);
    vector<BTreeNode*> path;
    FindPathCore(root, path, 0, expectedSum);
}

void FindPathCore(BTree root, vector<BTreeNode*> &path, 
        int currentSum, int expectedSum)
{
    currentSum += root->value;
    path.push_back(root);
    
    //递归出口：如果路径到达页节点，且和为期望值，则打印
    bool isLeaf = (root->lchild == NULL && root->rchild == NULL);
    if (isLeaf && currentSum == expectedSum)
    {
        vector<BTreeNode*>::iterator ite = path.begin();
        for (;ite != path.end(); ++ite)
            cout << ite->value << "\t";
        cout << endl;
    }

    //如果不是叶节点，则遍历他的子节点
    if (root->lchild != NULL)
        FindPathCore(root->lchild, path, currentSum, expectedSum);
    if (root->rchild != NULL)
        FindPathCore(root->rchild, path, currentSum, expectedSum);

    //该条路径不合要求，路径上删除该节点
    //currentSum -= root->value;    //不需要，因为非引用传递
    path.pop_back(root);
}
            

//函数：将二叉树转化成双向链表
BTreeNode* ConvertNode(BTree root)
{
    assert(root != NULL);
    BTreeNode* lastNode = NULL;
    ConvertNodeCore(root, lastNode);
    BTreeNode* head = lastNode;
    while(head != NULL && head->lchild != NULL)
        head = lchild;
    return head;
}

void ConvertNodeCore(BTreeNode* curNode, BTreeNode* &preNode)
{
    //可以借用中序遍历的思路
    if (curNode == NULL)
        return;
    if(curNode->lchild != NULL)
        ConvertNodeCore(curNode->lchild, preNode);
    
    //curNode前驱指向preNode, preNode后继指向curNode
    curNode->lchild = preNode;
    if (preNode != NULL)
        preNode->rchild = curNode;
    
    preNode = curNode;
    
    if(curNode->rchild != NULL)
        ConvertNodeCore(curNode->rchild, preNode);
}


//函数：求二叉树深度
int TreeDepth(BTree root)
{
    if (root == NULL)
        return 0;
    int llen = TreeDepth(root->lchild);
    int rlen = TreeDepth(root->rchild);
    return 1 + (llen > rlen ? llen : rlen);
}
    
//函数：判断二叉树是否平衡二叉树
bool IsAVLTree(BTree root)
{
    if (root == NULL)
        return true;
    int llen = TreeDepth(root->lchild);
    int rlen = TreeDepth(root->rchild);
    if (llen - rlen <= -1 || llen - rlen >= 1)
        return false;
    else
        return IsAVLTree(root->lchild) && IsAVLTree(root->rchild);
}

//层次遍历二叉树
void TraversalByLevel(BTree root)
{
    assert(root != NULL);
    queue<BTreeNode*> que;
    que.push(root);
    while(!que.empty())
    {
        BTreeNode *node = que.front();
        cout << node->value << "\t";
        que.pop();
        if (node->lchild != NULL)
            que.push(node->lchild);
        if (node->rchild != NULL)
            que.push(node->rchild);
    }
}
        
//求二叉树第K层节点个数
int GetNodeNumKthLevel(BTree root, int k)
{
    if (root == NULL)
        return 0;
    if (k == 1)
        return 1;
    return GetNodeNumKthLevel(root->lchild, k - 1) 
        + GetNodeNumKthLevel(root->rchild, k - 1);
}
    

//求二叉树中两个节点的最大距离
int GetMaxDistance(BTree root)
{
    if (root == NULL)
        return 0;
    int maxLeft = 
}

//判断一颗二叉树是否为完全二叉树
bool IsCompleteTree(BTree root)
{
    //按照层次遍历，当遇到一个节点的左子树为空时，则该节点右子树必须为空。
    //且后面遍历的节点必须都为叶节点
    assert(root != NULL);
    queue<BTreeNode*> que;
    que.push(root);
    bool leaf = false;
    while (!que.empty())
    {
        BTreeNode* node = que.front();
        que.pop();
        if(leaf && (node->lchild != NULL || node->rchild != NULL))  //若应是叶节点却不是
            return false;
        if (node->lchild == NULL && node->rchild != NULL)           //若左孩子为NULL，右却不为NULL
            return false;
        if (node->rchild == NULL)
            leaf = true;

        if (root->lchild != NULL)
            que.push(root->lchild);
        if (root->rchild != NULL)
            que.push(root->rchild);
    }
}
        
            
        
    

//求一个二叉树中两个节点最低公共祖先节点
BTreeNode* GetLCANode(BTree root);

