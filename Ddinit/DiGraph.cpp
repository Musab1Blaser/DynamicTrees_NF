
#ifndef DIGRAPH_H
#define DIGRAPH_H

#include "Graph.h"

namespace grafalgo {

class Digraph : public Graph {
public:
    Digraph(int=1, int=1);
    ~Digraph();

    void resize(int, int);
    void resize(int numv) { resize(numv, numv); }
    void expand(int, int);
    void expand(int numv) { resize(numv, max(numv, m())); }

    vertex tail(edge) const;
    vertex head(edge) const;

    virtual edge firstAt(vertex) const;
    virtual edge nextAt(vertex, edge) const;
    edge firstIn(vertex) const;
    edge nextIn(vertex, edge) const;
    edge firstOut(vertex) const;
    edge nextOut(vertex, edge) const;

    edge joinWith(vertex, vertex, edge);
    bool remove(edge);

    void rgraph(int, int);
    void rdag(int, int);

    virtual string& toDotString(string&) const;

protected:
    void makeSpace(int, int);
    void freeSpace();
    string& adjList2string(vertex, string&) const;
    bool readAdjList(istream&);

private:
    edge *fi;
    Digraph& operator=(const Digraph&);
};

inline edge Digraph::tail(edge e) const { return left(e); }

inline edge Digraph::head(edge e) const { return right(e); }

inline edge Digraph::firstAt(vertex v) const {
    assert(validVertex(v));
    return (fi[v] != 0 ? fi[v]/2 : firstOut(v));
}

inline edge Digraph::nextAt(vertex v, edge e) const {
    assert(validVertex(v) && validEdge(e));
    if (v != evec[e].l && v != evec[e].r) return 0;
    int ee = (v == evec[e].l ? 2*e : 2*e+1);
    int ff = adjLists->suc(ee);
    return (ff == fi[v] ? firstOut(v) : (ff == fe[v] ? 0 : ff/2));
}

inline edge Digraph::firstIn(vertex v) const {
    assert(validVertex(v));
    return fi[v]/2;
}

inline edge Digraph::nextIn(vertex v, edge e) const {
    assert(validVertex(v) && validEdge(e));
    if (v != evec[e].l && v != evec[e].r) return 0;
    int ee = (v == evec[e].l ? 2*e : 2*e+1);
    int ff = adjLists->suc(ee);
    return (fi[v] == ff ? 0 : ff/2);
}

inline edge Digraph::firstOut(vertex v) const {
    assert(validVertex(v));
    return fe[v]/2;
}

inline edge Digraph::nextOut(vertex v, edge e) const {
    assert(validVertex(v) && validEdge(e));
    if (v != evec[e].l && v != evec[e].r) return 0;
    int ee = (v == evec[e].l ? 2*e : 2*e+1);
    int ff = adjLists->suc(ee);
    return (fe[v] == ff ? 0 : ff/2);
}

} // ends namespace

#endif
