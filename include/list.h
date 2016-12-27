#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

// Simpler functions implemented as macros

/**
 * @def LIST_SIZE(list)
 * @brief A macro that evaluates to the number of elements in the list provided
 * by @a list parameter.
 * Complexity O(1).
 * @param list	A struct of type @a List
 * @return			The size of @a list
 */
#define LIST_SIZE(list) list->size

/**
 * @def LIST_HEAD(list)
 * @brief A macro that evaluates to the head(first element) of the list.
 * Complexity O(1).
 * @param list  A struct of type @a List
 * @return      A pointer to the head of the list
 */
#define LIST_HEAD(list) list->head

/**
 * @def LIST_TAIL(list)
 * @brief A macro that evaluates to the tail(last element) of the list.
 * Complexity O(1)
 * @param list	A struct of type @a List
 * @return			A pointer to the tail of the list
 */
#define LIST_TAIL(list) list->tail

/**
 * @def LIST_IS_HEAD(list, element)
 * @brief   A macro to check whether the @a element is the head of the list.
 * Complexity O(1)
 * @param	list    A struct of type @a List
 * @param	element A struct of type @a ListElmt
 * @return        @b 1 if @a element is head @b 0 otherwise
 */
#define LIST_IS_HEAD(list, element) (element == LIST_HEAD(list) ? 1 : 0)

/**
 * @def LIST_IS_TAIL(list, element)
 * @brief   A macro to check whether the @a element is the tail of the list.
 * Complexity O(1)
 * @param List		A struct of type @a List
 * @param element A struct of type @a ListElmt
 * @return				@b 1 if @a element is tail @b 0
 * otherwise
 */
#define LIST_IS_TAIL(list, element) (element == LIST_TAIL(list) ? 1 : 0)

/**
 * @def ELM_DATA(element)
 * @brief A macro to evaluate the data stored in @a element as a pointer.
 * Complexity O(1)
 * @param	element A struct of type @a ListElmt
 * @return        The pointer to the data field of @a element
 */
#define ELM_DATA(element) element->data

/**
 * @def ELM_NEXT(element)
 * @brief A macro to evaluate the next element of the given @a element.
 * Complexity O(1)
 * @param	element	A struct of type ListElmt
 * @return        A struct of type ListElmt
 */
#define ELM_NEXT(element) element->next

/**
 * @struct ListElmt
 * @brief A structure with two fields one to store data and other to store the
 * next pointer.
 * For defining the elements of the struct @a List
 */
typedef struct ListElmt {
  void *data;             // A pointer to void to store the data
  struct ListElmt *next;  // A pointer to the next @a ListElmt element
} ListElmt;

/**
 * @struct List
 * @brief A struct to contain the @a ListElmt 's
 * Includes pointers for functions to match and, destroy struct
 */
typedef struct List {
  int size;  // The size of the List
  /* User defined functions */
  int (*match)(const void *key_1, const void *key_2);
  void (*destroy)(void *data);
  ListElmt *head;  // The head of the list of type @a ListElmt
  ListElmt *tail;  // The tail of the list of type @a ListElmt
} List;

// Init and Destroy functions

/**
 * @fn void list_init(List *list, void (*destroy)(void *data))
 * @brief Initialize a new @a List
 * Complexity O(1)
 * @param	List		A struct of type @a List
 * @param destroy	A pointer to function to destroy the @a List
 */
void list_init(List *list, void (*destroy)(void *data));

/**
 * @fn void list_destroy(List *list)
 * @brief Destroy the list specified by @a list which points to @a List struct.
 * Complexity O(n)
 * @param list A struct of type @a List
 */
void list_destroy(List *list);

// Add or Remove elements

/**
 * @fn int list_ins_next(List *list, ListElmt *element, const void *data)
 * @brief Insert element of type @a ListElmt just after the @a ListElmt pointed
 * by @a element.
 * element
 * If @a element is NULL then the new element is inserted at head of the list
 * On destruction data pointed by @a data must be free'd by the user
 * Graphically:
 *
 * 											// Initial //
 *
 * 				  A											B
 * 	[data_a | next] ----> [data_b | next] ----||
 *
 * 						// list_ins_next(list, B, data) //
 *
 * 				  A										B											C
 * 	[data_a | next] ----> [data_b | next] ----> [data | next] ----||
 *
 * @param  list    A struct of type @a List
 * @param  element A struct of type @a ListElmt
 * @param  data    A pointer to the @a data pointer
 * @return         @b 0 if inserting the element is successful, or @b –1
 * otherwise
 */
int list_ins_next(List *list, ListElmt *element, const void *data);

/**
 * @fn int list_rem_next(List *list, ListElmt *element, void *data)
 * @brief Remove element of type @a ListElmt just after the @a ListElmt pointed
 * by @a element.
 * element
 * If @a element is NULL then the new element at head of the list is removed
 * On destruction data pointed by @a data must be free'd by the user
 * Complexity O(1)
 * Graphically:
 *
 * 											// Initial //
 *
 * 				  A											B											C
 * 	[data_a | next] ----> [data_b | next] ----> [data_b | next]
 *
 * 						// list_rem_next(list, B, data) //
 *
 * 				  A											B
 * 	[data_a | next] ----> [data_b | next]
 *
 *
 * @param  list    A struct of type @a List
 * @param  element A struct of type @a ListElmt
 * @param  data    A pointer to the @a data pointer
 * @return         @b 0 if removing the element is successful, or @b –1
 * otherwise
 */
int list_rem_next(List *list, ListElmt *element, void **data);

#endif	/* LIST_H */
