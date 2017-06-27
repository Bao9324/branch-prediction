# branch-prediction
In this lab, you will simulate a simple branch predictor with a 2-bit saturating counter. You are provided with a text file containing a trace of branch instructions consisting of the PC at which each branch occurs, and whether the branch is Taken or Not Taken. 
Your goal is write code to evaluate the performance of a 2-bit saturating counter based branch predictor on this trace. Your output file indicates, for each branch in the trace, whether it was predicted as Taken or Not Taken. 
Branch Predictor Architecture
Your design must consist of 2m 2-bit saturating counters indexed using m LSBs of each branch instruction. Each 2-bit saturating predictor starts in the 11 (Predict Taken with High Confidence) state and is updated as per the finite state machine discussed in Lecture 11. The value of m is specified in a config file config.txt. 
Config File
The config file config.txt contains a single line with the value of m. A sample file for m=12 is provided. The largest value of m is 32 (for 32 bit PCs), but we will not input an m larger than 20.
Trace File
The trace file, trace.txt, contains one branch per line. Each line has the PC for the corresponding branch (in hex format) followed by a single bit indicating Taken (1) or Not Taken (0). A sample trace file is provided.  
