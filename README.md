# grep-command
I have tried to mimic the grep command 

for compiling use,
gcc -o grepcmd grepcmd.c
for running the code:
./grepcmd option pattern directory
....................................................................
pattern: pattern to be searched
directory: it could be file or folder. for folder, it will traverse all leaf node files!! 
options:
-c : This prints only a count of the lines that match a pattern
-h : Display the matched lines, but do not display the filenames.
-i : Ignores, case for matching
-l : Displays list of a filenames only.
-n : Display the matched lines and their line numbers.
-v : This prints out all the lines that do not matches the pattern
