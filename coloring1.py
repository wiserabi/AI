import sys

def success(check,varNum):
    for x in check[varNum]:
        if x==-1:
            return False
    return True
#use of forward checking
def forward(graph,check,varNum,valueNum):
    #check success
    if success(check,varNum):
        print("success",check[varNum])
        sys.exit()
    
    #choose the most constrained var
    minval=10000
    for i in range(varNum):
        if minval>check[varNum+1][i] and check[varNum][i]==-1:
            minval=check[varNum+1][i]
            chosenVar=i
        #tie breaker
        elif minval==check[varNum+1][i] and check[varNum][i]==-1:
            if len(graph[chosenVar])<len(graph[i]):
                minval=check[varNum+1][i]
                chosenVar=i

    minval=10000
    #choose the least constraining value
    #adjacent variable domain 
    for h in range(valueNum):
        if check[chosenVar][h]==1:#if value exist in domain
            val=0
            for j in graph[chosenVar]:
                if check[j][h]==1:
                    val+=1
            if minval>val:
                minval=val
                chosenVal=h
    check[chosenVar][chosenVal]=0
    check[varNum][chosenVar]=chosenVal
    check[varNum+1][chosenVar]-=1
    #delete value from adjacent variable domain
    for i in graph[chosenVar]:
        check[i][chosenVal]=0
        check[varNum+1][i]-=1
    #print(check)
    #do recursive call or not?
    for i in range(varNum):
        if check[varNum][i]==-1 and check[varNum+1][i]<=0:
            return
    
    forward(graph,[x[:] for x in check],varNum,valueNum)

def main():

    varNum=int(sys.stdin.readline().strip())#number of variables which is also vertex
    edgeNum=int(sys.stdin.readline().strip())#connection between vertex
    valueNum=int(sys.stdin.readline().strip())#number of colors
    
    graph=[[] for x in range(varNum)]
    check=[[1 for x in range(valueNum)] for x in range(varNum)]
    check.append([-1 for x in range(varNum)])#check if each var colored or not
    # -1 stands for not colored and 0,1,2... is colored value
    check.append([valueNum for x in range(varNum)])

    for i in range(edgeNum):
        edge=[int(x) for x in (sys.stdin.readline()).split(' ') if x.strip()]
        graph[edge[0]].append(edge[1])
        graph[edge[1]].append(edge[0])
    #print(graph)
    
    forward(graph,check,varNum,valueNum)
    
                        
if __name__=="__main__":
    main()

