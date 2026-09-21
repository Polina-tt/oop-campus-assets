#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include "IssueRecord.hpp"

class IssueRegistry {
private:
    uint32_t next_record_id_{1};
    std::vector<IssueRecord> records_; 

public:
    IssueRegistry() = default;

    void createIssue(User& user, EquipmentItem& equipment) {
        if (equipment.isIssued()) {
            throw std::runtime_error("Помилка: Обладнання '" + equipment.getName() + "' вже видано!");
        }
        if (!user.canIssueMore()) {
            throw std::runtime_error("Помилка: Користувач " + user.getName() + " перевищив свій ліміт видач!");
        }

        equipment.setIssued(true);
        try {
            user.incrementIssues();
        } catch (...) {
            equipment.setIssued(false);
            throw;
        }

        records_.emplace_back(next_record_id_++, user, equipment);
    }

    void returnEquipment(EquipmentItem& equipment) {
        auto it = std::find_if(records_.begin(), records_.end(), [&](const IssueRecord& rec) {
            return rec.isActive() && rec.getEquipment().getId() == equipment.getId();
        });

        if (it == records_.end()) {
            throw std::runtime_error("Помилка: Активної видачі для обладнання '" + equipment.getName() + "' не знайдено!");
        }

        it->closeRecord();
    }

    [[nodiscard]] std::vector<IssueRecord> getActiveIssuesForUser(uint32_t user_id) const {
        std::vector<IssueRecord> user_active_records;
        for (const auto& rec : records_) {
            if (rec.isActive() && rec.getUser().getId() == user_id) {
                user_active_records.push_back(rec);
            }
        }
        return user_active_records;
    }
};