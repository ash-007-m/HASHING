#include <bits/stdc++.h>
#define ctime std::chrono::steady_clock::now();
#define ptime(diff) std::cout << std::chrono::duration<double, std::micro>(diff).count() << "micros" << std::endl
class map_Node
{
public:
    std::list<std::pair<int,int>> data;
};
class unordered_Map
{
    map_Node **bucket;
    int big_size = 100000;

public:
    unordered_Map()
    {
        bucket = new map_Node *[big_size];
        for (int i = 0; i < big_size; i++)
        {
            bucket[i] = new map_Node();
        }
    }
    int get_index(int key)
    {
        return key % big_size;
    }
    void insert(std::pair<int, int> temp)
    {
        int key = temp.pair::first;
        int data = temp.pair::second;
        int index=get_index(key);
        auto f=bucket[index]->data.list::begin();
        bool add=0;
        while (f !=bucket[index]->data.list::end())
        {
          if((*f).pair::first == key)
          {
          (*f).pair::second=data;
          add=1;
          break;
          }
          f++;
        }
       if(add==0)
        {
            bucket[index]->data.list::push_back(std::make_pair(key,data));
        }
        
    }
    void remove(int key)
    {
        int index=get_index(key);
       auto f=bucket[index]->data.list::begin();
       while (f !=bucket[index]->data.list::end())
       {
        if((*f).first==key)
        {
            bucket[index]->data.list::erase(f);
        }
        f++;
       }
    }
    int find(int key)
    {
        
        int index=get_index(key);
        auto f=bucket[index]->data.list::begin();
        bool add=0;
        while (f !=bucket[index]->data.list::end())
        {
          if((*f).pair::first == key)
          {
           return (*f).pair::second;
       
          }
          f++;
        }
        bucket[index]->data.list::push_back(std::make_pair(key,0));
        return 0;
    }
};

int main()
{
   
   unordered_Map hash;
   std::unordered_map<int,int> shash;
   std::vector<int> data(100000000);
    auto t1=ctime;
   for (int i = 0; i < 10000; i++)
   {
    int t=rand();
   //std::cout<<t<<" "<<hash.get_index(t)<<std::endl;
   // shash.insert(std::make_pair(t,t+1000));
   data[i]=t;
    hash.insert(std::make_pair(t,t+1000));
   //  if(i>5 and i<10)hash.remove(t);

   }
    auto t2 = ctime;
    std::cout << " average time for insertion";
    ptime(t2 - t1);
  
   for (int i = 0; i < 10000000; i++)
   {
   int t=data[i];
   hash.find(t);
   }
   
   


//    for(auto l: shash)
//    {int t=hash.find(l.first);
//     std::cout<<l.first<<" "<<l.second<<" "<<t;
//     if(l.second !=t)std::cout<<" error ";
//     std::cout<<std::endl;
//    }
   
    return 0;
}