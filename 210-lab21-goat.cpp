// COMS210 | Lab 21  | Winston Jose
// IDE used: Visual Studio Code
// Github link:


#include <iostream>
#include <random>
using namespace std;

class Goat{
    private:
        int age;
        string name;
        string color;


};


class DoublyLinkedList {
    private:
        struct Node{
            Goat goat;
            Node *prev;
            Node *next;
            Node (Goat &g, Node *p = nullptr, Node *n = nullptr){
                goat = g;
                prev = p;
                next = n;
            }
        };
        Node *head;
        Node *tail;
     public:
        DoublyLinkedList(){
            head = nullptr;
            tail = nullptr;
        }
    
    void push_back(Goat gt){
        Node *newNode = new Node(gt);
        if (!tail)
            head = tail = newNode
        


    }

};