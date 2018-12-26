#include <iostream>
#include <vector>

using namespace std;

void takeInputs(string &type, vector<int>& pages){
    int nums;
    cin>>nums;
    cin>>type;
    pages.reserve(nums);
}

bool isThere(vector<int>& pages, int target){
    for(auto& page : pages){
        if(page == target){return true;}
    }
    return false;
}

void firstInFirstOut(vector<int>& pages){

}

void leastRecentlyUsed(vector<int>& pages){

}

void clock(vector<int>& pages){

}

void pickPolicy(string &type, vector<int>& pages){
    if(type == "FIFO"){firstInFirstOut(pages);}
    else if(type == "LRU"){leastRecentlyUsed(pages);}
    else if(type == "CLOCK"){clock(pages);}
    else{
        cout<<"Wrong type! Renter it again"<<endl;
        cin>>type;
        pickPolicy(type, pages);
    }

    for(auto& page : pages){cout<<page<<" ";}
}

int main()
{
    string type;
    vector<int> pages;

    takeInputs(type, pages);

    pickPolicy(type, pages);




    return 0;
}
