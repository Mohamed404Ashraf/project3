# project3
This C++ program demonstrates reader-writer synchronization using semaphores. It consists of a writer thread and multiple reader threads that access a shared buffer.
The writer has exclusive access to write data into the buffer, while multiple readers can concurrently read from it. 
Semaphores are used to coordinate access and ensure that writers have priority over readers when writing.
