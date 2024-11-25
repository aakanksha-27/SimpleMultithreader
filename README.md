# OS-Assignment-5

##Introduction
SimpleMultithreader simply creates Pthreads whenever parallel_for APIs are invoked in the user program. It handles both single-threaded and double-threaded execution.

##Implementation
1) TaskSingle and TaskDouble structs store the ranges and lambda functions for single and double-range tasks.

2) run_task_single and run_task_double are thread functions that execute the lambda over their assigned ranges.

3) parallel_for (single-range) divides the range into segments and assigns each to a thread. It executes the lambda on each index in parallel.

4) parallel_for (double-range) divides both ranges into segments and assigns each to a thread, executing the lambda on pairs of indices.

5) Robust error handling has been done for invalid threads or failed operations.

##Contributions

Aakanksha(2023004) - Single thread execution
Palak Yadav(2023363) - Double thread execution

Link to GitHub repository: https://github.com/aakanksha-27/OS-Assignment-5 
