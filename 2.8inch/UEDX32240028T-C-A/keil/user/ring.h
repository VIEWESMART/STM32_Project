#ifndef __RINGQUEUE_H
#define __RINGQUEUE_H

/*
	存放插补结果数据
*/

typedef struct _RING_QUEUE
{
	int front;   /*头指针*/
	int rear;    /*尾指针*/
	int count;   /*计数器，记录队列中的 元素的个数*/
	int size;    /*环形队列的大小*/
	unsigned char *pdata; // 环形队列的数据指针 [QueueSize];
	
} RingQueue, *PRingQueue;


int  QueueEmpty(RingQueue *Q);
int  QueueFull(RingQueue *Q);
int  QueueCount(RingQueue *Q);
void InitQueue(RingQueue *Q, unsigned char *pQdata, int Qsize);
int  EnQueue(RingQueue *Q, unsigned char *x, int insize);
int  DeQueue(RingQueue *Q, unsigned char *x, int outsize);
int QueueFront(RingQueue *Q, unsigned char *x, int outsize);
int PeekQueue(RingQueue *Q, unsigned char * x, int outsize,int offset);
int ModifyQueueFront(RingQueue *Q, int offset);
int RemainByte(RingQueue *Q);

int QueueRear(RingQueue *Q, unsigned char * x, int outsize);
int EnQueueSignal( RingQueue *Q, unsigned char x);


#endif