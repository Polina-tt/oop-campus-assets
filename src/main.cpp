#include "equipment_item.hpp" 
#include <iostream> 
#include <cassert> 
#include <stdexcept> 
int main() { std::cout << "Running checks...\n"; EquipmentItem item(1, "Laptop", "Tech"); assert(item.getId() == 1); try { EquipmentItem bad(0, "X", "Y"); assert(false); } catch(...) {} try { EquipmentItem bad(2, "", "Y"); assert(false); } catch(...) {} item.rentOut(); assert(item.getState() == EquipmentState::InUse); try { item.rentOut(); assert(false); } catch(...) {} item.returnBack(); assert(item.isAvailable()); try { item.returnBack(); assert(false); } catch(...) {} item.sendToMaintenance(); assert(item.getState() == EquipmentState::UnderMaintenance); try { item.rentOut(); assert(false); } catch(...) {} item.finishMaintenance(); assert(item.isAvailable()); std::cout << "All 10 scenarios passed!\n"; return 0; }
