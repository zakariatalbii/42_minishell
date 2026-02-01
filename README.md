# 🐚 Minishell — A Minimal Unix Shell (42 Project)

**Minishell** is a team project from the **42 Cursus** that consists of building a simplified Unix shell, inspired by **bash**, entirely in **C**.

The goal of this project is to deeply understand how a shell works internally: from reading user input, parsing commands, handling environment variables, to executing programs using system calls.

---

## 🎯 Project Objectives

**Minishell** aims to reproduce the core behavior of a Unix shell while respecting strict constraints:

- Read and interpret user input
- Tokenize and parse commands correctly
- Handle quotes (`'` and `"`)
- Expand environment variables (`$VAR`, `$?`)
- Execute built-in commands
- Execute external programs using `fork` and `execve`
- Support pipes (`|`)
- Support redirections (`<<`, `<`, `>`, `>>`)
- Handle Unix signals (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)

---

## 🧠 Architecture & Workflow

The shell execution flow is divided into clear stages:

1. **Input Reading**
2. **Lexing / Tokenization**
3. **Parsing (AST construction)**
4. **Execution**
5. **Cleanup & Loop**

```
User Input
	↓
Tokenizer
	↓
Parser → Abstract Syntax Tree (AST)
	↓
Executor (fork / exec / pipes / redirections)
	↓
Exit Status
```

Each stage is isolated to keep the codebase readable, testable, and maintainable.

---

## 📂 Project Structure

```
.
├── Makefile
├── libft/				# C utility library
├── include/			# Header file
├── src/
│  ├── minishell.c		# main func
│  ├── parsing/			# Lexer, parser, expander, heredoc
│  ├── execution/		# Command execution, pipes, redirections
│  ├── environ/			# env funcs
│  ├── ft_signals.c		# signals
│  └── utils.c			# utils
└── en.subject.pdf
```

---

## 🔍 Parsing Pipeline (Input → Structure)

Parsing is one of the most critical parts of **Minishell**.  
It transforms raw user input into a structured representation ready for execution.

### 🪜 Parsing stages:

1. **Input reading**
	- Read the command line from the user prompt.

2. **Lexing & Tokenization**
	- Split the input into tokens (words, operators, pipes, redirections).
	- Respect quotes and avoid breaking quoted strings.

3. **Quote handling**
	- Single quotes `'` prevent expansion.
	- Double quotes `"` allow variable expansion.

4. **Expansion**
	- Expand environment variables & exit status (`$VAR`, `$?`).
	- Apply expansion rules depending on quote context.

5. **Parsing**
	- Organize tokens into logical command structures.
	- Identify commands, arguments, pipes, and redirections.
	- Build structured nodes used by the execution layer.

---

## ⚙️ Execution Pipeline (Structure → Processes)

Once parsing is complete, execution handles the system-level behavior:

- Execution of **built-in commands** without forking when required (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`)
- Execution of external programs using:
	- `fork()`
	- `execve()`
- Pipe creation and file descriptor management
- Input/output redirections
- Heredoc handling
- UNIX signal handling during command execution (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)

---

## 🛠️ Build & Run

### 📋 Requirements
- **Unix-like** system (Linux / macOS)
- `readline` library

### 📦 Build
```bash
# Clone the repository
git clone git@github.com:zakariatalbii/42_minishell.git
cd 42_minishell

# Compile the project
make
```

### ▶️ Run
```bash
./minishell
```

### 📌 Example Usage
```bash
minishell$ echo "Hello Minishell"
Hello Minishell

minishell$ cat << eof
> Hello Minishell
> eof
Hello Minishell

minishell$ cat file.txt > output.txt
```

---

## 🧪 Code Quality & Design Choices

- Modular and readable architecture
- Clear separation between parsing and execution
- State-aware parsing
- Proper memory management
- Behavior aligned with bash (within subject limits)

---

## 📚 What We Learned

- How a shell works internally
- Writing a lexer and parser from scratch
- Process management in Unix
- File descriptor manipulation
- Signal handling
- Team collaboration on a low-level systems project

---

## 🏁 Final Notes
**Minishell** is more than a simple project — it is a deep dive into Unix internals, process control, and parsing logic.
This project laid strong foundations in system programming and software architecture.

---

## 🤝 Team & Contributions

This project was developed as a **group project** by:

### 👤 **Zakaria Talbi**

- GitHub: [@zakariatalbii](https://github.com/zakariatalbii)

**Main responsibility:**
- Input handling
- Tokenization (lexing)
- Syntax parsing and command structuring
- Abstract Syntax Tree (AST) construction
- Quote management
- Environment variable expansion
- Operator precedence (`|`, `<`, `>`, `>>`, `<<`)
- Heredoc parsing
- Memory management for parsing structures

> In short: **the entire parsing pipeline**.

---

### 👤 Wafae Nid Hsain

- GitHub: [@wafae-nid](https://github.com/wafae-nid)

**Main responsibility:**
- Integration with parsing output
- Built-in command execution
- Process creation (`fork`, `execve`)
- Pipes and file descriptor management
- Redirections and heredocs
- Signal handling during execution
- Exit status propagation

> In short: **the entire execution pipeline**.

---

## 📜 License

This project is part of the 42 School cursus.

---

✨ *Minishell is not about writing a shell — it's about understanding how one works.*