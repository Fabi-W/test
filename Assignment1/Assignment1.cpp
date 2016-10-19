#include "RingBuffer.h"

#include <random>
#include <iostream>
#include <string>

int main()
{
	// DO NOT TOUCH START
	// for loop. random write length, random read length
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

	char letter = 't';
	//countElements(buffer, letter);

//	freeMemory(buffer);

	//RingBuffer* copyBuffer = copyRingbuffer(buffer);
	resizeBuffer(buffer, 30);

	return 0;
}

