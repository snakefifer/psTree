#include "psTreeFuncs.h"
#include "syscalls.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    char *path = parsePath(argc, argv);
    Process processes = compileProcess(path);
    vector<Process> &children = processes.getChildren();
    sortByPid(children);
    checkParents(children, argv);
    return 0;
}