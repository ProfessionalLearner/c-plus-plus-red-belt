#include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:
  struct Node {
    T value;
    Node* next = nullptr;
  };

  ~LinkedList() {
	  while(head != nullptr) {
		  PopFront();
	  }
  }

  void PushFront(const T& value) {
	  Node* new_node = new Node;
	  new_node->value = value;
	  new_node->next = head;
	  head = new_node;
  }

  void InsertAfter(Node* node, const T& value) {
	  if(node == nullptr) {
		  PushFront(value);
	  } else {
		  Node* next_node = node->next;
		  Node* new_node = new Node{value, next_node};
		  node->next = new_node;
	  }
  }

  void RemoveAfter(Node* node) {
	  if(node == nullptr) {
		  PopFront();
	  } else if(node->next == nullptr) {
		  return;
	  } else {
		  Node* remove_node = node->next;
		  node->next = node->next->next;
		  delete remove_node;
	  }
  }

  void PopFront() {
	  if(head == nullptr) {
		  return;
	  } else {
		 Node* head_next = head->next;
		 delete head;
		 head = head_next;
	  }
  }

  Node* GetHead() { return head; }
  const Node* GetHead() const { return head; }

private:
  Node* head = nullptr;
};


int main() {
	return 0;
}
