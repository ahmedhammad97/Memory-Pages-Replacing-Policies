#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <string>

using namespace std;


////////////////////////////////
//                            //
//   Coded by: Ahmed Hammad   //
//     www.ahmedhammad.me     //
//                            //
////////////////////////////////



/// Helper Functions
void takeInputs(string &type, vector<int>& pages, vector<int>& input){
    int nums;
    cin>>nums;
    cin>>type;
    pages.reserve(nums);

    int temp;
    while(1){
        cin>>temp;
        if(temp == -1){return;}
        else{input.push_back(temp);}
    }
}

void printHeader(string type){
    cout<<"Replacement Policy = "<<type<<endl;
    cout<<"-------------------------------------"<<endl;
    cout<<"Page   Content of Frames"<<endl;
    cout<<"----   -----------------"<<endl;
}

string fix(int num){
    if(num>9){return to_string(num);}
    else{return "0" + to_string(num);}
}

void printLine(vector<int>& pages, bool fault, int page){
    cout<<fix(page)<<" ";
    if(fault){cout<<"F";}else{cout<<" ";}
    cout<<"    ";
    for(auto& page : pages){
        cout<<fix(page)<<" ";
    }
    cout<<"\n";
}

void printFooter(int faults){
    cout<<"-------------------------------------"<<endl;
    cout<<"Number of page faults = "<<faults;
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

void flipUseBit(int page, vector<int>& pages, vector<bool>& bits){
    for(int i=0; i<pages.size(); i++){
        if(pages[i]==page){bits[i]=false; return;}
    }
}
/// End Helper Functions




/// Polocies
int firstInFirstOut(vector<int>& pages, vector<int>& input){
    int oldest=0, faults=0;
    for(auto& page : input){
        if(isThere(pages, page)){printLine(pages, false, page); continue;}
        if(pages.size() == pages.capacity()){
            pages[oldest] = page;
            oldest++;
            faults++;
            if(oldest == pages.size()){oldest=0;}
            printLine(pages, true, page);
        }
        else{pages.push_back(page); printLine(pages, false, page);}

    }
    return faults;
}

int leastRecentlyUsed(vector<int>& pages, vector<int>& input){
    int faults=0, index=0;
    unordered_map<int,int> usage;
    for(auto& page : input){
        if(isThere(pages, page)){
            usage[page] = ++index;
            printLine(pages, false, page);
            continue;
        }
        if(pages.size() == pages.capacity()){
            int minn = findAndReplaceMinimum(usage, page);
            usage.erase(minn);
            usage[page] = ++index;
            replacePage(pages, minn, page);
            faults++;
            printLine(pages, true, page);
        }
        else{
        pages.push_back(page);
        usage[page] = ++index;
        printLine(pages, false, page);
        }
    }
    return faults;
}

int clock(vector<int>& pages, vector<int>& input){
    int faults=0, index=0;
    vector<bool> bit(pages.capacity());
    fill(bit.begin(), bit.end(), false);
    for(auto& page : input){
        if(isThere(pages, page)){
            flipUseBit(page, pages, bit);
            printLine(pages, false, page);
            continue;
        }
        if(pages.size() == pages.capacity()){
            while(!bit[index]){
                bit[index]=true; index++;
                if(index==bit.size()){index=0;}
            }
            pages[index] = page;
            bit[index] = false;
            index++;
            if(index==bit.size()){index=0;}
            faults++;
            printLine(pages, true, page);
        }
        else{pages.push_back(page); printLine(pages, false, page);}
    }
    return faults;
}
/// End Polocies



int pickPolicy(string &type, vector<int>& pages, vector<int>& input){
    int faults;
    if(type == "FIFO"){faults = firstInFirstOut(pages, input);}
    else if(type == "LRU"){faults = leastRecentlyUsed(pages, input);}
    else if(type == "CLOCK"){faults = clock(pages, input);}
    else{
        cout<<"Wrong type! Renter it again"<<endl;
        cin>>type;
        pickPolicy(type, pages, input);
    }
    return faults;
}

int main()
{
    string type;
    vector<int> pages;
    vector<int> input;

    takeInputs(type, pages, input);

    printHeader(type);

    int faults = pickPolicy(type, pages, input);

    printFooter(faults);


    return 0;
}
