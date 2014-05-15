#pragma once
#include "Edge.h"
#include "Vertex.h"
#include "BinaryHeapPQ.h"
#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <regex>

class VertexNotFound{};
class EdgeNotFound{};
class NoWeightFound{};
class NoPathFound{};
class EmptyGraph{};

template<typename T, typename Hash>
class Graph
{
protected:
	typedef Vertex<T> Vertex;
	typedef Edge<T> Edge;
	typedef Item<Vertex*, int> Item;
	typedef Locator<Item> Locator;
	typedef HashTable<Locator, Vertex*, Hash> LocHash;
private:
	vector<Vertex*> vertList;
	vector<Edge*> edgeList;
	LocHash loc;

	void reset();		//Change all vertices to unvisited
	int isExist(Vertex* v);
	int weight(Vertex* source, Vertex* destin) throw(NoWeightFound);
	void DFS(Vertex* v);
	void BFS(Vertex* v);

	struct PQComp		//Provide a way to compare 2 elements
	{
		int operator() (const Item& e1, const Item& e2)
		{
			return e1.getKey() - e2.getKey();
		}
	};		
public:
	Graph(){}
	Graph(string fileName);
	~Graph();

	void addVertex(Vertex* v);
	void addEdge(Edge* e);
	void DFS() throw(EmptyGraph) {
		if (vertList.empty()) throw EmptyGraph();
		DFS(vertList[0]);
	}
	void BFS() throw(EmptyGraph){
		if (vertList.empty()) throw EmptyGraph();
		BFS(vertList[0]);
	}
	void printGraph(Vertex* v);
	void shortestPath(const T& source, const T& destin) throw(NoPathFound);
};

template<typename T, typename Hash>
Graph<T, Hash>::Graph(string fileName)
{
	ifstream ifs(fileName);
	string line;
	regex pat("(\\w{3}) (\\w{3}) (\\d*)");
	while (getline(ifs, line))
	{
		smatch matches;
		if (regex_match(line, matches, pat)){
			Vertex* source = new Vertex(T(matches[1], matches[1]));
			Vertex* destin = new Vertex(T(matches[2], matches[2]));
			addEdge(new Edge(source, destin, stoi(matches[3])));
		}
	}
	ifs.close();
}

template<typename T, typename Hash>
Graph<T, Hash>::~Graph()
{
	for (int i = 0; i < vertList.size(); ++i)
		delete vertList[i];
	for (int i = 0; i < edgeList.size(); ++i)
		delete edgeList[i];
	vertList.clear();
	edgeList.clear();
}

template<typename T, typename Hash>
int Graph<T, Hash>::isExist(Vertex* v)
{
	for (int i = 0; i < vertList.size(); ++i)
	if (vertList[i]->id == v->id)
		return i;	//returns its index in vertList
	return -1;	//Not exist
}

template<typename T, typename Hash>
void Graph<T, Hash>::reset()
{
	for (int i = 0; i < vertList.size(); ++i)
		vertList[i]->isVisited = false;
}

template<typename T, typename Hash>
int Graph<T, Hash>::weight(Vertex* source, Vertex* destin) throw(NoWeightFound)
{
	int sIndex = isExist(source);
	int eIndex = isExist(destin);
	if (sIndex != -1 && eIndex != -1){
		for (int i = 0; i < edgeList.size(); ++i)
		if (edgeList[i]->sVert == source && edgeList[i]->eVert == destin)
			return edgeList[i]->weight;
		throw NoWeightFound();
	}
	else throw NoWeightFound();
}

template<typename T, typename Hash>
void Graph<T, Hash>::DFS(Vertex* v)
{
	static Stack<Vertex*> vertStack;
	if (v->isVisited == false){
		cout << v->id << " ";
		vertStack.push(v);
		v->isVisited = true;
	}
	for (int i = 0; i < v->outEdge.size(); ++i)
	if (v->outEdge[i]->eVert->isVisited == false)
		DFS(v->outEdge[i]->eVert);
	if (!vertStack.isEmpty()){
		vertStack.pop();
		if (vertStack.isEmpty()) reset();
	}
}

template<typename T, typename Hash>
void Graph<T, Hash>::BFS(Vertex* v)
{
	static Queue<Vertex*> vertQueue;
	if (v->isVisited == false){
		v->isVisited = true;
		cout << v->id << " ";
	}
	for (int i = 0; i < v->outEdge.size(); ++i)
	if (v->outEdge[i]->eVert->isVisited == false){
		v->outEdge[i]->eVert->isVisited = true;
		cout << v->outEdge[i]->eVert->id << " ";
		vertQueue.enqueue(v->outEdge[i]->eVert);
	}
	if (!vertQueue.isEmpty())
		BFS(vertQueue.dequeue());
	v->isVisited = false;
}

template<typename T, typename Hash>
void Graph<T, Hash>::addVertex(Vertex* v)
{
	vertList.push_back(v);
}

template<typename T, typename Hash>
void Graph<T, Hash>::addEdge(Edge* e)
{
	int sIndex = isExist(e->sVert);
	int eIndex = isExist(e->eVert);
	if (sIndex == -1) vertList.push_back(e->sVert);
	else{
		delete e->sVert;
		e->sVert = vertList[sIndex];
	}
	if (eIndex == -1) vertList.push_back(e->eVert);
	else{
		delete e->eVert;
		e->eVert = vertList[eIndex];
	}
	e->sVert->outEdge.push_back(e);
	e->eVert->inEdge.push_back(e);
	edgeList.push_back(e);
}

template<typename T, typename Hash>
void Graph<T, Hash>::printGraph(Vertex* v)
{
	int index = isExist(v);
	if (index == -1) throw VertexNotFound();
	cout << v->id << ": ";
	for (int i = 0; i < vertList[index]->getOutEdge().size(); ++i)
		cout << vertList[index]->outEdge[i]->eVert->id << " ";
}

template<typename T, typename Hash>
void Graph<T, Hash>::shortestPath(const T& source, const T& destin) throw(NoPathFound)
{
	BinaryHeapPQ<Vertex*,int, PQComp> pq;
	for (int i = 0; i < vertList.size(); ++i){
		if (vertList[i]->id == source)
			pq.insert(0, vertList[i], &loc.emptySlot(vertList[i]));
		else pq.insert(1000000, vertList[i], &loc.emptySlot(vertList[i]));
	}
	vector<Item> visitedVert;
	while (true){
		Item temp = pq.removeMin();
		visitedVert.push_back(temp);
		if (temp.getElem()->id == destin) break;
		int size = temp.getElem()->outEdge.size();
		for (int i = 0; i < size; ++i){
			Vertex* endVert = temp.getElem()->outEdge[i]->eVert;
			int newDist = temp.getKey() + weight(temp.getElem(), endVert);
			if (newDist < loc[endVert].getItem()->getKey()){
				pq.decreaseKey(&loc[endVert], newDist);
				loc[endVert].getItem()->setParentIndex(visitedVert.size() - 1);
			}
		}
	}
	if (visitedVert[visitedVert.size() - 1].getKey() == 10000) throw NoPathFound();
	vector<Vertex*> path;
	for (int i = visitedVert.size() - 1; i >= 0;){
		path.push_back(visitedVert[i].getElem());
		i = visitedVert[i].getParentIndex();
	}
	for (int i = path.size() - 1; i >= 0; --i){
		if (i != 0) cout << "(" << path[i]->id << ")" << "--" << weight(path[i], path[i - 1]) << "-->";
		else cout << "(" << path[i]->id << ")\n";
	}
	cout << "Total Weight: " << visitedVert[visitedVert.size() - 1].getKey();
}