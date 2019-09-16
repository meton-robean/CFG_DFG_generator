clang-6.0 -emit-llvm test.c -c  -o test.bc
opt-6.0 -load  ./libDFGPass.so -DFGPass test.bc
