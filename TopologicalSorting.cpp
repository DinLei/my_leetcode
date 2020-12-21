#include<iostream>
#include<list>
#include<queue>

using namespace std;

class Graph {
  int V;
  list<int>* adj; //  临接列表
  int* indegree;  //  记录每个顶点的入度
  queue<int> q;   //  维护一个入度为0的顶点集合

public:
  Graph(int V);
  ~Graph();

  void addEdge(int v, int w); //  添加边
  bool topoSort(vector<int>&);            //  拓扑排序
};


Graph::Graph(int V) {
  this->V = V;
  adj = new list<int>[V];
  indegree = new int[V];
  for(int i=0; i<V; i++)
    indegree[i] = 0;
}

Graph::~Graph() {
  delete[] adj;
  delete[] indegree;
}

void Graph::addEdge(int v, int w) {
  adj[v].push_back(w);
  ++ indegree[w];
};

bool Graph::topoSort(vector<int>& res) {
  // 将所有入度为0的节点找出来
  for(int i=0; i<V; i++) 
    if( indegree[i] == 0 )
      q.push(i);
  // 拓扑遍历
  int count = 0;
  while ( !q.empty() ) {
    // 取出一个顶点
    int v = q.front();
    // cout << v << " ";
    res.push_back(v);
    q.pop();
    ++ count;
    // 将所有v指向的顶点的入度减1，并将入度为0的顶点压入队列
    list<int>::iterator beg = adj[v].begin();
    for( ; beg != adj[v].end(); ++beg ) {
      if( !(--indegree[*beg]) )
        q.push(*beg); // 若入度为0，则入栈
    } 
  }
  
  if( count < V ) { //  非DAG，没有输出全部顶点，有向图中有回路
    res.clear();
    return false;
  } else
    return true;
};

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
      vector<int> res;
      Graph g(numCourses);   // 创建图
      vector<vector<int>>::iterator edgePtr = prerequisites.begin();
      for( ; edgePtr != prerequisites.end(); ++edgePtr ) {
        vector<int> oneEdge = *edgePtr;
        g.addEdge(oneEdge[1], oneEdge[0]);
      }
      g.topoSort(res);
      
      return res;
    }
};


/*
int main()
{
    Graph g(2);   // 创建图
    g.addEdge(1, 0);
    // g.addEdge(5, 0);
    // g.addEdge(4, 0);
    // g.addEdge(4, 1);
    // g.addEdge(2, 3);
    // g.addEdge(3, 1);

    vector<int> res;
    g.topoSort(res);
    return 0;
}
*/

/*207. 课程表*/
/*
你这个学期必须选修 numCourse 门课程，记为 0 到 numCourse-1 。
在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们：[0,1]
给定课程总量以及它们的先决条件，请你判断是否可能完成所有课程的学习？
*/
class Solution {
public:
  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    list<int> adj[numCourses];
    vector<int> indegree(numCourses);
    for( vector<int>& edge: prerequisites ) {
      adj[ edge[1] ].push_back( edge[0] );
      indegree[ edge[0] ] ++;
    }
    queue<int> que;
    for( int i = 0; i < numCourses; i ++ ) {
      if( indegree[i] == 0 )
        que.push(i);
    }
    int count = 0;
    while( !que.empty() ) {
      int n = que.front(); que.pop();
      count ++;
      list<int>::iterator it = adj[n].begin();
      for( ; it != adj[n].end(); it ++ ) {
        if( !(--indegree[*it]) )
          que.push(*it);
      }
    }
    return count == numCourses;
  }
};