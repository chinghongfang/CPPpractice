#include"tree.h"
#include"red_black.h"
#include<set>
#include<unordered_set>
#include<iostream>
#include<vector>
#include<queue>
#include"avl_tree.h"
using namespace std;
int main(){
    int in;
    vector<int> arr;
    vector<int> remove;
    vector<int> query;
    int std_ans = 0;
    int uno_ans = 0;
    int tree_ans = 0;
    int avl_ans = 0;
    int arr_ans = 0;
    set<int> ordered_set;
    unordered_set<int> unordered;
    rb<int>* root = new rb<int>;
    avl<int>* avlt = new avl<int>; 
    vector<int> arr_diff;
    while(cin>>in){
        if (in == 0){
            cin>>in;
            arr.push_back(in);
        }else if (in == 1){
            cin>>in;
            remove.push_back(in);
        }else if (in == 2){
            cin>>in;
            query.push_back(in);
        }
    }


    clock_t start, end;



    // insert numbers. Numbers are not all different.
    start = clock();
    for (int i = 0; i<arr.size(); ++i) ordered_set.insert(arr[i]);
    end = clock();
    cout<<"std::set           insertion time: "
        <<((double)(end-start)/CLOCKS_PER_SEC)
        <<endl;

    start = clock();
    for (int i = 0; i<arr.size(); ++i) unordered.insert(arr[i]);   
    end = clock();
    cout<<"std::unordered_set insertion time: "
        <<((double)(end-start)/CLOCKS_PER_SEC)
        <<endl;

    start = clock();
    for (int i = 0; i<arr.size(); ++i) root->insert(arr[i]);
    end = clock();
    cout<<"red-black          insertion time: "
        <<((double)(end-start)/CLOCKS_PER_SEC)
        <<endl;
    start = clock();
    for (int i = 0; i<arr.size(); ++i) {
        avlt->insert(arr[i]);
    }
    end = clock();
    cout<<"avl tree           insertion time: "
        <<((double)(end-start)/CLOCKS_PER_SEC)
        <<endl;

    // create array with different element
    for (set<int>::iterator i = ordered_set.begin(); i!=ordered_set.end(); ++i){
        arr_diff.push_back(*i);
    }
    cout<<arr_diff.size()<<" different numbers\n\n";





    // search numbers 
    start = clock();
    for (int i = 0; i<query.size(); ++i)
        if (ordered_set.find(query[i])!=ordered_set.end()) ++std_ans;
    end = clock();
    cout<<"std::set           search time: "
        <<((double)(end-start)/CLOCKS_PER_SEC)
        <<endl;

    start = clock();
    for (int i = 0; i<query.size(); ++i){
        if (unordered.find(query[i])!=unordered.end()) ++uno_ans;
    }
    end = clock();
    cout<<"std::unordered_set search time: "
        <<((double)(end-start)/CLOCKS_PER_SEC)
        <<endl;

    start = clock();
    for (int i = 0; i<query.size(); ++i){
        if (search_tree(root, query[i])) ++tree_ans;
    }
    end = clock();
    cout<<"red-black tree     search time: "
        <<((double)(end-start)/CLOCKS_PER_SEC)
        <<endl;
    start = clock();
    for (int i = 0; i<query.size(); ++i){
        if (search_tree(avlt, query[i])) ++avl_ans;
    }
    end = clock();
    cout<<"avl tree           search time: "
        <<((double)(end-start)/CLOCKS_PER_SEC)
        <<endl;

    start = clock();
    for (int i = 0; i<query.size(); ++i){
        for (int j = 0; j<arr_diff.size(); ++j){
            if (arr_diff[j] == query[i]) {
                ++arr_ans;
                break;
            }
        }
    }
    end = clock();
    cout<<"array              search time: "
        <<((double)(end-start)/CLOCKS_PER_SEC)
        <<endl;
    cout<<endl;






    // element remove
    start = clock();
    for (int i = 0; i<remove.size(); ++i) ordered_set.erase(remove[i]);
    end = clock();
    cout<<"std::set           remove time: "
        <<((double)(end-start)/CLOCKS_PER_SEC)
        <<endl;

    start = clock();
    for (int i = 0; i<remove.size(); ++i) unordered.erase(remove[i]);
    end = clock();
    cout<<"std::unordered_set remove time: "
        <<((double)(end-start)/CLOCKS_PER_SEC)
        <<endl;

    start = clock();
    for (int i = 0; i<remove.size(); ++i) root->del(remove[i]);
    end = clock();
    cout<<"red-black          remove time: "
        <<((double)(end-start)/CLOCKS_PER_SEC)
        <<endl;

    start = clock();
    for (int i = 0; i<remove.size(); ++i) {
        avlt->del(remove[i]);
    }
    end = clock();
    cout<<"avl tree           remove time: "
        <<((double)(end-start)/CLOCKS_PER_SEC)
        <<endl;

    return 0;
}
