#include "ring.h"

#include "string.h"

/*  change from type to unsigned char,
	so that will be handle with char stream*/

//init Queue
void InitQueue(RingQueue *Q, unsigned char *pQdata, int Qsize)
{
	memset(pQdata,0,Qsize);//将自pQdata开始的Qsize位清零
	Q->pdata = pQdata;
	Q->size = Qsize;
	Q->front = Q->rear = 0;
	Q->count = 0;
}

// 判断队空return value: if count == 0 then reurn 1, else 0
int QueueEmpty( RingQueue *Q )
{
	return Q->count == 0;  /*队列无元素为空*/
}

// 判断队满return value: if count == 0 then reurn 1, else 0
int QueueFull( RingQueue *Q )
{  
	return Q->count == Q->size;
}

// 判断队列个数  return count 
int QueueCount( RingQueue *Q )
{
	return Q->count;  /*队列元素个数*/
}

/* 入队	return value: 1, if queue is full or there is not enough space for storing data entering
                      0,  data stored into queue successfully*/
int EnQueue( RingQueue *Q, unsigned char *x, int insize )
{
	int kx = 0;
	if ( QueueFull(Q) || (insize > (Q->size - Q->count)) )
		return 1;       //队列满
			
	//memcpy(&(Q->pdata[Q->rear]), x, insize);
	
	for ( kx = 0; kx < insize; kx++ )
	{
		Q->pdata[Q->rear] = x[kx];			 // store data into the queue
		Q->rear = (Q->rear+1)%Q->size;  //循环意义下尾指针加1
	}	 
	
	Q->count = Q->count+insize;  // count will increase insize
	return 0;
}

/* 入队	return value: 1, if queue is full or there is not enough space for storing data entering
                      0,  data stored into queue successfully*/
int EnQueueSignal( RingQueue *Q, unsigned char x)
{
	int kx = 0;
	if ( QueueFull(Q) || (1 > (Q->size - Q->count)) )
		return 1;       //队列满
			

	Q->pdata[Q->rear] = x;			 // store data into the queue
	Q->rear = (Q->rear+1)%Q->size;  //循环意义下尾指针加1
	Q->count = Q->count+1;  // count will increase insize
	return 0;
}
// 出队
/*  return value:
	1: 队列空或要求出列队字节数>队列中剩余字节数
	0: 成功出列	*/
int DeQueue( RingQueue *Q, unsigned char * x, int outsize )
{
	int kout = 0;
	if ( QueueEmpty(Q) || ( outsize > Q->count) )
		return 1;        //队列空或要求出列队字节数>队列中剩余字节数
		
	for ( kout = 0; kout < outsize; kout++ )
	{
	 	x[kout]  = Q->pdata[Q->front];
		//Q->count = Q->count - 1;
		Q->front = (Q->front+1)%Q->size; /*循环意义下头指针加1*/
	}

	Q->count = Q->count - outsize;
			
	return 0;	
}

//只读数据，不出队
int PeekQueue(RingQueue *Q, unsigned char * x, int outsize,int offset)
{
	int kout = 0;
	int curpos;
	if ( QueueEmpty(Q) || ( outsize > (Q->count-offset)) )
		return 1;        //队列空或要求出列队字节数>队列中剩余字节数
	curpos = Q->front+offset;
	for ( kout = 0; kout < outsize; kout++ )
	{
		//加上offset后有可能超过队列的长度
		curpos = curpos%Q->size; //循环意义下头指针加1
		x[kout]  = Q->pdata[curpos];
		curpos = curpos+1;
	}
	return 0;
}
/*取队头元素*/
/*  return value:
	1: 队列空或要求出列队字节数>队列中剩余字节数
	0: 成功取出头元素，指针不动*/
int QueueFront(RingQueue *Q, unsigned char * x, int outsize)
{
	int kout = 0;

	if( QueueEmpty(Q) || ( outsize > (Q->size - Q->count)) )
		return 1;
	
	for ( kout = 0; kout < outsize; kout++ )
	{
	 	x[kout]  = Q->pdata[Q->front];
	}
	return 0;
}

int QueueRear(RingQueue *Q, unsigned char * x, int outsize)
{
	int kout = 0;
	int start;
	if( QueueEmpty(Q) || ( outsize > (Q->size - Q->count)) )
		return 1;
	start = Q->rear-outsize+1;
	if(start<0)
	{
		start = start+Q->size;
	}
	
	for ( kout = start; kout < outsize; kout++ )
	{
		if(kout>Q->size)
		{
			kout = kout-Q->size;
		}
	 	x[kout]  = Q->pdata[Q->front];
	}
	return 0;
}

int ModifyQueueFront(RingQueue *Q, int offset)
{
	Q->front = (Q->front+offset)%Q->size;
	Q->count = Q->count - offset;
	return 0;
}

int RemainByte(RingQueue *Q)
{
	return (Q->size - Q->count);
}
