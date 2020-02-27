/*
------------------------------------------------ graphl.h -------------------------------------------------------
Eunmin Lee CSS343 A
Creation Date: 2/24/2020
Date of Last Modification: 2/26/2020
------------------------------------------------------------------------------------------------------------------
Purpose - Data structure Graph using linked list.
------------------------------------------------------------------------------------------------------------------
Implementation of graph stores nodedata
Also contains depth first search: the node intialize first takes priority for depth first search
------------------------------------------------------------------------------------------------------------------
*/
#include "graphl.h"
#include <sstream>
#include <stack> 
#include <vector>
using namespace std;

//------------------- constructors/destructor  -------------------------------
GraphL::GraphL() : graphNodes{ nullptr }, size{ 0 }{}

GraphL::~GraphL(){
	for (int i = 1; i <= size; i++) {
		edgeNodeDelete(graphNodes[i]->edgeHead);
		delete graphNodes[i]->data;
		delete graphNodes[i];
	}
	delete[] graphNodes;
}

//---------------------------- buildGraph -------------------------------------
// Build the graph based on data on the data in textfile
// Preconditions: ifstream must be created in main function
// Postconditions:  Connect dynamically allocated node to graphNode**
void GraphL::buildGraph(ifstream& infile){
	if (infile.is_open()) {
		string line;
		getline(infile, line);
		if (line != "") {
			stringstream S;
			S.str(line);
			S >> size;
			graphNodes = new GraphNode *[size + 1];
			graphNodes[0] = nullptr;
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

//---------------------------- depthFirstSearch -------------------------------------
// Display result of depth-first search
// Preconditions: None
// Postconditions:  Mark all node visited
void GraphL::depthFirstSearch(){
	cout << endl << "Depth-first ordering" << ": " ;
	depthFirstSearchHelper(1);
	
}

//---------------------------- depthFirstSearchHelper -------------------------------------
// Helper of depthFirstSearch: Display result of depth-first search
// Preconditions: None
// Postconditions:  Mark all node visited
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

//---------------------------- displayGraph -------------------------------------
// Display shortest distance, path to cout
// Preconditions: None
// Postconditions: None
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

//---------------------------- initNodes -------------------------------------
// Initialize name and priority of the nodes
// Preconditions: None
// Postconditions: Dynamically locate GraphNode and NodeData to graphNodes[]
void GraphL::initNodes(int nodePlace, string name) {
	graphNodes[nodePlace] = new GraphNode();
	graphNodes[nodePlace]->data = new NodeData(name);
}

//---------------------------- setNextNode -------------------------------------
// Connect edgeNode to graphNodes based on the priority
// Preconditions: None
// Postconditions: Dynamically locate EdgeNode
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

//---------------------------- edgeNodeDelete -------------------------------------
//Helper for deconstructor Delete EdgeNode
// Preconditions: None
// Postconditions: delete EdgeNode
void GraphL::edgeNodeDelete(EdgeNode* deletHepler) {
	if (deletHepler != nullptr) {
		edgeNodeDelete(deletHepler->nextEdge);
		delete deletHepler;
	}
}
