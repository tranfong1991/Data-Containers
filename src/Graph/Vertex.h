#pragma once
#include <stdio.h>
#include <vector>
#include "Edge.h"

using namespace std;

class EmptyOutEdge{};
class EmptyInEdge{};

template<typename T> class Edge;

template<typename T>
class Vertex
{
protected:
	typedef Edge<T> Edge;
private:
	T id;
	bool isVisited;
	vector<Edge*> outEdge;
	vector<Edge*> inEdge;

	template<typename T, typename Hash>
	friend class Graph;
public:
	Vertex(T i) : id(i), isVisited(false) {}

	T getID() const { return id; }
	bool visited() const { return isVisited; }
	const vector<Edge*>& getOutEdge() const throw(EmptyOutEdge){
		if (outEdge.empty()) throw EmptyOutEdge();
		return outEdge;
	}
	const vector<Edge*>& getInEdge() const throw(EmptyInEdge){
		if (inEdge.empty()) throw EmptyInEdge();
		return inEdge;
	}
	bool operator==(const Vertex& v){ return id == v.id && isVisited == v.isVisited; }
};
