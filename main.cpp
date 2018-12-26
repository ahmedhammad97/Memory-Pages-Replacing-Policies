#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>

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

int findAndReplaceMinimum(unordered_map<int,int>& usage, int page){
    int minValue = numeric_limits<int>::max();
    int minKey = -1;

    for(auto record : usage){
        if(record.second < minValue){minValue = record.second; minKey = record.first;}
    }
    return minKey;
}

void replacePage(vector<int>& pages, int oldPage, int newPage){
    for(auto& page : pages){
        if(page==oldPage){page = newPage; return;}
    }
}

void firstInFirstOut(vector<int>& pages){
    int page, oldest=0, faults=0;
    while(1){
        cin>>page;
        if(page==-1){return;}
        if(isThere(pages, page)){continue;}
        if(pages.size() == pages.capacity()){
            pages[oldest] = page;
            oldest++;
            faults++;
            if(oldest == pages.size()){oldest=0;}
        }
        else{pages.push_back(page);}
    }
}

void leastRecentlyUsed(vector<int>& pages){
    int page, faults=0, index=0;
    unordered_map<int,int> usage;
    while(1){
        cin>>page;
        if(page==-1){return;}
        if(isThere(pages, page)){usage[page] = ++index; continue;}
        if(pages.size() == pages.capacity()){
            int minn = findAndReplaceMinimum(usage, page);
            usage.erase(minn);
            usage[page] = ++index;
            replacePage(pages, minn, page);
            faults++;
        }
        else{
        pages.push_back(page);
        usage[page] = ++index;
        }
    }
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
