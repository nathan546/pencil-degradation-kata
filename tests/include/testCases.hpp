
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

		TestSuite(unsigned int pencilLen, unsigned int pointDura, unsigned int eraserDura, std::initializer_list<TestCase> incomingTestCases){
			for(TestCase currentCase : incomingTestCases)
				testCases.push_back(currentCase);

			pencilLength = pencilLen;
			eraserDurability = eraserDura;
			pointDurability = pointDura;
		}

		std::vector<TestCase> testCases;
		unsigned int pointDurability;
		unsigned int eraserDurability;
		unsigned int pencilLength;
};


TestSuite testSuites[] = 
{

	//Basic write test
	TestSuite(UINT_MAX, UINT_MAX, UINT_MAX,
		{
			{"write", "I will not continue writing on the writing board.", "I will not continue writing on the writing board."},
			{"erase", "writing"         , "I will not continue writing on the         board."},
			{"edit", "floor"            , "I will not continue writing on the floor   board."},
			{"write", " test"           , "I will not continue writing on the floor   board. test"},
			{"erase", "writing"         , "I will not continue         on the floor   board. test"},
			{"edit", "writing test test", "I will not continue writing @@sth@e@@oor   board. test"}
		}
	),

	//Write test example from Kata guidelines
	TestSuite(UINT_MAX, UINT_MAX, UINT_MAX,
		{
			{"write", "She sells sea shells", "She sells sea shells"},
			{"write", " down by the sea shore", "She sells sea shells down by the sea shore"}
		}
	),

	//Write/erase test example from Kata guidelines
	TestSuite(UINT_MAX, UINT_MAX, UINT_MAX,
		{
			{"write", "How much wood would a woodchuck chuck if a woodchuck could chuck wood?", "How much wood would a woodchuck chuck if a woodchuck could chuck wood?"},
			{"erase", "chuck", "How much wood would a woodchuck chuck if a woodchuck could       wood?"},
			{"erase", "chuck", "How much wood would a woodchuck chuck if a wood      could       wood?"}
		}
	),

	//Write/erase/edit test example from Kata guidelines
	TestSuite(UINT_MAX, UINT_MAX, UINT_MAX,
		{
			{"write", "An onion a day keeps the doctor away", "An onion a day keeps the doctor away"},
			{"erase", "onion"   , "An       a day keeps the doctor away"},
			{"edit", "onion"    , "An onion a day keeps the doctor away"},
			{"erase", "onion"   , "An       a day keeps the doctor away"},
			{"edit", "artichoke", "An artich@k@ay keeps the doctor away"}
		}
	),

	//Point degradation test from Kata guidelines
	TestSuite(UINT_MAX, 4, UINT_MAX,
		{
			{"write", "Text", "Tex "}
		}
	),

	//Point degradation test on an edit action
	TestSuite(UINT_MAX, 8, UINT_MAX,
		{
			{"write", "abcdef", "abcdef"},
			{"erase", "def",    "abc   "},
			{"edit",  "DEF",    "abcD  "}
		}
	),

	//Eraser degradation test from Kata guidelines
	TestSuite(UINT_MAX, UINT_MAX, 3,
		{
			{"write", "Buffalo Bill", "Buffalo Bill"},
			{"erase", "Bill", "Buffalo B   "}
		}
	),

	//Point degradation test with a sharpening
	TestSuite(1, 10, UINT_MAX,
		{
			{"write", "TextText", "TextText"},
			{"write", "NULL"    , "TextText    "},
			{"sharpen", "", ""},
			{"write", "Text"    , "TextText    Text"},
			{"write", "Te"      , "TextText    TextTe"},
			{"write", "xtText"  , "TextText    TextText    "}
		}
	),

	//Editing past the end of the string should not produce @ symbols!
	TestSuite(UINT_MAX, UINT_MAX, UINT_MAX,
		{
			{"write", "An onion a day keeps the doctor away", "An onion a day keeps the doctor away"},
			{"erase", "away", "An onion a day keeps the doctor     "},
			{"edit", "away all day", "An onion a day keeps the doctor away all day"}
		}
	)

};


#endif