#include<iostream>
#include<string>
#include <map>
#include<vector>
#include <sstream>
#include <cmath>

#define N 3

using namespace std;

string documents[N][2]={{"A","the mouse played with the cat"},
                      {"B","The quick brown fox jumps over the lazy dog"},
                      {"C","dog 1 and dog 2 ate the hot dog"}};

map <string, double> tf[3];
map <string, double> idf;

vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

string makeLower(string s){
    char *str=new char[s.length() +1];
    for(int i=0;i<=s.length();i++)
        if(s[i]>= 'A' and s[i] <='Z') str[i]=s[i]- 'A' + 'a';
        else str[i]=s[i];

    return str;

}

void calculateTFIDF(){
    for(int i=0;i<3;i++){

        vector<string> temp=split(documents[i][1], ' ');

        int len=temp.size();
        for(int j=0;j<len;j++) tf[i][makeLower(temp[j])] ++;
        cout<< "\n\n\nTF\n\n\n";
        for(map<string,double>::iterator it=tf[i].begin(); it!=tf[i].end(); ++it)
        {
            idf[it->first]++;
            cout << it->first << " => " << it->second << '\n';
        }
        cout<< "\n\n\nIDF\n\n\n";

    }

    for(map<string,double>::iterator it=idf.begin(); it!=idf.end(); ++it){
        cout << it->first << " => " << it->second << '\n';
    }

}

double findMatch(map<string, double> query, int documentNo){

   return 0;
}

int vectorDimension(int tfVal,int idfVal){
    if(idfVal==0) return 0;
    return tfVal*log(3.0/idfVal);
}

string findDocument(string query){
    vector<string> vec=split(query,' ');
    int len=vec.size();

    map<string,double> tfDumb;
    for(int i=0;i<len;i++) tfDumb[vec[i]]++;
    //vector< pair<int,int> > vc;
    int vc[2];

    int a[3],x=0;
    for(map<string,double>::iterator it=tfDumb.begin();it!=tfDumb.end();it++){
        //vectorDimension( it->second, idf[it->first]);
         a[x]=vectorDimension( it->second, idf[it->first] );
         x++;
    }
    vc[0]=a[0], vc[1]=a[1];

    //vector< pair<int,int> >
    int vpair[3][2];
    for(int i=0;i<3;i++){
        x=0;
        for(map<string,double>::iterator it=tfDumb.begin();it!=tfDumb.end();it++){
        //vectorDimension( it->second, idf[it->first]);
           a[x]=vectorDimension( tf[i][it->first], idf[it->first] );
            x++;
        }
       // vpair[i].push_back( { a[0], a[1] } );
        vpair[i][0]=a[0], vpair[i][1]=a[1];
    }

    string ch;
    double mini=9999.998;

    for(int i=0;i<3;i++){
        double dot, aval, bval;
        //dot=vc[0].first*vpair[i][0].first + vc[1].first*vpair[i][1].first ;
        dot=vc[0]*vpair[i][0] + vc[1]*vpair[i][1];
        //aval=sqrt( vpair[i][0].first*vpair[i][0].first + vpair[i][1].first*vpair[i][1].first );
        aval= sqrt(vpair[i][0]*vpair[i][0] + vpair[i][1]*vpair[i][1]);
        //bval=vc[0].first*vc[0].first + vc[1].first*vc[1].first;
        bval=sqrt(vc[0]*vc[0] + vc[1]*vc[1]);

        if((dot/(aval*bval))<mini){
             mini=dot/(aval*bval);
             if(i==0) ch="a\0";
             else if(i==1) ch="b\0";
             else if(i==2)ch="c\0";
        }
    }


    return ch;
}


int main(){

    calculateTFIDF();
    cout<<findDocument("fox jumps");

   /* map <string, double> m;
    m["foo"] = 42;

      if (m.find("foo") != m.end()){
        cout << "map contains key world!\n";
        cout<<m["foo"];
      }
      else{
        cout <<"not exist"<<endl;
      }

      */

    /*
    for(map<string,double>::iterator it=query.begin(); it!=query.end(); ++it)
    {
        cout << it->first << " => " << it->second << '\n';
    }
*/


    return 0;
}

