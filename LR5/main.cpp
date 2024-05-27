#include "include.h"

int main() {
	Deque deque; //�������� ������� Deque

	//�������� �������� ��������� �������
	std::shared_ptr<FractionNumber> frac1 = std::make_shared<FractionNumber>(3, 4);
	std::shared_ptr<FractionNumber> frac2 = std::make_shared<CalculatedFraction>(5, 6);
	std::shared_ptr<FractionNumber> frac3 = std::make_shared<MixedFraction>(2, 7, 8);

	//���������� ��������� � ���
	deque.addFront(frac1);
	deque.addRear(frac2);
	deque.insertAt(1, frac3);

	//����������� ��������� ����
	std::cout << "Deque after adding elements: " << std::endl;
	deque.displayAll();

	//�������� �������� �� ������ ����
	deque.removeFront();
	std::cout << "\nDeque after removing front element: " << std::endl;
	deque.displayAll();

	//�������� �������� �� �������
	deque.removeAt(1);
	std::cout << "\nDeque after removing element at index 1:" << std::endl;
	deque.displayAll();

	// ����� �������� �� �������
	std::shared_ptr<FractionNumber> found = deque.find(0);
	if (found) {
		std::cout << "\nElement found at index 0:" << std::endl;
		found->display();
	}
	
	return 0;
}