#include <iostream>
#include <vector>
#include <algorithm>

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

void fix(int num){
    if(num>9){cout<<num;}
    else{cout<<"0"<<num;}
}

void printLine(vector<int>& pages, bool fault, int page){
	fix(page);
    cout<<" ";
    if(fault){cout<<"F";}else{cout<<" ";}
    cout<<"   ";
    for(int i=0; i<pages.size(); i++){
        fix(pages[i]);
		cout<<" ";
    }
    cout<<"\n";
}

void printFooter(int faults){
    cout<<"-------------------------------------"<<endl;
    cout<<"Number of page faults = "<<faults<<endl;
}

bool isThere(vector<int>& pages, int target){
    for(int i=0; i<pages.size(); i++){
        if(pages[i] == target){return true;}
    }
    return false;
}

int getIndex(vector<int>& pages, int page){
		for(int i=0; i<pages.size(); i++){
			if(pages[i]==page){return i;}
		}
		cout<<"Error!"<<endl;
		return -1;
}

int findMinimum(vector<int>& usage){
    int minValue = 99999;
    int minKey = -1;

    for(int i=0; i<usage.size(); i++){
        if(usage[i] < minValue){minValue = usage[i]; minKey = i;}
    }
    return minKey;
}

void replacePage(vector<int>& pages, int oldPage, int newPage){
    for(int i=0; i<pages.size(); i++){
        if(pages[i]==oldPage){pages[i] = newPage; return;}
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
    for(int i=0; i<input.size(); i++){
		int page = input[i];
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
    vector<int> usage;
    usage.reserve(pages.capacity());
    for(int i=0; i<input.size(); i++){
		int page = input[i];
        if(isThere(pages, page)){
            usage[getIndex(pages, page)] = ++index;
            printLine(pages, false, page);
            continue;
        }
        if(pages.size() == pages.capacity()){
            int minnIndex = findMinimum(usage);
            usage[minnIndex] = ++index;
            pages[minnIndex] = page;
            faults++;
            printLine(pages, true, page);
        }
        else{
        pages.push_back(page);
        usage.push_back(++index);
        printLine(pages, false, page);
        }
    }
    return faults;
}

int clock(vector<int>& pages, vector<int>& input){
    int faults=0, index=0;
    vector<bool> bit(pages.capacity());
    fill(bit.begin(), bit.end(), false);
    for(int i=0; i<input.size(); i++){
		int page = input[i];
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
