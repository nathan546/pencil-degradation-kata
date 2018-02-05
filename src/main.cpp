#include <string>
#include <iostream>
#include "main.hpp"
#include "pencilFactory.hpp"

int main (void){
	return productionDemonstration();
}

static bool productionDemonstration(){
	int writingRepetitions;
	WritingBoard writingBoard;
	Pencil * pencil;

	unsigned int pencilLength = 1, pointDurability = 10000, eraserDurability = 10000;

	pencil = new Pencil(pencilLength, pointDurability, eraserDurability);
	pencil->setWritingBoard(&writingBoard);

	for(writingRepetitions = 0; writingRepetitions < CHALKBOARD_PUNISHMENT_COUNT; writingRepetitions++){
		pencil->writeText(repetitionPhrase);
	}

	pencil->eraseText("test case");

	pencil->editText("...");

	std::cout << pencil->readText() << std::endl;

	delete pencil;
}
