#include <iostream>
#include <mutex>

class Production {
private:
    // Приватний конструктор та деструктор, щоб заборонити створення екземплярів ззовні
    Production() {
        // Ініціалізація ресурсів або інших даних, які потрібно зберігати
    }

    ~Production() {
        // Звільнення ресурсів або інші завершальні дії
    }

    // Заборона копіювання та присвоєння
    Production(const Production&) = delete;
    Production& operator=(const Production&) = delete;

    // Єдиний екземпляр класу
    static Production* instance;

    // Мютекс для потокозахищеності
    static std::mutex mutex;

public:
    // Статичний метод для отримання єдиного екземпляра класу
    static Production& getInstance() {
        // Перевірка, чи є вже створений екземпляр
        if (!instance) {
            std::lock_guard<std::mutex> lock(mutex);  // Захоплення мютекса для потокозахищеності

            // Перевірка ще раз, оскільки можливо, поки чекали на захоплення мютекса, інший потік створив екземпляр
            if (!instance) {
                instance = new Production();
            }
        }

        return *instance;
    }

    // Методи виробництва, які можуть використовуватися для роботи з продукцією

    void produceItem() {
        std::cout << "Виробництво товару..." << std::endl;
        // Логіка виробництва товару
    }

    void shipItem() {
        std::cout << "Відвантаження товару..." << std::endl;
        // Логіка відвантаження товару
    }
};

// Ініціалізація статичних членів класу
Production* Production::instance = nullptr;
std::mutex Production::mutex;

int main() {
    // Використання єдиного екземпляра класу
    Production& production = Production::getInstance();

    // Виробництво та відвантаження товару
    production.produceItem();
    production.shipItem();

    return 0;
}