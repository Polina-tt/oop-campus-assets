#include "equipment_item.hpp" 
#include <stdexcept> 
EquipmentItem::EquipmentItem(int id, std::string name, std::string category) : m_id(id), m_name(std::move(name)), m_category(std::move(category)), m_state(EquipmentState::Available) { if (m_id <= 0) throw std::invalid_argument("ID must be ^> 0"); if (m_name.empty()) throw std::invalid_argument("Name empty"); if (m_category.empty()) throw std::invalid_argument("Category empty"); } 
int EquipmentItem::getId() const noexcept { return m_id; } 
std::string EquipmentItem::getName() const { return m_name; } 
std::string EquipmentItem::getCategory() const { return m_category; } 
EquipmentState EquipmentItem::getState() const noexcept { return m_state; } 
bool EquipmentItem::isAvailable() const noexcept { return m_state == EquipmentState::Available; } 
void EquipmentItem::rentOut() { if (m_state != EquipmentState::Available) throw std::logic_error("Not available"); m_state = EquipmentState::InUse; } 
void EquipmentItem::returnBack() { if (m_state != EquipmentState::InUse) throw std::logic_error("Not rented"); m_state = EquipmentState::Available; } 
void EquipmentItem::sendToMaintenance() { if (m_state != EquipmentState::Available) throw std::logic_error("Not available"); m_state = EquipmentState::UnderMaintenance; } 
void EquipmentItem::finishMaintenance() { if (m_state != EquipmentState::UnderMaintenance) throw std::logic_error("Not in maintenance"); m_state = EquipmentState::Available; }
