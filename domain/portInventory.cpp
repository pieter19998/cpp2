#include "portInventory.h"

portInventory::portInventory() {

}

const std::vector<std::unique_ptr<Wares>> &portInventory::GetWares() const {
    return wares_;
}
