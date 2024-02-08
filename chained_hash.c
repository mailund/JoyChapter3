
#include "chained_hash.h"

#include <stdlib.h>

#include "linked_lists.h"

LIST
get_key_bin(struct hash_table *table, unsigned int key)
{
  // table->table is an array of LIST_HEAD i.e. an array of struct link *,
  // which makes table->table plus any offset a struct link **, i.e., a LIST.
  unsigned int mask = table->size - 1;
  unsigned int index = key & mask;
  return table->bins + index;
}

struct hash_table *
new_table(unsigned int size)
{
  struct hash_table *table = malloc(sizeof *table);
  table->bins = malloc(size * sizeof *table->bins);
  table->size = size;
  for (LIST bin = table->bins; bin < table->bins + table->size; bin++) {
    init_linked_list(bin);
  }
  return table;
}

void
delete_table(struct hash_table *table)
{
  for (LIST bin = table->bins; bin < table->bins + table->size; bin++) {
    delete_linked_list(bin);
  }
  free(table->bins);
  free(table);
}

void
insert_key(struct hash_table *table, unsigned int key)
{
  LIST bin = get_key_bin(table, key);
  if (!contains_element(bin, key)) { // Avoid duplications
    add_element(bin, key);
  }
}

bool
contains_key(struct hash_table *table, unsigned int key)
{
  return contains_element(get_key_bin(table, key), key);
}

void
delete_key(struct hash_table *table, unsigned int key)
{
  LIST bin = get_key_bin(table, key);
  if (contains_element(bin, key)) {
    delete_element(bin, key);
  }
}
