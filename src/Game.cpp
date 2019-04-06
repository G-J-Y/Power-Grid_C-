#include "Game.h"

//default constructor
Game::Game() {};

Game::Game(int numOfPlayer) {
    players = new Player[numOfPlayer];
    this->numOfPlayer = numOfPlayer;
    step = 1;
    turn = 1;
    powerPlants = vector<PowerPlant>(43);
    //graph = new Graph(42); //if not initialize here, there's no address for graph
    // myLoader.Load(graph, numOfPlayer) calls graph by reference, but graph has no address
}


void Game::loader() {
    //mapLoader myLoader;
    //myLoader.Load(graph, numOfPlayer);


    //create game map
    cout << "Please input the name of the map file: \n";
    string fileName;
    cin >> fileName;
    ifstream inputStream;
    inputStream.open(fileName);


    if (inputStream.fail()) {
        cout << "Wrong format of map file!";
        exit(1);
    }

    map<string, int> cityNameIDPair;
    int cityID = 0;
    string next;

    inputStream >> next; //read the first string in the file
    if (next != "[City]") //a map file should start with "[City]"
    {
        cout << "This is not a valid map file text!";
        exit(1);
    }

    //read the first part of the file (city name list)
    //stores them into map<string, int>
    while (!inputStream.eof()) {
        inputStream >> next;
        if (next == "[Edge]")
            break;
        //cout << next << endl;
        cityNameIDPair.insert(pair<string, int>(next, cityID));
        cityID++;  //after storing the last city, the city size still increment once
    }

    //read the second part of the text
    string firstCity;
    string secondCity;
    string distance;
    int intDistance;
    int size = cityID; //if there is 10 city, the cityID will be 10 now
    Graph gameMap(size);
    //gameMap = Graph(size);
    createBaseCity(&gameMap, cityNameIDPair);
    printGraph(&gameMap);
    cout << "2222\n";
    /**/
    while (!inputStream.eof()) {
        inputStream >> firstCity >> secondCity >> distance;
        //cout << firstCity << " " << secondCity << " " << distance << endl;
        intDistance = std::stoi(distance); //cast string to int
        addEdge(&gameMap, firstCity, secondCity, intDistance, cityNameIDPair);
    }


    printGraph(&gameMap);

    if (isConnected(&gameMap))
        cout << "The original map is a connected graph.\n";
    else
        cout << "The original map is not a connected graph.\n";

    //Now will create a map for certain number of players
    //2 players -- 3 regions
    //3 players -- 3 regions
    //4 players -- 4 regions
    //5 players -- 5 regions
    //6 players -- 6 regions //in game rule it's 6 players -- 5 regions
    //int numOfplayer;
    int numToRemove; //how many areas to be removed
    int areaToRemove; // which area to be removed
    //cout << "\nEnter the number of players (2-6): ";
    //cin >> numOfplayer;
    while (numOfPlayer < 2 || numOfPlayer > 6) {
        cout << "Must be a number from 2-6. Enter again: ";
        cin >> numOfPlayer;
    }

    switch (numOfPlayer) {
        case 2:
        case 3:
            numToRemove = 3;
            break;
        case 4:
            numToRemove = 2;
            break;
        case 5:
            numToRemove = 1;
            break;
        case 6:
            numToRemove = 0;
            break;
    }
    cout << "In this game, there will be " << numOfPlayer << " players.\n"
         << "You need to choose " << numToRemove << " area(s) you don't want (1 - 6).\n";

    //Graph* copy;

    while (true) {
        graph = new Graph(gameMap);
        for (int i = 0; i < numToRemove; i++) {
            cout << "\nEnter the " << i << "th area you don't want: ";
            cin >> areaToRemove;
            removeArea(graph, areaToRemove);
        }

        cout << "\n----------------Map After Choosing Areas--------------------\n";
        printGraph(graph);

        int test = 0;
        for (int i = 0; i < graph->getSize(); i++) {
            if (graph->getArr()[i].getHead() == NULL)
                test++;
            else break;
        }


        cout << "The number of cities left in the map: " << graph->numOfCities() << endl;
        if (isConnected2(graph, test)) {
            cout << "\nAll areas in the map is connected. Game starts. Good Luck!!\n\n";
            break;
        } else {
            cout << "\nNot all areas in the map is connected!! \nPlease choose the area you don't want again. \n";
            delete graph;
        }
    }

    //tests whether the game map is created well. If yes, it should print the map
    cout << "\n----------------Printing game map in Game::loader--------------- \n";
    printGraph(graph);
    cout << "----------------Finish printing in Game::loader---------------- \n\n";


    //set Player's name

    for (int i = 0; i < numOfPlayer; i++) {
        cout << "Please enter the name of Player " << (i + 1) << " :" << endl;
        string name;
        cin >> name;
        players[i].setName(name);
    }

    powerPlants[0] = PowerPlant(3, 2, PowerPlant::oil, 1);
    powerPlants[1] = PowerPlant(4, 2, PowerPlant::coal, 1);
    powerPlants[2] = PowerPlant(5, 2, PowerPlant::hybrid, 1);
    powerPlants[3] = PowerPlant(6, 1, PowerPlant::garbage, 1);
    powerPlants[4] = PowerPlant(7, 3, PowerPlant::oil, 2);
    powerPlants[5] = PowerPlant(8, 3, PowerPlant::coal, 2);
    powerPlants[6] = PowerPlant(9, 1, PowerPlant::oil, 1);
    powerPlants[7] = PowerPlant(10, 2, PowerPlant::coal, 2);
    powerPlants[8] = PowerPlant(11, 1, PowerPlant::uranium, 2);
    powerPlants[9] = PowerPlant(12, 2, PowerPlant::hybrid, 2);
    powerPlants[10] = PowerPlant(13, 0, PowerPlant::eco, 1);
    powerPlants[11] = PowerPlant(14, 2, PowerPlant::garbage, 2);
    powerPlants[12] = PowerPlant(15, 2, PowerPlant::coal, 3);
    powerPlants[13] = PowerPlant(16, 2, PowerPlant::oil, 3);
    powerPlants[14] = PowerPlant(17, 1, PowerPlant::uranium, 2);
    powerPlants[15] = PowerPlant(18, 0, PowerPlant::eco, 2);
    powerPlants[16] = PowerPlant(19, 2, PowerPlant::garbage, 3);
    powerPlants[17] = PowerPlant(20, 3, PowerPlant::coal, 5);
    powerPlants[18] = PowerPlant(21, 2, PowerPlant::hybrid, 4);
    powerPlants[19] = PowerPlant(22, 0, PowerPlant::eco, 2);
    powerPlants[20] = PowerPlant(23, 1, PowerPlant::uranium, 3);
    powerPlants[21] = PowerPlant(24, 2, PowerPlant::garbage, 4);
    powerPlants[22] = PowerPlant(25, 2, PowerPlant::coal, 5);
    powerPlants[23] = PowerPlant(26, 2, PowerPlant::oil, 5);
    powerPlants[24] = PowerPlant(27, 0, PowerPlant::eco, 3);
    powerPlants[25] = PowerPlant(28, 1, PowerPlant::uranium, 4);
    powerPlants[26] = PowerPlant(29, 1, PowerPlant::hybrid, 4);
    powerPlants[27] = PowerPlant(30, 3, PowerPlant::garbage, 6);
    powerPlants[28] = PowerPlant(31, 3, PowerPlant::coal, 6);
    powerPlants[29] = PowerPlant(32, 3, PowerPlant::oil, 6);
    powerPlants[30] = PowerPlant(33, 0, PowerPlant::eco, 4);
    powerPlants[31] = PowerPlant(34, 1, PowerPlant::uranium, 5);
    powerPlants[32] = PowerPlant(35, 1, PowerPlant::oil, 5);
    powerPlants[33] = PowerPlant(36, 3, PowerPlant::coal, 7);
    powerPlants[34] = PowerPlant(37, 0, PowerPlant::eco, 4);
    powerPlants[35] = PowerPlant(38, 3, PowerPlant::garbage, 7);
    powerPlants[36] = PowerPlant(39, 1, PowerPlant::uranium, 6);
    powerPlants[37] = PowerPlant(40, 2, PowerPlant::oil, 6);
    powerPlants[38] = PowerPlant(42, 2, PowerPlant::coal, 6);
    powerPlants[39] = PowerPlant(44, 0, PowerPlant::eco, 5);
    powerPlants[40] = PowerPlant(46, 3, PowerPlant::hybrid, 7);
    powerPlants[41] = PowerPlant(50, 0, PowerPlant::hybrid, 6);
    powerPlants[42] = PowerPlant(0, 0, PowerPlant::step3, 0);

    //put first 8 cards into market
    for (int i = 0; i < 8; i++) {
        market.push_back(powerPlants[0]);
        powerPlants.erase(powerPlants.begin());
    }
    //Print the cards in the market
    cout << "------------------------------Market------------------------------" << endl;
    for (size_t i = 0; i < market.size(); i++) {
        cout << market[i].toString() << endl;
    }
    cout << endl;



    //Initialize resources Market
    resources[0] = Resources(3, 0, 0, 0, 1);
    resources[1] = Resources(3, 0, 0, 0, 2);
    resources[2] = Resources(3, 3, 0, 0, 3);
    resources[3] = Resources(3, 3, 0, 0, 4);
    resources[4] = Resources(3, 3, 0, 0, 5);
    resources[5] = Resources(3, 3, 0, 0, 6);
    resources[6] = Resources(3, 3, 3, 0, 7);
    resources[7] = Resources(3, 3, 3, 0, 8);
    resources[8] = Resources(0, 0, 0, 0, 10);
    resources[9] = Resources(0, 0, 0, 0, 12);
    resources[10] = Resources(0, 0, 0, 1, 14);
    resources[11] = Resources(0, 0, 0, 1, 16);


}

void Game::phase1() {
    cout << "\n----------------Printing game map in Game::phase1--------------- \n";
    printGraph(graph);
    cout << "----------------Finish printing in Game::phase1---------------- \n\n";
    //give a random order in the first turn
    if (turn == 1) {
        shufflePlayers();
        for (int i = 0; i < numOfPlayer; i++) {
            //players[i].setNumOfCity(i);
            cout << players[i].getName() << endl;
            cout << players[i].toString() << endl;
            cout << endl;
        }
    }

    //
    cout << "------------------------------After shuffle------------------------------" << endl;
    PowerPlant::shuffle(powerPlants);
    /*for (int i = 0; i < powerPlants.size(); i++) {
        cout << powerPlants[i].toString() << endl;
    }*/
    cout << endl;

    //Find cards: powerPlant 13 & step 3
    if (turn == 1) {
        for (size_t i = 0; i < powerPlants.size(); i++) {
            if (powerPlants[i].getNumber() == 13) {
                PowerPlant temp1;
                temp1 = powerPlants[i];
                powerPlants[i] = powerPlants[0];
                powerPlants[0] = temp1;
            }
            if (powerPlants[i].getTypeName() == "step3") {
                PowerPlant temp2;
                temp2 = powerPlants[i];
                powerPlants[i] = powerPlants[powerPlants.size() - 1];
                powerPlants[powerPlants.size() - 1] = temp2;
            }

        }
        cout << "--------------------After Setting Card Number13 & Card Step3--------------------" << endl;
        for (size_t i = 0; i < powerPlants.size(); i++) {
            cout << powerPlants[i].toString() << endl;
        }
        cout << endl;


        //auction process
        auctionPhase();


        cout << "Phase finish" << endl;
        cout << endl;

        //if no one buy card, delete the smallest one
        if (checkNoOneBuyCard()) {
            cout << "No one buy power plant card in this turn" << endl;
            cout << "------------------------------Market (Updated)------------------------------" << endl;
            market[0] = powerPlants.front();
            setMarketOrder(market);
            powerPlants.erase(powerPlants.begin());
            for (size_t i = 0; i < market.size(); i++) {
                cout << market[i].toString() << endl;
            }
            cout << endl;
        }


        // set the order of the players at the end of each turn
        setPlayerOrder(players, numOfPlayer);
        cout << "New order of the players " << endl;
        for (int i = 0; i < numOfPlayer; i++) {
            cout << players[i].getName() << endl;
            cout << players[i].toString() << endl;
            cout << endl;
        }

        cout << "Moving to the next phase" << endl;
        //turn++;
        cout << endl;
    }
}

void Game::phase3() {


    std::cout << "[INFO] PHASE3: Buying Resources" << std::endl;
    for (int i = numOfPlayer - 1; i >= 0; i--) {
        std::cout << "[INFO] " << players[i].getName() << ", it's your turn now!" << std::endl;
        std::cout << players[i].toString();
        std::cout << std::endl;

        std::cout << "[INFO] Here is the Resource Market:" << std::endl;


        for (int i = 0; i < 12; i++) {
            std::cout << resources[i].toString() << std::endl;
        }


        buyResources(i);

    }
}

void Game::phase4(){
    std::cout << "[INFO] PHASE4: Building" << std::endl;
    bool goToStep3 = false;
    for (int i = numOfPlayer - 1; i >= 0; i--) {
        std::cout << std::endl;
        printGraph(graph);
        std::cout << "[INFO]" << players[i].getName() << ", it's your turn!" << std::endl;
        while (true) {

            //check the step
            if (numOfPlayer == 2) {
                if (players[i].getNumOfCity() == 10) {
                    if (step == 1) {
                        step = 2;
                        goToStep3 = adjustMarket(step);
                    }
                }
            }
            if (numOfPlayer == 3 || numOfPlayer == 4 || numOfPlayer == 5) {
                if (players[i].getNumOfCity() == 7) {
                    if (step == 1) {
                        step = 2;
                        goToStep3 = adjustMarket(step);
                    }
                }
            }
            if (numOfPlayer == 6) {
                if (players[i].getNumOfCity() == 6) {
                    if (step == 1) {
                        step = 2;
                        goToStep3 = adjustMarket(step);
                    }
                }
            }

            std::cout << "[PROMPT]" << "Please enter the ID of the city that you want to build.(Enter -1 to skip)"
                      << std::endl;
            std::cout << "[ENTER] ";
            int inputNum;
            std::cin >> inputNum;
            std::cout << std::endl;

            if (inputNum == -1) {
                break;
            }

            vector<string> owners = graph->getArr()[inputNum].getBase()->getOwners();
            size_t size = owners.size();


            //check if the city is on the map
            if (graph->getArr()[inputNum].getHead() == NULL) {
                cout << "[ERROR] This city is not on the map. Please try another city!!\n";
                continue;
            }

            //check if the player have already built one
            bool isBuilt = false;
            for (size_t j = 0; j < size; j++) {
                if (players[j].getName() == owners[j]) {
                    cout << "[ERROR] You have owned this city. Please try another city!!\n";
                    isBuilt = true;
                    continue;
                }
            }
            if (isBuilt) { continue; }

            //check if there is enough space
            if (size >= (size_t) step) {
                std::cout << "[ERROR] You can not build plant in this city because there is no more space!"
                          << std::endl;
                continue;
            }

            //check if player has enough money
            int price = graph->getArr()[inputNum].getBase()->getPrice(size);
            //add network price
            price += graph->lowestPathPrice(inputNum, players[i].getName());
            if (players[i].getMoney() < price) {
                std::cout << "[ERROR] You do not have enough money. Please try another city!" << std::endl;
                continue;
            }

            graph->getArr()[inputNum].getBase()->addOwner(players[i].getName());
            players[i].setMoney(players[i].getMoney() - price);
            players[i].setNumOfCity(players[i].getNumOfCity() + 1);
            std::cout << "[SUCCESS] You have built a house in " << graph->getArr()[inputNum].getBase()->getName()
                      << " successfully." << std::endl;
            std::cout << "[SUCCESS] It cost you  " << price << " Elektro. Now you have " << players[i].getMoney()
                      << " Elektro." << std::endl;

        }
        printGraph(graph);
    }
    if (goToStep3) {
        step = 3;
    }
}


//check winning
bool Game::checkWin(){
    for(int i=0; i<numOfPlayer; i++){
        if(players[i].getNumOfCity()==7)  //just test, need to change to 17
            return true;
    }
    return false;
}

void Game::phase5() {
    //phase 5 begins

    Resources recycle;
    cout << "[INFO] PHASE5: Bureaucracy" << endl;
    earnCash(recycle);


    //print the resources in the market before re-supply
    cout << "[INFO] Here is the Resource Market:" << endl;
    for (int i = 0; i < 12; i++) {
        cout << resources[i].toString() << endl;
    }
    cout << "-----------------------------------------------" << endl;

    //re-supply the resource market
    reSupplyResource(recycle);

    //print the resources after re-supply
    cout << "-----------------------------------------------" << endl;
    std::cout << "[INFO] Here is the Resource Market:" << std::endl;
    for (int i = 0; i < 12; i++) {
        cout << resources[i].toString() << endl;
    }


    //update the power plant market
    updateMarket();

    //print the power plant market and the draw stack
    cout << "-----------------------------------------------" << endl;
    std::cout << "[INFO] Here is the Power Plant Market:" << std::endl;
    for (size_t i = 0; i < market.size(); i++) {
        cout << market[i].toString() << endl;
    }
    cout << "-----------------------------------------------" << endl;
    std::cout << "[INFO] Here is the Power Plant Draw Stack:" << std::endl;
    for (size_t i = 0; i < powerPlants.size(); i++) {
        cout << powerPlants[i].toString() << endl;
    }

    //each player possession at the end of this phase
    cout << "-----------------------------------------------" << endl;
    cout << "Each player possession at the end of this phase 5:" << endl;
    Player::printPlayerPossession(players, numOfPlayer);
}




//phase1_2 methods
int currentAuctionPrice = 0;
int indexOfCard = 0;
PowerPlant currentPowerPlant;

//in the first turn, the order of players is random
void Game::shufflePlayers() {
    int value;
    Player temp;

    if (players == NULL || numOfPlayer == 0)
        return;
    //change the random number
    srand((unsigned) time(NULL));
    for (int i = 0; i < numOfPlayer; i++) {
        //create a random number
        value = rand() % numOfPlayer;
        //shuffle
        temp = players[i];
        players[i] = players[value];
        players[value] = temp;
    }

}

//set the order of the players
void Game::setPlayerOrder(Player p[], int n) {
    Player temp;
    int cardPrice1;
    int cardPrice2;
    for (int i = 1; i < n; i++) {
        for (int j = n - 1; j > i - 1; j--) {
            if (p[j].getNumOfCity() > p[j - 1].getNumOfCity()) {
                temp = p[j];
                p[j] = p[j - 1];
                p[j - 1] = temp;
            } else if (p[j].getNumOfCity() == p[j - 1].getNumOfCity()) {
                cardPrice1 = p[j].getPowerPlant(0).getNumber();
                cardPrice2 = p[j - 1].getPowerPlant(0).getNumber();
                //need to create a method that set the powerPlant cards from big to small
                if (cardPrice1 > cardPrice2) {
                    temp = p[j];
                    p[j] = p[j - 1];
                    p[j - 1] = temp;
                }
            }
        }
    }
}

//every time a new card put into the market, set a new order
void Game::setMarketOrder(vector<PowerPlant> &p) {
    PowerPlant temp;
    for (int i = 1; i < p.size(); i++) {
        for (int j = p.size() - 1; j > i - 1; j--) {
            if (p[j].getNumber() < p[j - 1].getNumber()) {
                temp = p[j];
                p[j] = p[j - 1];
                p[j - 1] = temp;
            }

        }
    }
}

//every time players buy a new card, set the order of card owned by player
void Game::setCardOwnedByPlayer(Player &p) {
    PowerPlant big;
    PowerPlant small;
    for (int i = 1; i < p.getNumOfPowerPlant(); i++) {
        for (int j = p.getNumOfPowerPlant() - 1; j > i - 1; j--) {
            if (p.getPowerPlant(j).getNumber() > p.getPowerPlant(j - 1).getNumber()) {
                big = p.getPowerPlant(j);
                small = p.getPowerPlant(j - 1);
                p.setPowerPlant(big, j - 1);
                p.setPowerPlant(small, j);
            }

        }
    }
}

//return excess resources
void Game::checkReturnResources(Player &p) {
    int coal_max = 0;
    int oil_max = 0;
    int garbage_max = 0;
    int uranium_max = 0;
    int hybrid_max = 0;
    bool isHybrid = false;
    //calculate the total amount of each resource
    for (int i = 0; i < p.getNumOfPowerPlant(); i++) {
        if (p.getPowerPlant(i).getTypeName() == "coal") {
            coal_max += p.getPowerPlant(i).getNeed() * 2;
        }
        if (p.getPowerPlant(i).getTypeName() == "oil") {
            oil_max += p.getPowerPlant(i).getNeed() * 2;
        }
        if (p.getPowerPlant(i).getTypeName() == "garbage") {
            garbage_max += p.getPowerPlant(i).getNeed() * 2;
        }
        if (p.getPowerPlant(i).getTypeName() == "uranium") {
            uranium_max += p.getPowerPlant(i).getNeed() * 2;
        }
        if (p.getPowerPlant(i).getTypeName() == "hybrid") {
            isHybrid = true;
            hybrid_max += p.getPowerPlant(i).getNeed() * 2;
        }
    }
    int coalOilHybrid_max = coal_max + oil_max + hybrid_max;
    //calculate the maximum resources a player can hold
    int coal_player = p.getCoalNum();
    int oil_player = p.getOilNum();
    int garbage_player = p.getGarbageNum();
    int uranium_player = p.getUraniumNum();
    int coalOilHybrid_player = coal_player + oil_player;

    if (isHybrid == true) {
        int excess_coal = coal_player - coal_max;
        int excess_oil = oil_player - oil_max;
        if (excess_coal + excess_oil > hybrid_max) {
            if (excess_coal > 0 && excess_oil <= 0) {
                if (coal_player - (coal_max + hybrid_max > 0)) {
                    cout << "Excess and return " << coal_player - (coal_max + hybrid_max) << " coal" << endl;
                    p.setCoalNum(coal_max);
                }

            } else if (excess_oil > 0 && excess_coal <= 0) {
                if (oil_player - (oil_max + hybrid_max) > 0) {
                    cout << "Excess and return " << oil_player - (oil_max + hybrid_max) << " oil" << endl;
                    p.setOilNum(oil_max);
                }
            } else {                                                      //excess_coal > 0 && excess_oil > 0
                int keep;
                int leftHybridSpace;
                cout << "Excess " << excess_coal << " coal, and you have " << hybrid_max << " hybrid space" << endl;
                cout << "The coal resources do you want to put in hybrid: ";
                cin >> keep;
                while (keep < 0 || keep > hybrid_max) {
                    cout << "The number you enter is exceed, please enter a valid number: ";
                    cin >> keep;
                }
                cout << "Excess and return " << excess_coal - keep << " coal" << endl;
                p.setCoalNum(coal_max + keep);
                leftHybridSpace = hybrid_max - keep;
                if (excess_oil - leftHybridSpace > 0) {
                    cout << "Excess and return " << excess_oil - leftHybridSpace << " oil" << endl;
                    p.setOilNum(oil_max + leftHybridSpace);
                }
            }
            if (garbage_player > garbage_max) {
                cout << "Excess and return " << garbage_player - garbage_max << " garbage" << endl;
                p.setGarbageNum(garbage_max);
            }
            if (uranium_player > uranium_max) {
                cout << "Excess and return " << uranium_player - uranium_max << " uranium" << endl;
                p.setUraniumNum(uranium_max);
            }
        }
    } else {
        if (coal_player > coal_max) {
            cout << "Excess and return " << coal_player - coal_max << " coal" << endl;
            p.setCoalNum(coal_max);
        }
        if (oil_player > oil_max) {
            cout << "Excess and return " << oil_player - oil_max << " oil" << endl;
            p.setOilNum(oil_max);
        }
        if (garbage_player > garbage_max) {
            cout << "Excess and return " << garbage_player - garbage_max << " garbage" << endl;
            p.setGarbageNum(garbage_max);
        }
        if (uranium_player > uranium_max) {
            cout << "Excess and return " << uranium_player - uranium_max << " uranium" << endl;
            p.setUraniumNum(uranium_max);
        }
    }


}

//check if the cards owned by players over 4
void Game::buyCard(Player &p, PowerPlant card) {
    int num = p.getNumOfPowerPlant();

    if (num >= 3) {
        int cardNumber;
        bool success = false;
        cout << p.getName() << ", The maximum number of cards of players is 3, now you own: " << endl;
        for (int i = 0; i < num; i++) {
            cout << p.getPowerPlant(i).toString() << endl;
        }
        cout << endl;
        cout << "The new card you bought: " << endl;
        cout << card.toString() << endl;
        cout << endl;
        cout << "Please enter the number of the card you want to switch: ";
        cin >> cardNumber;
        do {
            for (int j = 0; j < num; j++) {
                if (p.getPowerPlant(j).getNumber() == cardNumber) {
                    success = true;

                    //switch
                    p.setPowerPlant(card, j);
                    setCardOwnedByPlayer(p);
                    cout << "Success! Now you own: " << endl;
                    p.setMoney(p.getMoney() - card.getNumber());

                    //print
                    for (int i = 0; i < num; i++) {
                        cout << p.getPowerPlant(i).toString() << endl;
                    }
                    cout << endl;

                    //check resouces method
                    checkReturnResources(p);
                    cout << endl;
                }
            }
            if (success == false) {
                cout << "You don't have this card please enter a correct number: ";
                cin >> cardNumber;
            }
        } while (success == false);


    } else {
        p.setPowerPlant(card, num);
        p.setBought(true);
        p.setMoney(p.getMoney() - card.getNumber());
        num = num + 1;
        p.setNumOfPowerPlant(num);
    }

}

//check if no one buy card in this turn
bool Game::checkNoOneBuyCard() {
    int numOfPassRound = 0;
    for (int i = 0; i < numOfPlayer; i++) {
        if (players[i].getRoundStatus() == false) {
            numOfPassRound++;
        }
    }
    if (numOfPassRound == numOfPlayer) {
        return true;
    } else {
        return false;
    }
}

//if draw step3 card
void Game::changeMarketToStep3(vector<PowerPlant> &p) {
    p.pop_back();
    p.erase(p.begin());
}

//check if a player can buy a card
void Game::abilityOfPurchase(int c) {
    if (step == 3) {
        for (int i = 0; i < market.size(); i++) {
            if (market[i].getNumber() == c) {
                currentPowerPlant = market[i];
                indexOfCard = i;
            }
        }
        while (currentPowerPlant.getNumber() == 0) {
            int choice;
            cout << "You cannot buy this card, please enter a new number: ";
            cin >> choice;
            for (int i = 0; i < market.size(); i++) {
                if (market[i].getNumber() == choice) {
                    currentPowerPlant = market[i];
                    indexOfCard = i;
                }
            }
        }
    } else {
        for (int i = 0; i < 4; i++) {
            if (market[i].getNumber() == c) {
                currentPowerPlant = market[i];
                indexOfCard = i;
            }
        }
        while (currentPowerPlant.getNumber() == 0) {
            int choice;
            cout << "You cannot buy this card, please enter a new number: ";
            cin >> choice;
            for (int i = 0; i < 4; i++) {
                if (market[i].getNumber() == choice) {
                    currentPowerPlant = market[i];
                    indexOfCard = i;
                }
            }
        }
    }
}

//this method set the status of the player to "pass"
void Game::pass(Player &p) {
    p.setAuction(false);
}

//this method set the price when in the auction process
void Game::auction(Player &p, PowerPlant n,int &passNum) {
    //currentAuctionPrice;
    int price;
    cout << "Please enter the price you auction: ";
    cin >> price;
    if (price > p.getMoney()) {
        do {
            cout << "You don't have enough money " << endl;
            cout << "Enter another price" << endl;
            cout << "Enter 0 to pass" << endl;
            cin >> price;
            if (price == 0) {
                pass(p);
				passNum++;
                break;
            }
        } while (price > p.getMoney());
    } else if (currentAuctionPrice == 0) {
        if (price < n.getNumber()) {
            do {
                cout << "The price is cheaper than current price" << endl;
                cout << "Enter another price" << endl;
                cout << "Enter 0 to pass" << endl;
                cin >> price;
                if (price == 0) {
                    pass(p);
					passNum++;
                    break;
                }
            } while (price < currentAuctionPrice);
        }
    } else if (currentAuctionPrice != 0) {
        if (price <= currentAuctionPrice) {
            //the first person can give == card price but second cannot
            do {
                cout << "The price should higher than current price" << endl;
                cout << "Enter another price" << endl;
                cout << "Enter 0 to pass" << endl;
                cin >> price;
                if (price == 0) {
                    pass(p);
					passNum++;
                    break;
                }
            } while (price <= currentAuctionPrice);
        }
    }

    cout << endl;

    if (price != 0) {
        currentAuctionPrice = price;
        cout << "The current price is: " << currentAuctionPrice << endl;
        cout << endl;
        p.setPrice(price);
    }

}


void Game::auctionPhase() {   //*player
    //start the auction, status: pass(0) || auction(1)
    int status;

    //in the first turn, each players must buy one power plant
    if (turn == 1) {
        int playerLeft = numOfPlayer;
        //PowerPlant currentPowerPlant;

        while (playerLeft > 1) {
            int choice;
            //int indexOfCard;

            // auction process
            int numOfPlayerPass = 0;
            while (numOfPlayerPass < playerLeft - 1) {
                for (int i = 0; i < numOfPlayer; i++) {
                    if (players[i].getNumOfPowerPlant() == 1) {
                        pass(players[i]);

                    } else {
                        if (numOfPlayerPass >= playerLeft - 1) {
                            break;
                        }
                        //cout << "Status:" << players[i].getAuction() << endl;
                        if (players[i].getAuction() == true) {

                            cout << players[i].getName() << endl;
                            cout << "It's your turn" << endl;

                            //who's turn right now
                            /*cout << players[i].getName() << endl;
                            cout << "It's your turn" << endl;*/
                            cout << "Auction -> Enter: 1" << endl;
                            cout << "Pass -> Enter: 0" << endl;
                            cin >> status;
                            cout << endl;

                            while (status != 0 && status != 1) {
                                cout << "Please enter a correct number" << endl;
                                cout << "Auction -> Enter: 1" << endl;
                                cout << "Pass -> Enter: 0" << endl;
                                cin >> status;
                            }
                            //in the first turn, no player can pass the whole round, each player should buy a power plant card
                            if (currentPowerPlant.getNumber() == 0 && status == 0) {
                                do {
                                    cout << "This is the first turn, you cannot pass your round" << endl;
                                    cout << "Please enter 1 to start auction" << endl;
                                    cin >> status;
                                } while (status != 1);
                            }

                            if (status == 0) {
                                pass(players[i]);
                                numOfPlayerPass++;
                            } else {

                                //if no card is auction
                                if (currentPowerPlant.getNumber() == 0) {
                                    //Print the cards in the market
                                    cout << "------------------------------Market------------------------------"
                                         << endl;
                                    for (int i = 0; i < market.size(); i++) {
                                        cout << market[i].toString() << endl;
                                    }
                                    cout << endl;
                                    //choose a card to auction
                                    cout << "Enter the number of the card in the market to start auction: ";
                                    cin >> choice;

                                    //check if the card is exist
                                    abilityOfPurchase(choice);

                                }

                                if (numOfPlayerPass < playerLeft - 1) {
                                    auction(players[i], market[indexOfCard],numOfPlayerPass);			
                                    //cout <<"Price" <<players[i].getPrice() << endl;
                                }

                            }

                        }

                    }
                }
            }
            //the number of player who doesn't buy the card
            playerLeft--;
            //who buy this card
            for (int i = 0; i < numOfPlayer; i++) {
                if (players[i].getAuction() == true && currentPowerPlant.getNumber() != 0) {
                    int num = players[i].getNumOfPowerPlant();
                    players[i].setPowerPlant(market[indexOfCard], num);
                    players[i].setMoney(players[i].getMoney() - market[indexOfCard].getNumber());
                    //print the information of the card
                    cout << "Congratulation, " << players[i].getName() << endl;
                    cout << "You get: " << endl;
                    cout << currentPowerPlant.toString() << endl;
                    cout << endl;

                    num = players[i].getNumOfPowerPlant() + 1;
                    players[i].setNumOfPowerPlant(num);

                }
            }

            //draw a new plant card, put it in the market and change the order
            market[indexOfCard] = powerPlants.front();
            powerPlants.erase(powerPlants.begin());
            setMarketOrder(market);

            //reset the status to true
            for (int i = 0; i < numOfPlayer; i++) {
                players[i].setAuction(true);
            }

            //reset auction price and auction card
            currentPowerPlant.setNumber(0);
            currentAuctionPrice = 0;
            //numOfPlayerPass = 0;
            indexOfCard = 0;

            //Print the cards in the market
            cout << "------------------------------Market (Updated)------------------------------" << endl;
            for (int i = 0; i < market.size(); i++) {
                cout << market[i].toString() << endl;
            }
            cout << endl;


        }

        //only one player left
        if (playerLeft == 1) {
            int who = 0;
            int choice;
			int numOfPass = numOfPlayer-1;
            for (int i = 0; i < numOfPlayer; i++) {
                if (players[i].getNumOfPowerPlant() == 0) {
                    who = i;
                }
            }
            //who's turn right now
            cout << players[who].getName() << endl;
            cout << "You are the last one" << endl;
            //choose a card to auction
            cout << "Enter the number of the card you want: ";
            cin >> choice;
            cout << endl;

            //check if the card is exist
            abilityOfPurchase(choice);

            auction(players[who], market[indexOfCard],numOfPass);
            //set card and money

            buyCard(players[who], market[indexOfCard]);
            /*  int num = players[who].getNumOfPowerPlant();
              players[who].setPowerPlant(market[indexOfCard], num);
              players[who].setMoney(players[who].getMoney() - market[indexOfCard].getNumber());*/

            //print the information of the card
            cout << "Congratulation, " << players[who].getName() << endl;
            cout << "You get: " << endl;
            cout << currentPowerPlant.toString() << endl;
            cout << endl;

            /*num = players[who].getNumOfPowerPlant() + 1;
            players[who].setNumOfPowerPlant(num);*/

            //draw a new plant card, put it in the market and change the order
            market[indexOfCard] = powerPlants.front();
            powerPlants.erase(powerPlants.begin());
            setMarketOrder(market);

            //reset auction price and auction card
            currentPowerPlant.setNumber(0);
            currentAuctionPrice = 0;
            //numOfPlayerPass = 0;
            indexOfCard = 0;

            //Print the cards in the market
            cout << "------------------------------Market (Updated)------------------------------" << endl;
            for (int i = 0; i < market.size(); i++) {
                cout << market[i].toString() << endl;
            }
            cout << endl;
        }
        //print every players' information
        cout << "Each player has a power plant card now" << endl;
        cout << endl;

        // set the order of the players at the end of each turn
        setPlayerOrder(players, numOfPlayer);
        for (int i = 0; i < numOfPlayer; i++) {
            cout << players[i].getName() << endl;
            cout << players[i].toString() << endl;
            cout << endl;
        }

        cout << "Moving to the next phase" << endl;
        turn++;
        cout << endl;

    }


        //****************************************************turn > 1***************************************************
    else {
        int playerLeft = numOfPlayer;
        //start turn
        while (playerLeft > 1) {
            int choice;
            //int indexOfCard;

            //reset the status to true
            /*for (int i = 0; i < numOfPlayer; i++) {
                players[i].setAuction(true);
            }
*/
            // auction process
            int numOfPlayerPass = 0;

            while (numOfPlayerPass < playerLeft - 1) {
                for (int i = 0; i < numOfPlayer; i++) {
                    if (numOfPlayerPass >= playerLeft - 1) {
                        break;
                    }
                    if (players[i].getRoundStatus() == false || players[i].getBought() == true) {
                        pass(players[i]);
                    } else {
                        //cout << "Bought?" << players[i].getBought() << endl; //test
                        if (players[i].getAuction() == true) {

                            cout << players[i].getName() << endl;
                            cout << "It's your turn" << endl;
                            cout << "Pass the whole round -> Enter: 9" << endl;
                            cout << "Auction -> Enter: 1" << endl;
                            cout << "Pass -> Enter: 0" << endl;
                            cin >> status;
                            cout << endl;

                            while (status != 0 && status != 1 && status != 9) {
                                cout << "Please enter a correct number" << endl;
                                cout << "Pass the whole round -> Enter: 9" << endl;
                                cout << "Auction -> Enter: 1" << endl;
                                cout << "Pass -> Enter: 0" << endl;
                                cin >> status;
                            }
                            //in the first turn, no player can pass the whole round, each player should buy a power plant card
                            if (currentPowerPlant.getNumber() == 0 && status == 0) {
                                do {
                                    cout
                                            << "This is the process of auction. If you want to pass the whole round, please enter 9: "
                                            << endl;
                                    cin >> status;
                                    while (status != 0 && status != 1 && status != 9) {
                                        cout << "Please enter a correct number" << endl;
                                        cout << "Pass the whole round -> Enter: 9" << endl;
                                        cout << "Auction -> Enter: 1" << endl;
                                        cin >> status;
                                    }
                                } while (status == 0);
                            }
                            if (currentPowerPlant.getNumber() != 0 && status == 9) {
                                do {
                                    cout
                                            << "This is the process of auction.You cannot pass the whole round, please enter 0 to pass auction: ";
                                    cin >> status;
                                    cout << endl;
                                    while (status != 0 && status != 1 && status != 9) {
                                        cout << "Please enter a correct number" << endl;
                                        cout << "Pass the whole round -> Enter: 9" << endl;
                                        cout << "Auction -> Enter: 1" << endl;
                                        cin >> status;
                                    }
                                } while (status == 9);
                            }

                            if (status == 0) {
                                pass(players[i]);
                                numOfPlayerPass++;
                            } else if (status == 9) {
                                players[i].setRoundStatus(false);
                                pass(players[i]);
                                numOfPlayerPass++;
                                playerLeft--;

                            } else {

                                if (currentPowerPlant.getNumber() == 0) {
                                    //if no card is auction, choose a card to start auction
                                    cout << "Enter the number of the card in the market to start auction: ";
                                    cin >> choice;
                                    //check if the card is exist
                                    abilityOfPurchase( choice);
                                }

                                if (numOfPlayerPass < playerLeft - 1) {
                                    auction(players[i], market[indexOfCard],numOfPlayerPass);
                                }

                            }

                        }


                    }
                }
            }
            //the number of player who doesn't buy the card
            //playerLeft--;
            //who buy this card
            for (int i = 0; i < numOfPlayer; i++) {
                if (players[i].getAuction() == true && currentPowerPlant.getNumber() != 0) {

                    buyCard(players[i], market[indexOfCard]);

                    //print the information of the card
                    cout << "Congratulation, " << players[i].getName() << endl;
                    cout << "You get: " << endl;
                    cout << currentPowerPlant.toString() << endl;
                    cout << endl;

                    playerLeft--;

                    //draw a new plant card, put it in the market and change the order
                    market[indexOfCard] = powerPlants.front();
                    if (powerPlants.front().getTypeName() == "step3") {
                        step = 3;
                        setMarketOrder(market);
                        changeMarketToStep3(market);
                        powerPlants.erase(powerPlants.begin());
                    } else {
                        powerPlants.erase(powerPlants.begin());
                        setMarketOrder(market);
                    }

                    ////**************check step3 process****************
                    //changeMarketToStep3(market);
                    //cout << "------------------------------Market (Step 3)------------------------------" << endl;//test
                    //for (int i = 0; i < market.size(); i++) {
                    //	cout << market[i].toString() << endl;
                    //}
                    //cout << endl;

                }

            }
            //reset the status to true
            for (int i = 0; i < numOfPlayer; i++) {
                players[i].setAuction(true);
            }

            //reset auction price and auction card
            currentPowerPlant.setNumber(0);
            currentAuctionPrice = 0;
            //numOfPlayerPass = 0;
            indexOfCard = 0;

            //Print the cards in the market
            cout << "------------------------------Market (Updated)------------------------------" << endl;
            for (int i = 0; i < market.size(); i++) {
                cout << market[i].toString() << endl;
            }
            cout << endl;

        }

        //only one player left
        if (playerLeft == 1) {
            int who;
            int choice;
			int numOfPass = numOfPlayer - 1;
            for (int i = 0; i < numOfPlayer; i++) {
                if (players[i].getBought() == false && players[i].getRoundStatus() == true) {
                    who = i;
                    //who's turn right now
                    cout << players[who].getName() << endl;
                    cout << "You are the last player" << endl;
                    cout << "Pass the whole round -> Enter: 9" << endl;
                    cout << "Auction -> Enter: 1" << endl;
                    cin >> status;
                    cout << endl;

                    while (status != 1 && status != 9) {
                        cout << "Please enter a correct number" << endl;
                        cout << "Pass the whole round -> Enter: 9" << endl;
                        cout << "Auction -> Enter: 1" << endl;
                        cout << "Pass -> Enter: 0" << endl;
                        cin >> status;
                    }

                    if (status == 9) {
                        players[who].setRoundStatus(false);
                        pass(players[who]);
                        playerLeft--;

                    } else {

                        if (currentPowerPlant.getNumber() == 0) {
                            //choose a card to auction
                            cout << "Enter the number of the card in the market to start auction: ";
                            cin >> choice;
                            //check if the card is exist
                            abilityOfPurchase(choice);

                        }
                        auction(players[who], market[indexOfCard],numOfPass);

                        buyCard(players[who], market[indexOfCard]);

                        //print the information of the card
                        cout << "Congratulation, " << players[who].getName() << endl;
                        cout << "You get: " << endl;
                        cout << currentPowerPlant.toString() << endl;
                        cout << endl;

                        //draw a new plant card, put it in the market and change the order
                        market[indexOfCard] = powerPlants.front();
                        if (powerPlants.front().getTypeName() == "step3") {
                            step = 3;
                            setMarketOrder(market);
                            changeMarketToStep3(market);
                            powerPlants.erase(powerPlants.begin());
                        } else {
                            powerPlants.erase(powerPlants.begin());
                            setMarketOrder(market);
                        }

                        //reset the status to true
                        for (int i = 0; i < numOfPlayer; i++) {
                            players[i].setAuction(true);
                        }

                        //reset auction price and auction card
                        currentPowerPlant.setNumber(0);
                        currentAuctionPrice = 0;
                        //numOfPlayerPass = 0;
                        indexOfCard = 0;

                    }


                }
            }

        }

        //reset the Bought status to false
        for (int i = 0; i < numOfPlayer; i++) {
            players[i].setBought(false);
        }

        //Print the cards in the market
        cout << "------------------------------Market (Updated)------------------------------" << endl;
        for (int i = 0; i < market.size(); i++) {
            cout << market[i].toString() << endl;
        }
        cout << endl;

    }
}







//phase3_4 methods
void Game::buyResources(int i) {
    int coalMax = 0;
    int oilMax = 0;
    int garbageMax = 0;
    int uraniumMax = 0;
    int hybridMax = 0;

    for (int j = 0; j < players[i].getNumOfPowerPlant(); j++) {
        PowerPlant pp = players[i].getPowerPlant(j);
        if (pp.getTypeName() == "coal") {
            coalMax += pp.getNeed() * 2;
        }
        if (players[i].getPowerPlant(j).getTypeName() == "oil") {
            oilMax += pp.getNeed() * 2;
        }
        if (players[i].getPowerPlant(j).getTypeName() == "garbage") {
            garbageMax += pp.getNeed() * 2;
        }
        if (players[i].getPowerPlant(j).getTypeName() == "uranium") {
            uraniumMax += pp.getNeed() * 2;
        }
        if (players[i].getPowerPlant(j).getTypeName() == "hybrid") {
            hybridMax += pp.getNeed() * 2;
        }
    }

    while (true) {
        //Coal Turn
        while (true) {
            int coalNum = players[i].getCoalNum();
            int oilNum = players[i].getOilNum();
            int inputNum;
            std::cout << std::endl;
            std::cout << "[PROMPT] How many coal do you want to buy? (Enter 0 to skip) " << std::endl;
            std::cout << "[ENTER] ";
            std::cin >> inputNum;
            std::cout << std::endl;
            if (inputNum == 0) {
                break;
            }
            //Check if Player's inventory is full
            if (inputNum > coalMax + hybridMax - coalNum + ((oilMax - oilNum) < 0 ? (oilMax - oilNum) : 0)) {
                std::cout << "[ERROR] You do not have enough space! Please enter a smaller numeber." << std::endl;
                continue;
            }

            //Check if Player's Money and Market's inventory is enough

            //two temp variable
            int cost = 0;
            int tempAmount = 0;

            for (int i = 0; i < 12; i++) {
                int left = resources[i].getCoal();                    //left is the resources left in the marketS
                if (left == 0) {
                    continue;
                }
                if (left >= inputNum - tempAmount) {
                    cost += resources[i].getPrice() * (inputNum - tempAmount);
                    tempAmount = inputNum;
                    break;
                } else if (left < inputNum - tempAmount) {
                    cost += resources[i].getPrice() * left;
                    tempAmount += left;
                }
            }

            if (tempAmount < inputNum) {
                std::cout << "[ERROR] Coal is out of stock. Please enter a smaller number!" << std::endl;
                continue;
            }
            if (cost > players[i].getMoney()) {
                std::cout << "[ERROR] You do not have enough money. Please enter a smaller number!" << std::endl;
                continue;
            }

            //pay money
            players[i].setMoney(players[i].getMoney() - cost);

            tempAmount = 0;
            for (int i = 0; i < 12; i++) {

                int left = resources[i].getCoal();

                if (left == 0) {
                    continue;
                }
                if (left >= inputNum - tempAmount) {
                    resources[i].setCoal(left - (inputNum - tempAmount));
                    break;
                } else if (left < inputNum - tempAmount) {
                    tempAmount += left;
                    resources[i].setCoal(0);
                }
            }
            //get resources
            players[i].setCoalNum(coalNum + inputNum);

            std::cout << "[SUCCESS] " << inputNum << " coal cost " << cost << " Elektro. You have "
                      << players[i].getMoney() << " Elektro now." << std::endl;

            break;
        }

        //Oil Turn
        while (true) {
            int coalNum = players[i].getCoalNum();
            int oilNum = players[i].getOilNum();
            int inputNum;
            std::cout << std::endl;
            std::cout << "[PROMPT] How many oil do you want to buy? (Enter 0 to skip)" << std::endl;
            std::cout << "[ENTER] ";
            std::cin >> inputNum;
            std::cout << std::endl;
            if (inputNum == 0) {
                break;
            }
            //Check if Player's inventory is vaild

            if (inputNum > oilMax + hybridMax - oilNum + ((coalMax - coalNum) < 0 ? (coalMax - coalNum) : 0)) {
                std::cout << "[ERROR] You do not have enough space! Please enter a smaller numeber.";
                continue;
            }


            //Check if Player's Money and Market's inventory is enough

            //two temp variable
            int cost = 0;
            int tempAmount = 0;

            for (int i = 0; i < 12; i++) {
                int left = resources[i].getOil();
                if (left == 0) {
                    continue;
                }
                if (left >= inputNum - tempAmount) {
                    cost += resources[i].getPrice() * (inputNum - tempAmount);
                    tempAmount = inputNum;
                    break;
                } else if (left < inputNum - tempAmount) {
                    cost += resources[i].getPrice() * left;
                    tempAmount += left;
                }
            }

            if (tempAmount < inputNum) {
                std::cout << "[ERROR] Oil is out of stock. Please enter a smaller number!" << std::endl;
                continue;
            }
            if (cost > players[i].getMoney()) {
                std::cout << "[ERROR] You do not have enough money. Please enter a smaller number!" << std::endl;
                continue;
            }

            //pay money
            players[i].setMoney(players[i].getMoney() - cost);

            tempAmount = 0;
            for (int i = 0; i < 12; i++) {

                int left = resources[i].getOil();

                if (left == 0) {
                    continue;
                }
                if (left >= inputNum - tempAmount) {
                    resources[i].setOil(left - (inputNum - tempAmount));
                    break;
                } else if (left < inputNum - tempAmount) {
                    tempAmount += left;
                    resources[i].setOil(0);
                }
            }
            //get resources
            players[i].setOilNum(oilNum + inputNum);

            std::cout << "[SUCCESS]" << inputNum << " oil cost " << cost << " Elektro. You have "
                      << players[i].getMoney() << " Elektro now." << std::endl;
            break;
        }

        //Garbage Turn
        while (true) {
            int garbageNum = players[i].getGarbageNum();
            int inputNum;
            std::cout << std::endl;
            std::cout << "[PROMPT] How many garbage do you want to buy? (Enter 0 to skip)" << std::endl;
            std::cout << "[ENTER] ";
            std::cin >> inputNum;
            std::cout << std::endl;
            if (inputNum == 0) {
                break;
            }
            //Check if Player's inventory is vaild

            if (inputNum > garbageMax - garbageNum) {
                std::cout << "[ERROR] You do not have enough space! Please enter a smaller numeber.";
                continue;
            }


            //Check if Player's Money and Market's inventory is enough

            //two temp variable
            int cost = 0;
            int tempAmount = 0;

            for (int i = 0; i < 12; i++) {
                int left = resources[i].getGarbage();
                if (left == 0) {
                    continue;
                }
                if (left >= inputNum - tempAmount) {
                    cost += resources[i].getPrice() * (inputNum - tempAmount);
                    tempAmount = inputNum;
                    break;
                } else if (left < inputNum - tempAmount) {
                    cost += resources[i].getPrice() * left;
                    tempAmount += left;
                }
            }

            if (tempAmount < inputNum) {
                std::cout << "[ERROR] Garbage is out of stock. Please enter a smaller number!" << std::endl;
                continue;
            }
            if (cost > players[i].getMoney()) {
                std::cout << "[ERROR] You do not have enough money. Please enter a smaller number!" << std::endl;
                continue;
            }

            //pay money
            players[i].setMoney(players[i].getMoney() - cost);

            tempAmount = 0;
            for (int i = 0; i < 12; i++) {

                int left = resources[i].getGarbage();

                if (left == 0) {
                    continue;
                }
                if (left >= inputNum - tempAmount) {
                    resources[i].setGarbage(left - (inputNum - tempAmount));
                    break;
                } else if (left < inputNum - tempAmount) {
                    tempAmount += left;
                    resources[i].setGarbage(0);
                }
            }

            //get resources
            players[i].setGarbageNum(garbageNum + inputNum);

            std::cout << "[SUCCESS]" << inputNum << " garbage cost " << cost << " Elektro. You have "
                      << players[i].getMoney() << " Elektro now." << std::endl;
            break;
        }

        //Uranium Turn
        while (true) {
            int uraniumNum = players[i].getUraniumNum();
            int inputNum;
            std::cout << std::endl;
            std::cout << "[PROMPT] How many uranium do you want to buy? (Enter 0 to skip)" << std::endl;
            std::cout << "[ENTER] ";
            std::cin >> inputNum;
            std::cout << std::endl;
            if (inputNum == 0) {
                break;
            }
            //Check if Player's inventory is vaild

            if (inputNum > uraniumMax - uraniumNum) {
                std::cout << "[ERROR] You do not have enough space! Please enter a smaller numeber.";
                continue;
            }


            //Check if Player's Money and Market's inventory is enough

            //two temp variable
            int cost = 0;
            int tempAmount = 0;

            for (int i = 0; i < 12; i++) {
                int left = resources[i].getUranium();
                if (left == 0) {
                    continue;
                }
                if (left >= inputNum - tempAmount) {
                    cost += resources[i].getPrice() * (inputNum - tempAmount);
                    tempAmount = inputNum;
                    break;
                } else if (left < inputNum - tempAmount) {
                    cost += resources[i].getPrice() * left;
                    tempAmount += left;
                }
            }

            if (tempAmount < inputNum) {
                std::cout << "[ERROR] Uranium is out of stock. Please enter a smaller number!" << std::endl;
                continue;
            }
            if (cost > players[i].getMoney()) {
                std::cout << "[ERROR] You do not have enough money. Please enter a smaller number!" << std::endl;
                continue;
            }

            //pay money
            players[i].setMoney(players[i].getMoney() - cost);
            tempAmount = 0;
            for (int i = 0; i < 12; i++) {

                int left = resources[i].getUranium();

                if (left == 0) {
                    continue;
                }
                if (left >= inputNum - tempAmount) {
                    resources[i].setUranium(left - (inputNum - tempAmount));
                    break;
                } else if (left < inputNum - tempAmount) {
                    tempAmount += left;
                    resources[i].setUranium(0);
                }
            }
            //get resources

            players[i].setUraniumNum(uraniumNum + inputNum);

            std::cout << "[SUCCESS]" << inputNum << " uranium cost " << cost << " Elektro. You have "
                      << players[i].getMoney() << " Elektro now." << std::endl;
            break;
        }
        break;
    }
}
bool Game::adjustMarket(int &step) {
    bool goToStep3 = false;
    std::cout << "[INFO] It is STEP 2 now!!" << std::endl;
    std::cout << "[INFO] Remove first card in the market!" << std::endl;
    market.erase(market.begin());						//remove first card in market
    std::cout << "[INFO] Add a new card to the market!" << std::endl;
    if (powerPlants[0].getType() == PowerPlant::step3) {
        std::cout << "[INFO] Find STEP 3 Card. Shuffle the deck." << std::endl;
        std::cout << "[INFO] STEP 3 starts in phase 5!!" << std::endl;
        powerPlants.erase(powerPlants.begin());
        PowerPlant::shuffle(powerPlants);
        bool goToStep3 = true;
    }
    else {
        market.push_back(powerPlants[0]);
        powerPlants.erase(powerPlants.begin());
    }

    std::cout << "[INFO] Reorder the cards in the market!" << std::endl;
    PowerPlant::setMarketOrder(market);					//reorder
    return goToStep3;
}





//phase 5 methods
//every player earns cash based on the number of cities he powers as shown on the payment table
void Game::earnCash(Resources recycle) {
    int payment[21] = {10, 22, 33, 44, 54, 64, 73, 82, 90, 98, 105, 112, 118, 124, 129, 134, 138, 142, 145, 148,
                       150};     //payment corresponding to the number of powered cities
    string yesInput;
    int earnedCash, money;
    for (int i = 0; i < numOfPlayer; i++) {
        int numOfPowerPlant = players[i].getNumOfPowerPlant();
        int totalNumInput = 0;
        for (int j = 0; j < numOfPowerPlant; j++) {
            PowerPlant currentPlant = players[i].getPowerPlant(j);
            cout << "[PROMPT] Player " << (i + 1)
                 << ": Do you wish to supply cities with electricity by using power plant "
                 << currentPlant.getNumber() << " ?" << endl;
            do {
                cin >> yesInput;
                if (yesInput == "Y" || yesInput == "y") {
                    if (validUsingPowerPlant(i, currentPlant, recycle)) {
                        totalNumInput += currentPlant.getSupplyCity();
                        break;
                    }
                } else
                    break;
            } while (true);

            if (totalNumInput > players[i].getNumOfCity())
                totalNumInput = players[i].getNumOfCity();
        }

        players[i].addNumOfPoweredCities(totalNumInput);

        earnedCash = payment[totalNumInput];
        money = players[i].getMoney() + earnedCash;
        players[i].setMoney(money);
        cout << "[SUCCESS] You have supplied " << totalNumInput << " city/cities this round." << endl;
        cout << "[INFO] You have earned " << earnedCash << " this round." << endl;
        cout << "[INFO] Now you have " << players[i].getNumOfPoweredCities() << " city/cities that have been powered.\n"
             << endl;
    }
}

//return true if the input is valid for the number of cities the player wants to power
bool Game::validUsingPowerPlant(int i, PowerPlant currentPlant, Resources recycle) {
    PowerPlant::Type type = currentPlant.getType();
    int needNum = currentPlant.getNeed();
    if (type == PowerPlant::hybrid) {
        int numCoalHybrid, numOilHybrid;
        do {
            do {
                cout << "\n[PROMPT] Please enter the coal that you want to use to power the power plant:" << endl;
                cout << "-> ";
                if (!cin) {
                    cout << "[ERROR] Invalid input";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (!(cin >> numCoalHybrid));

            do {
                cout << "\n[PROMPT] Please enter the oil that you want to use to power the power plant:" << endl;
                cout << "-> ";
                if (!cin) {
                    cout << "[ERROR] Invalid input";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (!(cin >> numOilHybrid));
        } while (numCoalHybrid + numOilHybrid != currentPlant.getNeed());
        recycle.addCoal(numCoalHybrid);
        players[i].deCoalNum(numCoalHybrid);
        recycle.addOil(numOilHybrid);
        players[i].deOilNum(numOilHybrid);
    }
    switch (type) {
        case PowerPlant::coal:
            if (players[i].getCoalNum() >= needNum) {
                recycle.addCoal(needNum);
                players[i].deCoalNum(needNum);
                return true;
            } else
                cout << "[ERROR] You can not power cities by using power plant " << currentPlant.getNumber() <<
                     " because you do not have enough coals." << endl;
            return false;
        case PowerPlant::oil:
            if (players[i].getOilNum() >= currentPlant.getNeed()) {
                recycle.addOil(needNum);
                players[i].deOilNum(needNum);
                return true;
            } else
                cout << "[ERROR] You can not power cities by using power plant " << currentPlant.getNumber() <<
                     " because you do not have enough oil." << endl;
            return false;
        case PowerPlant::garbage:
            if (players[i].getGarbageNum() >= currentPlant.getNeed()) {
                recycle.addGarbage(needNum);
                players[i].deGarbageNum(needNum);
                return true;
            } else
                cout << "[ERROR] You can not power cities by using power plant " << currentPlant.getNumber() <<
                     " because you do not have enough garbage." << endl;
            return false;
        case PowerPlant::uranium:
            if (players[i].getUraniumNum() >= currentPlant.getNeed()) {
                recycle.addUranium(needNum);
                players[i].deUraniumNum(needNum);
                return true;
            } else
                cout << "[ERROR] You can not power cities by using power plant " << currentPlant.getNumber() <<
                     " because you do not have enough uranium." << endl;
            return false;
        default:
            return true;
    }
}

//Based on the number of players and the step of the game, the players re-supply the resource market from the supply of resources.
void Game::reSupplyResource(Resources recycle) {

    //Based on the number of players and the step of the game, the players re-supply the resource market (see table at the back of the rules) from the supply of resources
    Resources table;
    switch (numOfPlayer) {
        case 2:
            switch (step) {
                case 1:
                    table = Resources(3, 2, 1, 1, 0);
                    break;
                case 2:
                    table = Resources(4, 2, 2, 1, 0);
                    break;
                case 3:
                    table = Resources(3, 4, 3, 1, 0);
                    break;
            }
            break;
        case 3:
            switch (step) {
                case 1:
                    table = Resources(4, 2, 1, 1, 0);
                    break;
                case 2:
                    table = Resources(5, 3, 2, 1, 0);
                    break;
                case 3:
                    table = Resources(3, 4, 3, 1, 0);
                    break;
            }
            break;
        case 4:
            switch (step) {
                case 1:
                    table = Resources(5, 3, 2, 1, 0);
                    break;
                case 2:
                    table = Resources(6, 4, 3, 2, 0);
                    break;
                case 3:
                    table = Resources(4, 5, 4, 2, 0);
                    break;
            }
            break;
        case 5:
            switch (step) {
                case 1:
                    table = Resources(5, 4, 3, 2, 0);
                    break;
                case 2:
                    table = Resources(7, 5, 3, 3, 0);
                    break;
                case 3:
                    table = Resources(5, 6, 5, 2, 0);
                    break;
            }
            break;
        case 6:
            switch (step) {
                case 1:
                    table = Resources(7, 5, 3, 2, 0);
                    break;
                case 2:
                    table = Resources(9, 6, 5, 3, 0);
                    break;
                case 3:
                    table = Resources(6, 7, 6, 3, 0);
                    break;
            }
            break;
    }


    //change the number of resources that will be supplied according to the available in the game
    // (if the players store too many resources in their power plants, the resource is not fully re-supplied! The resource tokens in the game are limited.)
    Resources toSupply;
    if (recycle.getCoal() >= table.getCoal()) {
        recycle.setCoal(recycle.getCoal() - table.getCoal());
        toSupply.setCoal(table.getCoal());
    } else {
        toSupply.setCoal(recycle.getCoal());
        recycle.setCoal(0);
    }

    if (recycle.getOil() >= table.getOil()) {
        recycle.setOil(recycle.getOil() - table.getOil());
        toSupply.setOil(table.getOil());
    } else {
        toSupply.setOil(recycle.getOil());
        recycle.setOil(0);
    }

    if (recycle.getGarbage() >= table.getGarbage()) {
        recycle.setGarbage(recycle.getGarbage() - table.getGarbage());
        toSupply.setGarbage(table.getGarbage());
    } else {
        toSupply.setGarbage(recycle.getGarbage());
        recycle.setGarbage(0);
    }

    if (recycle.getUranium() >= table.getUranium()) {
        recycle.setUranium(recycle.getUranium() - table.getUranium());
        toSupply.setUranium(table.getUranium());
    } else {
        toSupply.setUranium(recycle.getUranium());
        recycle.setUranium(0);
    }

    //print the resources that will be supplied to the market
    int numOfCoalToSupply = toSupply.getCoal();
    int numOfOilToSupply = toSupply.getOil();
    int numOfGarbageToSupply = toSupply.getGarbage();
    int numOfUraniumToSupply = toSupply.getUranium();
    cout << "[INFO] To be re-supplied in step " << step << " for coal: " << numOfCoalToSupply << endl;
    cout << "[INFO] To be re-supplied in step " << step << " for oil: " << numOfOilToSupply << endl;
    cout << "[INFO] To be re-supplied in step " << step << " for garbage: " << numOfGarbageToSupply << endl;
    cout << "[INFO] To be re-supplied in step " << step << " for uranium: " << numOfUraniumToSupply << endl;

    //re-supply the uranium
    for (int i = 11; i >= 0; i--) {
        if (numOfUraniumToSupply > 0) {
            if (resources[i].getUranium() == 1)
                continue;
            else {
                if (resources[i].getUranium() == 0) {
                    resources[i].setUranium(1);
                    numOfUraniumToSupply--;
                }
            }
        }
    }


    for (int i = 7; i >= 0; i--) {
        //re-supply the coal
        if (numOfCoalToSupply > 0) {
            switch (resources[i].getCoal()) {
                case 3:
                    break;
                case 2: {
                    numOfCoalToSupply--;
                    resources[i].setCoal(3);
                    break;
                }
                case 1: {
                    int spaceCoalTemp = numOfCoalToSupply - 2;
                    if (spaceCoalTemp >= 0) {
                        resources[i].setCoal(3);
                        numOfCoalToSupply -= 2;
                    } else {
                        resources[i].setCoal(2);
                        numOfCoalToSupply--;
                    }
                    break;
                }
                case 0: {
                    int spaceCoalTemp = numOfCoalToSupply - 3;
                    if (spaceCoalTemp >= 0) {
                        resources[i].setCoal(3);
                        numOfCoalToSupply -= 3;
                    } else {
                        resources[i].setCoal(numOfCoalToSupply);
                        numOfCoalToSupply = 0;
                    }
                    break;
                }
            }
        }

        //re-supply the oil
        if (numOfOilToSupply > 0) {
            switch (resources[i].getOil()) {
                case 3:
                    break;
                case 2: {
                    numOfOilToSupply--;
                    resources[i].setOil(3);
                    break;
                }
                case 1: {
                    int spaceOilTemp = numOfOilToSupply - 2;
                    if (spaceOilTemp >= 0) {
                        resources[i].setOil(3);
                        numOfOilToSupply -= 2;
                    } else {
                        resources[i].setOil(2);
                        numOfOilToSupply--;
                    }
                    break;
                }
                case 0: {
                    int spaceOilTemp = numOfOilToSupply - 3;
                    if (spaceOilTemp >= 0) {
                        resources[i].setOil(3);
                        numOfOilToSupply -= 3;
                    } else {
                        resources[i].setOil(numOfOilToSupply);
                        numOfOilToSupply = 0;
                    }
                    break;
                }
            }
        }

        //re-supply the garbage
        if (numOfGarbageToSupply > 0) {
            switch (resources[i].getGarbage()) {
                case 3:
                    break;
                case 2: {
                    numOfGarbageToSupply--;
                    resources[i].setGarbage(3);
                    break;
                }
                case 1: {
                    int spaceGarbageTemp = numOfGarbageToSupply - 2;
                    if (spaceGarbageTemp >= 0) {
                        resources[i].setGarbage(3);
                        numOfGarbageToSupply -= 2;
                    } else {
                        resources[i].setGarbage(2);
                        numOfGarbageToSupply--;
                    }
                    break;
                }
                case 0: {
                    int spaceGarbageTemp = numOfGarbageToSupply - 3;
                    if (spaceGarbageTemp >= 0) {
                        resources[i].setGarbage(3);
                        numOfGarbageToSupply -= 3;
                    } else {
                        resources[i].setGarbage(numOfGarbageToSupply);
                        numOfGarbageToSupply = 0;
                    }
                    break;
                }
            }
        }


    }
}

//Place the highest numbered power plant from the future market face down under the draw stack and draw a new one to replace it
void Game::updateMarket() {
    //If the »Step 3« card is drawn in phase 5 (Bureaucracy),
    //remove this card and the lowest numbered power plant from the game and do not draw replacements
    PowerPlant theFirstInDrawStack = powerPlants.front();
    if (theFirstInDrawStack.getTypeName() == "step3") {
        cout << "[INFO] It is STEP 3 Card !!" << endl;
        market.erase(market.begin());
        PowerPlant::setMarketOrder(market);
        powerPlants.erase(powerPlants.begin());
        step = 3;
        PowerPlant::shuffle(powerPlants);
    } else {
        PowerPlant theHighest = market.back();
        market.pop_back();
        market.push_back(powerPlants.front());
        powerPlants.push_back(theHighest);
        powerPlants.erase(powerPlants.begin());
    }
}

