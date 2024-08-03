# Timber #
A thread safe logging utility for C++ programs. 

## Why? ##
I wanted to learn how to implement a logger. There are a few ways to go 
about handling how the logger actually writes to disk, and how to configure
the logger itself which makes this interesting. It should be useful for debugging
other C++ programs to. This will also use 

```cpp std::source_location
```
for ease of use. It provides useful metadata about function's and line numbers of various
statements.

## How it works ##
The thread safety comes from the, 
```cpp std::lock_guard 
```
which uses RAII or Scope Based Resource Management to automatically manage the mutex. Whenever a call to the log 
function is made, it locks the mutex, after it unlocks it. 

Not sure if there could be a deadlock though ...

## Links ##
- [gcc macro stuff](https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html)
- [api design in C++](https://youtube.com/watch?v=zL-vn_pGGgY) 
- [raii or sbrm]()

