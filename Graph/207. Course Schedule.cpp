/*
* 1. 如何解决这个问题？
*   先建立AOV网，选择邻接表法建图，之后进行拓扑排序。
* 2. 理清拓扑排序思路：
* (1) 从AOV网中选择一个没有前驱的顶点，输出它
* (2) 从AOV网中删除该顶点，并且删除以该顶点为尾的全部有向边
* (3) 重复上述两步，直到剩余的网中不再存在没有前驱的顶点为止
* 3. 如何建图？使用什么数据结构？要注意什么？
*   数据结构：根据题目给出条件，我们可以使用vector<unordered_set<int>> graph建图
*   注意：由于要进行拓扑排序，我们建树时要记录每个节点的入度vector<int> indegrees(numCourses, 0)
*   建图：for pre in prerequisites:	// 题目给出：<0,1> : to take course 0 you have to first take course 1 即 1 -> 0
*			graph[pre.second].insert(pre.first)  // 插入节点
*			indegrees[pre.first]++;				// 弧尾入度++
* 4. 拓扑排序
*   此问题不需要进行边的删除，我们只需要减少节点的入度就可以了
*/ 

/*  Approach One：拓扑排序不使用栈或者队列	
*	属于BFS：访问一个顶点，然后访问该顶点的其余邻接点	*/
bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<unordered_set<int>> graph(numCourses);			// 模拟邻接表
    vector<int> indegrees(numCourses, 0);		// 用于记录节点入度数
    createGraph(graph, numCourses, prerequisites, indegrees);
    // 拓扑排序
    for(int i = 0; i < numCourses; ++i){
    	// 找到入度为0的节点
    	int zeroIn = 0;
    	for(; zeroIn < numCourses; ++zeroIn)
    		if(!indegrees[zeroIn]) break;
    	// 没有入度为0的节点了
    	if(zeroIn == numCourses) return false;

    	// 删除顶点和与顶点相连的边，此问题不需要删除边
    	// 如 1 -> 2 , 1 -> 3 ：1的入度变为-1，而2、3的入度均要减1 
    	indegrees[zeroIn] = -1;
    	for(int next : graph[zeroIn])
    		indegrees[next]--;
    }
    return true;
}

void createGraph(vector<unordered_set<int>> &graph, int numCourses
	, vector<pair<int, int>>& prerequisites, vector<int>& indegrees){
	for(pair<int, int>& pre : prerequisites){
		graph[pre.second].insert(pre.first);	// 插入节点
		indegrees[pre.first]++; 	// 弧尾入度++			
	}
}


/*  Approach Two：拓扑排序使用栈
*	BFS：访问一个顶点，然后访问该顶点的其余邻接点	*/
bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<unordered_set<int>> graph(numCourses);			// 模拟邻接表
    vector<int> indegrees(numCourses, 0);		// 用于记录节点入度数
    createGraph(graph, numCourses, prerequisites, indegrees);
    // 拓扑排序
    stack<int> st;
    int counter = 0;
    // 入度为0的顶点入栈
    for(int i = 0; i < numCourses; ++i)
    	if(!indegrees[i]) st.push(i);
    while(!st.empty()){
    	int zeroIn = st.top();	// 弹出一个入度为0的顶点
    	st.pop();
    	++counter;	// 入度为0的节点数
    	/* plan[k++] = zeroIn; // 可以记录课程的安排次序*/
    	// 访问zeroIn的所有边
    	for(int next : graph[zeroIn]){
    		if(!(--indegrees[next]))	//  弧头入度数减1变成了入度为0的顶点 (如1 -> 2，2即弧头)
    			st.push(next);
    	}
    }
    if(counter == numCourses)	// 拓扑排序之后所有节点都可以入度为0，除非是非连通图
    	return true;
    else
    	return false;
}

/*  Approach Three：查看是否存在环
*	Depth First Search：
*    1. 访问一个顶点w，然后访问该顶点的未被访问的下一个邻接点v
*    2. 访问v的下一个未被访问的邻接点x，依次类推，直到所有和w相通的点都被访问过
*    3. 若此时仍有顶点未被访问，则从中选一个顶点做为始点，重复1.2
*    注意：我们要使用一个visited[0..n-1]，标识顶点是否被访问
*	那么在有向图的DFS中，我们如何判断是否存在环呢？
*	 很简单，我们可以记录我们访问的路径path
*    假设我们正在访问V，准备访问V的下一个邻接点W，但是W在我们访问的路径上，则存在环
*/
bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {			
    // 模拟邻接表
    vector<unordered_set<int>> graph = createGraph(numCourses, prerequisites);
    vector<bool> visited(numCourses, false);    // 被访问过的节点
    vector<bool> path(numCourses, false);  // 当前的访问路径
    for(int i = 0; i < numCourses; ++i)
        if(!visited[i] && dfsCycle(graph, i, visited, path))	// 顶点未被访问过，但存在环
            return false;
    return true;
}

bool dfsCycle(vector<unordered_set<int>>& graph, int v, vector<bool>& visited, vector<bool>& path){
    if(visited[v]) return false;    // 被访问过的节点不需要再次被访问
    path[v] = visited[v] = true;	// 设置顶点为被访问过，加入当前的访问路径
    for(int next : graph[v]){
        // 如果该顶点的邻接点在当前访问路径上，说明存在环，否则查看邻接点
        if(path[next] || dfsCycle(graph, next, visited, path))
            return true;
    }
    path[v] = false;    // 递归回来时，我们需要将该顶点取出访问路径
    return false;
}

vector<unordered_set<int>> createGraph(int numCourses, vector<pair<int, int>>& prerequisites){
    vector<unordered_set<int>> graph(numCourses);
    for(pair<int, int>& pre : prerequisites)
        graph[pre.second].insert(pre.first);    // 插入节点
    return graph;
}