/*
 *  (C) Adam Bajguz - 2017y.
 *
 *  eCW_graphics.h library continues the development of newconio.h library
 *
 *  Librart is based on:
 *  #1 -> https://msdn.microsoft.com/en-us/library/windows/desktop/ms682073(v=vs.85).aspx
 *  #2 -> http://stackoverflow.com/questions/33975912/how-to-set-console-font-to-raster-font-programmatically
 *  #3 newconio.h library -> http://eduinf.waw.pl/inf/utils/010_2010/1003.php
 *
 *  Console palette colours changing in next version of library.
 */

#ifndef ECW_GRAPHICS_HPP_INCLUDED
#define ECW_GRAPHICS_HPP_INCLUDED

#include <stdbool.h>
#include <windows.h>
#include <math.h>

/*
 *   This part of library is the original newconio.h library with some minor
 *   improvments, changes and English translation made by Adam Bajguz in 2014y.
 */

// I Liceum Ogólnokształcące
// im. K. Brodzińskiego
// w Tarnowie
//----------------------------------------------------------------
// Koło informatyczne 2006/7
//----------------------------------------------------------------
// plik nagłówkowy dla procedur obsługi konsoli znakowej w Windows
//                 (C) 2006 mgr Jerzy Wałaszek
//----------------------------------------------------------------

enum COLORS
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    YELLOW,
    LIGHTGRAY,
    GRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    LIGHTYELLOW,
    WHITE
};

enum FRAMES
{
    FRAME_EMPTY,
    FRAME_SINGLE,
    FRAME_DOUBLE,
    FRAME_SOLID,
    FRAME_SHADED,
    cFRAME_SHADED2,
    cFRAME_SHADED3,
    cFRAME_DOTTED,
    cFRAME_x,
    cFRAME_x2
};

void _cinit();
void clrscr();
void fillrectattr(short bfcolor, short xb, short yb, short xe, short ye);
void fillrectch(TCHAR c, short xb, short yb, short xe, short ye);
void fillrect(TCHAR c, short bfcolor, short xb, short yb, short xe, short ye);
void frame(enum FRAMES type, short bfcolor, short xb, short yb, short xe, short ye);
void fillframe(enum FRAMES type, short bfcolor, short xb, short yb, short xe, short ye);
short getattrxy(short x, short y);
char getchxy(short x, short y);
void putattrxy(short bfcolor, short x, short y);
void putchxy(TCHAR c, short x, short y);
void putxy(TCHAR c, short bfcolor, short x, short y);
void scrollrect(short dir, short howfar, short xb, short yb, short xe, short ye);
void textattr(short bfcolor);

/*
 *   =============================================================================
 */



/*
 *   =============================================================================
 *   This part of library was made by Adam Bajguz in 2014y. and improved in 2017y.
 */

void setDcolor();
void setcolor(short bfcolor);
short bfcolor(enum COLORS background, enum COLORS foreground);
void cDEFAULT_FONT();
void cSIZE(short x, short y, short left_pos, short top_pos);
POINT cGetSIZE();
void cBUFFER(short x, short y);
void cTITLE(LPCTSTR str);
void cCURSOR(bool visible, short csize);
void gotoxy(short x, short y);
void cPRINT_FILL(short x, short y, short dimx, short dimy, short background);
void cPRINT_FRAME(short x, short y, short dimx, short dimy);
void cPRINT_RECTANGLE(short x, short y, short dimx, short dimy, short style, short border_background, short border_foreground);
void cPRINT_LINE_H(short x, short y, char c, short dimx, short background, short foreground);
void cPRINT_LINE_V(short x, short y, char zn, short dimy, short background, short foreground);


/*
 *   =============================================================================
 */


#endif // ECW_GRAPHICS_HPP_INCLUDED
