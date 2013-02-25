mexCommandWrapper
=================

A MATLAB mex program for calling Windows command lines as a separate thread and without blocking MATLAB command sequence. Unlike MATLAB's built-in dos command which switches focus from the MATLAB window to the external program, this mex program brings the MATLAB main window back to foreground and focus shortly after the initiation of the external program.

