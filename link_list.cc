#include <iostream>
#include <cassert>

// Template class for a doubly linked list
template<typename T>
class DoublyLinkedList {
private:
    // Internal node structure
    struct Node {
        T data;          // The data stored in the node
        Node* next;      // Pointer to the next node in the list
        Node* prev;      // Pointer to the previous node in the list

        // Constructor for creating a new node
        Node(T val, Node* p = nullptr, Node* n = nullptr) : data(val), prev(p), next(n) {}
    };

    Node* head; // Pointer to the first node in the list
    Node* tail; // Pointer to the last node in the list
    size_t size; // The number of nodes in the list

public:
    // Constructor to initialize an empty list
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Destructor to clean up all nodes
    ~DoublyLinkedList() {
        while (head) {
            remove(head->data);
        }
    }

    void addFront(T value) {
        Node* newNode = new Node(value, nullptr, head);
        if (head != nullptr) {
            head->prev = newNode;
        }
        head = newNode;
        if (tail == nullptr) {
            tail = newNode;
        }
        size++;
    }

    void addBack(T value) {
        Node* newNode = new Node(value, tail, nullptr);
        if (tail != nullptr) {
            tail->next = newNode;
        }
        tail = newNode;
        if (head == nullptr) {
            head = newNode;
        }
        size++;
    }

    // Function to remove a node with the specified value
    bool remove(T value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                if (current->prev) current->prev->next = current->next;
                if (current->next) current->next->prev = current->prev;
                if (current == head) head = current->next;
                if (current == tail) tail = current->prev;
                delete current;
                size--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Function to return the size of the list
    size_t getSize() const {
        return size;
    }

    // Function to print all elements in the list
    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

void testEmptyList() {
    DoublyLinkedList<int> list;
    assert(list.getSize() == 0);
    assert(!list.remove(10)); // Attempt to remove from empty list should fail
    std::cout << "Test empty list passed.\n";
}

void testAddFrontAndBack() {
    DoublyLinkedList<int> list;
    list.addFront(10);
    list.addBack(20);
    list.addFront(30);
    assert(list.getSize() == 3);
    list.print(); // Should print: 30 10 20
    std::cout << "Test add front and back passed.\n";
}

void testRemoveElements() {
    DoublyLinkedList<int> list;
    list.addBack(10);
    list.addBack(20);
    list.addBack(30);
    assert(list.remove(20)); // Remove middle element
    assert(list.getSize() == 2);
    list.print(); // Should print: 10 30
    assert(list.remove(10)); // Remove head
    assert(list.remove(30)); // Remove tail
    assert(list.getSize() == 0);
    assert(!list.remove(40)); // Attempt to remove non-existent element
    list.print(); // Should print nothing
    std::cout << "Test remove elements passed.\n";
}

void testListIntegrity() {
    DoublyLinkedList<int> list;
    for (int i = 0; i < 100; i++) {
        list.addBack(i);
    }
    for (int i = 0; i < 50; i++) {
        assert(list.remove(i));
    }
    assert(list.getSize() == 50);
    for (int i = 50; i < 100; i++) {
        assert(list.remove(i));
    }
    assert(list.getSize() == 0);
    std::cout << "Test list integrity passed.\n";
}

int main() {
    testEmptyList();
    testAddFrontAndBack();
    testRemoveElements();
    testListIntegrity();
    std::cout << "All tests passed." << std::endl;
    return 0;
}