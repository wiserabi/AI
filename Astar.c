#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define max 5000
//using A* in slider puzzle
int qSize=0;
typedef struct node{
  int gh[2];//g=gh[0],h=gh[1],g is the cost of path until now
  char puzzle[3][3];//h is heuristic function result
  struct node *parent;
}node;

void swap(char* p1,char* p2){
  char temp;
  temp=*p1;
  *p1=*p2;
  *p2=temp;
}

int manhattan(char puzzle[3][3]){
  char arr[8][2]={{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1}};
  int i,j,k,d1,d2,sum=0;
  for(i=1;i<9;i++){//for each number
    for(j=0;j<3;j++){//iterate puzzle
	for(k=0;k<3;k++){
	   if(i==puzzle[j][k]){
		d1=arr[i-1][0]-j;
		d2=arr[i-1][1]-k;
		if(d1<0){
		  d1=-d1;
		}
		if(d2<0){
		  d2=-d2;
		}
		sum=sum+d1+d2;
	   }
	}
    }
  }
  return sum;
}
void insert(node* queue[max],node* one){
  int child,parent,cost,pcost;
  node* tmp;
  qSize++;
  child=qSize;
  parent=qSize/2;
  queue[qSize]=one;
  while(parent!=0){
    cost=queue[child]->gh[0]+queue[child]->gh[1];//child node cost
    pcost=queue[parent]->gh[0]+queue[parent]->gh[1];//cost of parent node
    if(pcost>cost){//if parent cost is bigger swap
	tmp=queue[parent];
	queue[parent]=queue[child];
	queue[child]=tmp;	
    }
    else{
	break;
    }
    child=parent;
    parent=parent/2;  
  } 
}
node* delete(node* queue[max]){
  node* min,*tmp;
  int left,right,parent=1,cost,costL,costR;
  if(qSize<1){
    printf("unable to delete");
    exit(0);
  }
  min=queue[1];
  queue[1]=queue[qSize];
  queue[qSize]=min;
  qSize--;
  while(qSize!=0){
    left=parent*2;
    right=left+1;
    cost=queue[parent]->gh[0]+queue[parent]->gh[1];

    if(right<=qSize&&cost>queue[right]->gh[0]+queue[right]->gh[1]){
      tmp=queue[parent];
      queue[parent]=queue[right];
      queue[right]=tmp;
      parent=right;
    }
    else if(left<=qSize&&cost>queue[left]->gh[0]+queue[left]->gh[1]){
      tmp=queue[parent];
      queue[parent]=queue[left];
      queue[left]=tmp;
      parent=left;
    }
    else{
      break;
    }
  }
  return min;
}
int main(){
  char goal[3][3]={1,2,3,4,5,6,7,8,0},n;
  node* temp=NULL,*queue[max]={NULL,},*poped;
  int i,j,depth=0,arr[4][2]={{0,1},{1,0},{-1,0},{0,-1}},zeroX,zeroY,k,count,h;
  srand(time(0));
  n=rand()%30+5;
  zeroX=2;
  zeroY=2;
  //procedure of mixing the puzzle
  while(n>0){
    count=rand()%4;
    i=zeroX;
    j=zeroY;
    if(count==0){
          zeroX++;
    }
    else if(count==1){
          zeroX--;
    }  
    else if(count==2){
          zeroY++;
    }
    else if(count==3){
          zeroY--;
    }
    if(zeroX==-1||zeroX==3){
	zeroX=1;
    } 
    if(zeroY==-1||zeroY==3){
        zeroY=1;
    }
    swap(&goal[zeroY][zeroX],&goal[j][i]); 
    n--;
  }
  printf("solve the following\n");
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
	printf("%d ",goal[i][j]);
    } 
    printf("\n");
  }
  printf("\n");
  //root node
  temp=malloc(sizeof(node));
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
	temp->puzzle[i][j]=goal[i][j];
    }
  }
  temp->gh[0]=0;
  temp->gh[1]=manhattan(temp->puzzle);
  temp->parent=NULL;
  insert(queue,temp);
  
  while(qSize<max){
    //delete from the queue
    poped=delete(queue);

    //find the position of zero
    for(i=0;i<3;i++){
      for(j=0;j<3;j++){
        if(poped->puzzle[i][j]==0){
	  zeroX=j;
	  zeroY=i;
	}
      }
    }	
    
    //check if deleted node match the goal
    if(poped->gh[1]==0){
      printf("found\n");
      while(poped->parent!=NULL){
         for(i=0;i<3;i++){
	   for(j=0;j<3;j++){
	     printf("%d ",poped->puzzle[i][j]);    
	   }
	   printf("\n");
         }
         printf("\n");
	 poped=poped->parent;
      }
      //free all resource
      for(i=0;i<max;i++){
        if(queue[i]==NULL){
	  break;
	}
        free(queue[i]);
      }
      break;
    } 
     
    //insert all the child nodes  
    for(k=0;k<4;k++){
      if(!(zeroY+arr[k][0]<0||zeroY+arr[k][0]>2||zeroX+arr[k][1]<0
	||zeroX+arr[k][1]>2)){
	temp=NULL;	
	temp=malloc(sizeof(node));
	temp->gh[0]=poped->gh[0]+1;
        temp->parent=poped;
	for(i=0;i<3;i++){
          for(j=0;j<3;j++){
	    if(i==zeroY&&j==zeroX){
	      temp->puzzle[zeroY+arr[k][0]][zeroX+arr[k][1]]=
	      poped->puzzle[zeroY][zeroX];	
	    }
	    else if(i==zeroY+arr[k][0]&&j==zeroX+arr[k][1]){
	      temp->puzzle[zeroY][zeroX]=
	      poped->puzzle[zeroY+arr[k][0]][zeroX+arr[k][1]];	
	    }
	    else{
              temp->puzzle[i][j]=poped->puzzle[i][j];
	    }
          }
        }
	
	temp->gh[1]=manhattan(temp->puzzle);
	insert(queue,temp);
      }
    }
  }
 
  return 0;
}
