## UID: 806284201

## Pipe Up

Low level code performed by the pipe ( | ) operator in shells wherein users pass in
executable names as command line arguments and each one is executed as a new process.

## Building

To build the program, run: 
```
make ./pipe
```

## Running

Example run of program, using at least two additional arguments with what to expect:
```
> ls
Makefile    pipe.c  __pycache__ test_lab1.py
pipe        pipe.o  README.md
> ./pipe ls
Makefile    pipe.c  __pycache__ test_lab1.py
pipe        pipe.o  README.md
> ls | cat | wc
        7       7       63
> ./pipe ls cat wc
        7       7       63
```

## Cleaning up

To clean up all binary files, run: 
```
make clean
```
