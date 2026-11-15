#include <iostream>
#include <string>
using namespace std;
// PHASE 1: COURSE REGISTRATION SYSTEM
// Concepts used:structures,arrays,functions,loops,conditions and linear search.
const int MAX_STUDENTS=100;
const int MAX_COURSES=50;
const int MAX_REGISTRATIONS=200;
struct Student {
    int id;
    string name;
    string department;
};
struct Course {
    int id;
    string name;
    int creditHours;
};
struct Registration {
    int studentId;
    int courseId;
};
Student students[MAX_STUDENTS];
Course courses[MAX_COURSES];
Registration registrations[MAX_REGISTRATIONS];
int studentCount=0;
int courseCount=0;
int registrationCount=0;
//Search for a student using linear search.
//Returns the array index if found; otherwise returns -1.
int findStudent(int id) {
    for (int i=0;i<studentCount;i++) {
        if (students[i].id==id) {
            return i;
        }
    }
    return -1;
}
//Search for a course using linear search.
int findCourse(int id) {
    for (int i=0;i<courseCount;i++) {
        if (courses[i].id==id) {
            return i;
        }
    }
    return -1;
}
bool alreadyRegistered(int studentId,int courseId) {
    for (int i=0;i<registrationCount;i++){
        if (registrations[i].studentId == studentId &&
            registrations[i].courseId == courseId) {
            return true;
        }
    }
    return false;
}
void addStudent() {
    if (studentCount == MAX_STUDENTS) {
        cout << "Student record limit reached.\n";
        return;
    }
    int id;
    cout<<"Enter student ID: ";
    cin>>id;
    if (findStudent(id) != -1) {
        cout<<"This student ID already exists.\n";
        return;
    }
    students[studentCount].id = id;
    cout<<"Enter student name: ";
    getline(cin>>ws,students[studentCount].name);
    cout<<"Enter department: ";
    getline(cin,students[studentCount].department);
    studentCount++;
    cout<<"Student added successfully.\n";
}
void displayStudents() {
    if (studentCount==0) {
        cout<<"No students have been added yet.\n";
        return;
    }
    cout<<"\n--- STUDENT LIST ---\n";
    for(int i = 0; i < studentCount; i++) {
        cout <<"ID: " << students[i].id
             <<" | Name: " << students[i].name
             <<" | Department: " << students[i].department << '\n';
    }
}
void searchStudent() {
    int id;
    cout<<"Enter student ID: ";
    cin>>id;
    int index=findStudent(id);
    if(index == -1) {
        cout<<"Student not found.\n";
    } else {
        cout<<"Student found!\n";
        cout<<"Name: " << students[index].name
             <<"\nDepartment: "<<students[index].department<<'\n';
    }
}
void updateStudent() {
    int id;
    cout << "Enter student ID to update: ";
    cin >> id;

    int index = findStudent(id);

    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Enter updated name: ";
    getline(cin >> ws, students[index].name);

    cout << "Enter updated department: ";
    getline(cin, students[index].department);

    cout << "Student information updated.\n";
}

void deleteStudent() {
    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;

    int index = findStudent(id);

    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    // Shift later records one position to the left.
    for (int i = index; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--;

    // Remove registrations belonging to the deleted student.
    for (int i = 0; i < registrationCount; ) {
        if (registrations[i].studentId == id) {
            for (int j = i; j < registrationCount - 1; j++) {
                registrations[j] = registrations[j + 1];
            }
            registrationCount--;
        } else {
            i++;
        }
    }

    cout << "Student and related registrations deleted.\n";
}

void addCourse() {
    if (courseCount == MAX_COURSES) {
        cout << "Course record limit reached.\n";
        return;
    }

    int id;
    cout << "Enter course ID: ";
    cin >> id;

    if (findCourse(id) != -1) {
        cout << "This course ID already exists.\n";
        return;
    }

    courses[courseCount].id = id;

    cout << "Enter course name: ";
    getline(cin >> ws, courses[courseCount].name);

    cout << "Enter credit hours: ";
    cin >> courses[courseCount].creditHours;

    if (courses[courseCount].creditHours <= 0) {
        cout << "Credit hours must be greater than zero. Course not added.\n";
        return;
    }

    courseCount++;
    cout << "Course added successfully.\n";
}

void displayCourses() {
    if (courseCount == 0) {
        cout << "No courses have been added yet.\n";
        return;
    }

    cout << "\n--- COURSE LIST ---\n";
    for (int i = 0; i < courseCount; i++) {
        cout << "Course ID: " << courses[i].id
             << " | Name: " << courses[i].name
             << " | Credit Hours: " << courses[i].creditHours << '\n';
    }
}

void registerCourse() {
    if (registrationCount == MAX_REGISTRATIONS) {
        cout << "Registration record limit reached.\n";
        return;
    }

    int studentId, courseId;

    cout << "Enter student ID: ";
    cin >> studentId;

    if (findStudent(studentId) == -1) {
        cout << "Student does not exist. Add the student first.\n";
        return;
    }

    cout << "Enter course ID: ";
    cin >> courseId;

    if (findCourse(courseId) == -1) {
        cout << "Course does not exist. Add the course first.\n";
        return;
    }

    if (alreadyRegistered(studentId, courseId)) {
        cout << "Student is already registered in this course.\n";
        return;
    }

    registrations[registrationCount].studentId = studentId;
    registrations[registrationCount].courseId = courseId;
    registrationCount++;

    cout << "Course registration completed successfully.\n";
}

void dropCourse() {
    int studentId, courseId;

    cout << "Enter student ID: ";
    cin >> studentId;

    cout << "Enter course ID to drop: ";
    cin >> courseId;

    for (int i = 0; i < registrationCount; i++) {
        if (registrations[i].studentId == studentId &&
            registrations[i].courseId == courseId) {

            for (int j = i; j < registrationCount - 1; j++) {
                registrations[j] = registrations[j + 1];
            }

            registrationCount--;
            cout << "Course registration dropped successfully.\n";
            return;
        }
    }

    cout << "Registration record not found.\n";
}
void displayRegistrations() {
    if (registrationCount == 0) {
        cout << "No course registrations found.\n";
        return;
    }
    cout << "\n--- COURSE REGISTRATIONS ---\n";
    for (int i = 0; i < registrationCount; i++) {
        int sIndex = findStudent(registrations[i].studentId);
        int cIndex = findCourse(registrations[i].courseId);
        cout << "Student ID: " << registrations[i].studentId;
        if (sIndex != -1) {
            cout << " | Student: " << students[sIndex].name;
        }
        cout << " | Course ID: " << registrations[i].courseId;
        if (cIndex != -1) {
            cout << " | Course: " << courses[cIndex].name;
        }
        cout << '\n';
    }
}
void showMenu() {
    cout << "\n===== COURSE REGISTRATION SYSTEM - PHASE 1 =====\n";
    cout << "1. Add Student\n";
    cout << "2. Display Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Add Course\n";
    cout << "7. Display Courses\n";
    cout << "8. Register Student in a Course\n";
    cout << "9. Drop Course Registration\n";
    cout << "10. Display Registrations\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}
int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                addCourse();
                break;
            case 7:
                displayCourses();
                break;
            case 8:
                registerCourse();
                break;
            case 9:
                dropCourse();
                break;
            case 10:
                displayRegistrations();
                break;
            case 0:
                cout << "Thank you for using the system!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
