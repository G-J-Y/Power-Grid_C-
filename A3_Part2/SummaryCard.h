//
// Created by Tyler on 2019-02-28.
//

#ifndef PROJECT345_SUMMARYCARD_H
#define PROJECT345_SUMMARYCARD_H

#include <iostream>
#include <string>

class SummaryCard {

private:
    std::string m_info = "Turn\n"
                       "1. DETERMINE TURN ORDER\n"
                       "2. BUY POWER PLANT\n"
                       "\tThe best bbegins.\n"
                       "\tPer round, each may bug only one power plant.\n"
                       "3. BUY RAW MATERIALS\n"
                       "\tThe worst begins.\n"
                       "\tMaximum double input per power plant.\n"
                       "4. BUILDING\n"
                       "\tThe last player begins.\n"
                       "5. BUREAUCRACY\n"
                       "    Get money\n"
                       "    In phase 1 and 2: Place highest power plant under the stack.\n"
                       "    In phase 3: Remove lowest power plant from the game.\n"
                       "    Restock raw materials.";

public:

    SummaryCard();

    void printInfo();
};


#endif //PROJECT345_SUMMARYCARD_H
