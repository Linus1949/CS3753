#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

int queue_init(queue* q, int size){
	q->list = malloc(sizeof(queue_node) * size);

	if (!(q->list)){
		fprintf(stderr, "->Faill to initialize a queue<-");
		return QUEUE_FAIL;
	}
	else{
		for(int i=0; i < size; i++){
		q->list[i].data = NULL;
		}
		q->head = 0;
		q->tail = 0;
		q->maxSize = size;

		return size;
	}
}

bool is_empty(queue* q){
	if ((q->head == q->tail) && (q->list[q->head].data == NULL)){
		return true;
	}
	else{
		return false;
	}
}

bool is_full(queue* q){
	if ((q->head == q->tail) && (q->list[q->head].data != NULL)){
		return true;
	}
	else{
		return false;
	}
}

int queue_push(queue* q, void* data){
	if (is_full(q)){
		return QUEUE_FAIL;
	}
	else{
		q->list[q->tail].data = data;
		q->tail = ((q->tail + 1) % (q->maxSize));
		return QUEUE_PASS;
	}
}

void* queue_pop(queue* q){
	if (is_empty(q)){
		return NULL;
	}
	else{
		void* pop_data = q->list[q->head].data;
		q->list[q->head].data = NULL;
		q->head = ((q->tail + 1) % (q->maxSize));

		return pop_data;
	}
}

void queue_destruct(queue* q){
	while(!is_empty(q)){
		queue_pop(q);
	}
	free(q->list);
}