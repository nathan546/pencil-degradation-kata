
#ifndef TEST_CASES_HPP

#define TEST_CASES_HPP

#include <vector>
#include <climits>

class TestCase{

	public:

		TestCase(std::string oper, std::string inputStr, std::string expectedStr){
			operation = oper;
			inputString = inputStr;
			expectedString = expectedStr;
		}

		std::string operation;
		std::string inputString;
		std::string expectedString;


};

class TestSuite{


	public:

		TestSuite(std::initializer_list<TestCase> incomingTestCases){
			for(TestCase currentCase : incomingTestCases)
				testCases.push_back(currentCase);
		}

		std::vector<TestCase> testCases;
};


TestSuite testSuites[] = 
{

	//Basic write test
	TestSuite(
		{
			{"write", "I will not continue writing on the writing board.", "I will not continue writing on the writing board."},
			{"erase", "writing", "I will not continue writing on the         board."}
		}
	),

	//Write test example from Kata guidelines
	TestSuite(
		{
			{"write", "She sells sea shells", "She sells sea shells"},
			{"write", " down by the sea shore", "She sells sea shells down by the sea shore"}
		}
	),

	//Write/erase test example from Kata guidelines
	TestSuite(
		{
			{"write", "How much wood would a woodchuck chuck if a woodchuck could chuck wood?", "How much wood would a woodchuck chuck if a woodchuck could chuck wood?"},
			{"erase", "chuck", "How much wood would a woodchuck chuck if a woodchuck could       wood?"},
			{"erase", "chuck", "How much wood would a woodchuck chuck if a wood      could       wood?"}
		}
	),

	//Write/erase/edit test example from Kata guidelines
	TestSuite(
		{
			{"write", "An onion a day keeps the doctor away", "An onion a day keeps the doctor away"},
			{"erase", "onion"   , "An       a day keeps the doctor away"},
			{"edit", "onion"    , "An onion a day keeps the doctor away"}
		}
	)

};


#endif