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
  if(DEBUG) fprintf(stderr, "DEBUG:eye->nodeAmount:%i\n",(*eye).nodeAmount);
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
  fromNode = getNodeFromValue(eye, a);
  if (fromNode == NULL) {
    fprintf(stderr, "Failed inside 'graphInsertArrow'.\n Couldn't find node with 'a' value\n");
    return;
  }
  toNode = getNodeFromValue(eye, b);
  if (fromNode == NULL) {
    fprintf(stderr, "Failed inside 'graphInsertArrow'.\n Couldn't find node with 'b' value\n");
    return;
  }
  if(DEBUG) fprintf(stderr, "DEBUG:Starting reallocs\n");
  void *reallocated0, *reallocated1;
  (*fromNode).conections++; //Set number of arrows
  reallocated0 = realloc((*fromNode).arrows, sizeof(Node **) * (*fromNode).conections);
  reallocated1 = realloc((*fromNode).weights, sizeof(int *) * (*fromNode).conections);
  if(DEBUG) fprintf(stderr, "DEBUG:Done with reallocs\n");
  if (reallocated0 == NULL || reallocated1 == NULL){
    fprintf(stderr, "Failed inside 'graphInsertArrow'.\nFailed a realloc\n");
    (*fromNode).conections--;
    return;
  }
  if(DEBUG) fprintf(stderr, "DEBUG:No Realloc was NULL\n");
  (*fromNode).arrows  = (Node **) reallocated0;
  (*fromNode).weights = (int *)  reallocated1;

  *( ((Node **) (*fromNode).arrows) + ((*fromNode).conections - 1))  = toNode;
  *( ((int  *) (*fromNode).weights) + ((*fromNode).conections - 1)) = weight;

  return;
}

void freeGraph(Sentinel **pEye){
  Sentinel *eye = *pEye;
  for (size_t i = 0; i < (*eye).nodeAmount; i++) {
    freeNode( ((Node **) (*eye).nodeList) + i);
  }
  free((*eye).nodeList);
  free(eye);
  *pEye = NULL;
}

void freeNode(Node **pNode) {
  Node *node = *pNode;
  for (size_t i = 0; i < (*node).conections; i++) {
    free(((Node **) (*node).arrows) + i);
    free(((int  *) (*node).weights) + i);
  }
  free(node);
  *pNode = NULL;
}

int Bellman_Ford(Sentinel *graph){
  return -1;
}
