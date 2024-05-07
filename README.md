# MiniShell
## Overview
MiniShell is a project where we have created our own shell. It provides basic shell functionalities such as executing commands, managing processes, and handling input/output redirection.

### Build Image
To build an image named ubuntu-c-dev based on the provided Dockerfile:

```r
docker build -t ubuntu-c-dev .
```

### Run Container
To run a container based on the ubuntu-c-dev image with your own folder mounted:

```bash
docker run -it --rm --init -v "$PWD:/pwd" ubuntu-c-dev sh -c "cd /pwd; bash"
```
### Usage
To use MiniShell, follow these steps:

Build the Docker image using the provided Dockerfile.

Run a container based on the image, with your folder mounted.

Run make in root folder to compile code.

Run program.

./minishell

### Example

```shell
./minishell
```
