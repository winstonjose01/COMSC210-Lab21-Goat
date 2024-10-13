// COMS210 | Lab 21  | Winston Jose
// IDE used: Visual Studio Code
// Github link:


#include <iostream>
#include <random>
#include <iomanip>
using namespace std;

const int SIZE = 15;
const int MAX = 15, MIN = 1, MAX_LIST = 20, MIN_LIST = 5;

class Goat{
    private:
        int age;            // Goat's age
        string name;        // Goat's name
        string color;       // Goat's color

        // Arrays to store possible names and colors for goats
        string names[SIZE] = {
                        "Billy", "Nanny", "Daisy", "Goatbert", "Bella", 
                        "Luna", "Charlie", "Mabel", "Finn", "Pepper", 
                        "Clover", "Rosie", "Hazel", "Oreo", "Patches"};
        string colors[SIZE] = {
                        "Red", "Green", "Blue", "Yellow", "Purple", 
                        "Orange", "Pink", "Brown", "Black", "White", 
                        "Gray", "Cyan", "Magenta", "Violet", "Turquoise"};
    public:
    // Default constructor to randomly assign a name, color, and age to a goat
        Goat(){
            age = MIN + rand() % (MAX - MIN + 1);
            name = names[rand() % (MAX - MIN + 1)];
            color = colors[rand() % (MAX - MIN + 1)];
        }

        // Parameterized constructor to create a goat with a specific age, name, and color
        Goat(int a, string n, string c){
            age = a; name = n; color = c;
        }

        // Function to print Goat's details (name, color, and age)
        void print() const {
            cout << setw(5) << " " << name << " (" << color << ", " << age << ")" << endl;
        }

        // Function to get the name of the goat
        string getname() {
            return name;
        }
        
        
};

// Class representing a doubly linked list for Goat objects
class DoublyLinkedList {
    private:
        struct Node{
            // Structure for a node in the doubly linked list
            Goat goat;      
            Node *prev;
            Node *next;
             // Constructor for Node, initializing goat, prev, and next pointers
            Node (Goat &g, Node *p = nullptr, Node *n = nullptr){
                goat = g;
                prev = p;
                next = n;
            }
        };
        Node *head; // Pointer to the first node on the list
        Node *tail; // Pointer to the last node on the list
     public:
        // Constructor to initialize an empty doubly linked list
        DoublyLinkedList(){
            head = nullptr; 
            tail = nullptr; 
        }
    
        void push_back(Goat gt){
            Node *newNode = new Node(gt);
            if (!tail)
                head = tail = newNode;
            else{
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
                }
        }

        void push_front(Goat gt){
            Node* newNode = new Node(gt);
            if (!head)
                head = tail = newNode;
            else{
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
        }

        void insert_after(Goat gt, int position){
            if (position <0){
                cout << "Position must be >=0" << endl;
                return;
            }

            Node *newNode = new Node(gt);
            if (!head){
                head = tail = newNode;
                return;
            }

            Node *temp = head;
            for (int i = 0; i < position && temp; i++)
                temp = temp->next;
            
            if (!temp){
                cout << "Position exceeds list size. Node not inserted. \n";
                delete newNode;
                return;
            }

            newNode->next = temp->next;
            newNode->prev = temp;
            if (temp->next)
                temp->next->prev = newNode;
            else
                tail = newNode; // Inserting at the end
            temp->next = newNode;
        }

        void delete_node(Goat gt){
            if (!head) return;

            Node *temp = head;
            while (temp && !(temp->goat.getname() == gt.getname()))
                temp = temp ->next;
            
            if (!temp) return; // Value not found

            if (temp->prev){
                temp->prev->next = temp->next;
            }
            else{
                head = temp->next; // Deleting the head
            }

            if (temp->next){
                temp->next->prev = temp->prev;
            }
            else {
                tail = temp->prev; // Deleting the tail
            }

            delete temp;
        }

        void print(){
            Node *current = head;
            if (!current){
                cout << "List is empty!" << endl;
                return;
            }
            while (current){
                current-> goat.print();
                current = current->next;            
            }
            cout << endl;
        }
        void print_reverse(){
            Node *current = tail;
            if(!current){
                cout << "List is empty!" << endl;
                return;
            }
            while (current){
                current->goat.print();
                current = current->prev;
            }
            cout << endl;
        }

        ~DoublyLinkedList(){
            while (head){
                Node *temp = head;
                head = head->next;
                delete temp;
            }
        }
};

int main(){
    srand(time(0));
    DoublyLinkedList goat_list;
    int size = MIN_LIST + rand()%(MAX_LIST - MIN_LIST  + 1);

    for (int i = 0; i < size; i++){
        goat_list.push_back(Goat());
    }

    cout << "Forward:" << endl;
    goat_list.print();

    cout << "Backward:" << endl;
    goat_list.print_reverse();

    goat_list.~DoublyLinkedList();

    return 0;
}