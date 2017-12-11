This is a minor toy project, for working with something Linux on a flight from
Chicago (ORD) to San Francisco (SFO). It isn't really meant to be anything, but
I figured it could be a fun learning experience.

I ended up working on a past university assignment, from CSC209. I didn't look
back at the exact project description, but the basic task was to implement a
MapReduce engine in C, using `fork()` to map in parallel.

I decided to work on this project for a few reasons. First, I wanted to see if
it was any easier after a few years spent thinking about other things. I
haven't worked in C for a while, and I was curious what stuck with me. I was
also curious to see how much progress I could make on this assignment without
online resources. I have offline copies of The Linux Programming Interface by
Michael Kerrisk and K&R, but I got some good practice using man 2 as a
reference.

Here's a basic overview of the architecture:
- A main process is started by the user
- For each datum to be processed, the main process forks a child process and
  creates a FIFO for writing data to the child
- The main process tells each child process the index of the datum for
  processing
- The child process processes the datum at the given index, and returns the
  result as an exit status
- The main process collects these exit statuses in the heap and does the reduce
  operation in-process.

This architecture has several major disadvantages, and should not be used for a
production MapReduce engine. But it is a good assignment for learning about
coordination of processes. Maybe on a later flight I'll work on a more
efficient engine.

Questions:
In TLPI Figure 26.1 it says that under normal termination, only one
byte is available for the exit status of the child process. On my 2016 MacBook,
I found that exit statuses above 256 worked as expected, instead of overflowing
a single byte. Is this undefined behavior?
