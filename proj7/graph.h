// graph.h <Starter Code>
// Haoji Ni
//
// Basic graph class using adjacency matrix representation.  Currently
// limited to a graph with at most 100 vertices.
//
// University of Illinois at Chicago
// CS 251: Spring 2022
// Project #7 - Openstreet Maps
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>

using namespace std;

template<typename VertexT, typename WeightT>
class graph {
 private:
    typedef pair<VertexT, WeightT> vwPair;
    map <VertexT, vector<vwPair>> adjList;

 public:
  // constructor:
  // Constructs an empty graph
  // you expect the graph to contain.
  graph() {
    adjList.clear();
  }
  // NumVertices
  // Returns the # of vertices currently in the graph.
  int NumVertices() const {
    return adjList.size();
  }

  // NumEdges
  // Returns the # of edges currently in the graph.
  int NumEdges() const {
    int count = 0;
    // iterate through the adjacency list, add the size together
    for (auto it = adjList.begin(); it != adjList.end(); ++it) {
      count += it->second.size();
    }
    return count;
  }

  // addVertex
  // Adds the vertex v to the graph if there's room, and if so
  // returns true.  If the graph is full, or the vertex already
  // exists in the graph, then false is returned.
  bool addVertex(VertexT v) {
      // if the vertex is already exist, return false
    if (adjList.find(v) != adjList.end()) {
      return false;
    }
    adjList[v];
    return true;
  }

  // addEdge
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist, returns false.
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  bool addEdge(VertexT from, VertexT to, WeightT weight) {
    // we need to search the Vertices and find the position
    // of each vertex; this will denote the row and col to
    // access in the adjacency matrix:

    // find the first vertex in the adjacency list
    auto from_v = adjList.find(from);
    if (from_v == adjList.end()) {
      return false;
    }
    // find the second vertex in the adjacency list
    auto to_v = adjList.find(to);
    if (to_v == adjList.end()) {
      return false;
    }
    // if the edge already exists, overwrite the weight
    for (auto it = from_v->second.begin(); it != from_v->second.end(); ++it) {
      if (it->first == to) {
        it->second = weight;
        return true;
      }
    }
    // if the edge doesn't exist, add it
    from_v->second.push_back(vwPair(to, weight));
    return true;
  }

  // getWeight
  // Returns the weight associated with a given edge.  If
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not
  // exist, the weight parameter is unchanged and false is
  // returned.
  bool getWeight(VertexT from, VertexT to, WeightT& weight) const {
      // we need to search the Vertices and find the position
      // of each vertex; this will denote the row and col to
      // access in the adjacency matrix:

      // find the first vertex in the adjacency list
      auto from_v = adjList.find(from);
      if (from_v == adjList.end()) {
          return false;
      }
      // find the second vertex in the adjacency list
      auto to_v = adjList.find(to);
      if (to_v == adjList.end()) {
          return false;
      }
      // the vertices exist, but does the edge exist?
      for (auto it = from_v->second.begin(); it != from_v->second.end(); ++it) {
          if (it->first == to) {
              weight = it->second;
              return true;
          }
      }
      return false;
  }

  // neighbors
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  set<VertexT> neighbors(VertexT v) const {
    // Create a set S to store neighbors
    set<VertexT>  S;
    // if not found return empty set
    auto from_v = adjList.find(v);
    if (from_v == adjList.end()) {
      return S;
    }
    // otherwise, iterate through the adjacency list, and add into set
    for (auto it = from_v->second.begin(); it != from_v->second.end(); ++it) {
        S.insert(it->first);
    }
    return S;
  }

  // getVertices
  // Returns a vector containing all the vertices currently in
  // the graph.
  vector<VertexT> getVertices() const {
    // Create a vector V to store vertices
    vector<VertexT> V;
    // iterate through the adjacency list, and add into vector
    for (auto it = adjList.begin(); it != adjList.end(); ++it) {
      V.push_back(it->first);
    }
    return V;
  }

  // dump
  // Dumps the internal state of the graph for debugging purposes.
  void dump(ostream& output) const {
    // dump function for self testing
    output << "Graph dump:" << endl;
    output << "  Vertices: " << endl;
    // iterate through the adjacency list, output it
    for (auto it = adjList.begin(); it != adjList.end(); ++it) {
      output << "    " << it->first << endl;
    }
    output << "  Edges: " << endl;
    // iterate through the adjacency list, output it
    for (auto it = adjList.begin(); it != adjList.end(); ++it) {
      output << "    " << it->first << ": ";
      for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
        output << "(" << it2->first << ", " << it2->second << ") ";
      }
      output << endl;
    }
  }
};
