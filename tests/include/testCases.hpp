
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
	)

};


#endif