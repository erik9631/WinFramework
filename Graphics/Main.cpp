﻿#include <codecvt>
#include "ApplicationController.h"
#include "WinWrapper.h" // Needed
#include "Button.h"
#include <Windows.h>
#include "WindowFrame.h"
#include "DemoApplication.h"
using namespace std;


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ApplicationController controller(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	int returnVal = LiiEntry();

	//Thread cleanup
	ApplicationController::JoinThreads();

	return returnVal;
}

/*
* TODO
* 1) Add OnActionEvent for buttons
* 2) Repaint not being used on pure renderable components. Investigate better design --- interface pollution
*	A) Repaint should notify the parent component which in return should send a repaint request
* 3) Create a global event class that has event src as parameter. All events MUST derive from that
* 9) Input is propagated by the root to whoever has the focus. To make the design consistent, each component should propagate the input to its subcomponents. The component recieving
*	 The event should then decide whether it should notify the subscribers or not (Based on IsFocus). Revisit this design and improve.
* 10) Every renderable should have scaling option and offset option. Either relative or relative with %
* 11) Make graphical element properties consistent
* 12) Renderables lack visibility option.
* 13) Renderables should have rendering order
* 14) Checkbox should be a graphical component on its own, similar to radio button
* 15) Matrix transformation reset applies to renderables on the same layer. Graphics is a POINTER!!!!! -- I think I fixed this??? lol
* 17) Behaviors should have setters and getters. They are strategy pattern and they should be run time hot swapable
* 18) Specialize the trackbar behavior to either vertical or horizontal
* 19) If parent component has focus and hovering over sub component, the parent doesn't recieve hover -- Should differentiate between OnHover and OnMove (One hovers when mouse within, the other when focused)
* 20) Fix InternalOffset calls causing massive slow down (Internal offset calls Element offset which causes updates, this is temporarily disabled for the sake of functionality)
*		Should be removed entirely. The offsets should be handled by the matrix you fucking moron
* 21) Duplicate methods. "Listener methods" leftover in the components. 
* 22) Wrap grid into a builder. The parameters should not be changed after the grid is created. Explore other options making it possible.
* 23) Finish collision checking so invalid spans can't be added to the grid --- done, grid should only call the method now.
* 24) Fix event GetSrc generics. Some return components some return any and some return your custom made generic type. Explore if it is necessary and try to avoid it.
* 
* Optimization
* 1) Create rendering queve and rendering request class which specifies the rendering source. Each class should have an ID (Either real or pregenerated from the type)
*	 The rendering queve should be handled by the root and it should limit the maximum amount of renders to 30 repaints per second
* 2) Combobox memory leaks
* 
* Design
* 1) Remove generics from all the events and send the src as subject by default. The inheritance hierarchy will allow you to cast it to the correct type. Src is ALWAYS a subject.
* 2) All the behaviors should be covered by a common interface to be able to make them hot swappable. (It is not going to be completely possible, but at least create a common interface for the same behavioral groups)
* 3) Trackbar
*		1) UpdateTracker() vs UpdateTrackerHeight, rename and recheck the design. What is the difference, why is UpdateTrackbar not calling UpdateTracker --- optimize and change
* 3) ListBox and combobox
*		1) Both have internal factories that generate the elements. Give an option to place any factory inside the components so any element can be part of it.
* 4) Introduce a merge function, so composite components handle events as a single logical component
* 
* Bugs
* Trackbar
*	1) If trackbar width is called after trackbar control, the width doesn't get updated
*	2) If component is added to the controlled trackbar before the trackbar is added as a control, the size doesn't update
*/
	
/*int LiiEntry()
{
	DemoApplication::LaunchDemoApp();
	ApplicationController::JoinThreads();
	return 0;
}*/