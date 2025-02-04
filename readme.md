## Warehouse Editor

An editor to make layouts for conveyor belts in a warehouse. Made with C++, ImGui [~~and OpenGL~~](https://github.com/boi-one/WarehouseEditor3D)

---

### How to build:

1. install cmake

2. create a new directory in the root called `build`

3. go to the build directory in the commandline and type `cmake ..`

---

### TODO:
- [x] camera
    - [x] position
    - [x] zoom
    - [x] move
        - [ ] with mouse
- [x] conveyor
    - [x] edit path
    - [x] connect conveyors
    - [x] selectable
    - [x] delete
    - [x] move with mouse
- [x] layers
    - [x] connect between layers
    - [x] show layers
    - [x] delete layers
    - [x] reorder layers
        - [ ] drag and drop
- [x] saving and loading to json
- [ ] convenience
    - [x] 2d grid
    - [x] snap to grid
    ###### after refactor:
    - [ ] copy paste
    - [ ] undo  redo
- [x] create a 3d view in pure opengl: [repository link](https://github.com/boi-one/WarehouseEditor3D)
