#include "the5.h"

// do not add extra libraries here

bool recurs(int index, int nElements,std::vector<bool>& isVisited,const std::vector<std::vector<int>>& dependencyMatrix, std::vector<int>& compileOrder,std::vector<int>& isCycle, std::vector<std::vector<int>>& cyclicDependencies  )
{
    if(isVisited[index] == true)
        return 0;
    bool isInCycle = false;
    int indexOfCycleBegin;
    for(int i = 0; i < isCycle.size();i++)
        if(isCycle[i] == index){
            isInCycle = true;
            indexOfCycleBegin = i;
        }
    if(isInCycle)
    {
        /*for(int i = 0 ; i <indexOfCycleBegin; i++)
            isCycle.erase(isCycle.begin());
        cyclicDependencies.push_back(isCycle);
        isCycle.clear();*/
        return 1;
    }
    else
    {
        isCycle.push_back(index);
    }
    bool output = 0;
    for (int i = 0; i<nElements; i++)
    {
        if (dependencyMatrix[i][index] == 1)
            if(recurs(i,nElements,isVisited,dependencyMatrix, compileOrder,isCycle,cyclicDependencies)){
                output++;


            }
    }

    compileOrder.push_back(index);
    isVisited[index] = true;
    return output;
}

void run(const std::vector<std::vector<int>>& dependencyMatrix, 
         bool& isCompilable,
         std::vector<int>& compileOrder, 
         std::vector<std::vector<int>>& cyclicDependencies){
             
    int nElements = dependencyMatrix[0].size();
    std::vector<bool> isVisited(nElements,false);
    isCompilable = true;
    for (int i = 0; i<nElements; i++)
    {
        std::vector<int> isCycle;
        if (recurs(i,nElements,isVisited,dependencyMatrix, compileOrder,isCycle,cyclicDependencies))
        {
            isCompilable = false;
           cyclicDependencies.push_back(isCycle);
            isCycle.clear();
        }
    }

}