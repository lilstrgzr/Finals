#include <iostream>
#include<thread>
#include<chrono>


enum Direction {
	dir_min,
	up, 
	right,
	down,
	left,
	dir_max
};

class A {
public:
	virtual void print() const {
		std::cout << "A\n";
	}
};

class B : public A {
public:
	virtual void print() const override {
		std::cout << "B\n";
	}

	void special() const {
		std::cout << "B.special()\n";
	}
};

class C : public B {
public:
	void print() const override {
		std::cout << "C\n";
	}
};

double sum(double num1, double num2) {
	std::cout << "Thread №" << std::this_thread::get_id() << "\tSTART CALCULATING-------\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	std::cout << "Thread №" << std::this_thread::get_id() << "\tGETTING RESULT-------\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	std::cout << "Thread №" << std::this_thread::get_id() << "\tSTOP CALCULATING-------\n";
	return num1 + num2;
}

int main() {
	setlocale(LC_ALL, "russian");

	//Enums

	Direction dir = static_cast<Direction>(3);
	std::cout << dir << std::endl;
	
		

	do {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		switch (dir) {
		case up:
			std::cout << "Шаг вверх\n";
			break;
		case right:
			std::cout << "Шаг вправо\n";
			break;
		case down:
			std::cout << "Шаг влево\n";
			break;
		case left:
			std::cout << "Шаг вниз\n";
			break;
		}
		dir = static_cast<Direction>(dir + 1);
		if (dir == dir_max)
			dir = static_cast<Direction>(dir_min + 1);
	} while (true);



	//Привидения типов в стиле С++

	int num = 10;
	std::cout << static_cast<char>(num);
	A* pa = new B;
	pa->print();

	B* pb = static_cast<B*>(pa);
	pb->print();
	pb->special();

	pa = new A;
	std::cout << "---------\n";
	B* rpb = static_cast<B*>(pa);
	rpb->print();
	rpb->special();

	B* tpb;
	std::cout << "Enter number -> ";
	std::cin >> num;

	if (num % 2 == 0)
		tpb = new B;
	else
		tpb = static_cast<B*>(new A);
	C* pc = dynamic_cast<C*>(tpb);
	pc->print();




	int result{};
	std::thread th([&result]() {
		result = sum(5, 7);
		});

	for (int i = 0; i < 10; ++i) {
		std::cout << "Thread №" << std::this_thread::get_id() << "\tmain()\t" << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	}

	th.join();
	std::cout << "result = " << result << std::endl;




		return 0;
}