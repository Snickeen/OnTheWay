/**
 * Author: Snickeen.
 * Email: ff@snickeen.com
 * Time: 2018_05_03_4
 * If you find out some bugs, please tell me. Thanks.
**/

#include<stdio.h>


///*************************************************************************************///
///down*         Introduction about Functions of AVL_Tree                          *down///
///*************************************************************************************///

/*

inline AVLINT __height(AVLNode *root);     //the height of the tree
inline AVLINT BF(AVLNode *root);           //balanceFactor = height(left subtree) - height(right subtree)
inline void __update_height(AVLNode *root);//update the height of the tree
inline AVLINT __size(AVLNode *root);       //size: the number of nodes of subtree
inline void __update_size(AVLNode *root);  //update the size of subtree
inline void __update_info(AVLNode *root);  //update height and size, maybe more

//four rotations of AVL_Tree
inline AVLNode* __rr_Rotation(AVLNode *root);      //right-right rotation
inline AVLNode* __ll_Rotation(AVLNode *root);      //left-left rotation
inline AVLNode* __lr_Rotation(AVLNode *root);      //left-right rotation
inline AVLNode* __rl_Rotation(AVLNode *root);      //right-left rotation

inline AVLNode* Balance(AVLNode *root);            //balance the tree
inline AVLNode* Insert(AVLNode *root,AVLINT k);    //insert a node

inline AVLNode* __search(AVLNode *root,AVLINT &k); //if value k in the tree, return its node
inline bool Search(AVLNode *root,AVLINT &k);       //is value k here? yes or no

inline AVLNode* __treeMinNode(AVLNode *root);      //get the node of minimum value: go left, again and again
inline AVLNode* __treeMaxNode(AVLNode *root);      //get the node of maximum value: go right, again and again

inline AVLNode* __Delete(AVLNode *root,AVLINT k);  //delete the node of value k
inline bool Delete(AVLNode *root,AVLINT &k);       //can we delete node successfully?
inline void __deleteTree(AVLNode *root);           //delete the whole AVL_Tree

inline AVLNode* findk(AVLNode *root,AVLINT k);     //find Kth minimum

inline void InorderTraversal_print(AVLNode *root); //inorder traversal ver_1: print val,height,balanceFactor
inline void PreorderTraversal(AVLNode *root);      //preorder traversal
inline void PostorderTraversal(AVLNode *root);     //postorder traversal
...

*/

///*************************************************************************************///
///down*                     AVL_Tree code template                                *down///
///*************************************************************************************///

///Note1: All the values in the tree will be distinct.
///Note2: Height of a Null node is -1 and the height of the leaf node is 0.

//if you want update this code, don't forget check these:
//    struct node
//    __update_info()
//    Insert():new node
//    __Delete(): copy max_or_min to root

///AVL_Tree Node
typedef int AVLINT;
struct node{
    AVLINT val, x;
    node *left;
    node *right;
    AVLINT ht; //height
    AVLINT sz;//size: the number of nodes in current subtree
};
const AVLINT HeightOfTheLeafNode = 0;
typedef node AVLNode;

AVLINT t;

///AVL_Tree function


AVLNode *avlroot = NULL;

//the height of the tree
inline AVLINT __height(AVLNode *root){
    if(NULL==root)return HeightOfTheLeafNode-1;
    return root->ht;
}
//balanceFactor = height(left subtree) - height(right subtree)
inline AVLINT BF(AVLNode *root){
    if(NULL==root)return 0;
    return __height(root->left) - __height(root->right);
}

//update the height of the tree
inline void __update_height(AVLNode *root){
    if(NULL==root)return ;
    AVLINT l = __height(root->left), r = __height(root->right);
    root->ht = (l>r?l:r)+1;
}

//size: the number of nodes of subtree
inline AVLINT __size(AVLNode *root){
    if(NULL==root)return 0;
    return root->sz;
}
//update the size of subtree
inline void __update_size(AVLNode *root){
    if(NULL==root)return ;
    AVLINT l=__size(root->left), r=__size(root->right);
    root->sz=l+r+1;
}

//update height and size, maybe more
inline void __update_info(AVLNode *root){
    if(NULL==root)return ;
    __update_height(root);
    __update_size(root);
}

//four rotations of AVL_Tree
inline AVLNode* __rr_Rotation(AVLNode *root){//right-right rotation
    AVLNode* tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    __update_info(root);
    __update_info(tmp);
    return tmp;
}
inline AVLNode* __ll_Rotation(AVLNode *root){//left-left rotation
    AVLNode* tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    __update_info(root);
    __update_info(tmp);
    return tmp;
}
inline AVLNode* __lr_Rotation(AVLNode *root){//left-right rotation
    root->left = __rr_Rotation(root->left);
    return __ll_Rotation(root);
}
inline AVLNode* __rl_Rotation(AVLNode *root){//right-left rotation
    root->right = __ll_Rotation(root->right);
    return __rr_Rotation(root);
}

//balance the tree
inline AVLNode* Balance(AVLNode *root){
    AVLINT balanceFactor = BF(root);//balanceFactor
    if(balanceFactor > 1){//about root: height(left subtree) > height(right subtree)
        //about left subtree: height(left subtree) > height(right subtree)
        if(BF(root->left) > 0) root=__ll_Rotation(root);
        //about left subtree: height(left subtree) < height(right subtree)
        else root=__lr_Rotation(root);
    }
    else if(balanceFactor < -1){//about root: height(left subtree) < height(right subtree)
        //about right subtree: height(left subtree) > height(right subtree)
        if(BF(root->right) > 0) root=__rl_Rotation(root);
        //about right subtree: height(left subtree) < height(right subtree)
        else root=__rr_Rotation(root);
    }
    return root;
}

//insert a node
inline AVLNode* Insert(AVLNode *root,AVLINT k){
    if(NULL == root){
        root = new AVLNode(); //
        root->val = k; root->x = t;
        root->left = root->right = NULL;
        root->ht = HeightOfTheLeafNode; //
        root->sz = 1;
        return root;
    }//recursion exit
    else if(k < root->val){
        root->left = Insert(root->left,k);//recursion about left subtree
    }
    else if(k > root->val){
        root->right = Insert(root->right,k);//recursion about right subtree
    }
    else if(k == root->val){
        return NULL;
    }
    __update_info(root);
    root = Balance(root);//balance operation
    return root;
}

//if value k in the tree, return its node
inline AVLNode* __search(AVLNode *root,AVLINT &k){
    if(NULL == root || k == root->val) return root;
    else if(k > root->val) return __search(root->right,k);
    else return __search(root->left,k);
}
//is value k here? yes or no
inline bool Search(AVLNode *root,AVLINT &k){
    return NULL!=__search(root,k);
}

//get the node of minimum value: go left, again and again
inline AVLNode* __treeMinNode(AVLNode *root){
    if(NULL == root || NULL == root->left)return root;
    if(NULL != root->left)return __treeMinNode(root->left);
}
//get the node of maximum value: go right, again and again
inline AVLNode* __treeMaxNode(AVLNode *root){
    if(NULL == root || NULL == root->right)return root;
    if(NULL != root->right)return __treeMaxNode(root->right);
}

//delete the node of value k
inline AVLNode* __Delete(AVLNode *root,AVLINT k){
    if(root == NULL)return root;
    if(k == root->val){
        if((NULL!=root->left)&&(NULL!=root->right)){//two children
            if(BF(root) > 0){//height(left subtree) > height(right subtree), delete node of left subtree
                AVLNode *tmp = __treeMaxNode(root->left);//value replaced by maximum of left subtree
                root->val = tmp->val;
                root->x = tmp->x;
                root->left = __Delete(root->left, root->val);//delete maximum node of left subtree
            }
            else{//height(left subtree) < height(right subtree), delete node of right subtree
                AVLNode *tmp = __treeMinNode(root->right);//value replaced by minimum of right subtree
                root->val = tmp->val;
                root->x = tmp->x;
                root->right = __Delete(root->right, root->val);//delete minimum node of right subtree
            }
        }
        else{//one child or no child
            AVLNode *tmp = root;
            root = (root->left) ? (root->left) :( root->right);
            delete tmp;
            tmp = NULL;
        }
    }//end-if
    else if(k < root->val){//delete k in left subtree
        root->left = __Delete(root->left,k);//Recursion
        //check and balance tree
        if (BF(root) < -1){//after deleted node of left subtree, height(left subtree) < height(right subtree)
            if(BF(root->right) > 0) root=__rl_Rotation(root);
            else root=__rr_Rotation(root);
        }
    }//end else if
    else{//delete k in right subtree
        root->right = __Delete(root->right,k);
        if(BF(root) > 1){////after deleted node of left subtree, height(left subtree) > height(right subtree)
            if(BF(root->left) < 0) root=__lr_Rotation(root);
            else root=__ll_Rotation(root);
        }
    }//end else
    __update_info(root);
    return root;
}
//can we delete node successfully?
inline bool Delete(AVLNode *root,AVLINT &k){
    if(NULL==root || !Search(root,k))return false;
    return NULL!=__Delete(root,k);
}

//delete the whole AVL_Tree
inline void __deleteTree(AVLNode *root){
    if(NULL == root)return ;
    __deleteTree(root->left);
    __deleteTree(root->right);
    delete root;
    root = NULL;
    return ;
}

//find Kth minimum
inline AVLNode* findk(AVLNode *root,AVLINT k){
    if(NULL==root)return root;
    if(k == __size(root->left)+1)return root;
    else if(k <= __size(root->left)) return findk(root->left,k);
    else return findk(root->right, k - (root->sz - __size(root->right)));
}


//inorder traversal ver_1: print val,height,balanceFactor
inline void InorderTraversal_print(AVLNode *root){
    if(NULL==root)return ;
    InorderTraversal_print(root->left);
    printf("%d %d %d\n",root->val,root->ht,BF(root));
    InorderTraversal_print(root->right);
}
//preorder traversal
inline void PreorderTraversal(AVLNode *root){
    if(NULL==root)return ;
    printf("%d %d %d\n",root->val,root->ht,BF(root));
    PreorderTraversal(root->left);
    PreorderTraversal(root->right);
}
//postorder traversal
inline void PostorderTraversal(AVLNode *root){
    if(NULL==root)return ;
    PostorderTraversal(root->left);
    PostorderTraversal(root->right);
    printf("%d %d %d\n",root->val,root->ht,BF(root));
}

///*************************************************************************************///
///up*                       AVL_Tree code template                                  *up///
///*************************************************************************************///







// POJ3481 AC Time: 547MS  Memery: 0.6MB
// HDU1908 AC Time: 187MS  Memery: 1.6MB
// HDU1908 AC Time: 124ms  Memery: 1616kB //delete some function
// HDU1908 AC Time: 187ms  Memery: 1620kB //update size
inline void POJ3481_HDU1908(){
    AVLNode *root=NULL, *tmp;
    int op,x,y;
    while(~scanf("%d",&op), op){
        if(op==1){
            scanf("%d%d",&t,&y); //t
            root=Insert(root,y);
        }
        if(op==2){
            tmp=__treeMaxNode(root);
            if(tmp!=NULL){
                printf("%d\n",tmp->x);
                root=__Delete(root,tmp->val);
            }
            else puts("0");
        }
        if(op==3){
            tmp=__treeMinNode(root);
            if(tmp!=NULL){
                printf("%d\n",tmp->x);
                root=__Delete(root,tmp->val);
            }
            else puts("0");
        }
    }
    return ;
}




//hdu 2193 AVL_Tree height
//max height of AVL_Tree with n nodes
inline void HDU2193(){
    int a[46],_n;
    a[0]=1;a[1]=2;
    for(int i=2;i<=45;i++)
        a[i]=a[i-1]+a[i-2]+1;
    while (~scanf("%d",&_n),_n){
        int ans=0;
        while (a[ans]<=_n) ans++;
        printf("%d\n",--ans);
    }
    return ;
}



///HIT1819 can't be connect, submit it later
//http://acm.hit.edu.cn/judge/show.php?Proid=1819&Contestid=0
//https://vjudge.net/problem/HIT-1819
inline void HIT1819(){
    int n,minn, k, ans, delta;//ans //delta: add or sub
    char op[6];
    while(~scanf("%d%d",&n,&minn)){
        AVLNode *root=NULL, *tmp;
        delta=ans=0;//many tests, init
        while(n--){
            scanf("%s%d",&op,&k);
            if(op[0]=='I'){
                if(k<minn)continue;
                root=Insert(root,k-delta);
            }
            else if(op[0]=='A'){
                delta+=k;
            }
            else if(op[0]=='S'){
                delta-=k;
                while(NULL!=root){
                    tmp=findk(root,1);
                    if(tmp->val + delta >= minn) break;
                    else {
                        ans++;
                        root=__Delete(root,tmp->val);
                    }
                }
            }
            else if(op[0]=='F'){
                if(NULL==root || k<=0 || root->sz < k)puts("-1");
                else {
                    tmp=findk(root,root->sz - k + 1);
                    printf("%d\n",tmp->val + delta);
                }
            }
        }
        printf("%d\n",ans);
        __deleteTree(root);
    }
}

signed main()
{
//    HDU2193();
    POJ3481_HDU1908();
//    CodeVS1285(); //code it later
//    HIT1819();//submit it later
    return 0;
}
