#include <string.h>
#include <stdlib.h>
#include "prio-q.h"

/* This file contains functions essential for creating manipulating 
 * the Prio_que data structure. init() must be called first on any
 * Prio_que to ensure that the rest of the functions work properly.
 * clear() must also be called on the Prio_que after all operations have
 * been performed to ensure that there are no memory leaks.
 * If edits to the Prio_que are made using only these functions, 
 * the element with the highest priority will always remain
 * at the head of the list. 
 */

static void clear_aux(Node *node);

/**
 * Initializes the priority queue to an empty list,
 * setting the head to null. This must be called on
 * any newly declared Prio_que before using any other operations on it
 * or it may not function properly.
 **/
void init(Prio_que *const prio_q) {
  if (prio_q != NULL) {
    prio_q -> head = NULL; 
  }
}

/**
 * Adds an element to the queue, its placement is determined by its priority.
 * elements with greater priority will always be ahead of elements with lower
 * priority. The function returns 0 and has no effect if any of the passed
 * pointers are NULL, or if the priority is negative, or if there is an 
 * element with equal priority already in the list. It returns 1 otherwise.
 **/
unsigned int enqueue(Prio_que *const prio_q, const char new_element[],
		     unsigned int priority) {
  char *data;
  Node *new_node;
  Node *curr_node;
  Node *prev_node = NULL;
  
  /* Returns 0 on bad input. Negative priority check doesn't do anything, since 
     priority is unsigned, but is kept in case the type of priority changes */
  if (prio_q == NULL || new_element == NULL || priority < 0)
    return 0;
 
    /* Allocates and initializes the new node */
    data = calloc(strlen(new_element) + 1, sizeof(*new_element));
    strcpy(data, new_element);
    new_node = malloc(sizeof(*new_node));
    new_node -> data = data;
    new_node -> priority = priority;
    new_node -> next = NULL;

    curr_node = prio_q -> head;

    /* Iterates through the queue to find where to insert the node */
    while (curr_node != NULL) {
      /* If it finds a node with lower priority */
      if ((curr_node -> priority) < priority) {
        new_node -> next = curr_node;

        /* Checks if it need to insert at the head */
        if (prev_node == NULL) {
          prio_q -> head = new_node;
        } else {
          prev_node -> next = new_node;
        } 

        return 1;
        /* If it finds a node with equal priority */
      } else if ((curr_node -> priority) == priority) {
	      return 0;
      }

      /* Updating nodes for next loop */
      prev_node = curr_node;
      curr_node = curr_node -> next;
    }

    /* If it needs to insert at the end of the queue 
       (or the head of an empty queue) */ 
    if (prev_node == NULL) {
      prio_q -> head = new_node;
    } else {
      prev_node -> next = new_node;
    }
    
    return 1;
}


/**
 * Returns 1 if the list is empty, returns 0 otherwise.
 **/
unsigned int is_empty(const Prio_que prio_q) {
  unsigned int result = 0;

  if ((prio_q.head) == NULL)
    result = 1;

  return result;
}

/**
 * Returns an integer equal to the number of elements in the queue
 **/
unsigned int size(const Prio_que prio_q) {
  unsigned int size = 0;
  Node *curr_node = prio_q.head;

  while (curr_node != NULL) {
    size++;
    curr_node = curr_node -> next;
  }

  return size;
}

/**
 * Returns a pointer to a deep copy of the first string in the queue
 * without modifying the queue in any way. If the queue is empty it 
 * returns NULL.
 **/
char *peek(Prio_que prio_q) {
  char *result;

  if (is_empty(prio_q)) 
    return NULL;
  
  /* Allocates result and copies the head's value into it */
  result = calloc(strlen(prio_q.head -> data) + 1, sizeof(*result));
  strcpy(result, prio_q.head -> data);

  return result;
}

/**
 * Returns a deep copy to the first string in the queue and removes
 * that element from the queue, freeing the memory it used.
 * Returns NULL and does nothing if the list
 * is empty or if the passed pointer is NULL.
 **/
char *dequeue(Prio_que *const prio_q) {
  char *result;
  Node *old_head;

  if (prio_q == NULL || is_empty(*prio_q)) 
    return NULL;

  /* Allocates new memory for the string and copies the data into it */
  result = calloc(strlen(prio_q -> head -> data) + 1, sizeof(*result));
  strcpy(result, prio_q -> head -> data);

  /* Removes the head from the queue */
  old_head = prio_q -> head;
  prio_q -> head = old_head -> next;

  /* Frees the memory the removed node used */
  free(old_head -> data);
  free(old_head);

  return result;
}

/**
 * Returns a pointer to an array containing every string in the 
 * queue in order of decreasing priority. It appends a NULL value 
 * to the end of the array to mark the end. without modifying the 
 * originl queue. If the queue is empty, the array will only have 
 * one NULL element.
 **/
char **get_all_elements(Prio_que prio_q) {
  char **array;
  char *node_data;
  Node *curr_node;
  int i;

  /* Allocate the array with one extra element for NULL */
  array = calloc(size(prio_q) + 1, sizeof((prio_q.head -> data)));

  /* Loops through the queue */
  curr_node = prio_q.head;
  for (i = 0; i < size(prio_q); i++) {
    /* Allocates and copies each string into the array */
    node_data = curr_node -> data;
    array[i] = calloc(strlen(node_data) + 1, sizeof(*node_data));
    strcpy(array[i], node_data);
    curr_node = curr_node -> next;
  }
  /* Sets the last element to NULL */
  array[i] = NULL;
  
  return array;
}

/**
 * Takes a dynamically allocated array of dynamically allocated strings,
 * and frees all of the memory associated with them, as well as the array
 * itself. The last element of the array MUST be NULL or invalid memory 
 * operations will occur. Has no effect when passed a NULL pointer.
 **/
void free_name_list(char *name_list[]) {
  int i = 0;
  if (name_list != NULL) {
    /* Free all elements of the array */
    while (name_list[i] != NULL) {
      free(name_list[i]);
      i++;
    }
    /* Free the array itself */
    free(name_list);
  }
}

/**
 * Frees all dynamically allocated memory associated with the
 * Prio_que, leaving nothing behind in memory. clear() should
 * be called on all queues after operations are complete, before the
 * Prio_que goes out of scope to avoid any memory leaks.
 * Has no effect when passed a NULL pointer.
 **/
void clear(Prio_que *const prio_q) {
  if (prio_q != NULL) {
    clear_aux(prio_q -> head);
  }
}

/**
 * Recursively travels down the Prio_que until it reaches the end,
 * Then frees the memory of the nodes, starting at the end and returning
 * back up the call stack.
 **/
static void clear_aux(Node *node) {
  if (node != NULL) {
    clear_aux(node -> next);
    free(node -> data);
    free(node);
  }
}

/**
 * Returns the priority of the element in the queue with the specified data.
 * If there is more than one node with the specified data in the queue, the
 * higher priority is returned. If the element does not exist, or the
 * passed array is NULL, -1 is returned.
 **/
int get_priority(Prio_que prio_q, char element[]) {
  Node *curr_node;
  if (element == NULL)
    return -1;

  curr_node = prio_q.head;
  
  /* Loop through the queue until the element or end is found */
  while (curr_node != NULL) {
    /* Check if this node matches the data */
    if (strcmp(curr_node -> data, element) == 0) {
      return curr_node -> priority;
    }
    /* Prime for next iteration */
    curr_node = curr_node -> next;
  }
  /* If the element was not found*/
  return -1;
}

/**
 * Removes all elements from the queue between low and high (inclusive), 
 * then returns the number of elements that were removed. Also frees
 * any memory associated with removed elements.
 * Returns 0 and does nothing if the passed pointer is NULL, or if low is 
 * greater than high.
 **/
unsigned int remove_elements_between(Prio_que *const prio_q, unsigned int low,
				     unsigned int high) {
  int elements_removed = 0;
  Node *prev_node = NULL;
  Node *curr_node;
  Node *next_node;
  if (prio_q == NULL || low > high)
    return 0;

  curr_node = prio_q -> head;

  /* Loop through the queue */
  while (curr_node != NULL) {
    next_node = curr_node -> next;

    /* Test each element to see if it is within the params */
    if ((curr_node -> priority >= low) && (curr_node -> priority <= high)) {

      /** Remove any matched elements **/
      if (prio_q -> head == curr_node) {
	      /* If it's the head */
        prio_q -> head = next_node;

      } else {
        /* If it's in the middle or the tail */
        prev_node -> next = next_node;

      }
      free(curr_node -> data);
      free(curr_node);
      curr_node = next_node;
      /* prev_node stays the same */

      elements_removed++;
    } else {
      /* If this element is not within the parameters, prime the next loop */
      prev_node = curr_node;
      curr_node = next_node;
    }
  }
  /* Return the count */
  return elements_removed;
}

/**
 * Changes the priority of the specified element to the new priority specified,
 * and returns 1 on successfull operation.
 * The function returns 0 and has no effect If any of the following are true:
 *  - Either of the pointer parameters are NULL.
 *  - There is no element with the specified data.
 *  - There is more than one element with the specified data.
 *  - There is already an element with the specified priority in the list.
 **/
unsigned int change_priority(Prio_que *prio_q, char element[],
			     unsigned int new_priority) {
  Node *curr_node;
  Node *sub_node;
  if (prio_q == NULL || element == NULL)
    return 0;

  curr_node = prio_q -> head;

  /* Loop through the entire queue */
  while (curr_node != NULL) {
    /* Test for specified element */
    if (strcmp(curr_node -> data, element) == 0) {

      /* Ceck if this element already has the new priority */
      if (curr_node -> priority == new_priority)
      	return 0;

      /* Loop through the queue from this point to check for duplicates */
      sub_node = curr_node -> next;

      while (sub_node != NULL) {
	      if (strcmp(sub_node -> data, element) == 0) {
	        /* If a duplicate element was found */
	        return 0;
	      }
        /* Prime inner loop */
        sub_node = sub_node -> next;
      }

      /** If no duplicates were found **/

      /* Remove specified element */
      remove_elements_between(prio_q, curr_node -> priority,
			      curr_node -> priority);
      
      /* Re-add specified element with new priority */
      enqueue(prio_q, element, new_priority);

      /* If element was added successfully */
      return 1;
    }

    /* Prime for next loop */
    curr_node = curr_node -> next;
  }

  /* If the element was not found */
  return 0;
}
