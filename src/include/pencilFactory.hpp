#ifndef PENCIL_HPP

#define PENCIL_HPP

#include <string>
#include <iostream>

	class UnidirectionalDegradationCounter{
		protected:
			UnidirectionalDegradationCounter(unsigned int initialDegradationValue);

			void decrementDegradation();
			unsigned int getDegradationValue();
		private:
			unsigned int degradationValue;
	};


	class WritingBoard {
		friend class Pencil;

		private:
			std::string readText();
			bool writeText(std::string writeText);
			bool eraseText(std::string eraseText);
			bool editText(std::string editText);
			std::string currentText;

			bool editingOverlappingText(std::string editText, int overlappedCharCount);
			bool erasedEndOfCurrentString();
			unsigned int lastErasePosition;
			unsigned int lastEraseSize;
	};

	class GraphitePoint : UnidirectionalDegradationCounter{
		friend class Pencil;

		private:
			GraphitePoint(unsigned int graphitePointDurability) : UnidirectionalDegradationCounter(graphitePointDurability){};

			void performDegradation(std::string &degradeText);
	};

	class Eraser : UnidirectionalDegradationCounter{
		friend class Pencil;

		private:
			//Constructor
			Eraser(unsigned int eraserDurability) : UnidirectionalDegradationCounter(eraserDurability){};

			unsigned int performDegradation(std::string &degradeText);
	};

	class Pencil : UnidirectionalDegradationCounter{
		public:
			Pencil(unsigned int pencilLength, unsigned int pointDurability, unsigned int eraserDurability);
			~Pencil();

			std::string readText();
			bool writeText(std::string writeText);
			bool eraseText(std::string eraseText);
			bool editText(std::string editText);
			bool setWritingBoard(WritingBoard * incomingWritingBoard);
			bool sharpenPencil();

		private:
			WritingBoard  * writingBoard;
			GraphitePoint * pencilPoint;
			Eraser        * pencilEraser;
			unsigned int pointDurabilityInitial;

	};

#endif