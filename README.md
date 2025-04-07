# Stack-and-Queue-Application
This C project implements a text editor with differential Undo and Redo functionality using two stacks (Undo/Redo) and one queue. The application allows users to load a text file, perform string manipulations (insert/remove), and undo/redo changes. The updated text is saved to a new output file based on user input.

Features:
1. Load Input File: Load the initial text from a file.
2. Print Text: Display the current content of the text.
3. Insert Strings: Insert words/strings into the text.
4. Remove Strings: Delete words/strings from the text.
5. Undo Operation: Undo the last change by moving it from the Undo Stack to the Redo Stack.
6. Redo Operation: Redo a previously undone operation by moving it from the Redo Stack to the Undo Stack.
7. Display Undo/Redo Stacks: Show the current content of both stacks.
8. Save Updated Text: Save the modified text to an output file.
9. Exit: Exit the program.

Stack and Queue Implementation:
* Undo Stack: Stores changes made to the text (insert/remove operations, word, type of operation, and index).
* Redo Stack: Stores undone changes, allowing users to redo them.
* Add Queue: Stores words for added strings, which are then inserted into both the text and the Undo Stack.

Operations:
* Insert: A word is added to the text, logged to the Queue, and then pushed to the Undo Stack.
* Remove: A word is removed from the text, the operation is logged, and the change is pushed to the Undo Stack.
* Undo: Reverts the last operation by popping from the Undo Stack and pushing to the Redo Stack.
* Redo: Reapplies the last undone operation by popping from the Redo Stack and pushing back to the Undo Stack.

