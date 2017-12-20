#include <stdio.h>
#include <stdlib.h>

static FILE *graph = NULL;

static void die(char *message) {
  perror(message);
  exit(-1);
}

void print_prologue()
{
  graph = fopen("callgraph.dot", "w");
  if (graph == NULL)
    die("Couldn't open output file");

  if (fprintf(graph, "digraph {\n  concentrate=true;\n") < 0)
    die("Error writing to output file");
}

void print_epilogue()
{
  if (fprintf(graph, "}\n") < 0)
    die("Error writing to output file");

  if (fclose(graph) != 0)
    die("Error closing output file");
}

void print_edge(const char * src, const char * dst)
{
  if (fprintf(graph, "  %s -> %s;\n", src, dst) < 0)
    die("Error writing to output file");
}
