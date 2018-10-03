#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define max 1000
//solving 8queens problem using genetic algorithm
void mutate(int* child){
  child[rand()%8]=rand()%8;
}
int* reproduce(int x,int y,int** pop){
  int cut=rand()%8,*child,i;
  child=malloc(sizeof(int)*8);
  for(i=0;i<8;i++){
    if(i<=cut){
      child[i]=pop[x][i];
    }
    else{
      child[i]=pop[y][i];
    }
  }
  return child;
}
int fitness(int* state){
  int i,j,count=0;
  for(i=0;i<8;i++){
    for(j=i+1;j<8;j++){
	if(state[i]!=state[j]&&abs(i-j)!=abs(state[i]-state[j])){
	  count++;
	}
    }
  }
  //printf("fitness %d\n",count);
  return count;
}
int randomSelect(int** pop,int p,int* fit,int sum){
  int i,choose;
  choose=rand()%sum+1;
 
  sum=0;
  for(i=0;i<p;i++){
    sum+=fit[i]; 
    if(choose<=sum){
      //printf("choice %d\n",i);
      return i; 
    } 
  }
}
int main(){
  int t=0,**pop,p,**newpop,i,j,k,x,y,*child,
      *fit,maxfit=0,store[8],sum;//pop=population
  srand(time(0));
  printf("enter the size of population\n");
  scanf("%d",&p);
  pop=malloc(sizeof(int*)*p);
  newpop=malloc(sizeof(int*)*p);
  //create first pop
  for(i=0;i<p;i++){
    pop[i]=malloc(sizeof(int)*8);
    for(j=0;j<8;j++){
      pop[i][j]=rand()%8;
    }
  }
  fit=malloc(sizeof(int)*p);
  while(t<max){
    for(i=0;i<p;i++){
      //calculate all the fitness in pop
      sum=0;
      for(j=0;j<p;j++){
        fit[j]=fitness(pop[j]);
        if(fit[j]>maxfit){//store the max fitness until now
	  maxfit=fit[j];
	  for(k=0;k<8;k++){
            store[k]=pop[j][k];
	  }
        }
        sum+=fit[j];
      }
      x=randomSelect(pop,p,fit,sum);//parent1
      y=randomSelect(pop,p,fit,sum); //parent2
      child=reproduce(x,y,pop);

      if(rand()%100<3){//with small probability mutate
	mutate(child);
      }
      newpop[i]=child;
    }
    //free pop and change to newpop
    for(i=0;i<p;i++){
      free(pop[i]);
      pop[i]=newpop[i]; 
    }
    t++;
  }
  printf("maxfit %d\n",maxfit);
  for(i=0;i<8;i++){
    printf("%d ",store[i]);
    free(pop[i]);
  }
  free(fit);
  free(pop);
  free(newpop);
  return 0;
}
