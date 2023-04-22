#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include <iostream>

#include "node.hpp"
namespace containers {

template <class T>
class Queue {
   public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = value_type const&;
    using size_type = size_t;

   private:
    Node<T>* head_ = nullptr;
    Node<T>* tail_ = nullptr;
    size_type size_ = 0;

   public:
    Queue() : size_(0) {
        Node<T>* null_tmp = new Node<T>;
        head_ = null_tmp;
        tail_ = null_tmp;
    };

    explicit Queue(std::initializer_list<value_type> const& items) : Queue() {
        for (auto i = items.begin(); i != items.end(); ++i) {
            value_type value = *i;
            push(value);
        }
    };

    Queue(const Queue& q) : Queue() {
        for (Node<T>* count_node = q.head_; count_node;
             count_node = count_node->GetPrev()) {
            push(count_node->GetValue());
        }
    };

    Queue(Queue&& q) : head_(nullptr), tail_(nullptr) {
        std::swap(head_, q.head_);
        std::swap(tail_, q.tail_);
        size_ = q.size_;
        q.size_ = 0;
    };

    ~Queue() {
        while (head_) {
            pop();
        }
    };

    Queue& operator=(Queue&& other) {
        while (head_) {
            pop();
        }
        swap(other);
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
        return *this;
    };

    const_reference front() { return head_->GetValue(); };

    const_reference back() { return tail_->GetNext()->GetValue(); };

    void push(const_reference value) {
        tail_->SetPrev(new Node<T>(value_type(), tail_));
        tail_->SetValue(value);
        tail_ = tail_->GetPrev();
        ++size_;
    };

    void pop() {
        Node<T>* tmp = head_->GetPrev();
        delete head_;
        head_ = tmp;
        --size_;
    };

    void swap(Queue& other) {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    };

    size_type size() { return size_; };

    bool empty() { return !size_; };

    template <typename... Args>
    void emplace_back(Args&&... args) {
        value_type value(args...);
        push(value);
    };
};

}  // namespace s21

#endif  // S21_QUEUE_H_
