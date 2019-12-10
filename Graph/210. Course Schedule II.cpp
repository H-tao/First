class Solution {
public:
    /*
    * 1. 理清拓扑排序思路：
    * (1) 从AOV网中选择一个没有前驱的顶点，输出它
    * (2) 从AOV网中删除该顶点，并且删除以该顶点为尾的全部有向边
    * (3) 重复上述两步，直到剩余的网中不再存在没有前驱的顶点为止
    * 2. 如何解决这个问题？
    *   先建立AOV网，选择邻接表法建图，之后进行拓扑排序。
    * 3. 如何建图？使用什么数据结构？要注意什么？
    *   数据结构：根据题目给出条件，我们可以使用vector<unordered_set<int>> graph建图
    *   注意：由于要进行拓扑排序，我们建树时要记录每个节点的入度vector<int> indegrees(numCourses, 0)
    *   建图：for pre in prerequisites:	// <0,1> 1 -> 0 : to take course 0 you have to first take course 1
    *			graph[pre.second].insert(pre.first)  // 插入节点
    *			indegrees[pre.first]++;				// 弧尾入度++
    * 4. 拓扑排序
    */ 

    /*  BFS：访问一个顶点，然后访问该顶点的其余邻接点	*/
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<unordered_set<int>> graph(numCourses);			// 模拟邻接表
        vector<int> indegrees(numCourses, 0);		// 用于记录节点入度数
        createGraph(graph, numCourses, prerequisites, indegrees);
        // 拓扑排序
        vector<int> plan(numCourses, 0);
        stack<int> st;
        int counter = 0;   // 记录入度为0的节点数
        // 入度为0的顶点入栈
        for(int i = 0; i < numCourses; ++i)
            if(!indegrees[i]) st.push(i);
        while(!st.empty()){
            int zeroIn = st.top();	// 弹出一个入度为0的顶点
            st.pop();
            plan[counter++] = zeroIn; // 入度为0的节点加入课程的安排次序*/
            // 访问zeroIn的所有边
            for(int next : graph[zeroIn]){
                if(!(--indegrees[next]))	//  弧头入度数减1变成了入度为0的顶点 (如1 -> 2，2即弧头)
                    st.push(next);
            }
        }
        if(counter == numCourses)	// 拓扑排序之后所有节点都可以入度为0，除非是非连通图
            return plan;
        else
            return vector<int>();
    }

    void createGraph(vector<unordered_set<int>> &graph, int numCourses
        , vector<pair<int, int>>& prerequisites, vector<int>& indegrees){
        for(pair<int, int>& pre : prerequisites){
            graph[pre.second].insert(pre.first);    // 插入节点
            indegrees[pre.first]++; // 弧尾入度++
        }
    }
};