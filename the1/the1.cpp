#include "the1.h"

// swaps the elements by taking their adresses
void swapVar(unsigned short& var1,unsigned short& var2)
{
    unsigned short temp = var1;
    var1 = var2;
    var2 = temp;
}

// update the necessary variables after swap operation
void updateCtrlVar(int index1, int index2, long& swap, double& avg_dist, double& max_dist )
{
    int distance;
    if(index1<index2)
        distance = (index2 - index1);
    else
        distance = (index1 - index2);

    long double totalDistance = avg_dist*swap;
    totalDistance += distance;
    swap++;
    avg_dist = totalDistance/swap;
    if(distance>max_dist)
        max_dist = distance;

}

// take the median of first, middle and last elements put it in the pivot position
// the below operation doesn't take place if any two of the three values are equal
void medianOfThree(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool hoare, int size)
{
    if(size <3) return;
    
    int midIndex, firstIndex = 0, lastIndex = size-1;
    
    //find the middile index
    if((size%2)==1)
    {
        midIndex = (size-1)/2;
    }
    else
    {
        midIndex = (size/2)-1;
    }

    if ((arr[firstIndex] < arr[midIndex] && arr[midIndex] < arr[lastIndex]) || (arr[lastIndex] < arr[midIndex] && arr[midIndex] < arr[firstIndex])) //check for middle one
    {
        //middle element is median
        if(hoare == false)          //swap middle element with last element if the sort type is lomuto
        {
            swapVar(arr[midIndex],arr[lastIndex]);
            updateCtrlVar(lastIndex,midIndex,swap,avg_dist,max_dist);
        }
    }
    else if ((arr[midIndex] < arr[firstIndex] && arr[firstIndex] < arr[lastIndex]) || (arr[lastIndex] < arr[firstIndex] && arr[firstIndex] < arr[midIndex])) //check for first one
    {
        //first element is median
        if(hoare == false)          //swap first element with last element if the sort type is lomuto
        {
            swapVar(arr[firstIndex],arr[lastIndex]);
            updateCtrlVar(lastIndex,firstIndex,swap,avg_dist,max_dist);
        }
        else                        //swap first element with middle element if the sort type is hoare
        {
            swapVar(arr[firstIndex],arr[midIndex]);
            updateCtrlVar(midIndex,firstIndex,swap,avg_dist,max_dist);
        }
    }
    else if ((arr[midIndex] < arr[lastIndex] && arr[lastIndex] < arr[firstIndex]) || (arr[firstIndex] < arr[lastIndex] && arr[lastIndex] < arr[midIndex])) //check for last one
    {
        //last element is median
        if(hoare == true)           //swap last element with middle element if the sort type is hoare
        {
            swapVar(arr[lastIndex],arr[midIndex]);
            updateCtrlVar(midIndex,lastIndex,swap,avg_dist,max_dist);
        }
    }
}

int LomutoPartition(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, int size)
{
    unsigned short pivot = arr[size-1];
    int i = -1;
    for(int j=0; j<(size-1); j++)
    {
        if(arr[j] >= pivot)
        {
            i++;
            swapVar(arr[i],arr[j]);
            updateCtrlVar(i,j,swap,avg_dist,max_dist);
        }
    }
    swapVar(arr[i+1],arr[size-1]);
    updateCtrlVar(i+1,size-1,swap,avg_dist,max_dist);
    return(i+1);
}

int quickSortWithLomuto(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool median_of_3, int size)
{
    int calls = 1;
    if (size >1)
    {
        if(median_of_3 == true)
            medianOfThree(arr, swap, avg_dist, max_dist, false, size);
        int pivotIndex = LomutoPartition(arr,swap,avg_dist,max_dist,size);
        unsigned short* arrLeft = &arr[0];
        unsigned short* arrRight = &arr[pivotIndex+1];

	    calls += quickSortWithLomuto(arrLeft, swap, avg_dist,max_dist,median_of_3,pivotIndex);
	    calls += quickSortWithLomuto(arrRight, swap, avg_dist,max_dist,median_of_3,size-pivotIndex-1);
    }

    return calls;
}

int HoarePartition(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, int size)
{
    int midIndex;
    if(size%2==1)
        midIndex = (size-1)/2;
    else
        midIndex = (size)/2-1;
    unsigned short pivot = arr[midIndex];

    int i = -1;
    int j = size;

    while(true)
    {
        do{
           j--; 
        }
        while(arr[j] < pivot);
        
        do{
           i++; 
        }
        while(arr[i] > pivot);
        
        if(i<j)
        {
            swapVar(arr[i],arr[j]);
            updateCtrlVar(i,j,swap,avg_dist,max_dist);
        }
        else
        {
            return(j);
        }
    }
}

int quickSortWithHoare(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool median_of_3, int size)
{
    int calls = 1;
    if (size >1)
    {
        if(median_of_3 == true)
            medianOfThree(arr, swap, avg_dist, max_dist, true, size);
        int pivotIndex = HoarePartition(arr,swap,avg_dist,max_dist,size);
        unsigned short* arrLeft = &arr[0];
        unsigned short* arrRight = &arr[pivotIndex+1];

	    calls += quickSortWithHoare(arrLeft, swap, avg_dist,max_dist,median_of_3,pivotIndex+1);
	    calls += quickSortWithHoare(arrRight, swap, avg_dist,max_dist,median_of_3,size-pivotIndex-1);
    }

    return calls;
}

int quickSort(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool hoare, bool median_of_3, int size){

    max_dist = 0;
    avg_dist = 0;
    swap = 0;

    if(hoare == true)
	    return quickSortWithHoare(arr, swap, avg_dist,max_dist, median_of_3, size );
    else
	    return quickSortWithLomuto(arr, swap, avg_dist,max_dist, median_of_3, size);

}