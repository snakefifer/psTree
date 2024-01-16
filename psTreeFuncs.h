#ifndef PSTREEFUNCS_H
#define PSTREEFUNCS_H

#include <iostream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;

class Process {
    private:
        int pid;
        int ppid;
        string name;
        string state;
        vector<Process> children;
    public:
        Process();
        Process(int _pid, int _ppid, string _name, string _state);
        int getPid();
        void setPid(int _pid);
        int getPpid();
        void setPpid(int _ppid);
        string getName();
        void setName(string _name);
        string getState();
        void setState(string _state);
        vector<Process>& getChildren();
        void addChild(Process child);
        friend ostream & operator <<(ostream &os, Process &process);
};

char* parsePath(int argc, char* argv[]);
Process compileProcess(char* path);
void checkParents(vector<Process> children, char *argv[]);
void sortByPid(vector<Process> &processes);
void printTree(vector<Process> processes, int ppid, int indent);

#endif