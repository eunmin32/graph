#include "nodedata.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

class GraphM {
	const static int MAXNODES = 30;

	public:
		GraphM();
		~GraphM();
		void buildGraph(ifstream& infile);
		void findShortestPath();
		string traversePath(int from, int to);
		void displayAll();              // display shortest distance, path to cout
		void display(int from, int to);
		bool insertEdge(int nodeA, int nodeB, int distance); //insert an edge into graph between two given nodes
		bool removeEdge(int nodeA, int nodeB);
		void printOnlyGraph();


	private:
		struct TableType {
			bool visited = false;          // whether node has been visited
			int dist;              // shortest distance from source known so far
			int path;              // previous node in path of min dist
		};
		NodeData* data[MAXNODES];      // data for graph nodes 1D
		int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix 2D
		int size;          // number of nodes in the graph
		TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path 2D

};