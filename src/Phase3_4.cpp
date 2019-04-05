#include "Phase3_4.h"


int coalMax = 0;
int oilMax = 0;
int garbageMax = 0;
int uraniumMax = 0;
int hybridMax = 0;


void buyResources(int i, Player* players, Resources* resources){
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

    while (true)
    {
        //Coal Turn
        while (true)
        {
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
                int left = resources[i].getCoal();					//left is the resources left in the marketS
                if (left == 0) {
                    continue;
                }
                if (left >= inputNum - tempAmount) {
                    cost += resources[i].getPrice() * (inputNum - tempAmount);
                    tempAmount = inputNum;
                    break;
                }
                else if (left < inputNum - tempAmount) {
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
            players[i].setMoney(players[i].getMoney()-cost);

            tempAmount = 0;
            for (int i = 0; i < 12; i++) {

                int left = resources[i].getCoal();

                if (left == 0) {
                    continue;
                }
                if (left >= inputNum - tempAmount) {
                    resources[i].setCoal(left - (inputNum - tempAmount));
                    break;
                }
                else if (left < inputNum - tempAmount) {
                    tempAmount += left;
                    resources[i].setCoal(0);
                }
            }
            //get resources
            players[i].setCoalNum(coalNum + inputNum);

            std::cout << "[SUCCESS] " << inputNum << " coal cost " << cost << " Elektro. You have " << players[i].getMoney() << " Elektro now." << std::endl;

            break;
        }

        //Oil Turn
        while (true)
        {
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
                }
                else if (left < inputNum - tempAmount) {
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
                }
                else if (left < inputNum - tempAmount) {
                    tempAmount += left;
                    resources[i].setOil(0);
                }
            }
            //get resources
            players[i].setOilNum(oilNum + inputNum);

            std::cout << "[SUCCESS]" << inputNum << " oil cost " << cost << " Elektro. You have " << players[i].getMoney() << " Elektro now." << std::endl;
            break;
        }

        //Garbage Turn
        while (true)
        {
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
                }
                else if (left < inputNum - tempAmount) {
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
            players[i].setMoney(players[i].getMoney()-cost);

            tempAmount = 0;
            for (int i = 0; i < 12; i++) {

                int left = resources[i].getGarbage();

                if (left == 0) {
                    continue;
                }
                if (left >= inputNum - tempAmount) {
                    resources[i].setGarbage(left - (inputNum - tempAmount));
                    break;
                }
                else if (left < inputNum - tempAmount) {
                    tempAmount += left;
                    resources[i].setGarbage(0);
                }
            }

            //get resources
            players[i].setGarbageNum(garbageNum + inputNum);

            std::cout << "[SUCCESS]" << inputNum << " garbage cost " << cost << " Elektro. You have " << players[i].getMoney() << " Elektro now." << std::endl;
            break;
        }

        //Uranium Turn
        while (true)
        {
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

            if (inputNum > uraniumMax- uraniumNum) {
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
                }
                else if (left < inputNum - tempAmount) {
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
                }
                else if (left < inputNum - tempAmount) {
                    tempAmount += left;
                    resources[i].setUranium(0);
                }
            }
            //get resources

            players[i].setUraniumNum(uraniumNum + inputNum);

            std::cout << "[SUCCESS]" << inputNum << " uranium cost " << cost << " Elektro. You have " << players[i].getMoney() << " Elektro now." << std::endl;
            break;
        }
        break;
    }
}




void building(int step, int numOfPlayer, Player* players, int i, Graph* graph, vector<PowerPlant> &powerPlants, vector<PowerPlant> &market){


    std::cout << "[INFO]" << players[i].getName() << ", it's your turn!" << std::endl;
    while (true) {
        //check the step
        if (numOfPlayer == 2) {
            if (players[i].getNumOfCity() == 10) {
                if (step == 1) {
                    step = 2;
                    goToStep3 = adjustMarket(step, market, powerPlants);
                }
            }
        }
        if (numOfPlayer == 3 || numOfPlayer == 4 || numOfPlayer == 5) {
            if (players[i].getNumOfCity() == 7) {
                if (step == 1) {
                    step = 2;
                    goToStep3 = adjustMarket(step, market, powerPlants);
                }
            }
        }
        if (numOfPlayer == 6) {
            if (players[i].getNumOfCity() == 6) {
                if (step == 1) {
                    step = 2;
                    goToStep3 = adjustMarket(step, market, powerPlants);
                }
            }
        }

        std::cout << "[PROMPT]" << "Please enter the ID of the city that you want to build.(Enter -1 to skip)" << std::endl;
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
        if (size >= (size_t)step) {
            std::cout << "[ERROR] You can not build plant in this city because there is no more space!" << std::endl;
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
        std::cout << "[SUCCESS] You have built a house in " << graph->getArr()[inputNum].getBase()->getName() << " successfully." << std::endl;
        std::cout << "[SUCCESS] It cost you  " << price << " Elektro. Now you have " << players[i].getMoney() << " Elektro." << std::endl;

    }
}