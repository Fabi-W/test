#include "RingBuffer.h"
#include <string>


RingBuffer* createRingBuffer(const unsigned int size)
{
	RingBuffer* data = new RingBuffer;
	
	data->data = new Data*[size];
	data->readIdx = 0;
	data->writeIdx = 0;
	data->size = size;

	for (unsigned int i = 0; i < size; ++i)
		data->data[i] = new Data;

	return data;
}

bool readElement(RingBuffer* buffer, char* data)
{
	if (buffer->readIdx == buffer->writeIdx)
		return false;

	*data = buffer->data[buffer->readIdx]->content;
	buffer->readIdx = ++buffer->readIdx % buffer->size;
	
	return true;
}

void writeElement(RingBuffer* buffer, char data)
{
	buffer->data[buffer->writeIdx]->content = data;
	buffer->writeIdx = ++buffer->writeIdx % buffer->size;
}

void freeMemory(RingBuffer* buffer)
{
	for (unsigned int i = 0; i < buffer->size; i++)
	{
		delete[] buffer->data[i];
	}
	delete[] buffer->data;
	delete buffer;
	buffer = nullptr;
}

void countElements(RingBuffer* buffer, char value)
{
	unsigned int count = 0;
	for (unsigned int i = 0; i < buffer->size; i++) {
		if (buffer->data[i]->content == value) {
			cout << buffer->data[i]->content << endl;
			count++;
		}
	}

	cout << "Counted " << value << " " << count << " time(s)" << endl;
}

RingBuffer* copyRingbuffer(RingBuffer* buffer)
{
	RingBuffer* data = new RingBuffer;
	data->data = new Data*[buffer->size];
	data->readIdx = buffer->readIdx;
	data->writeIdx = buffer->writeIdx;
	data->size = buffer->size;

	for (unsigned int i = 0; i < buffer->size; ++i) {
		data->data[i] = new Data;
		data->data[i]->content = buffer->data[i]->content;
	}

	return data;
}

void resizeBuffer(RingBuffer* buffer, unsigned int newSize)
{
	
	if (newSize > buffer->size) {

		// Save content into array
		char* content = new char[newSize];
		for (unsigned int i = 0; i < newSize; i++) {
			if (i < buffer->size) {
				content[i] = buffer->data[i]->content;
			}
			else {
				content[i] = 0;
			}
		}

		// Delete existing content
		for (unsigned int i = 0; i < buffer->size; i++)
		{
			delete[] buffer->data[i];
		}

		buffer->data = new Data*[newSize];

		for (unsigned int k = 0; k < newSize; ++k) {
			buffer->data[k] = new Data;
			buffer->data[k]->content = content[k];
		}

		delete[] content;
	}

	else if (newSize < buffer->size) {
		if (buffer->readIdx > newSize) {
			buffer->readIdx = 0;
		}
		if (buffer->writeIdx > newSize) {
			buffer->writeIdx = newSize;
		}

		buffer->size = newSize;

		for (unsigned int j = newSize; j < buffer->size; j++) {
			delete[] buffer->data[j];
		}
	}

	else {
		cout << "Same size as original buffer" << endl;
	}
}

void checkBuffer(RingBuffer* buffer)
{
	for (unsigned int i = 0; i < buffer->size; i++) {
		cout << buffer->data[i]->content;
	}

	cout << endl;
}