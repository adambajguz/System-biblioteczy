#ifndef VERSION_H
#define VERSION_H

	//Software Status
	static const char STATUS[] =  "Release";
	static const char STATUS_SHORT[] =  "r";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 0;
	static const long BUILD  = 5;
	static const long REVISION  = 8;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 5607;
	#define RC_FILEVERSION 1,0,5,8
	#define RC_FILEVERSION_STRING "1, 0, 5, 8\0"
	static const char FULLVERSION_STRING [] = "1.0.5.8";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 160;
	

#endif //VERSION_H
