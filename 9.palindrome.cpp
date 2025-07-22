// Given an integer x, return true if x is a palindrome,
// and false otherwise.

 
#include<iostream>
using namespace std;
int main()
{
    int x;  //here x is a number you have entered
    cout<<"enter a number";
    cin>>x;
    
    string s=to_string(x);  //converts number int o string
    int left=0;
    int right=s.length()-1;


    bool Palindrome=false;

    while(left<=right){
        if(s[left]=s[right]){
            Palindrome=true;
            break;
        }
        left ++;
        right--;
    }
    if (Palindrome){
        cout<<"true" <<endl;
    }else{
        cout<<"false"<<endl;
    }
}