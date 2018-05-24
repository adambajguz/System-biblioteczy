/*
 *  (C) Adam Bajguz - 2017y.
 *
 *  eCW_graphics.h library continues the development of newconio.h library
 *
 *  Library is based on:
 *  #1 -> https://msdn.microsoft.com/en-us/library/windows/desktop/ms682073(v=vs.85).aspx
 *  #2 -> http://stackoverflow.com/questions/33975912/how-to-set-console-font-to-raster-font-programmatically
 *  #3 newconio.h library -> http://eduinf.waw.pl/inf/utils/010_2010/1003.php
 *
 */

#include "eCW_graphics.h"

/*
 *   This part of library is the original newconio.h library with some minor
 *   improvments, changes and English translation made by Adam Bajguz in 2014y.
 */

static WORD   _txattr;
static HANDLE _hcout,_hcin;

// Function that initializes the librarry and sets the input and output code page in the console window
//------------------------------------------------------------------------------------------------------
// code_page - code page (852 - standard)
//------------------------------------------------------------------------------------------------------
void _cinit(unsigned int code_page)
{
    _hcout = GetStdHandle(STD_OUTPUT_HANDLE);
    _hcin  = GetStdHandle(STD_INPUT_HANDLE);
    //SetConsoleOutputCP(1250);
    //SetConsoleOutputCP(852);
    SetConsoleOutputCP(code_page);
    //SetConsoleCP(1250);
    //SetConsoleCP(852);
    SetConsoleCP(code_page);
    _txattr = 0x07;
}


// This function that clears entire console.
//-------------------------------------------
void clrscr()
{
    COORD cpos = {0, 0};
    DWORD cwrt;
    CONSOLE_SCREEN_BUFFER_INFO cinf;
    DWORD csize;

    if(!GetConsoleScreenBufferInfo(_hcout, &cinf)) return;
    csize = cinf.dwSize.X * cinf.dwSize.Y;
    if(!FillConsoleOutputCharacter(_hcout,' ',csize,cpos,&cwrt)) return;
    if(!FillConsoleOutputAttribute(_hcout,_txattr,csize,cpos,&cwrt)) return;
    SetConsoleCursorPosition(_hcout, cpos);
    SetConsoleTextAttribute(_hcout,_txattr);
}

// This function fills an area of the console window using given color attribute.
//
// Position of the cursor and characters in the area will be not changed.
// -------------------------------------------------------------------------------
// bfcolor - color attribute to fill the area
// xb, yb - the coordinates of the upper left corner
// xe, ye - the coordinates of the lower right corner
//--------------------------------------------------------------------------------
void fillrectattr(short bfcolor, short xb, short yb, short xe, short ye)
{
    CONSOLE_SCREEN_BUFFER_INFO cinf;
    COORD pos;
    DWORD crd;

    if(!GetConsoleScreenBufferInfo(_hcout, &cinf)) return;
    if((xb >= cinf.dwSize.X) || (yb >= cinf.dwSize.Y) ||
            (xe < xb) || (ye < yb) || (xe < 0) || (ye < 0)) return; // outside the window
    if(xb < 0) xb = 0;
    if(yb < 0) yb = 0;
    if(xe >= cinf.dwSize.X) xe = cinf.dwSize.X - 1;
    if(ye >= cinf.dwSize.Y) ye = cinf.dwSize.Y - 1;
    DWORD len = xe - xb + 1;
    pos.X = xb;
    for(int i = yb; i <= ye; ++i)
    {
        pos.Y = i;
        FillConsoleOutputAttribute(_hcout, bfcolor, len, pos, &crd);
    }
}

// This function fills an area of the console window with given character.
//
// Position of the cursor and color atributes in the area will not be changed.
//-----------------------------------------------------------------------------
// c - character to fill the area
// xb, yb - the coordinates of the upper left corner
// xe, ye - the coordinates of the lower right corner
//-----------------------------------------------------------------------------
void fillrectch(TCHAR c, short xb, short yb, short xe, short ye)
{
    CONSOLE_SCREEN_BUFFER_INFO cinf;
    COORD pos;
    DWORD crd;

    if(!GetConsoleScreenBufferInfo(_hcout, &cinf)) return;
    if((xb >= cinf.dwSize.X) || (yb >= cinf.dwSize.Y) ||
            (xe < xb) || (ye < yb) || (xe < 0) || (ye < 0)) return; // outside the window
    if(xb < 0) xb = 0;
    if(yb < 0) yb = 0;
    if(xe >= cinf.dwSize.X) xe = cinf.dwSize.X - 1;
    if(ye >= cinf.dwSize.Y) ye = cinf.dwSize.Y - 1;
    DWORD len = xe - xb + 1;
    pos.X = xb;
    for(int i = yb; i <= ye; ++i)
    {
        pos.Y = i;
        FillConsoleOutputCharacter(_hcout, c, len, pos, &crd);
    }
}

// This function fills an area of the console window with given character and attribute.
//
// Position of the cursor will not be changed.
//---------------------------------------------------------------------------------------
// c - character to fill the area
// bfcolor - color attribute to fill the area
// xb, yb - the coordinates of the upper left corner
// xe, ye - the coordinates of the lower right corner
//---------------------------------------------------------------------------------------
void fillrect(TCHAR c, short bfcolor, short xb, short yb, short xe, short ye)
{
    CONSOLE_SCREEN_BUFFER_INFO cinf;
    COORD pos;
    DWORD crd;

    if(!GetConsoleScreenBufferInfo(_hcout, &cinf)) return;
    if((xb >= cinf.dwSize.X) || (yb >= cinf.dwSize.Y) ||
            (xe < xb) || (ye < yb) || (xe < 0) || (ye < 0)) return; // outside the window
    if(xb < 0) xb = 0;
    if(yb < 0) yb = 0;
    if(xe >= cinf.dwSize.X) xe = cinf.dwSize.X - 1;
    if(ye >= cinf.dwSize.Y) ye = cinf.dwSize.Y - 1;
    DWORD len = xe - xb + 1;
    pos.X = xb;
    for(int i = yb; i <= ye; ++i)
    {
        pos.Y = i;
        FillConsoleOutputCharacter(_hcout, c, len, pos, &crd);
        FillConsoleOutputAttribute(_hcout, bfcolor, len, pos, &crd);
    }
}

// This function draws a rectangular frame.
//------------------------------------------------------
// type - specifies the type of frame. Available types:
//        FRAME_EMPTY,
//        FRAME_SINGLE,
//        FRAME_DOUBLE,
//        FRAME_SOLID,
//        FRAME_SHADED.
// bfcolor - color attribute to fill the area
// xb, yb - the coordinates of the upper left corner
// xe, ye - the coordinates of the lower right corner
//------------------------------------------------------
void frame(enum FRAMES type, short bfcolor, short xb, short yb, short xe, short ye)
{
    unsigned char c = 32;

    if((xb >= xe) || (yb >= ye)) return;

    switch(type) // upper left corner
    {
    case FRAME_EMPTY :
        c =  32;
        break;
    case FRAME_SINGLE:
        c = 218;
        break;
    case FRAME_DOUBLE:
        c = 201;
        break;
    case FRAME_SOLID :
        c = 219;
        break;
    case FRAME_SHADED:
        c = 177;
        break;
    }
    fillrect(c, bfcolor, xb, yb, xb, yb);

    switch(type) // lower left corner
    {
    case FRAME_SINGLE:
        c = 192;
        break;
    case FRAME_DOUBLE:
        c = 200;
        break;
    }
    fillrect(c, bfcolor, xb, ye, xb, ye);

    switch(type) // upper right corner
    {
    case FRAME_SINGLE:
        c = 191;
        break;
    case FRAME_DOUBLE:
        c = 187;
        break;
    }
    fillrect(c, bfcolor, xe, yb, xe, yb);

    switch(type) // lower right corner
    {
    case FRAME_SINGLE:
        c = 217;
        break;
    case FRAME_DOUBLE:
        c = 188;
        break;
    }
    fillrect(c,bfcolor,xe,ye,xe,ye);

    switch(type) // top and bottom
    {
    case FRAME_SINGLE:
        c = 196;
        break;
    case FRAME_DOUBLE:
        c = 205;
        break;
    }
    fillrect(c, bfcolor, xb + 1, yb, xe - 1, yb);
    fillrect(c, bfcolor, xb + 1, ye, xe - 1, ye);

    switch(type) // left and right
    {
    case FRAME_SINGLE:
        c = 179;
        break;
    case FRAME_DOUBLE:
        c = 186;
        break;
    }
    fillrect(c, bfcolor, xb, yb + 1, xb, ye - 1);
    fillrect(c, bfcolor, xe, yb + 1, xe, ye - 1);
}

// This function draws a filled rectangular box.
//------------------------------------------------------
// type - specifies the type of frame. Available types:
//        FRAME_EMPTY,
//        FRAME_SINGLE,
//        FRAME_DOUBLE,
//        FRAME_SOLID,
//        FRAME_SHADED.
// bfcolor - color attribute to fill the area
// xb, yb - the coordinates of the upper left corner
// xe, ye - the coordinates of the lower right corner
//------------------------------------------------------
void fillframe(enum FRAMES type, short bfcolor, short xb, short yb, short xe, short ye)
{
    frame(type, bfcolor, xb, yb, xe, ye);
    fillrect(' ', bfcolor, xb+1, yb+1, xe-1, ye-1);
}

// This function reads the color attribute on the position (x, y).
//---------------------------------------------------------------
// x - horizontal position (0 - ...)
// y - vertical position (0 - ...)
//---------------------------------------------------------------
short getattrxy(short x, short y)
{
    COORD pos = {x, y};
    WORD attr;
    DWORD crd;

    ReadConsoleOutputAttribute(_hcout, &attr, 1, pos, &crd);
    return attr;
}

// This function reads the character on the position (x, y).
//---------------------------------------------------------
// x - horizontal position (0 - ...)
// y - vertical position (0 - ...)
//---------------------------------------------------------
char getchxy(short x, short y)
{
    COORD pos = {x, y};
    TCHAR c;
    DWORD crd;

    ReadConsoleOutputCharacter(_hcout, &c, 1, pos, &crd);
    return c;
}

// This function writes color attribute on the position (x, y).
//
// Position of the cursor and character will not be changed.
//-------------------------------------------------------------
// bfcolor - color attribute
// x - horizontal position (0 - ...)
// y - vertical position (0 - ...)
//-------------------------------------------------------------
void putattrxy(short bfcolor, short x, short y)
{
    COORD pos = {x, y};
    DWORD cwrt;

    WriteConsoleOutputAttribute(_hcout, &bfcolor, 1, pos, &cwrt);
}

// This function writes character on the position (x, y).
//
// Position of the cursor and color atribute will not be changed.
//-----------------------------------------------------------
// c - character
// x - horizontal position (0 - ...)
// y - vertical position (0 - ...)
//-----------------------------------------------------------
void putchxy(TCHAR c, short x, short y)
{
    COORD pos = {x, y};
    DWORD cwrt;

    WriteConsoleOutputCharacter(_hcout, &c, 1, pos, &cwrt);
}

// This function writes character and color atribute on the position (x, y).
//
// Position of the cursor will not be changed.
//-------------------------------------------------------------------------
// c - character
// bfcolor - color attribute
// x - horizontal position (0 - ...)
// y - vertical position (0 - ...)
//-------------------------------------------------------
void putxy(TCHAR c, short bfcolor, short x, short y)
{
    COORD pos = {x, y};
    DWORD cwrt;

    WriteConsoleOutputCharacter(_hcout, &c, 1, pos, &cwrt);
    WriteConsoleOutputAttribute(_hcout, &bfcolor, 1, pos, &cwrt);
}

// This function writes color atribute on the postiton (x, y).
//-----------------------------------------------------------
// bfcolor - color attribute
//-----------------------------------------------------------
void textattr(short bfcolor)
{
    _txattr = bfcolor & 0xff;
    SetConsoleTextAttribute(_hcout, _txattr);
}

/*
 *   =============================================================================
 */




/*
 *   This part of library was made by Adam Bajguz in 2014y. and improved in 2017y.
 */

// This function sets the default color of the console
//-----------------------------------------------------
// bfcolor - color attribute
//-----------------------------------------------------
void setDcolor()
{
    _txattr = 0x07;
    SetConsoleTextAttribute(_hcout, _txattr);
}

// This function sets color atribute
//-----------------------------------
// bfcolor - color attribute
//-----------------------------------
void setcolor(short bfcolor)
{
    _txattr = bfcolor;
    SetConsoleTextAttribute(_hcout, _txattr);
}

// This function returns color atribute.
//-----------------------------------------
// background - background color attribute
// foreground - foreground color attribute
//-----------------------------------------
short bfcolor(enum COLORS background, enum COLORS foreground)
{
    return ((background << 4) + foreground);
}


// This function sets console font to default Terminal Raster 8x12 font
//----------------------------------------------------------------------
void cDEFAULT_FONT()
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize=sizeof(cfi);
    cfi.dwFontSize.X=8;
    cfi.dwFontSize.Y=12;
    wcscpy(cfi.FaceName, L"Terminal");
    cfi.FontFamily=FF_DONTCARE;
    cfi.FontWeight=FW_NORMAL;
    cfi.nFont=0;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

// This function sets console window size and position
//------------------------------------------------------
// x - horizontal size (0 - ...)
// y - vertical size (0 - ...)
// left_pos - position in pixels from left screen edge
// top_pos - position in pixels from top screen edge
//------------------------------------------------------

void cSIZE(short x, short y, short left_pos, short top_pos)
{
    SMALL_RECT test;

    test.Left = left_pos;
    test.Top = top_pos;
    test.Right = x*12;
    test.Bottom = y*8;
    SetConsoleWindowInfo(_hcout, false, &test);


//    RECT r;
//    GetWindowRect(_hcout, &r);
//    r.left = left_pos;
//    r.top = top_pos;
//    //MoveWindow(console, r.left, r.top, x*10, (y+20)*10, TRUE); ///old method
//    //MoveWindow(console, r.left, r.top, x*20, y*20, TRUE); /// new method
//    MoveWindow(_hcout, r.left, r.top, (x+5)*8, (y+5)*12, TRUE); //100% working method
}

// This function returns the size of the console window
//------------------------------------------------------
POINT cGetSIZE()
{
    CONSOLE_SCREEN_BUFFER_INFO cinf;
    POINT csize;

    GetConsoleScreenBufferInfo(_hcout, &cinf);
    csize.x = cinf.dwSize.X;
    csize.y = cinf.dwSize.Y;

    return csize;
}

// This function sets console buffer size
//----------------------------------------
// x - horizontal size (0 - ...)
// y - vertical size (0 - ...)
//----------------------------------------
void cBUFFER(short x, short y)
{
    COORD c = {x, y};
    SetConsoleScreenBufferSize(_hcout, c);
}

// This function sets console title
//----------------------------------
// str - title
//----------------------------------
void cTITLE(LPCTSTR str)
{
    SetConsoleTitleA(str);
}

// This function sets cursor atributes
//----------------------------------------------------------------------
// visible - visibility of the cursor (true = visible / false = hidden)
// csize - cursor size (20 - default size)
//----------------------------------------------------------------------
void cCURSOR(bool visible, short csize)
{
    CONSOLE_CURSOR_INFO ccinfo;
    ccinfo.dwSize = csize;
    ccinfo.bVisible = visible;
    SetConsoleCursorInfo(_hcout, & ccinfo);
}

// This function moves the cursor to the postiton (x, y).
//----------------------------------------------------------------------
// visible - visibility of the cursor (true = visible / false = hidden)
// csize - cursor size
//----------------------------------------------------------------------
void gotoxy(short x, short y)
{
    COORD pos = {x,y};
    SetConsoleCursorPosition(_hcout, pos);
}

void cPRINT_FILL(short x, short y, short dimx, short dimy, short background)
{
    setcolor(bfcolor(background, background));
    ++x;
    ++y;
    short a=ceil(dimy/2);
    dimx=dimx-2;
    dimy=dimy-2;

    for(short i=0; i<a; ++i)
    {
        putxy(' ', _txattr, x, y);
        putxy(' ', _txattr, x, y+dimy);

        for (short ax=x+1; ax <= x+dimx-1; ++ax)
        {
            putxy(' ', _txattr, ax, y);
            putxy(' ', _txattr, ax, y+dimy);
        }

        putxy(' ', _txattr, x+dimx, y);
        putxy(' ', _txattr, x+dimx, y+dimy);

        for (short ay=y+1; ay <= y+dimy-1; ++ay)
        {
            putxy(' ', _txattr, x, ay);
            putxy(' ', _txattr, x+dimx, ay);
        }

        ++x;
        ++y;
        dimx=dimx-2;
        dimy=dimy-2;
    }
}

void cPRINT_FRAME(short x, short y, short dimx, short dimy)
{
    putchxy(' ',x,y);
    putchxy(' ',x,y+dimy);

    for (short ax=x+1; ax <= x+dimx-1; ++ax)
    {
        putchxy(' ',ax,y);
        putchxy(' ',ax,y+dimy);
    }
    putchxy(' ',x+dimx,y);
    putchxy(' ',x+dimx,y+dimy);

    for (short ay=y+1; ay <= y+dimy-1; ++ay)
    {
        putchxy(' ',x,ay);
        putchxy(' ',x+dimx,ay);
    }
}

void cPRINT_RECTANGLE(short x, short y, short dimx, short dimy, short style, short border_background, short border_foreground)
{
    setcolor(bfcolor(border_background, border_foreground));

    unsigned char chars[6] = {201, 200, 205, 187, 188, 186};
    switch(style)
    {
    case 0:
        chars[0] = 32;
        chars[1] = 32;
        chars[2] = 32;
        chars[3] = 32;
        chars[4] = 32;
        chars[5] = 32;
        break;
    case 1:
        chars[0] = 218;
        chars[1] = 192;
        chars[2] = 196;
        chars[3] = 191;
        chars[4] = 217;
        chars[5] = 179;
        break;
    case 2:
        chars[0] = 201;
        chars[1] = 200;
        chars[2] = 205;
        chars[3] = 187;
        chars[4] = 188;
        chars[5] = 186;
        break;
    case 3:
        chars[0] = 219;
        chars[1] = 219;
        chars[2] = 219;
        chars[3] = 219;
        chars[4] = 219;
        chars[5] = 219;
        break;
    case 4:
        chars[0] = 176;
        chars[1] = 176;
        chars[2] = 176;
        chars[3] = 176;
        chars[4] = 176;
        chars[5] = 176;
        break;
    case 5:
        chars[0] = 177;
        chars[1] = 177;
        chars[2] = 177;
        chars[3] = 177;
        chars[4] = 177;
        chars[5] = 177;
        break;
    case 6:
        chars[0] = 178;
        chars[1] = 178;
        chars[2] = 178;
        chars[3] = 178;
        chars[4] = 178;
        chars[5] = 178;
        break;
    case 7:
        chars[0] = 250;
        chars[1] = 250;
        chars[2] = 250;
        chars[3] = 250;
        chars[4] = 250;
        chars[5] = 250;
        break;
    case 8:
        chars[0] = 158;
        chars[1] = 158;
        chars[2] = 158;
        chars[3] = 158;
        chars[4] = 158;
        chars[5] = 158;
        break;
    case 9:
        chars[0] = 207;
        chars[1] = 207;
        chars[2] = 207;
        chars[3] = 207;
        chars[4] = 207;
        chars[5] = 207;
        break;
    }
    putxy((char)chars[0], _txattr, x, y);
    putxy((char)chars[1], _txattr, x, y+dimy);


    for (short ax=x+1; ax <= x+dimx-1; ++ax)
    {
        putxy((char)chars[2], _txattr, ax, y);
        putxy((char)chars[2], _txattr, ax, y+dimy);
    }

    putxy((char)chars[3], _txattr, x+dimx, y);
    putxy((char)chars[4], _txattr, x+dimx, y+dimy);

    for (short ay=y+1; ay <= y+dimy-1; ++ay)
    {
        putxy((char)chars[5], _txattr, x, ay);
        putxy((char)chars[5], _txattr, x+dimx, ay);
    }
}

void cPRINT_LINE_H(short x, short y, char zn, short dimx, short background, short foreground)
{
    setcolor(bfcolor(background, foreground));
    for (short ax=x; ax <= x+dimx-1; ++ax)
    {
        putxy(zn, _txattr, ax, y);
    }
}

void cPRINT_LINE_V(short x, short y, char zn, short dimy, short background, short foreground)
{
    setcolor(bfcolor(background, foreground));
    for (short ay=y; ay <= y+dimy; ++ay)
    {
        putxy(zn, _txattr, x, ay);
    }
}
