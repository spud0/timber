# Timber #
A logging utility for C++ programs. 

## Why? ##
I wanted to learn how to implement a logger. There are a few ways to go 
about handling how the logger actually writes to disk, and how to configure
the logger itself which makes this interesting.

- This depends on a toml parsing library 
[toml.hpp](https://github.com/marzer/tomlplusplus/)

- This will also use 
```cpp 
std::source_location
std::expected
```
which gives me useful metadata about function's and line numbers of various
statements and a convenient way to wrap return values.

## How it works ##
Currently just specify a toml file and it will get parsed, which will set 
the configuration of the logger.

## Links ##
- [gcc stuff](https://gcc.gnu.org/onlinedocs/gcc/index.html)
- [api design in C++](https://youtube.com/watch?v=zL-vn_pGGgY) 
- 

