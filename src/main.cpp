// Lab 1 Code  
#include <iostream>
#include <cassert>
#include "EquipmentItem.hpp"
#include "User.hpp"
#include "IssueRegistry.hpp"

int main() {
    std::cout << "[INFO] Запуск обов'язкових сценаріїв варіанта 1...\n";

    EquipmentItem laptop(101, "ThinkPad");
    EquipmentItem phone(102, "iPhone");
    User student1(1, "Олексій", 1); 
    User student2(2, "Марія", 2);   
    IssueRegistry registry;

    // 1. Успішна видача
    registry.createIssue(student1, laptop);
    assert(laptop.isIssued() == true);
    assert(student1.getActiveIssuesCount() == 1);

    // 2. Повторна видача того самого обладнання (Помилка)
    try {
        registry.createIssue(student2, laptop);
        assert(false); 
    } catch (const std::runtime_error&) {
        std::cout << "[OK] Сценарій 2 (повторна видача) захищений.\n";
    }

    // 3. Перевищення ліміту користувача (Помилка)
    try {
        registry.createIssue(student1, phone);
        assert(false);
    } catch (const std::runtime_error&) {
        std::cout << "[OK] Сценарій 3 (перевищення ліміту) захищений.\n";
    }

    // 4. Пошук активних видач конкретного користувача
    auto active_alex = registry.getActiveIssuesForUser(student1.getId());
    assert(active_alex.size() == 1);

    // 5. Повернення обладнання
    registry.returnEquipment(laptop);
    assert(laptop.isIssued() == false);
    assert(student1.getActiveIssuesCount() == 0);

    // 6. Повторне повернення
    try {
        registry.returnEquipment(laptop);
        assert(false);
    } catch (const std::runtime_error&) {
        std::cout << "[OK] Сценарій 6 (повторне повернення) захищений.\n";
    }

    // 7. Видача іншому користувачу після повернення
    registry.createIssue(student2, laptop);
    assert(laptop.isIssued() == true);
    assert(student2.getActiveIssuesCount() == 1);

    std::cout << "\n[SUCCESS] Усі сценарії успішно пройдено без збоїв інваріантів!\n";
    return 0;
}