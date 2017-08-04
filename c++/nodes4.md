# Notes (Part 4)

## Mutexes & Lock Guards

## Producer-consumer queue
* Some worker is enqueuing work for another thread to perform
* Multiple threads may produce work, but want only one thread to serially perform that work
* If consumer wants the next unit of work, they should pull next job off the queue—if there are no elements in the queue, they should sleep until there is something in the queue
