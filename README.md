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

To use `conda` Python when building (repalce `myenv` with the name of your `conda` environment):

```bash
cmake -DPYTHON_LIBRARY=$HOME/miniconda3/envs/myenv/lib/libpython3.6m.dylib -DPYTHON_EXECUTABLE=/$HOME/miniconda3/envs/myenv/bin/python ..
```

