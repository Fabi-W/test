#include "RingBuffer.h"

#include <random>
#include <iostream>
#include <string>

int main()
{
	// DO NOT TOUCH START
	// for loop. random write length, random read length.
	//std::random_device rd;
	//std::mt19937 gen(rd());
	std::mt19937 gen(100);
	std::uniform_int_distribution<> dist(1, 2);
	std::string testStr = "The test string that goes in the ring buffer.";
	std::string readStr;
	std::string writeStr;
	
	RingBuffer* buffer = createRingBuffer(40);

	for (int i = 0; i < 300; ++i)
	{	
		if (dist(gen) == 1)
		{
			char data;
			if(readElement(buffer, &data))
				readStr += data;			
		}
		if (dist(gen) == 2)
		{
			char data = testStr[writeStr.length() % testStr.length()];
			writeElement(buffer, data);
			writeStr += data;
		}

		std::cout << "Read: " << readStr << std::endl;
		std::cout << "Write: " << writeStr << std::endl;
	}
	// DO NOT TOUCH END

	// TODO: write your test code here.
	// check if all memory is freed using the diagnostics tool.

	// count a char
	cout << "Search for a char output:" << endl;
	char letter = 'a';
	countElements(buffer, letter);

	// Copy an existing buffer
	RingBuffer* copyBuffer = copyRingbuffer(buffer);

	// Check the content of both buffers
	cout << "Buffer and CopyBuffer content:" << endl;
	checkBuffer(buffer);
	checkBuffer(copyBuffer);

	// Resize a buffer
	unsigned int originalBufferSize = buffer->size;

	// Biger
	unsigned int newSizeBig = 50;
	resizeBuffer(buffer, newSizeBig);

	if (newSizeBig > originalBufferSize) {
		for (unsigned int j = originalBufferSize; j < buffer->size; j++) {
			buffer->data[j]->content = 'o';
		}
	}

	//Smaller
	unsigned int newSizeSmall = 30;
	resizeBuffer(copyBuffer, newSizeSmall);

	cout << "Resized buffer output:" << endl;
	checkBuffer(buffer);
	checkBuffer(copyBuffer);

	// Free the memory
	freeMemory(buffer);
	freeMemory(copyBuffer);

	return 0;
}

