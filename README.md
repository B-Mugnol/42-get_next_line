# 42-get_next_line
#### 42cursus' get_next_line, subject Version 10


This function is the core of this project, it reads and returns a line from the file descriptor *fd*:
```c
char	*get_next_line(int fd);
```
More specifically, it will recursively read *BUFFER_SIZE* bytes from a file, using *read(2)*, until it reaches a line break character (*'\n'*) or the end of the file, and return a string with the content read up to the line break.

Sucessive calls of the function passing the same file descriptor *fd* as argument will print the file's content line by line. The **gnl** on the *bonus* files of this project is able to read from different file descriptors successively, returning the content respective to the file descriptor passed as argument no matter how you order the function calls.


You can change how many bytes it will read at a time by using the flag `-D BUFFER_SIZE=X` when compiling. The default value is 42.


## Notes:
- Choosing a very low *BUFFER_SIZE* value isn't performatic and may take some time to process a file that contains very long lines (thousands of characters before a line break); 

  - On the other side, too high a value will cause more memory to be temporarily allocated than the function would directly use, and may possibly cause memory allocation failure.

- By default, it works for file descriptors numbered from 0 to 256. This upper value is given by MAX_FD, defined in the header files. How many file descriptors your system can handle depends on operating system, build, user shenanigans, and other factors; the number 256 was chosen based on the enviroment in which this project was tested. When available, using the command `ulimit -n` on your terminal will show your enviroment's own file descriptor limit.

- Since this was an individual and small project with very linear progression, commits were made directly to the master branch. I know it isn't a good practice. Please don't judge me :(
