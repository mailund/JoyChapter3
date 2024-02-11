
#include "linked_lists.h"

#include <stdio.h>

LIST
new_owned_list()
{
  struct link **ptr = malloc(sizeof *ptr);
  *ptr = NULL;
  return ptr;
}

void
free_list(LIST list)
{
  while (*list) {
    struct link *next = (*list)->next;
    free(*list);
    *list = next;
  }
}

void
free_owned_list(LIST list)
{
  free_list(list);
  free(list);
}

struct link *
new_link(unsigned int key, struct link *next)
{
  struct link *link = malloc(sizeof *link);
  *link = (struct link){.key = key, .next = next};
  return link;
}

void
add_element(LIST list, unsigned int key)
{
  // Build link and put it at the front of the list.
  // The hash table checks for duplicates if we want to
  // avoid those
  *list = new_link(key, *list);
}

LIST
find_key(LIST list, unsigned int key)
{
  for (; *list; list = &(*list)->next) {
    if ((*list)->key == key)
      return list;
  }
  return NULL;
}

void
delete_element(LIST list, unsigned int key)
{
  struct link **prev_ref = find_key(list, key);
  if (prev_ref) {
    // Cut out *prev_ref as this is the link that contains
    // key. First, save its next, then we can free it, and
    // finally update the list by updating the pointer
    // that previously pointed to the now deleted link.
    struct link *next = (*prev_ref)->next;
    free(*prev_ref);
    *prev_ref = next;
  }
}

bool
contains_element(LIST list, unsigned int key)
{
  return find_key(list, key) != 0;
}
