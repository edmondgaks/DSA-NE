#include <iostream>
#include <limits>
using namespace std;


// Class for Patients including linked lists
class PatientsLL {
public:
    int patient_id;
    string name;
    string dob;
    string gender;
    PatientsLL *next;

    PatientsLL(int patient_id, string name, string dob, string gender) {
        this->patient_id = patient_id;
        this->name = name;
        this->dob = dob;
        this->gender = gender;
        this->next = nullptr;
    }
};
// Class for Doctors including linked lists
class DoctorsLL {
public:
    int doctor_id;
    string name;
    string specialization;
    DoctorsLL *next;

    DoctorsLL(int doctor_id, string name, string specialization) {
        this->doctor_id = doctor_id;
        this->name = name;
        this->specialization = specialization;
        this->next = nullptr;
    }
};
// Class of Appointments including linked lists
class Appointments {
public:
    int appointment_id;
    int patient_id;
    int doctor_id;
    string appointment_date;
    Appointments *next;

    Appointments(int appointment_id, int patient_id, int doctor_id, string appointment_date) {
        this->appointment_id = appointment_id;
        this->patient_id = patient_id;
        this->doctor_id = doctor_id;
        this->appointment_date = appointment_date;
        this->next = nullptr;
    }
};

class HospitalManagementSystem {
public:
    PatientsLL *patients;
    DoctorsLL *doctors;
    Appointments *appointments;

    HospitalManagementSystem() {
        patients = nullptr;
        doctors = nullptr;
        appointments = nullptr;
    }
    // Not this class(HospitalManagementSystem)
    ~HospitalManagementSystem() {
        // First Delete all nodes in the patients linked list
        while (patients != nullptr) {
            PatientsLL* next = patients->next;
            delete patients;
            patients = next;
        }

        // Firstly Delete all nodes in the doctors linked list
        while (doctors != nullptr) {
            DoctorsLL* next = doctors->next;
            delete doctors;
            doctors = next;
        }

        // Firstly Delete all nodes in the appointments linked list
        while (appointments != nullptr) {
            Appointments* next = appointments->next;
            delete appointments;
            appointments = next;
        }
    }

    bool checkPatientId(int patient_id) const{
        PatientsLL *temp = patients;
        while (temp != nullptr) {
            if (temp->patient_id == patient_id) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    bool checkDoctorId(int doctor_id) const {
        DoctorsLL *temp = doctors;
        while (temp != nullptr) {
            if (temp->doctor_id == doctor_id) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    bool checkAppointmentId(int appointment_id) const {
        Appointments *temp = appointments;
        while (temp != nullptr) {
            if (temp->appointment_id == appointment_id) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void savePatient(int patient_id, string name, string dob, string gender) {
        PatientsLL *temp = patients;
        while (temp != nullptr) {
            if (temp->patient_id == patient_id) {
                throw invalid_argument("Patient ID already exists. Please enter a different ID.");
            }
            temp = temp->next;
        }
        auto *newPatient = new PatientsLL(patient_id, name, dob, gender);
        newPatient->next = patients;
        patients = newPatient;
    }

    void saveDoctor(int doctor_id, string name, string specialization) {
        DoctorsLL *temp = doctors;
        while (temp != nullptr) {
            if (temp->doctor_id == doctor_id) {
                throw invalid_argument("Doctor ID already exists. Please enter a different ID.");
            }
            temp = temp->next;
        }
        auto *newDoctor = new DoctorsLL(doctor_id, name, specialization);
        newDoctor->next = doctors;
        doctors = newDoctor;
    }

    void saveAppointment(int appointment_id, int patient_id, int doctor_id, string appointment_date) {
        Appointments *temp = appointments;
        while (temp != nullptr) {
            if (temp->appointment_id == appointment_id) {
                throw invalid_argument("Appointment ID already exists. Please enter a different ID.");
            }
            temp = temp->next;
        }
        Appointments *newAppointment = new Appointments(appointment_id, patient_id, doctor_id, appointment_date);
        newAppointment->next = appointments;
        appointments = newAppointment;
    }

    void checkAndSavePatient() {
        int patient_id;
        string name, dob, gender;
        cout << "PATIENT REGISTRATION \n";
        cout << "----------------------\n";
        while (true) {
            try {
                cout << "ID: ";
                cin >> patient_id;
                if (cin.fail()) {
                    throw invalid_argument("Invalid input for patient ID. Please enter a number.");
                }
                if(checkPatientId(patient_id)) {
                    throw invalid_argument("Patient ID already exists. Please enter a different ID.");
                }
                // Ignore or clear character from the buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "NAME: ";
                getline(cin, name);
                while (true) {
                    cout << "DoB: ";
                    getline(cin, dob);
                    break;
                }
                while (true) {
                    cout << "GENDER: ";
                    getline(cin, gender);
                    if (gender == "male" || gender == "female" || gender == "Male" || gender == "Female" || gender == "FEMALE" || gender == "MALE") {
                        break;
                    } else {
                        cout << "Invalid gender. Please use Male or Female.\n";
                    }
                }
                savePatient(patient_id, name, dob, gender);
                break; // break the loop if no exception was thrown
            } catch (const invalid_argument &e) {
                cout << "INVALID_ARGUMENT_EXCEPTION " << e.what() << endl;
                cin.clear(); // clear the error flag
                // Ignore or clear character from the buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    void checkAndSaveDoctor() {
        int doctor_id;
        string name, specialization;
        cout << "DOCTOR REGISTRATION" << endl;
        cout << "-------------------" << endl;
        while (true) {
            try {
                cout << "ID: ";
                cin >> doctor_id;
                if (cin.fail()) {
                    throw invalid_argument("Invalid input for doctor ID. Please enter a number.");
                }
                if(checkDoctorId(doctor_id)) {
                    throw invalid_argument("Doctor ID already exists. Please enter a unique ID.");
                }
                // Ignore or clear character from the buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "NAME: ";
                getline(cin, name);
                cout << "SPECIALIZATION: ";
                getline(cin, specialization);
                saveDoctor(doctor_id, name, specialization);
                break; // break the loop if no exception was thrown
            } catch (const invalid_argument &error) {
                cout << "INVALID EXCEPTION " << error.what() << endl;
                cin.clear();
                // Ignore or clear character from the buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    void checkAndSaveAppointment() {
        int appointment_id, patient_id, doctor_id;
        string appointment_date;
        cout << "APPOINTMENT REGISTRATION" << endl;
        cout << "------------------------" << endl;
        while (true) {
            try {
                cout << "ID: ";
                cin >> appointment_id;
                if (cin.fail()) {
                    throw invalid_argument("Invalid input for appointment ID. Please enter a number.");
                }
                if (checkAppointmentId(appointment_id)) {
                    throw invalid_argument("Appointment ID already exists. Please enter another ID.");
                }
                cout << "PATIENT ID: ";
                cin >> patient_id;
                if (cin.fail()) {
                    throw invalid_argument("Invalid input for patient ID. Please enter a number.");
                }
                // check if the patient ID exists
                if (!checkPatientId(patient_id)) {
                    throw invalid_argument("Patient ID does not exist. Please register the patient first.");
                }
                cout << "DOCTOR ID: ";
                cin >> doctor_id;
                if (cin.fail()) {
                    throw invalid_argument("Invalid input for doctor ID. Please enter a number.");
                }
                // Ignore or clear character from the buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                // check if the doctor ID exists
                if (!checkDoctorId(doctor_id)) {
                    throw invalid_argument("Doctor ID does not exist. Please register the doctor first.");
                }
                while (true) {
                    cout << "APPOINTMENT DATE: ";
                    getline(cin, appointment_date);
                    break;
                }
                saveAppointment(appointment_id, patient_id, doctor_id, appointment_date);
                break;
            } catch (const invalid_argument &error) {
                cout << "INVALID_ARGUMENT_EXCEPTION " << error.what() << endl;
                cin.clear();
                // Ignore or clear character from the buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    void displayPatients() const {
        PatientsLL *temp = patients;
        while (temp != nullptr) {
            cout << "Patient ID: " << temp->patient_id << ", Name: " << temp->name << ", DOB: " << temp->dob <<
                    ", Gender: " << temp->gender << endl;
            temp = temp->next;
        }
    }

    void displayDoctors() const {
        DoctorsLL *temp = doctors;
        while (temp != nullptr) {
            cout << "Doctor ID: " << temp->doctor_id << ", Name: " << temp->name << ", Specialization: " << temp->
                    specialization << endl;
            temp = temp->next;
        }
    }

    void displayAppointments() const {
        Appointments *temp = appointments;
        while (temp != nullptr) {
            cout << "Appointment ID: " << temp->appointment_id << ", Patient ID: " << temp->patient_id <<
                    ", Doctor ID: " << temp->doctor_id << ", Appointment Date: " << temp->appointment_date << endl;
            temp = temp->next;
        }
    }
};

int main() {
    HospitalManagementSystem hms;
    int choice;

    cout << "--------- WELCOME TO RUHENGERI HOSPITAL ------" << endl;
    while (true) {
        cout << "Menu: " << endl;
        cout << "1. Register a patient:" << endl;
        cout << "2. Register a doctor:" << endl;
        cout << "3. Register an appointment:" << endl;
        cout << "4. Display Patients:" << endl;
        cout << "5. Display Doctors:" << endl;
        cout << "6. Display Appointments:" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            // Ignore or clear character from the buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        try {
            switch (choice) {
                case 1: {
                    // Register a patient
                    hms.checkAndSavePatient();
                    break;
                }
                case 2: {
                    // Register a doctor
                    hms.checkAndSaveDoctor();
                    break;
                }
                case 3: {
                    // Register an appointment
                    hms.checkAndSaveAppointment();
                    break;
                }
                case 4:
                    // Display all patients
                    hms.displayPatients();
                    break;
                case 5:
                    // Display all doctors
                    hms.displayDoctors();
                    break;
                case 6:
                    // Display all appointments
                    hms.displayAppointments();
                    break;
                case 7:
                    // Exit
                    return 0;
                default:
                    cout << "Invalid choice. Please try again.\n" << endl;
            }
        } catch (const exception &error) {
            cout << error.what() << endl;
        }
    }
}