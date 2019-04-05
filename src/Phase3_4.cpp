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
