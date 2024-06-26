#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <iostream>
#include <fstream>
#include <utility>
#include <functional>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <unordered_map>
#include <limits>
#include <stdexcept>



template <typename T>
class Graph {
 private:
  std::vector<std::unordered_map<int, T> > adjList {};
  int numVertices {};

 public:
  // empty graph with N vertices
  explicit Graph(int N);

  // construct graph from edge list in filename
  explicit Graph(const std::string& filename);

  // add an edge directed from vertex i to vertex j with given weight
  void addEdge(int i, int j, T weight);

  // removes edge from vertex i to vertex j
  void removeEdge(int i, int j);

  // is there an edge from vertex i to vertex j?
  bool isEdge(int i, int j) const;

  // return weight of edge from i to j
  // will throw an exception if there is no edge from i to j
  T getEdgeWeight(int i, int j) const;

  // returns number of vertices in the graph
  int size() const;

  // alias a const iterator to our adjacency list type to iterator
  using iterator = 
  typename std::vector<std::unordered_map<int, T> >::const_iterator;

  // cbegin returns const iterator pointing to first element of adjList
  iterator begin() const {
    return adjList.cbegin();
  }

  iterator end() const {
    return adjList.cend();
  }

  // return iterator to a particular vertex
  iterator neighbours(int a) const {
    return adjList.begin() + a;
  }
};

template <typename T>
Graph<T>::Graph(int N) : adjList(N), numVertices {N} {}

template <typename T>
Graph<T>::Graph(const std::string& inputFile) {
  std::ifstream infile {inputFile};
  if (!infile) {
    std::cerr << inputFile << " could not be opened\n";
    return;
  }
  // first line has number of vertices
  infile >> numVertices;
  adjList.resize(numVertices);
  int i {};
  int j {};
  double weight {};
  // assume each remaining line is of form
  // origin dest weight
  while (infile >> i >> j >> weight) {
    addEdge(i, j, static_cast<T>(weight));
  }
}

template <typename T>
int Graph<T>::size() const {
  return numVertices;
}

template <typename T>
void Graph<T>::addEdge(int i, int j, T weight) {
  if (i < 0 or i >= numVertices or j < 0 or j >= numVertices) {
    throw std::out_of_range("invalid vertex number");
  }
  adjList[i].insert({j, weight});
}

template <typename T>
void Graph<T>::removeEdge(int i, int j) {
  // check if i and j are valid
  if (i >= 0 && i < numVertices && j >= 0 && j < numVertices) {
    adjList[i].erase(j);
  }
}

template <typename T>
bool Graph<T>::isEdge(int i, int j) const {
  if (i >= 0 && i < numVertices && j >= 0 && j < numVertices) {
    return adjList.at(i).contains(j);
  }
  return false;
}

template <typename T>
T Graph<T>::getEdgeWeight(int i, int j) const {
  return adjList.at(i).at(j);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Graph<T>& G) {
  for (int i = 0; i < G.size(); ++i) {
    out << i << ':';
    for (const auto& [neighbour, weight] : *(G.neighbours(i))) {
      out << " (" << i << ", " << neighbour << ")[" << weight << ']';
    }
    out << '\n';
  }
  return out;
}

template <typename T>
bool isSubgraph(const Graph<T>& H, const Graph<T>& G) {
    int h_size = H.size();
    int g_size = G.size();
    if(h_size <= 0 || h_size > g_size ) return false;

    bool is_sub=true;
//    int h_edges=0;
    for(int i=0;i<h_size;i++){
        for(const auto &[neighbour, weight]: *(H.neighbours(i))){
            if(G.isEdge(i,neighbour)){
                if(G.getEdgeWeight(i, neighbour) != weight){
                    is_sub= false;
                }
            }else {
                is_sub = false;
            }
        }
    }

  return is_sub;
}
template <typename T>
void dfs(const Graph<T>& G, int cur, std::vector<int>& visited_vertices){
    visited_vertices[cur]++;
    if(visited_vertices[cur]>1){
        return;
    }

    for(const auto &[neighbour, weight]: *(G.neighbours(cur))){
        dfs(G,neighbour,visited_vertices);
    }


}


template <typename T>
bool isTreePlusIsolated(const Graph<T>& G, int root) {
    std::vector<int> visited_vertices(G.size(),0);
    dfs(G,root,visited_vertices);
    bool result = true;
    for(int i=0;i<visited_vertices.size();i++){
//        printf("i = %d, visited_vertices[i] is %d \n",i, visited_vertices[i]);
        if(visited_vertices[i]==0){
            // unreachable
            bool isolated=true;
            for(const auto &[neighbour, weight]: *(G.neighbours(i))){
                    isolated=false;
            }
            if(!isolated){
                result=false;
            }
        }else if (visited_vertices[i]>1){
            result=false; // undirected cycle
        }
    }

  return result;
}

template <typename T>
std::vector<T> pathLengthsFromRoot(const Graph<T>& tree, int root) {
  std::vector<T> bestDistanceTo(tree.size());
   std::queue<int> queue;
    std::vector<T> visited(tree.size(),0);
    queue.push(root);
    while (!queue.empty()){

        int first = queue.front();
        queue.pop();
//    remove(queue.)
        for(const auto &[neighbour, weight]: *(tree.neighbours(first))){
            int cur_len = bestDistanceTo[first] + weight;
            if(visited[neighbour]==0){
                // first visit
                bestDistanceTo[neighbour] = cur_len;
                visited[neighbour]++;
            }else{
                if(bestDistanceTo[neighbour] > cur_len){
                    bestDistanceTo[neighbour] = cur_len;
                }
            }
            queue.push(neighbour);
        }
    }

  return bestDistanceTo;
}



template <typename T>
bool allEdgesRelaxed(const std::vector<T>& bestDistanceTo, const Graph<T>& G, 
                      int source) {
    int g_size = G.size();

    if(bestDistanceTo.at(source) !=0) return false;
    bool result=true;
//    int h_edges=0;
    for(int k=0;k<bestDistanceTo.size();k++){
        int dest =k;
        if(dest==source) continue;
        for(int i=0;i<g_size;i++){
            for(const auto &[neighbour, weight]: *(G.neighbours(i))){
                if(G.isEdge(i,neighbour)){
                    if(neighbour == dest){
                      if(bestDistanceTo.at(dest) > bestDistanceTo.at(i) + G.getEdgeWeight(i,dest)){
//                          bestDistanceTo.at(dest) =  bestDistanceTo.at(i) + G.getEdgeWeight(i,dest);
                          result = false;
                      }
                    }
                }
            }
        }
    }
  return result;
}

#endif      // GRAPH_HPP_
