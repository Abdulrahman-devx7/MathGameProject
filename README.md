# Procedural Math Game🎮 #
A modular and console-based math quiz game that can generate simple math questions of different difficulties and various mathematical operations.

## 📝 The objectives ##
- Improve procedural programming architectures and clean code principles.
- Improve efficiency of code by passing by reference in order to save memory, thus, improving performance.
- Implement IPO (input->process->output) conceptual model to enhance data flow.
- Implement state machine design by using Enums to list conditions the system can be in and switch statements to handle logic.


## 🚀 Core features ##
- Dynamic difficulty scaling that allows players to choose between Easy, Mid, Hard, and Mixed levels.
- Comprehensive coverage of generating questions of that involve the four major math operations
- Visual real-time feedback that changes the background the console color depending on the user's interactions.
- An active game grading system that concludes the user's performance at the end of the game.



## ⚙️ Architecture and engineering choices ##
- Encapsulation of several related data types in structs to implement modularity to process individual variables in functions and prevent parameter inflation.
- Usage of Enums to process individual conditions and provide the user with several running modes (i.e. Mixed or hard mode as a difficulty and types of math operations to be involved.)
- On-The-Go memory-efficient question streaming.
- Real-time performance evaluation through
- Passing encapsulated variables via structs by reference to improve memory efficiency with $O(1)$ space efficiency.


