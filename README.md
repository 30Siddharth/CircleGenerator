
# Circle Generator

# Introduction
This code creates an App that allows user to create circle by selection points.

# Algorithm - Least Square Algorithm

- We use Eigen library to solve the problem.
- We cast the problem of finding the best fit circle as a geometric Least Squares problem as shown in the below paper.
credits: http://emis.maths.adelaide.edu.au/journals/BBMS/Bulletin/sup962/gander.pdf
- The Eigen library has a SVD solver which gives the singular value for the problem which are the co-ordintates of the center and the radius.
- if no. of points <3 then the matrix looses rank and we dont get a solution. Otherwise the matrix gives the solution

# App Demo
[![Watch the video](https://img.youtube.com/vi/rxW7r-dFajg/hqdefault.jpg)](https://youtu.be/rxW7r-dFajg)
# Walkthrough
The GUI interface used is wxWidgets to create the GUI which is platform agnostic. The interface can be installed in Windows, Linux and Mac.
1. The bacground dot grid is constructed with small rectangles that activate and deactivate based on mouse clicks.
2. Select all the required points >=3.
3. Once that is done we find the radius and center using least squres.
4. We draw the circle based on this data using wxWidgets DC class members.
5. To refresh the window we can click on the screen.

## Getting Started

These instructions is to help you get started,

### Prerequisites

- g++ Compiler
- wxWidgets
- Eigen

### Installing wxWidgets 
#### Linux
- $ sudo apt-get install libgtk-3-dev build-essential checkinstall
- Download and Extract wxWidget. https://www.wxwidgets.org/downloads/
- $ mkdir gtk-build
- $ cd gtk-build/
- $ ../configure --disable-shared --enable-unicode
- $ make

It Takes about 20 mins to build.
Credits: https://www.binarytides.com/install-wxwidgets-ubuntu/

#### Windows
- A nice intro to setup wxWidgets Video: https://www.youtube.com/watch?v=sRhoZcNpMb4
- Download the Windows zip file - https://www.wxwidgets.org/downloads/
- Unpack it
- Go to build -> msw -> vx_vc16.sln 
- Select compile mode (32 bit / 64 bit) and build
- Restart Visual Studio
- To manual setup refer ~/docs/msw/install.md
- For Auto setup use the property sheet. 
- NOTE: The application build has to be build in x86 mode
- To get eigen in visual studio use Tools->NuGet Package Manager



### How To Use
- After the prerequisites are done download the github repository
-  $ make (type make to invoke the make file)
- ./CircleGenerator

## Test Cases
### Manual Testing
- Constructing Different size circles (small to large)
- Closing and opening the application
- Checking mouse click to activate the desired grid points (Corners and center locations)
- 3 points circle check - radius and center close to solution. 3 points has a unique solution.
- Clicking outside the grid locations.


### Unit Testing
- TODO

## Versioning
- 1.0
    - First Release
    - Known Bug
        - The screen resets on increasing or decreasing size of the window
        - Dots Selection not accurate always
        - Generate Button doesnt show up after refresh. Hover hover area to show it. 


## Authors

* **Subhransu Mahapatra** 



 
