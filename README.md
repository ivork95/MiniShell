Bouw image genaamd test op basis van Dockerfile:
```
docker build -t test .
```

Draai container op basis van image genaamd test:
```
docker run -it --rm test
```

Draai container op basis van image genaamd test met mounted eigen folder
docker run -it --rm --init -v "$PWD:/pwd" test sh -c "cd /pwd; bash"


-i = interactive so bash doesn’t immediately quit because there is no input
-t = bash shows prompt
--rm = delete container on exit to not waste space
-v = mounts specific folder from host to Docker container
--init = shiieet snap het nut niet, maar Noah gebruikt het
-c = CPU shares (relative weight) ???
sh = ?
