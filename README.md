# C++ Process Tree

Create a textual output depicting the process hierarchy (sample output below) with siblings at the same "level" of indentation and children being indented by four hyphens (i.e., "----" from their parent).

If there is not a singular origin parent process, you are to exit with an error message and a return code of 98.
If there is not a singular origin parent process with a PPid of 0, you are to exit with an error message and a return code of 99.

The program is run by calling psTree followed by a single argument passed on the command line. Thus, you do NOT prompt for input, you read input from argv[]! The argument to be passed is the top-level directory in which one or more process directories are located.

In your C++ code, you are to create a single class named "Process" to store information about each process you encounter. As you encounter a valid process, you will need to create an instance of this class that contains private members to hold that process' PID, PPID, Name, and State. You will also need to keep some form of list (vector, array, or list container) to hold all its children. Thus, you will need to have setter (mutator) and getter (accessor) functions to set or get these variable values. You may also need/have additional member functions.

You must also overload the insertion (output) operator such that the information in a Process object (node) can be displayed. This will help with debugging and simplifying your printing out of the hierarchy.

Sample output (MATCH THIS OUTPUT!)

```
$> psTree /path/to/folder/
systemd (1,sleeping)
----NetworkManager (1616,sleeping)
--------gmain (1623,sleeping)    
--------gdbus (1624,sleeping)
----sshd (1635,running)
--------sshd (1383882,sleeping)
------------sshd (1383942,sleeping)
----------------bash (1383952,sleeping)
--------------------sleep (1385681,stopped)
--------------------psTree (1385685,running)
--------------------a.out (1473880,zombie)
----crond (3657,sleeping)
```