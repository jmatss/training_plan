# How to build (with gcc)
```
gcc src/*.c test/*.c test/cunit/libcunit.a -Itest/cunit -Isrc -o test_runner.exe
```
```
gcc src/j_stack.c test/*.c -Isrc test/cunit/libcunit.a -Itest/cunit src/linn_lib/libl_stack.a -Isrc/linn_lib -o test_runner.exe
```

# How to build (with cmake/make)
```
cmake .
```
```
make
```

### (with MinGW):
```
cmake -G "MinGW Makefiles" .
```
```
mingw32-make
```

### Clean (with MinGW unix/windows):
```
mingw32-make clean
```
```
mingw32-make win-clean
```

# Run tests
```
test_runner.exe
```