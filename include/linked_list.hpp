
#pragma once
#include <cstddef>
#include <stdexcept>
#include <cstring>

#include "list.hpp"

template <typename T>
class Node {
public:
	Node(const T& element)
		: m_prev(nullptr)
		, m_next(nullptr)
		, m_data(element) {
	}

	void set_prev(Node* new_value) {
		this->m_prev = new_value;
	}

	void set_next(Node* new_value) {
		this->m_next = new_value;
	}

	const T& get_data() {
		return this->m_data;
	}

	T& get_data_mut() {
		return this->m_data;
	}

	Node* get_next() {
		return this->m_next;
	}

	Node* get_prev() {
		return this->m_prev;
	}

private:
	Node* m_prev;
	Node* m_next;
	T m_data;
};

template <typename T>
class LinkedList : public List<T> {
public:
	size_t length() const {
		return this->m_size;
	}

	void push_front(const T& element) {
		Node<T>* node = new Node(element);
		if (this->is_empty()) {
			this->m_head = node;
			this->m_tail = node;
		}

		this->m_head->set_prev(node);
		node->set_next(this->m_head);
		this->m_head = node;
		this->m_size += 1;
	}

	void push_back(const T& element) {
		Node<T>* node = new Node(element);
		if (this->is_empty()) {
			this->m_head = node;
			this->m_tail = node;
		}

		this->m_tail->set_next(node);
		node->set_prev(this->m_tail);
		this->m_tail = node;
		this->m_size += 1;
	}

	T pop_back() {
		if (this->is_empty()) {
			throw std::out_of_range("List is empty");
		}
		T last = this->get_last();
		this->m_tail = this->m_tail->get_prev();
		delete this->m_tail->get_next();
		this->m_tail->set_next(nullptr);
		this->m_size -= 1;
		return last;
	}

	T pop_front() {
		if (this->is_empty()) {
			throw std::out_of_range("List is empty");
		}
		if (this->length() == 1) {
			const auto tmp = this->get_first();
			delete this->m_head;
			this->m_head = nullptr;
			this->m_tail = nullptr;
			this->m_size = 0;
			return tmp;
		}
		const auto first = this->get_first();
		this->m_head = this->m_head->get_next();
		delete this->m_head->get_prev();
		this->m_head->set_prev(nullptr);
		this->m_size -= 1;
		return first;
	}

	void insert(const size_t index, const T& element) {
		if (index >= this->length()) {
			this->push_back(element);
		}

		if (index == 0) {
			this->push_front(element);
		}

		Node<T>* curr = this->m_head;
		for (size_t i = 0; i < index; i++) {
			curr = curr->get_next();
		}
		Node<T>* node = new Node(element);

		node->set_next(curr);
		node->set_prev(curr->get_prev());
		curr->get_prev()->set_next(node);
		curr->set_prev(node);
		this->m_size += 1;
	}

	T remove(const size_t index) {
		if (index >= this->length()) {
			throw std::out_of_range("index is out of bounds");
		}
		if (index == 0) {
			return this->pop_front();
		}
		if (index - 1 == this->length()) {
			return this->pop_back();
		}
		if (this->length() == 1) {
			T tmp = this->get_first();
			delete this->m_head;
			this->m_head = nullptr;
			this->m_tail = nullptr;
			this->m_size = 0;
			return tmp;
		}
		Node<T>* curr = this->m_head;
		for (size_t i = 0; i < index; i++) {
			curr = curr->get_next();
		}
		T tmp = curr->get_data();
		Node<T>* prev = curr->get_prev();
		Node<T>* next = curr->get_next();
		delete curr;
		prev->set_next(next);
		next->set_prev(prev);
		this->m_size -= 1;
		return tmp;
	}

	bool is_empty() const {
		if (this->length() == 0) {
			return true;
		}
		return false;
	}

	const T& get(const size_t index) const {
		if (index >= this->length()) {
			throw std::out_of_range("index is out of bounds");
		}

		Node<T>* current = this->m_head;
		for (size_t i = 0; i < index; i++) {
			current = current->get_next();
		}

		return current->get_data();
	}

	T& get_mut(const size_t index) const {
		if (index >= this->length()) {
			throw std::out_of_range("index is out of bounds");
		}

		Node<T>* current = this->m_head;
		for (size_t i = 0; i < index; i++) {
			current = current->get_next();
		}

		return current->get_data_mut();
	}

	const T& get_first() const {
		if (this->is_empty() || this->m_head == nullptr) {
			throw std::out_of_range("List is empty");
		}
		return this->m_head->get_data();
	}

	const T& get_last() const {
		if (this->is_empty() || this->m_tail == nullptr) {
			throw std::out_of_range("List is empty");
		}
		return this->m_tail->get_data();
	}


private:
	Node<T>* m_head;
	Node<T>* m_tail;
	size_t m_size;
};