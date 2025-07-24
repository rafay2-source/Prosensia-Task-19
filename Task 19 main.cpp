#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Student {
    int rollNo;
    string name, dept;
    float cgpa;

public:
    void input() {
        cout << "Enter Roll No: "; cin >> rollNo;
        cout << "Enter Name: "; cin.ignore(); getline(cin, name);
        cout << "Enter Department: "; getline(cin, dept);
        cout << "Enter CGPA: "; cin >> cgpa;
    }

    void display() const {
        cout << rollNo << " | " << name << " | " << dept << " | " << cgpa << endl;
    }

    int getRollNo() const { return rollNo; }

    float getCGPA() const { return cgpa; }

    void update() {
        cout << "Update Name: "; cin.ignore(); getline(cin, name);
        cout << "Update Department: "; getline(cin, dept);
        cout << "Update CGPA: "; cin >> cgpa;
    }

    void writeToFile(ofstream& fout) const {
        fout << rollNo << '\n' << name << '\n' << dept << '\n' << cgpa << '\n';
    }

    void readFromFile(ifstream& fin) {
        fin >> rollNo; fin.ignore();
        getline(fin, name);
        getline(fin, dept);
        fin >> cgpa; fin.ignore();
    }
};

void addStudent() {
    ofstream fout("students.txt", ios::app);
    Student s;
    s.input();
    s.writeToFile(fout);
    fout.close();
}

void viewAll() {
    ifstream fin("students.txt");
    if (!fin) { cout << "No file found.\n"; return; }

    Student s;
    while (fin.peek() != EOF) {
        s.readFromFile(fin);
        s.display();
    }
    fin.close();
}

void searchStudent(int rno) {
    ifstream fin("students.txt");
    Student s;
    bool found = false;
    while (fin.peek() != EOF) {
        s.readFromFile(fin);
        if (s.getRollNo() == rno) {
            cout << "Found:\n"; s.display(); found = true;
        }
    }
    if (!found) cout << "Record not found.\n";
    fin.close();
}

void updateStudent(int rno) {
    ifstream fin("students.txt");
    ofstream fout("temp.txt");
    Student s;
    bool updated = false;

    while (fin.peek() != EOF) {
        s.readFromFile(fin);
        if (s.getRollNo() == rno) {
            cout << "Old Data:\n"; s.display();
            s.update(); updated = true;
        }
        s.writeToFile(fout);
    }
    fin.close(); fout.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (updated) cout << "Record Updated.\n";
    else cout << "Record not found.\n";
}

void deleteStudent(int rno) {
    ifstream fin("students.txt");
    ofstream fout("temp.txt");
    Student s;
    bool deleted = false;

    while (fin.peek() != EOF) {
        s.readFromFile(fin);
        if (s.getRollNo() != rno)
            s.writeToFile(fout);
        else
            deleted = true;
    }
    fin.close(); fout.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (deleted) cout << "Record Deleted.\n";
    else cout << "Record not found.\n";
}

int main() {
    int choice, roll;
    while (true) {
        cout << "\n1.Add 2.View All 3.Search 4.Update 5.Delete 6.Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewAll(); break;
            case 3: cout << "Enter Roll No: "; cin >> roll; searchStudent(roll); break;
            case 4: cout << "Enter Roll No: "; cin >> roll; updateStudent(roll); break;
            case 5: cout << "Enter Roll No: "; cin >> roll; deleteStudent(roll); break;
            case 6: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
