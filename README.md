# Bash-Shell
Created a bash shell like a linux terminal using fork(),execvp() and piping
This is c program to create a terminal shell . 
The OS command interpreter is the program that people interact with in order to launch and control programs. On UNIX systems, the command interpreter is often called shell: a user-level program that gives people a command-line interface to launching, suspending, and killing other programs. sh, ksh, csh, tcsh, bash, ... are all examples of UNIX shells.
Shell has following features:-

1.	The shell run continuously, and display a prompt (something similar to ‘$’)  when waiting for input.
2.	The shell should read a line from input one at a time. 
3.	Parse the line into the program name and an array of parameters;
4.	Use the fork() system call to spawn a new child process;
  a. The child process then uses the exec() system call (or one of its variants) to launch the specified program;
  b. The parent process (the shell) uses the wait() system call (or one of its variants) to wait for the child to terminate;


The shell runs programs using two core system calls: fork() and execvp(). The execvp() call is used to overlay the currently running program with a new program, which is how the shell turns a forked process into the program it wants to run. In addition, the shell must wait until the previously started program.

Additional use of Pipes:
Pipes allow the stdins and stdouts of a list of programs to be concatenated in a chain. More specifically, the first program's stdout is directed to the stdin of the second program; the second program's stdout is directed to the stdin of the third program; and so on so forth. Multiple piped programs in a command line are separated with the token "|". A command line will therefore have the following form:
     <program1> <arglist1> | <program2> <arglist2> | ... | <programN> 


Other useful links:
		 	 	 		
●	GNU C Library: http://www.delorie.com/gnu/docs/glibc/libc_toc.html
●	File Descriptors: http://www.delorie.com/gnu/docs/glibc/libc_169.html 
●	Duplicating File Descriptors: http://www.delorie.com/gnu/docs/glibc/libc_257.html
●	Pipes: http://www.delorie.com/gnu/docs/glibc/libc_296.html
