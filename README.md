# MiniShell

Bouw image genaamd ubuntu-c-dev op basis van Dockerfile:
```bash
docker build -t  ubuntu-c-dev .
```

Draai container op basis van image genaamd  ubuntu-c-dev met mounted eigen folder:
```bash
docker run --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -it --rm --init -v "$PWD:/pwd"  ubuntu-c-dev sh -c "cd /pwd; bash"
```
--cap-add=SYS_PTRACE --security-opt seccomp=unconfined = nodig om lldb te kunnen runnen in container
-i = interactive so bash doesn’t immediately quit because there is no input\
-t = bash shows prompt\
--rm = delete container on exit to not waste space\
-v = mounts specific folder from host to Docker container\
--init = shiieet snap het nut niet, maar Noah gebruikt het\
-c = CPU shares (relative weight) ???\
sh = ?

Run code met readline in Ubuntu:
```bash
gcc code.c -L/usr/local/lib -I/usr/local/include -lreadline
```

show current frame - f

cat < README.md | cat > outfile2 < Makefile

TODO:
	-echo ?$
	-trowh error when quotes not closed
	-echo 'hallo '$PATH' '
	-<< a < Makefile cat
	-<<a echo hallo | cat
	-  << a < Makefile < Dockerfile cat > outfile
	-find newline when exeec $NOT-EXIST
    -echo builtin -nnn flag
	- echo ?$ geeft een leak van 100 bytes aan omdat de args[1] pointer naar "?$" door expander word overschreven met een pointer naar "0"
	- check if cuotes closed
	- unlink filename when signaled
	-
> << a cat
> ctrl-c
> exit

> heredoc zonder command