# boost_serialization_map

A sample to illustrate boost serialize STL map  

# data define:

```c++
struct Position {
    ...
}

struct Drive {
    ...
}

std::map<Position, std::vector<Drive>>
```

# Compile

```shell
$ g++ -std=c++11 -Os -Wall -pedantic -pthread main.cpp -lboost_{system,serialization} && ./a.out
```

# Run

```shell
$ a.out
save map size: 1
save map's value size: 3
load map size: 1
save map's value size: 3
```
