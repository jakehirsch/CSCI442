#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Required for strdup

struct person {
  char *name;
  int id;
};

struct person *create_person(const char *name, int id) {
  struct person *p = malloc(sizeof(struct person));
  if (p == NULL)
    return NULL;

  p->name = strdup(name);
  p->id = id;
  return p;
}

void free_person(struct person *p) {
  if (p != NULL) {
    free(p->name); // Free the duplicated stringmake 
    free(p);       // Free the struct itself
  }
}

int main(void) {
  struct person *bob = create_person("Bob", 42);
  printf("Created person: Name=%s, ID=%d\n", bob->name, bob->id);
  free_person(bob);
  printf("Person data has been freed.\n");
  return 0;
}