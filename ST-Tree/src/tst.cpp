#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <cstdlib>

using namespace boost;

int main()
{
    typedef property<edge_weight_t, int> EdgeWeightProperty;
    typedef adjacency_list<vecS, vecS, bidirectionalS, no_property, EdgeWeightProperty> Graph;
    enum {A, B, C, D, E, N};
    const int num_vertices = N;
    const char* name = "ABCDEF";

    typedef std::pair<int, int> Edge;
    Edge edge_array[] =
    { Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
      Edge(C,E), Edge(B,D), Edge(D,E), Edge(B, A) };
    const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);
    int weights[] = {3, 4, 1, 2, 1, 8, 9, 10};
    Graph g(edge_array, edge_array + num_edges, weights, num_vertices);
    // boost::property_map< Graph, vertex_index_t >::type vertex_id = get(vertex_index, g);
    property_map<Graph, vertex_index_t>::type vertex_id = get(vertex_index, g);
    property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, g);

    // for (int i = 0; i < num_edges; ++i)
    // {
    //     // weightmap[edge_array[i]] = weight[i];
    //     add_edge(edge_array[i].first, edge_array[i].second, weights[i], g);
    // }

    std::ofstream dot_file("graph.dot");
    write_graphviz(dot_file, g, make_label_writer(name), make_label_writer(weightmap), default_writer());
    system("dot -Tpng graph.dot -o graph.png");
    system("xdg-open graph.png");

    int x;

    if (std::cin >> x)
    {
        Edge edge_array2[] =
        { Edge(1,3), Edge(1,4), Edge(3,1), Edge(4,3),
        Edge(3,5), Edge(2,4), Edge(4,5), Edge(2, 1) };

        Graph g(edge_array2, edge_array2 + sizeof(edge_array2)/ sizeof(Edge), num_vertices);
        // remove_vertex(A, g);


        std::ofstream dot_file("graph2.dot");
        write_graphviz(dot_file, g);
        system("dot -Tpng graph2.dot -o graph2.png");
        system("xdg-open graph2.png");

    }


    return 0;
}