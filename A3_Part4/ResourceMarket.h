
#ifndef PROJECT_RESOURCEMARKET_H
#define PROJECT_RESOURCEMARKET_H

#include "Resources.h"

class ResourceMarket {

private:
    Resources * resourcesMarket;
    static ResourceMarket *s_instance;
    ResourceMarket();
    ~ResourceMarket();

public:

    static ResourceMarket *instance();
    Resources* getResourcesMarket(){return resourcesMarket;};
};


#endif //PROJECT_RESOURCEMARKET_H
