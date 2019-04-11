

#include "ResourceMarket.h"


ResourceMarket::ResourceMarket(){
    resourcesMarket = new Resources[12];
    resourcesMarket[0] = Resources(3, 0, 0, 0, 1);
    resourcesMarket[1] = Resources(3, 0, 0, 0, 2);
    resourcesMarket[2] = Resources(3, 3, 0, 0, 3);
    resourcesMarket[3] = Resources(3, 3, 0, 0, 4);
    resourcesMarket[4] = Resources(3, 3, 0, 0, 5);
    resourcesMarket[5] = Resources(3, 3, 0, 0, 6);
    resourcesMarket[6] = Resources(3, 3, 3, 0, 7);
    resourcesMarket[7] = Resources(3, 3, 3, 0, 8);
    resourcesMarket[8] = Resources(0, 0, 0, 0, 10);
    resourcesMarket[9] = Resources(0, 0, 0, 0, 12);
    resourcesMarket[10] = Resources(0, 0, 0, 1, 14);
    resourcesMarket[11] = Resources(0, 0, 0, 1, 16);
};

ResourceMarket::~ResourceMarket() {
    delete resourcesMarket;
    //delete s_instance;
}

ResourceMarket*  ResourceMarket:: instance(){
    if(!s_instance)
        s_instance = new ResourceMarket();
    return s_instance;
}


ResourceMarket * ResourceMarket::s_instance = 0;