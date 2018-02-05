#include <exception>
#include "testPencilFactory.hpp"
#include "assertionHelper.hpp"

int main (void){
	//Exit code of 0 for success, otherwise 1
	return performTests();
}

bool performTests(){
	bool status;

	RESET_ASSERTION_STATISTICS();

	std::cout << std::endl << "Running all tests which are contained within tests/testCases.hpp" << std::endl;

	for(TestSuite &currentSuite : testSuites){

		WritingBoard writingBoard;

		TestPencilFactory testPencilFactory(currentSuite.pencilLength, currentSuite.pointDurability, currentSuite.eraserDurability, &writingBoard);

		for(auto currentCase : currentSuite.testCases){
			status = testPencilFactory.addTest(currentCase.operation, currentCase.inputString, currentCase.expectedString);
			if(status == 0){
				return 1;
			}
		}

		status = testPencilFactory.runAllTests();
		if(status == 0){
			return 1;
		}
		
	}

	PRINT_ASSERTION_STATISTICS();

	if( HAVE_FAILURE() ){
		return 1;
	}else{
		return 0;
	}


}


TestPencilAction::TestPencilAction(std::string initInputAction, std::string initInputText, std::string initExpectedResult){
	inputAction = initInputAction;
	inputText = initInputText;
	expectedResult = initExpectedResult;
	nextAction = NULL;
}

bool TestPencilAction::performAction(Pencil * pencil){
	bool ret = 0;

	if(inputAction.compare("write") == 0){
			ret = pencil->writeText(inputText);
	}else if(inputAction.compare("erase") == 0){
			ret = pencil->eraseText(inputText);
	}else if(inputAction.compare("edit") == 0){
			ret = pencil->editText(inputText);
	}else if(inputAction.compare("sharpen") == 0){
			return pencil->sharpenPencil(); //Don't assert
	}

	ASSERT_EQUAL(pencil->readText(), expectedResult);

	return ret;

}

TestPencilAction * TestPencilAction::getNextAction(){
	return nextAction;
}

bool TestPencilAction::setNextAction(TestPencilAction * incomingAction){
	if(nextAction == NULL){
		nextAction = incomingAction;
		return 1;
	}else{
		//Somebody has lost their mind!  Please don't leak memory!
		return 0;
	}
}



TestPencilFactory::TestPencilFactory(unsigned int pencilLength, unsigned int pointDurability, unsigned int eraserDurability, WritingBoard * incomingWritingBoard){

	try{
		pencil = new Pencil(pencilLength, pointDurability, eraserDurability);
	}catch(std::exception& e){
		std::cout << e.what() << std::endl;
	}

	pencil->setWritingBoard(incomingWritingBoard);
	headAction = NULL;

}

TestPencilFactory::~TestPencilFactory(){
	TestPencilAction * nextAction;

	if(headAction != NULL){
		currentAction = headAction;

		do{
			nextAction = currentAction->getNextAction();
			delete currentAction;
			currentAction = nextAction;
		}while(nextAction != NULL);

	}

}


bool TestPencilFactory::runAllTests(){
	TestPencilAction * nextAction;

	if(headAction != NULL){
		currentAction = headAction;

		do{
			nextAction = currentAction->getNextAction();

			if(!currentAction->performAction(pencil)){
				return 0;
			}

			currentAction = nextAction;
		}while(nextAction != NULL);

	}

	return 1;
}

bool TestPencilFactory::addTest(std::string initInputAction, std::string initInputText, std::string initExpectedResult){

	TestPencilAction * tempAction;

	try{
		tempAction = new TestPencilAction(initInputAction, initInputText, initExpectedResult);
	}catch(std::exception& e){
		std::cout << e.what() << std::endl;
		return 0;
	}

	if(headAction == NULL){
		headAction = tempAction;
		currentAction = tempAction;
	}else{
		if(currentAction->setNextAction(tempAction)){
			currentAction = tempAction;
		}else{
			return 0;
		}
		
	}

	return 1;
}