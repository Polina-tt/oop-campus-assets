#pragma once
#include "User.hpp"
#include "EquipmentItem.hpp"

class IssueRecord {
private:
    uint32_t record_id_;
    User& user_;               
    EquipmentItem& equipment_; 
    bool is_active_{true};

public:
    IssueRecord() = delete;
    IssueRecord(uint32_t record_id, User& user, EquipmentItem& equipment)
        : record_id_(record_id), user_(user), equipment_(equipment) {
        if (record_id_ == 0) throw std::invalid_argument("ID запису має бути позитивним!");
    }

    [[nodiscard]] uint32_t getRecordId() const { return record_id_; }
    [[nodiscard]] const User& getUser() const { return user_; }
    [[nodiscard]] const EquipmentItem& getEquipment() const { return equipment_; }
    [[nodiscard]] bool isActive() const { return is_active_; }

    void closeRecord() {
        if (!is_active_) throw std::runtime_error("Запис про видачу вже закритий! Повторне закриття заборонене.");
        is_active_ = false;
        user_.decrementIssues();
        equipment_.setIssued(false);
    }
};