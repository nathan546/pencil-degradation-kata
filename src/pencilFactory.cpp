#include "pencilFactory.hpp"




GraphitePoint::GraphitePoint(unsigned int initialDegradationValue){
	degradationValue = initialDegradationValue;
}


void GraphitePoint::decrementDegradation(){
	if(degradationValue > 0) //This is an unsigned int -- don't let it accidently roll back over to 2^32!
		degradationValue--;
}


unsigned int GraphitePoint::getDegradationValue(){
	return degradationValue;
}


void GraphitePoint::performDegradation(std::string &degradeText){

	for(int i = 0; i < degradeText.length(); i++){

		if( isupper(degradeText[i]) ){

			if( getDegradationValue() < 2){
				degradeText[i] = ' '; //replace with space if we don't have enough point durability left
			}else{
				decrementDegradation();
				decrementDegradation();
			}

		}else if( islower(degradeText[i]) ){

			if( getDegradationValue() < 1){
				degradeText[i] = ' '; //replace with space if we don't have enough point durability left
			}else{
				decrementDegradation();
			}

		}

	}

}










Pencil::Pencil(unsigned int pointDurability){
	pencilPoint = new GraphitePoint(pointDurability);
}


Pencil::~Pencil(){
}


std::string Pencil::readText(){
	return writingBoard->readText();
}


bool Pencil::writeText(std::string writeText){
	if(writingBoard != NULL){
		pencilPoint->performDegradation(writeText);
		return writingBoard->writeText(writeText);
	}else{
		return 0;
	}
}

bool Pencil::eraseText(std::string eraseText){
		return writingBoard->eraseText(eraseText);
}

bool Pencil::editText(std::string editText){
	if(writingBoard != NULL){
		pencilPoint->performDegradation(editText);
		return writingBoard->editText(editText);
	}else{
		return 0;
	}
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
			lastErasePosition = findPosition;
			lastEraseSize = length;
		}else{
			return 0;
		}

		return 1;

	}catch(...){
		return 0;
	}
}

bool WritingBoard::editText(std::string editText){
	try{

		//Do we have a last position that was erased?  If not, we don't know where to put the new word!
		if(lastErasePosition != 0){

			int length = editText.length();
			int overlappedCharPos;
			int overlappedCharCount = length - lastEraseSize;

			if(overlappedCharCount <= 0){
				currentText.replace(lastErasePosition, length, editText);
			}else{

				//We don't have enough room to place the whole word, so place what we can first, up to the size of the last erased word
				currentText.replace(lastErasePosition, lastEraseSize, editText.substr(0, lastEraseSize));

				//Now step through the remaining characters and determine if they are to be the desired letter or an overlapped '@' character
				for(overlappedCharPos = 0; overlappedCharPos < overlappedCharCount; overlappedCharPos++){
					int currentEditPos = lastEraseSize+overlappedCharPos;
					int currentBoardPos = currentEditPos + lastErasePosition;

					if(editText[currentEditPos] != ' '){
						if(currentText[currentBoardPos] != editText[currentEditPos]){
							if( currentText[currentBoardPos] == ' ' ){
								currentText[currentBoardPos] = editText[currentEditPos];
							}else{
								currentText[currentBoardPos] = '@';
							}
						}
					}
					
				}

			}

			lastErasePosition = 0;
			lastEraseSize = 0;
			return 1;

		}else{
			return 0;
		}

	}catch(...){
		return 0;
	}
}



