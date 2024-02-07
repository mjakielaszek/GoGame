/*
 * template for the course Podstawy Programowania
 * only to be used for the project in this course
 * author: K.M. Ocetkiewicz
 */
#ifndef CONIO2_H
#define CONIO2_H

#define NAME 50			//maximum save name length
#define TEXTX 1			//coordinates of the beggining of the menu
#define TEXTY 1

#define STARTX 40		//sets coordinates of the left top corner of the board
#define STARTY 2

#define COLOR1     0		//colors of the players
#define COLOR2		15
#define BACKGROUND	6		//background color
#define OUTLINE 219			//outline color
#define STONE 64			//stone symbol

#define ENTER 0x0d			//keybinds which appear more frequently
#define I 0x69
#define H 0x68

#define BLACK		0
#define BLUE		1
#define GREEN		2
#define CYAN		3
#define RED			4
#define MAGENTA		5
#define BROWN		6
#define LIGHTGRAY	7
#define DARKGRAY	8
#define LIGHTBLUE	9
#define LIGHTGREEN	10
#define LIGHTCYAN	11
#define LIGHTRED	12
#define LIGHTMAGENTA	13
#define YELLOW		14
#define WHITE		15

#define _NOCURSOR	0
#define _SOLIDCURSOR	1
#define _NORMALCURSOR	2

#ifndef EOF
#define EOF		-1
#endif
#define SIZE		30
#define LASTMODE	-1
#define C80		3
#define C4350		8

#define STAR 42
#define CROSS 158

#define LEFTTOP 218
#define TOP 194
#define RIGHTTOP 191

#define LEFT 195
#define MIDDLE 197
#define RIGHT 180

#define LEFTBOTTOM 192
#define BOTTOM 193
#define RIGHTBOTTOM 217

extern int _wscroll;		// 1 = enable scroll
// 0 = disable scroll

struct text_info {
	unsigned char curx;
	unsigned char cury;
	unsigned short attribute;
	unsigned short normattr;
	unsigned char screenwidth;
	unsigned char screenheight;
};

#ifdef __cplusplus
extern "C" {
#endif
	void gotoxy(int x, int y);		// move cursor to the position (x,y)
	int wherex(void);			// return x coordinate of the cursor
	int wherey(void);			// return y coordinate of the cursor 
	void _setcursortype(int cur_t);		// set cursor type: _NOCURSOR, _SOLIDCURSOR or _NORMALCURSOR

	void textattr(int newattr);		// set foreground and background color at once (newattr = background * 16 + foreground)
	void textbackground(int newcolor);	// set background color of new characters
	void textcolor(int newcolor);		// set foreground color of new characters

	void clreol(void);			// clear till the end of current line
	void clrscr(void);			// clear entire screen
	void delline(void);			// delete current line
	void insline(void);			// insert empty line at cursor position

	int getch(void);			// wait for keyboard input and return the read character
	int getche(void);			// as above, but also write the read character to screen
	int kbhit(void);			// test if a key was pressed; if kbhit returns nonzero,
	// the next getch will return immediately
	int ungetch(int ch);			// return character ch to input buffer; the
	// next getch will return this character

	int cputs(const char* str);		// write string str to screen at current cursor position
	int putch(int c);			// write single character to screen at current cursor position

	// save a portion of screen to buffer dest; dest must be large enough to hold
	// two bytes per every saved character
	int gettext(int left, int top, int right, int bottom, void* dest);
	// write a saved portion from buffer to screen
	int puttext(int left, int top, int right, int bottom, void* source);
	// move a portion of screen to position (delstleft, desttop)
	int movetext(int left, int top, int right, int bottom, int destleft, int desttop);

	// get information about the state of screen
	// see the text_info structure
	void gettextinfo(struct text_info* info);

	// set screen size: C80, C4350 or LASTMODE
	void textmode(int mode);

	// bonus functions
	void settitle(const char* title);

	int Conio2_Init(void);

	void printingMenu();						//printing the controls
	void menuSize();							//printing the size choice menu
	void printingCoords(int x, int y);
	void printingScore(int scoreP1, int scoreP2);

	void printingBoard(int** board, int size);	//printing boards
	void printingTop(int size);					//printing the top row of the board
	void printingMiddle(int y, int size);		//printing the middle of the board
	void printingBottom(int size);				//printing the bottom row of the board
	void printingStones(int** board, int size);	//printing stones on the board
	void printingOutline(int size);				//printing outline of the board

	void printingInfo(bool takenplace, bool invalidplacement, bool hMode, bool hAllowed, int size, bool ko);	//checking if any rule has been violatego to print the info
	void newGame(int** board, int size);			//resets a certain array
	void newBoards(int** board, int** whiteBoard, int** blackBoard, int size);		//resets all the boards
	void movement(int* zero, int* zn, int* y, int* x, int size);

	int checkLiberties(int** board, int i, int j, int x, int size);			//checks liberties of a given coords using the ones below
	int leftLiberty(int** board, int i, int j, int x);			
	int rightLiberty(int** board, int i, int j, int x, int size);
	int lowerLiberty(int** board, int i, int j, int x, int size);
	int upperLiberty(int** board, int i, int j, int x);

	int checkKill(int** board, int x, int y, int* z, int* m, int size, int* scoreP1, int* scoreP2);		//checks if a stone destroys any surrounding while placing
	int confirmOrCancel(int x, int y, int size);		
	
	void settingStones(int** board, int x, int y, bool* player1, int* z);		//places the stones on the main board
	void checkKo(int** board, int** colorBoard, int** backupBoard, int size, bool* ko, bool* player1);		//checks for ko rule violation
	void infoOff(bool* takenplace, bool* invalidplacement, bool* ko);			//resets the rule violation info after a successfull placement

	void readFileName(char name[NAME], int x, int y);		
	void gameEndInfo(int size, int scoreP1, int scoreP2);		

	void checkingH(int size, int** board, bool* player1, bool* hAllowed);		//checks if any stones have been placed in hmode to know if it can be used again
	void checkStones(int** board, int size, int* scoreP1, int* scoreP2);		//checks all stones for breaths 
	void setCursor(int size, int* x, int* y);									//sets cursor in the middle of the board
	void customSize(int* size);
	void handicapPlacement(int** board, bool* takenplace, int x, int y);		//places stones in hMode
	void gameSave(int** board, int** whiteBoard, int** blackBoard, int scoreP1, int scoreP2, int player, int size);
	void gameLoad(int** board, int** whiteBoard, int** blackBoard, int* scoreP1, int* scoreP2, int* player, int size);		
	void cursorDisplay(int x, int y, bool player1, int symbol);
	void initializeBoards(int size, int** board, int** whiteBoard, int** blackBoard);
	void freeMemory(int** board1, int** board2, int** board3);
	
#ifdef __cplusplus
}
#endif
#endif