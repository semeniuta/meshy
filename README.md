# meshy

C++ library for mesh files processing. 

Format of a binary STL file:

```
char[80] – Header
char[4]  – Number of triangles (unsigned long)

foreach triangle
    char[12] – Normal vector (float[3])
    char[12] – Vertex 1 (float[3])
    char[12] – Vertex 2 (float[3])
    char[12] – Vertex 3 (float[3])
    char[2]  – Attribute byte count (short)
end 
```

To use `conda` Python when building:

```bash
cmake -DPYTHON_LIBRARY=$CONDA_PREFIX/lib/libpython3.6m.dylib -DPYTHON_EXECUTABLE=$CONDA_PREFIX/bin/python ..
```

