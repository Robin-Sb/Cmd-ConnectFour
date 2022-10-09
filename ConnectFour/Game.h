#pragma once
#include <functional>
#include <string>
#include "GameState.h"

enum Field_Content {
	red,
	yellow,
	empty
};


class Game {
	public:
		Game();
		typedef void (*transitions)(int& row, int& column);
		GameState insertStone(bool isRedTurn, int column);
		std::string printBoard();
		bool checkIfFilled();
	private:
		int findExtendOfDirection(int row, int column, bool isRedTurn, transitions transition);
		bool check4Connected(int row, int column, bool isRedTurn);
		bool isValidField(int row, int column);
		bool isSameColor(int row, int column, bool isRedTurn);
		// 7 colums, 6 rows for gamefield
		Field_Content field[6][7];
};