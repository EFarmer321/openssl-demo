A basic demonstration of openssl made for the Computer Networks, reuploaded and rewritten to no longer naively contain certificates in the repository and to work on Windows instead of Linux.

## How to Build

### Requirements

- MSYS2 MINGW64. ?Below dependencies should be installed with the terminal:
- Perl
- Make
- GCC

### Steps

1. When cloning this repository, use `git clone https://github.com/EFarmer321/openssl-demo.git --recursive` to include the `openssl` submodule.
2. Open up MSYS2 MINGW64 and run the following:

```
cd lib/openssl
perl Configure mingw64 no-shared no-asm --prefix=$(realpath../openssl-build)
make -j$(nproc)
make install
cd ../..
```

Running `make`