#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

#ifdef DEBUG
#undef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

/**
 * Starts an empty grath.
 * @method createGraph
 * @return Sentinel, the 'head' of the grath.
 */
Sentinel *createGraph(){
  Sentinel *ret;

  ret = malloc(sizeof(Sentinel));
  (*ret).nodeAmount = 0;
  (*ret).nodeList = NULL;

  return ret;
}

/**
 * Inserts a new Node in the grath with 'value'.
 * @method graphInsertNode
 * @param  eye             Grath's sentinel.
 * @param  value           Node's value.
 */
void graphInsertNode(Sentinel * eye, int value){
  if(DEBUG) fprintf(stderr, "DEBUG:Starting 'graphInsertNode'\n");

  (*eye).nodeAmount++;
  void *reallocated;
  reallocated = realloc((*eye).nodeList, sizeof(Node **) * (*eye).nodeAmount);
  if (reallocated == NULL) {
    fprintf(stderr, "Failed inside 'graphInsertNode'.\nFailed realloc\n");
    (*eye).nodeAmount--;
    return;
  }
  (*eye).nodeList  = (Node **) reallocated;
  Node *newNode;

  newNode = malloc(sizeof(Node));
  (*newNode).value = value;  //Set Node's value
  (*newNode).conections = 0; //Set number of arrows
  (*newNode).arrows  = NULL; //Still a empty list of pointers
  (*newNode).weights = NULL; //Still a empty list of weights
  *( ((Node **) (*eye).nodeList) + ((*eye).nodeAmount - 1) ) = newNode; //Set last node on the list to the new node

  if(DEBUG) fprintf(stderr, "DEBUG:Finished 'graphInsertNode'\n");
  return;
}

/**
 * Find node with a given 'value'
 * @method getNodeFromValue
 * @param  eye              Graph's sentinel.
 * @param  find             Node's value to be found.
 * @return                  Node's pointer.
 */
Node *getNodeFromValue(Sentinel *eye, int find){
  if(DEBUG) fprintf(stderr, "DEBUG:Starting 'getNodeFromValue'\n");
  Node *probe;
  size_t i = -1;
  do{
    i++;
    if (i > (*eye).nodeAmount) {
      fprintf(stderr, "Failed inside 'getNodeFromValue'.\n Couldn't find node with 'find' value\n");
      return NULL;
    }
    probe = *( ((Node **) (*eye).nodeList) + i);
    if(DEBUG) fprintf(stderr, "DEBUG:Viewing node:(prob->value) %i\n", probe->value);
  }while((*probe).value != find);

  if(DEBUG) fprintf(stderr, "DEBUG:Finished 'getNodeFromValue'\n");
  return probe;
}

/**
 * Inserts a new weighted arrow from 'a' node to 'b' node.
 * @method graphInsertArrow
 * @param  eye              Graph's sentinel
 * @param  a                Origin's node
 * @param  b                Destination node
 * @param  weight           Weight from 'a' to 'b'
 */
void graphInsertArrow(Sentinel *eye, int a, int b, int weight){
  if(DEBUG) fprintf(stderr, "DEBUG:Starting 'graphInsertArrow'\n");
  Node *fromNode;
  Node *toNode;
  fromNode = getNodeFromValue(eye, a); //Get node 'a'
  if (fromNode == NULL) {
    fprintf(stderr, "Failed inside 'graphInsertArrow'.\n Couldn't find node with 'a' value\n");
    return;
  }
  toNode = getNodeFromValue(eye, b); //Get node 'b'
  if (fromNode == NULL) {
    fprintf(stderr, "Failed inside 'graphInsertArrow'.\n Couldn't find node with 'b' value\n");
    return;
  }

  void *reallocated0, *reallocated1;
  (*fromNode).conections++; //Set number of arrows
  reallocated0 = realloc((*fromNode).arrows, sizeof(Node **) * (*fromNode).conections);
  reallocated1 = realloc((*fromNode).weights, sizeof(int *) * (*fromNode).conections);
  if (reallocated0 == NULL || reallocated1 == NULL){
    fprintf(stderr, "Failed inside 'graphInsertArrow'.\nFailed a realloc\n");
    (*fromNode).conections--;
    return;
  }
  (*fromNode).arrows  = (Node **) reallocated0; //Set pointer to reallocated memory block
  (*fromNode).weights = (int *)  reallocated1;  //Set pointer to reallocated memory blcok
  *( ((Node **) (*fromNode).arrows) + ((*fromNode).conections - 1) ) = toNode; //Set last element as new conection
  *( ((int  *) (*fromNode).weights) + ((*fromNode).conections - 1) ) = weight; //Set last element as new conection

  if(DEBUG) fprintf(stderr, "DEBUG:Finished 'graphInsertArrow'\n");
  return;
}

/**
 * Releses all graph's memory and set pointer to NULL
 * @method freeGraph
 * @param pEye pointer to graph's pointer
 */
void freeGraph(Sentinel **pEye){
  if(DEBUG) fprintf(stderr, "DEBUG:Starting 'freeGraph'\n");
  Sentinel *eye = *pEye;
  for (size_t i = 0; i < (*eye).nodeAmount; i++) {
    freeNode( ((Node **) (*eye).nodeList) + i);
  }
  free((*eye).nodeList);
  free(eye);
  *pEye = NULL;

  if(DEBUG) fprintf(stderr, "DEBUG:Finished 'freeGraph'\n");
  return;
}

/**
 * Releses all node's memory and set pointer to NULL
 * @param pNode pointer to node's pointer
 */
void freeNode(Node **pNode) {
  if(DEBUG) fprintf(stderr, "DEBUG:Starting 'freeNode'\n");
  Node *node = *pNode;
  free( ((Node **) (*node).arrows));
  free( ((int  *) (*node).weights));
  free(node);
  *pNode = NULL;

  if(DEBUG) fprintf(stderr, "DEBUG:Finished 'freeNode'\n");
  return;
}

/**
 * The Bellman–Ford's algorithm to find the shortest path used to see if there's a negative-weight cycles
 * @param  graph  Graph's pointer
 * @return        [description]
 */
int Bellman_Ford(Sentinel *graph){
  int distance[(*graph).nodeAmount];
  Node *predecessor[(*graph).nodeAmount]; //Will be needed only if DEBUG is set
  Node *uNode, *vNode;
  int weight, u, v;

  //Step 1 set distance to maximum and predecessor to NULL
  for (size_t i = 0; i < (*graph).nodeAmount; i++) {
    distance[i] = 10000; // Values will never be grather than 1000
    predecessor[i] = NULL;
  }
  distance[0] = 0; //set 'source' distance
  predecessor[0] = getNodeFromValue(graph, 0); //Set 'source' predecessor in case of debug

  //Step 2 relax the arrows
  for (size_t i = 0; i < (*graph).nodeAmount; i++) {
    uNode = *(( (Node **) (*graph).nodeList) + i);
    for (size_t j = 0; j < (*uNode).conections; j++) {
      weight = *( ((int *) (*uNode).weights) + j);
      vNode  = *( ((Node **) (*uNode).arrows) + j);
      u = (*uNode).value;
      v = (*vNode).value;
      if(distance[u] +  weight < distance[v]){
        distance[v] = distance[u] + weight;
        predecessor[v] = uNode;
      }
    }
  }

  //Step 3 check for negative-weight cycles
  for (size_t i = 0; i < (*graph).nodeAmount; i++) {
    if(DEBUG) fprintf(stderr, "Node:%i -> Predecessor:%i Distance:%i\n",(int) i, (*(predecessor[i])).value ,distance[i] );
    uNode = *(( (Node **) (*graph).nodeList) + i);
    for (size_t j = 0; j < (*uNode).conections; j++) {
      weight = *( ((int *) (*uNode).weights) + j);
      vNode  = *( ((Node **) (*uNode).arrows) + j);
      u = (*uNode).value;
      v = (*vNode).value;
      if (distance[u] +  weight < distance[v]) {
        return 1;
      }
    }
  }
  return 0;
}
