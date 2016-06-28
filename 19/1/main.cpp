#include <iostream>
#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <map>
#include <set>

#include <vector>
#include <array>

struct Point {
  Point(int x, int y) : x(x), y(y) {}
  int x;
  int y;
  bool operator< (const Point& other) const {
    return y < other.y || (y == other.y && x < other.x);
  }
  Point operator+ (const Point& other) {
    return Point(x + other.x, y + other.y);
  }
};

struct classcomp {
  bool operator() (const Point& lhs, const Point& rhs) const
  {return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x);}
};

struct Cell {
  Cell(Point p, bool isWall) : p(p), isWall(isWall) {}
  Point p;
  bool isWall;
};

bool IsReacheable(std::map<Point, Cell> mazeMap, Point& a, Point& b, std::set<Point, classcomp>& checked)
{
  std::map<Point, Cell>::iterator cell = mazeMap.find(a);
  if (cell == mazeMap.end() || cell->second.isWall || checked.find(a) != checked.end()) {
    return false;
  }
  if (a.x == b.x && a.y == b.y) {
    return true;
  }
  checked.emplace(a);

  Point shifted[4] = { a + Point(1,0), a + Point(0,1), a + Point(-1, 0), a + Point(0, -1)};

  for (int i = 0; i < 4; ++i) {
    std::map<Point, Cell>::iterator next = mazeMap.find(shifted[i]);
    if (next != mazeMap.end() && IsReacheable(mazeMap, next->second.p, b, checked)) {
      return true;
    }
  }

//  std::cout << "deadend (" << a.x << "," << a.y << ")" << std::endl;
  return false;
}

//////////

typedef enum { WHITE, BLACK } Color;

struct Coordinate {
  bool operator==(const Coordinate& that) const {
    return x == that.x && y == that.y;
  }
  int x, y;
};

using std::vector;

//forward declaration
bool SearchMazeHelper(const Coordinate& cur, const Coordinate& e,
                      vector<vector<Color>>* maze, vector<Coordinate>* path);
bool IsFeasible(const Coordinate& cur, const vector<vector<Color>>& maze);


vector<Coordinate> SearchMaze(vector<vector<Color>> maze, const Coordinate& s, const Coordinate& e) {
  vector<Coordinate> path;
  if (maze[s.y][s.x] == BLACK) {
    return path;
  }

  maze[s.y][s.x] = BLACK; // paint it black
  path.emplace_back(s); // add the node s (as a candidate of tail of path)
  if (!SearchMazeHelper(s, e, &maze, &path)) { // helper function may emplace nodes into path
    path.pop_back(); // cancel it (remove the node s from the path)
  }
  return path; // empty path means no path from s to e
}

bool SearchMazeHelper(const Coordinate& cur, const Coordinate& e,
                      vector<vector<Color>>* maze, vector<Coordinate>* path) {

  if (cur == e) {
    return true;
  }
  const std::array<std::array<int, 2>, 4> kShift = {{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}};
  for (auto& s : kShift) {
    Coordinate next{cur.x + s[0], cur.y + s[1]};
    if (IsFeasible(next, *maze)) {
      (*maze)[next.y][next.x] = BLACK;
      path->emplace_back(next);
      if (SearchMazeHelper(next, e, maze, path)) {
        return true;
      }
      path->pop_back();
    }
  }
  return false;
}

bool IsFeasible(const Coordinate& cur, const vector<vector<Color>>& maze) {
  return cur.y >= 0 && cur.y < maze.size() && cur.x >= 0 && cur.x < maze[cur.y].size() &&
         maze[cur.y][cur.x] == WHITE;
}



/////////////

int main(int argc, char* argv[])
{
  static int wx = 10, wy = 10;
  int mapSource[wx][wy];
  std::map<Point, Cell> mazeMap;
  vector<vector<Color>> maze;
  for (int y = 0; y < wy; ++y) {
    vector<Color> X;
    for (int x = 0; x < wx; ++x) {
      int r = (rand() % 5) / 3 ;

      std::cout << r << " ";

      Point p(x, y);
      Cell c(p, r);
      mazeMap.insert(std::pair<Point, Cell>(p, c));

      X.emplace_back((r == 1) ? BLACK : WHITE);
    }
    maze.emplace_back(X);
    std::cout << std::endl;
  }

  for (int sy = 0; sy < wy; ++sy) {
    for (int sx = 0; sx < wx; ++sx) {
      Point start(sx, sy);
      Coordinate s{sx, sy};
      for (int ey = 0; ey < wy; ++ey) {
        for (int ex = 0; ex < wx; ++ex) {
          std::set<Point, classcomp> checked;

          Point end(ex, ey);
          Coordinate e{ex, ey};

          bool res1 = IsReacheable(mazeMap, start, end, checked);
          int res2 = SearchMaze(maze, s, e).size();
//          if (res2 > wx) {
//            std::cout << "s(" << sx << "," << sy << "), e(" << ex << "," << ey << ")  " << res1 << ", " << res2 << std::endl;
//          }
          assert(res1 == (res2 > 0));
        }
      }
    }
  }
  std::cout << "test passed - two algorithms showed same results" << std::endl;

  return 0;
}
