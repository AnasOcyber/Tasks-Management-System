#include <iostream>
#include <fstream>

using namespace std;

class Task {
private:
    string taskId;
    string taskTitle;
    string taskDescription;
    string taskDueDate;
    string taskStatus;

public:
    void setId(string id) {
        taskId = id;
    }

    string getId() {
        return taskId;
    }

    void setTitle(string title) {
        taskTitle = title;
    }

    string getTitle() {
        return taskTitle;
    }

    void setDescription(string description) {
        taskDescription = description;
    }

    string getDescription() {
        return taskDescription;
    }

    void setDueDate(string dueDate) {
        taskDueDate = dueDate;
    }

    string getDueDate() {
        return taskDueDate;
    }

    void setStatus(string status) {
        taskStatus = status;
    }

    string getStatus() {
        return taskStatus;
    }

    Task(string id, string title, string description, string dueDate, string status) {
        setId(id);
        setTitle(title);
        setDescription(description);
        setDueDate(dueDate);
        setStatus(status);
    }

    void update(string title="", string description="", string dueDate="", string status="") {
        cout << endl << "Leave empty in case you dont want to update value." << endl;

        cout << "New Title?";
        getline(cin, title);

        cout << "New Description?";
        getline(cin, description);

        cout << "New Due Date?";
        getline(cin, dueDate);

        cout << "New Status?";
        getline(cin, status);

        if (title != "")
            setTitle(title);

        if (description != "")
            setDescription(description);

        if (dueDate != "")
            setDueDate(dueDate);

        if (status != "")
            setStatus(status);
    }

    void showDetails() {
        cout << "Id: " << taskId << endl
             << "Title: " << taskTitle << endl
             << "Description: " << taskDescription << endl
             << "Due Date: " << taskDueDate << endl
             << "Task Status: " << taskStatus << endl;
    }
};


class TaskManager {
private:
    string taskId;
    string taskTitle;
    string taskDescription;
    string taskDueDate;
    string taskStatus;
    string directory = "../database/";
    string databaseRecords = directory + "total-files.txt";

public:
    void addTask(string title, string description, string dueDate) {
        int id;
        ifstream getRecords(databaseRecords);
        getRecords >> id;
        getRecords.close();

        const string status = "Pending";
        string file;

        id++;
        file = directory + to_string(id) + ".txt";

        ofstream saveRecords(databaseRecords);
        saveRecords << id;
        saveRecords.close();

        ofstream outputFile(file);

        Task task(to_string(id), title, description, dueDate, status);
        outputFile << task.getId() << endl
                   << task.getTitle() << endl
                   << task.getDescription() << endl
                   << task.getDueDate() << endl
                   << task.getStatus();
        outputFile.close();

        cout << "Task added successfully." << endl
             << "------------------------" << endl;
    }

    void updateStatus(int id, string status) {
        string file = directory + to_string(id) + ".txt";

        ifstream inputFile(file);
        getline(inputFile, taskId);
        getline(inputFile, taskTitle);
        getline(inputFile, taskDescription);
        getline(inputFile, taskDueDate);
        getline(inputFile, taskStatus);
        inputFile.close();

        taskStatus = status;

        ofstream outputFile(file);
        outputFile << taskId << endl
                   << taskTitle << endl
                   << taskDescription << endl
                   << taskDueDate << endl
                   << taskStatus;
        outputFile.close();

        cout << "Status changed successfully." << endl
             << "----------------------------";
    }

    void displayAll() {
        int id;
        ifstream records(databaseRecords);
        records >> id;
        records.close();

        if (id) {
            for (int index = 1; index <= id; index++) {
                string file = directory + to_string(index) + ".txt";

                ifstream inputFile(file);
                if(!inputFile){
                    id++;
                    continue;
                }
                getline(inputFile, taskId);
                getline(inputFile, taskTitle);
                getline(inputFile, taskDescription);
                getline(inputFile, taskDueDate);
                getline(inputFile, taskStatus);
                cout << taskId << "\t"
                     << taskTitle << "\t"
                     << taskDescription << "\t"
                     << taskDueDate << "\t"
                     << taskStatus << endl;
                cout << ("---") << endl;
                inputFile.close();
            }
        }

        else
            cout << "No records found." << endl
                 << "-----------------";
    }

    void removeCompletedTask() {
        int records;
        ifstream getRecords(databaseRecords);
        getRecords >> records;
        getRecords.close();

        int filesDeleted = 0;

        for (int id = 1; id <= records; id++) {
            string file = directory + to_string(id) + ".txt";

            ifstream inputFile(file);
            getline(inputFile, taskId);
            getline(inputFile, taskTitle);
            getline(inputFile, taskDescription);
            getline(inputFile, taskDueDate);
            getline(inputFile, taskStatus);
            if (taskStatus == "Completed") {
                remove(file.c_str());
                cout << "Task(s) removed successfully." << endl
                     << "--------------------------";
                filesDeleted++;
            }
            inputFile.close();
        }

        if (!filesDeleted)
            cout << "No completed tasks." << endl
                 << "-----------------" << endl;

        ofstream saveRecords(databaseRecords);
        saveRecords << records - filesDeleted;
        saveRecords.close();
    }
};

void showMenu() {
    TaskManager taskManager;

    int choice;
    while (choice != 5) {
        cout << "1. Add new task" << endl
             << "2. Update task status" << endl
             << "3. Display tasks" << endl
             << "4. Remove completed tasks" << endl
             << "5. Exit" << endl;

        cout << "Choice: ";
        cin >> choice;

        cout << endl;

        if (choice == 1) {
            string title;
            string description;
            string dueDate;

            cin.ignore();

            cout << "Task Title: ";
            getline(cin, title);

            cout << "Task Description: ";
            getline(cin, description);

            cout << "Task Due Date (DD-MM-YYYY): ";
            getline(cin, dueDate);

            taskManager.addTask(title, description, dueDate);
        }

        else if (choice == 2) {
            int id;
            char status;

            cout << "Id: ";
            cin >> id;

            int checkId;

            ifstream inputFile("../database/" + to_string(id) + ".txt");
            inputFile >> checkId;

            if (checkId == id) {

                while (true) {
                    cout << "C for Completed." << endl
                         << "P for Pending." << endl;

                    cout << "Status (C/P): ";
                    cin >> status;
                    cout << endl;
                    if (status == 'C') {
                        taskManager.updateStatus(id, "Completed");
                        break;
                    }
                    else if (status == 'P') {
                        taskManager.updateStatus(id, "Pending");
                        break;
                    }
                    else
                        cout << "Only C or P!" << endl
                             << "------------" << endl;
                }
            }
            else
                cout << "No record found for id: " << id << endl
                     << "-------------------------";
        }

        else if (choice == 3)
            taskManager.displayAll();

        else if (choice == 4)
            taskManager.removeCompletedTask();

        else if (choice == 5)
            cout << "Exiting" << endl
                 << "-------";

        else
            cout << "Invalid choice." << endl;
        cout << endl;
    }
}

int main() {
    showMenu();
    return 0;
}

