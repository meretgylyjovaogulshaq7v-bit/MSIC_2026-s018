
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Method class
class Method {
public:
    string name;
    int complexity;
    vector<string> attributes;

    Method(string n, int c) {
        name = n;
        complexity = c;
    }

    void addAttribute(string attr) {
        attributes.push_back(attr);
    }
};

// OOP Class
class OOPClass {
public:
    string name;
    vector<string> attributes;
    vector<Method> methods;
    vector<string> parents;
    vector<string> dependencies;

    OOPClass(string n) {
        name = n;
    }

    void addAttribute(string attr) {
        attributes.push_back(attr);
    }

    void addMethod(Method m) {
        methods.push_back(m);
    }

    void addParent(string parent) {
        parents.push_back(parent);
    }

    void addDependency(string dep) {
        dependencies.push_back(dep);
    }

    // WMC - Weighted Methods per Class
    int calculateWMC() {
        int total = 0;
        for (const auto& m : methods) {
            total += m.complexity;
        }
        return total;
    }

    // DIT - Depth of Inheritance Tree
    int calculateDIT(vector<OOPClass>& classes) {
        if (parents.empty())
            return 0;

        int maxDepth = 0;

        for (const string& parent : parents) {
            OOPClass* p = findClass(classes, parent);

            if (p != nullptr) {
                maxDepth = max(maxDepth,
                               p->calculateDIT(classes) + 1);
            }
        }

        return maxDepth;
    }

    // NOC - Number of Children
    int calculateNOC(vector<OOPClass>& classes) {
        int count = 0;

        for (const auto& c : classes) {
            if (find(c.parents.begin(),
                     c.parents.end(), name) != c.parents.end()) {
                count++;
            }
        }

        return count;
    }

    // CBO - Coupling Between Objects
    int calculateCBO() {
        vector<string> uniqueDeps = dependencies;

        sort(uniqueDeps.begin(), uniqueDeps.end());

        uniqueDeps.erase(
            unique(uniqueDeps.begin(), uniqueDeps.end()),
            uniqueDeps.end()
        );

        return uniqueDeps.size();
    }

    // RFC - Response For a Class
    int calculateRFC() {
        vector<string> responses;

        for (const auto& m : methods) {
            responses.push_back(m.name);
        }

        for (const auto& d : dependencies) {
            responses.push_back(d);
        }

        sort(responses.begin(), responses.end());

        responses.erase(
            unique(responses.begin(), responses.end()),
            responses.end()
        );

        return responses.size();
    }

    // LCOM - Lack of Cohesion of Methods
    int calculateLCOM() {
        int P = 0;
        int Q = 0;

        for (size_t i = 0; i < methods.size(); i++) {
            for (size_t j = i + 1; j < methods.size(); j++) {

                bool shared = false;

                for (const auto& a : methods[i].attributes) {
                    if (find(methods[j].attributes.begin(),
                             methods[j].attributes.end(), a)
                        != methods[j].attributes.end()) {
                        shared = true;
                        break;
                    }
                }

                if (shared)
                    Q++;
                else
                    P++;
            }
        }

        return max(0, P - Q);
    }

    // Display metrics
    void displayMetrics(vector<OOPClass>& classes) {
        cout << "\n========== OOP METRICS ==========\n";

        cout << "Class Name: " << name << endl;
        cout << "WMC: " << calculateWMC() << endl;
        cout << "DIT: " << calculateDIT(classes) << endl;
        cout << "NOC: " << calculateNOC(classes) << endl;
        cout << "CBO: " << calculateCBO() << endl;
        cout << "RFC: " << calculateRFC() << endl;
        cout << "LCOM: " << calculateLCOM() << endl;

        cout << "================================\n";
    }

    // Find class declaration
    static OOPClass* findClass(
        vector<OOPClass>& classes,
        const string& className
    ) {
        for (auto& c : classes) {
            if (c.name == className)
                return &c;
        }

        return nullptr;
    }
};

// Global class search function
OOPClass* classfind(
    vector<OOPClass>& classes,
    const string& name
) {
    for (auto& c : classes) {
        if (c.name == name)
            return &c;
    }

    return nullptr;
}

// Save results to file
void SaveResults(vector<OOPClass>& classes) {
    ofstream file("results.txt");

    if (!file.is_open()) {
        throw runtime_error("Cannot open results.txt");
    }

    file << "OOP METRICS CALCULATION RESULTS\n";
    file << "================================\n";

    for (auto& c : classes) {
        file << "\nClass: " << c.name << endl;
        file << "WMC: " << c.calculateWMC() << endl;
        file << "DIT: " << c.calculateDIT(classes) << endl;
        file << "NOC: " << c.calculateNOC(classes) << endl;
        file << "CBO: " << c.calculateCBO() << endl;
        file << "RFC: " << c.calculateRFC() << endl;
        file << "LCOM: " << c.calculateLCOM() << endl;
    }

    file.close();

    cout << "\nResults saved successfully to results.txt!\n";
}

// Main function
int main() {
    vector<OOPClass> classes;

    int choice;

    do {
        cout << "\n================================\n";
        cout << "     OOP METRICS SYSTEM\n";
        cout << "================================\n";
        cout << "1. Add class\n";
        cout << "2. Add attribute\n";
        cout << "3. Add method\n";
        cout << "4. Add inheritance\n";
        cout << "5. Add dependency\n";
        cout << "6. Display class metrics\n";
        cout << "7. Display all metrics\n";
        cout << "8. Save results to file\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input!\n";
            continue;
        }

        try {
            string className;
            string value;

            switch (choice) {

            case 1: {
                cout << "Enter class name: ";
                cin >> className;

                if (classfind(classes, className) != nullptr)
                    throw runtime_error("Class already exists!");

                classes.emplace_back(className);

                cout << "Class added successfully!\n";
                break;
            }

            case 2: {
                cout << "Enter class name: ";
                cin >> className;

                OOPClass* c = classfind(classes, className);

                if (!c)
                    throw runtime_error("Class not found!");

                cout << "Enter attribute name: ";
                cin >> value;

                c->addAttribute(value);

                cout << "Attribute added!\n";
                break;
            }

            case 3: {
                cout << "Enter class name: ";
                cin >> className;

                OOPClass* c = classfind(classes, className);

                if (!c)
                    throw runtime_error("Class not found!");

                string methodName;
                int complexity;

                cout << "Enter method name: ";
                cin >> methodName;

                cout << "Enter complexity: ";
                cin >> complexity;

                if (complexity < 1)
                    throw runtime_error("Complexity must be positive!");

                Method m(methodName, complexity);

                int number;
                cout << "Number of attributes used by method: ";
                cin >> number;

                if (number < 0)
                    throw runtime_error("Invalid number!");

                for (int i = 0; i < number; i++) {
                    cout << "Attribute " << i + 1 << ": ";
                    cin >> value;
                    m.addAttribute(value);
                }

                c->addMethod(m);

                cout << "Method added successfully!\n";
                break;
            }

            case 4: {
                string child, parent;

                cout << "Enter child class: ";
                cin >> child;

                cout << "Enter parent class: ";
                cin >> parent;

                OOPClass* c = classfind(classes, child);

                if (!c || !classfind(classes, parent))
                    throw runtime_error("Class not found!");

                if (child == parent)
                    throw runtime_error("A class cannot inherit itself!");

                c->addParent(parent);

                cout << "Inheritance added!\n";
                break;
            }

            case 5: {
                string source, target;

                cout << "Enter source class: ";
                cin >> source;

                cout << "Enter dependent class: ";
                cin >> target;

                OOPClass* c = classfind(classes, source);

                if (!c || !classfind(classes, target))
                    throw runtime_error("Class not found!");

                if (source == target)
                    throw runtime_error("Self-dependency is not allowed!");

                c->addDependency(target);

                cout << "Dependency added!\n";
                break;
            }

            case 6: {
                cout << "Enter class name: ";
                cin >> className;

                OOPClass* c = classfind(classes, className);

                if (!c)
                    throw runtime_error("Class not found!");

                c->displayMetrics(classes);
                break;
            }

            case 7: {
                if (classes.empty()) {
                    cout << "No classes available!\n";
                    break;
                }

                for (auto& c : classes)
                    c.displayMetrics(classes);

                break;
            }

            case 8:
                SaveResults(classes);
                break;

            case 0:
                cout << "Exiting application...\n";
                break;

            default:
                cout << "Invalid option!\n";
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

    } while (choice != 0);

    return 0;
}
