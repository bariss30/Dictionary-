# C Dictionary Application

This C program implements a simple dictionary application where users can add, search, display, remove, and edit words and their meanings.

## Features

- **Add Word:** Users can add new words along with their meanings to the dictionary.
- **Search Meaning:** Users can search for the meaning of a word in the dictionary.
- **Display Dictionary:** Users can view the entire dictionary.
- **Remove Word:** Users can remove a word and its meaning from the dictionary.
- **Edit Word:** Users can edit the meaning of an existing word in the dictionary.
- **Persistent Storage:** Dictionary entries are stored in a file (`dictionary.txt`) and loaded into memory at the start of the program. Any changes made to the dictionary are reflected in the file.

## Usage

1. Compile the source code using a C compiler.
2. Run the compiled executable.
3. Choose from the menu options to perform various operations on the dictionary.

```bash
gcc main.c -o dictionary
./dictionary
