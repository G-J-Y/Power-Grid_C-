#define PROJECT_PHASE5_H


class Phase5 {
private:
    Player* player;    //player array
    int numOfPlayer;    //the size of player
    int payment [];     //payment corresponding to the number of powered cities
    int numOfPoweredCities  //the number of cities the player wants to power


public:
    Phase5();
    Phase5(Player*, int);
    void earnCash();                    //the players earn cash
    bool validNumOfPoweredCities(int);    //return if the input is valid for the number of cities the player wants to power




};


#endif //PROJECT_PHASE5_H
