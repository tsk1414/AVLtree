#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

struct node { 
    int key; 
    string value; 
    node *left; 
    node *right; 
    int height; 
}; 

//class AVLTreeMap 
class AVLTreeMap { 
    node *root; 
    
    private:
        int getHeight(node *curr) {
            if (curr == nullptr) {
                return -1;
            }
            return curr->height;
        }
        int getBalance(node *curr) { 
            int leftHeight = getHeight(curr->left);
            int rightHeight = getHeight(curr->right);

            // do arithmetic
            return leftHeight - rightHeight;
        }
        void updateHeight(node* n) {
            // get heights of each child
            // set our height = 1 + max of them
            n->height = 1 + max(getHeight(n->right), getHeight(n->left));
        }
        bool isBalanced(node* n) {
            int bf = getBalance(n);

            // if it's > 1 or < -1, return false
            if (bf > 1 || bf < -1) {
                return false;
            }
            // otherwise return true
            return true;
        }
        node *rotateLeft(node *b){
            // save values we care about
            node* a = b->right;
            node* s2 = a->left;

            // update some values
            a->left = b;
            b->right = s2;

            // update heights of nodes whose heights might have changed (a and b)
            updateHeight(b);
            updateHeight(a);

            // return new root
            return a;
        }
        node *rotateRight(node *a){
            // save values we care about
            node* b = a->left;
            node* s2 = b->right;

            // update some values
            b->right = a;
            a->left = s2;

            // update heights of nodes whose heights might have changed (a and b)
            updateHeight(a);
            updateHeight(b);

            // return new root
            return b;
        }
        
        node* rebalance(node* n) {
            // determine the balance factor of current node, as well as child nodes
            int bf = getBalance(n);
            // determine if it's left- unbalanced or right-unbalanced
            // if balance factor is positive...
            if (bf > 0) {
            // Left cases
            // if left-right
                if (getBalance(n->left) < 0) {
                  // rotate left n->left
                    n->left = rotateLeft(n->left);
                }
            // if left-left
              // rotate right n
                n = rotateRight(n);
            } else {
            // if right-left  
                if (getBalance(n->right) > 0) {
                    n->right = rotateRight(n->right);
                }
                // if right-right
                n = rotateLeft(n);
            }

            return n;
        }

        node* getSmallest(node*n){
            node* min = n;
            while (min->left != nullptr)
                
                getSmallest(min->left);
            return min;

        }
        node* removeHere(node* n){
            if (n->left != nullptr && n->right != nullptr){
                node* smallest = getSmallest(n->right);
                n->key = smallest->key;
                n->value = smallest->value;
                n->right = remove(n->right,smallest->key);
            }
            else if (n->left !=nullptr){
                n = n->left;
            }
            else{
                n = n->right;
            }
            
            return n;
        }
        
    
        node* insert(node* n, int key, string value);
        node* remove(node* n, int key);
        node* search(node* n, int key);
        void inOrder(node* n);
    
    
    public:
        AVLTreeMap(){
            root = nullptr;
        }
        node* get(int key){
            return search(root,key);
        }
        void put(int key, string value){
            root = insert(root,key,value);
        }
        void deletion (int key){
            root = remove(root, key);

        }
        void printLevelOrder()  {  
            queue<node*> levelOrder;
            levelOrder.push(root);
            while (!levelOrder.empty()){
                node* n = levelOrder.front();
                levelOrder.pop();
                if (n != nullptr){
                    cout << n->key << ":" << n->value << "(" << getBalance(n) << ") ";
                    levelOrder.push(n->left);
                    levelOrder.push(n->right);                    
                }
            }
            cout <<"\n";
        }  
        void inOrder() {
            inOrder(root);
        }
        
};

//functions
void AVLTreeMap::inOrder(node* n) {
    if (n != nullptr) {
      inOrder(n->left);
      std::cout << n->key << " ";
      inOrder(n->right);
    }
  }
node* AVLTreeMap::search(node* n, int key) {
  if (n == nullptr) {
    return nullptr;
  }

  if (key == n->key) {
    return n;
  }
  if (key < n->key) {
    return search(n->left, key);
  }
  return search(n->right, key);
}

node* AVLTreeMap::insert(node* n, int key, string value) {
    // If node == null, return a new data node.
    if (n == nullptr) {
        node* newNode = new node();
        newNode->key = key;
        newNode->value = value;
        newNode->height = 0;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    // Set (L|R) child = insert(value, node.(L|R))
    if (key < n->key) {
        n->left = insert(n->left, key, value);
    } 
    else {
        n->right = insert(n->right, key, value);
    }

    // If the current node is unbalanced, determine which case it is and perform the appropriate rotation(s).
    if (!isBalanced(n)) {
        n = rebalance(n);
    }

    // Update the height of the current node.
    updateHeight(n);

    // Return the node
    return n;
}

node* AVLTreeMap::remove(node* n, int key) {

    if (n == nullptr)
        return n;

    if (key == n->key){
       
        n=removeHere(n);
        return n;
    }
    else if (key < n->key){
        n->left=remove(n->left,key);
    }
    else{
        n->right=remove(n->right,key);
    }
    
    
    if (!isBalanced(n)) {
        n = rebalance(n);
     }
    updateHeight(n);
    
    return n;
}




int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));
    AVLTreeMap treemap;
    for (int n_itr = 0; n_itr < n; n_itr++) {
        
        string c_temp;
        cin >> c_temp;
        string command = (ltrim(rtrim(c_temp)));
        
        if (command == "put"){
            int key;
            string value;
            cin >> key;
            cin >> value;
            treemap.put(key,value);
        }
        else if (command == "get"){
            int key;
            cin >> key;
            node* node = treemap.get(key);
            if (node == nullptr){
                cout << "Not Found\n";
            }
            else
                cout << node->value << endl;
            ;
        }
        else if (command == "remove"){
            int key;
            cin >> key;
            treemap.deletion(key);
            ;
        }
        else if (command == "levelorder"){
            treemap.printLevelOrder();
            ;
        }
        
    }

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}