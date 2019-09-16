# DFG_CFG_generator
generating DFG and CFG from source code (using LLVM ) or from binary (using LLVM and Mcsema)

### Install:  
#### 1. compile LLVM DFG pass and CFG pass   
following their README in dir LLVM_PASS, the you can get libCFGPass.so and libDFGPass.so   
(NOTE: in this test, we use LLVM 6.0 and Clang 6.0)  
  
#### 2. install Mcsema  
install Mcsema following  https://github.com/trailofbits/mcsema  
after installing, you can use mcsema-disass and mcsema-lift in your Ubuntu  
(NOTE: as Mcsema needs dependency of IDA, so you need to download IDA software as well. in this test we use IDA PRO 6.4 version）  

### Usage:  
#### 1.from source code to generate DFG&CFG:  
CFG: run shell: ./gen_cfg.sh    
`clang-6.0 -emit-llvm test.c -c  -o test.bc`   
`opt-6.0 -load  ./libCFGPass.so -CFG test.bc`  

DFG: run shell: ./gen_dfg.sh  
`clang-6.0 -emit-llvm test.c -c  -o test.bc`  
`opt-6.0 -load  ./libDFGPass.so -DFGPass test.bc`  

#### 2.from binary to generate DFG&CFG:  
run mcsema_binary2llvmbitcode.sh to transfer binary to LLVM IR(bitcode format):  
`sudo mcsema-disass --arch amd64 --os linux --disassembler /home/cmt/Applications/ida-pro/ida-pro/idal64 --binary ./test --entrypoint main --output auth.cfg --log_file ./log`  

`mcsema-lift-4.0 --arch amd64 --os linux --cfg ./auth.cfg --output ./test.bc --explicit_args`  
after get the bitcode we need, you can use gen_cfg.sh and gen_dfg.sh as above to get DFG&CFG  

### Test:  
test.c:  
```bash
void ff3(){
  printf("f3\n");
  int a=1;
  if(a==1){
    f1();
  }else{
    f2();
  }
 f1();
 f2();
}

```

### Result:  
![CFG](https://github.com/meton-robean/DFG_CFG_generator/blob/master/imgs/cfg/f3_cfg.png)  
![DFG](https://github.com/meton-robean/DFG_CFG_generator/blob/master/imgs/dfg/f3_dfg.png)  



