#include<iostream>
using namespace std;
bool checkpossiblilyt(int *Requestarray,int Numberofsmokes,int rechargetime){
   int initial_charges=2;
   int first_recharge=-1;
   int second_recharge=-1;
   for(int i=0;i<Numberofsmokes;i++){
    if(first_recharge!=-1&&Requestarray[i]>=first_recharge){
        initial_charges++;
        first_recharge=-1;
    }
    if(second_recharge!=-1&&Requestarray[i]>=second_recharge){
        initial_charges++;
        second_recharge=-1;
    }
    if(initial_charges==0){
        return false;
    }
    initial_charges--;
    if(first_recharge==-1){
        first_recharge=Requestarray[i]+rechargetime;
    }
    else if(second_recharge==-1){
        second_recharge=first_recharge+rechargetime;
    }

}
return true;
}
int main(){
    int Numberofsmokes;
    int rechargetime;
    cout<<"Enter the number of smokes: ";
    cin>>Numberofsmokes;
    cout<<"Enter the recharge time: ";
    cin>>rechargetime;
    int *Requestarray= new int[Numberofsmokes];
    int numberoftests;
    cin>>numberoftests;
    cin.ignore();
    while(numberoftests--){
    for(int i=0;i<Numberofsmokes;i++){
        cin>>Requestarray[i];
    }
    if(checkpossiblilyt(Requestarray,Numberofsmokes,rechargetime)){
        cout<<"Yes"<<endl;
    }
    else{
        cout<<"No"<<endl;
    }
}
    delete[] Requestarray;
}