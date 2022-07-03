#/bin/sh

cmake_conda() {

    if [ -z $CONDA_PREFIX ]
    then
        echo 'CONDA_PREFIX was not defined'
        CONDA_PREFIX=$(dirname $(dirname $(which python)))
        echo "CONDA_PREFIX is set to $CONDA_PREFIX"
    else
        echo "CONDA_PREFIX is $CONDA_PREFIX"
    fi

    PY_LIB=$(ls $CONDA_PREFIX/lib/libpython*.dylib)
    echo "Python library is at $PY_LIB"

    cmake -DPYTHON_LIBRARY=$PY_LIB -DPYTHON_EXECUTABLE=$CONDA_PREFIX/bin/python ..

} 

if [[ $(which conda) ]]
then
    echo "conda is present"
    cmake_conda

else
    echo "conda is absent"
    cmake ..
fi
