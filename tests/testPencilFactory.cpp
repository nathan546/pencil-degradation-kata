#include "testPencilFactory.hpp"
#include "assertionHelper.hpp"

int main (void){
	//Exit code of 0 for success, otherwise 1
	return performTests();
}

bool performTests(){

	//Reset assertion success/failure count to zero
	RESET_ASSERTION_STATISTICS();

	//Create a new writing board
	WritingBoard writingBoard;

	//Instantiate a new pencil from the pencil factory
	TestPencilFactory testPencilFactory(&writingBoard);

	//Add the case to our test list
	testPencilFactory.addTest("write", "first test", "first test");

	//Execute all the test cases which were added
	testPencilFactory.runAllTests();

	//Print the success/failure count after running all our tests
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



TestPencilFactory::TestPencilFactory(WritingBoard * incomingWritingBoard){

	pencil = new Pencil();
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
	}catch(...){
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