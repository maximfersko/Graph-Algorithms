#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <cstddef>
#include <iostream>

#include "node.hpp"

namespace containers {

template <class T>
class Stack {
   public:
    using value_type = T;
    using reference = T&;
    using const_reference = value_type const&;
    using size_type = size_t;

   private:
    Node<T>* head_;

   public:
    Stack() : head_(nullptr){};

    explicit Stack(std::initializer_list<value_type> const& items) : Stack() {
        for (auto i = items.begin(); i != items.end(); ++i) {
            value_type value = *i;
            push(value);
        }
    };

    Stack(const Stack& other) : Stack() {
        if (this != &other) {
            *this = other;
        }
    };

    Stack(Stack&& other) {
        if (this != &other) {
            std::swap(head_, other.head_);
            other.head_ = nullptr;
        }
    };

    ~Stack() { free_stack(); };

    void push(const_reference value) {
        Node<T>* new_head = new Node<T>(value);
        new_head->SetNext(nullptr);
        if (!empty()) {
            new_head->SetNext(head_);
        }
        head_ = new_head;
    };

    void pop() {
        Node<T>* tmp = head_->GetNext();
        delete head_;
        head_ = tmp;
    };

    size_type size() {
        size_type size = 0;
        Node<T>* tmp = head_;
        while (tmp) {
            ++size;
            tmp = tmp->GetNext();
        }
        return size;
    };

    bool empty() { return size() == 0; };

    const_reference top() { return head_->GetValue(); };

    void swap(Stack& other) {
        Node<T>* tmp = head_;
        head_ = other.head_;
        other.head_ = tmp;
    };

    Stack& operator=(Stack&& other) {
        std::swap(this->head_, other.head_);
        return *this;
    };

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            Node<T>* tmp = other.head_;
            free_stack();
            copy_stack(*this, tmp);
        }
        return *this;
    }

    template <typename... Args>
    void emplace_front(Args&&... args) {
        value_type value(args...);
        push(value);
    };

   private:
    void copy_stack(Stack& other, Node<T>* iter) {
        value_type value;
        Node<T>* next = iter;
        if (iter != nullptr) {
            value = next->GetValue();
            next = next->GetNext();
            copy_stack(other, next);
        }
        if (next != nullptr) {
            other.push(value);
        }
    };

    void free_stack() {
        while (head_ != nullptr) {
            pop();
        }
    }
};

}  // namespace s21

#endif  // S21_STACK_H_
