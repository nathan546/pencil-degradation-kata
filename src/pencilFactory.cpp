#include "pencilFactory.hpp"


Pencil::Pencil(){

}


Pencil::~Pencil(){
}


std::string Pencil::readText(){
	return writingBoard->readText();
}


bool Pencil::writeText(std::string writeText){
		return writingBoard->writeText(writeText);
}

bool Pencil::eraseText(std::string eraseText){
		return writingBoard->eraseText(eraseText);
}


bool Pencil::setWritingBoard(WritingBoard * incomingWritingBoard){
	if(incomingWritingBoard != NULL){
		writingBoard = incomingWritingBoard;
		return 1; 
	}
	return 0;
}










std::string WritingBoard::readText(){
	return currentText;
}

bool WritingBoard::writeText(std::string writeText){
	try{
		currentText += writeText; //just concatenate it in... easy!
		return 1;
	}catch(...){
		return 0;
	}

}

bool WritingBoard::eraseText(std::string eraseText){
	try{

		std::size_t findPosition;
		std::string replace;
		int length = eraseText.length();

		//Find the text we're trying to erase, starting from the reverse
		findPosition = currentText.rfind(eraseText);

		if(findPosition != std::string::npos){
			//We found the text, replace it with spaces for its full length
			currentText.replace(findPosition, length, length, ' ');
		}else{
			return 0;
		}

		return 1;

	}catch(...){
		return 0;
	}
}



