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
    string totalFiles = directory + "total-files.txt";

public:
    void addTask(int id, string title, string description, string dueDate, string status) {
        string file = directory + to_string(id) + ".txt";

//        Storing number of files
        ofstream records(totalFiles);
        records << id;

        ofstream outputFile(file);

        Task task(to_string(id), title, description, dueDate, status);
        outputFile << task.getId() << endl
                   << task.getTitle() << endl
                   << task.getDescription() << endl
                   << task.getDueDate() << endl
                   << task.getStatus();
        outputFile.close();
    }

    void updateStatus(int id, string status) {
        string file = directory + to_string(id) + ".txt";

        ifstream inputFile(file);
        getline(inputFile, taskId);
        getline(inputFile, taskTitle);
        getline(inputFile, taskDescription);
        getline(inputFile, taskDueDate);
        getline(inputFile, taskStatus);

        taskStatus = status;

        ofstream outputFile(file);
        outputFile << taskId << endl
                   << taskTitle << endl
                   << taskDescription << endl
                   << taskDueDate << endl
                   << taskStatus;
        outputFile.close();
    }

    void displayAll() {
        int id;
        ifstream records(totalFiles);
        records >> id;

       for (int index = 1; index <= id; index++) {
            string file = directory + to_string(index) + ".txt";

            ifstream inputFile(file);

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

    void removeCompletedTask() {
        int id = 0;
        while (id <= 3) {
            string file = directory + to_string(id) + ".txt";

            ifstream inputFile(file);
            getline(inputFile, taskId);
            getline(inputFile, taskTitle);
            getline(inputFile, taskDescription);
            getline(inputFile, taskDueDate);
            getline(inputFile, taskStatus);
            inputFile.close();
            if (taskStatus == "Completed")
                remove(file.c_str());
            id++;
        }
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

        if (choice == 1) {
            int id;
            string title;
            string description;
            string dueDate;
            string status;

            cout << "Task Id: ";
            cin >> id;

            cout << "Task Title: ";
            cin >> title;

            cout << "Task Description: ";
            cin >> description;

            cout << "Task Due Date (DD-MM-YYYY): ";
            cin >> dueDate;

            cout << "Task Status: ";
            cin >> status;

            taskManager.addTask(id, title, description, dueDate, status);
        }

        else if (choice == 2) {
            int id;
            char status;

            cout << "Id: ";
            cin >> id;

            cout << "Note: C = Completed." << endl << "P = pending." << endl;


            while (true) {
                cout << "Status (C/P): ";
                cin >> status;
                if (status == 'C') {
                    taskManager.updateStatus(id, "Completed");
                    break;
                }
                else if (status == 'P') {
                    taskManager.updateStatus(id, "Pending");
                    break;
                }
                else
                    cout << "Only C or P!";
            }
        }

        else if (choice == 3)
            taskManager.displayAll();

        else if (choice == 4)
            taskManager.removeCompletedTask();

        else if (choice == 5)
            cout << "Exiting";

        else
            cout << "Invalid choice." << endl;
        cout << endl;
    }
}

int main() {
    showMenu();
    return 0;
}

