#include <iostream>
#include <fstream>

using namespace std;

int counter = 0;

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

public:
    void addTask(int id, string title, string description, string dueDate, string status) {
        string file = directory + to_string(id) + ".txt";

        ofstream outputFile(file);

        Task task(to_string(id), title, description, dueDate, status);
        outputFile << task.getId() << endl
                   << task.getTitle() << endl
                   << task.getDescription() << endl
                   << task.getDueDate() << endl
                   << task.getStatus();
        outputFile.close();
        counter++;
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
        int id = 1;
        while (id <= 3) {
            string file = directory + to_string(id) + ".txt";

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
            id++;
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

int main() {
    TaskManager taskManager;
//    taskManager.addTask(1, "First Task", "Task Full Description", "02-03-2023", "Pending");
//    taskManager.addTask(2, "Second Task", "Task Full Description", "02-03-2023", "Pending");
//    taskManager.addTask(3, "Third Task", "Task Full Description", "02-03-2023", "Pending");
//    taskManager.updateStatus(1, "Completed");
//    taskManager.displayAll();
//    taskManager.removeCompletedTask();
    return 0;
}

