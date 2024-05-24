### Available options

Minishell can execute programs using absolute, relative, or environment paths (like /bin/ls or ls), and can handle arguments or options. Single ``(')`` and double ``(")`` quotes function similarly to bash, except for multiline commands.

Our Shell handle redirections ``(>, >>, <)`` and pipes ``(|)``. like in Bash.

Environment variables, such as ``$HOME``, are supported, along with the return code special variable ``$?``.

Additionally, you can interrupt a program with ``Ctrl-C``, quit with ``Ctrl-\``, and send an ``EOF`` with ``Ctrl-D``, just like in bash.

Some functions are built-in, meaning they are directly implemented in Minishell rather than calling external executables. These include ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset``, and ``exit``.
