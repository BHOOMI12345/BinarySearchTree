#include <bits/stdc++.h>

using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int d)
    {
        data = d;
        left = NULL;
        right = NULL;
    }
};

Node *minimumFromRight(Node *root)
{
    Node *temp = root;
    while (temp->left != NULL)
    {
        temp = temp->left;
    }

    return temp;
}

Node *deleteNode(Node *root, int x)
{
    if (root == NULL)
    {
        return false;
    }

    if (root->data == x)
    {
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }

        if (root->left != NULL && root->right == NULL)
        {
            Node *temp = root->left;
            delete root;
            return root->left;
        }

        if (root->left == NULL && root->right != NULL)
        {
            Node *temp = root->right;
            delete root;
            return root->right;
        }

        if (root->left != NULL && root->right != NULL)
        {
            int min = minimumFromRight(root->right)->data;
            root->data = min;
            root->right = deleteNode(root->right, min);
            return root;
        }
    }

    else if (root->data < x)
    {
        root->right = deleteNode(root->right, x);
        return root;
    }

    else
    {
        root->left = deleteNode(root->left, x);
        return root;
    }
}

bool isBst(Node *root, int min, int max)
{
    if (root == NULL)
    {
        return true;
    }
    if (root->data > min && root->data < max)
    {
        bool left = isBst(root->left, min, root->data);
        bool right = isBst(root->right, root->data, max);
        return left && right;
    }

    else
    {
        return false;
    }
}

bool isValidBST(Node *root)
{
    return isBst(root, INT_MIN, INT_MAX);
}

int height(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    int left = height(root->left);
    int right = height(root->right);
    int ans = max(left, right) + 1;
    return ans;
}

pair<int, int> diameter(Node *root)
{
    if (root == NULL)
    {
        return make_pair(0, 0);
    }

    pair<int, int> left = diameter(root->left);
    pair<int, int> right = diameter(root->right);

    int leftAns = left.first;
    int rightAns = right.first;
    int op3 = left.second + right.second + 1;

    pair<int, int> ans;
    ans.first = max(leftAns, max(rightAns, op3));
    ans.second = max(left.second, right.second) + 1;

    return ans;
}

pair<bool, int> isBalanced(Node *root)
{
    if (root == NULL)
    {
        return make_pair(true, 0);
    }

    pair<bool, int> left = isBalanced(root->left);
    pair<bool, int> right = isBalanced(root->right);

    bool leftAns = left.first;
    bool rightAns = right.first;
    bool diff = abs(left.second - right.second) <= 1;

    pair<bool, int> ans;
    ans.second = max(left.second, right.second) + 1;

    if (leftAns && rightAns && diff)
    {
        ans.first = true;
    }
    else
    {
        ans.first = false;
    }

    return ans;
}

bool isIdentical(Node *r1, Node *r2)
{
    if (r1 == NULL && r2 == NULL)
    {
        return true;
    }

    if (r1 != NULL && r2 == NULL)
    {
        return false;
    }

    if (r1 == NULL && r2 != NULL)
    {
        return false;
    }

    bool left = isIdentical(r1->left, r2->left);
    bool right = isIdentical(r1->right, r2->right);

    bool cond = r1->data == r2->data;

    if (left && right && cond)
    {
        return true;
    }

    else
    {
        return false;
    }
}

pair<bool, int> checkSum(Node *root)
{
    if (root == NULL)
    {
        pair<bool, int> p = make_pair(true, 0);
        return p;
    }

    if (root->left == NULL && root->right == NULL)
    {
        pair<bool, int> p = make_pair(true, root->data);
        return p;
    }

    pair<bool, int> left = checkSum(root->left);
    pair<bool, int> right = checkSum(root->right);

    bool leftAns = left.first;
    bool rightAns = right.first;
    bool val = root->data == left.second + right.second;

    pair<bool, int> ans;

    if (leftAns && rightAns && val)
    {
        ans.first = true;
        ans.second = 2 * root->data;
    }
    else
    {
        ans.second = false;
    }
    return ans;
}

vector<int> zigzagTraversal(Node *root)
{
    vector<int> result;
    if (root == NULL)
    {
        return result;
    }

    queue<Node *> q;
    q.push(root);

    bool leftToRight = true;
    while (!q.empty())
    {
        int size = q.size();
        vector<int> ans(size);
        for (int i = 0; i < size; i++)
        {
            Node *frontnode = q.front();
            q.pop();
            int index = leftToRight ? i : size - i - 1;
            ans.push_back(frontnode->data);

            if (frontnode->left)
            {
                q.push(frontnode->left);
            }

            if (frontnode->right)
            {
                q.push(frontnode->right);
            }
        }

        leftToRight = !leftToRight;
        for (auto i : ans)
        {
            result.push_back(i);
        }
    }

    return result;
}


void traversalLeft(Node * root, vector<int> ans)
{
    if((root==NULL) || ( root->left ==NULL && root->right==NULL))
    {
        return;
    }

    ans.push_back(root->data);
    if(root->left)
    {
        traversalLeft(root->left,ans);
    }
    else
    {
        traversalLeft(root->right,ans);
    }
}

void traversalLeaf(Node * root, vector<int> ans)
{
    if(root==NULL)
    {
        return;
    }

    if(root->left==NULL && root->right==NULL)
    {
        ans.push_back(root->data);
    }
    if(root->left)
    {
        traversalLeaf(root->left,ans);
    }
    else
    {
        traversalLeaf(root->right,ans);
    }
}

void traversalRight(Node * root, vector<int> ans)
{
    if((root==NULL)||(root->left ==NULL && root->right ==NULL))
    {
        return;
    }
    if(root->right)
    {
        traversalRight(root->right, ans);
    }
    else
    {
        traversalRight(root->left,ans);
    }

    ans.push_back(root->data);

}

vector<int> boundaryTraversal(Node * root)
{
    vector<int> result;
    if(root==NULL)
    {
        return result;
    }
    result.push_back(root->data);

    traversalLeft(root->left,result);
    traversalLeaf(root->left,result);
    traversalLeaf(root->right, result);
    traversalRight(root->right, result);
    return result;
}

vector<int> topView(Node * root)
{
    vector<int> ans;
    if(root==NULL)
    {
        return ans;
    }

    map<int,int> topNode;
    queue<pair<Node *, int>> q;

    q.push(make_pair(root,0));
    while(q.empty())
    {
        pair<Node * ,int> temp  = q.front();
        q.pop();
        Node * frontNode = temp.first;
        int hd = temp.second;

        if(topNode.find(hd) == topNode.end())
        {
            topNode[hd] = frontNode->data;
        }

        if(frontNode->left)
        {
            q.push(make_pair(frontNode->left,hd-1));
        }

        if(frontNode->right)
        {
            q.push(make_pair(frontNode->right,hd+1));
        }
    }

    for(auto i: topNode)
    {
        ans.push_back(i.second);
    }
    return ans;
}


vector<int> bottomView(Node *root)
{
    vector<int> ans;
    if(root==NULL)
    {
        return ans;
    }

    map<int, int> bottomNode;
    queue<pair<Node * , int>> q;
    q.push(make_pair(root,0));

    while(!q.empty())
    {
        pair<Node *, int> temp = q.front();
        Node * frontNode   = temp.first;
        int hd = temp.second;

        bottomNode[hd] = frontNode->data;

        if(frontNode->left)
        {
            q.push(make_pair(frontNode->left,hd-1));
        }

        if(frontNode->right)
        {
            q.push(make_pair(frontNode->right,hd+1));
        }

    }

    for(auto i : bottomNode)
    {
        ans.push_back(i.second);
    }
    return ans;
}

vector<int> solve(Node * root, vector<int> & ans, int level)
{
    if(root==NULL)
    {
        return ans;
    }

    if(level == ans.size())
    {
        ans.push_back(root->data);
    }

    solve(root->left, ans, level+1);
    solve(root->right, ans, level+1);

    return ans;
}

vector<int> solveright(Node * root, vector<int> & ans, int level)
{
    if(root==NULL)
    {
        return ans;
    }

    if(level==ans.size())
    {
        ans.push_back(root->data);
    }

    solve(root->right, ans,level+1);
    solve(root->left,ans,level+1);

    return ans;
}

void solveSum(Node * root,int len, int sum, int &maxSum, int &maxLen)
{
    if(root==NULL)
    {
        if(len > maxLen)
        {
            maxLen = len;
            maxSum = sum;
        }

        if(len == maxLen)
        {
            sum = max(sum,maxSum);
        }
    }

    sum = sum + root->data;

    solveSum(root->left,len+1,sum,maxSum,maxLen);
    solveSum(root->right,len+1,sum,maxSum,maxLen);

}

int sumOfRootToLeafNode (Node * root)
{
    int len = 0;
    int sum = 0;
    int maxSum = INT_MIN;
    int maxLen = 0;
    solveSum(root,len,sum,maxSum,maxLen);
    return maxSum;
}


Node * lca(Node *root, int n1, int n2)
{
    if(root==NULL)
    {
        return NULL;
    }

    if(root->data==n1 || root->data==n2)
    {
        return root;
    }

    Node * leftAns = lca(root->left,n1,n2);
    Node * rightAns = lca(root->right,n1,n2);

    if(leftAns==NULL && rightAns==NULL)
    {
        return NULL;
    }

    else if(leftAns!=NULL && rightAns==NULL)
    {
        return leftAns;
    }

    else if(leftAns==NULL && rightAns!=NULL)
    {
        return rightAns;
    }
    else
    {
        return;
    }
}

void solve1(Node * root, int &k, int &count, vector<int> &path)
{
    if(root==NULL)
    {
        return;
    }

    path.push_back(root->data);

    solve1(root->left,k,count,path);
    solve1(root->right, k, count, path);

    int size = path.size();
    int sum = 0;
    for(int i = size-1;i>=0;i--)
    {
        sum+= path[i];
        if(sum==k)
        {
            count++;
        }
    }
}

int kpaths(Node * root,int k)
{
    vector<int> path;
    int count = 0;
    solve1(root,k,count,path);
    return count;

}

Node * solve2(Node * root, int node, int k)
{
    if(root==NULL)
    {
        return NULL;
    }

    Node * leftAns = solve2(root->left, node , k);
    Node * rightAns = solve2(root->right, node, k);

    if(leftAns!=NULL && rightAns==NULL)
    {
        k--;
        if(k<=0)
        {
            k = INT_MAX;
            return root;
        }
        return  leftAns;
    }

    if(leftAns==NULL && rightAns!=NULL)
    {
        k--;
        if(k <= 0)
        {
            k = INT_MAX;
            return root;
        }
        return rightAns;
    }

    else
    {
        return NULL;
    }
}


int kthAncestor(Node * root, int node ,  int k)
{
    Node * ans = solve2(root, node, k);
    if(ans==NULL || ans->data== node)
    {
        return -1;
    }
    else
    {
        return ans->data;
    }

    return 0;
}


pair<int,int> maximumSum(Node * root)
{
    if(root==NULL)
    {
        return make_pair(0,0);
    }

    pair<int,int> leftAns = maximumSum(root->left);
    pair<int,int> rightAns = maximumSum(root->right);

    pair<int,int> res;

    res.first = root->data + leftAns.second + rightAns.second;
    res.second = max(leftAns.first,leftAns.second)+max(rightAns.first,rightAns.second);

    return res;
}

int sum(Node * root)
{
    pair<int,int> ans = maximumSum(root);
    return max(ans.first,ans.second);
}