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
	
	RingBuffer* buffer = new RingBuffer(40);

	for (int i = 0; i < 300; ++i)
	{	
		if (dist(gen) == 1)
		{
			char data;
			if(buffer->readElement(&data))
				readStr += data;			
		}
		if (dist(gen) == 2)
		{
			char data = testStr[writeStr.length() % testStr.length()];
			buffer->writeElement(data);
			writeStr += data;
		}

		std::cout << "Read: " << readStr << std::endl;
		std::cout << "Write: " << writeStr << std::endl;
	}
	// DO NOT TOUCH END

	// TODO: write your test code here.
	// check if all memory is freed using the diagnostics tool.

	cout << endl << "Output original buffer form start to end: " << endl;
	buffer->checkBuffer();


	/**************************** Count a char ****************************/
	cout << endl << "Count a char:" << endl;
	char letter = 't';
	buffer->countElements(letter);

	
	/*********************** Copy and resize some stuff **********************/
	RingBuffer* copy1 = new RingBuffer(*buffer);
	RingBuffer* copy2 = new RingBuffer(*buffer);
	cout << endl << "created copy 1 and 2 via copy constructor, output: " << endl; copy2->checkBuffer();

	copy2->resizeBuffer(50);
	cout << endl << "output copy2 after resize: " << endl; copy2->checkBuffer();

	*copy2 = *copy1;
	cout << endl << "assigned copy1 to copy2, output copy2: " << endl; copy2->checkBuffer();


	/******************************** Delete ********************************/
	delete buffer;
	delete copy1;
	delete copy2;
	
	return 0;
}

