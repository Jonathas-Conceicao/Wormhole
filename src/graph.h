#ifndef GRAPH_H
#define GRAPH_H
#endif

#ifdef DEBUG
#undef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

/**
 * Struct on wich the graph is build.
 * All graphs are a conjuct of nodes.
 */
typedef struct _Node{
  unsigned int value;       //Node's value
  unsigned int conections;  //Quantity of arrows
  struct _Node **arrows;    //List of pointers of Nodes that are pointed by this node
  int          *weights;    //List of weights of each arrow
} Node;

/**
 * Graph's sentinel ONLY used in graph.c to find a graph by it's value.
 */
typedef struct _Sentinel{
  unsigned int nodeAmount;       //Quantity of nodes
  Node         **nodeList;       //List will all the pointers of Nodes
} Sentinel; //Graph's auxiliar struct.

Sentinel *createGraph();
void freeNode(Node **);
void freeGraph(Sentinel **);
void graphInsertNode(Sentinel *, int);
Node *getNodeFromValue(Sentinel *, int);
void graphInsertArrow(Sentinel *, int, int, int);
int Bellman_Ford(Sentinel *);
