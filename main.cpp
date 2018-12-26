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
int page, oldest=0, falts=0;

    while(1){
        cin>>page;
        if(page==-1){return;}
        if(isThere(pages, page)){continue;}
        if(pages.size() == pages.capacity()){
            pages[oldest] = page;
            oldest++;
            if(oldest == pages.size()){oldest=0;}
        }
        else{pages.push_back(page);}
    }
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
