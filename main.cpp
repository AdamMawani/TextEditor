#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Task structure to hold task details
struct Task {
    string description;
    bool completed;

    Task(const string& desc) : description(desc), completed(false) {}
};

// TaskEditor class to manage tasks
class TaskEditor {
private:
    vector<Task> tasks;

public:
    // Method to add a new task
    void addTask(const string& description) {
        tasks.push_back(Task(description));
        cout << "Task added successfully!" << endl;
    }

    // Method to display all tasks
    void viewTasks() {
        if (tasks.empty()) {
            cout << "No tasks found." << endl;
            return;
        }

        cout << "Tasks:" << endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << (tasks[i].completed ? "[X] " : "[ ] ") << tasks[i].description << endl;
        }
    }

    // Method to mark a task as completed
    void markTaskCompleted(size_t index) {
        if (index >= 1 && index <= tasks.size()) {
            tasks[index - 1].completed = true;
            cout << "Task marked as completed!" << endl;
        } else {
            cout << "Invalid task index." << endl;
        }
    }
};

int main() {
    TaskEditor editor;
    int choice;

    do {
        cout << "\nTask Editor Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string desc;
                cout << "Enter task description: ";
                cin.ignore();
                getline(cin, desc);
                editor.addTask(desc);
                break;
            }
            case 2:
                editor.viewTasks();
                break;
            case 3: {
                size_t index;
                cout << "Enter task index to mark as completed: ";
                cin >> index;
                editor.markTaskCompleted(index);
                break;
            }
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
