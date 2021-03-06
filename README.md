# Lii Framework
Lii framework is an open source framework which allows you to create interactive desktop applications on windows platform with ease.

## Documentation
You can access an up to date version of the documentation here:
[Doxygen generated documentation](https://erik9631.github.io/WinFramework/html/index.html)

## Installation
### Make sure you have the latest Visual Studio version!
1. Download the file from the release tab.
2. Extract it somewhere to your disk.
3. In visual studio, point the compiler to the include/header directory where you extracted your zip.
	- This is found under C/C++ > General > Additional Include Directories.
4. Point the compiler to the .lib file located in the include directory.
	- This is found under Linker > General > Additional Library Directories
5. Include the lib in the additional dependencies.
	- This is located under Linker > Input > Additional Dependencies.
	- Type in the name of the lib (Lii.lib for release and LiiDebug.lib for debug configuration)
6. Under Linker > System change the subsystem type to Windows Application
7. Under C/C++ > General set the language version to C++17
	
## Entry point
Once everything is linked, you can create your first source file.
include the WinWrapper.h header and define the entry point.
An example of a bare-bone entry point:
```C++
#include <WinWrapper.h> // Needed
#include <ApplicationController.h>
int LiiEntry()
{
	ApplicationController::JoinThreads();
	return 0;
}
```

