#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// هيكل لتخزين معلومات جهة الاتصال
struct Contact {
    string name;
    string phone;
    string email;
};

// دالة لعرض القائمة الرئيسية
void showMenu() {
    cout << "\n Contact Management System " << endl;
    cout << "1. Add Contact" << endl;
    cout << "2. View All Contacts" << endl;
    cout << "3. Search Contact" << endl;
    cout << "4. Delete Contact" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose an option: ";
}

// دالة لإضافة جهة اتصال جديدة
void addContact(vector<Contact>& contacts) {
    Contact newContact;
    
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, newContact.name);
    
    cout << "Enter phone: ";
    cin >> newContact.phone;
    
    cout << "Enter email: ";
    cin >> newContact.email;
    
    contacts.push_back(newContact);
    
    // حفظ البيانات في الملف
    ofstream outFile("contacts.txt", ios::app);
    if (outFile.is_open()) {
        outFile << newContact.name << "," << newContact.phone << "," << newContact.email << endl;
        outFile.close();
        cout << "Contact added successfully!" << endl;
    } else {
        cout << "Error opening file for writing!" << endl;
    }
}

// دالة لعرض كل جهات الاتصال
void viewContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts found." << endl;
        return;
    }
    
    cout << "\n--- Contact List ---" << endl;
    for (size_t i = 0; i < contacts.size(); i++) {
        cout << i + 1 << ". Name: " << contacts[i].name 
             << " | Phone: " << contacts[i].phone 
             << " | Email: " << contacts[i].email << endl;
    }
}

// دالة للبحث عن جهة اتصال بالاسم
void searchContact(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts to search in." << endl;
        return;
    }
    
    string searchName;
    cout << "Enter name to search: ";
    cin.ignore();
    getline(cin, searchName);
    
    bool found = false;
    for (size_t i = 0; i < contacts.size(); i++) {
        if (contacts[i].name == searchName) {
            cout << "\nFound!" << endl;
            cout << "Name: " << contacts[i].name << endl;
            cout << "Phone: " << contacts[i].phone << endl;
            cout << "Email: " << contacts[i].email << endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "No matching contact found." << endl;
    }
}

// دالة لحذف جهة اتصال
void deleteContact(vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts to delete." << endl;
        return;
    }
    
    string targetName;
    cout << "Enter name to delete: ";
    cin.ignore();
    getline(cin, targetName);
    
    bool deleted = false;
    for (auto it = contacts.begin(); it != contacts.end(); ++it) {
        if (it->name == targetName) {
            contacts.erase(it);
            cout << "Contact deleted successfully." << endl;
            deleted = true;
            break;
        }
    }
    
    if (!deleted) {
        cout << "Contact not found." << endl;
    }
}

int main() {
    vector<Contact> contacts;
    int choice;
    
    // محاولة قراءة البيانات القديمة من الملف عند بداية التشغيل
    ifstream inFile("contacts.txt");
    string line;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            // قراءة بسيطة للبيانات المخزنة
            size_t p1 = line.find(',');
            size_t p2 = line.find(',', p1 + 1);
            if (p1 != string::npos && p2 != string::npos) {
                Contact c;
                c.name = line.substr(0, p1);
                c.phone = line.substr(p1 + 1, p2 - p1 - 1);
                c.email = line.substr(p2 + 1);
                contacts.push_back(c);
            }
        }
        inFile.close();
    }
    
    do {
        showMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                addContact(contacts);
                break;
            case 2:
                viewContacts(contacts);
                break;
            case 3:
                searchContact(contacts);
                break;
            case 4:
                deleteContact(contacts);
                break;
            case 5:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);
    
    return 0;
}
