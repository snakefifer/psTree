#include "psTreeFuncs.h"
#include "syscalls.h"
#include <algorithm>
#include <string>

using namespace std;

Process::Process() {}

Process::Process(int _pid, int _ppid, string _name, string _state) {
    pid = _pid;
    ppid = _ppid;
    name = _name;
    state = _state;
}

int Process::getPid() {
    return pid;
}

void Process::setPid(int _pid) {
    pid = _pid;
}

int Process::getPpid() {
    return ppid;
}

void Process::setPpid(int _ppid) {
    ppid = _ppid;
}

string Process::getName() {
    string out = name;
    size_t found = out.find('\n');
    if (found != string::npos)
        out.erase(found);
    return out;
}

void Process::setName(string _name) {
    name = _name;
}

string Process::getState() {
    string out = state;
    size_t beg = out.find('(');
    size_t end = out.find(')');
    return state.substr(beg + 1, end - beg - 1);
}

void Process::setState(string _state) {
    state = _state;
}

vector<Process>& Process::getChildren() {
    return children;
}

void Process::addChild(Process child) {
    children.push_back(child);
}

ostream & operator <<(ostream &os, Process &process) {
    os << process.getName() << " (" << process.getPid() << "," <<  process.getState() << ")";
    return os;
}

char* parsePath(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        cerr << "Improper Argument Count." << endl;
        exit(1);
    }
    char *path;
    if (argc == 2)
        path = argv[1];
    else
        path = argv[2];
    return path;
}

Process compileProcess(char *path) {
    Chdir(path);
    DIR *dptr = Opendir(path);
    struct dirent *fileptr = NULL;
    Process processes;
    while ((fileptr = Readdir(dptr))) {
        if (strcmp(fileptr -> d_name, ".") && strcmp(fileptr -> d_name, "..")) {
            if (fileptr -> d_type == DT_DIR) {
                char newPath[1024];
                strcpy(newPath, path);
                strcat(newPath, "/");
                strcat(newPath, fileptr -> d_name);
                Process child = compileProcess(newPath);
                processes.addChild(child);
            } else {
                FILE *file = Fopen(fileptr -> d_name, "r");
                char line[256];
                while (fgets(line, sizeof(line), file) != NULL) {
                    if (strncmp(line, "Name:", 5) == 0) {
                        processes.setName(line + 6);
                    } else if (strncmp(line, "State:", 6) == 0) {
                        processes.setState(line + 7);
                    } else if (strncmp(line, "Pid:", 4) == 0) {
                        processes.setPid(stoi(line + 4));
                    } else if (strncmp(line, "PPid:", 5) == 0) {
                        processes.setPpid(stoi(line + 5));
                        Process process(processes.getPid(), processes.getPpid(), processes.getName(), processes.getState());
                        processes.addChild(process);
                    }
                }
                Fclose(file);
            }
        }
    }
    Closedir(dptr);
    return processes;
}

void printTree(vector<Process> processes, int ppid, int indent) {
    string dashes;
    for (int i = 0; i < indent; i++)
        dashes += "----";
    for (size_t i = 0; i < processes.size(); i++) {
        if (processes[i].getName() != "") {
            if (processes[i].getPpid() == ppid) {
                cout << dashes << processes[i] << endl;
                int next = processes[i].getPid();
                printTree(processes, next, indent + 1);
            }
        }
    }
}

void checkParents(vector<Process> children, char *argv[]) {
    int count = 0;
    int index;
    for (size_t i = 0; i < children.size(); i++) {
        if (children[i].getPpid() == 0) {
            count++;
            index = i;
        }
    }
    if (count == 0) {
        cerr << "No origin parent process was found." << endl;
        exit(98);
    } else if (count > 1) {
        if (strcmp(argv[1], "-u") != 0) {
            cerr << "More than one origin parant process was found." << endl;
            exit(99);
        }
    } else {
        cout << children[index] << endl;
        printTree(children, children[index].getPid(), 1);
    }
}

void sortByPid(vector<Process> &processes) {
    sort(processes.begin(), processes.end(), 
        [](Process &a, Process &b) {
            return a.getPid() < b.getPid();
        });
}