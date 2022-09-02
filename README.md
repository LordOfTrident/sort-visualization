<p align="center">
	<h1 align="center">Sort Visualization</h2>
	<p align="center">A sorting algortihms visualization program written in C with SDL2</p>
</p>
<p align="center">
	<a href="./LICENSE">
		<img alt="License" src="https://img.shields.io/badge/license-GPL-blue?color=7aca00"/>
	</a>
	<a href="https://github.com/LordOfTrident/sort-visualization/issues">
		<img alt="Issues" src="https://img.shields.io/github/issues/LordOfTrident/sort-visualization?color=0088ff"/>
	</a>
	<a href="https://github.com/LordOfTrident/sort-visualization/pulls">
		<img alt="GitHub pull requests" src="https://img.shields.io/github/issues-pr/LordOfTrident/sort-visualization?color=0088ff"/>
	</a>
	<br><br><br>
	<img width="450px" src="res/clip.gif"/>
</p>

## Table of contents
* [Introduction](#introduction)
* [Quickstart](#quickstart)
* [Controls](#controls)
* [Bugs](#bugs)
* [Dependencies](#dependencies)
* [Make](#make)

## Introduction
Pretty boring huh. I have written a similar program in C++ with SDL2 before, but the code was very
bad and it was a while ago, so i decided to practice some more and write this.

## Quickstart
```sh
$ make
$ ./bin/app
```

## Controls
| Key  | Action                                        |
| ---- | --------------------------------------------- |
| ESC  | Quit the program or stop the current sorting  |
| R    | Shuffle the list                              |
| B    | Bubblesort                                    |
| Q    | Quicksort                                     |

## Bugs
If you find any bugs, please create an issue and report them.

## Dependencies
- [SDL2](https://www.libsdl.org/)

## Make
Run `make all` to see all the make rules.
