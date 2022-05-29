#include <iostream>
#include "Container.h"
#include "Object.h"

uint16_t Object::count = 0;

Exercise* RandStuff(Container<Exercise*> &cont) {
	Exercise* ex;
	int k = rand() % 4;
	char sign[4] = {'+', '-', '*', '/'};
	int ind = 0;
	switch (k) {
	case 0:
		ex = new Arithmetical(rand() % 50, rand() % 50, sign[rand() % 4], std::to_string(ind));
		++ind;
		return ex;
	case 1:
		ex = new CounterObjectsInContainer(cont);
		return ex;
	case 2:
		ex = new CounterExercises(cont);
		return ex;
	case 3:
		ex = new CountObject;
		return ex;
	default:
		throw "Такое не добавлял...";
		break;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	Container <Exercise*> exers;

	Exercise* question0 = RandStuff(exers);
	AddExercise* add0 = new AddExercise(exers, question0);
	add0->execute();
	Exercise* question1 = RandStuff(exers);
	AddExercise* add1 = new AddExercise(exers, question1);
	add1->execute();
	Exercise* question2 = RandStuff(exers);
	AddExercise* add2 = new AddExercise(exers, question2);
	add2->execute();
	Exercise* question3 = RandStuff(exers);
	AddExercise* add3 = new AddExercise(exers, question3);
	add3->execute();
	Exercise* question4 = RandStuff(exers);
	AddExercise* add4 = new AddExercise(exers, question4);
	add4->execute();
	Exercise* question5 = RandStuff(exers);
	AddExercise* add5 = new AddExercise(exers, question5);
	add5->execute();
	Exercise* question6 = RandStuff(exers);
	AddExercise* add6 = new AddExercise(exers, question6);
	add6->execute();
	Exercise* question7 = RandStuff(exers);
	AddExercise* add7 = new AddExercise(exers, question7);
	add7->execute();
	Exercise* question8 = RandStuff(exers);
	AddExercise* add8 = new AddExercise(exers, question8);
	add8->execute();
	Exercise* question9 = RandStuff(exers);
	AddExercise* add9 = new AddExercise(exers, question9);
	add9->execute();

	Container <std::string> info;

	CountObject* count = new CountObject;
	count->execute();
	std::cout << count->toString() << std::endl;

	while (!exers.is_empty()) {
		exers.show_first()->execute();
		info.push_back(exers.show_first()->toString());
		exers.pop_first();
	}

	for (Container<std::string>::Enumeration i = info.begin(); i != info.end(); i++) {
		std::cout << i.get_list()->data << std::endl;
	}

	exers.clear();
	info.clear();
	if ((!exers.is_empty()) || (!info.is_empty())) {
		throw "Ой, походу не пустые:)";
	}

	delete count;

	delete add0;
	delete add1;
	delete add2;
	delete add3;
	delete add4;
	delete add5;
	delete add6;
	delete add7;
	delete add8;
	delete add9;
	delete question0;
	delete question1;
	delete question2;
	delete question3;
	delete question4;
	delete question5;
	delete question6;
	delete question7;
	delete question8;
	delete question9;

	CountObject* count0 = new CountObject;
	count0->execute();
	std::cout << count0->toString() << std::endl;

	delete count0;

	return 0;
}