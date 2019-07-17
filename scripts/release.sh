#!/bin/bash 

reset="\033[0m"
bold="\033[1m"
green="\033[32m"
yellow="\033[33m"

if [[ "$1" == "" ]]; then
  echo -e "${green}Usage ./scripts/release <major|minor|patch>${reset}"
  exit 1
fi

esy install

if [[ -n $(git status -s) ]]; then
  echo -e "${yellow}Commit or stash uncommited changes before release.${reset}"
  echo -e "${bold}Changes files:${reset}"
  git status -s
  exit 1
fi


npm version $1
esy release

sed -i '' 's/"TodoApp.exe":/"todo":/g' ./_release/package.json

echo -e "${bold}Released $(git describe --abbrev=0).${reset} Publishing it."

git push --follow-tags origin master 

cd _release
  if [[ "$1" == "pre"* ]]; then
    npm publish --prerelease
  else
    npm publish
  fi
cd -

echo -e "${green}${bold}All done 🚀${reset}"
