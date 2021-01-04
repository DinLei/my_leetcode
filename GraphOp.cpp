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


/*207. 课程表*/
/*
你这个学期必须选修 numCourse 门课程，记为 0 到 numCourse-1 。
在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们：[0,1]
给定课程总量以及它们的先决条件，请你判断是否可能完成所有课程的学习？
*/
// 方法一：邻接表bfs
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
// 方法二：邻接表dfs
class Solution {
private:
    vector<vector<int>> edges;
    vector<int> visited;
    bool valid = true;

public:
    void dfs(int u) {
        visited[u] = 1;
        for (int v: edges[u]) {
            if (visited[v] == 0) {
                dfs(v);
                if (!valid) {
                    return;
                }
            }
            else if (visited[v] == 1) {
                valid = false;
                return;
            }
        }
        visited[u] = 2;
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for (const auto& info: prerequisites) {
            edges[info[1]].push_back(info[0]);
        }
        for (int i = 0; i < numCourses && valid; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        return valid;
    }
};


/*990. 等式方程的可满足性*/
class Solution {
public:
  vector<int> parent;

  // 找父节点
  int findSet( int x ) {
    int xp = parent[x];
    if( xp == -1 )
      return x;
    return findSet( xp );
  }
  // 建立关系
  void unionSet( int x, int y ) {
    int xp = findSet( x );
    int yp = findSet( y );
    if( xp != yp ) 
      parent[xp] = yp;
  }
  
  bool equationsPossible(vector<string>& equations) {
    int eSize = equations.size(); 

    parent.resize( 26, -1 );

    for( int i = 0; i < eSize; i ++ ) {
      if( equations[i][1] == '=' ) {
        char left = equations[i][0];
        char right = equations[i][3];
        unionSet( left-'a', right-'a' );
      }
    }

    for( int i = 0; i < eSize; i ++ ) {
      if( equations[i][1] == '!' ) {
        char left = equations[i][0];
        char right = equations[i][3];

        int lp = findSet( left-'a' );
        int rp = findSet( right-'a' );
        if( lp == rp )
          return false;
      }
    }  
    return true;
  }
};