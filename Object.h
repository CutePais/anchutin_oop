#pragma once
#include <iostream>
#include "Container.h"
#include <string>

class Object {
public:
	virtual std::string toString() const = 0;
	Object() {
	}
	~Object() {
	}
	Object(const Object& other) {
		++count;
	}
protected:
	static uint16_t count;
};

class Exercise : public Object {
public:
	virtual void execute() = 0;
	virtual bool HasRes() = 0;
	Exercise() {
		++count;
		complete = false;
	}
	~Exercise() {
		--count;
	}
protected:
	bool complete;
};

class Named : virtual public Object {
protected:
	std::string o_name;
};

class Arithmetical : public Named, public Exercise {
private:
	int val_1;
	int val_2;
	char val_sign;
	double res;
public:
	Arithmetical(int a, int b, char sign, std::string name): val_1(a), val_2(b), val_sign(sign){
		o_name = name;
		res = 0;
	}

	bool HasRes() {
		return complete;
	}

	double take_res() {
		return res;
	}

	void execute() {
		try {
			switch (val_sign) {
			case '+':
				res = val_1 + val_2;
				complete = true;
				break;
			case '-':
				res = val_1 - val_2;
				complete = true;
				break;
			case '*':
				res = val_1 * val_2;
				complete = true;
				break;
			case '/':
				res = val_1 / val_2;
				complete = true;
				break;
			default:
				throw "Какой знак, такая и ошибка";
				break;
			}
		}
		catch (const char* err) {
			std::cout << err << std::endl;
		}
	}

	std::string toString() const {
		if (complete) {
			std::string issue = "Задача решена: " + std::to_string(val_1) + " " + val_sign + " " + std::to_string(val_2) + " = " + std::to_string(res);
			return issue;
		}
		else {
			std::string issue = "Задача пока что не решена, но возможно получить результат: " + std::to_string(val_1) + " " + val_sign + " " + std::to_string(val_2) + " = " + std::to_string(res);
			return issue;
		};
	}
};

class AddExercise : public Exercise {
private:
	Container<Exercise*>& cont;
	Exercise* task;
public:
	AddExercise(Container<Exercise*>& other_c, Exercise* other_ex): cont(other_c), task(other_ex) {
	}

	bool HasRes(){
		return false;
	}

	void execute() {
		cont.push_back(task);
		complete = true;
	}

	std::string toString() const {
		if (complete) {
			std::string issue = "Задача была добавлена в контейнер";
			return issue;
		}
		else {
			std::string issue = "Задача всё ещё не добавлена, но действие возможно";
			return issue;
		};
	}
};

class CounterObjectsInContainer : public Exercise {
private:
	Container<Exercise*>& cont;
	uint16_t count;
public:
	CounterObjectsInContainer(Container<Exercise*>& other_c) : cont(other_c), count(0) {
	}

	bool HasRes(){
		return true;
	}

	uint16_t take_res() {
		return count;
	}

	void execute() {
		cont.size();
		complete = true;
	}

	std::string toString() const {
		if (complete) {
			std::string issue = "Количество объектов рассчитано";
			return issue;
		}
		else {
			std::string issue = "Количество объектов всё ещё не рассчитано, но данная операция возможна";
			return issue;
		};
	}
};

class CounterExercises : public Exercise {
private:
	Container<Exercise*>& cont;
	uint16_t count;
public:
	CounterExercises(Container<Exercise*>& other_c) : cont(other_c), count(0) {
	}

	bool HasRes(){
		return true;
	}

	uint16_t take_res() {
		return count;
	}

	void execute() {
		for (Container<Exercise*>::Enumeration i = cont.begin(); i != cont.end(); i++) {
			if (i.get_list()->data->HasRes()) count++;
		}
		complete = true;
	}

	std::string toString() const {
		if (complete) {
			std::string issue = "Количество задач с результатом рассчитано";
			return issue;
		}
		else {
			std::string issue = "Количество задач с результатом всё ещё не рассчитано, но данная операция возможна";
			return issue;
		};
	}
};

class ClearObject: public Exercise {
private:
	Container<Exercise*>& cont;
public:
	ClearObject(Container<Exercise*>& other_c) : cont(other_c) {
	}

	bool HasRes(){
		return false;
	}

	void execute() {
		cont.clear();
		complete = true;
	}

	std::string toString() const {
		if (complete) {
			std::string issue = "Контейнер очищен";
			return issue;
		}
		else {
			std::string issue = "Контейнер не очищен, но данная операция возможна";
			return issue;
		};
	}
};

class CountObject : public Exercise {
private:
	uint16_t counter;
public:
	CountObject(){
		counter = 0;
	}

	bool HasRes(){
		return true;
	}

	uint16_t take_res() {
		return counter;
	}

	void execute() {
		counter = count;
		complete = true;
	}

	std::string toString() const {
		if (complete) {
			std::string issue = "Количество наследников-объектов вычислено: " + std::to_string(counter);
			return issue;
		}
		else {
			std::string issue = "Количество наследников-объектов всё ещё не вычислено, но данная операция возможна";
			return issue;
		};
	}
};

