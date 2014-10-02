#!/bin/bash

if command -v brew; then
  echo "Brew exists"
else
  echo "Homebrew not installed"
  echo "You can get it from http://brew.sh/"
  exit 1
fi

# We probably have homebrew now
brew install libsndfile
brew install glew
