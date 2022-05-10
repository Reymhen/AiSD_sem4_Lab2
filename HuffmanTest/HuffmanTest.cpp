#include "pch.h"
#include "CppUnitTest.h"
#include "../HuffmanAlgoritm.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HuffmanTest
{
	TEST_CLASS(HuffmanTest)
	{
	public:
		
		TEST_METHOD(creatingAnEncodingTableTest)
		{
			string testString = "roottt";
			RBtree<char, int> map;
			CodeHuffman test = CodeHuffman(testString);
			test.creatingAnEncodingTable(testString, map);
			Assert::IsTrue(map.get_size() == 3);
			Assert::IsTrue(map.find('o')->value == 2);
			Assert::IsTrue(map.find('r')->value == 1);
			Assert::IsTrue(map.find('t')->value == 3);


		}
		TEST_METHOD(creatingHuffmanTreeTest)
		{
			string testString = "roottt";
			RBtree<char, int> map;
			CodeHuffman test = CodeHuffman(testString);
			test.creatingAnEncodingTable(testString, map);
			test.creatingHuffmanTree(map);
			Assert::IsTrue(test.get_size() == 5);
		}
		TEST_METHOD(codingTreeTest)
		{
			string testString = "roottt";
			string check = "000101111";
			RBtree<char, int> map;
			CodeHuffman test = CodeHuffman(testString);
			test.creatingAnEncodingTable(testString, map);
			test.creatingHuffmanTree(map);
			test.coding();
			Assert::IsTrue(test.codingString == check);
		}
		TEST_METHOD(decodingTest)
		{

			string testString = "roottt";
			string check = "000101111";
			RBtree<char, int> map;
			CodeHuffman test = CodeHuffman(testString);
			test.creatingAnEncodingTable(testString, map);
			test.creatingHuffmanTree(map);
			test.coding();
			test.decoding();
			Assert::IsTrue(test.codingString == check);
			Assert::IsTrue(test.decodingString == testString);
		}
		TEST_METHOD(compressionRatioTest)
		{

			string testString = "roit";
			string check = "00101101";
			RBtree<char, int> map;
			CodeHuffman test = CodeHuffman(testString);
			test.creatingAnEncodingTable(testString, map);
			test.creatingHuffmanTree(map);
			test.coding();
			test.decoding();
			Assert::IsTrue(test.codingString == check);
			Assert::IsTrue(test.decodingString == testString);
			float temp = test.compressionRatio(testString, test.codingString);
			Assert::IsTrue(temp == 4);
		}
	};
}
