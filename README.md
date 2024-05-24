<h1 align="center">
	📟 Minishell 📟
</h1>

## 💡 About the project

> This project is a reproduction of a ``Bash Shell`` in ``C``.

### Features

Minishell can execute programs using absolute, relative, or environment paths (like /bin/ls or ls), and can handle arguments and options. Single ``(')`` and double ``(")`` quotes are behaving similarly to Bash.

Our Shell handle redirections ``(>, >>, <)`` and pipes ``(|)``. like in Bash.

Environment variables, such as ``$HOME``, are supported, along with the return code special variable ``$?``.

Additionally, you can interrupt a program with ``Ctrl-C``, quit with ``Ctrl-\``, and send an ``EOF`` with ``Ctrl-D``, just like in bash.

Some functions are built-in, meaning they are directly implemented in Minishell rather than calling external executables. These include ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset``, and ``exit``.

## 🛠️ Usage

### Requirements

The project is written using the C language and requires the **`gcc` compiler** to run.

### Instructions

**1. Compiling Minishell**

To compile, clone the repository, go to the project directory and run :

```shell
$ git submodule update --init --recursive
$ make
```
**2. Starting the program**

```shell
./minishell
```
Enjoy!

### Credits

This project was developed collaboratively with [Andrii Syvash](https://github.com/redarling).
