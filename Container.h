#pragma once
#include <iostream>
#include <exception>
#include <cstdint>
#include <cstdlib>

template <typename T> class Container {
private:
	struct List {
		T data;
		List* prev;
		List* next;
	};
	List* head;
	List* tail;
	uint16_t contsize;

public:
	Container() {
		contsize = 0;
		head = NULL;
		tail = NULL;
	}

	~Container() {
		clear();
	}

	Container(const Container& other) {
		contsize = 0;
		head = NULL;
		tail = NULL;

		List* k = other.head;

		while (k != NULL) {
			push_back(k->data);
			k = k->next;
		}
	}

	void push_front(const T& data) {
		List* k = new List;
		k->data = data;
		k->prev = NULL;
		k->next = head;

		if (head != NULL) {
			head->prev = k;
		}

		if (contsize == 0) {
			head = k;
			tail = k;
		}
		else head = k;

		++contsize;
	}

	void push_back(const T& data) {
		List* k = new List;
		k->data = data;
		k->prev = tail;
		k->next = NULL;

		if (tail != NULL) {
			tail->next = k;
		}

		if (contsize == 0) {
			head = k;
			tail = k;
		}
		else tail = k;

		++contsize;
	}

	void pop_first() {
		if (contsize == 0) {
			throw std::exception("Ща бы с пустого контейнера удолять в 2к22...");
		}
		if (contsize == 1) {
			head = NULL;
			tail = NULL;
			--contsize;
		}
		else {
			List* k = head->next;
			k->prev = NULL;
			head = k;
			--contsize;
		}
	}

	void pop_last() {
		if (contsize == 0) {
			throw std::exception("Ща бы с пустого контейнера удолять в 2к22...");
		}
		if (contsize == 1) {
			head = NULL;
			tail = NULL;
			--contsize;
		}
		else {
			List* k = tail->prev;
			k->next = NULL;
			tail = k;
			--contsize;
		}
	}

	T& show_first() const {
		if (contsize == 0) {
			throw std::exception("Не покажусь. Я пустой:(");
		}
		else return head->data;
	}

	T& show_last() const {
		if (contsize == 0) {
			throw std::exception("Не покажусь. Я пустой:(");
		}
		else return tail->data;
	}

	class Enumeration {
	private:
		List* list;
	public:
		Enumeration(List* k) : list(k) {
		};

		List* get_list() {
			return list;
		}

		Enumeration operator++(int) {
			if (list != NULL) {
				list = list->next;
				return *this;
			}
		}

		Enumeration operator--(int) {
			if (list != NULL) {
				list = list->prev;
				return *this;
			}
		}

		bool operator==(const Enumeration& other) {
			return list == other.list;
		}

		bool operator!=(const Enumeration& other) {
			return list != other.list;
		}
	};

	Enumeration begin() {
		return Enumeration(head);
	}
	Enumeration end() {
		return Enumeration(tail);
	}

	uint16_t size() const {
		return contsize;
	}

	bool is_empty() const {
		return contsize == 0;
	}

	void swap(Container& other) {
		uint16_t cont2size = other.contsize;
		other.contsize = contsize;
		contsize = cont2size;
		List* k = other.head;
		other.head = head;
		head = k;
		k = other.tail;
		other.tail = tail;
		tail = k;
	}

	void reverse() {
		List* k = head;
		List* prev = NULL;
		List* next = NULL;
		while (k != NULL) {
			next = k->next;
			k->prev = prev;
			prev = k;
			k = next;
		}
		head = prev;
	}

	void clear() {
		while (head != NULL) {
			List* k = head;
			head = head->next;
			delete k;
		}
		contsize = 0;
		head = NULL;
		tail = NULL;
	}

};