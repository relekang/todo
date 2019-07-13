#!/bin/bash

previous=$(git describe --abbrev=0 | cut -c 2-)
next=$(npm run --silent echo-version)

sed -i '' "s/${previous}/${next}/g" executable/TodoApp.re
git add executable/TodoApp.re
