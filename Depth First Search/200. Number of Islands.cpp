class Solution {
public:
    /*
        访问所有的点：
        1.遇到'0'(water)我们就返回
        2.遇到'1'(land),我们就把这个点设置成'0'(water),然后继续搜索其上下左右的点

        Custom testcase:
        [["1","1","1"],["0","1","0"],["1","1","1"]] 让我Wrong Answer了一次(只访问了下边和右边)
    */
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty()) return 0;
        int rows = grid.size(), cols = grid[0].size();

        int lands = 0;  // land总数
        // 遍历每一个点，遇到新的land时，++lands
        for(int r = 0; r < rows; ++r){
            for(int c = 0; c < cols; ++c){
                if(grid[r][c] == '1'){
                    searchLand(r, c, grid);
                    ++lands;
                }
            }
        }
        return lands;
    }

private:
    void searchLand(int row, int col, vector<vector<char>>& grid){
        if(row >= grid.size() || col >= grid[0].size() || row < 0 || col < 0) return;   // 边界
        if(grid[row][col] == '0') return;   // 遇到了water

        grid[row][col] = '0';  // 将该节点设置为'0'
        searchLand(row - 1, col, grid);    // 访问上边的点
        searchLand(row + 1, col, grid);    // 访问下边的点
        searchLand(row, col - 1, grid);    // 访问左边的点
        searchLand(row, col + 1, grid);    // 访问右边的点
    }
};