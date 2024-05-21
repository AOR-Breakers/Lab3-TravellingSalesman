#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Graph {
private:
  std::vector<std::vector<int>> StoredGraph;
  int VerticeCount;
  int EdgeCount;
  int VeticeNumberingOffset;
  bool IsDirected = false;

public:
  Graph() = delete;
  explicit Graph(int VerticeCount, int EdgeCount, int Offset = 0)
      : StoredGraph(VerticeCount, std::vector<int>(VerticeCount, 0)),
        VerticeCount(VerticeCount), EdgeCount(EdgeCount),
        VeticeNumberingOffset(Offset){};

  explicit Graph(int VerticeCount, int EdgeCount, int Offset, bool IsDirected)
      : Graph(VerticeCount, EdgeCount, Offset) {
    this->IsDirected = IsDirected;
  }

  int verticeCount() const { return VerticeCount; }

  void addEdge(int V, int U, int Weight) {
    StoredGraph[V][U] = Weight;

    if (!IsDirected) {
      StoredGraph[U][V] = Weight;
    }
  }

  int getEdgeWeight(int V, int U) const { return StoredGraph[V][U]; }

  static Graph fromFile(std::string Filepath) {
    std::ifstream InputFile(Filepath);

    int VerticeCount, EdgeCount, Offset;
    InputFile >> VerticeCount >> EdgeCount >> Offset;

    Graph NewGraph(VerticeCount, EdgeCount, Offset);
    for (int Index = 0; Index < EdgeCount; ++Index) {
      int V, U;
      double Weight;
      InputFile >> V >> U >> Weight;
      NewGraph.addEdge(V, U, Weight);
    }
    return NewGraph;
  }

  int fitnessFunction(const std::vector<int> &Path) const {
    int Value = 0;
    for (size_t Index = 1; Index < Path.size(); ++Index) {
      Value += (getEdgeWeight(Path[Index - 1], Path[Index]));
    }

    Value += getEdgeWeight(Path[Path.size() - 1], Path[1]);
    return Value;
  }

  std::vector<int> convertPath(const std::vector<int> &Path) {
    std::vector<int> NewPath;
    for (auto &Vertice : Path) {
      NewPath.push_back(Vertice - VeticeNumberingOffset);
    }
    return NewPath;
  }
};

template <typename T> void printVector(const std::vector<T> &V) {
  for (auto &Value : V) {
    std::cout << Value << ' ';
  }
  std::cout << '\n';
};
