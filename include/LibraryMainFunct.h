#ifndef LIBRARYMAINFUNCT_H_INCLUDED
#define LIBRARYMAINFUNCT_H_INCLUDED

// File with Library Main Functions

#include <stdlib.h>
#include "./LibrarySettingsChoice.h"
#include "../version.h"

#define CCHOICE_SIZE 5
#define LAST_FILE "last.cfg"

void SetConfig(const MainConfig cfg); // Function that saves main app config to MAIN_CONFIG_FILE

_lib_ret Settings(int arg, FILE ** libfile, struct _lib_data * data); // Function that provides main app config changing menu
_lib_ret About(int arg, FILE ** libfile, struct _lib_data * data); // Function that prints informations about program

_lib_ret CloseLib(int arg, FILE ** libfile, struct _lib_data * data); // Function that closes opened library file
_lib_ret CloseApp(int arg, FILE ** libfile, struct _lib_data * data); // Function that exits from the program

_lib_ret NewFile(int arg, FILE ** libfile, struct _lib_data * data); // Function that creates new library file
_lib_ret LoadFile(int arg, FILE ** libfile, struct _lib_data * data); // Function that loads library file

const char * GetLastFile(void); // Function that returns last library filename
void SetLastFile(const char fname[256]); // Function that sets last libaray filename

#endif // LIBRARYMAINFUNCT_H_INCLUDED
