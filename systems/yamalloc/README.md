# Yet Another Memory Allocator (Yamalloc)
Implementation of a very simple memory allocator for fun. It compiles to a shared library and you can preload it to use it instead C's standard library's malloc.  
As it is a very naive implementation you can expect segfaults.

## Building the Docker container
```sh
docker build -t yamalloc .
```

## Running the Docker container
You can start an interactive bash session inside the container like this
```sh
docker run -it --rm yamalloc /bin/bash
```

And then run some Linux utilities to test the library is working. E.g.:
```sh
LD_PRELOAD=./malloc.so ls
LD_PRELOAD=./malloc.so top
LD_PRELOAD=./malloc.so mkdir some_folder
```
You should see some output comming from the library besides the additional output of the program. I left this output intentionally for debugging purposes.


