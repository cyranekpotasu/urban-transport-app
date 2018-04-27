# Urban Transport App
Application finds path between two tram stops on
the map of Wrocław. Uses 3 different searching
algorithms: BFS, DFS and A*.

Written for AI and algorithms course.

Data acquired from the [website of Wrocław.](https://www.wroclaw.pl/open-data/dataset/przystanki-tramwajowe-i-autobusowe)

## User guide
#### Requirements
* python3
* GCC compatible with C++14

#### Install Python packages
`sudo pip install -r requirements.txt`
#### Build 
```
mkdir build
cd build
cmake ..
make
```

Make sure binary file (UrbanTransportApp) is
in bin/ directory, if not, move it there.

Run app by `python3 app.py`