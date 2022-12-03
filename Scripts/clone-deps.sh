#!/bin/sh

git=$1
repo_dir=$2
repo_url=$3

ping -c 1 -W 1000 google.com
if [ "$$?" -eq 0 ]; then
    if [ -d "${repo_dir}" ]; then
        ${git} -C "${repo_dir}" pull origin main
    else
            ${git} clone ${repo_url}
    fi
fi
