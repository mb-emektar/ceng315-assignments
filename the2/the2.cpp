#include "the2.h"

// do not add extra libraries here
/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    ascending : true for ascending, false for descending 
    size      : number of elements in the array
*/

// find the element that has maximum number of letter digits
// we will use it while iterating
int find_max_element(std::string* arr, int size, int &iter_count)
{
    int max_num_of_letters = 0;
    for (int i = 0; i < size; i++)
    {
        if(arr[i].size()>max_num_of_letters)
            max_num_of_letters=arr[i].size();
    }

    return max_num_of_letters;
}

void counting_sort(std::string* A, int size, int current_digit , bool ascending, int &iter_count){

    // there are 26 uppercase English letters
    int letter_count=26;
    std::string B[size+1] = {};
    int C[letter_count+1] = {0}; //+1 for shorter strings

    // subtract 64 to map uppercase letters from 65-90 (according to ASCII) to 1-26 interval 
    // we will use 0th index for the shorter strings
    
    // find the frequency of letters 
    for(int j = 0; j < size; j++) 
    {
        if(A[j].size() < current_digit+1 ) // if the string is shorter
            C[0]++;
        else
            C[(A[j][current_digit]-64)]++;
        iter_count++;
    }
    
    // cumulative counting sort
    for(int i = 1; i < letter_count+1; i++) 
    {
        C[i]=C[i]+C[i-1];
        iter_count++;
    }
    
    // sort the strings to B according to current_index
    for(int i = 0, j=size-1; j > -1; j--) 
    {
        if(A[j].size() >= current_digit+1 )
        {
            B[C[A[j][current_digit]-64]-1] = A[j];
            C[A[j][current_digit]-64] = C[A[j][current_digit]-64]-1;
        }
        else // if the string is shorter
        {
            B[C[0]-1] = A[j];
            C[0]--;
        }
        iter_count++;

    }
    for(int j = 0, i = 0; i < size;i++) // copy the newly sorted array B into original array arr
    {
        A[i]=B[i];
        iter_count++;
    }
    
}

int radix_string_sort(std::string* arr, int size, bool ascending){

    int iter_count =0;
    int max_digits = find_max_element(arr,size,iter_count);

    // iterate based on the longest array
    for (int i = max_digits-1; i >-1 ; i-- ) 
        counting_sort(arr,size,i,ascending,iter_count);

    // simply reverse the array if the descending order is requested
    if (ascending == false)
    {
        for(int i = 0; i < size/2 ; i++)
        {
            std::string temp = arr[i];
            arr[i] = arr[size-1-i];
            arr[size-1-i] = temp;
        }
    }
    return iter_count;
}
