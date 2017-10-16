#include<stdio.h>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<set>
#include<map>
#include<cstring>

#define pf printf
#define sf scanf

#define pi 3.141592653589793116
#define maxREAL 9999999.0
#define INF 9999999
#define maxNEG -99999999.0

#define debug cout<<"Hello here!"<<endl;
#define newl pf("\n");

using namespace std;
int dp[1000][10000];

//recursion part
/**int minCoin(int coins[],int len,int value){
    if(value==0) return 0;

    int res=INF;

    for(int i=0;i<len;i++){
        if(coins[i]<=value){
            int sr=minCoin(coins,len,value-coins[i]);

            if(sr!=INF and sr + 1 <res ){
                res=sr +1;
            }
        }
    }

    return res;
}*/

int minCoinDP(int coins[],int range[],int len,int value)
{

    int **track;
    track=new int*[len+1];
    for(int i=0;i<=len;i++) track[i]=new int[value +1];
    
    memset(track,0,sizeof(track));

    for(int i = 0; i<=value; ++i)
        dp[0][i] = INF;
    for(int i=0; i<=len; i++)
        dp[i][0] = 0;
    for(int i=1; i<=len; i++)
    {
        for(int j=0; j<=value; j++)
        {
            dp[i][j]=dp[i-1][j];
                for(int k=0; (k<=range[i-1]) && (j-k*coins[i-1]>=0) ; k++){
                    if(dp[i-1][j-k*coins[i-1]] + k<dp[i][j])
                        track[i][j]=k;
                    dp[i][j]=min(dp[i][j],dp[i-1][j-k*coins[i-1]] + k);

            }
        }
    }

    /*for(int i=0;i<=len;i++)
    {
        for(int j=0;j<=value;j++)
            cout<<track[i][j]<<' ';
        cout<<endl;
    }*/
    int tvalue=value;
    int tlen=len;
    while(1){
            if(value==0 or len==0) break;
        if(track[len][value]){
                cout<<coins[len-1]<< "*" << track[len][value]<<endl;
                value-=coins[len-1]*track[len][value];
        }
        len--;
    }

    return dp[tlen][tvalue];
}

int main()
{

    int len,val;

    cin>>val>>len;
    int coins[len],range[len];

    for(int i=0; i<len; i++)
    {
        cin>>coins[i];
    }
    for(int i=0; i<len; i++)
    {
        cin>>range[i];
    }

    cout<< minCoinDP(coins,range,len,val)<<endl;


    return 0;
}
