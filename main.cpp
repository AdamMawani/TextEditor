#include <iostream>
#include <vector>
#include <string>
#include <fstream> // For file I/O
#include <algorithm> // For search functionality

using namespace std;

struct Task {
    string description;
    bool completed;
    // Additional fields
    int priority;   // Priority level of task
    string dueDate; // Due date of task

    Task(const string& desc) : description(desc), completed(false), priority(0), dueDate("") {}
};

class TaskEditor {
private:
    vector<Task> tasks;

public:
    void addTask(const string& description) {
        tasks.push_back(Task(description));
        cout << "Task added successfully!" << endl;
    }

    void viewTasks() {
        if (tasks.empty()) {
            cout << "No tasks found." << endl;
            return;
        }

        cout << "Tasks:" << endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << (tasks[i].completed ? "[X] " : "[ ] ") 
                 << "Priority: " << tasks[i].priority 
                 << ", Description: " << tasks[i].description 
                 << ", Due Date: " << tasks[i].dueDate << endl;
        }
    }

    void markTaskCompleted(size_t index) {
        if (index >= 1 && index <= tasks.size()) {
            tasks[index - 1].completed = true;
            cout << "Task marked as completed!" << endl;
        } else {
            cout << "Invalid task index." << endl;
        }
    }

    // New method to edit task description
    void editTaskDescription(size_t index, const string& newDescription) {
        if (index >= 1 && index <= tasks.size()) {
            tasks[index - 1].description = newDescription;
            cout << "Task description updated successfully!" << endl;
        } else {
            cout << "Invalid task index." << endl;
        }
    }

    // New method to delete task
    void deleteTask(size_t index) {
        if (index >= 1 && index <= tasks.size()) {
            tasks.erase(tasks.begin() + index - 1);
            cout << "Task deleted successfully!" << endl;
        } else {
            cout << "Invalid task index." << endl;
        }
    }

    // New method to save tasks to a file
    void saveTasks(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& task : tasks) {
                outFile << task.description << "," << task.completed << "," << task.priority << "," << task.dueDate << endl;
            }
            cout << "Tasks saved successfully!" << endl;
            outFile.close();
        } else {
            cout << "Unable to open file." << endl;
        }
    }

    // New method to load tasks from a file
    void loadTasks(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            tasks.clear(); // Clear existing tasks
            string line;
            while (getline(inFile, line)) {
                size_t pos = line.find(",");
                if (pos != string::npos) {
                    Task task(line.substr(0, pos));
                    task.completed = stoi(line.substr(pos + 1, 1));
                    task.priority = stoi(line.substr(pos + 3, 1));
                    task.dueDate = line.substr(pos + 5);
                    tasks.push_back(task);
                }
            }
            cout << "Tasks loaded successfully!" << endl;
            inFile.close();
        } else {
            cout << "Unable to open file." << endl;
        }
    }

    // New method to search for tasks based on keywords
    void searchTasks(const string& keyword) {
        vector<Task> matchedTasks;
        for (const auto& task : tasks) {
            if (task.description.find(keyword) != string::npos) {
                matchedTasks.push_back(task);
            }
        }
        if (matchedTasks.empty()) {
            cout << "No tasks found matching the keyword." << endl;
        } else {
            cout << "Matched tasks:" << endl;
            for (const auto& task : matchedTasks) {
                cout << "Priority: " << task.priority 
                     << ", Description: " << task.description 
                     << ", Due Date: " << task.dueDate << endl;
            }
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
        cout << "4. Edit Task Description\n";
        cout << "5. Delete Task\n";
        cout << "6. Save Tasks\n";
        cout << "7. Load Tasks\n";
        cout << "8. Search Tasks\n";
        cout << "9. Exit\n";
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
            case 4: {
                size_t index;
                string newDesc;
                cout << "Enter task index to edit description: ";
                cin >> index;
                cout << "Enter new description: ";
                cin.ignore();
                getline(cin, newDesc);
                editor.editTaskDescription(index, newDesc);
                break;
            }
            case 5: {
                size_t index;
                cout << "Enter task index to delete: ";
                cin >> index;
                editor.deleteTask(index);
                break;
            }
            case 6: {
                string filename;
                cout << "Enter filename to save tasks: ";
                cin >> filename;
                editor.saveTasks(filename);
                break;
            }
            case 7: {
                string filename;
                cout << "Enter filename to load tasks: ";
                cin >> filename;
                editor.loadTasks(filename);
                break;
            }
            case 8: {
                string keyword;
                cout << "Enter keyword to search tasks: ";
                cin >> keyword;
                editor.searchTasks(keyword);
                break;
            }
            case 9:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}