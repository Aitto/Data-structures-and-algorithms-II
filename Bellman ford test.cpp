
#include<stdio.h>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<algorithm>

#define pf printf
#define sf scanf
#define pi 3.141592653589793116
#define INF 99999
#define maxInt 99999999
#define maxNEG -99999999.0
#define debug cout<<"Hello here!"<<endl;

using namespace std;

struct edgeExtra{
    int u;
    int v;
    float weight;
    edgeExtra(int x=0,int y=0, float z=0.0){
        u=x,v=y,weight=z;
    }
};

struct edge{
    int v;
    float weight;
    edge(int x=0,float w=0.0){
        v=x,weight=w;
    }
};

class HeapItem{
public:
    int data;
    float key;
};

class priorityQueue{
    HeapItem *A;
    int length;
    int capacity;
    int *map;

public:
    priorityQueue(int c=32){
        //initialized at 1
        capacity=c;
        A=new HeapItem[capacity+1];
        map=new int[capacity+1];
    }

    void enqueue(int data,int key){

        //increasing queue size
        if(length==capacity){
            HeapItem *t;
            int *tt;
            capacity= (capacity-1)*2;
            t=new HeapItem[capacity+1];
            tt=new int[capacity + 1];

            for(int i=1;i<=length;i++) {
                t[i]=A[i];
                tt[i]=map[i];
            }
            delete []A;
            delete []map;

            A=t;
            map=tt;
        }

        length++;
        A[length].data=data;
        A[length].key=key;

        //mapping the data
        map[data]=length;
        buHeapify(length);
        //building heap property
    }

    void buHeapify(int source){
        //getting parent and child
        int parent=source/2;
        int child=source;

        while(parent){
            if( A[parent].key> A[child].key ){
                HeapItem temp;
                temp=A[parent];
                A[parent]=A[child];
                A[child]=temp;

                map[A[parent].data]=parent;
                map[A[child].data]=child;

                child=parent;
                parent=parent/2;
            }else break;
        }
    }

    void heapify(int source){
        int smallest;
        int left,right;

        while(1){
            left=source*2;
            right=source*2 +1;

            if(left > length) break; // right> left so if left>length we are at bottom
            else if(right > length ) smallest=left;
            else if( A[left].key < A[right].key ){
                smallest=left;
            }else{
                smallest=right;
            }

            if( A[smallest].key< A[source].key ){
                HeapItem t;
                t=A[smallest];
                A[smallest]=A[source];
                A[source]=t;

                //keeping track of data
                map[ A[source].data ]=source;
                map[ A[smallest].data ]=smallest;
                source=smallest;
            }else break; //tree is heapified
        }
    }

    void updateKey(int data,float key){
        int pos=map[data];
        int k=getKey(data);

        if(pos==0){
            pf("No such heapitem found!\n");
            return;
        }

        if( A[pos].key >key ){
            A[pos].key=key;
            buHeapify(pos);
        }else{
            A[pos].key=key;
            heapify(pos);
        }
    }

    float getKey(int data){
        return A[ map[data] ].key;
    }

    HeapItem extractMin(){
        HeapItem temp;

        if( length==0 ){
            temp.data=-1;
            temp.key=-1.0;
            pf("No heap item to extract\n");

            return temp;
        }
        temp=A[1];
        A[1]=A[length];
        length--;
        heapify(1);

        return temp;
    }

};

class MinHeapEdge{
    edgeExtra *A;
    int length;
    int capacity;
    int **map;

public:
    MinHeapEdge(int c=16){
        length=0;
        capacity=c +1;
        A=new edgeExtra[capacity+1];
        map=new int*[capacity+1];
        for(int i=0;i<=capacity;i++) map[i]=new int[capacity + 1];
        //debug
    }

    void enqueue(int u,int v,float w){
        //cout<< u<< " "<<v << " "<<w<<endl;
        //increasing queue size
        if(length==capacity){
            pf("Increasing minHeapEdge capacity\n");
            edgeExtra *t;
            int **tt;
            //allocating new memory
            capacity=(capacity-1)* 2;

            t=new edgeExtra[capacity+1];
            tt=new int*[capacity + 1];

            for(int i=0;i<=length;i++) {
                t[i]=A[i];
                tt[i]=new int[capacity + 1];
                for(int j=0;j<=capacity;j++) tt[i][j]=map[i][j];
            }
            free(A);
            free(map);

            A=t;
            map=tt;
        }

        length++;
        A[length].u=u;
        A[length].v=v;
        A[length].weight=w;

        //mapping the data. As edge will be ()
        map[u][v]=length;
        //map[v][u]=length;
        buHeapify(length);
        //building heap property
    }

    void buHeapify(int source){
        //getting parent and child
        int parent=source/2;
        int child=source;

        while(parent){
            if( A[parent].weight> A[child].weight ){
                edgeExtra temp;
                temp=A[parent];
                A[parent]=A[child];
                A[child]=temp;

                //mapping data
                map[A[parent].u][A[parent].v]=parent;
                //map[A[parent].v][A[parent].u]=parent;
                map[A[child].u][A[child].v]=child;
                //map[A[child].v][A[child].u]=child;

                child=parent;
                parent=parent/2;
            }else break;
        }
        //debug
    }

    void heapify(int source){
        int smallest;
        int left,right;

        while(1){
            left=source*2;
            right=source*2 +1;

            if(left > length) break; // right> left so if left>length we are at bottom
            else if(right > length ) smallest=left;
            else if( A[left].weight < A[right].weight ){
                smallest=left;
            }else{
                smallest=right;
            }

            if( A[smallest].weight< A[source].weight ){
                edgeExtra t;
                t=A[smallest];
                A[smallest]=A[source];
                A[source]=t;

                //keeping track of data
                map[ A[source].u ][ A[source].v ]=source;
                //map[ A[source].v ][A[source].u]=source;
                map[ A[smallest].v ][A[smallest].u]=smallest;
                //map[ A[smallest].u ][A[smallest].v]=smallest;
                source=smallest;
            }else break; //tree is heapified
        }
    }

    void updateKey(int u,int v,int w){
        int pos=map[u][v];
        int k=getWeight(u,v);

        if(pos==0){
            pf("No such heapitem found!\n");
            return;
        }

        if( A[pos].weight >w ){
            A[pos].weight=w;
            buHeapify(pos);
        }else{
            A[pos].weight=w;
            heapify(pos);
        }
    }

    float getWeight(int u,int v){
        int pos=map[u][v];
        if(pos <0 || pos >length){
            pf("Mapping error!\n");
            return -0.1;
        }
        return A[ pos ].weight;
    }

    edgeExtra removeMin(){
        edgeExtra t;

        if(length==0){
            pf("No item to remove\n");
            t.u=-1;
            t.v=-1;
            t.weight=-1.0;
            return t;
        }
        t=A[1];

        A[1]=A[length];
        length--;

        heapify(1);

        return t;
    }

    void printHeap(){
        for(int i=1;i<=length;i++){
            pf("(%d, %d, %f) ",A[i].u, A[i].v, A[i].weight);
        }
        cout<<endl;
    }

};

/**maintain Adjacency list class*/
class AdjList{
    edge *list;
    int length;
    int capacity;
public:
    Adjlist(int l=4){
        capacity=l;
        list = new edge[capacity];
        length=0;
    }

    void insert(edge item){
        /** doubles the capacity if list is full */
        if(length==capacity){
            edge *temp;
            capacity*=2;
            temp=new edge[capacity];

            for(int i=0;i<length;i++) temp[i]=list[i];

            list=temp;
        }
        list[length]=item;
        length++;
    }

    int getLength(){
        return length;
    }

    //returns true if the item exists and removed, otherwise false
    bool removeItem(edge e){
        int pos=searchItem(e.v,e.weight);
        if(pos==-1) return false;
        return removeItemAt(pos);
    }

    bool removeItemAt(int pos){
        if(pos<0 || pos >=length) return false;
        list[pos]=list[length-1];
        length--;
        return true;
    }

    edge getItemAt(int position){
        if(position<0 || position>=length) return edge(0,0.0);

        return list[position];
    }

    int searchItem(edge e){
        int v=e.v,w=e.weight;
        for(int i=0;i<length;i++){
            if(list[i].v==v &&  list[i].weight==w) return i;
        }

        return -1;
    }

     int searchItem(int v,int w){
        for(int i=0;i<length;i++){
            if(list[i].v==v &&  list[i].weight==w) return i;
        }

        return -1;
    }

};

class Graph{
    AdjList *adjlist;
    edgeExtra *e;
    int eLength;
    int nEdges;
    int length;
    int nVertices;
    MinHeapEdge mh;
    int *parent;
    int *distance;
    bool directed;
public:
    Graph(bool dir=false){
        directed=dir;
        e=0;
        adjlist=0;
        eLength=0;
        length=0;
        nVertices=0;
        nEdges=0;
        parent=0;
        distance=0;
    }

    void setNvertices(int n){
        nVertices=n;
        // depends on how graph is initialized
        //if initialized from 1 then allocate memory of size (nVertices + 1) else nVertices
        adjlist=new AdjList[nVertices + 1];
        parent=new int[nVertices + 1];
        distance=new int[nVertices + 1];
    }

    void setNedges(int n){
        nEdges=n;
        // for saving edges
        e=new edgeExtra[nEdges +1];
        eLength=0;
        //debug
    }

    void addEdge(int u,int v,float w){
        //This condition will vary with initialization
        if(u<1 || v<1 || u>nVertices || v>nVertices) {
            pf("vertex out of bound\n");
            return;
        }

        adjlist[u].insert(edge(v,w));
        if(!directed) adjlist[v].insert(edge(u,w));
        //for(int i=0;i<eLength;i++) if( e[i].u==u && e[i].v==v && e[i].weight==w ) return;

        e[eLength].u=u;
        e[eLength].v=v;
        e[eLength].weight=w;
        eLength++;
    }

    void removeEdge(int u,int v,float w){
        if(eLength==0){
            pf("No edge to remove\n");
            return;
        }

        //This condition will vary with initialization
        if(u<1 || v<1 || u>nVertices || v>nVertices) {
            pf("Vertex out of bound\n");
            return;
        }

        adjlist[u].removeItem(edge(v,w));
        if(!directed)adjlist[v].removeItem(edge(u,w));

        for(int i=0;i<eLength;i++){
            if( e[i].u==u && e[i].v==v && e[i].weight==w ){
                e[i]=e[eLength-1];
                eLength--;
                break;
            }
        }
    }

    bool areAdjacent(int u,int v){
        for(int i=0;i< adjlist[u].getLength();i++){
            edge t1=adjlist[u].getItemAt(i);
            if(t1.v==v) {
                return true;
                break;
            }
        }
        return false;
    }

    bool hasCommonAdjacent(int u,int v){
        if(u<1 || v<1 || u>length || v>length){
            pf("vertex out of bound\n");
            return false;
        }

        int len=adjlist[u].getLength(),check;
        edge tmp;

        for(int i=0;i<len;i++){
            tmp=adjlist[u].getItemAt(i);
            check = adjlist[v].searchItem(tmp);
            if(check!=-1) return true;
        }
        return false;
    }

    bool relaxation(int u,int v,float w,bool f=true){

        if(u<1 || v<1 || u>nVertices || v>nVertices) {
            pf("Vertex out of bound\n");
            return false;
        }

        float cost=w;
        //cout<< "uvw:"<< u<< " "<<v<< " "<<cost<< " "<<distance[u]<< " " << distance[v] <<endl;

        /*float cost=mh.getWeight(u,v);
        if(cost==-0.1) {
            pf("Edge doesn't exist");
            return false;
        }*/


        if(distance[u]==INF && distance[v]==INF) return false;
        else if(distance[u] + cost< distance[v]){
                //cout<< "uv:"<< u<< " "<<v<< " "<<cost<< " "<<distance[u]<< " " << distance[v] <<endl;
            if(f)parent[v]=u;
            if(f)distance[v]=distance[u] + cost;
            return true;
        }
        return false;
    }
/*5 5
1 2 10
2 3 9
3 4 4
4 2 -4
3 5 5*/
    void bell_man_Ford_Algorithm(int source=1){

        //for(int i=0;i<eLength;i++) mh.enqueue( e[i].u, e[i].v, e[i].weight );
        /*printEdges();
        char t;
        sf("%c",&t);*/

        for(int i=0;i<=nVertices;i++){
            parent[i]=-1;
            distance[i]=INF;
        }

        distance[source]=0;
        parent[source]=0;

        //debug
        for(int i=1;i<nVertices;i++)
        {
            for(int j=0;j<nEdges;j++){
                relaxation( e[j].u, e[j].v ,e[j].weight);
            }
        }

        //debug
        //printEdges();

        bool flag=true;
        for(int j=0;j<nEdges ;j++){
            cout<< distance[e[j].u]<< " "<<e[j].weight<< " "<<distance[e[j].v]<<endl;
            if(relaxation( e[j].u, e[j].v, e[j].weight,false )){
                flag=false;
                pf("Negative cycle exist\n");
                break;
            }
        }

        if(flag) pf("No negative cycle exist\n");
        for(int i=1;i<=nVertices;i++){
            if(parent[i]!=-1 && parent[i]!=0)
                pf("v: %d, v.d: %d, p: %d\n",i,distance[i],parent[i]);
            else if( parent[i]==0)
                pf("v: %d, v.d: %d, p: nill\n",i,distance[i]);

        }
        //mh.printHeap();
    }

    void printEdges(){
        for(int i=0;i<nEdges;i++){
            pf("%d %d %f\n",e[i].u,e[i].v,e[i].weight );
        }
    }

};

int main(){
    
    //freopen("in.txt","r",stdin);
    
    int u,v;
    float w;
    int vertices,edges;

    Graph g(true);

    sf("%d %d",&vertices,&edges);

    g.setNvertices(vertices);
    g.setNedges(edges);

    for(int i=0;i<edges;i++){
        sf("%d %d %f",&u,&v,&w);
        g.addEdge(u,v,w);
    }

    int source;
    printf("Source?: \n");
    sf("%d",&source);

    g.bell_man_Ford_Algorithm(source);

    return 0;

}
