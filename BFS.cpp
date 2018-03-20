
// vector of size num vertexes
void insertEdge(std::vector<node> graph, int to, int from ){
    node* first = graph[to];
    node* second = graph[from];

    first->adjacencies.insert(first->adjacencies.end(), from);
    second->adjacencies.insert(second->adjacencies.end(), to);
}

void BFS(std::vector<node> graph, node root)
{
    root.visited = true;
    Bag frontier(root);
    std::map<int, std::vector<int>> depthMap;
    int depthCounter = -1;
    createNewDepth(depthCounter,depthMap);

    while ( ! frontier.isEmpty() )
{
    depthCounter++;
    cilk::reducer<BagMonoid> list;

frontier.size = 4;
for (int i=0; i< frontier.size(); i++){
    std::vector<node*> adjacents = frontier.getItem(i).getAdjacents();
    for (int adjCount = 0; adjCount < adjacents.size(); ++ adjCount) {
        if (adjacents[adjCount]->visited == false) {
            succbag.insertNode((adjacents[adjCount]));


        }
    }

}
frontier = succbag.getValue();

}
}


void createNewDepth(int num, std::map<int, std::vector<int>> depthMap){
    std::vector<int> values;
    std::pair <int,std::vector<int>> newDepth (depth,values);
    depthMap.insert (newDepth);


}