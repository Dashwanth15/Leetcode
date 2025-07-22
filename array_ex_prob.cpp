// 1.two sum problem
// Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

// You may assume that each input would have exactly one solution, and you may not use the same element twice.
#include<iostream>
using namespace std;
int main(){
    int sum=0;
    int arr[4]={2,7,11,15};
    for(int i=0;i<5;i++){
        for(int j=i+1;j<5;j++){
           sum=arr[i]+arr[j];
           if(sum==26){
            cout<<i<<"and"<<j<<endl;
           }
        }
    }
    return 0;

}
