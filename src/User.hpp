#pragma once
#include <string>
#include <stdexcept>

class User {
private:
    uint32_t id_;
    std::string name_;
    uint32_t max_active_issues_;
    uint32_t current_active_issues_{0};

public:
    User() = delete;
    User(uint32_t id, std::string name, uint32_t max_issues)
        : id_(id), name_(std::move(name)), max_active_issues_(max_issues) {
        if (id_ == 0) throw std::invalid_argument("ID користувача має бути позитивним!");
        if (name_.empty()) throw std::invalid_argument("Ім'я користувача не може бути порожнім!");
        if (max_issues == 0) throw std::invalid_argument("Максимальна кількість видач має бути > 0!");
    }

    [[nodiscard]] uint32_t getId() const { return id_; }
    [[nodiscard]] const std::string& getName() const { return name_; }
    [[nodiscard]] bool canIssueMore() const { return current_active_issues_ < max_active_issues_; }
    [[nodiscard]] uint32_t getActiveIssuesCount() const { return current_active_issues_; }

    void incrementIssues() {
        if (!canIssueMore()) throw std::runtime_error("Перевищено ліміт активних видач користувача!");
        current_active_issues_++;
    }

    void decrementIssues() {
        if (current_active_issues_ == 0) throw std::runtime_error("У користувача немає активних видач!");
        current_active_issues_--;
    }
};