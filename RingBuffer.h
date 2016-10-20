#pragma once
using namespace std;
#include <iostream>

struct Data
{
	char content = 0;
};

struct RingBuffer
{
	Data** data;
	unsigned int readIdx;
	unsigned int writeIdx;
	unsigned int size;
};

RingBuffer* createRingBuffer(const unsigned int size);

// returns false, if end of new data is reached
bool readElement(RingBuffer* buffer, char* data);
void writeElement(RingBuffer* buffer, char data);

// Free all of the memory allocated by the RingBuffer (here: 216 bytes)
void freeMemory(RingBuffer* buffer);

// count all elements of a char value (e.g., 'e' or 't'). 
// Search the whole ring buffer, not only between readIdx and writeIdx.
void countElements(RingBuffer* buffer, char value);

// Copy a RingBuffer, i.e. create copies of the Data instances 
// in the source RingBuffer and copy the Data into a new target
// RingBuffer. Take care to not only copy the pointers to Data!
RingBuffer* copyRingbuffer(RingBuffer* buffer);

// Resize a RingBuffer. If the buffer size is reduced, 
// elements are discarded. 
void resizeBuffer(RingBuffer* buffer, unsigned int newSize);

void checkBuffer(RingBuffer* buffer);


