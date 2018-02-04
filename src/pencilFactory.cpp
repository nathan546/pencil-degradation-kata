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



