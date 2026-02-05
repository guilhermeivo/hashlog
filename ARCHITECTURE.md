# Architecture

## Repository Structure

```
.
├── include/
│   src/
│   ├── builtin/
│   ├── core/
│   │   ├── hash.h
│   │   ├── object.h
│   │   └── refs.h
│   ├── objects/
│   │   ├── blob.h
│   │   └── commit.h
│   ├── refs/
│   │   └── thread.h
│   └── main.c
└── Makefile
```

### `builtin/`

All commands used in the project, both low-level and high-level.

### `objects/`

Data saved in the `.hashlog/object/` folder, following the example.

```
object/ee/810cb24b6c085ccab38ff0dcdea763a6ae893198d13f9e9e851fe241bde7d1
```

### `objects/`

Functions that process the data in the `.hashlog/object/` folder:

* blobs
* commits

### `refs/`

Functions that process the data in the `.hashlog/ref/<reference_name>/` folder:

* threads