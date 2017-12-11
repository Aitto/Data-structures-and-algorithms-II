/**
Author: Aitto_Sang
CSE@Buet
*/
/**
Segment Tree for finding minimum in a range
*/
#include<stdio.h>
#include<iostream>
#include<cmath>
#include<cstdlib>
//#include<algorithm>
//#include<stack>
#include<cstring>
#include<ctime>
//#include<bits/stdc++.h>

#define lli long long int
#define pf printf
#define sf scanf
#define pi 3.141592653589793116
#define inf 1e9
#define linf 1e15
#define NULL_VALUE -999999
#define maxNEG -99999999.0
#define debug cout<<"Hello here!"<<endl;
#define readFile freopen("in.txt","r",stdin);
#define syncronize ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);


using namespace std;

int nextPrime(int i){
    int lim;
    bool track;
    for(i+=2;1;i+=2){
        track=true;
        lim=sqrt(i);

        for(int j=2;j<=lim;j++)
        if(i%j==0){
            track=false;
            break;
        }
        if(track) return i;
    }
}

int pow(int x,int y)
{
    int ans=1;
    while(y--) ans=(ans*x)%1000000;

    return ans;
}

struct elements
{
    string str;
    int data;
};

int hash1(const string str,int tableSize)
{
    int mask=5,len=str.length(),key=0;

    for(int i=1; i<=len; i++)
    {
        key= (key*mask + str[i-1]*pow(mask,i))%10000000;
        mask=nextPrime(mask);
    }

    return key%tableSize;
}

int hash2(int k,int m)
{
    double factor = (sqrt(5)-1)/2.0;
    int index;
    double c = k*factor;
    int INT = c;
    double d = c-INT;
    double r = d*m;
    index = r;
    return index;
}

int hashDumb(const string str,const int tableLength)
{

    int len=str.length();
    const float factor=pi;
    double sum=0;

    for(int i=0; i<len; i++)
    {
        sum= fmod(sum*factor + pow(str[i],str[i]),10000000);
    }

    int key= sum;
    return key%tableLength;
}

int hash3(const string str,int tablesize)
{
    long fnv_prime = 0x811C9DC5;
    long hash = 0;

    for(int i = 0; i < str.length(); i++)
    {
        hash *= fnv_prime;
        hash ^= str[i];
    }

    return abs(hash%tablesize);
}

int linearProb(elements *element,int tableLength,string s,int startIndex,bool src=true,bool del=false)
{
    if(src)
    {
        //For inserting
        int i=startIndex;

        while(1)
        {
            i++;
            i=i%tableLength;
            if(element[i].str.length()==0 or element[i].str=="-1") return i; // Empty or deleted slot found
            if(i==startIndex) return inf; //Table is full. No slot available
            if(element[i].str==s) return -1; //Duplicate data

        }
    }
    else
    {
        if(del)
        {
            //For deleting For searching returning index
            int i=startIndex;

            while(1)
            {
                i++;
                i=i%tableLength;
                if(element[i].str.length()==0) return -1; // Empty or deleted slot found
                if(i==startIndex) return inf; //Table is full. Not found
                if(element[i].str==s) return i; //Duplicate data
            }

        }
        else
        {
            //For searching
            int i=startIndex;

            while(1)
            {
                i++;
                i=i%tableLength;
                if(element[i].str.length()==0) return i; // Empty or deleted slot found
                if(i==startIndex) return inf; //Table is full. No slot available
                if(element[i].str==s) return -1; //Duplicate data

            }
        }

    }

}

class HashOpen
{
    elements  *element;
    int hashLength;
    int clash;

public:
    HashOpen(int len=10000)
    {
        hashLength=len;
        element=new elements[hashLength +1];
        clash=0;
    }

    int insertData(const char *str,const int data,int hashing)
    {
        int key;


        if(hashing==1) key=hash1(str,hashLength);
        else if(hashing==2) key=hash2(data,hashLength);
        else key=hash3(str,hashLength);
        // debug cout<<key<<endl;
        //int key=hash2()

        if(element[key].str.length()>0)
        {
            //pf("Clash in data... hash position: %d",key);
            key=linearProb(element,hashLength,str,key);
            //pf("returned position: %d\n",key);
            clash++;
        }
        if(key==inf)
        {
            //pf("Table is full\n");
            clash--;
            return inf;
        }
        else if(key==-1)
        {
            //pf("Duplicate data\n");
            clash--;
            return -1;
        }
        //cout<< "inserting: "<<str<< " "<<data<< " at "<<key<<endl;

        element[key].str=str;
        element[key].data=data;

        return 1;
    }

    int searchData(const string key,int hashing)
    {

        int index;
        if(hashing==1) index=hash1(key,hashLength);
        else if(hashing==2) index;
        else index=hash3(key,hashLength);

        int track=index;
        if(element[track].str!=key) track=linearProb(element,hashLength,key,index,false); //false for ignoring deleted key

        if(track==-1)
        {
            //cout<< "found key"<<endl;
            return -1;
        }else {
           // cout<< "key not found"<<endl;
        }

        return 0;

    }

    void deleteData(const char* str,int hashing)
    {
        int index;
        if(hashing==1) index=hash1(str,hashLength);
        else if(hashing==2) index;
        else index=hash3(str,hashLength);

        int track=index;
        if(element[track].str!=str) track=linearProb(element, hashLength,str,index,false,true);

        if(track!=-1 or track!=inf)
        {
            element[track].str="-1";
            element[track].data=-inf;
            //pf("Data Deleted\n");
        }
    }

    void printHashTable()
    {
        //for(int i=0; i<hashLength; i++) cout<< element[i].str<< " "<<element[i].data<<endl;
        cout<<endl<< "total number of clash: "<<clash<<"about "<< (double)(clash/(double)hashLength)*100<<"\%"<<endl;
    }

};

class elementSC
{
public:
    string str;
    int data;
    elementSC *next;

    elementSC(string s,int d)
    {
        str=s;
        data=d;
        next=0;
    }
};

class HashSC
{
    elementSC **element;
    int tableSize;
    int clash;
public:

    HashSC(int len=10000)
    {
        debug
        tableSize=len;
        element=new elementSC*[tableSize +1];
        for(int i=0; i<len; i++) element[i]=0;
        clash=0;
    }

    bool insertData(const char* str,const int data,int hashing)
    {
        //int index=hash1(str,tableSize);
        int index;
        if(hashing ==1) index=hash1(str,tableSize);
        else if(hashing==2) index=hash2(data,tableSize);
        else index=hash3(str,tableSize);

        if(element[index]!=0)
        {
            elementSC *temp=element[index];

            while(temp->next!=0)
            {
                if(temp->str==str)
                {
                    cout<< "duplicate data..."<<endl;
                    clash--;
                    return true;
                }
                temp=temp->next;
            }

            temp->next=new elementSC(str,data);
            temp->next->next=0;
            clash++;
        }
        else
        {
            element[index]=new elementSC(str,data);
            element[index]->next=0;
        }

        return false;
    }

    void Search(string key,int hashing,int data=0){
        int index;
        if(hashing==1) index=hash1(key,tableSize);
        else if(hashing==2) index=hash2(data,tableSize);
        else index=hash3(key,tableSize);

        if(element[index]==0){
            //cout<< " No data found "<<endl;
            return;
        }
        elementSC *temp=element[index];
        while(temp!=0){
            if(temp->str==key){
                //cout<<"Data found"<<endl;
                return;
            }
            temp=temp->next;
        }

    }

    void deleteData(string key,int hashing,int data=0)
    {
        int index;
        if(hashing==1) index=hash1(key,tableSize);
        else if(hashing==2) index=hash2(data,tableSize);
        else index=hash3(key,tableSize);

        elementSC *temp=element[index];
        if(temp==0) return;
        if(temp->str==key) element[index]=temp->next;
        while(temp->next!=0)
        {
            if(temp->next->str==key)
            {
                //cout<<"data deleted...\n";
                temp->next=temp->next->next;
                return;
            }
            temp=temp->next;
        }

    }

    void printHashTable()
    {
        elementSC *temp;
        /*for(int i=0; i<tableSize; i++)
        {
            temp=element[i];

            while(temp!=0)
            {
                cout<<temp->str<< " "<<temp->data<<endl;
                temp=temp->next;
            }
        }*/

        cout<< "total clash about: "<<(clash*100.0/tableSize)<< "\%" <<endl;
    }

};

int main()
{

    syncronize
    readFile
    srand(time(NULL));

    int tableSize,wordLength=0,words=1,track;
    char *ch;

    cin>>tableSize>>wordLength;
    ch=new char[wordLength +1];

    HashOpen *h;
    HashSC *hsc;

    for(int i=1; i<=2; i++)
    {
        // Linear Probing Method
        if(i==1)
        {
            //Controlling hash functions
            for(int hashing=1; hashing<=3; hashing++)
            {
                h=new HashOpen(tableSize);

                for(int k=0; k<tableSize; k++)
                {
                    //Generating words
                    for(int j=0; j<wordLength; j++)
                    {
                        ch[j]= (rand()%26) + 97;
                    }
                    ch[wordLength]='\0';

                    track=h->insertData(ch, k +1,hashing);

                    //cout<< "inserting: "<<ch<<endl;
                    //Checking if data is duplicate or table is full
                    while(track==-1)
                    {
                        for(int j=0; j<wordLength; j++)
                        {
                            ch[j]= (rand()%26) + 97;
                        }
                        ch[wordLength]='\0';

                        track=h->insertData(ch,k+1,hashing);

                        if(track==inf) break;
                    }
                    if(track==inf) break;
                }

               // cout<< endl<<"Printing hash..."<<endl;
                //h.print();
                h->printHashTable();
                free(h);
            }
        }else{
            for(int hashing=1; hashing<=3; hashing++)
            {
                hsc=new HashSC(tableSize);

                for(int k=0; k<tableSize; k++)
                {
                    for(int j=0; j<wordLength; j++)
                    {
                        ch[j]= (rand()%26) + 97;
                    }
                    ch[wordLength]='\0';
                    //track=h.insertData(ch, i +1);
                    bool track=hsc->insertData(ch,k +1,hashing);

                    while(track)
                    {
                        for(int j=0; j<wordLength; j++)
                        {
                            ch[j]= (rand()%26) + 97;
                        }
                        ch[wordLength]='\0';

                        track=hsc->insertData(ch,k +1,hashing);
                    }

                }

                cout<< endl<<"Printing hash..."<<endl;
                //h.print();
                hsc->printHashTable();
                free(hsc);
        }
    }
    }

    return 0;

}
