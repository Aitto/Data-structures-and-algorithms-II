#include<stdio.h>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<stack>
#include<cstring>

#define pf printf
#define sf scanf
#define pi 3.141592653589793116
#define INF 99999
#define maxInt 99999999
#define maxNEG -99999999.0
#define debug cout<<"Hello here!"<<endl;
#define readFile freopen("in.txt","r",stdin);

#define NULL_VALUE -999999
#define INFINITY 999999
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0
#define WHITE 1
#define GREY 2
#define BLACK 3


using namespace std;

class HeapItem
{
public:
	int data; //actual data that is stored
	float key; //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
	HeapItem * A; //stores heap items, e.g., nodes
	int heapLength;
	int * map;

	MinHeap() //constructor
	{
		A = new HeapItem[MAX_HEAP_SIZE];
		map = new int[MAX_HEAP_SIZE];
		heapLength=0;
	}

	~MinHeap() //destructor
	{
		if(map) delete [] map;
		if(A) delete [] A;
		map = 0; //set to NULL after deletion
		A = 0; //set to NULL after deletion
	}

    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
	void initialize(int v[], int n)
	{
		heapLength = n;
		for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
		{
			A[i+1].data = v[i];
			A[i+1].key = MAXREAL;
			map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
		}
	}

	//this function inserts a new (data,key) pair in the heap
    //call to buheapify is required
    void insertItem(int data, int key)
    {
        heapLength++;

        A[heapLength].data=data;
        A[heapLength].key=key;

        map[data]=heapLength;
        //Restoring heap property
        buHeapify(heapLength);

    }

    //this function removes (and returns) the node which contains the minimum key value
	HeapItem removeMin()
	{
        HeapItem hp;
	    if(heapLength==0){
            cout<<"Heap is empty"<<endl;

            //Returning dummy object

            hp.data=-1;
            hp.key=-1;

            return hp;
	    }

	    hp=A[1];
	    A[1]=A[heapLength];
	    heapLength--;

	    //restoring heap property
	    heapify(1);
	    return hp;

	}


    //The function updates the key value of an existing data
    //stored in the heap
	//Note that updates can result in an increase or decrease of key value
	//Call to heapify or buheapify is required
	void updateKey(int data, float key)
	{
	    int index=map[data];
	    if(index==0){
            cout<< "No such heapitem found! \n";
            return;
	    }

		//Write your codes here.
        if( A[index].key >key ){
            A[index].key=key;
            buHeapify(index);
        }else{
            A[index].key=key;
            heapify(index);
        }
	}


    //This function returns the key value of a data stored in heap
	float getKey(int data)
	{
		int i = map[data];
		return A[i].key;
	}

    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling
    //this function will restore heap property
	void heapify(int i)
	{
		int l,r,smallest;
		while(1)
		{
			l=2*i;      //left child index
			r=2*i+1;    //right child index
			smallest=i;

			if(l>heapLength && r>heapLength)
				break; //nothing to do, we are at bottom
			else if(r>heapLength)
				smallest = l;
			else if(l>heapLength)
				smallest = r;
			else if( A[l].key < A[r].key )
				smallest = l;
			else
				smallest = r;

			if(A[i].key <= A[smallest].key)
				break;	//we are done heapifying
            else
			{
                //swap nodes with smallest child, adjust map array accordingly
				HeapItem t;
				t=A[i];
				A[i]=A[smallest];
				map[A[i].data]=i;
				A[smallest]=t;
				map[A[smallest].data]=smallest;
				i=smallest;
			}

		}

		//cout<< "heapify complete.....\n";
		//printHeap();
	}

    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling
    //this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then
    //calling this function restores heap property
	void buHeapify(int i)
	{
        int parent=i/2;
        while(parent){
            if( A[parent].key > A[i].key ){
                HeapItem hp=A[parent];
                A[parent]=A[i];
                A[i]=hp;
                map[A[parent].data]=parent;
                map[A[i].data]=i;
                i=parent;
                parent=parent/2;
            }else break;

        }

        //cout << "buHeapify complete!....\n";
        //printHeap();

	}

    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1;i<=heapLength;i++)
        {
            printf("(%d,%.2f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }

	bool Empty()
	{
		if(heapLength==0)return true;
		else return false;
	}
};


/** Edge and weight*/
class edge{
public:
    int dest;
    float weight;

    edge(){
        dest=0;
        weight=0;
    }

    edge(int v,float w){
        dest=v;
        weight=w;
    }
};

struct edgeExtra{

    int u;
    int v;
    float w;

    edgeExtra(){
        u=0;v=0;w=0.0;
    }

};

//****************Dynamic ArrayList class based************************
class ArrayList
{
	edge * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(edge item) ;
    void insertItem(edge item) ;
	void removeItem(edge item) ;
	void removeItemAt(int item);
	edge getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 4 ;
	listMaxSize = listInitSize ;
	list = new edge[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(edge newEdge)
{
	edge * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new edge[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newEdge ; //store new item
	length++ ;
}

int ArrayList::searchItem(edge item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i].dest == item.dest && list[i].weight == item.weight ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(edge item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


edge ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) {
        cout<< "No such edge found....\n";
        edge temp(0,0);
        return temp;
	}
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("Vertex: %d, Edge: %d", list[i].dest,list[i].weight);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
    edgeExtra *e;
    int eLength;
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	MinHeap hp;
	int *parent;
	bool *visit;
	int *distance;
	int **cost;
	int **w;
	int **p;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir=false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v,int w);
	void removeEdge(int u, int v,int w);
    void printGraph();
    void primsAlgo();

    void setnEdges(int n){
        eLength=0;
        //nEdges=n;

        e=new edgeExtra[n];
        cost=new int*[n + 1];
        for(int i=0;i<=n;i++) cost[i]=new int[n +1];
        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)
            cost[i][j]=INFINITY;
    }



    bool relaxation(int u,int v,bool f=true){
        if( u<1 || v<1 || u>nVertices || v>nVertices) return false;

        if((distance[u]==INFINITY && distance[v]==INFINITY) || cost[u][v]==INFINITY ) return false;
        else{
            if(distance[u] + cost[u][v] < distance[v] ){
                if(f)parent[v]=u;
                if(f)distance[v]=distance[u] + cost[u][v];
                return true;
            }
        }

        return false;
    }

    void bell_man_Ford_Algorithm(int source){

        for(int i=0;i<=nVertices;i++)
        {
            parent[i]=-1;
            distance[i]=INFINITY;
        }

        parent[source]=0;
        distance[source]=0;

        for(int i=1;i<nVertices;i++){
            for(int j=0;j<=nEdges;j++){
                relaxation( e[j].u, e[j].v );
            }
        }

        bool flag=true;
        for(int i=0;i<nEdges;i++){
            if(relaxation( e[i].u, e[i].v,false )){
                pf("Negative cycle exist\n");
                flag=false;
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

        cout<<endl;

    }

    void Floyad_warshall(){

        //Initializing

        for(int i=0;i<=nVertices;i++)
            for(int j=0;j<=nVertices;j++)
            {
                if(i==j) w[i][j]=0;
                else
                    w[i][j]=INF;
                p[i][j]=INF;
            }

        for(int i=0;i<nEdges;i++){
            if( e[i].u >nVertices or e[i].u<1 or e[i].v >nVertices or e[i].v<1 ) continue;
            w[e[i].u][e[i].v]= e[i].w;
            p[e[i].u][e[i].v]= e[i].u;
            //parent[e[i].v]= e[i].u;
        }

        cout<< "Before: "<<endl;
        for(int i=1;i<=nVertices;i++){
            for(int j=1;j<=nVertices;j++){
                if(w[i][j]==INF) pf("INF ");
                else pf("%3d ",w[i][j]);
            }
            pf("\n");
        }

        for(int k=1;k<=nVertices;k++)
        {
            for(int i=1;i<=nVertices;i++)
            {
                for(int j=1;j<=nVertices;j++)
                {
                    if(w[i][k]==INF or w[k][j]==INF) continue;
                    if(w[i][j] > w[i][k] + w[k][j] )
                    {
                        w[i][j]=w[i][k] +w[k][j];
                        p[i][j]=p[k][j];
                    }
                }
            }
        }

        cout<< "After: "<<endl;
        for(int i=1;i<=nVertices;i++){
            for(int j=1;j<=nVertices;j++){
                if(w[i][j]==INF) pf("INF ");
                else pf("%3d ",w[i][j]);
            }
            pf("\n");
        }
        cout<< "Parents: "<<endl;
        for(int i=1;i<=nVertices;i++){
            for(int j=1;j<=nVertices;j++){
                if(p[i][j]==INF) pf("INF ");
                else pf("%3d ",p[i][j]);
            }
            pf("\n");
        }



    }

};


Graph::Graph(bool dir)
{
    w=0;
    cost=0;
    eLength=0;
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	parent=0;
	visit=0;
	directed =dir;
	distance=0;//set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	if(adjList!=0) delete[] adjList ; //delete previous list
	if(parent!=0) delete[] parent; //delete previous record
	if(visit!=0) delete[] visit;
    if(distance!=0) delete[] distance;


	adjList = new ArrayList[nVertices+1] ;
	parent = new int[nVertices+1] ;
	visit=new bool[nVertices+1] ;
	distance=new int[nVertices+1];
	w=new int*[nVertices +1];
	p=new int*[nVertices +1];
	for(int i=0;i<=nVertices;i++) {
        w[i]=new int[nVertices + 1];
        p[i]=new int[nVertices + 1];
	}

	cout<< "Initializing vertices at 1\n" ;
}

void Graph::addEdge(int u, int v,int w)
{
    if(u<=0 || v<=0 || u>nVertices || v>nVertices) {
        cout<< "Vertices out of range\n";
        return;
    } //vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(edge(v,w)) ;
	cost[u][v]=w;
	e[eLength].u=u;
	e[eLength].v=v;
	e[eLength].w=w;
	eLength++;

	//if(!directed) adjList[v].insertItem(edge(u,w)) ;
}

void Graph::removeEdge(int u, int v,int w)
{
    if(u<=0 || u>nVertices || v<=0 || v>nVertices){
        cout<< "Out of bound...\n";
    }
    //write this function
    adjList->removeItem(edge(u,w));
    adjList->removeItem(edge(v,w));
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" Vertex: %d, Edge: %d", adjList[i].getItem(j).dest,adjList[i].getItem(j).weight);
        }
        printf("\n");
    }
}

void Graph::primsAlgo()
{
    //setting key to infinite;
    for(int i=1;i<=nVertices;i++)
    {
        hp.insertItem(i,MAXREAL);
        parent[i]=-1;
        visit[i]=false;
        distance[i]=MAXREAL;
    }

    //hp.printHeap();
    parent[1]=0;
    distance[1]=0;
    hp.updateKey(1,0);

    HeapItem x;
    edge e;

    while(!hp.Empty())
    {
        x=hp.removeMin();

        if(visit[x.data]==true) continue;

        for(int i=0;i<adjList[x.data].getLength();i++ )
        {
            e=adjList[x.data].getItem(i);
            if(e.weight < distance[e.dest] && !visit[e.dest])
            {
                parent[e.dest] = x.data;
                distance[e.dest]=e.weight;
                hp.updateKey(e.dest,e.weight);
            }
        }
        visit[x.data]=true;
    }

    int sum=0;
    for(int i=2;i<=nVertices;i++)
    {
        printf("%d %d\n",i,parent[i]);
        sum+=distance[i];
    }

    printf("%d\n",sum);

}


Graph::~Graph()
{
    if(adjList!=0) delete[] adjList ; //delete previous list
	if(parent!=0) delete[] parent; //delete previous record
	if(visit!=0) delete[] visit;
    if(distance!=0) delete[] distance;
}



int main(){

    freopen("test.txt", "r",stdin);

    int n,m;
    int u,v,w;

    Graph g;

    scanf("%d %d",&n,&m);

    g.setnVertices(n);
    g.setnEdges(m);

    for(int i=0;i<m;i++)
    {
        scanf("%d %d %d",&u,&v,&w);
        g.addEdge(u,v,w);
    }

    g.Floyad_warshall();


    return 0;

}

/**
*/
