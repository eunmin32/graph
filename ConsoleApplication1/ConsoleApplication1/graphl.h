#include "nodedata.h"
#include <iostream>
#include <fstream>
using namespace std;

class GraphL {
	public:
		GraphL();
		~GraphL();
		void buildGraph(ifstream& file);
		void depthFirstSearch();
		void depthFirstSearchHelper(int initial);
		void displayGraph();              // display shortest distance, path to cout

	private:
		struct EdgeNode {
			int adjGraphNode;  // subscript of the adjacent graph node
			EdgeNode* nextEdge;
		};
		struct GraphNode {    // structs used for simplicity, use classes if desired
			EdgeNode* edgeHead; // head of the list of edges
			NodeData* data;     // data information about each node
			bool visited = false;
		};
		GraphNode** graphNodes;      // forward reference for the compiler
		int size;
		void initNodes(int nodePlace, string name);
		void setNextNode(int nodePlace, int adjNode);
};