#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab12.1C++/Lab12.1C++.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char inputFile[] = "test_input.bin";
			char outputFile[] = "test_output.bin";

			ofstream fout(inputFile, ios::binary);
			double testData[] = { 1.2, -3.4, 5.6, 0.0, -1.1, 7.8 };
			for (double num : testData) {
				fout.write((char*)&num, sizeof(num));
			}
			fout.close();

			ProcessBIN(inputFile, outputFile);

			ifstream fin(outputFile, ios::binary);
			double maxValue, minValue;
			fin.read((char*)&maxValue, sizeof(maxValue));
			fin.read((char*)&minValue, sizeof(minValue));
			fin.close();

			Assert::AreEqual(7.8, maxValue);
			Assert::AreEqual(-3.4, minValue);
		}
	};
}
