#!/usr/bin/bash
projectname="Audible"

makearg=""
cmakearg=""
folder="build"
for arg in "$@"; do
        
    if [ "$arg" = "--release" ]; then
        cmakearg+=" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=\"-O3\" "
    elif [ "$arg" = "--debug" ]; then
        folder="debug"
        cmakearg+=" -DCMAKE_BUILD_TYPE=Debug "
    elif [ "$arg" = "--fastcomile" ]; then
        makearg+=" -j4 "
    elif [ "$arg" = "--reset" ]; then
        rm -rf $folder/*
    fi
done

mkdir $folder 2>/dev/null
cd $folder/

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
else
    echo "$(tput setaf 2)$(tput bold)Compilation of $projectname finished.$(tput sgr0)
Execute $projectname++ with $folder/$projectname"
fi

cd ../
echo -ne "$(tput sgr0)"
