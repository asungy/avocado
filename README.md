Avocado
===

# Building example
```bash
mkdir build and cd build
cmake -DAVO_BuildTests=ON -DCMAKE_BUILD_TYPE=Debug -GNinja ..
```

# Building metrics (updated on 12-17-2020)
| Build system | Mode    | Build time (seconds) |
| :----------- | :-----: | -------------------: |
| Ninja        | Debug   | 15.11                |
| Ninja        | Release | 23.63                |
| Make -j12    | Debug   | 26.23                |
| Make -j12    | Release | 37.04                |
