#include "RingBuffer.h"
#include <string>

RingBuffer::RingBuffer(const unsigned int size)
{
	data = new Data*[size];
	readIdx = 0;
	writeIdx = 0;
	this->size = size;

	for (unsigned int i = 0; i < size; ++i)
		this->data[i] = new Data;
}

RingBuffer::~RingBuffer()
{
	for (unsigned int i = 0; i < size; i++) {
		delete data[i];
		data[i] = nullptr;
	}

	delete[] data;
	data = nullptr;
}

RingBuffer::RingBuffer(const RingBuffer& buffer)
	: readIdx(buffer.readIdx)
	, writeIdx(buffer.writeIdx)
	, size(buffer.size)
	, data(nullptr)
{
	data = new Data*[buffer.size];

	for (unsigned int i = 0; i < buffer.size; ++i) {
		data[i] = new Data;
		data[i]->content = buffer.data[i]->content;
	}
}

RingBuffer& RingBuffer::operator=(const RingBuffer& buffer)
{
	if (this == &buffer) {
		return *this;
	}

	if (data) {
		for (unsigned int i = 0; i < size; i++) {
			delete data[i];
			data[i] = nullptr;
		}

		delete[] data;
	}

	readIdx = buffer.readIdx;
	writeIdx = buffer.writeIdx;
	size = buffer.size;

	if (buffer.data) {
		data = new Data*[buffer.size];

		for (unsigned int i = 0; i < buffer.size; ++i) {
			data[i] = new Data;
			data[i]->content = buffer.data[i]->content;
		}
	}

	return *this;
	
}

bool RingBuffer::readElement(char* data)
{
	if (readIdx == writeIdx)
		return false;

	*data = this->data[readIdx]->content;
	readIdx = ++readIdx % size;

	return true;
}

void RingBuffer::writeElement(char data)
{
	this->data[writeIdx]->content = data;
	writeIdx = ++writeIdx % size;
}

void RingBuffer::countElements (char value) const
{
	unsigned int count = 0;
	for (unsigned int i = 0; i < size; i++) {
		if (data[i]->content == value) {
			count++;
		}
	}

	cout << "Counted " << value << " " << count << " time(s)" << endl;
}

void RingBuffer::resizeBuffer(unsigned int newSize)
{
	if (newSize > size) {

		// Save content into array
		char* content = new char[newSize];
		for (unsigned int i = 0; i < newSize; i++) {
			if (i < size) {
				content[i] = data[i]->content;
			}
			else {
				content[i] = 'o';
			}
		}

		// Delete existing content
		for (unsigned int m = 0; m < size; m++)
		{
			delete data[m];
			data[m] = nullptr;
		}
		delete[] data;
		data = new Data*[newSize];
		size = newSize;

		for (unsigned int k = 0; k < newSize; ++k) {
			data[k] = new Data;
			data[k]->content = content[k];
		}

		delete[] content;
	}

	else if (newSize < size) {
		if (readIdx > newSize) {
			readIdx = 0;
		}
		if (writeIdx > newSize) {
			writeIdx = newSize;
		}

		for (unsigned int j = newSize; j < size; j++) {
			delete data[j];
			data[j] = nullptr;
		}

		size = newSize;
	}

	else {
		cout << "Same size as original buffer" << endl;
	}
}

void RingBuffer::checkBuffer() const
{
	for (unsigned int i = 0; i < size; i++) {
		cout << data[i]->content;
	}
	cout << endl;
}