#include<stdio.h>
#include<time.h>
#include<math.h>

int successor(char* queens,int h){
  int i,j,k,t,temp,nRow=8,nCol=8,original;
  for(i=0;i<8;i++){//iterate col
    original=queens[i];
    for(j=0;j<8;j++){//choose row
      temp=0;
      
      if(original!=j){
      	queens[i]=j;
        for(k=0;k<8;k++){//recalculate h
	  for(t=k+1;t<8;t++){
	    if(queens[k]==queens[t]||abs(queens[k]-queens[t])==abs(k-t)){
	      temp++;//same row or diagonal
	    }
	  }
	}
	if(temp<h){
	  h=temp;
	  nRow=j;
	  nCol=i;
	}
      }
    }
    queens[i]=original;
  }
  if(nCol<8){
    queens[nCol]=nRow;
  }
  return h;
}

int main(int argc,char* argv[]){
  char queens[8];
  int i,j,h=-1,nexth;
  srand(time(0));

  while(h!=0){
    for(i=0;i<8;i++){
      queens[i]=rand()%8;//rand row
    }
    for(i=0;i<8;i++){
      printf("queens[%d] %d\n",i,queens[i]);
    }  
    for(i=0;i<8;i++){
      for(j=i+1;j<8;j++){	
	  if(queens[i]==queens[j]||abs(queens[i]-queens[j])==abs(i-j)){
	    h++;//same row or diagonal
	  }
      }  
    }
    
    while(h>(nexth=successor(queens,h))){
      h=nexth;
      printf("value of h %d\n",h);
      for(i=0;i<8;i++){
    	printf("queens[%d] %d\n",i,queens[i]);
      }
    }
    
  }
  return 0;
}
