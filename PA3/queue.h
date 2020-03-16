#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdbool.h>
#define QUEUE_MAXSIZE 50
#define QUEUE_PASS 0
#define QUEUE_FAIL -1

typedef struct queue_node
{
	void* data;
} queue_node;

typedef struct queue_struc
{
	queue_node* list;
	int head;
	int tail;
	int maxSize;
} queue;

/* initilize a new queue
 * if pass, return size
 * if fail, return QUEUE_FAIL
 */
int queue_init(queue* q, int size);

/* test the queue is empty
 * if empty, return true
 * else, return false
 */
bool is_empty(queue* q);

/* test the queue is full
 * if full, return true
 * else, return false
 */
bool is_full(queue* q);

/* push new data to queue
 * if suceess, return QUEUE_PASS
 * if fials, return QUEUE_FAIL
 */
int queue_push(queue* q, void* data);

/* return head node from queue
 * return NULL, if queue is empty
 */
void* queue_pop(queue* q);

/* Destory queue and free memory
 */
void queue_destruct(queue* q);

#endif