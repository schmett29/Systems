Name: David Schmetterling
Section: 02

To run:
gcc -o assicnment6.exe assignment6.c

About:
I have included a picture which shows a general outline for how my program works. The main thread spawns 3 processes and creates 4 pipes (fd1,2,3,4). The first process reads in a line (up to 80 characters), and sends it to process 2 until the current line = NULL. It then uses the read command to wait to send the next line until Process 2 requests it. Process 2 changes the case, character by character, in the given line. Then it uses read to wait on a response from process 3, send process 3 the changed line, and asks process 1 for the next line. Process 3 writes the line to an output file and then sends a message back to process 2 to ask for the next line. When the input file reaches its end, Process 1 sends "end" to process 2 and then exits. When process 2 receieves this, it sends "end" to process 3 and then terminates. When process 3 receives "end", it closes the file that it is writing to, and exits. Then the parent thread, which is waiting for all the children to exit, closes all of the pipes just in case and terminates the program.