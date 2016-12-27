#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>

/**
 * @def DLIST_SIZE(list)
 * @brief A macro that evaluates to the number of elements in the list provided
 * by @a list parameter.
 * Complexity O(1).
 * @param list	A struct of type @a DList
 * @return			The size of @a list
 */
#define DLIST_SIZE(list) ((list)->size)

/**
 * @def DLIST_HEAD(list)
 * @brief A macro that evaluates to the head(first element) of the list.
 * Complexity O(1).
 * @param list  A struct of type @a DList
 * @return      A pointer to the head of the list
 */
#define DLIST_HEAD(list) ((list)->head)

/**
 * @def DLIST_TAIL(list)
 * @brief A macro that evaluates to the tail(last element) of the list.
 * Complexity O(1)
 * @param list	A struct of type @a DList
 * @return			A pointer to the tail of the list
 */
#define DLIST_TAIL(list) ((list)->tail)

/**
 * @def DLIST_IS_HEAD(list, element)
 * @brief   A macro to check whether the @a element is the head of the list.
 * Complexity O(1)
 * @param	list    A struct of type @a DList
 * @param	element A struct of type @a DListElmt
 * @return        @b 1 if @a element is head @b 0 otherwise
 */
#define DLIST_IS_HEAD(element) ((element)->prev == NULL ? 1 : 0)

/**
 * @def LIST_IS_TAIL(list, element)
 * @brief   A macro to check whether the @a element is the tail of the list.
 * Complexity O(1)
 * @param DList		A struct of type @a DList
 * @param element A struct of type @a DListElmt
 * @return				@b 1 if @a element is tail @b 0
 * otherwise
 */
#define DLIST_IS_TAIL(element) ((element)->next == NULL ? 1 : 0)

/**
 * @def ELM_DATA(element)
 * @brief A macro to evaluate the data stored in @a element as a pointer.
 * Complexity O(1)
 * @param	element A struct of type @a DListElmt
 * @return        The pointer to the data field of @a element
 */
#define ELM_DATA(element) ((element)->data)

/**
 * @def ELM_NEXT(element)
 * @brief A macro to evaluate the next element of the given @a element.
 * Complexity O(1)
 * @param	element	A struct of type DListElmt
 * @return        A struct of type DListElmt
 */
#define ELM_NEXT(element) ((element)->next)

/**
 * @def ELM_PREV(element)
 * @brief A macro to evaluate the previous element of the given @a element.
 * Complexity O(1)
 * @param	element	A struct of type DListElmt
 * @return        A struct of type DListElmt
 */
#define ELM_PREV(element) ((element)->prev)

/**
 * @struct DListElmt
 * @brief A structure with three fields one to store data and other two to store
 * the
 * previous and next pointer.
 * For defining the elements of the struct @a DList
 */
typedef struct DListElmt {
  void *data;              // A pointer to void to store the data
  struct DListElmt *prev;  // A pointer to the previous @a DListElmt element
  struct DListElmt *next;  // A pointer to the next @a DListElmt element
} DListElmt;

/**
 * @struct DList
 * @brief A struct to contain the @a DListElmt 's
 * Includes pointers for functions to match and, destroy struct
 */
typedef struct DList {
  int size;  // The size of the DList
  /* User defined functions */
  int (*match)(const void *key_1, const void *key_2);
  void (*destroy)(void *data);

  DListElmt *head;  // The head of the list of type @a DListElmt
  DListElmt *tail;  // The tail of the list of type @a DListElmt
} DList;

// Init and destroy functions

/**
 * @fn void dlist_init(DList *list, void (*destroy)(void *data))
 * @brief Initialize a new @a DList
 * Complexity O(1)
 * @param	DList		A struct of type @a DList
 * @param destroy	A pointer to function to destroy the @a DList
 */
void dlist_init(DList *list, void (*destroy)(void *data));

/**
 * @fn void dlist_destroy(DList *list)
 * @brief Destroy the list specified by @a list which points to @a DList struct.
 * Complexity O(n)
 * @param list A struct of type @a DList
 */
void dlist_destroy(DList *list);

// Insert functions

/**
 * @fn int dlist_ins_next(DList *list, DListElmt *element, const void *data)
 * @brief Insert element of type @a DListElmt just after the @a DListElmt pointed
 * by @a element.
 * element
 * If @a element is NULL then the new element is inserted at head of the list
 * On destruction data pointed by @a data must be free'd by the user
 * Graphically:
 *
 * 																// Initial //
 *
 * 				  	A															B
 * 	[prev | data_a | next] ----> [prev | data_b | next] ----||
 *
 * 											// dlist_ins_next(list, B, data) //
 *
 * 				  	A															B														C
 * 	[prev | data_a | next] ----> [prev | data_b | next] ----> [prev | data | next] ----||
 *
 * @param  list    A struct of type @a DList
 * @param  element A struct of type @a DListElmt
 * @param  data    A pointer to the @a data pointer
 * @return         @b 0 if inserting the element is successful, or @b –1
 * otherwise
 */
int dlist_ins_next(DList *list, DListElmt *element, const void *data);

/**
 * @fn int dlist_ins_prev(DList *list, DListElmt *element, const void *data)
 * @brief Insert element of type @a DListElmt just before the @a DListElmt pointed
 * by @a element.
 * element
 * If @a element is NULL then the new element is inserted at head of the list
 * On destruction data pointed by @a data must be free'd by the user
 * Graphically:
 *
 * 																// Initial //
 *
 * 				  	A															B
 * 	[prev | data_a | next] ----> [prev | data_b | next] ----||
 *
 * 											// dlist_ins_next(list, B, data) //
 *
 * 				  	A														C														B
 * 	[prev | data_a | next] ----> [prev | data | next] ----> [prev | data_b | next] ----||
 *
 * @param  list    A struct of type @a DList
 * @param  element A struct of type @a DListElmt
 * @param  data    A pointer to the @a data pointer
 * @return         @b 0 if inserting the element is successful, or @b –1
 * otherwise
 */
int dlist_ins_prev(DList *list, DListElmt *element, const void *data);

// Remove function

/**
 * @fn int dlist_remove(DList *list, DListElmt *element, void **data);
 * @brief Removes @a element of type @a DListElmt.
 * Upon removal @a data points data contained by @a element
 * Data pointed by @a data must be free'd by the user
 * Graphically:
 *
 * 																// Initial //
 * 				  	A														C														B
 * 	[prev | data_a | next] ----> [prev | data | next] ----> [prev | data_b | next] ----||

 *
 * 											// dlist_remove(list, C, data) //
 *
 * 				  	A															B
 * 	[prev | data_a | next] ----> [prev | data_b | next] ----||
 *
 * @param  list    A struct of type @a DList
 * @param  element A struct of type @a DListElmt
 * @param  data    A pointer to the @a data pointer
 * @return         @b 0 if removing the element is successful or @b -1 otherwise
 */
int dlist_remove(DList *list, DListElmt *element, void **data);

#endif /* DLIST_H */
