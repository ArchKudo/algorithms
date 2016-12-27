#include "include/dlist.h"
#include <stdlib.h>
#include <string.h>

void dlist_init(DList *list, void (*destroy)(void *data)) {
  DLIST_SIZE(list) = 0;
  DLIST_HEAD(list) = NULL;
  DLIST_TAIL(list) = NULL;
  list->destroy = destroy;
}

void dlist_destroy(DList *list) {
  void *data;
  while (DLIST_SIZE(list) > 0) {
    if (dlist_remove(list, DLIST_TAIL(list), (void **)&data) == 0 &&
        list->destroy != NULL) {
      list->destroy(data);
    }
  }
  memset(list, 0, sizeof(DList));
}

int dlist_ins_next(DList *list, DListElmt *element, const void *data) {
  DListElmt *new_element;
  if (element == NULL && DLIST_SIZE(list) != 0) {
    return -1;
  }
  if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL) {
    return -1;
  }
  ELM_DATA(new_element) = (void *)data;

  if (DLIST_SIZE(list) == 0) {
    DLIST_HEAD(list) = new_element;
    ELM_PREV(new_element) = NULL;
    ELM_NEXT(new_element) = NULL;
    DLIST_TAIL(list) = new_element;
  } else {
    ELM_NEXT(new_element) = ELM_NEXT(element);
    ELM_PREV(new_element) = element;
    if (ELM_NEXT(new_element) == NULL) {
      DLIST_TAIL(list) = new_element;
    } else {
      ELM_PREV(ELM_NEXT(element)) = new_element;
      ELM_NEXT(element) = new_element;
    }
  }
  DLIST_SIZE(list)++;
  return 0;
}

int dlist_ins_prev(DList *list, DListElmt *element, const void *data) {
  DListElmt *new_element;
  if (DLIST_SIZE(list) != 0 && element == NULL) {
    return -1;
  }
  if ((new_element = (DListElmt *)malloc(sizeof(DList))) == NULL) {
    return -1;
  }
  ELM_DATA(new_element) = (void *)data;
  if (DLIST_SIZE(list) == 0) {
    DLIST_HEAD(list) = new_element;
    ELM_NEXT(new_element) = NULL;
    ELM_PREV(new_element) = NULL;
    DLIST_TAIL(list) = new_element;
  } else {
    ELM_NEXT(new_element) = element;
    ELM_PREV(new_element) = ELM_PREV(element);
    if (ELM_PREV(element) == NULL) {
      DLIST_HEAD(list) = new_element;
    } else {
      ELM_NEXT(ELM_PREV(element)) = new_element;
    }
    ELM_PREV(element) = new_element;
  }
  DLIST_SIZE(list)++;
  return 0;
}

int dlist_remove(DList *list, DListElmt *element, void **data) {
	if (element == NULL && DLIST_SIZE(list) == 0) {
		return -1;
	}
	*data = ELM_DATA(element);

	if (element == DLIST_HEAD(list)) {
		DLIST_HEAD(list) = ELM_NEXT(element);
    if (DLIST_HEAD(list) == NULL) {
      DLIST_TAIL(list) = NULL;
    } else {
      ELM_PREV(ELM_NEXT(element)) = NULL;
    }
	} else {
    ELM_NEXT(ELM_PREV(element)) = ELM_NEXT(element);
    if (ELM_NEXT(element) == NULL) {
      DLIST_TAIL(list) = ELM_PREV(element);
    } else {
      ELM_PREV(ELM_NEXT(element)) = ELM_PREV(element);
    }
  }
  free(element);
  DLIST_SIZE(list)--;
  return 0;
}
