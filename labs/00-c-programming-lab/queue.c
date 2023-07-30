/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

list_ele_t *ele_new(char *s)
{
    char *news = malloc(strlen(s)+1);
    if (news == NULL){
        return NULL;
    }

    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL){
        free(news);
        return NULL;
    }

    strcpy(news, s);
    newh->value=news;
    newh->next=NULL;
    return newh;
}

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->len = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL){
        return;
    }
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t* walker = q->head;
    while (q->head){
        walker =q->head;
        q->head=walker->next;
        free(walker->value);
        free(walker);
    }
    q->head=NULL;
    q->tail=NULL;
    q->len=0;
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL){
        return false;
    }
    list_ele_t *newh = ele_new(s);
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (newh == NULL){
        return false;
    }
    newh->next = q->head;
    q->head = newh;
    q->len++;
    if(q->tail == NULL){
        q->tail=newh;
    }
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL){
        return false;
    }
    if (q->len == 0){
       return q_insert_head(q,s);
    }

    list_ele_t *newh = ele_new(s);
    if (newh == NULL) {
        return false;
    }
    q->tail->next=newh;
    q->tail = newh;
    q->len++;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->len == 0){
        return false;
    }
    if (sp){
        strncpy(sp, q->head->value, bufsize);
        sp[bufsize-1]='\0';
    }
    /* You need to fix up this code. */
    list_ele_t* old_head = q->head;
    q->head = q->head->next;
    q->len--;
    if (q->len == 0){
        q->tail = NULL;
    }
    free(old_head->value);
    free(old_head);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL){
        return 0;
    }
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->len;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q == NULL || q->len <=1){
        return;
    }

    list_ele_t *walker = q->head;
    list_ele_t *walker_next = q->head->next;
    while (walker->next){
        walker_next=walker->next;
        walker->next=walker_next->next;
        walker_next->next=q->head;
        q->head=walker_next;
    }
    q->tail=walker;
}

