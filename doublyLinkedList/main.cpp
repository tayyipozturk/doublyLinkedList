#include <iostream>

#include "DoublyLinkedList.h"

int main() {
    DoublyLinkedList<int> llist;
    DoublyLinkedList<int> second;

    llist.print();
    llist.insertBack(123213);
    llist.print();
    llist.removeNode(123213);
    
    llist.insertFront(6);
    llist.insertBack(2);
    llist.insertSorted(4);


    llist.print();

    return 0;
}
