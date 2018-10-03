#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 0x7FFFFFFF
#define min 0x80000001
#define branch 2

int minimax(int depth,int nodeI,char maxlayer,int* leaf,int alpha,int beta,int d){
  int best=0,i,val;
  //terminating condition
  if(depth==d){
    return leaf[nodeI];
  }
  if(maxlayer){
     best=min;
     for(i=0;i<branch;i++){
       val=minimax(depth+1,nodeI*branch+i,0,leaf,alpha,beta,d);
       best=best<val?val:best;
       alpha=alpha<best?best:alpha;
       if(beta<=alpha){//pruning
	 break;
       }
     }
     return best;
  }
  else{
    best=max;
    for(i=0;i<branch;i++){
      val=minimax(depth+1,nodeI*branch+i,1,leaf,alpha,beta,d);
      best=best<val?best:val;
      beta=beta<best?beta:best;
      if(beta<=alpha){
	break;	 
      }
    }
    return best;
  }
}
int main(int argc,char *argv[]){
  int i,*leaf,d;
  printf("input depth\n");
  scanf("%d",&d);

  if(argc<2){
    printf("no input\n");
    return 0;
  }
  
  leaf=malloc(sizeof(int)*(argc-1));
  for(i=0;i<argc-1;i++){
    leaf[i]=atoi(argv[i+1]);
  }
  printf("optimal value %d\n",minimax(0,0,1,leaf,min,max,d));
  return 0;
}
