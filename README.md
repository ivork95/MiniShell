Bouw image genaamd ubuntu-c-dev op basis van Dockerfile:
```
docker build -t  ubuntu-c-dev .
```

Draai container op basis van image genaamd  ubuntu-c-dev met mounted eigen folder:
```
docker run -it --rm --init -v "$PWD:/pwd"  ubuntu-c-dev sh -c "cd /pwd; bash"
```

-i = interactive so bash doesn’t immediately quit because there is no input\
-t = bash shows prompt\
--rm = delete container on exit to not waste space\
-v = mounts specific folder from host to Docker container\
--init = shiieet snap het nut niet, maar Noah gebruikt het\
-c = CPU shares (relative weight) ???\
sh = ?

Run code met readline in ubuntu:
```
gcc code.c -L/usr/local/lib -I/usr/local/include -lreadline
```