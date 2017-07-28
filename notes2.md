# C Notes (Part 2)

## Signals
* SIGINT (ctrl+C) — "please turn yourself off"
  * Terminal sends SIGINT to the foreground process
  * Signal is sent to the process, and the process invokes a signal handler
    * The signal handler is some functionality that you write that's responsible for cleanup and shutting down the program
* ctrl+Z tells the terminal to send a SIGSTOP(?) which says to please pause yourself
  * `bg` => most recent process, restart via a SIGSTART(?), but run in the background
* `kill -9` sends to a `SIGKILL`

## Segmentation Faults
* Tries to dereference a garbage or null pointer, this looks it up in the **translation lookaside buffer** (TLB), which maps Virtual Memory => Physical Memory
* A segmentation fault occurs when you've gone outside of the block of memory that the OS has given you.
  * This then sets an error condition in the CPU.
  * CPU keeps a list of signal handlers. There's a special function pointer for the signal handler in your code.
  * The CPU will then call your signal handler.
* `malloc` is a library function (part of `glibc`)
  * Maintains a `free list` which is a list of blocks that are free. When you free something up, it adds it to the free list.

## Stack vs Heap
  * The C runtime creates a stack, for which it grabs a certain amount of memory. A *stack overflow* is when the stack itself runs out of memory due to things you place on the stack, but the stack is very fast to access due to the memory model.
  * For stuff on the heap, these are more random-access, but you can store essentially unlimited amounts of stuff onto the heap without a problem.

## Memory errors
  * Referencing data that you've never allocated (or have previously freed)
  * A buffer overrun (going past the end of the buffer)
  * Failing to free memory—you have a memory leak
  * Double freeing (freeing something twice)
  *
