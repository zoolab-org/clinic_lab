
# DEMO for Length Extension Attack (LEA)

## Prerequisite

- GNU make
- docker runtime, e.g., docker.io or Docker Desktop

## Quick Start

### Run the codes

- If the toolchain, libmbedtls (2.x or 3.x), and the required development files are installed natively.

   ```
   make
   ./md5demo
   ```

- Otherwise,

  ```
  make docker-build     # build the lab docker image
  make docker-run       # run the docker image
  (in the docker runtime)
  make
  ./md5demo
  ```

