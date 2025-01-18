#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;
struct Doctor {
    int id;
    string name;
    string attendance[7]; 
    string category;
    int pay;
    int no_of_days;
    Doctor* next; 
    Doctor(int doctorId, string doctorName, string category) {
        id = doctorId;
        name = doctorName;
        this->category = category;
        for (int i = 0; i < 7; i++) {
            attendance[i] = "Not Marked";
        }
        next = nullptr;
        pay=0;
        no_of_days=0;
    }
};
// Class Doctor Attendance System
class DoctorAttendanceSystem {
private:
    Doctor* head; 
public:
    DoctorAttendanceSystem() : head(nullptr) {}
    // Add a doctor to the system
    void addDoctor(int id, const string& name, const string& category) {
        //To Check if the doctor ID already exists
        Doctor* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) {
                cout << "Doctor with ID " << id << " already exists." << endl;
                return;
            }
            temp = temp->next;
        }
        // Add the new doctor
        Doctor* newDoctor = new Doctor(id, name, category);
        newDoctor->next = head;
        head = newDoctor;
        cout << "Doctor " << name << " added successfully with ID: " << id << " Category: " << category << endl;
    }
     void removeDoctor(const string& name) {
        if (!head) {
           cout << "List is empty. Cannot remove doctor.\n";
            return;
        }
        // Check if  head node is to remove
        if (head->name == name) {
            Doctor* toDelete = head;
            head = head->next;
            delete toDelete;
          cout << "Doctor " << name << " removed from the list.\n";
            return;
        }
        // Traversal
        Doctor* temp = head;
        while (temp->next && temp->next->name != name) {
            temp = temp->next;}
        if (temp->next) {
            Doctor* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            cout << "Doctor " << name << " removed from the list.\n";
        } else {
            cout << "Doctor " << name << " not found in the list.\n";
        }    }

   
    void markAttendance(int id, const string& day, const string& status) {
        Doctor* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) {
                int dayIndex = getDayIndex(day);
                if (dayIndex != -1) {
                    temp->attendance[dayIndex] = status;
                    cout << "Attendance marked for Doctor ID " << id << " on " << day << ": " << status << endl;
                    if (status=="present"){ temp->no_of_days++;      
                    }
                } else {
                    cout << "Invalid day provided." << endl;
                }
                return;
            }
            temp = temp->next;
        }
        cout << "Doctor ID " << id << " not found." << endl;
    }
int calculatepay(int id) {
    Doctor* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            if (temp->category == "surgical") {
                temp->pay = 10000 * temp->no_of_days;
            } else if (temp->category == "general") {
                temp->pay = 7000 * temp->no_of_days;
            } else {
                cout << "Invalid category for Doctor ID " << id << "." << endl;
                return -1; 
            }
            return temp->pay;  }
        temp = temp->next;   }
    cout << "Doctor ID " << id << " not found." << endl;
    return -1;  
}
    void viewAttendance(int id) {
        Doctor* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) {
                cout << "Attendance for " << temp->name << " (ID: " << id << "):" << endl;
                string days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
                for (int i = 0; i < 7; i++) {
                    cout << days[i] << ": " << temp->attendance[i] << endl;
                }
                return;
            }
            temp = temp->next;
        }
        cout << "Doctor ID " << id << " not found." << endl;
    }
    // View attendance for all doctors
   void viewAllAttendance() {
        Doctor* temp = head;
        if (!temp) {
            cout << "No doctors found." << endl;
            return;
        }
        while (temp != nullptr) {
            cout << "Doctor ID: " << temp->id << ", Name: " << temp->name << endl;
            string days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
            for (int i = 0; i < 7; i++) {
                cout << "  " << days[i] << ": " << temp->attendance[i] << endl;
            }
            cout << "-----------------------------" << endl;
            temp = temp->next;
        }
    }
~DoctorAttendanceSystem() {
        while (head) {
            Doctor* temp = head;
            head = head->next;
            delete temp;
        }
    }
     Doctor* getDoctor(int id) {
        Doctor* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
//private:
    // Helper function to get the index of a day
    int getDayIndex(const string& day) {
        string days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        for (int i = 0; i < 7; i++) {
            if (days[i] == day) {
                return i;
            }
        }
        return -1; // Invalid day
    }
};

struct Patient {
    int id;
    string name;
    int age;
    string disease;
    Patient* next;

    Patient(int patientId, string patientName, int patientAge, string patientDisease)
        : id(patientId), name(patientName), age(patientAge), disease(patientDisease), next(nullptr) {}
};

// Class to manage the linked list
class PatientManagementSystem {
private:
    Patient* head;
    int nextId;

public:
    PatientManagementSystem() : head(nullptr), nextId(1) {}

// Adding  patient 
    void addPatient(const string& name, int age, const string& disease) {
        Patient* newPatient = new Patient(nextId++, name, age, disease);
        if (!head) {
            head = newPatient;
        } else {
            Patient* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newPatient;
        }
        cout << "Patient added successfully! Patient ID: " << newPatient->id << endl;
    }
// Discharge patient through id
    void dischargePatient(int id) {
        if (!head) {
            cout << "No patients in the system.\n";
            return;}
 // Check if  head node is  remove
        if (head->id == id) {
            Patient* toDelete = head;
            head = head->next;
            delete toDelete;
            cout << "Patient with ID " << id << " has been discharged.\n";
            return;}
   // Traversal
        Patient* temp = head;
        while (temp->next && temp->next->id != id) {
            temp = temp->next;}
        if (temp->next) {
            Patient* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            cout << "Patient with ID " << id << " has been discharged.\n";
        } else {
            cout << "Patient with ID " << id << " not found.\n";
        }
    }

    // View all patients
    void viewPatients() const {
        if (!head) {
            cout << "No patients in the system.\n";
            return;
        }
        Patient* temp = head;
        cout << "Patient Details:\n";
        while (temp) {
            cout << "ID: " << temp->id
                 << ", Name: " << temp->name
                 << ", Age: " << temp->age
                 << ", Disease: " << temp->disease << endl;
            temp = temp->next;
        }
    }

    // Search for a patient by ID
    void searchPatient(int id) const {
        Patient* temp = head;
        while (temp) {
            if (temp->id == id) {
                cout << "Patient Found:\n";
                cout << "ID: " << temp->id
                     << ", Name: " << temp->name
                     << ", Age: " << temp->age
                     << ", Disease: " << temp->disease << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Patient with ID " << id << " not found.\n";
    }

    // Edit patient details
    void editPatient(int id) {
        Patient* temp = head;
        while (temp) {
            if (temp->id == id) {
                cout << "Editing details for Patient ID: " << id << endl;
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, temp->name);
                cout << "Enter new age: ";
                cin >> temp->age;
                cout << "Enter new disease: ";
                cin.ignore();
                getline(cin, temp->disease);
                cout << "Patient details updated successfully.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Patient with ID " << id << " not found.\n";
    }
Patient* getPatient(int id) {
        Patient* temp = head;
        while (temp) {
            if (temp->id == id) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Destructor to free memory
    ~PatientManagementSystem() {
        while (head) {
            Patient* temp = head;
            head = head->next;
            delete temp;
        }
    }
};




// Struct to represent an appointment
struct Appointment {
    int doctorId;
    int patientId;
    string day;
    string time;

    Appointment(int docId, int patId, const string& appointmentDay, const string& appointmentTime)
        : doctorId(docId), patientId(patId), day(appointmentDay), time(appointmentTime) {}
};

// Class to manage appointments
class AppointmentSystem {
private:
    unordered_map<int, vector<Appointment>> doctorAppointments; // Keyed by doctor ID
    unordered_map<int, vector<Appointment>> patientAppointments; // Keyed by patient ID

public:
    // Add an appointment
    void addAppointment(int doctorId, int patientId, const string& day, const string& time,
                        DoctorAttendanceSystem& docSys, PatientManagementSystem& patSys) {
        // Validate doctor and patient
        Doctor* doctor = docSys.getDoctor(doctorId);
        Patient* patient = patSys.getPatient(patientId);

        if (!doctor) {
            cout << "Doctor with ID " << doctorId << " not found.\n";
            return;
        }

        if (!patient) {
            cout << "Patient with ID " << patientId << " not found.\n";
            return;
        }

        // Check doctor's attendance for the day
     //   int dayIndex = docSys.getDayIndex(day);
     //   if (dayIndex == -1 || doctor->attendance[dayIndex] != "present") {
     //       cout << "Doctor " << doctor->name << " is not available on " << day << ".\n";
      //      return;
      //  }

        // Schedule the appointment
        Appointment appointment(doctorId, patientId, day, time);
        doctorAppointments[doctorId].push_back(appointment);
        patientAppointments[patientId].push_back(appointment);

        cout << "Appointment scheduled: Doctor " << doctor->name << " with Patient " << patient->name
             << " on " << day << " at " << time << ".\n";
             return ;
    }

    // View appointments by doctor
    void viewAppointmentsByDoctor(int doctorId, DoctorAttendanceSystem& docSys) {
        Doctor* doctor = docSys.getDoctor(doctorId);
        if (!doctor) {
            cout << "Doctor with ID " << doctorId << " not found.\n";
            return;
        }

        cout << "--- Appointments for Doctor " << doctor->name << " ---\n";
        if (doctorAppointments[doctorId].empty()) {
            cout << "No appointments scheduled.\n";
            return;
        }

        for (const auto& appointment : doctorAppointments[doctorId]) {
            cout << "Patient ID: " << appointment.patientId << ", Day: " << appointment.day
                 << ", Time: " << appointment.time << "\n";
        }
    }
    // View appointments by patient
   void viewAppointmentsByPatient(int patientId, PatientManagementSystem& patSys) {
        Patient* patient = patSys.getPatient(patientId);
        if (!patient) {
            cout << "Patient with ID " << patientId << " not found.\n";
            return;
        }

        cout << "--- Appointments for Patient " << patient->name << " ---\n";
        if (patientAppointments[patientId].empty()) {
            cout << "No appointments scheduled.\n";
            return;
        }

        for (const auto& appointment : patientAppointments[patientId]) {
            cout << "Doctor ID: " << appointment.doctorId << ", Day: " << appointment.day
                 << ", Time: " << appointment.time << "\n";
        }
    }

    // Cancel an appointment
    void cancelAppointment(int doctorId, int patientId) {
        auto& docApps = doctorAppointments[doctorId];
        auto& patApps = patientAppointments[patientId];

        // Remove from doctor's appointments
        docApps.erase(remove_if(docApps.begin(), docApps.end(),
                                [patientId](const Appointment& app) { return app.patientId == patientId; }),
                      docApps.end());

        // Remove from patient's appointments
        patApps.erase(remove_if(patApps.begin(), patApps.end(),
                                [doctorId](const Appointment& app) { return app.doctorId == doctorId; }),
                      patApps.end());

        cout << "Appointment between Doctor ID " << doctorId << " and Patient ID " << patientId
             << " has been canceled.\n";
    }
};


// Main function
int main() {
    PatientManagementSystem system2;
    AppointmentSystem appointmentSystem;
    DoctorAttendanceSystem system1;
    
	start:
    cout << "Enter 1 for Doctor Management and 2 for patient, 3 for appiontment 4 for exit.\n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        int cho;
        int id;
        string name, category;

        while (true) {
            cout << "\n--- Doctor Management System ---\n";
            cout << "1. Add doctor\n";
            cout << "2. Mark Attendance\n";
            cout << "3. View Attendance\n";
            cout << "4. View All Attendances\n";
            cout << "5. Calulate Pay\n";
            cout << "6. Exit\n";
            cout << "Enter your choice: ";
            cin >> cho;

            switch (cho) {
            case 1:{
                    cout << "Enter name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter ID: ";
                    cin >> id;
                    cout << "Enter category: ";
                    cin.ignore();
                    getline(cin, category);
                    system1.addDoctor(id, name, category);
                        break;}

                case 2:
                  {  string day, status;
                    cout << "Enter Doctor ID to mark attendance: ";
                    cin >> id;
                    cout << "Enter Day: ";
                    cin >> day;
                    cout << "Enter Status: ";
                    cin >> status;
                    system1.markAttendance(id, day, status);
                    break;}

                case 3:
                   { cout << "Enter the Doctor ID to view attendance: ";
                    cin >> id;
                    system1.viewAttendance(id);
                    break;}

                case 4:
                    {system1.viewAllAttendance();
                    break;}
                case 5:
                {
                    cout<<"Enter id to calculate pay"<<endl;
                    cin>>id;
                    cout<<system1.calculatepay(id);
                    break;
                }
                case 6:
                    cout << "Exiting\n";
                   // break;
                    goto start;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }
   else  if (choice==2){
      int cho;
      int id, age;
    string name, disease;
    while (true) {
        cout << "\n--- Patient Management System ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Discharge Patient\n";
        cout << "3. View All Patients\n";
        cout << "4. Search Patient\n";
        cout << "5. Edit Patient Details\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> cho;

        switch (cho) {
        case 1:
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter disease: ";
            cin.ignore();
            getline(cin, disease);
            system2.addPatient(name, age, disease);
            break;

        case 2:
            cout << "Enter Patient ID to discharge: ";
            cin >> id;
            system2.dischargePatient(id);
            break;

        case 3:
            system2.viewPatients();
            break;

        case 4:
            cout << "Enter Patient ID to search: ";
            cin >> id;
            system2.searchPatient(id);
            break;

        case 5:
            cout << "Enter Patient ID to edit: ";
            cin >> id;
            system2.editPatient(id);
            break;

        case 6:
            cout << "Exiting ";
            goto start;
            return 0;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
else if (choice==3){   
   int doctorId, patientId;
            string day, time;
            while (true) {
        cout << "\n--- Appointment System ---\n";
        cout << "1. Make an Appointmnet\n";
        cout << "2. Cancel Appointment\n";
        cout << "3. View All doctors appointment\n";
        cout << "4. View all patient appointment\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        int cho;
        cin >> cho;
        switch (cho) {
        case 1:
            cout << "Enter Doctor ID: ";
            cin >> doctorId;
            cout << "Enter Patient ID: ";
            cin >> patientId;
            cout << "Enter Appointment Day: ";
            cin >> day;
            cout << "Enter Appointment Time: ";
            cin >> time;
            appointmentSystem.addAppointment(doctorId, patientId, day, time, system1, system2);
            break;
			
            case 2:
            cout << "Enter Doctor ID: ";
            cin >> doctorId;
            cout << "Enter Patient ID: ";
            cin >> patientId;
			appointmentSystem.cancelAppointment(doctorId, patientId);
			cout<<"Your appointment is being canceled."<<endl;
			break;
			
			case 3:
			 cout << "Enter Doctor ID: ";
            cin >> doctorId;
				appointmentSystem.viewAppointmentsByDoctor(doctorId,  system1);
				break;
			case 4:

			 cout << "Enter Patient ID: ";
            cin >> patientId;
            appointmentSystem.viewAppointmentsByPatient(patientId, system2);
            break;
            case 5:
            cout << "Exiting ";
            goto start;
            return 0;
        } } }
		else if (choice == 4) {
            cout << "------------------------EXITING PROGRAM--------------------------- " << endl;
          // break;
           
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    

    return 0;
}
