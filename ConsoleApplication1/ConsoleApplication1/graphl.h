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

#include "nodedata.h"
#include <fstream>
using namespace std;

class GraphL {
	public:
		GraphL();	//Constructor
		~GraphL();	//Deconstructor
		
		void buildGraph(ifstream& file);	//build the graph based on data on the data in textfile connect node to graphNode**
		void depthFirstSearch();	//Display result of depth-first search and mark all node visited
		void depthFirstSearchHelper(int initial);	//Helper of depth-first search
		void displayGraph();              // display shortest distance, path to cout

	private:
		struct EdgeNode {
			int adjGraphNode;  // subscript of the adjacent graph node
			EdgeNode* nextEdge;	//point to the other adjacnet node
		};
		struct GraphNode {    // structs used for simplicity, use classes if desired
			EdgeNode* edgeHead; // head of the list of edges
			NodeData* data;     // data information about each node
			bool visited = false;	//true if the node is already visited while depth-first search
		};
		GraphNode** graphNodes;      // forward reference for the compiler
		int size;	//the total number of the nodes
		void initNodes(int nodePlace, string name);	//initialize name and priority of the nodes
		void setNextNode(int nodePlace, int adjNode);	//connect edgenode to graph nodes based on the priority
		void edgeNodeDelete(EdgeNode* deletHepler); //Helper for deconstructor Delete EdgeNode
};