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
        int age;
        string name;
        string color;
        string names[SIZE] = {
                        "Billy", "Nanny", "Daisy", "Goatbert", "Bella", 
                        "Luna", "Charlie", "Mabel", "Finn", "Pepper", 
                        "Clover", "Rosie", "Hazel", "Oreo", "Patches"};
        string colors[SIZE] = {
                        "Red", "Green", "Blue", "Yellow", "Purple", 
                        "Orange", "Pink", "Brown", "Black", "White", 
                        "Gray", "Cyan", "Magenta", "Violet", "Turquoise"};
    public:
        Goat(){
            age = MIN + rand() % (MAX - MIN + 1);
            name = names[rand() % (MAX - MIN + 1)];
            color = colors[rand() % (MAX - MIN + 1)];
        }
        Goat(int a, string n, string c){
            age = a; name = n; color = c;
        }

        void print() const {
            cout << setw(5) << " " << name << " (" << color << ", " << age << ")" << endl;
        }
        
        
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
            while (temp && !(temp->goat == gt))
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