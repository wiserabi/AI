#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#define N 100
#define max 500
//backtrack,min conflict
char safe(int* queen,int i,int col){
  int j;
  for (j=0;j<col;j++){
    if(queen[j]==i||abs(queen[j]-i)==abs(j-col)){
      return 0;
    }
  }
  return 1;
}
char backtrack(int* queen,int col){
  int i;
  for(i=0;i<N;i++){
    if(col>=N){
      return 1;
    } 
    if(safe(queen,i,col)){
      queen[col]=i;
      if(backtrack(queen,col+1)){ 
        return 1; 
      }     
    } 
  }
}
int conflict(int* queen,int col,int row){
  int i,conf=0;
  for(i=0;i<N;i++){
    if(i!=col){
      if(queen[i]==row||abs(queen[i]-row)==abs(i-col)){
        conf++; 
      }
    }
  }
  return conf;
}
void min_conflict(int* queen){
  int i,col,j,arr[N]={0},count,minval,temp,row;
  char success;
  srand(time(0));
  for(i=0;i<N;i++){
    do{
      queen[i]=rand()%N;
    }while(conflict(queen,i,queen[i])>1);
  }
  for(i=0;i<max;i++){
    //check success
    success=1;
    count=0;
    for(j=0;j<N;j++){
      if(conflict(queen,j,queen[j])!=0){
        arr[count]=j;
        count++;
        success=0;
      }  
    }
    if(success){
      for(i=0;i<N;i++){
        printf("%d ",queen[i]);
      }
      printf("\n");
      break; 
    } 
    //choose the column ,find min conflict in column
    col=arr[rand()%count];
    minval=0x7FFFFFFF;
    for(j=0;j<N;j++){//iter row
      if(minval>(temp=conflict(queen,col,j))){
        minval=temp;
	row=j;
      }
      else if(minval==temp){
	if(rand()%2){
          minval=temp;
	  row=j;
        }
      }
    }
    queen[col]=row;    
  }  
}
int main(){
  int queen[N]={0},i,mode;//queen[col]=row
  scanf("%d",&mode);
  if(mode==0){
    backtrack(queen,0);
    for(i=0;i<N;i++){
      printf("%d ",queen[i]);
    }
    printf("\n");
  }
  else{
    min_conflict(queen);
  } 
}
