// 26. Remove Duplicates from Sorted Array

// Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place such that each unique element appears only once. The relative order of the elements should be kept the same. Then return the number of unique elements in nums.

// Consider the number of unique elements of nums to be k, to get accepted, you need to do the following things:

// Change the array nums such that the first k elements of nums contain the unique elements in the order they were present in nums initially. The remaining elements of nums are not important as well as the size of nums.
// Return k.


#include<iostream>
using namespace std;
int main(){
    int i,j,arr[6];
    for(i=0;i<=5;i++){
        cout<<"enter array elements"<<endl;
        cin>>arr[i];
    }
    for(i=0;i<=5;i++){
        for(j=i+1;j<=5;j++){
            if(arr[i]==arr[j]){
                cout<<arr[i]<<" is duplicate"<<endl;

            }
        }
    }

}
