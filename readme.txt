Greetings, welcome to my read me file for Assignment 3 in CS3022F

The images inlcuded in the file are simple pgm files which can be used to rest the program in the different ways via Makefile commands. The
To run the program first type in 'Make' to compile;

From then on just you can run the program using the format below.


./findcomp -s <miValidsize> <maxValidSize> -t <threshold>  (-p) (-w) outputfilename INPUTFILE.pgm

This will run the program

The -s and -t commands are crucial and thus a command list without them wont allow you to print or to write the output of the program to

To clean the folder and get rid of all object and outputpgm files a clean command is included in the makefile.

The ConnectedComponent file represents each conncected component found in the source input image, i holds all the the data for that component has methods to allow comparison of the

the PGMimageProcessor is the main file in the assignemnt , it reads in the file, formats the pgm , and performs varouis actions of the data, such as flipping of characters, writing to output files  etc etc.

catch.hhp allows unit testing for the flder functions

Test.cpp contains the unit tests for this assignemnt.

EDIT I APOLOGIZE FULLY BUT TO RUN THE UNIT TEST PLEASE USE "g++ Test.cpp" then type "./a.out" To run the tests I WAS NOT ABLE TO MAKE IT RUN VIA MAKEFILE

To run the unit tests just type in "make Test" and wait, the compilation time may be a bit long.


Thats about it, the different commands in the make file(especially run1 and run2 will show the differnt in the output image when the minimun and max Component size are changed)


Thank You for reading , and marking.
Tadiwa Magwenzi


NB my PORGRAM CAN HANDLE FOREGROUND DETECTION FROM BOTH SIUATIONS WHERE THE BACK GROUND IS DARKER AND WHEN IN IS LIGHTER, :)