void BFS(Graph *G, Vertex root)
{
Bag<Vertex> frontier(root);
while ( ! frontier.isEmpty() )
{
cilk::hyperobject< Bag<Vertex> > succbag();

cilk_for (int i=0; i< frontier.size(); i++)
{
for( Vertex v in frontier[i].adjacency() )
{
if( ! v.unvisited() )
succbag.insert(v);
}
}
frontier = succbag.getValue();
}
}