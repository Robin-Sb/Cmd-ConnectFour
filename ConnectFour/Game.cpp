#include "Game.h"

Game::Game () {
	for (int row{ 0 }; row < std::size(field); row++) {
		for (int column{ 0 }; column < std::size(field[row]); column++) {
			field[row][column] = Field_Content { empty };
		}
	}
}

bool Game::isValidField(int row, int column) {
	if (row > 6 || row < 0 || column > 7 || column < 0)
		return false;
	else
		return true;
}

bool Game::isSameColor(int row, int column, bool isRedTurn) {
	if (isRedTurn) {
		if (field[row][column] == Field_Content::red) {
			return true;
		}
	} else {
		if (field[row][column] == Field_Content::yellow) {
			return true;
		}
	}
	return false;
}

bool Game::checkIfFilled() {
	for (int row{ 0 }; row < std::size(field); row++) {
		for (int column{ 0 }; column < std::size(field[row]); column++) {
			if (field[row][column] == Field_Content::empty) {
				return false;
			}
		}
	}
	return true;
}

int Game::findExtendOfDirection(int row, int column, bool isRedTurn, Game::transitions transition) {
	bool done{ false };
	int extend{ 0 };
	while (!done) {
		transition(row, column);
		if (isValidField(row, column) && isSameColor(row, column, isRedTurn)) {
			extend++;
		}
		else {
			done = true;
		}
	}
	return extend;
}

bool Game::check4Connected(int row, int column, bool isRedTurn) {
	int bottom_extend = findExtendOfDirection(row, column, isRedTurn, [](int &rw, int &clmn) -> void {rw++; });
	int bottom_left_extend = findExtendOfDirection(row, column, isRedTurn, [](int& rw, int& clmn) -> void {rw++; clmn--; });
	int bottom_right_extend = findExtendOfDirection(row, column, isRedTurn, [](int& rw, int& clmn) -> void {rw++; clmn++; });
	int top_left_extend = findExtendOfDirection(row, column, isRedTurn, [](int& rw, int& clmn) -> void {rw--; clmn--; });
	int top_right_extend = findExtendOfDirection(row, column, isRedTurn, [](int& rw, int& clmn) -> void {rw--; clmn++; });
	int right_extend = findExtendOfDirection(row, column, isRedTurn, [](int& rw, int& clmn) -> void {clmn++; });
	int left_extend = findExtendOfDirection(row, column, isRedTurn, [](int& rw, int& clmn) -> void {rw++; });

	if (bottom_extend >= 3)
		return true;
	if (bottom_left_extend + top_right_extend >= 3)
		return true;
	if (bottom_right_extend + top_left_extend >= 3)
		return true;
	if (right_extend + left_extend >= 3)
		return true;
	return false;
}

GameState Game::insertStone(bool isRedTurn, int column) {
	int found_row{-1};
	for (int row{ static_cast<int>(std::size(field)) - 1 }; row >= 0; row--) {
		if (field[row][column] == Field_Content::empty) {
			found_row = row;
			if (isRedTurn)
				field[row][column] = Field_Content::red;
			else
				field[row][column] = Field_Content::yellow;
			break;
		}
	}
	GameState gs;
	gs.columnFilled = false;
	bool are4Connected = false;
	if (found_row == -1) {
		gs.columnFilled = true;
	}
	else {
		are4Connected = check4Connected(found_row, column, isRedTurn);
	}
	gs.playerWon = are4Connected;
	return gs;
}

std::string Game::printBoard() {
	std::string output{""};
	for (int row{ 0 }; row < std::size(field); row++) {
		output += "|";
		for (int column{ 0 }; column < std::size(field[row]); column++) {
			if (field[row][column] == Field_Content::red) {
				output += "r";
			}
			else if (field[row][column] == Field_Content::yellow) {
				output += "y";
			}
			else {
				output += " ";
			}
			output += "|";
		}
		output += "\n";
	}
	return output;
}