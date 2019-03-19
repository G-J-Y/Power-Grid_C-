
#include "Phase5.h"
#include <iostream>



Phase5(){
    player = nullptr;
}



Phase5(Player* pl, int n){
    player = pl;
    numOfPlayer = n;
    int payment[21] = {10, 22, 33, 44, 54, 64, 73, 82, 90, 98, 105, 112, 118, 124, 129, 134, 138, 142, 145, 148, 150};
    numOfPoweredCities = 0;
}


//every player indicates how many cities in his network he wishes
//(and is able) to supply with electricity. He earns cash based on the number of cities
//he powers as shown on the payment table
void Phase5::earnCash() {
    for(int i=0; i<n; i++){
        do{
            cout<<"How many cities do you wish to supply with electricity?"<<endl;
            cin>>numOfPoweredCities;
        }while(!validNumOfPoweredCities(i))

    }


}



bool Phase5::validNumOfPoweredCities(int i) {

    if(numOfPoweredCities<=player)

    return (numOfPoweredCities<=);
}