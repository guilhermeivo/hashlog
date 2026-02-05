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

Functions that process the data in the `.hashlog/object/` folder:

* blobs
* commits

### `refs/`

Functions that process the data in the `.hashlog/ref/<reference_name>/` folder:

* threads