/**
This algorithm determines maximum flow in a network. Using ford_fulkersion method
*/
#include<stdio.h>
#include<iostream>

#define inf 99999999
#define NULL_VALUE -999999
#define debug cout<< "Here I'm!"<<endl;
#define readFile freopen("in.txt","r",stdin);
#define sf scanf
#define pf printf

void bfs(int **graph,int n,int source,int *parent,int *visit);

using namespace std;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue()
    {
        queueInitSize = 2 ;
        queueMaxSize = queueInitSize;
        data = new int[queueMaxSize] ; //allocate initial memory
        length = 0 ;
        front = 0;
        rear = 0;
    }

    ~Queue(){
        if(data) delete[] data; //deallocate memory
        data = 0; //set to NULL
    }

    void enqueue(int item){
        if (length == queueMaxSize)
        {
            int * tempData ;
            //allocate new memory space for tempList
            queueMaxSize = 2 * queueMaxSize ;
            tempData = new int[queueMaxSize] ;
            int i, j;
            j = 0;
            for( i = rear; i < length ; i++ )
            {
                tempData[j++] = data[i] ; //copy items from rear
            }
            for( i = 0; i < rear ; i++ )
            {
                tempData[j++] = data[i] ; //copy items before rear
            }
            rear = 0 ;
            front = length ;
            delete[] data ; //free the memory allocated before
            data = tempData ; //make list to point to new memory
        }

        data[front] = item ; //store new item
        front = (front + 1) % queueMaxSize ;
        length++ ;
    } //insert item in the queue


    int dequeue(){
        if(length == 0) return NULL_VALUE ;
        int item = data[rear] ;
        rear = (rear + 1) % queueMaxSize ;
        length-- ;
        return item ;
    } //returns the item according to FIFO

        bool empty(){
        if(length == 0) return true ;
        else return false ;
    } //return true if Queue is empty
};

//initialize a 1D array
void initialize(int *p,int n,int val){
    for(int i=0;i<n;i++) p[i]=val;
}

//Determines if there is a path exist from sink to source, by checking their parents
bool existAPath(int *p,int source,int sink){
    //cout<<endl<<endl<< "Path: "<<endl;
    while(1){
        if(source==sink) return true;
        if(sink==-1) return false;
        //pf("%d %d\n",p[sink],sink);
        sink=p[sink];
    }
}

//Determines minimum capacity or maximum flow in the path from source, to sink
int minflow(int **graph,int *p,int source,int sink){
    int maxFlow=inf;

    while(1){
        if(source==sink) return maxFlow;
        if( graph[p[sink]][sink] < maxFlow ) maxFlow=graph[p[sink]][sink];
        sink=p[sink];
    }
}

//Finds residual network in the graph
void makeResidual(int **graph,int **flow,int **residual,int n){

    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
        /*If there in an edge from i to j, then residual capacity of edge (i,j) would be
        capacity of the edge (i,j) - flow in the edge (i,j)
        */
        if(graph[i][j]!=inf) residual[i][j]=graph[i][j]-flow[i][j];
        /* If there is a flow from i to j, and there is no edge from j to i, then residual capacity of edge(j,i)
        would be equal to flow of (i,j)
        */
        if(graph[j][i]==inf and flow[i][j]!=0) residual[j][i]=flow[i][j];
        //We asumed that inf=no edge; Capacity 0 means no flow there, which similar to no edge
        if(residual[i][j]==0) residual[i][j]=inf;
    }
}

//printing a 2D array
void print(int **arr,int s,int n){
    for(int i=s;i<=n;i++){
        for(int j=s;j<=n;j++){
            if(arr[i][j]==inf) pf("INF ");
            else pf("%3d ",arr[i][j]);
        }
        pf("\n");
    }
}

//Printing a 1D array
void print(int *arr,int s,int n){
    for(int i=s;i<=n;i++){
        cout<<i<< " " <<arr[i]<<endl;
    }
    pf("\n");
}

//Making flow graph
void makeFlow(int **graph,int **flow,int *parent,int source,int sink,int value){
    
    //Adding flow value in the augmentation path. Searching the path by parents from sink to source
    while(1){
        if(source==sink) return;
        if(graph[parent[sink]][sink]!=inf) //IF there is really an edge, then add flow
            flow[parent[sink]][sink]+=value;
        else
            flow[parent[sink]][sink]-=value; //If there is no such edge, means cancellation of the flow
        sink=parent[sink];
    }

}

void fordFulkerson(int **graph,int **flow,int **residual,int n,int source,int sink){
    int *parent,*visit;
    parent=new int[n +1];
    visit=new int[n +1];

    int maxflow=0;

    makeResidual(graph,flow,residual,n);
    /*cout<< "Graph: "<<endl;
    print(graph,1,n);
    cout<< "Flow: "<<endl;
    print(flow,1,n);
    cout<< "Residual: "<<endl;
    print(residual,1,n);
    pf("\n\nSink:%d, Source:%d\n\n",sink,source);*/

    bfs(residual,n,source,parent,visit);

    while(existAPath(parent,source,sink)){
        int tem=minflow(residual,parent,source,sink);

        maxflow+=tem;
        //cout<< "\nmin flow:"<<tem<<endl<<endl;

        makeFlow(graph,flow,parent,source,sink,tem);
        makeResidual(graph,flow,residual,n);
        /*cout<< "Graph: "<<endl;
        print(graph,1,n);
        cout<< "Flow: "<<endl;
        print(flow,1,n);
        cout<< "Residual: "<<endl;
        print(residual,1,n);*/

        bfs(residual,n,source,parent,visit);

        //tem=minflow(residual,parent,source,sink);
        //cout<< "min flow:"<<tem<<endl;
        //print(parent,1,n);
        //break;
    }

    cout<<endl<< "Maxflow: "<<maxflow<<endl;
}

//Runnign bfs tp find shortest path. Level by level travarsal
void bfs(int **graph,int n,int source,int *parent,int *visit){

    initialize(parent,n +1,-1);
    initialize(visit,n +1, 0);
    parent[source]=0;

    int temp;
    Queue que;
    que.enqueue(source);

    while(!que.empty()){
        temp=que.dequeue();

        for(int i=1;i<=n;i++){
            if(visit[i]==1) continue;
            if(  (graph[temp][i]!=inf)and parent[i]==-1){
                que.enqueue(i);
                parent[i]=temp;
            }
        }
        visit[temp]=1;
    }

}

int main(){

    readFile

    int n,m,u,v,c,source,sink;
    cin>>n>>m;

    int **graph,**flow,**residual;

    //Memory allocation and initialization
    graph=new int*[n +1];
    flow=new int*[n +1];
    residual=new int*[n +1];

    for(int i=0;i<=n;i++){
        graph[i]=new int[n +1];
        flow[i]=new int[n +1];
        residual[i]=new int[n +1];

        for(int j=0;j<=n;j++){
            graph[i][j]=inf;
            flow[i][j]=0;
            residual[i][j]=inf;
        }
    }

    //Input graph
    for(int i=0;i<m;i++){
        cin>>u>>v>>c;
        graph[u][v]=c;
    }

    cin>>source>>sink;
    fordFulkerson(graph,flow,residual,n,source,sink);


    return 0;
}
