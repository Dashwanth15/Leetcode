#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    vector<int>numbers={1,2,2};
    sort(numbers.begin(),numbers.end(),greater<int>());
   
    int result=0;
    for(int i=0;i<numbers.size()-2;i++){
        
        if(numbers[i+1]+numbers[i+2]>numbers[i]){
            result=numbers[i]+numbers[i+1]+numbers[i+2];
             cout<<"perimeter of triange is: "<<result;
   
        }
        else{
            cout<<"enter correct dimenstions";
        }
        
        
       
       
   }
   
    
}