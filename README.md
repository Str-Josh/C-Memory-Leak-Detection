# Memory Leak Detection
Memory leak detector for tracking and managing memory allocations on the heap using C.

## Overview
The project creates malloc and free functions, which are wrapped using linker substitution, that in addition to standard allocation and deallocation, the functions will add/remove nodes to a Linked List with the memory address information and memory allocation size. Upon program exit, a displayLeakDetectionReport function is called and displays current Linked List nodes and the memory allocation information contained within the node.

## Developed Using
* __C__

## Getting Started
### Prerequisites
* C Compiler (Clang, GCC, etc.) Examples are using GCC.

### Installation
1. Clone the repo: <br> `git clone https://github.com/Str-Josh/C-Memory-Leak-Detection.git`
2. Change git remote url to avoid accidental pushes to main project
<br>`git remote set-url origin github_username/repo_name`
<br>`git remote -v`
3. Compile the following scripts:
<br>`gcc -c LinkedList.c`
<br>`gcc -c MemoryLeakDetector.c`
<br>`gcc -c main.c` (Optional)
4. Link the object files as well as create link substitution (can use your own object file in place of main.o)
<br>`gcc -Wl,--wrap=malloc -Wl,--wrap=calloc -Wl,--wrap=realloc -Wl,--wrap=free MemoryLeakDetector.o LinkedList.o main.o -o <YourDesiredApplicationName>`
5. Execute <YourDesiredApplicationName>
<br>`./<YourDesiredApplicationName>`


Lessons Learned:
* Memory Management using stdlib.h library
* Implementation of Linked List Data Structure
* Linker Substitution
* Usage of the valgrind tool for memory debugging and memory leak detection
* Automatically invocation of functions at program exit.


Future Additions/Improvements:
* Add more analytics regarding memory allocations/deallocations
* Implement file path and line number tracking for each allocation and deallocation

