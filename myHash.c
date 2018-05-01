#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_TABLE_SIZE = 24;

struct node {
  char *data;
  struct node* next;
};

struct node* create(char *data, struct node* next)
{
  struct node* new_node = (struct node*)malloc(sizeof(struct node));

  if(new_node == NULL) {
      printf("Error creating a new node.\n");
      exit(0);
  }
  new_node->data = data;
  new_node->next = next;
 
  return new_node;
}

int get_hash_code(char *string) {
  int value = 0;
  int ascii;

  for(int i=0; i < strlen(string); i++) {
    ascii = (int) string[i];
    value += ascii;
  }

  return value % MAX_TABLE_SIZE;
}

struct node* get_tail(struct node* origin) {
  if(origin->next) {
    return get_tail(origin->next);
  }
  return origin;
}

void insert_in_table(char *string, struct node** hash_table) {
  int hash_code = get_hash_code(string);
  printf("inserting %s with hash code %d\n", string, hash_code);
  
  if(hash_table[hash_code] != NULL) {
    printf("Collision while inserting! \n");

    struct node* tail = get_tail(hash_table[hash_code]);
    tail->next = create(string, NULL);
  }
  else {
    hash_table[hash_code] = create(string, NULL);
  }
}

int is_in_linked_list(char *string, struct node* origin){
  if(strcmp(origin->data, string) == 0) {
    return 1;
  }
  else {
    if(origin->next) {
      return is_in_linked_list(string, origin->next);
    }
    return 0;
  }
}

int is_in_table(char *string, struct node** hash_table) {
  int hash_code = get_hash_code(string);
  if(hash_table[hash_code] != NULL) {
    return is_in_linked_list(string, hash_table[hash_code]);
  }
  else {
    return 0;
  }
}

void check_if_in_table(char *string, struct node** hash_table) {
  printf("%s is in table: %d\n", string, is_in_table(string, hash_table));
}

int main() {
  struct node* hash_table[MAX_TABLE_SIZE];

  for(int i=0; i < MAX_TABLE_SIZE; i++) {
    hash_table[i] = NULL;
  }

  insert_in_table("alex", hash_table);
  check_if_in_table("alex", hash_table);
  check_if_in_table("laex", hash_table);
  check_if_in_table("jean", hash_table);

  insert_in_table("laex", hash_table);
  check_if_in_table("laex", hash_table);
}
