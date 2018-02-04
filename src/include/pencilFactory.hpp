#ifndef PENCIL_HPP

#define PENCIL_HPP

#include <string>
#include <iostream>
	

	class WritingBoard {

		friend class Pencil;

		private:
			std::string readText();
			bool writeText(std::string writeText);
			bool eraseText(std::string eraseText);

			std::string currentText;
	};



	class Pencil{
		public:
			Pencil();
			~Pencil();

			std::string readText();
			bool writeText(std::string writeText);
			bool eraseText(std::string eraseText);
			bool setWritingBoard(WritingBoard * incomingWritingBoard);

		private:
			WritingBoard  * writingBoard;
	};

#endif