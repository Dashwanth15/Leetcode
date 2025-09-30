
//136. Single Number

// Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.

// You must implement a solution with a linear runtime complexity and use only constant extra space.

 
#include <iostream>
using namespace std;
int main()
{
    int arr[]={1,1,2,2,3,4,4,5,5};
    int n=sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<n;i++){
        if((i==0||arr[i]!=arr[i-1])&&(i==n-1||arr[i]!=arr[i+1])){
            cout<<arr[i];
        }
    }
    return 0;
}