#!/bin/sh

# set -e

make re


for filename in maps/bad/*.cub; do
    echo "TESTING: $filename"
    valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 --track-fds=yes ./cub3D $filename 2> $filename.log
    if ( cat $filename.log | grep "ERROR SUMMARY: 0 errors" > /dev/null )
    then
        echo "====================================="
    else
        echo "ALERTE YA UN PB NOOOOOOOOON !"
        cat $filename.log
        exit 1
    fi 
    # echo "======================================="
done