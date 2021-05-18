#include <stdio.h>
int i, j;
#define A(x,y) for(j=0;j<y;++j)printf(x);
int main(){for (;i<5;++i){if (i==4) {A("4",5);A("2",5);}else{A(" ",4-i);A("4",1);A(" ",2*i);A("2",1);}A("\n",1);}}