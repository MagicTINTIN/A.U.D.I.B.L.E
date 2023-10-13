#!/usr/bin/bash
if [[ $# == 0 ]]; then
    echo "You need to indicate the test folder to build"
    exit 1
fi
originalfolder=$(pwd)
relative=$(dirname "$0")
cd $(dirname "$0")
testFolder=$(pwd)
projectname=$1

makearg=""
cmakearg=""
folder="build/$projectname"
for arg in "$@"; do
        
    if [ "$arg" = "--release" ]; then
        cmakearg+=" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=\"-O3\" "
    elif [ "$arg" = "--debug" ]; then
        folder="debug/$projectname"
        cmakearg+=" -DCMAKE_BUILD_TYPE=Debug "
    elif [ "$arg" = "--fastcomile" ]; then
        makearg+=" -j4 "
    elif [ "$arg" = "--reset" ]; then
        rm -rf $folder/$projectname*
    fi
done

mkdir $folder 2>/dev/null
cd $folder/

cmake $cmakearg ../../$projectname
if [[ $? != 0 ]]; then
    err=$?
    echo -ne "$(tput setaf 9)"
    echo "Compilation of $projectname went wrong.$(tput sgr0)"
    cd $originalfolder
    exit $err
fi
make $makearg
if [[ $? != 0 ]]; then
    err=$?
    echo -ne "$(tput setaf 9)"
    echo "Compilation of $projectname went wrong.$(tput sgr0)"
    cd $originalfolder
    exit $err
else
    echo "$(tput setaf 2)$(tput bold)Compilation of $projectname finished.$(tput sgr0)
Execute $projectname++ with $relative/$folder/$projectname"
fi

cd $originalfolder
echo -ne "$(tput sgr0)"