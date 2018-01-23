#include<stdio.h>
#include<vector>
#include<iostream>
#include<set>
#include<algorithm>

#define sf scanf
#define pf printf
#define N 100
#define maz(a,b) a>b?a:b;
#define inf 1e9;

using namespace std;

int n,m,t,maxSize,total;
vector<int> subSet[N];
string stans;

void findSetCover(string track,int indexTrack){
    int picked=0;
    int maxCardinality=0;

    set<int> coveredSet;

    for(int i=0;i<m;i++){
        if(track[i]=='1'){
            picked++;
            for(int j=0;j<subSet[i].size(); j++){
                coveredSet.insert(subSet[i][j]);
            }
        }else{
            maxSize=subSet[i].size();
            maxCardinality=max(maxCardinality,maxSize);
        }
    }

    int lowerB=inf;
    if(maxCardinality){
        double x=(double)(n-coveredSet.size())/maxCardinality;
        lowerB=picked + ceil(x);
    }

    if(coveredSet.size()==n){
        int counter=0;
        for(int i=0;i<m;i++){
            if(track[i]=='1') counter++;
        }
        if(total>counter){
            total=counter;
            stans=track;
            return;
        }
    }

    if(lowerB>total) return;

    string tempS=track;
    track[indexTrack]='1';

    if(indexTrack<m){
        findSetCover(tempS,indexTrack +1);
        findSetCover(track,indexTrack +1);
    }

}

int main(){

    char ch;
    string track;

    sf("%d %d%c",&n,&m,&ch);

    vector<int> tt;

    int i=0,x;
    //cout<<n<< " "<<m<< " "<<ch<<123<<endl;
    t=m;
    while(t--){
        sf("%d%c",&x,&ch);
        subSet[i].push_back(x);
        while(ch!='\n'){
            sf("%d%c",&x,&ch);
            subSet[i].push_back(x);
        }
        i++;
    }

    total=m;

    string s;
    for(int i=0;i<m;i++) s+='0';

    stans=s;
    findSetCover(s,0);

    int k=0;
    for(int i=0;i<m;i++){
        if(stans[i]=='1') k++;
    }

    cout<<k<<endl;
    for(int i=0;i<m;i++){
        if(stans[i]=='1'){
            for(int j=0;j< subSet[i].size();j++) pf("%d ",subSet[i][j]);
            pf("\n");
        }
    }

    /*cout<<endl<<endl;
    for(i=0;i<m;i++){
        int j=subSet[i].size();
        while(j){
            cout<<subSet[i][j-1]<<" ";
            j--;
        }
        cout<<endl;
    }*/


    return 0;

}

/*5 6
1 2 3
4 5 6
7 8 9
0 1 2
3 4 5
6 7 8
*/
