#include <iostream>


using namespace std;

///////////////////////////////////////////////////challange 1///////////////////////////////////////////////////////
struct Student {
    string name;
    Student* next = nullptr;
};


struct Queue {
    Student* first = nullptr;
    Student* last = nullptr;

    int size() {
        int count = 0;
        Student* current = first;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    void enqueue(Student* newStudent, int index = 0) {
        int queueSize = size();

        if (index < 0 || index > queueSize) {
            cout << "queue is not that size" << endl;
            return;
        }

        if (index == 0) {
            if (first == nullptr && last == nullptr) {
                first = newStudent;
                last = newStudent;
            }
            else {
                last->next = newStudent;
                last = newStudent;
            }
            return;
        }

        if (index == queueSize) {
            newStudent->next = first;
            first = newStudent;
            if (last == nullptr) {
                last = newStudent;
            }
            return;
        }

        int targetIndex = queueSize - index - 1;
        Student* current = first;
        for (int i = 0; i < targetIndex; i++) {
            current = current->next;
        }
        newStudent->next = current->next;
        current->next = newStudent;
    }

    Student* findIndex(int index) {
        int queueSize = size();

        if (index < 0 || index >= queueSize) {
            cout << "Index out of bounds" << endl;
            return nullptr;
        }

        int targetIndex = queueSize - index - 1;
        Student* current = first;

        for (int i = 0; i < targetIndex; i++) {
            current = current->next;
        }

        return current;
    }

    void display() {
        if (first == nullptr) {
            cout << "queue is empty." << endl;
            return;
        }

        cout << "last student: " << last->name << endl;

        Student* current = first;
        while (current != nullptr) {
            cout << current->name << " ";
            current = current->next;
        }

        cout << "\n" << "first student: " << first->name << endl;
        cout << "\n\n";
    }
};

///////////////////////////////////////////////////challange 1///////////////////////////////////////////////////////


///////////////////////////////////////////////////challange 2///////////////////////////////////////////////////////

struct Student2 {
    int id;
    string name;
    Student2* left = nullptr;
    Student2* right = nullptr;
};

struct BinarySearchTree {
    Student2* root = nullptr;

    void insert(Student2* newStudent) {
        if (root == nullptr) {
            root = newStudent;
            return;
        }

        Student2* current = root;
        Student2* parent = nullptr;

        while (true) {
            parent = current;
            if (newStudent->id < current->id) {
                current = current->left;
                if (current == nullptr) {
                    parent->left = newStudent;
                    return;
                }
            }
            else {
                current = current->right;
                if (current == nullptr) {
                    parent->right = newStudent;
                    return;
                }
            }
        }
    }

    Student2* find(Student2* student) {
        Student2* current = root;
        while (current != nullptr) {
            if (student->id == current->id) {
                return current;
            }
            else if (student->id < current->id) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return nullptr;
    }
};
///////////////////////////////////////////////////challange 2///////////////////////////////////////////////////////

int main() {



    int choice;

    cout << "select challenge to run (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        cout << "///////////////////////////////////////////////////challange 1///////////////////////////////////////////////////////" << endl;
        Queue studentQueue;

        studentQueue.enqueue(new Student{ "tantawy" });
        studentQueue.display();

        studentQueue.enqueue(new Student{ "Ghandy" }, 1);
        studentQueue.display();

        studentQueue.enqueue(new Student{ "mohamed" }, 1);
        studentQueue.display();

        studentQueue.enqueue(new Student{ "ehab" }, 2);

        studentQueue.display();
        studentQueue.enqueue(new Student{ "omar" }, 0);


        studentQueue.display();
        studentQueue.enqueue(new Student{ "sayed" }, 5);

        studentQueue.display();

        Student* foundStudent = studentQueue.findIndex(1);

        cout << foundStudent->name << endl;
    }
    else if (choice == 2) {
        cout << "///////////////////////////////////////////////////challange 2///////////////////////////////////////////////////////" << endl;







        BinarySearchTree bst;


        Student2 student1 = { 1, "omar" };
        Student2 student2 = { 2, "sayed" };
        Student2 student3 = { 5, "mohamed" };
        Student2 student4 = { 4, "osama" };
        Student2 student5 = { 10, "mustafa" };

        bst.insert(&student1);
        bst.insert(&student2);
        bst.insert(&student3);
        bst.insert(&student4);
        bst.insert(&student5);

        Student2* foundStudentBst = bst.find(&student3);

        cout << foundStudentBst->id << " " << foundStudentBst->name << endl;

    }
    return 0;
}