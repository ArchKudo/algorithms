#include "include/list.h"
#include <stdlib.h>
#include <string.h>

void list_init(List *list, void (*destroy)(void *data)) {
  LIST_SIZE(list) = 0;
  /* User defined function to deallocate data associated with ListElmt */
  list->destroy = destroy;
  LIST_HEAD(list) = NULL;
  LIST_TAIL(list) = NULL;
}

void list_destroy(List *list) {
  void *data;
  // Remove each element starting from head
  // Check whether destroy functon is defined
  while (LIST_SIZE(list) > 0) {
    if (list_rem_next(list, NULL, (void **)&data) == 0 &&
        list->destroy != NULL) {
      list->destroy(data);
    }
  }
  memset(list, 0, sizeof(List));  // Safety Precautionary Measure
}

int list_ins_next(List *list, ListElmt *element, const void *data) {
  ListElmt *new_element;
  if ((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL) {
    return -1;
  }
  new_element->data = (void *)data;
  // Set the new list element to head of list
  if (element == NULL) {
    if (LIST_SIZE(list) == 0) {
      LIST_TAIL(list) = new_element;
    }
    // Set @a new_element's @a next to the @a head of the list
    ELM_NEXT(new_element) = LIST_HEAD(list);
    // Set @a new_element to head of the list
    LIST_HEAD(list) = new_element;
  } else {  // Else for anywhere in the list

    // If the given element(@a element) is at tail of the list
    if (ELM_NEXT(element) == NULL) {
      // Set the @a new_element to tail of the list
      LIST_TAIL(list) = new_element;
    }

    // Set @a new_element's next to that of @a element's next
    ELM_NEXT(new_element) = ELM_NEXT(element);
    // Set @a element's next to @a new_element
    ELM_NEXT(element) = new_element;
  }
  LIST_SIZE(list)++;
  return 0;
}

int list_rem_next(List *list, ListElmt *element, void **data) {
  ListElmt *old_element;
  // Check whether size of list is not 0
  if (LIST_SIZE(list) == 0) {
    return -1;
  }
  // Remove head element
  if (element == NULL) {
    *data = ELM_DATA(LIST_HEAD(list));
    old_element = LIST_HEAD(list);
    LIST_HEAD(list) = ELM_NEXT(LIST_HEAD(list));
    if (LIST_SIZE(list) == 1) {
      LIST_TAIL(list) = NULL;
    }
  } else {
    if (ELM_NEXT(element) == NULL) {
      return -1;
    }
    *data = ELM_DATA(ELM_NEXT(element));
    old_element = ELM_NEXT(element);
    ELM_NEXT(element) = ELM_NEXT(ELM_NEXT(element));
    if (ELM_NEXT(element) == NULL) {
      LIST_TAIL(list) = element;
    }
  }
  free(old_element);
  LIST_SIZE(list)--;
  return 0;
}
