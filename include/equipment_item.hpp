#pragma once 
#include <string> 
enum class EquipmentState { Available, InUse, UnderMaintenance }; 
class EquipmentItem { private: int m_id; std::string m_name; std::string m_category; EquipmentState m_state; public: EquipmentItem(int id, std::string name, std::string category); [[nodiscard]] int getId() const noexcept; [[nodiscard]] std::string getName() const; [[nodiscard]] std::string getCategory() const; [[nodiscard]] EquipmentState getState() const noexcept; [[nodiscard]] bool isAvailable() const noexcept; void rentOut(); void returnBack(); void sendToMaintenance(); void finishMaintenance(); };
