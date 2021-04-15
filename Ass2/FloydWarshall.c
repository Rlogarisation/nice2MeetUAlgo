// Floyd Warshall ADT interface
// COMP2521 Assignment 2

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FloydWarshall.h"
#include "Graph.h"

/**
 * Finds all shortest paths between all pairs of nodes.
 * 
 * The  function  returns  a 'ShortestPaths' structure with the required
 * information:
 * - the number of vertices in the graph
 * - distance matrix
 * - matrix of intermediates (see description above)
 */
ShortestPaths FloydWarshall(Graph g) {
	// Implement the framework for ShortestPaths.
	// I AM NOT SURE THE APPROPRIATE SIZE FOR THIS.
	ShortestPaths sps;
	sps.numNodes = GraphNumVertices(g);


	// Implement sps.dist:
	// An 2d array which shows shortest distance between any two vertices.
	// Set the distance between all as infinity for now.
	sps.dist = malloc(sps.numNodes * sizeof(int *));
	// Implement sps.next:
	// An 2d array which shows next vertex from given vertex to des.
	// Set the whole array fill with -1 for now.
	sps.next = malloc(sps.numNodes * sizeof(int));
	
	for (int v = 0; v < sps.numNodes; v++) {
		sps.dist[v] = malloc(sps.numNodes * sizeof(int));
		memset(sps.dist[v], INFINITY, sps.numNodes * sizeof(int));
		sps.next[v] = malloc(sps.numNodes * sizeof(int));
		memset(sps.next[v], -1, sps.numNodes * sizeof(int));
	}

	// First, fill in the value of dist[v][v] itself = 0.
	// In next, Assume itself to itself is value itself for now.
	for (int v = 0; v < sps.numNodes; v++) {
		sps.dist[v][v] = 0;
		sps.next[v][v] = v;
	} 
	// Second, fill in the neighbour distance.
	for (int v = 0; v < sps.numNodes; v++) {
		AdjList ListOutIncident = GraphOutIncident(g, v);
		while (ListOutIncident != NULL) {
			sps.dist[v][ListOutIncident->v] = ListOutIncident->weight;
			// Assume in next: node 1 to node 2 will have a next of node 2.
			sps.next[v][ListOutIncident->v] = ListOutIncident->v;
			ListOutIncident = ListOutIncident->next;
		}
	}
	// Last step, search the shortest path between inter-vertices.
	for (int k = 1; k < sps.numNodes; k++) {
		for (int i = 1; i < sps.numNodes; i++) {
			for (int j = 1; j < sps.numNodes; j++) {
				if (sps.dist[i][j] > sps.dist[i][k] + sps.dist[k][j]) {
					sps.dist[i][j] = sps.dist[i][k] + sps.dist[k][j];
					sps.next[i][j] = k;
				}
			}
		}
	}

	return sps;
}

/**
 * This  function  is  for  you to print out the ShortestPaths structure
 * while you are debugging/testing your implementation. 
 * 
 * We will not call this function during testing, so you may  print  out
 * the  given  ShortestPaths  structure in whatever format you want. You
 * may choose not to implement this function.
 */
void showShortestPaths(ShortestPaths sps) {

}

/**
 * Frees  all  memory associated with the given ShortestPaths structure.
 * We will call this function during testing, so you must implement it.
 */
void freeShortestPaths(ShortestPaths sps) {
	// free(sps);

}
