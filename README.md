# Tiny-language

A simple compiler project for a tiny custom programming language, featuring both lexical and syntactic analysis with a graphical user interface (GUI) for interactive parsing and error feedback.

---

## Table of Contents

- [Features](#features)
- [Example Grammar](#example-grammar)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Build Instructions](#build-instructions)
  - [Usage](#usage)
- [Directory Structure](#directory-structure)
- [Example Input](#example-input)
- [Project Structure](#project-structure)
- [Contributing](#contributing)

---

## Features

- **Lexical Analysis:** Tokenizes user input, categorizing keywords, identifiers, operators, and more.
- **Syntax Analysis (Parsing):** Uses a hand-crafted parser to analyze the structure of the input based on a defined grammar.
- **Error Reporting:** Provides clear, color-coded feedback for parsing errors, including line number and token details.
- **Graphical User Interface:** Built with Windows Forms in C++/CLI, allowing users to interactively enter code, run analysis, and view results.
- **Custom Grammar:** Implements a simple imperative language supporting conditional statements, loops, assignments, reading/writing, and declarations.
- **Educational Resource:** Easily extensible for students or those learning about compiler design and language processing.
- **Grammar Resources:** Includes text files for grammar, FIRST/FOLLOW sets, and parsing rules for deeper understanding and debugging.

---

## Example Grammar

See [`Rules/1.1Grammeraftersimple.txt`](https://github.com/Shady-Mo/Tiny-language/blob/master/Rules/1.1Grammeraftersimple.txt) for the full grammar. Example constructs include:

```
<program>           ==> <stmt_list>
<stmt_list>         ==> <stmt> <stmt_list_tail>
<stmt>              ==> <if_stmt> | <repeat_stmt> | <assign_stmt> ; | <read_stmt> ; | <write_stmt> ; | <declare_stmt> ;
<if_stmt>           ==> if <exp> then <stmt_list> <else_part> end
<repeat_stmt>       ==> repeat <stmt_list> until <exp> ;
<assign_stmt>       ==> IDENTIFIER := <exp>
<read_stmt>         ==> read IDENTIFIER
<write_stmt>        ==> write <write_stmt_tail>
<declare_stmt>      ==> int IDENTIFIER
```

---

## Getting Started

### Prerequisites

- **Windows** operating system
- **Visual Studio** with C++/CLI support

### Build Instructions

1. Open the solution in Visual Studio.
2. Build the project (`compiler_gui`) in Debug or Release mode.
3. Run the executable generated in `compiler_gui/x64/Debug/` or `compiler_gui/x64/Release/`.

### Usage

1. Launch the application.
2. Enter your Tiny-language source code in the provided text box.
3. Click the **Lexical Analysis** button to view tokenization results.
4. Click the **Parse** button to perform syntax analysis.
5. View tokens and parser analysis results in the corresponding output areas.
6. Parsing errors (if any) are highlighted in red with detailed messages (line, token, error description).

---

## Directory Structure

- `compiler_gui/` — Main source code for the GUI, lexer, and parser logic.
- `Rules/` — Text files describing the language grammar, first/follow sets, and other parsing rules.
- `compiler_gui/x64/Debug/` — Build output directory.

---

## Example Input

```tiny
int x;
read x;
if x < 10 then
  write "Less than ten";
else
  write x;
end
```

---

## Project Structure

```
Tiny-language/
│
├── compiler_gui/
│   ├── MainForm.h         # Windows Forms GUI logic
│   ├── lexerlogic.h       # Lexical analysis implementation
│   ├── ParserLogic.h/.cpp # Syntax analysis implementation (parser)
│   └── ...                # Other source and header files
│
├── Rules/
│   ├── 1.1Grammeraftersimple.txt # Full grammar rules for the language
│   ├── 2First.txt                # FIRST sets for parsing
│   ├── 3Follow.txt               # FOLLOW sets for parsing
│   └── ...                       # Other parsing resources
│
└── README.md
```

---

## Contributing

Contributions are welcome! If you'd like to improve the grammar, fix bugs, or extend the functionality:

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Submit a pull request describing your changes.

For questions or suggestions, please open an issue.
