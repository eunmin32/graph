/*
------------------------------------------------ graphm.h -------------------------------------------------------
Eunmin Lee CSS343 A
Creation Date: 2/24/2020
Date of Last Modification: 2/26/2020
------------------------------------------------------------------------------------------------------------------
Purpose - Data structure Graph using adjacency matrix
------------------------------------------------------------------------------------------------------------------
Implementation of graph stores nodedata
Also contains Dijkstra's algorithm (find shortest path)
------------------------------------------------------------------------------------------------------------------
*/
#include "nodedata.h"
#include <fstream>

using namespace std;

class GraphM {
	const static int MAXNODES = 30; //Maximum Node capacity of the graph
	const static int MAXDIS = 999999; //Maximum Distance Possible in edge

	public:
		GraphM();		//constructor
		~GraphM(); 		//deconstructor
		void buildGraph(ifstream& infile);		//build the graph based on data on the data in textfile (fill up C[][] and data[], and set size) 
		void findShortestPath();		//Do Dijkstra's algorthim and store the data in TableType T[][]
		void displayAll();              // display shortest distance, path to cout
		void display(int from, int to);			//Display all the adjacent nodes of all nodes
		void printOnlyGraph();				//Print cost table of the graph


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
		bool insertEdge(int nodeA, int nodeB, int distance); //insert an edge into graph between two given nodes
		bool removeEdge(int nodeA, int nodeB); //remove an edge 
		string traversePath(int from, int to);  //return Dijkstra's path

};