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
#include "graphm.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

//------------------- constructors/destructor  -------------------------------
GraphM::GraphM(){
	size = 0;
	for (int i = 0; i < MAXNODES; i++) {
		for (int j = 0; j < MAXNODES; j++) {
			C[i][j] = MAXDIS;
		}
		data[i] = new NodeData();
	}
}

GraphM::~GraphM() {
	for (int i = 0; i < MAXNODES; i++) {
		delete data[i];
	}
}

//---------------------------- buildGraph -------------------------------------
// Build the graph based on data on the data in textfile
// Preconditions: ifstream must be created in main function
// Postconditions: Set value at data[]* and size, and fill up C[][] 
void GraphM::buildGraph(ifstream& infile){ 
	string line;
	if (infile.is_open()) {
		getline(infile, line);
		if (line != "") {
			stringstream S;
			S.str(line);
			S >> size;
			for (int i = 1; i <= size; i++) {
				(*data[i]).setData(infile);
				insertEdge(i, i, 0);
			}

			int a, b, c;
			while (line != "0 0 0") {
				getline(infile, line);
				stringstream S;
				S.str(line);
				S >> a;
				S >> b;
				S >> c;
				insertEdge(a, b, c);
			}
		}
	}
}

//---------------------------- findShortestPath -------------------------------------
// //Do Dijkstra's algorthim 
// Preconditions: Node
// Postconditions: Store the shortes path in TableType T[][]
void GraphM::findShortestPath(){
	int beginningV = 1;
	while (beginningV <= size) {
		int currV = beginningV;
		//initalize table
		for (int vertex = 1; vertex <= size; vertex++) {
			T[beginningV][vertex].dist = C[beginningV][vertex];
			T[beginningV][vertex].path = beginningV;
		}
		T[beginningV][currV].visited = true;
		T[beginningV][currV].path = 0;

		for (int vertex = 1; vertex < size; vertex++) { //repeat size - 1 times

			//selecting next vertex (finding shortest path);
			int minDis = MAXDIS;
			int currVCandidate = currV;
			for (int i = 1; i <= size; i++) {
				if (!T[beginningV][i].visited) {
					if (T[beginningV][i].dist < minDis) {
						minDis = T[beginningV][i].dist;
						currVCandidate = i;
					}
				}
			}
			currV = currVCandidate;
			T[beginningV][currV].visited = true;
			//changing shortest path
			for (int i = 1; i <= size; i++) {
				if (!T[beginningV][i].visited) {
					int sumDis = C[currV][i] + T[beginningV][currV].dist;
					if (sumDis < T[beginningV][i].dist) {
						T[beginningV][i].path = currV;
						T[beginningV][i].dist = sumDis;
					}

				}
			}
		}
		beginningV++;
	}
	
}

//---------------------------- displayAll -------------------------------------
// Display shortest distance of all Nodes, path to cout
// Preconditions: Node
// Postconditions: Node
void GraphM::displayAll(){
	cout << endl;
	cout << "Description               From node  To node  Dijkstra's  Path    " << endl;
	for (int fromNode = 1; fromNode <= size; fromNode++) {
		cout << *data[fromNode] << endl;
		for (int toNode = 1; toNode <= size; toNode++) {
			if (toNode != fromNode) {
				cout << "                               ";
				cout << fromNode << "       "; 
				cout << toNode << "       ";
				if (T[fromNode][toNode].dist == MAXDIS) {
					cout << "---";
				} else {
					cout << T[fromNode][toNode].dist << "          ";
					cout << traversePath(fromNode, toNode);
				}
				cout << endl;
			}
		}

	}
}

//---------------------------- display -------------------------------------
// Display all the adjacent nodes of all nodes
// Preconditions: Node
// Postconditions: Node
void GraphM::display(int from, int to) {
	if (to <= size && from <= size) {
		cout << endl << from << "       ";
		cout << to << "       ";

		if (T[from][to].dist == MAXDIS) {
			cout << "---" << endl;
		}
		else {
			cout << T[from][to].dist << "          ";
			string path = traversePath(from, to);
			stringstream S;
			S.str(path);
			int v;
			cout << path << endl;
			while (S >> v) {
				cout << *data[v] << endl;
			}
		}
	}
}


//---------------------------- printOnlyGraph -------------------------------------
// Print cost table of the graph
// Preconditions: Node
// Postconditions: Node
void GraphM::printOnlyGraph(){
	cout << "COST TABLE :             ";
	for (int i = 1; i <= size; i++) {\
		cout << i << "  ";
	}
	for (int i = 1; i <= size; i++) {
		cout << endl << *data[i] << ": " << endl;
		cout << "                         ";
		for (int j = 1; j <= size; j++) {
			if (C[i][j] >= MAXDIS)
				cout << "∞  ";
			else 
				cout << C[i][j] << " ";
			if (C[i][j] < 10)
				cout << " ";
		}
		cout << endl;
	}

}

//---------------------------- insertEdge -------------------------------------
// Insert an edge into graph between two given nodes
// Preconditions: Assuming highest possible distance is MAXDIS
// Postconditions: Node
bool GraphM::insertEdge(int nodeA, int nodeB, int distance) {
	if (C[nodeA][nodeB] != MAXDIS) {
		cout << "Edge Already Existed";
		return false;
	}
	C[nodeA][nodeB] = distance;
	return true;
}

//---------------------------- removeEdge -------------------------------------
// Remove an edge from the graph
// Preconditions: Assuming highest possible distance is MAXDIS
// Postconditions: Node
bool GraphM::removeEdge(int nodeA, int nodeB) {
	if (C[nodeA][nodeB] == MAXDIS) {
		cout << "Didn't have edge";
		return false;
	}
	C[nodeA][nodeB] = MAXDIS;
	return true;
}

//---------------------------- traversePath -------------------------------------
// Return string of Dijkstra's path
// Preconditions: None
// Postconditions: None
string GraphM::traversePath(int from, int to) {
	string path;
	if (from == to) {
		return to_string(from) + " ";
	}
	path += traversePath(from, T[from][to].path) + to_string(to) + " ";
	return path;
}

