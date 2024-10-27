#include <iostream>;
#include <vector>;
#include <string>;
#include <limits>;

using namespace std;


// vector<int> bubbleSort(vector<int> arr) {
//     for (int i = 0; i < arr.size(); i++)
//     {

//         for (int j = i + 1; j < arr.size(); j++)
//         {

//             if (arr[i] > arr[j])
//             {
//                 int temp = arr[i];
//                 arr[i] = arr[j];
//                 arr[j] = temp;
//             }
//         }
//     }

//     return arr;
// }

// vector<int> booleanSort(const vector<int>& arr, int maxValue) {

//     vector<bool> presence(maxValue + 1, false);


//     for (int num : arr) {
//         presence[num] = true;
//     }

//     vector<int> sortedArr;
//     for (int i = 0; i <= maxValue; i++) {
//         if (presence[i]) {
//             sortedArr.push_back(i);
//         }
//     }

//     return sortedArr;
// }

// vector<int> insertionSort(vector<int> arr) {


//     for (int i = 1; i < arr.size(); i++) {
//         int key = arr[i];
//         int j = i - 1;

//         while (j >= 0 && arr[j] > key) {
//             arr[j + 1] = arr[j];
//             j = j - 1;
//         }
//         arr[j + 1] = key;
//     }
//     return arr;
// }

// int binarySearch(vector<int> arr, int n) {
//     int f = 0;
//     int l = arr.size() - 1;

//     while (f <= l) {
//         int mid = (f + l) / 2;
//         if (arr[mid] == n)
//         {
//             return mid;
//         }

//         if (arr[mid] > n) {
//             l = mid - 1;
//         }

//         if (arr[mid] < n) {
//             f = mid + 1;
//         }
//     }

//     return -1;
// }


// int binarySearchWithRecursion(vector<int> arr, int n, int left = 0, int right = -1) {

//     if (right == -1) {
//         right = arr.size() - 1;
//     }

//     if (left > right) {
//         return -1;
//     }

//     int mid = left + (right - left) / 2;


//     if (arr[mid] == n) {
//         return mid;
//     }



//     else if (arr[mid] > n) {
//         return binarySearchWithRecursion(arr, n, left, mid - 1);
//     }
//     else if (arr[mid] < n) {
//         return binarySearchWithRecursion(arr, n, mid + 1, right);
//     }
// }



struct Employee {
    int id;
    string name;
    Employee* next;
    Employee* prev;

    Employee(int empId, const string& empName) : id(empId), name(empName), next(nullptr), prev(nullptr) {}
};

void addEmployee(Employee*& head, int id, const string& name) {
    Employee* newEmployee = new Employee(id, name);
    newEmployee->next = head;
    newEmployee->prev = nullptr;

    if (head != nullptr) {
        head->prev = newEmployee;
    }

    head = newEmployee;
}

void displayEmployees(Employee* head) {
    Employee* temp = head;
    while (temp != nullptr) {
        cout << "ID: " << temp->id << ", Name: " << temp->name << endl;
        temp = temp->next;
    }
}

void findEmployee(Employee* head, int id) {
    Employee* current = head;
    while (current != nullptr) {
        if (current->id == id) {
            cout << "Found Employee - ID: " << current->id << ", Name: " << current->name << endl;
            return;
        }
        current = current->next;
    }
    cout << "Employee with ID " << id << " not found." << endl;
}

void updateEmployee(Employee*& head, int id, int newId, const string& newName) {
    Employee* current = head;
    while (current != nullptr) {
        if (current->id == id) {
            Employee* newEmployee = new Employee(newId, newName);
            newEmployee->next = current->next;
            newEmployee->prev = current->prev;

            if (current->prev != nullptr) {
                current->prev->next = newEmployee;
            }
            else {
                head = newEmployee;
            }

            if (current->next != nullptr) {
                current->next->prev = newEmployee;
            }

            delete current;
            cout << "Updated Employee - New ID: " << newEmployee->id << ", New Name: " << newEmployee->name << endl;
            return;
        }
        current = current->next;
    }
    cout << "Employee with ID " << id << " not found." << endl;
}

void deleteEmployee(Employee*& head, int id) {
    Employee* current = head;
    while (current != nullptr) {
        if (current->id == id) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            }
            else {
                head = current->next;
            }

            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }

            delete current;
            cout << "Employee with ID " << id << " deleted." << endl;
            return;
        }
        current = current->next;
    }
    cout << "Employee with ID " << id << " not found." << endl;
}

int sizeOfList(Employee* head) {
    int size = 0;
    Employee* current = head;
    while (current != nullptr) {
        size++;
        current = current->next;
    }
    return size;
}

Employee* mergeSortLinkedList(Employee* head) {
    if (!head || !head->next) {
        return head;
    }

    if (!head->next->next) {
        if (head->id > head->next->id) {
            Employee* second = head->next;
            head->next = nullptr;
            second->next = head;
            return second;
        }
        return head;
    }

    Employee* left = head;
    Employee* right = head->next;

    while (right && right->next) {
        left = left->next;
        right = right->next->next;
    }

    Employee* mid = left->next;
    left->next = nullptr;


    Employee* leftSorted = mergeSortLinkedList(head);
    Employee* rightSorted = mergeSortLinkedList(mid);

    Employee* sortedList = nullptr;

    if (leftSorted == nullptr) return rightSorted;
    if (rightSorted == nullptr) return leftSorted;

    if (leftSorted->id <= rightSorted->id) {
        sortedList = leftSorted;
        leftSorted = leftSorted->next;
    }
    else {
        sortedList = rightSorted;
        rightSorted = rightSorted->next;
    }

    Employee* current = sortedList;

    while (leftSorted && rightSorted) {
        if (leftSorted->id <= rightSorted->id) {
            current->next = leftSorted;
            leftSorted = leftSorted->next;
        }
        else {
            current->next = rightSorted;
            rightSorted = rightSorted->next;
        }
        current = current->next;
    }

    if (leftSorted) {
        current->next = leftSorted;
    }
    else {
        current->next = rightSorted;
    }

    return sortedList;

}



int main() {

    Employee* EmployeeList = nullptr;
    string name;
    int id;
    int newId;
    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Employees\n";
        cout << "3. Find Employee\n";
        cout << "4. Update Employee\n";
        cout << "5. Delete Employee\n";
        cout << "6. Size of the list\n";
        cout << "7. Sort list based on employee\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            cout << "Enter Employee ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Employee Name: ";
            getline(cin, name);
            addEmployee(EmployeeList, id, name);
            break;

        case 2:
            cout << "Employee List:" << endl;
            displayEmployees(EmployeeList);
            break;

        case 3:
            cout << "Enter Employee ID to find: ";
            cin >> id;
            findEmployee(EmployeeList, id);
            break;

        case 4:
            cout << "Enter Employee ID to update: ";
            cin >> id;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter new ID: ";
            cin >> newId;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter new name: ";
            getline(cin, name);
            updateEmployee(EmployeeList, id, newId, name);
            break;

        case 5:
            cout << "Enter Employee ID to delete: ";
            cin >> id;
            deleteEmployee(EmployeeList, id);
            break;

        case 6:
            cout << "Size of Employee List: " << sizeOfList(EmployeeList) << endl;
            break;

        case 7:
            EmployeeList = mergeSortLinkedList(EmployeeList);
            cout << "Employee List sorted by ID." << endl;
            break;

        case 8:
            cout << "Exiting program." << endl;
            while (EmployeeList != nullptr) {
                Employee* temp = EmployeeList;
                EmployeeList = EmployeeList->next;
                delete temp;
            }
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    // vector<int> arr = { 20, 25, 7, 9, 10, 2, 1 };


    // vector<int> arr1 = bubbleSort(arr);
    // vector<int> arr2 = insertionSort(arr);

    // cout << "bubble sort: " << endl;

    // for (int i = 0; i < arr1.size(); i++)
    // {

    //     cout << arr1[i] << " ";
    // }

    // cout << endl;

    // cout << "insertion sort" << endl;

    // for (int i = 0; i < arr2.size(); i++)
    // {
    //     cout << arr2[i] << " ";
    // }
    // cout << endl;

    // // numbers[iterArray] = vec1[iterOne] > vec2[iterTwo] ? vec1[iterOne++] : vec2[iterTwo++];




    // int index = binarySearchWithRecursion(arr1, 20);

    // cout << index << endl;

    return 0;
}