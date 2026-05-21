#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits>
#include <vector>

using namespace std;

// ------------- MEDIA CLASS --------------
class Media {
public:
    string mediaID = "M101";
    string fileType;
    float fileSize;
    string filePath;

    void uploadMedia() { cout << "Media Uploaded!\n"; }
    void downloadMedia() { cout << "Media Downloaded!\n"; }
};

// --------------- MESSAGE CLASS ------------------
class Message {
public:
    string messageID;
    string content;
    string timestamp = "2026-04-15 21:44"; //sequence diagram representation
    string status = "Sent"; 
};

// --------------- CONTACT CLASS ----------------------
class Contact {
public:
    string name;
    string phone;
    bool isActive;
    bool isChatLocked;

    Contact() {
        isActive = false;
        isChatLocked = false;
    }
};

// --------------- GROUP STRUCT -----------------
struct Group {
    string name;
    vector<Contact> members;  
};

// --------------- STATUS CLASS --------------------
class Status {
private:
    string statuses[2];
    int count = 0;

public: //---upload status----------
    void uploadStatus() {
        if (count >= 2) {
            cout << "Only 2 statuses allowed!\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear the buffer
        cout << "Enter Status: ";
        getline(cin, statuses[count]);
        count++;
        cout << "Status uploaded!\n";
    }
// --------view status------------
    void viewStatus() {
        if (count == 0) {
            cout << "No status available.\n";
            return;
        }
        cout << "\n--- Status List ---\n";
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ". " << statuses[i] << endl;
        }
    }
//------------delete status-----------
    void deleteStatus() {
        if (count == 0) {
            cout << "No status to delete.\n";
            return;
        }
        viewStatus();
        int c;
        cout << "Enter number to delete: ";
        cin >> c;
        if (c < 1 || c > count) {
            cout << "Invalid choice! thankyou\n";
            return;
        }
        for (int i = c - 1; i < count - 1; i++) {
            statuses[i] = statuses[i + 1];
        }
        count--;
        cout << "Deleted!\n";
    }
};

// ----------- ADMIN CLASS -------- encapsulated (Monitoring Diagram)
class Admin {
private:
    string adminName = "";
    string password = "";
    string employeeID = "ADM-007"; 
    string role = "System Admin";  
    bool isRegistered = false;

public: //----------registerd admin--------
    void registerAdmin() {
        if (isRegistered) {
            cout << "Admin already registered!\n";
            return;
        }
        cout << "\n--- Admin Setup (Set your credentials) ---\n";
        cout << "Set Admin Name: ";
        cin >> adminName;
        cout << "Set Admin Password: ";
        cin >> password;
        isRegistered = true;
        cout << "Admin Registered Successfully! (Role: " << role << ")\n";
    }

    bool login() { //----------login--------------
        if (!isRegistered) {
            cout << "No admin found! Please register first.\n";
            return false;
        }
        string nameInput, passInput;
        cout << "\n--- Admin Login ---\n";
        cout << "Enter Name: ";
        cin >> nameInput;
        cout << "Enter Password: ";
        cin >> passInput;
        if (nameInput == adminName && passInput == password) {
            cout << "Login successful! ID: " << employeeID << "\n";
            return true;
        }
        cout << "!! You are not allowed to use the admin panel !!\n";
        return false;
    }
//------------other  encapsulated functions--------------
    void monitorActivity() { cout << "Monitoring activity...\n"; }
    void reportUser() { cout << "User reported with Evidence ID: R-99!\n"; }
    void manageDatabase() { cout << "Database Managed & Synced!\n"; }
};

// -------------- USER CLASS (Whatapp module)----------
class User {
public:
    string userID = "U-123";
    string bio = "Available";
    string profilePic = "img.png";
    Contact myContacts[10]; //---------------database logic (deployment diagram USE)--------------
    string globalPin = "1234";

    vector<Group> groups; //-------------multiple user add in multiple groups (cardinality)-----------------
    vector<Contact> archivedChats;

    bool isValidPhone(string p) {
        if (p.length() != 11 || p[0] != '0' || p[1] != '3') {
            cout << "!! Error: 11 digits starting with 03 !!\n";
            return false;
        }
        return true;
    }
//--------check contact------------
    bool hasContacts() {
        for (int i = 0; i < 10; i++) {
            if (myContacts[i].isActive) return true;
        }
        return false;
    }

    int findContactIndex(string search) {
        for (int i = 0; i < 10; i++) {
            if (myContacts[i].isActive && (myContacts[i].name == search || myContacts[i].phone == search)) {
                return i;
            }
        }
        return -1;
    }
//---------add contact manuall-------------
    void addContactManual(string preFilledPhone = "") {
        string n, p;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter Name: "; 
        getline(cin, n); 
        if (preFilledPhone == "") {
            while (true) {
                cout << "Enter Phone (03xxxxxxxxx): "; cin >> p;
                if (isValidPhone(p)) break;
            }
        } else {
            p = preFilledPhone;
            cout << "Using Phone: " << p << endl;
        }
        for (int i = 0; i < 10; i++) {
            if (!myContacts[i].isActive) {
                myContacts[i].name = n;
                myContacts[i].phone = p;
                myContacts[i].isActive = true;
                cout << "Contact Saved Successfully!\n";
                return;
            }
        }
        cout << "Memory Full!\n";
    }
           //---------Group--------------
    void manageGroups() {
        int choice;
        cout << "\n--- Group Management ---\n1. Create Group\n2. View Groups\n3. Add Members\n4. Remove Members\n5. Rename Group\n6. Delete Group\n7. Back\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            if (!hasContacts()) {
                cout << "No contact to add in group. Contact list is empty.\n";
                return;
            }
            showAll(); 
            Group g; //------struct object-----
            cout << "Enter Group Name: ";
            cin.ignore();
            getline(cin, g.name);
            while (true) {
                string name;
                cout << "Enter member name to add (0 to stop): ";
                getline(cin, name);
                if (name == "0") break;
                int idx = findContactIndex(name);
                if (idx != -1) {
                    bool alreadyExists = false;
                    for(int j=0; j < (int)g.members.size(); j++){
                        if(g.members[j].name == myContacts[idx].name){
                            alreadyExists = true;
                            break;
                        }
                    } //----------already exist------------
                    if(alreadyExists){
                        cout << "Already entered in the group!\n";
                    } else {
                        g.members.push_back(myContacts[idx]);
                        cout << "Member Added Successfully!\n";
                    }
                }
                else cout << "Contact not found!\n";
            }
            groups.push_back(g); //---------vector class used push back function to add data-------------
            cout << "Group Created!\n";
        } 
        else if (choice == 2) {//---------empty group---------------
            if (groups.empty()) { cout << "No groups found.\n"; return; }
            for (int i = 0; i < (int)groups.size(); i++) {
                cout << i + 1 << ". " << groups[i].name << " (" << groups[i].members.size() << " members)\n";
            }
        }
        else if (choice == 3 || choice == 4 || choice == 5) {//---------modify groups----------
            if (groups.empty()) { cout << "No groups to modify.\n"; return; }
            int gIdx;
            cout << "Select Group Number: "; cin >> gIdx;
            if (gIdx < 1 || gIdx > (int)groups.size()) return;
            gIdx--;
//---------add members in groups--------------
            if (choice == 3) {
                showAll();
                cin.ignore();
                string name; cout << "Member to add: "; getline(cin, name);
                int idx = findContactIndex(name);
                if (idx != -1) {
                    bool alreadyExists = false;
                    for(int j=0; j < (int)groups[gIdx].members.size(); j++){
                        if(groups[gIdx].members[j].name == myContacts[idx].name){
                            alreadyExists = true;
                            break;
                        }
                    }
                    if(alreadyExists){
                        cout << "Already entered in the group!\n";
                    } else {
                        groups[gIdx].members.push_back(myContacts[idx]);
                        cout << "Member Added Successfully!\n";
                    }
                }//----------delete members from groups--------------
            } else if (choice == 4) {
                cin.ignore();
                string name; cout << "Member to remove: "; getline(cin, name);
                for (auto it = groups[gIdx].members.begin(); it != groups[gIdx].members.end(); ++it) {
                    if (it->name == name) { 
                        groups[gIdx].members.erase(it); 
                        cout << "Member Removed!\n";
                        break; 
                    }
                }
            } else {
                cout << "New Group Name: "; cin.ignore(); getline(cin, groups[gIdx].name);
            }
        } //--------delete group--------------
        else if (choice == 6) { 
            if (groups.empty()) { cout << "No groups to delete.\n"; return; }
            for (int i = 0; i < (int)groups.size(); i++) cout << i + 1 << ". " << groups[i].name << endl;
            int gIdx;
            cout << "Select Group Number to Delete: "; cin >> gIdx;
            if (gIdx >= 1 && gIdx <= (int)groups.size()) {
                groups.erase(groups.begin() + (gIdx - 1));
                cout << "Group Deleted Successfully!\n";
            } else cout << "Invalid Selection!\n";
        }
    }
// ----------Archieve Chat-----------
    void archiveChat() {
        if (!hasContacts()) {
            cout << "No contact to archive. Contact list is empty.\n";
            return;
        }
        showAll(); 
        string name;
        cout << "Enter Name/Phone to Archive: ";
        cin.ignore();
        getline(cin, name);

        int idx = findContactIndex(name);
        if (idx != -1) {
            archivedChats.push_back(myContacts[idx]);
            myContacts[idx].isActive = false;
            cout << "Chat Archived Successfully!\n";
        } else {
            cout << "Contact not found!\n";
        }
    }
// -----Message class-----------
    void sendMessageLogic() {
        if (!hasContacts()) { cout << "No contacts available!\n"; return; }
        string search; 
        cout << "\nEnter Name or Phone: "; 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, search); 
        
        int idx = findContactIndex(search);
        if (idx == -1) {
            char choice; cout << "Not saved! Add contact? (y/n): "; cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                string pIn = (search.length() == 11) ? search : "";
                addContactManual(pIn);
                idx = findContactIndex(search); 
                if (idx == -1) return; 
            } else return;
        }
        if (myContacts[idx].isChatLocked) {
            string p; cout << "LOCKED. Enter PIN: "; cin >> p;
            if (p != globalPin) { 
                cout << "!! Wrong PIN !!\n"; 
                return; 
            }
        }
        //---------------------location----------------
        cout << "\n1. Text\n2. Media/File\n3. Location\nChoice: ";
        int t; cin >> t;
        if (t == 1) {//----------send message------------
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string msgContent; cout << "Type message: "; getline(cin, msgContent);
            Message m; m.content = msgContent;
            cout << "Message Sent at " << m.timestamp << " (Status: " << m.status << ")\n";
        } else if (t == 2) { //media is a weak entity and depends on send message logic
            Media med; med.uploadMedia();
        } else {
            cout << "Current Location Shared!\n";
        }
    }
//----------make call----------------(audio/video)
    void makeCall() {
        if (!hasContacts()) { cout << "No contacts!\n"; return; }
        string search; cout << "\nEnter Name or Phone: "; 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, search);

        int idx = findContactIndex(search);
        if (idx == -1) { cout << "Not found!\n"; return; }
        if (myContacts[idx].isChatLocked) {
            string p; cout << "LOCKED. Enter PIN: "; cin >> p;
            if (p != globalPin) {
                cout << "!! Wrong PIN !!\n"; 
                return;
            }
        }
        cout << "Calling " << myContacts[idx].name << "...\n1. Audio\n2. Video\nChoice: ";
        int c; cin >> c;
        cout << (c == 1 ? "Audio" : "Video") << " call started.\n";
    }
//---------manage chat lock-------------
    void manageChatLock() {
        if (!hasContacts()) {
            cout << "No contact available for chat lock!\n";
            return;
        }
        showAll();
        string search; cout << "\nEnter Name/Phone: "; 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, search);

        int idx = findContactIndex(search);
        if (idx == -1) { cout << "Contact not found!\n"; return; }
        string pin; cout << "Enter PIN: "; cin >> pin;
        if (pin != globalPin) {
            cout << "!! Wrong PIN !!\n"; 
            return;
        }
//-----------enable/disable chat lock----------------
        myContacts[idx].isChatLocked = !myContacts[idx].isChatLocked;
        if (myContacts[idx].isChatLocked)
            cout << "Chat lock enabled for " << myContacts[idx].name << endl;
        else
            cout << "Chat lock disabled for " << myContacts[idx].name << endl;
    }
// -----update contact--------
    void updateContact() {
        if (!hasContacts()) { // FIX: Empty list check
            cout << "List is empty!\n";
            return;
        }
        string p, newName; 
        cout << "Enter Phone or Name to update: "; 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, p);
        int idx = findContactIndex(p);
        if (idx != -1) { 
            cout << "New Name: "; 
            getline(cin, newName);
            myContacts[idx].name = newName; 
            cout << "Updated!\n"; 
        }
        else cout << "Not found!\n";
    }
//------delete contact--------
    void deleteContact() {
        if (!hasContacts()) { // FIX: Empty list check
            cout << "List is empty!\n";
            return;
        }
        string p; cout << "Enter Phone or Name to delete: "; 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, p);
        int idx = findContactIndex(p);
        if (idx != -1) { myContacts[idx].isActive = false; cout << "Deleted!\n"; }
        else cout << "Not found!\n";
    }
//-----show all contact-------
    void showAll() {
        cout << "\n--- Contacts List (Bio: " << bio << ") ---\n";
        bool empty = true;
        for (int i = 0; i < 10; i++) {
            if (myContacts[i].isActive) {
                empty = false;
                cout << "Name: " << myContacts[i].name << " | Phone: " << myContacts[i].phone;
                if (myContacts[i].isChatLocked) cout << " [LOCKED]";
                cout << endl;
            }
        }
        if (empty) cout << "List is empty.\n";
    }
};
//----------main function------
int main() { //deployemnt diagram use (USER devices)
    User u; Status s; Admin a;
    int mainChoice = 0;

    while (mainChoice != 5) {
        cout << "\n==== WHATSAPP MANAGEMENT SYSTEM ====\n";
        cout << "1. Contacts Module\n2. WhatsApp Modules\n3. Status Module\n4. Admin Panel\n5. Exit\nChoice: ";
        
        if (!(cin >> mainChoice)) { 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (mainChoice == 1) {
            int cChoice = 0;
            while (cChoice != 5) {
                cout << "\n-- Contacts --\n1.Add\n2.Update\n3.Delete\n4.View\n5.Back\nChoice: ";
                if (!(cin >> cChoice)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                if (cChoice == 1) u.addContactManual();
                else if (cChoice == 2) u.updateContact();
                else if (cChoice == 3) u.deleteContact();
                else if (cChoice == 4) u.showAll();
                else if (cChoice != 5) cout << "Invalid choice! thankyou\n";
            }
        }
        else if (mainChoice == 2) {
            int ch = 0;
            while (ch != 6) {
                cout << "\n1.Send Message\n2.Make Call\n3.Chat Lock\n4.Group Management\n5.Archive Chat\n6.Back\nChoice: ";
                if (!(cin >> ch)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                if (ch == 1) u.sendMessageLogic();
                else if (ch == 2) u.makeCall();
                else if (ch == 3) u.manageChatLock();
                else if (ch == 4) u.manageGroups();
                else if (ch == 5) u.archiveChat();
                else if (ch != 6) cout << "Invalid choice! thankyou\n";
            }
        }
        else if (mainChoice == 3) {
            int st = 0;
            while (st != 4) {
                cout << "\n1.Upload\n2.View\n3.Delete\n4.Back\nChoice: ";
                if (!(cin >> st)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                if (st == 1) s.uploadStatus();
                else if (st == 2) s.viewStatus();
                else if (st == 3) s.deleteStatus();
                else if (st != 4) cout << "Invalid choice! thankyou\n";
            }
        }
        else if (mainChoice == 4) {
            int adEntry = 0;
            while (adEntry != 3) {
                cout << "\n-- Admin Access --\n1. Set Credentials\n2. Login\n3. Back\nChoice: ";
                if (!(cin >> adEntry)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                if (adEntry == 1) a.registerAdmin();
                else if (adEntry == 2) {
                    if (a.login()) {
                        int ad = 0;
                        while (ad != 4) {
                            cout << "\n1.Monitor\n2.Report\n3.Manage DB\n4.Logout\nChoice: ";
                            if (!(cin >> ad)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                            if (ad == 1) a.monitorActivity();
                            else if (ad == 2) a.reportUser();
                            else if (ad == 3) a.manageDatabase();
                            else if (ad != 4) cout << "Invalid choice! thankyou\n";
                        }
                    }
                }
                else if (adEntry != 3) cout << "Invalid choice! thankyou\n";
            }
        }
    }
    return 0;
}