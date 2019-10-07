Filler:
-----
The aim of Filler project is to create a player program to compete against other other students' bots on the Filles board. The principle is simple: two players take on each other on a board, and take turns placing the piece that the master of the game (```filler_vm```, supplied in the form of a Ruby executable) gives them, earning points. The game stops as soon as a piece can no longer be placed. Little playful project!

How does filler_vm work
-----
Parameters:
* ```-f resources/maps/map[00,01,02]```
There are 3 provided maps in the project:
- ```resourses/maps/map00``` - small map, 14x30 cells
- ```resourses/maps/map01``` - medium map
- ```resourses/maps/map02``` - large map
A map consist:
- '.' characters - empty cells
- 'o' character - the start point of the first player
- 'x' character - the start point of the second player


Unique features:
-----
* [ncurses](http://dkhramov.dp.ua/Comp.NcursesTutorial#.XLBLGpj7RPa) visualizer

![filler](http://g.recordit.co/ExEjAtnKje.gif)

Run the project:
-----

```
git clone **--recursive** https://github.com/olehsamoilenko/Filler.git
cd Filler
make
./resourses/filler_vm -p1 osamoile.filler -p2 resourses/players/other_player.filler -f resourses/maps/map[00,01,02] | ./visualiser/visualiser
```

:green_apple: Works only on **Mac OS**
