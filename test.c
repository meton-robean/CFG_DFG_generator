#include<stdio.h>

void f1(){

   printf("f1\n");
}

void f2(){
 printf("f2\n");
 f1();

}

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

int main(){

   printf("hello world!\n");
   ff3();
   return 0;

}

