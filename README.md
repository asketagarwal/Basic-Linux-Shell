# Basic-Linux-Shell

The shell will give a prompt for the user to type in a command, take the command, execute it, and  then  give  the  prompt  back  for  the  next  command  (i.e.,  actually  give  the  functionality  of  a shell). 

1.	Give a prompt (like the $ prompt you get in Linux) for the user to type in a command. The prompt should have the current working 		directory name (full path) followed by the “>” sign (for ex., /usr/home/agupta/temp>). 
2.	The builtin commands are:
	cd<dir>
	pwd
	mkdir<dir>
	rmdir<dir>
	ls -option (-l option supported)
	cp file1 file2 (copy of directory supported)
	exit

3.	Other files other than this are executed using exec family of commands.
4.	Supports background execution of commands. (using &)
5.	Supports redirection (< and > also together)
6.	Supoorts piping upto 3 stages. (a.out | b.out | c.out)


	To run execute the following commands:
	
	cc shell.c -o shell
	cc run.c
	./a.out
