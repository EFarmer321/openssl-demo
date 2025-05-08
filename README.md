A basic demonstration of openssl made for the Computer Networks, reuploaded and rewritten to no longer naively contain certificates in the repository and to work on Windows instead of Linux.

## How to Build

### Requirements

- MSYS2 MINGW64. Below dependencies should be installed with the terminal:
    - Perl
    - Make
    - GCC
    - mingw-w64-x86_64-openssl

### Steps

1. When cloning this repository, use `git clone https://github.com/EFarmer321/openssl-demo.git --recursive` to include the `openssl` submodule.
2. Create a folder named openssl-build inside the openssl folder.
3. Open up MSYS2 MINGW64 and run the following:

```
cd lib/openssl
perl Configure mingw64 no-shared no-asm --prefix=$(realpath ../openssl-build)
make -j$(nproc)
make install
cd ../..
```

Now in the repository, run `make all` to produce the necessary exe files.
