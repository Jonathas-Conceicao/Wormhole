#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int main(int argc, char const *argv[]) {
  size_t i, n, m; //Variables for the for loops.
  int interactions, galaxys, whormholes; //Input data
  int x, y, t; //Input data
  Sentinel *graph;

  scanf("%d%*c", &interactions);
  for (i = 0; i < interactions; i++) {
    scanf("%d %d%*c", &galaxys, &whormholes);
    graph = createGraph();
    for (n = 0; n < galaxys; n++) {
      graphInsertNode(graph, n);
    }
    for (m = 0; m < whormholes; m++) {
      scanf("%d %d %d\n", &x, &y, &t);
      graphInsertArrow(graph, x, y, t);
    }
    if (Bellman_Ford(graph) > 0) printf("possível\n");
    else printf("impossível\n");
    freeGraph(&graph);
  }
  return 0;
}
