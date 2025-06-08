# ShellForge

![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)
![Language: C](https://img.shields.io/badge/Language-C-green.svg)
![Status: Active](https://img.shields.io/badge/Status-Active-brightgreen.svg)
![Last Updated](https://img.shields.io/badge/Last%20Updated-2025--06--08-orange.svg)

A robust and efficient implementation of a Unix shell in C, designed with a focus on modularity, performance, and extensibility.

![ShellForge Shell](https://i.imgur.com/XJ8uR9a.png)

## Overview

ShellForge is a production-grade shell implementation initially built to emulate bash functionality, with ongoing work to extend and customize its capabilities. It offers:

- Command execution with robust argument handling
- Advanced I/O redirection (`|`, `>`, `>>`, `<`, `<<`)
- Environment variable management and expansion
- Logical operation support (`&&`, `||`)
- Comprehensive built-in commands
- Enterprise-grade signal handling
- Detailed error reporting with appropriate exit codes

While the current version maintains compatibility with bash behavior, future development will focus on enhanced features and optimizations that differentiate ShellForge as a unique and powerful shell alternative.

## Dependencies

ShellForge leverages [CLibKit](https://github.com/ssive7b/CLibKit) for core utility functions. The library is integrated as a Git submodule.

## Architecture

ShellForge implements a pipeline architecture that emphasizes clean separation of concerns and optimal performance:

### 1. Lexical Analysis Engine

The lexer processes input using a deterministic finite automaton (state machine) approach:

```
Input String → Tokenization → Token Stream
```

This approach provides several advantages:
- Predictable O(n) time complexity for token recognition
- Resilient handling of complex quoting rules
- Extensible design for future syntax enhancements

### 2. Syntactic Parsing Framework

The parser employs a sophisticated algorithm to construct an Abstract Syntax Tree:

```
Token Stream → Syntax Analysis → Abstract Syntax Tree
```

Key innovations include:
- Operator precedence resolution with minimal overhead
- Efficient error detection and recovery mechanisms
- Dynamic command grouping with nested scopes
- Unified handling of all redirection types

### 3. Variable Expansion System

The expander implements context-aware variable resolution:

```
AST with variables → Expansion → Resolved AST
```

Notable features:
- Context-sensitive expansion based on quoting
- Efficient caching of frequently accessed variables
- Special parameter handling with consistent semantics

### 4. Execution Engine

The execution module utilizes a function dispatch table architecture:

```
AST → Command Resolution → Process Creation → Execution
```

This approach delivers:
- O(1) dispatch time for command execution
- Optimized inter-process communication
- Resource-efficient file descriptor management
- Zero-copy execution where possible

## Implementation Highlights

### Function Dispatch Tables

ShellForge implements a highly efficient execution mechanism:

```c
typedef void *(*t_exec_mode)(t_shell *sh, t_anode *node);

typedef struct s_exec_table
{
    t_exec_mode exec_modes[NODE_TYPES_COUNT];
} t_exec_table;
```

This design enables near-constant time command resolution regardless of command complexity.

### Resource Management

The shell implements enterprise-grade resource management:

- Structured cleanup routines to prevent resource leaks
- Optimized memory allocation patterns for frequent operations
- Efficient file descriptor lifecycle management
- Consistent error propagation

### Signal Architecture

ShellForge employs a context-aware signal handling system:

- Mode-specific signal handlers for maximum reliability
- Non-blocking signal processing during critical operations
- Graceful termination support for all execution paths

## Built-in Commands

ShellForge provides a comprehensive set of built-in commands:

| Command | Description |
|---------|-------------|
| `cd` | Directory navigation with path resolution |
| `echo` | Text display with option parsing |
| `env` | Environment variable listing |
| `exit` | Shell termination with status code support |
| `export` | Environment variable definition and management |
| `pwd` | Current working directory reporting |
| `unset` | Environment variable removal |

## Building and Running

### First-time Setup

```bash
# Clone the repository with submodules
git clone --recursive https://github.com/ssive7b/shellforge.git
cd shellforge

# Or, if you've already cloned without --recursive:
git submodule update --init --recursive
```

### Building

```bash
# Compile the project
make

# Run the shell
./shellforge
```

### Usage Examples

```bash
# Basic command execution
./shellforge
> ls -la

# Run a script
./shellforge < script.sh

# Interactive use with pipes and redirections
./shellforge
> cat file.txt | grep pattern > results.txt
```

## Contributing

Contributions are welcome! Feel free to submit pull requests or open issues for bugs, feature requests, or improvements.

When contributing, please ensure you maintain the Git submodule structure by testing with a fresh clone using the `--recursive` flag.

## License

This project is released under the MIT License. See the [LICENSE](LICENSE) file for details.