#pragma once
#include <string>
#include <stdexcept>
#include <cstdint>

class EquipmentItem {
private:
    uint32_t id_;
    std::string name_;
    bool is_issued_{false};

public:
    EquipmentItem() = delete;
    explicit EquipmentItem(uint32_t id, std::string name)
        : id_(id), name_(std::move(name)) {
        if (id_ == 0) throw std::invalid_argument("ID обладнання має бути позитивним!");
        if (name_.empty()) throw std::invalid_argument("Назва обладнання не може бути порожньою!");
    }

    [[nodiscard]] uint32_t getId() const { return id_; }
    [[nodiscard]] const std::string& getName() const { return name_; }
    [[nodiscard]] bool isIssued() const { return is_issued_; }

    void setIssued(bool status) { is_issued_ = status; }
};