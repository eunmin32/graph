#include "graphl.h"
#include <sstream>
#include <stack> 
#include <vector>
using namespace std;

GraphL::GraphL() : graphNodes{ nullptr }, size{0}{
}

GraphL::~GraphL(){
}

void GraphL::buildGraph(ifstream& infile){
	if (infile.is_open()) {
		string line;
		getline(infile, line);
		if (line != "") {
			stringstream S;
			S.str(line);
			S >> size;
			graphNodes = new GraphNode * [size];
			for (int i = 1; i <= size; i++) {
				getline(infile, line);
				initNodes(i, line);
			}
			int a, b;
			getline(infile, line);
			while (line != "0 0") {
				stringstream S;
				S.str(line);
				S >> a;
				S >> b;
				setNextNode(a, b);
				getline(infile, line);
			}
		}
	}
}

void GraphL::depthFirstSearch(){
	cout << endl << "Depth-first ordering" << ": " ;
	depthFirstSearchHelper(1);
	
}

void GraphL::depthFirstSearchHelper(int initial) {	
	EdgeNode* iiii = graphNodes[initial]->edgeHead;
	graphNodes[initial]->visited = true;
	cout << initial << " ";
	while (iiii != nullptr) {
		if (graphNodes[iiii->adjGraphNode]->visited == false) {
			depthFirstSearchHelper(iiii->adjGraphNode);
		}
		iiii = iiii->nextEdge;
	}
	
}

void GraphL::displayGraph(){
	cout << endl << "Graph: " << endl;
	for (int i = 1; i <= size; i++) {
		cout << "Node " << i << "       " << *(graphNodes[i]->data) << endl;
		if (graphNodes[i]->edgeHead != nullptr) {
			EdgeNode* curr = graphNodes[i]->edgeHead;
			while (curr != nullptr) {
				cout << "   " << "edge " << i << " " << curr->adjGraphNode << endl;
				curr = curr->nextEdge;
			}
		}

	}
}

void GraphL::initNodes(int nodePlace, string name) {
	graphNodes[nodePlace] = new GraphNode();
	graphNodes[nodePlace]->data = new NodeData(name);
}

void GraphL::setNextNode(int nodePlace, int adjNode){
	if (graphNodes[nodePlace]->edgeHead == nullptr) {
		graphNodes[nodePlace]->edgeHead = new EdgeNode();
		graphNodes[nodePlace]->edgeHead->adjGraphNode = adjNode;
	} else {
		EdgeNode* curr = graphNodes[nodePlace]->edgeHead;
		if (adjNode < curr->adjGraphNode) {
			graphNodes[nodePlace]->edgeHead = new EdgeNode();
			graphNodes[nodePlace]->edgeHead->adjGraphNode = adjNode;
			graphNodes[nodePlace]->edgeHead->nextEdge = curr;
			return;
		}
		while (curr->nextEdge != nullptr) {
			if (adjNode < curr->nextEdge->adjGraphNode) {
				EdgeNode* next = curr->nextEdge;
				curr->nextEdge = new EdgeNode();
				curr->nextEdge->adjGraphNode = adjNode;
				curr->nextEdge->nextEdge = next;
			}
			curr = curr->nextEdge;
		}
		curr->nextEdge = new EdgeNode();
		curr->nextEdge->adjGraphNode = adjNode;
	}
}
