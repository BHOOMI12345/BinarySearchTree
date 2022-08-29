#include<bits/stdc++.h>
using namespace std;

class Node 
{
    public:

    int data;
    Node* right;
    Node * left;
    Node * next ;

    Node(int d)
    {
        this->data = d;
        this->right = NULL;
        this->left = NULL;
        this->next = NULL;

    }
};

class info{
    public:

    int maxi;
    int mini;
    bool isBst;
    int size;
};



//Q1 INSERTION IN BST
Node * insertIntoBST(Node * &root, int d)
{
    if(root==NULL)
    {
        root = new Node (d);
        return root;
    }

    if(d > root->data)
    {
        root->right = insertIntoBST(root->right, d);
    }
    else
    {
        root->left = insertIntoBST(root->left,d);
    }
    return root;
}

void takeInput(Node *& root)
{
    int data;
    cin>>data;
    

    while (data!=-1)
    {
        root = insertIntoBST(root, data);
        cin>>data;
    }
    
}

void levelOrderTraversal(Node * root)
{
    queue<Node * > q;
    q.push(root);

    while (!q.empty())
    {
        Node * temp = q.front();
        q.pop();

        if(temp==NULL)
        {
            cout<<endl;
            if(!q.empty())
            {
                q.push(NULL);
            }
        }

        else
        {
            cout<<temp->data<<" ";
            if(temp->left)
            {
                q.push(temp->left);
            }
            if(temp->right)
            {
                q.push(temp->right);
            }
        }
    }
    
}



//Q2 SEARCHING IN BST

bool searchInBstRecursive(Node * root,int value)
{
    if(root==NULL)
    {
        return false;
    }

    if(root->data ==value)
    {
        return true;
    }

    if(root->data < value)
    {
        return searchInBstRecursive(root->right,value);
    }
    else
    {
        return searchInBstRecursive(root->left, value);
    }
}

bool searchInBstIterative(Node * root, int val)
{
    Node * temp = root;
    while(temp!=NULL)
    {
        if(temp->data==val)
        {
            return true;
        }
        if(temp->left)
        {
            temp = temp->left;
        }

        if(temp->right)
        {
            temp = temp->right;
        }
    }
    return true;

}

Node* searchLeetcode(Node * root ,int val)
{
    while(root!=NULL && root->data!=val)
    {
        root = root->data > val ? root->left : root->right;
    }

    return root;
}



//Q3 MAXIMUM AND MINIMUM ELEMENT IN BST
int maximumElement(Node * root)
{
    Node * temp = root;
    while(temp->right!=NULL)
    {
        temp = temp->right;
    }
    return temp->data;
}

int minimumElement(Node * root)
{
    Node * temp = root;
    while(temp->left!=NULL)
    {
        temp = temp->left;
    }
    return temp->data;
}



//Q4 DELETION IN BST
Node * DeleteFromBst(Node * root, int x)
{
    if(root==NULL)
    {
        return root;
    }
    if(root->data == x)
    {
        //0 child
        if(root->left==NULL && root->right==NULL)
        {
            delete root;
            return NULL;
        }
 
        //1 child(left child)
        if(root->left!=NULL && root->right==NULL)
        {
            Node * temp = root->left;
            delete root;
            return temp;
        }

        //1 child (right child)
        if(root->left==NULL && root->right!=NULL)
        {
            Node * temp =  root->right;
            delete root;
            return temp;
        }

        // 2 child 
        else
        {
            int max = maximumElement(root->left);
            root->data = max;
            root->left = DeleteFromBst(root->left,max);
            return root;
        }
    }

    else if(root->data < x)
    {
        root->right = DeleteFromBst(root->right,x);
        return root;
    }

    else
    {
        root->left = DeleteFromBst(root->left,x);
        return root;
    }
    return root;
}

//Q5 VALIDATION OF BST

bool isBst(Node * root, int min, int max)
{
    if(root==NULL)
    {
        return true;
    }

    if(root->data > min && root->data < min)
    {
        bool left = isBst(root->left,min,root->data);
        bool right = isBst(root->right,root->data,max);
        return left && right;
    }
    else
    {
        return false;
    }
}

bool validateBst(Node* root)
{
    return isBst(root, INT_MIN, INT_MAX);

}


//Q6 KTH SMALLEST ELEMENT
int solve(Node* root,int k , int &i)
{
    if(root==NULL)
    {
        return -1;
    }

    //L
    int left = solve(root->left, k , i);

    if(left!=-1)
    {
        return left;
    }

    i++;
    //N
    if(i==k)
    {
        return root->data;
    }

    //R
    return solve(root->right,k,i);

}

int kthsmallest(Node* root,int k)
{
    int ans;
    int i = 0;
    ans = solve(root,k,i);
    return ans;
}


//Q7 PREDECESSOR and SUCCESSOR
pair<int,int> findPreSuc(Node * root, int k)
{
    int pre = -1;
    int suc = -1;
    Node * temp = root;
    while(temp->data!=k)
    {
        if(temp->data > k)
        {
            suc = temp->data;
            temp = temp->left;
        }
        else
        {
            pre = temp->data;
            temp = temp->right;
        }
    }

    Node * leftTree = temp->left;
    while (leftTree!=NULL)
    {
        pre = leftTree->data;
        leftTree = leftTree->right;
    }

    Node * rightTree = temp->right;
    while (rightTree!=NULL)
    {
        suc = rightTree->data;
        rightTree = rightTree->left; 
    }
    
    pair<int,int> ans = make_pair(pre,suc);
    return ans;
    
}

//Q8 LOWEST COMMON ANCESTOR IN BST
Node * findLca(Node * root, Node * P, Node * Q)
{
    if(root==NULL)
    {
        return NULL;
    }

    if(root->data < P->data && root->data < Q->data)
    {
        return findLca(root->right,P,Q);
    }
    else if(root->data > P->data && root->data > Q->data)
    {
        return findLca(root->left,P,Q);
    }
    else
    {
        return root;
    }
}

//Q9 2 SUM IN BST
void inorder(Node * root, vector<int> & inordervalue)
{
    if(root==NULL)
    {
        return;
    }

    inorder(root->left, inordervalue);
    inordervalue.push_back(root->data);
    inorder(root->right, inordervalue);
}
bool twoSum(Node * root, int target)
{
    vector<int> inordervalue;
    int n = inordervalue.size();
    int i = 0;
    int j = n-1;

    while(i<j)
    {
        int sum = inordervalue[i]+inordervalue[j];
        if(sum==target)
        {
            return true;
        }
        else if(sum > target)
        {
            j--;
        }
        else
        {
            i++;
        }

    }
    return false;
}


//Q10 FLATTEN THE BST IN LINKED LIST

void inorder(Node * root, vector<int> & inordervalue)
{
    if(root==NULL)
    {
        return;
    }

    inorder(root->left, inordervalue);
    inordervalue.push_back(root->data);
    inorder(root->right,inordervalue);
}

Node * flattenTheBst(Node * root)
{
    vector<int> in;
    inorder(root,in);

    int n =in.size();
    Node * newRoot = new Node(in[0]);
    Node * curr = newRoot;

    for(int i =1;i<n;i++)
    {
        Node * temp = new Node(in[i]);
        curr->left = NULL;
        curr->right = temp;
        curr = temp;
    }

    curr->left = NULL;
    curr->right = NULL;


    return newRoot;
}

//Q11 NORMAL BST TO BALANCED BST

void inorder(Node * root, vector<int> & in)
{
    if(root==NULL)
    {
        return;
    }
    inorder(root->left, in);
    in.push_back(root->data);
    inorder(root->right,in);
}

Node * inorderToBst(int s , int e,vector<int> & in)
{
    if(s>=e)
    {
        return NULL;
    }
    int mid = (s+e)/2;
    Node * root = new Node(in[mid]);

    root->left = inorderToBst(s,mid-1,in);
    root->right = inorderToBst(mid+1,e,in);

    return root;
}

Node * normalToBst(Node * root)
{
    vector <int> invector;
    inorder(root,invector);

    return inorderToBst(0,invector.size(),invector);
}


//Q12 PREORDER TRAVERSAL OG BINARY SEARCH TREE

Node * solve(vector<int> & in, int mini, int maxi, int &i)
{
    if(i>=in.size())
    {
        return NULL;
    }

    if(in[i]< mini || in[i] > maxi)
    {
        return NULL;
    }

    Node * root  = new Node (in[i]);
    root->left = solve(in, mini, root->data, i);
    root->right = solve(in, root->data,maxi,i);
    return root;
}

Node * Bst(vector<int> preorder)
{
    int i = 0;
    int mini = INT_MIN;
    int maxi = INT_MAX;
    return solve(preorder, mini, maxi, i);
}


//Q13 MERGE TWO SORTED BINARY SEARCH TREES
void inorderTraversal(Node * root, vector<int> in)
{
    if(root==NULL)
    {
        return;
    }

    inorderTraversal(root->left,in);
    in.push_back(root->data);
    inorderTraversal(root->right,in);
}

vector<int> mergeTwoVectors(vector<int> a,vector<int> b)
{
    vector<int> ans(a.size() + b.size());
    int i = 0, j = 0,k=0;

    while (i< a.size() && j < b.size())
    {
        if(a[i] < b[j])
        {
            ans[k++] = a[i];
            i++;
        }
        else
        {
            ans[k++] = b[j];
            j++;
        }
    }

    while(i< a.size())
    {
        ans[k++] = a[i];
        i++;
    }

    while(j<b.size())
    {
        ans[k++] = b[j];
        j++;
    }
    
    return ans;

}

Node * inorderToBst2(vector<int>& in, int s , int e,int i)
{
    if(s>e)
    {
        return NULL;
    }

    int mid = (s+e)/2;
    Node * newRoot = new Node (in[mid]);
    newRoot->left = inorderToBst2(in,s,mid-1,i);
    newRoot->right = inorderToBst2(in, mid+1,e,i);
    return newRoot;

}

Node * mergeSortedTrees(Node * root1, Node * root2)
{
    vector<int> bst1, bst2;
    inorderTraversal(root1, bst1);
    inorderTraversal(root2,bst2);

    vector<int> mergeVector = mergeTwoVectors(bst1,bst2);
    Node * root = inorderToBst2(mergeVector,0,mergeVector.size()-1,0);
}

//Q14 MERGE TWO SORTED BINARY SEARCH TREES USING LINKED LIST

//1. convert bst into sorted linked list

void convertIntoSortedLinkedList(Node * root, Node * &head)
{
    if(root==NULL)
    {
        return;
    }
    convertIntoSortedLinkedList(root->right, head);

    root->right = head;
    if(head!=NULL)
    {
        head->left = root;
    }
    head = root;
    convertIntoSortedLinkedList(root->left,head);

}

//2. merge two sorted linked list;

Node * mergeLL(Node * head1, Node * head2)
{
    Node *head  = NULL;
    Node * tail = NULL;

    while(head1!=NULL && head2!=NULL)
    {
        if(head1->data < head2->data)
        {
            if(head==NULL)
            {
                head = head1;
                tail = head1;
                head1 = head1->right;
            }

            else
            {
                tail->right = head1;
                head1->left = tail;
                tail = head1;
                head1 = head1->right;
            }
        }
        else
        {
            if(head==NULL)
            {
                head = head2;
                tail = head2;
                head2 = head2->right;
            }

            else
            {
                tail = tail->right;
                head2->left = tail;
                tail = head2;
                head2 = head2->right;
            }
        }
    }

    while(head1!=NULL)
    {
        tail->right = head1;
        head1->left = tail;
        tail = head1;
        head1 = head1->right;
    }

    while(head2!=NULL)
    {
        tail->right = head2;
        head2->left = tail;
        tail = head2;
        head2 = head2->right;
    }

    return head;
}

int countNodes(Node * head)
{
    int cnt = 0;
    Node * temp = head;
    while (temp!=NULL)
    {
        cnt++;
        temp = temp->right;
    }
    return cnt;
}

//3. conversion of linked list into binary search trees

Node * convertSortedLinkedListIntoBst(Node * head, int n)
{
    if(n< 0 || head==NULL)
    {
        return NULL;
    }

    Node * left = convertSortedLinkedListIntoBst(head, n/2);
    Node * root = head;
    root->left = left;
    head = head->next;
    root->right = convertSortedLinkedListIntoBst(head, n-n/2-1);
    return root;
}

Node * mergeSortedTreesLL(Node * root1, Node * root2)
{
    Node * head1 = NULL;
    Node *head2 = NULL;
    convertIntoSortedLinkedList(root1, head1);
    convertIntoSortedLinkedList(root2, head2);

    Node * head = mergeLL(head1, head2);

    int n = countNodes(head);
    Node * root = convertSortedLinkedListIntoBst(head,n);
    return root;

}


//Q15 LARGEST BINARY SEARCH TREE 

info solve(Node * root, int& ans)
{
    if(root==NULL)
    {
        return {INT_MIN, INT_MAX, true, 0};
    }
    info left = solve(root->left,ans);
    info right = solve(root->right, ans);

    info currNode ;
    currNode.size = left.size + right.size + 1;
    currNode.maxi = max(root->data,right.maxi);
    currNode.mini = max(root->data,left.mini);

    if(left.isBst && right.isBst && (root->data > left.maxi && root->data < right.mini))
    {
        currNode.isBst = true;
    }
    else
    {
        currNode.isBst = false;
    }
    

    if(currNode.isBst)
    {
        ans = max(ans,currNode.size);
    }
    return currNode;
}


int largestBst(Node * root)
{
    int maxsize = 0;
    info temp = solve(root,maxsize);
    return maxsize;
}



int main()
{
    Node* root = NULL;
    cout<<"Enter the data to create the BST"<<endl;
    takeInput(root);

    levelOrderTraversal(root);
    return 0;
}
