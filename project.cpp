#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"conio2.h"

int main() {
	char txt[32];
	int** board, **whiteBoard, **blackBoard;
	bool invalidplacement = false, hAllowed = true, hMode = false, takenplace = false, player1 = true, gameover = false, ko = false;
	int scoreP1 = 0, scoreP2 = 0, size = 0, player = 0, zn = 0, zero = 0, fControls = 0, sControls = 0, iControls = 0, z = 1, m = 0;
#ifndef __cplusplus
	Conio2_Init();
#endif
	settitle("Michal Jakielaszek, 193300");
	_setcursortype(_NOCURSOR);
	menuSize();
	while (size == 0) {
		sControls = getch();
		if (sControls == 0x31) size = 9;
		else if (sControls == 0x32) size = 13;
		else if (sControls == 0x33) size = 19;
		else if (sControls == 0x34) customSize(&size);
		else if (sControls == 'q') return 0;
	}
	board = (int**)malloc(size * sizeof(int*));				//main board for saving the positions
	whiteBoard = (int**)malloc(size * sizeof(int*));		//boards used for checking ko rule
	blackBoard = (int**)malloc(size * sizeof(int*));
	initializeBoards(size, board, whiteBoard, blackBoard);
	newBoards(board, whiteBoard, blackBoard, size);
	int x = STARTX + (size / 2), y = STARTY + (size / 2);
	do {
		textbackground(BLACK);
		clrscr();
		textcolor(7);
		printingMenu();
		printingCoords(x, y);
		printingScore(scoreP1, scoreP2);
		if (zero) sprintf(txt, "key code: 0x00 0x%02x", zn);
		else sprintf(txt, "key code: 0x%02x", zn);
		gotoxy(TEXTX, TEXTY + 11);
		cputs(txt);
		printingBoard(board, size);
		printingInfo(takenplace, invalidplacement, hMode, hAllowed, size, ko);
		textcolor(WHITE);
		cursorDisplay(x, y, player1, STAR);

		zero = 0;
		zn = getch();
		if (zn == 0) movement(&zero, &zn, &y, &x, size);
		else if (zn == H && hMode) {
			hMode = false;
			checkingH(size, board, &player1, &hAllowed);
		}
		else if (zn == H && hAllowed && !hMode) hMode = true;		
		else if (zn == I && hMode) handicapPlacement(board, &takenplace, x, y);	
		else if (zn == 0x6e) {			//restarting the game
			hAllowed = true;
			player1 = true;
			infoOff(&takenplace, &invalidplacement, &ko);
			newBoards(board, whiteBoard, blackBoard, size);
			setCursor(size, &x, &y);
		}
		else if (zn == I && !hMode) {		//setting stones out of hmode
			infoOff(&takenplace, &invalidplacement, &ko);
			cursorDisplay(x, y, player1, CROSS);
			if (player1) {								//player 1 has '1's
				if (board[x - STARTX][y - STARTY] != 2)    takenplace = true;
				else if (checkKill(board, x, y, &z, &m, size, &scoreP1, &scoreP2) == 1 || checkLiberties(board, x - STARTX, y - STARTY, z, size) == 0 || checkLiberties(board, x - STARTX, y - STARTY, z, size) == 2) {
					if (confirmOrCancel(x, y, size) == 0) {
						settingStones(board, x, y, &player1, &z);
						checkKo(board, blackBoard, whiteBoard, size, &ko, &player1);
						hAllowed = false;
					}
				}
				else if (checkLiberties(board, x - STARTX, y - STARTY, z, size) == 1) invalidplacement = true;
			}
			else if (!player1) {
				if (board[x - STARTX][y - STARTY] != 2)    takenplace = true;
				else if (checkKill(board, x, y, &m, &z, size, &scoreP1, &scoreP2) == 1 || checkLiberties(board, x - STARTX, y - STARTY, m, size) == 0 || checkLiberties(board, x - STARTX, y - STARTY, m, size) == 2) {
					if (confirmOrCancel(x, y, size) == 0) {
						settingStones(board, x, y, &player1, &m);
						checkKo(board, whiteBoard, blackBoard, size, &ko, &player1);
						hAllowed = false;
					}
				}
				else if (checkLiberties(board, x - STARTX, y - STARTY, z, size) == 1) invalidplacement = true;
			}
		}
		else if (zn == 'f') {		//ending the game
			gameEndInfo(size, scoreP1, scoreP2);
			while (fControls != 'q' && fControls != 'n') {
				fControls = getch();
				if (fControls == 'q') gameover = true;
				else if (fControls == 'n') {
					newGame(board, size);
					setCursor(size, &x, &y);
					hAllowed = true;
				}
			}
		}
		else if (zn == 0x73) {	//saving the game
			if (player1) player = 1;
			if (!player1) player = 0;
			gameSave(board, whiteBoard, blackBoard, scoreP1, scoreP2, player, size);
		}
		else if (zn == 'l') {	//running from a save 
			gameLoad(board, whiteBoard, blackBoard, &scoreP1, &scoreP2, &player, size);
			if (player == 0) player1 = true;
			if (player == 1) player1 = false;
			checkingH(size, board, &player1, &hAllowed);
		}
		else if (zn == 'q')	 gameover = true;
		checkStones(board, size, &scoreP1, &scoreP2);		//checking every stone for breaths at the end of each loop
	} while (gameover == false);
	freeMemory(board, whiteBoard, blackBoard);
	_setcursortype(_NORMALCURSOR);
	return 0;
}