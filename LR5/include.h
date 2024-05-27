#include <iostream>
#include <string>
#include <fstream>
#include <memory>

class FractionNumber {

private:
    int* numerator;
    int* denominator;

public:
    //����������� � �����������
    FractionNumber(int num, int denom) : numerator(new int(num)), denominator(new int(denom)) {
        if (denom == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
    }

    //����������� �����������
    FractionNumber(const FractionNumber& otherFraction) : numerator(new int(*otherFraction.numerator)), denominator(new int(*otherFraction.denominator)) {}

    //����������� �� ���������
    FractionNumber() : FractionNumber(5, 9) {}

    //����������� ����������
    virtual ~FractionNumber() {
        delete numerator;
        delete denominator;
        std::cout << "Fraction object is being destroyed." << std::endl;
    }

    //����������� ����� ��� ����������� �����
    virtual void display() const {
        std::cout << *numerator << "/" << *denominator << std::endl;
    }

    //����������� ����� ��� ����������� � float
    virtual float toFloat() const {
        return static_cast<float>(*numerator) / static_cast<float>(*denominator);
    }
};


// ����� CalculatedFraction
class CalculatedFraction : public FractionNumber {
public:
    CalculatedFraction(int num, int denom) : FractionNumber(num, denom){} 
};

// ����� MixedFraction
class MixedFraction : public FractionNumber {
private:
    int wholePart;

public:
    MixedFraction(int whole, int num, int denom) : FractionNumber(num, denom), wholePart(whole) {}

    void display() const override {
        std::cout << wholePart << " ";
        FractionNumber::display();
    }

    int getWholePart() const {
        return wholePart;
    }
};

// ���� ������
struct Node {
    std::shared_ptr<FractionNumber> data; // ������ ����
    Node* next; // ��������� �� ��������� ����

    // ����������� ����
    Node(std::shared_ptr<FractionNumber> frac) : data(frac), next(nullptr) {}
};

// ����� Deque
class Deque {
private:
    Node* head; // ��������� �� ������ ������
    Node* tail; // ��������� �� ����� ������

public:
    // ����������� �� ���������
    Deque() : head(nullptr), tail(nullptr) {}

    // ����������
    ~Deque() {
        while (head) { // �������� ���� ����� ������
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // ����� ���������� �������� � ������
    void addFront(std::shared_ptr<FractionNumber> frac) {
        Node* newNode = new Node(frac);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
    }

    // ����� ���������� �������� � �����
    void addRear(std::shared_ptr<FractionNumber> frac) {
        Node* newNode = new Node(frac);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // ����� �������� �������� �� ������
    void removeFront() {
        if (!head) {
            std::cerr << "Deque is empty." << std::endl;
            return;
        }
        Node* temp = head;
        head = head->next;
        if (!head) {
            tail = nullptr;
        }
        delete temp;
    }

    // ����� ������� �������� �� �������
    void insertAt(int index, std::shared_ptr<FractionNumber> frac) {
        if (index == 0) {
            addFront(frac);
            return;
        }
        Node* current = head;
        for (int i = 0; i < index - 1 && current; ++i) {
            current = current->next;
        }
        if (!current) {
            std::cerr << "Index out of bounds." << std::endl;
            return;
        }
        Node* newNode = new Node(frac);
        newNode->next = current->next;
        current->next = newNode;
        if (!newNode->next) {
            tail = newNode;
        }
    }

    // ����� �������� �������� �� �������
    void removeAt(int index) {
        if (index == 0 && head) {
            removeFront();
            return;
        }
        Node* current = head;
        for (int i = 0; i < index - 1 && current; ++i) {
            current = current->next;
        }
        if (!current || !current->next) {
            std::cerr << "Index out of bounds." << std::endl;
            return;
        }
        Node* temp = current->next;
        current->next = temp->next;
        if (!current->next) {
            tail = current;
        }
        delete temp;
    }

    // ����� ������ �������� �� �������
    std::shared_ptr<FractionNumber> find(int index) {
        Node* current = head;
        for (int i = 0; i < index && current; ++i) {
            current = current->next;
        }
        if (!current) {
            std::cerr << "Index out of bounds." << std::endl;
            return nullptr;
        }
        return current->data;
    }

    // ����� ����������� ���� ��������� ������
    void displayAll() const {
        Node* current = head;
        while (current) {
            current->data->display();
            current = current->next;
        }
    }
};
