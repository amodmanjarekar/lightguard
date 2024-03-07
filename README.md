# Lightguard

Lightguard is visual implementation of the [Art Gallery Problem](https://en.wikipedia.org/wiki/Art_gallery_problem). It uses ray casting to determine the vision of each security guard (point) that you place into a randomly generated polygonal room.

### Folder Structure

```
|──lib/
|  |──raycast.c (provides raycasting functionality)
|──rust/
|──|──src/
|──|──|──helper.rs (to perform array operations for random room generation)
|──main.c
```

### Dependencies

- [Rust](https://rust-lang.org)
- [Raylib](https://raylib.com) (C)

### How to run

1. Build the project with

```console
$ source ./build.sh
```

2. Run the build

```console
$ ./main
```
