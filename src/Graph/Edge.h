#pragma once
#include "Vertex.h"

template<typename T>
class Edge
{
protected:
	typedef Vertex<T> Vertex;
private:
	int weight;
	Vertex* sVert;
	Vertex* eVert;

	template<typename T, typename Hash>
	friend class Graph;
public:
	Edge(Vertex* s = NULL, Vertex* e = NULL, int weit = 0)
		: sVert(s), eVert(e), weight(weit){}

	int getWeight() const { return weight; }
	Vertex* getSVert() const { return sVert; }
	Vertex* getEVert() const { return eVert; }
	bool operator==(const Edge& e){ return sVert == e.sVert && eVert == e.eVert && weight == e.weight; }
};