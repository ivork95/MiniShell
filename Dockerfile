FROM ubuntu:latest

RUN apt-get update && \
    apt-get install vim \
                    libcriterion-dev \
                    gcc \
                    make \
                    clang \
                    valgrind \
                    -y && \
    apt-get clean && rm -rf /var/lib/apt/lists/*