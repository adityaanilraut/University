#include <Python.h>
#include <iostream>
#include<string>
using namespace std;

int main() {
    // Initialize the Python Interpreter
    Py_Initialize();

    string cPlusPlusData = "[10,20,30,40,50]";

    // Create a Python variable and assign it the C++ data
    std::string pythonCode = "cPlusPlusData = " + cPlusPlusData;//std::to_string(cPlusPlusData);

    // Run the Python code that sets up the variable
    PyRun_SimpleString(pythonCode.c_str());

    // Now let's use that variab Python
    PyRun_SimpleString("print('Data from C++:', cPlusPlusData)");
    PyRun_SimpleString("import pandas as pd");
    PyRun_SimpleString("import matplotlib.pyplot as plt");
    PyRun_SimpleString("file_path = 'new.csv'");
    PyRun_SimpleString("data = pd.read_csv(file_path)");
    PyRun_SimpleString("data.head()");

    PyRun_SimpleString("# Re-importing matplotlib.pyplot as plt due to previous environment reset");
    
    PyRun_SimpleString("sizes = data['size']");
    PyRun_SimpleString("bubbleSort_times = data['bubbleSort']");
    PyRun_SimpleString("insertionSort_times = data['insertionSort']");
    PyRun_SimpleString("selectionSort_times = data['selectionSort']");
    PyRun_SimpleString("mergeSort_times = data['mergesort']");
    PyRun_SimpleString("plt.figure(figsize=(10, 6))");
    PyRun_SimpleString("# Plot each sorting algorithm's data");
    PyRun_SimpleString("plt.plot(sizes, bubbleSort_times, label='Bubble Sort', marker='o')");
    PyRun_SimpleString("plt.plot(sizes, insertionSort_times, label='Insertion Sort', marker='s')");
    PyRun_SimpleString("plt.plot(sizes, selectionSort_times, label='Selection Sort', marker='^')");
    PyRun_SimpleString("plt.plot(sizes, mergeSort_times, label='Merge Sort', marker='x')");
    PyRun_SimpleString("# Adding titles and labels");
    PyRun_SimpleString("plt.title('Sorting Algorithms: Time Complexity Comparison')");
    PyRun_SimpleString("plt.xlabel('Input Size')");
    PyRun_SimpleString("plt.ylabel('Time Taken (seconds)')");
    PyRun_SimpleString("plt.yscale('log')  # Log scale for better visualization of time differences");
    PyRun_SimpleString("# Adding a legend");
    PyRun_SimpleString("plt.legend()");
    PyRun_SimpleString("# Display the plot");
    PyRun_SimpleString("plt.show()");



    // Display the plot
    
    
    PyRun_SimpleString(" ");
    PyRun_SimpleString(" ");

    PyRun_SimpleString(" ");
    PyRun_SimpleString(" ");
    PyRun_SimpleString(" ");
    PyRun_SimpleString(" ");
    PyRun_SimpleString(" ");
    PyRun_SimpleString(" ");
    PyRun_SimpleString(" ");
    PyRun_SimpleString(" ");

    PyRun_SimpleString(" ");
    PyRun_SimpleString(" ");
    PyRun_SimpleString(" ");

    PyRun_SimpleString(" ");
    PyRun_SimpleString(" ");

    PyRun_SimpleString(" ");
    PyRun_SimpleString(" ");

    PyRun_SimpleString(" ");
    PyRun_SimpleString(" ");


    PyRun_SimpleString(" ");

    PyRun_SimpleString(" ");
    PyRun_SimpleString(" ");

    PyRun_SimpleString(" ");

    PyRun_SimpleString(" ");

    PyRun_SimpleString(" ");

    PyRun_SimpleString(" ");
    
    PyRun_SimpleString("plt.show()");
    // Finalize the Python Interpreter
    Py_Finalize();

    return 0;
}