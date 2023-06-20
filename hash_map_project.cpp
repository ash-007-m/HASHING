#include <bits/stdc++.h>
#define ctime std::chrono::steady_clock::now();
#define ptime(diff) std::cout << std::chrono::duration<double, std::micro>(diff).count() << "micros" << std::endl
class node
{
public:
    int data_at;
    int key;
    node *left;
    node *right;
    node *parent;
};

class unordered_map
{
private:
    node **bucket;
    int max_size = 100000;
    int get_index(int key)
    {
        return key % (max_size - 1);
    }
    void rotate(node *&A, int o, int t, node *&root)
    {

        if (o == 0 and t == 0) // left left rotation
        {
            auto gp = A->parent;
            auto B = A->left;
            if (gp)
            {
                if (gp->key > A->key)
                    gp->left = B;
                else
                {
                    gp->right = B;
                }
                A->left = B->right;
                if (A->left)
                {
                    A->left->parent = A;
                }
                B->right = A;
                A->parent = B;
                B->parent = gp;
                return;
            } // mean A is root
            root = B;
            B->parent = NULL;
            A->left = B->right;
            if (A->left)
            {
                A->left->parent = A;
            }
            B->right = A;
            A->parent = B;
            return;
        }
        if (o == 1 and t == 1) // right right case
        {
            auto gp = A->parent;
            auto B = A->right;
            A->parent = B;
            if (gp)
            {
                B->parent = gp;
                if (gp->key > A->key)
                    gp->left = B;
                else
                    gp->right = B;

                A->right = B->left;
                if (B->left)
                    B->left->parent = A;
                B->left = A;
                return;
            }
            root = B;
            B->parent = NULL;
            A->right = B->left;
            if (B->left)
                B->left->parent = A;
            B->left = A;
        }
        if (o == 0 and t == 1) //  left right rotation
        {
            auto gp = A->parent;
            auto B = A->left;
            auto C = B->right;
            B->right = C->left;
            if (C->left)
                C->left->parent = B;
            C->left = B;
            A->left = C->right;
            if (C->right)
                C->right->parent = A;
            C->right = A;
            A->parent = C;
            B->parent = C;
            if (gp)
            {
                C->parent = gp;
                if (gp->key > A->key)
                    gp->left = C;
                else
                    gp->right = C;
                return;
            }
            root = C;
            C->parent = NULL;
            return;
        }
        if (o == 1 and t == 0) // right left rotation case
        {
            auto gp = A->parent;
            auto B = A->right;
            auto C = B->left;
            A->parent = C;
            A->right = C->left;
            if (C->left)
                C->left->parent = A;
            C->left = A;
            B->left = C->right;
            if (C->right)
                C->right->parent = B;
            C->right = B;
            B->parent = C;
            if (gp)
            {
                C->parent = gp;
                if (gp->key > C->key)
                    gp->left = C;
                else
                    gp->right = C;
                return;
            }
            root = C;
            C->parent = NULL;
        }
    }
    int height(node *pointer)
    {
        if (pointer == NULL)
            return 0;
        if (pointer->left == NULL and pointer->right == NULL)
            return 1;
        if (pointer->left == NULL)
            return 1 + height(pointer->right);
        if (pointer->right == NULL)
            return 1 + height(pointer->left);

        return 1 + std::max(height(pointer->left), height(pointer->right));
    }
    void insert_avl(int data, node *&root, int key)
    {
        if (root == NULL)
        {
            root = new node();
            root->key = key;
            root->data_at = data;
            return;
        }
        if (root->key == key)
        {
            root->data_at = data;
            return;
        }
        auto temp = root;
        auto pa = root->parent;
        while (1)
        {
            if (temp->key == key)
            {

                temp->data_at = data;
                break;
            }
            if (temp->key > key)
            {
                if (temp->left == NULL)
                {
                    temp->left = new node();
                    temp->left->key = key;
                    temp->left->data_at = data;
                    temp->left->parent = temp;
                    temp = temp->left;
                    break;
                }
                temp = temp->left;
            }
            else
            {
                if (temp->right == NULL)
                {
                    temp->right = new node();
                    temp->right->key = key;
                    temp->right->data_at = data;
                    temp->right->parent = temp;
                    temp = temp->right;
                    break;
                }
                temp = temp->right;
            }
        }
        int o = -1;
        int t = -1;
        bool is = 0;
        while (temp)
        {
            int diff = abs(height(temp->left) - height(temp->right));
            if (diff > 1)
            {
                is = 1;
                break;
            }
            if (temp == root)
                break;
            t = o;
            if (temp->parent->key > temp->key)
            {
                o = 0;
            }
            else
                o = 1;
            temp = temp->parent;
        }
        if (not is)
            return;
        if (o not_eq -1 and t not_eq -1 and is)
        {
            rotate(temp, o, t, root);
        }
    }
    void BFS(node *&root)
    {
        std::queue<node *> data;
        data.queue::push(root);
        while (not data.empty())
        {
            auto l = data.front();
            data.pop();
            std::cout << l->key << "  ";

            if (l->left not_eq NULL)
            {
                data.push(l->left);
                std::cout << " left" << l->left->key << " ";
            }
            if (l->right not_eq NULL)
            {
                data.push(l->right);
                std::cout << "right" << l->right->key << " ";
            }
            std::cout << std::endl;
        }
    }
    node *remove_helper(int data, node *&root)
    {
        if (root->key == data)
        {
            auto temp = root;
            if (root->left == NULL)
            {
                root = root->right;
                root->parent = NULL;
                return NULL;
            }
            if (root->right == NULL)
            {
                root = root->left;
                root->parent = NULL;
                return NULL;
            }
            temp = root->left;
            if (temp->right == NULL)
            {
                temp->right = root->right;
                root->right->parent = temp;

                root = temp;
                root->parent = NULL;
                return NULL;
            }
            while (temp->right->right not_eq NULL)
            {
                temp = temp->right;
            }
            root->key = temp->right->key;
            temp->right = temp->right->left;
            if (temp->right)
                temp->right->parent = temp;
            return NULL;
        }
        else
        {
            // given node is not root
            auto temp = root;
            auto pa = root;
            while (1)
            {
                if (temp == NULL)
                    return NULL;
                if (temp->key > data)
                {
                    pa = temp;
                    temp = temp->left;
                    continue;
                }
                if (temp->key < data)
                {
                    pa = temp;
                    temp = temp->right;
                    continue;
                }
                if (pa->key > temp->key) // temp is left child of its parent
                {
                    if (temp->right == NULL)
                    {
                        pa->left = temp->left;
                        if (temp->left)
                            temp->left->parent = pa;
                        return pa;
                    }
                    if (temp->left == NULL)
                    {
                        pa->left = temp->right;
                        temp->right->parent = pa;
                        return pa;
                    }
                    auto temp2 = temp->left;
                    if (temp2->right == NULL)
                    {
                        pa->left = temp2;
                        temp2->parent = pa;
                        temp2->right = temp->right;
                        if (temp2->right)
                            temp2->right->parent = temp2;
                        return pa;
                    }
                    while (temp2->right->right not_eq NULL)
                    {
                        temp2 = temp2->right;
                    }
                    temp->key = temp2->right->key;
                    temp2->right = temp2->right->left;
                    if (temp2->right)
                        temp2->right->parent = temp2;
                    return pa;
                }
                if (temp->right == NULL)
                {
                    pa->right = temp->left;
                    if (pa->right)
                        pa->right->parent = pa;
                    return pa;
                }
                if (temp->left == NULL)
                {
                    pa->right = temp->right;
                    if (temp->right)
                        temp->right->parent = pa;
                    return pa;
                }
                auto temp2 = temp->left;
                if (temp2->right == NULL)
                {
                    pa->right = temp2;
                    temp2->parent = pa;
                    temp2->right = temp->right;
                    if (temp2->right)
                        temp2->right->parent = temp2;
                    return pa;
                }
                while (temp2->right->right not_eq NULL)
                {
                    temp2 = temp2->right;
                }
                temp->key = temp2->right->key;
                temp2->right = temp2->right->left;
                if (temp2->right)
                    temp2->right->parent = pa;
                return pa;
            }
        }
    }
    int height_helper(node *temp, int &t)
    {
        if (not temp)
            return 0;
        int left = height(temp->left);
        int right = height(temp->right);
        if (left > right)
            t = 0;
        else
            t = 1;
        return 1 + std::max(left, right);
    }
    void remove(int data, node *&root)
    {
        auto temp = remove_helper(data, root);
        int o = -1;
        int t = -1;
        while (temp)
        {
            int t1 = -1;
            int t2 = -1;
            int left = height_helper(temp->left, t1);
            int right = height_helper(temp->right, t2);
            if (left > right)
            {
                o = 0;
                t = t1;
                if (left - right > 1)
                {
                    if (t1 == 0) // we are goning to do left left rotation
                    {
                        auto dummy = temp->left;
                        rotate(temp, o, t, root);
                        temp = dummy;
                        continue;
                    }
                    else
                    // its a left right rotation
                    {
                        auto dummy = temp->left->right;
                        rotate(temp, o, t, root);
                        temp = dummy;
                        continue;
                    }
                }
            }
            else
            {
                if (right > left)
                {
                    o = 1;
                    t = t2;
                    if (right - left > 1)
                    {
                        if (t == 0) // its a right left rotation
                        {
                            auto dummy = temp->right->left;
                            rotate(temp, o, t, root);
                            temp = dummy;
                            continue;
                        }
                        else
                        { // its an left right rotation
                            auto dummy = temp->right;
                            rotate(temp, o, t, root);
                            temp = dummy;
                            continue;
                        }
                    }
                }
            }
            if (temp)
                temp = temp->parent;
        }
    }
    int find_avl(int key, node *&root)
    {
        if (root == NULL)
        {
            root = new node();
            root->key = key;
            root->data_at = 0;
            return 0;
        }
        if (root->key == key)
        {
            return root->data_at;
        }
        auto temp = root;
        auto pa = root->parent;
        while (1)
        {
            if (temp->key == key)
            {
                return temp->data_at;
            }
            if (temp->key > key)
            {
                if (temp->left == NULL)
                {
                    temp->left = new node();
                    temp->left->key = key;
                    temp->left->data_at = 0;
                    temp->left->parent = temp;
                    temp = temp->left;
                    return 0;
                }
                temp = temp->left;
            }
            else
            {
                if (temp->right == NULL)
                {
                    temp->right = new node();
                    temp->right->key = key;
                    temp->right->data_at = 0;
                    temp->right->parent = temp;
                    temp = temp->right;
                    return 0;
                }
                temp = temp->right;
            }
        }
        return 0;
    }
    bool is_there(int key, node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        if (root->key == key)
        {
            return 1;
        }
        auto temp = root;
        auto pa = root->parent;
        while (1)
        {
            if (temp->key == key)
            {
                return 1;
            }
            if (temp->key > key)
            {
                if (temp->left == NULL)
                {
                    return 0;
                }
                temp = temp->left;
            }
            else
            {
                if (temp->right == NULL)
                {
                    return 0;
                }
                temp = temp->right;
            }
        }
        return 0;
    }

public:
    void insert(std::pair<int, int> temp)
    {
        int key = temp.pair::first;
        int data = temp.pair::second;
        int index = unordered_map::get_index(key);
        node *root = bucket[index];
        insert_avl(data, root, key);
    }
    void delete_(int key)
    {
        int index = get_index(key);
        node *root = unordered_map::bucket[index];
        unordered_map::remove(key, root);
    }
    bool count(int key)
    {
        int index = get_index(key);
        node *root = unordered_map::bucket[index];
        return is_there(key, root);
    }
    unordered_map()
    {
        bucket = new node *[max_size];
        for (int i = 0; i < max_size; i++)
        {
            bucket[i] = new node();
        }
    }
    int find(int key)
    {
        int index = get_index(key);
        node *root = bucket[index];
        return find_avl(key, root);
    }
};

int main()
{
    unordered_map hash;
    std::unordered_map<int, int> shash;
    std::vector<int> data(100000000);
  auto t1 = ctime;  
    for (int i = 0; i < 10000; i++)
    {
        int t = std::rand();
        //   std::cout<<t<<std::endl;
        //  data.vector::push_back(t);
        hash.insert(std::make_pair(t, t + 1000));
        data[i] = t;
    }
   auto t2 = ctime;
    std::cout << " average time for insertion";
    ptime(t2 - t1);

    for (int i = 0; i < 10000000; i++)
    {
        int t = data[i];
        hash.find(t);
    }
 
    // for(auto l: shash)
    // {int f=l.second;

    //  if(l.first>500 and l.first<1000)
    //     hash.delete_(l.first);
    //   int two=hash.find(l.first);
    //     std::cout<<l.first<<" "<<l.second<<"    "<<two<<" ";
    //     if(f != two) std::cout<<" error";

    //    std:: cout<<std::endl;
    // }

    // hash.insert(std::make_pair(50,45));

    // std::cout<<hash.find(50);

    return 0;
}