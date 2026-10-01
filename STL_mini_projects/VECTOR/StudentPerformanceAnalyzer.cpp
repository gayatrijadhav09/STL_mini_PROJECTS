#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    float marks;
};

void addStudent(vector<Student>& students) {
    Student s;

    cout << "\nEnter Roll No: ";
    cin >> s.rollNo;

    cout << "Enter Name: ";
    cin >> s.name;

    cout << "Enter Marks: ";
    cin >> s.marks;

    students.push_back(s);

    cout << "\nStudent added successfully!\n";
}

void displayStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "\nNo student records found.\n";
        return;
    }

    cout << "\n----- Student Records -----\n";

    for (int i = 0; i < students.size(); i++) {
        cout << "\nRoll No : " << students[i].rollNo;
        cout << "\nName    : " << students[i].name;
        cout << "\nMarks   : " << students[i].marks;
        cout << "\n---------------------------\n";
    }
}

void searchStudent(const vector<Student>& students) {
    int rollNo;

    cout << "\nEnter Roll No to search: ";
    cin >> rollNo;

    for (int i = 0; i < students.size(); i++) {
        if (students[i].rollNo == rollNo) {
            cout << "\nStudent Found!\n";
            cout << "Roll No : " << students[i].rollNo << endl;
            cout << "Name    : " << students[i].name << endl;
            cout << "Marks   : " << students[i].marks << endl;
            return;
        }
    }

    cout << "\nStudent not found.\n";
}

void updateStudent(vector<Student>& students) {
    int rollNo;

    cout << "\nEnter Roll No to update: ";
    cin >> rollNo;

    for (int i = 0; i < students.size(); i++) {
        if (students[i].rollNo == rollNo) {
            cout << "Enter new name: ";
            cin >> students[i].name;

            cout << "Enter new marks: ";
            cin >> students[i].marks;

            cout << "\nStudent updated successfully!\n";
            return;
        }
    }

    cout << "\nStudent not found.\n";
}

void deleteStudent(vector<Student>& students) {
    int rollNo;

    cout << "\nEnter Roll No to delete: ";
    cin >> rollNo;

    for (int i = 0; i < students.size(); i++) {
        if (students[i].rollNo == rollNo) {
            students.erase(students.begin() + i);

            cout << "\nStudent deleted successfully!\n";
            return;
        }
    }

    cout << "\nStudent not found.\n";
}

void findTopper(const vector<Student>& students) {
    if (students.empty()) {
        cout << "\nNo student records found.\n";
        return;
    }

    int topperIndex = 0;

    for (int i = 1; i < students.size(); i++) {
        if (students[i].marks > students[topperIndex].marks) {
            topperIndex = i;
        }
    }

    cout << "\n----- Topper -----\n";
    cout << "Roll No : " << students[topperIndex].rollNo << endl;
    cout << "Name    : " << students[topperIndex].name << endl;
    cout << "Marks   : " << students[topperIndex].marks << endl;
}

void classAverage(const vector<Student>& students) {
    if (students.empty()) {
        cout << "\nNo student records found.\n";
        return;
    }

    float total = 0;

    for (int i = 0; i < students.size(); i++) {
        total = total + students[i].marks;
    }

    float average = total / students.size();

    cout << "\nClass Average = " << average << endl;
}

int main() {
    vector<Student> students;

    int choice;

    do {
        cout << "\n===== STUDENT RECORD MANAGER =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Find Topper\n";
        cout << "7. Class Average\n";
        cout << "8. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students);
                break;

            case 2:
                displayStudents(students);
                break;

            case 3:
                searchStudent(students);
                break;

            case 4:
                updateStudent(students);
                break;

            case 5:
                deleteStudent(students);
                break;

            case 6:
                findTopper(students);
                break;

            case 7:
                classAverage(students);
                break;

            case 8:
                cout << "\nThank you!\n";
                break;

            default:
                cout << "\nInvalid choice.\n";
        }

    } while (choice != 8);

    return 0;
}
