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
public:
    void addTask(string id, string title, string description, string dueDate, string status) {
        string directory = "../database/";
        string fileName = directory + id + ".txt";
        ifstream inputFile(fileName);

        if (!inputFile) {
            ofstream outputFile(fileName);

            Task task(id, title, description, dueDate, status);

            outputFile << task.getId() << endl
                       << task.getTitle() << endl
                       << task.getDescription() << endl
                       << task.getDueDate() << endl
                       << task.getStatus() << endl;
            outputFile.close();
        }
        else {
            id = id + "-regenerated";
            fileName = directory + id + ".txt";

            ofstream outputFile(fileName);

            Task task(id, title, description, dueDate, status);

            outputFile << task.getId() << endl
                       << task.getTitle() << endl
                       << task.getDescription() << endl
                       << task.getDueDate() << endl
                       << task.getStatus() << endl;

            outputFile.close();
        }


    }
};

int main() {
    TaskManager taskManager;
    taskManager.addTask("1", "First Task", "Task Full Description", "02-03-2023", "Pending");
    taskManager.addTask("3", "First Task", "Task Full Description", "02-03-2023", "Pending");
    taskManager.addTask("3", "First Task", "Task Full Description", "02-03-2023", "Pending");

    return 0;
}

