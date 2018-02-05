#include <string>
#include <iostream>
#include "main.hpp"
#include "pencilFactory.hpp"

int main (void){
	return productionDemonstration();
}

static bool productionDemonstration(){
	bool ret = 1;
	int writingRepetitions;
	WritingBoard writingBoard;
	Pencil * pencil;

	unsigned int pencilLength = 1, pointDurability = 10000, eraserDurability = 10000;

	try{
		pencil = new Pencil(pencilLength, pointDurability, eraserDurability);
	}catch(std::exception& e){
		std::cout << e.what() << std::endl;
		return 1; //Error
	}

	ret &= pencil->setWritingBoard(&writingBoard);

	for(writingRepetitions = 0; writingRepetitions < CHALKBOARD_PUNISHMENT_COUNT; writingRepetitions++){
		ret &= pencil->writeText(repetitionPhrase);
		ret &= pencil->eraseText("test case\r\n");
		ret &= pencil->editText("useful and relevant test case\r\n");
	}

	std::cout << pencil->readText() << std::endl;

	try{
		delete pencil;
	}catch(std::exception& e){
		std::cout << e.what() << std::endl;
		return 1; //Error
	}

	if(ret == 0){
		return 1; //Error
	}else{
		return 0;
	}


}
