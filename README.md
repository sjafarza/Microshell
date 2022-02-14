# Microshell

--------------------------------------------------------------------------------------
Assignment name  : microshell
Expected files   : *.c *.h
Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp

Write a program that will behave like executing a shell command.
- The command line to execute will be the arguments of this program
- Executable's path will be absolute or relative but your program must not build a path (from the PATH variable for example)
- You must implement "|" and ";" like in bash
- we will never try a "|" immediately followed or preceded by nothing or "|" or ";"
- Your program must implement the built-in command cd only with a path as argument (no '-' or without parameters)
- if cd has the wrong number of argument your program should print in STDERR "error: cd: bad arguments" followed by a '\n'
- if cd failed your program should print in STDERR "error: cd: cannot change directory to path_to_change" followed by a '\n' with path_to_change replaced by the argument to cd
- a cd command will never be immediately followed or preceded by a "|"
- You don't need to manage any type of wildcards (*, ~ etc...)
- You don't need to manage environment variables ($BLA ...)
- If a system call, except execve and chdir, returns an error your program should immediatly print "error: fatal" in STDERR followed by a '\n' and the program should exit
- If execve failed you should print "error: cannot execute executable_that_failed" in STDERR followed by a '\n' with executable_that_failed replaced with the path of the failed executable (It should be the first argument of execve)
- Your program should be able to manage more than hundreds of "|" even if we limit the number of "open files" to less than 30.

for example this should work:
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
*********************************************************************************************
$>./microshell /bin/echo woot "; /bin/echo NOPE;" "; ;" ";" /bin/echo YEAH
woot ; /bin/echo NOPE; ; ;
YEAH



Hints:
Don't forget to pass the environment variable to execve

Hints:
Do not leak file descriptors!

*******************************************************************************************************************
Example for test
*******************************************************************************************************************


1) ./microshell /bin/ls
2) ./microshell /bin/cat microshell.c
3) ./microshell /bin/ls microshell.c
4) ./microshell /bin/ls salut
5) ./microshell ";"
6) ./microshell ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";"
7) ./microshell ";" ";" /bin/echo OK
8) ./microshell ";" ";" /bin/echo OK ";"
9) ./microshell ";" ";" /bin/echo OK ";" ";"
10) ./microshell ";" ";" /bin/echo OK ";" ";" ";" /bin/echo OK
11) ./microshell /bin/ls "|" /usr/bin/grep microshell
12) ./microshell /bin/ls "|" /usr/bin/grep microshell "|" /usr/bin/grep micro
1") ./microshell /bin/ls "|" /usr/bin/grep microshell "|" /usr/bin/grep micro "|" /usr/bin/grep shell "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro
13) ./microshell /bin/ls "|" /usr/bin/grep microshell "|" /usr/bin/grep micro "|" /usr/bin/grep shell "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep micro "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell "|" /usr/bin/grep shell
14) ./microshell /bin/ls ewqew "|" /usr/bin/grep micro "|" /bin/cat -n ";" /bin/echo dernier ";" /bin/echo
15) ./microshell /bin/ls "|" /usr/bin/grep micro "|" /bin/cat -n ";" /bin/echo dernier ";" /bin/echo ftest ";"
16) ./microshell /bin/echo ftest ";" /bin/echo ftewerwerwerst ";" /bin/echo werwerwer ";" /bin/echo qweqweqweqew ";" /bin/echo qwewqeqrtregrfyukui ";"
17) ./microshell /bin/ls ftest ";" /bin/ls ";" /bin/ls werwer ";" /bin/ls microshell.c ";" /bin/ls subject.fr.txt ";"
18) ./microshell /bin/ls "|" /usr/bin/grep micro ";" /bin/ls "|" /usr/bin/grep micro ";" /bin/ls "|" /usr/bin/grep micro ";" /bin/ls "|" /usr/bin/grep micro ";"
19) ./microshell /bin/cat reserv_microsh.c "|" /usr/bin/grep a "|" /usr/bin/grep b ";" /bin/cat reserv_microsh.c ";"
20) ./microshell /bin/cat reserv_microsh.c "|" /usr/bin/grep a "|" /usr/bin/grep w ";" /bin/cat reserv_microsh.c ";"
21) ./microshell /bin/cat reserv_microsh.c "|" /usr/bin/grep a "|" /usr/bin/grep w ";" /bin/cat reserv_microsh.c
22) ./microshell /bin/cat reserv_microsh.c ";" /bin/cat reserv_microsh.c "|" /usr/bin/grep a "|" /usr/bin/grep b "|" /usr/bin/grep z ";" /bin/cat reserv_microsh.c
23) ./microshell ";" /bin/cat reserv_microsh.c ";" /bin/cat reserv_microsh.c "|" /usr/bin/grep a "|" /usr/bin/grep b "|" /usr/bin/grep z ";" /bin/cat reserv_microsh.c
24) ./microshell blah "|" /bin/echo OK
25) ./microshell blah "|" /bin/echo OK ";"
26) ./microshell ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" blah "|" /bin/echo OK ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";" ";"
