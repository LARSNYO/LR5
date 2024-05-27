#include "include.h"

int main() {
	Deque deque; //создание объекта Deque

	//Создание объектов различных классов
	std::shared_ptr<FractionNumber> frac1 = std::make_shared<FractionNumber>(3, 4);
	std::shared_ptr<FractionNumber> frac2 = std::make_shared<CalculatedFraction>(5, 6);
	std::shared_ptr<FractionNumber> frac3 = std::make_shared<MixedFraction>(2, 7, 8);

	//Добавление элементов в дек
	deque.addFront(frac1);
	deque.addRear(frac2);
	deque.insertAt(1, frac3);

	//Отображение элементов дека
	std::cout << "Deque after adding elements: " << std::endl;
	deque.displayAll();

	//Удаление элемента из начала дека
	deque.removeFront();
	std::cout << "\nDeque after removing front element: " << std::endl;
	deque.displayAll();

	//Удаление элемента по индексу
	deque.removeAt(1);
	std::cout << "\nDeque after removing element at index 1:" << std::endl;
	deque.displayAll();

	// Поиск элемента по индексу
	std::shared_ptr<FractionNumber> found = deque.find(0);
	if (found) {
		std::cout << "\nElement found at index 0:" << std::endl;
		found->display();
	}
	
	return 0;
}