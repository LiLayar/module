#include <iostream>
#include <mutex>

class Production {
private:
    // ��������� ����������� �� ����������, ��� ���������� ��������� ���������� �����
    Production() {
        // ����������� ������� ��� ����� �����, �� ������� ��������
    }

    ~Production() {
        // ��������� ������� ��� ���� ���������� 䳿
    }

    // �������� ��������� �� ���������
    Production(const Production&) = delete;
    Production& operator=(const Production&) = delete;

    // ������ ��������� �����
    static Production* instance;

    // ������ ��� ����������������
    static std::mutex mutex;

public:
    // ��������� ����� ��� ��������� ������� ���������� �����
    static Production& getInstance() {
        // ��������, �� � ��� ��������� ���������
        if (!instance) {
            std::lock_guard<std::mutex> lock(mutex);  // ���������� ������� ��� ����������������

            // �������� �� ���, ������� �������, ���� ������ �� ���������� �������, ����� ���� ������� ���������
            if (!instance) {
                instance = new Production();
            }
        }

        return *instance;
    }

    // ������ �����������, �� ������ ����������������� ��� ������ � ����������

    void produceItem() {
        std::cout << "����������� ������..." << std::endl;
        // ����� ����������� ������
    }

    void shipItem() {
        std::cout << "³����������� ������..." << std::endl;
        // ����� ������������ ������
    }
};

// ����������� ��������� ����� �����
Production* Production::instance = nullptr;
std::mutex Production::mutex;

int main() {
    // ������������ ������� ���������� �����
    Production& production = Production::getInstance();

    // ����������� �� ������������ ������
    production.produceItem();
    production.shipItem();

    return 0;
}