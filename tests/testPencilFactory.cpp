#include <exception>
#include "testPencilFactory.hpp"
#include "assertionHelper.hpp"

int main (void){
	//Exit code of 0 for success, otherwise 1
	return performTests();
}

bool performTests(){

	RESET_ASSERTION_STATISTICS();

	std::cout << std::endl << "Running all tests which are contained within tests/testCases.hpp" << std::endl;

	for(TestSuite &currentSuite : testSuites){

		WritingBoard writingBoard;

		TestPencilFactory testPencilFactory(currentSuite.pencilLength, currentSuite.pointDurability, currentSuite.eraserDurability, &writingBoard);

		for(auto currentCase : currentSuite.testCases){
			testPencilFactory.addTest(currentCase.operation, currentCase.inputString, currentCase.expectedString);
		}

		testPencilFactory.runAllTests();

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

	if(inputAction.compare("write") == 0){
			pencil->writeText(inputText);
	}else if(inputAction.compare("erase") == 0){
			pencil->eraseText(inputText);
	}else if(inputAction.compare("edit") == 0){
			pencil->editText(inputText);
	}else if(inputAction.compare("sharpen") == 0){
			pencil->sharpenPencil();
			return 1; //Don't assert
	}

	ASSERT_EQUAL(pencil->readText(), expectedResult);

	return 1;

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


void TestPencilFactory::runAllTests(){
	TestPencilAction * nextAction;

	if(headAction != NULL){
		currentAction = headAction;

		do{
			nextAction = currentAction->getNextAction();
			currentAction->performAction(pencil);
			currentAction = nextAction;
		}while(nextAction != NULL);
		
	}
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
		currentAction->setNextAction(tempAction);
		currentAction = tempAction;
	}

	return 1;
}