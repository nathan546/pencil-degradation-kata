#ifndef TEST_FACTORY_HPP

#define TEST_FACTORY_HPP

#include <string>
#include <iostream>
#include "pencilFactory.hpp"
#include "testPencilFactory.hpp"
#include "assertionHelper.hpp"
#include "testCases.hpp"

class TestPencilAction{

	public:
		TestPencilAction(std::string initInputAction, std::string initInputText, std::string initExpectedResult);
		bool performAction(Pencil * pencil);
		TestPencilAction * getNextAction();
		bool setNextAction(TestPencilAction * incomingAction);

	private:
		std::string inputAction;
		std::string inputText;
		std::string expectedResult;

		TestPencilAction * nextAction = NULL;
};


class TestPencilFactory{

	public:
		TestPencilFactory(unsigned int pencilLength, unsigned int pointDurability, unsigned int eraserDurability, WritingBoard * incomingWritingBoard);
		~TestPencilFactory();
		bool addTest(std::string inputAction, std::string inputText, std::string expectedResult);
		bool runAllTests();

	private:	
		TestPencilAction * headAction;
		TestPencilAction * currentAction;
		Pencil * pencil;
		
};

bool performTests();

#endif

