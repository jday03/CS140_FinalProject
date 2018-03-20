
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

    while ( ! frontier.isEmpty() )
{
    depthCounter++;
    cilk::reducer<BagMonoid> list;

frontier.size = 4;
for (int i=0; i< frontier.size(); i++){
    std::vector<node*> adjacents = frontier.getItem(i).getAdjacents();
    for (int adjCount = 0; adjCount < adjacents.size(); ++ adjCount) {
        if (adjacents[adjCount]->visited == false) {
            adjacents[adjCount].depth = depthCounter;
            succbag.insertNode((adjacents[adjCount]));
        }
    }

}
frontier = succbag.getValue();

}

    manageDepthCounter(depthCounter,graph,depthMap);
}




void manageDepthCounter(int depthCount, std::vector<node> graph,std::map<int, std::vector<int>> depthMap){
    for(int count = 0; count <= depthCount; ++count){
        std::vector<int> values;
        std::pair <int,std::vector<int>> newDepth (count,values);
        depthMap.insert (newDepth);
    }

    for(int count = 0; count < graph.size(); ++count){
        node temp = graph[count];
        if(temp.depth >= 0){
            auto iter = depthMap.find(temp.depth);
            iter->second->insert(iter->end(),temp.number);
        }
    }

}



void printDepthCounter(depthMap){
    auto iter = depthMap.find(0);
    while (iter != depthMap.end()){
        auto vec = iter->second;
        std::cout<< "Nodes at depth: ";
        for(int count = 0; count < vec.size();++count){
            std::cout<< " " << vec[count] << " ,";

        }
        std::cout << std::endl;
    }
}