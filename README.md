# OS-Assignment-5

-TaskSingle and TaskDouble structs store the ranges and lambda functions for single and double-range tasks, respectively.

-run_task_single and run_task_double are thread functions that execute the lambda over their assigned ranges.

-parallel_for (single-range) divides the range into segments and assigns each to a thread. It executes the lambda on each index in parallel.

-parallel_for (double-range) divides both ranges into segments and assigns each to a thread, executing the lambda on pairs of indices.

-Error handling checks for invalid threads or failed operations.
