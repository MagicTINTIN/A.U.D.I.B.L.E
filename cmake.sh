#!/usr/bin/bash
projectname="Audible"

makearg=""
cmakearg=""
for arg in "$@"; do
        
    if [ "$arg" = "--release" ]; then
        cmakearg+=" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=\"-O3\" "
    elif [ "$arg" = "--debug" ]; then
        cmakearg+=" -DCMAKE_BUILD_TYPE=Debug "
    elif [ "$arg" = "--fastcomile" ]; then
        makearg+=" -j4 "
    elif [ "$arg" = "--reset" ]; then
        rm -rf build/*
    fi
done

mkdir build 2>/dev/null
cd build/

cmake $cmakearg ../sources
if [[ $? != 0 ]]; then
    err=$?
    echo -ne "$(tput setaf 9)"
    echo "Compilation of $projectname went wrong.$(tput sgr0)"
    cd ../
    exit $err
fi
make $makearg
if [[ $? != 0 ]]; then
    err=$?
    echo -ne "$(tput setaf 9)"
    echo "Compilation of $projectname went wrong.$(tput sgr0)"
    cd ../
    exit $err
elif [[ $? == 0 ]]; then
    echo "$(tput setaf 2)$(tput bold)Compilation of $projectname finished.$(tput sgr0)
    Execute $projectname++ with build/$projectname"
fi

cd ../
echo -ne "$(tput sgr0)"
