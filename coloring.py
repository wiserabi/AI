import sys
def MRV(poped,varNum,backtrack):
    minval=0x7FFFFFFF
    for i in range(varNum):
        num=0
        for x in poped[i]:
            num=num+x
        if num==0 and poped[varNum][i]==-1:
                
            print("backtrack")
            backtrack[0]=True 
            break
        if num<minval and poped[varNum][i]==-1:
            minval=num
            choose=i
    return choose

def Success(copied,varNum):#check complete assignment
    for x in copied[varNum]:
        if x==-1:
           return False 
    return True
def inference(copied,varNum,graph,valueNum):#check for variables that only one color is available
    for i in range(varNum):# i is var index
        num=0
        for j in range(valueNum):
            num=num+copied[i][j]
            if copied[i][j]==1:
                val=j #j is value index
                
        if num==1 and copied[varNum][i]==-1:#if only one value available and not colored
            copied[i][val]=0
            for j in graph[i]:#look for the adjacent of chosen var
                copied[j][val]=0#set the adjacent value unavailable
            copied[varNum][i]=val
            
    return
def main():

    varNum=int(sys.stdin.readline().strip())#number of variables which is also vertex
    edgeNum=int(sys.stdin.readline().strip())#connection between vertex
    valueNum=int(sys.stdin.readline().strip())#number of colors
    
    graph=[[] for x in range(varNum)]
    check=[[1 for x in range(valueNum)] for x in range(varNum)]
    check.append([-1 for x in range(varNum)])#check if each var colored or not
    # -1 stands for not colored and 0,1,2... is colored value

    for i in range(edgeNum):
        edge=[int(x) for x in (sys.stdin.readline()).split(' ') if x.strip()]
        graph[edge[0]].append(edge[1])
        graph[edge[1]].append(edge[0])
    #print(graph)
    #print(check)
    stack=[check]
    stackP=1
    while stackP!=0:
        #pop
        poped=stack.pop(-1)
        stackP=stackP-1
        #choose the variable with fewest legal values
        backtrack=[False]
        choose=MRV(poped,varNum,backtrack)

        #print("chosen",choose)
        
        #push the child
        if not backtrack[0]:
            for i in range(valueNum):#possible number of child=number of values(colors)
                copied=[x[:] for x in poped]
                if poped[choose][i]==1:#if color of index i is available
                    copied[choose][i]=0 # set it unavailable
                    for j in graph[choose]:#look for the adjacent of chosen var
                        copied[j][i]=0#set the adjacent value unavailable
                    copied[varNum][choose]=i#mark as colored
                    
                    inference(copied,varNum,graph,valueNum) #inference
                    if Success(copied,varNum): #check for success
                        #print("copied",copied)
                        print("success",copied[varNum])
                        return
                    #now push this copied to the stack
                    stack.append(copied)
                    stackP+=1
                        
if __name__=="__main__":
    main()
