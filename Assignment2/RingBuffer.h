#pragma once
using namespace std;
#include <iostream>

struct Data
{
	char content = 0;
};

class RingBuffer
{
private:
	Data** data;
	unsigned int readIdx;
	unsigned int writeIdx;
	unsigned int size;

public:
	RingBuffer(unsigned int size);
	~RingBuffer();
	RingBuffer(const RingBuffer& buffer);
	RingBuffer& operator=(const RingBuffer& buffer);

	bool readElement(char* data);
	void writeElement(char data);
	void countElements(char value) const;
	void resizeBuffer(unsigned int newSize);
	void checkBuffer() const;
};