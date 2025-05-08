A basic demonstration of openssl made for the Computer Networks, reuploaded and rewritten to no longer naively contain certificates in the repository and to work on Windows instead of Linux.

## How to Build

### Requirements

- MSYS2 MINGW64. Below dependencies should be installed with the terminal:
    - Make
    - GCC
    - mingw-w64-x86_64-openssl

### Steps

1. When cloning this repository, use `git clone https://github.com/EFarmer321/openssl-demo.git` to include the `openssl` submodule.
2. Generate a self-certificate named `server.crt` and a private key `server.pem`. Here's an example: `openssl req -newkey rsa:2048 -out server.crt -keyout server.pem -days 365 -nodes -x509`

Now in the repository, run `make all` to produce the necessary exe files.
