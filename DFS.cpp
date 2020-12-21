// DFS
/*200. 岛屿数量*/
/*
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。
*/
class Solution {
public:
  int numIslands(vector<vector<char>>& grid) {
    int nrow = grid.size();
    if(nrow == 0)
      return 0;
    int ncol = grid[0].size();

    int ans = 0;
    for(int i = 0; i < nrow; i ++) {
      for(int j = 0; j < ncol; j ++) {
        if(grid[i][j] == '1') {
          ans ++;
          dfs(grid, i, j, nrow, ncol);
        }
      }
    }
    return ans;
  }

  void dfs(vector<vector<char>>& grid, int i, int j, int nrow, int ncol) {
    if(grid[i][j] != '1')
      return ;
    grid[i][j] = 'x';
    if(i > 0)
      dfs(grid, i-1, j, nrow, ncol);
    if(i < nrow-1)
      dfs(grid, i+1, j, nrow, ncol);
    if(j > 0)
      dfs(grid, i, j-1, nrow, ncol);
    if(j < ncol-1)
      dfs(grid, i, j+1, nrow, ncol);
  }
};

/*695. 岛屿的最大面积*/
class Solution {
private:
  int di[4] = {1, 0, -1, 0};
  int dj[4] = {0, -1, 0, 1};
public:
  int maxAreaOfIsland(vector<vector<int>>& grid) {
    int nrow = grid.size();
    if(nrow == 0)
      return 0;
    int ncol = grid[0].size();

    int ans = 0;
    for(int i = 0; i < nrow; i ++) {
      for(int j = 0; j < ncol; j ++) {
        ans = max(ans, dfs(grid, i, j, nrow, ncol));
      }
    }
    return ans;
  }

  int dfs(vector<vector<int>>& grid, int i, int j, int nrow, int ncol) {
    if(i < 0 || i == nrow || j < 0 || j == ncol || grid[i][j] != 1)
      return 0;
    grid[i][j] = 0;
    int area = 1;
    for(int x = 0; x < 4; x ++) {
      area += dfs(grid, i + di[x], j + dj[x], nrow, ncol);
    }
    return area;
  }
};