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