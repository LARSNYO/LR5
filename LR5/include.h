#include <iostream>
#include <string>
#include <fstream>
#include <memory>

class FractionNumber {

private:
    int* numerator;
    int* denominator;

public:
    //Конструктор с параметрами
    FractionNumber(int num, int denom) : numerator(new int(num)), denominator(new int(denom)) {
        if (denom == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
    }

    //Конструктор копирования
    FractionNumber(const FractionNumber& otherFraction) : numerator(new int(*otherFraction.numerator)), denominator(new int(*otherFraction.denominator)) {}

    //Конструктор по умолчанию
    FractionNumber() : FractionNumber(5, 9) {}

    //Виртуальный деструктор
    virtual ~FractionNumber() {
        delete numerator;
        delete denominator;
        std::cout << "Fraction object is being destroyed." << std::endl;
    }

    //Виртуальный метод для отображения дроби
    virtual void display() const {
        std::cout << *numerator << "/" << *denominator << std::endl;
    }

    //Виртуальный метод для конвертации в float
    virtual float toFloat() const {
        return static_cast<float>(*numerator) / static_cast<float>(*denominator);
    }
};


// Класс CalculatedFraction
class CalculatedFraction : public FractionNumber {
public:
    CalculatedFraction(int num, int denom) : FractionNumber(num, denom){} 
};

// Класс MixedFraction
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

// Узел списка
struct Node {
    std::shared_ptr<FractionNumber> data; // Данные узла
    Node* next; // Указатель на следующий узел

    // Конструктор узла
    Node(std::shared_ptr<FractionNumber> frac) : data(frac), next(nullptr) {}
};

// Класс Deque
class Deque {
private:
    Node* head; // Указатель на голову списка
    Node* tail; // Указатель на хвост списка

public:
    // Конструктор по умолчанию
    Deque() : head(nullptr), tail(nullptr) {}

    // Деструктор
    ~Deque() {
        while (head) { // Удаление всех узлов списка
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Метод добавления элемента в начало
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

    // Метод добавления элемента в конец
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

    // Метод удаления элемента из начала
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

    // Метод вставки элемента по индексу
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

    // Метод удаления элемента по индексу
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

    // Метод поиска элемента по индексу
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

    // Метод отображения всех элементов списка
    void displayAll() const {
        Node* current = head;
        while (current) {
            current->data->display();
            current = current->next;
        }
    }
};
