#include "graphm.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <istream>
#include <algorithm>
using namespace std;

GraphM::GraphM() {
	size = 0;
	for (int i = 0; i < MAXNODES; i++) {
		for (int j = 0; j < MAXNODES; j++) {
			C[i][j] = 9999;
		}
		data[i] = new NodeData();
	}
}

GraphM::~GraphM() {
	for (int i = 0; i < MAXNODES; i++) {
		delete data[i];
	}
}

void GraphM::buildGraph(ifstream& infile){ 
	string line;
	if (infile.is_open()) {
		getline(infile, line);
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
			int minDis = 9999;
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

// 
string GraphM::traversePath(int from, int to) {
	string path; 
	if (from == to) {
		return to_string(from) + " ";
	}	
	path += traversePath(from, T[from][to].path) + to_string(to) + " ";
	return path;
}

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
				if (T[fromNode][toNode].dist == 9999) {
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

void GraphM::display(int from, int to) {
	if (to <= size && from <= size) {
		cout << endl << from << "       ";
		cout << to << "       ";

		if (T[from][to].dist == 9999) {
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

bool GraphM::insertEdge(int nodeA, int nodeB, int distance){
	if (C[nodeA][nodeB] != 9999) {
		cout << "Edge Already Existed";
		return false;
	}
	C[nodeA][nodeB] = distance;
	return true;
}

bool GraphM::removeEdge(int nodeA, int nodeB){
	if (C[nodeA][nodeB] == 9999) {
		cout << "Didn't have edge";
		return false;
	}
	C[nodeA][nodeB] = 9999;
	return true;
}

void GraphM::printOnlyGraph(){
	cout << "COST TABLE :             ";
	for (int i = 1; i <= size; i++) {\
		cout << i << "  ";
	}
	for (int i = 1; i <= size; i++) {
		cout << endl << *data[i] << ": " << endl;
		cout << "                         ";
		for (int j = 1; j <= size; j++) {
			if (C[i][j] >= 9999)
				cout << "∞  ";
			else 
				cout << C[i][j] << " ";
			if (C[i][j] < 10)
				cout << " ";
		}
		cout << endl;
	}

}
