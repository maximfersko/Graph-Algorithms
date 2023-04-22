#ifndef S21_NODE_H_
#define S21_NODE_H_

namespace containers {
template <class T>
class Node {
   public:
    Node(T value = T(), Node* next = nullptr, Node* prev = nullptr)
        : value_(value), next_(next), prev_(prev){};
    T& GetValue() { return value_; };
    Node* GetNext() { return next_; };
    Node* GetPrev() { return prev_; };
    void SetNext(Node* new_next) { next_ = new_next; }
    void SetPrev(Node* new_prev) { prev_ = new_prev; }
    void SetValue(T new_value) { value_ = new_value; }

   private:
    T value_;
    Node* next_;
    Node* prev_;
};

}  // namespace s21

#endif  // S21_NODE_H