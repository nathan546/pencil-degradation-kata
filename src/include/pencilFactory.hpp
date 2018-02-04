#ifndef PENCIL_HPP

#define PENCIL_HPP

#include <string>
#include <iostream>
	

	class WritingBoard {

		friend class Pencil;

		private:
			std::string readText();
			bool writeText(std::string writeText);
			bool editText(std::string editText);
			bool eraseText(std::string eraseText);

			std::string currentText;
	};



	class Pencil{
		public:
			Pencil();
			~Pencil();

			std::string readText();
			bool writeText(std::string writeText);
			bool setWritingBoard(WritingBoard * incomingWritingBoard);

		private:
			WritingBoard  * writingBoard;
	};

#endif