#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

struct Point { int x, y; };
std::vector<Point> P;
std::vector<Point> CH; //ConvexHull

class Jarvis
{
  public:
    bool compare(Point a, Point b);
    int cross (Point o, Point a, Point b);
    int length2(Point a, Point b);
    bool far(Point o, Point a, Point b);
    void March();
};

bool Jarvis::compare(Point a, Point b)
{
  return (a.y < b.y) || (a.y == b.y && a.x < b.x);
}

//if > 0 : counterclockwise
int Jarvis::cross(Point o, Point a, Point b)
{
  return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

int Jarvis::length2(Point a, Point b)
{
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool Jarvis::far(Point o, Point a, Point b)
{
  return length2(o, a) > length2(o, b);
}

void Jarvis::March()
{
  //find first point
  int start = 0;
  for(int i = 0; i < P.size(); i++)
  {
    if(compare(P[i], P[start]))
      start = i;
  }

  int m = 0; //count ConvexHull tops
  CH.push_back(P[start]);
  //CH[m] = P[start]; //record start

  //start ConvexHull
  int current = start;
  for(m = 1; true; m++)
  {
    //find next ConvexHull point:
    //1. find outermost point
    //2. if there have collinear, find far one
    
    int next = current;
    for(int i = 0; i < P.size(); i++)
    {
      int c = cross(CH[m-1], P[i], P[next]);
      if(c > 0 || c == 0 && far(CH[m-1], P[i], P[next]))
        next = i;
    }

    if(next == start) 
      break;

    //CH[m] = P[next]; //record found ConvexHull point
    CH.push_back(P[next]);
    current = next; //go next point
  }
}

class Graham
{
  public:
    static int cross(Point o, Point a, Point b);
    static int length2(Point a, Point b);
    static bool compare_position(Point a, Point b);
    static bool compare_angle(Point a, Point b);
    static bool closest(Point o, Point a, Point b);
    int Scan();
};

int Graham::cross(Point o, Point a, Point b)
{
  return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

bool Graham::compare_position(Point a, Point b)
{
  return (a.y < b.y) || (a.y == b.y && a.x < b.x);
}

bool Graham::compare_angle(Point a, Point b)
{
  int c = cross(P[0], a, b); //P[0] as center
  return c > 0 || (c == 0 && closest(P[0], a, b));
}

int Graham::length2(Point a, Point b)
{
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool Graham::closest(Point o, Point a, Point b)
{
  return length2(o, a) < length2(o, b);
}

int Graham::Scan()
{
  //bool (Graham::* comp) (Point, Point) = &Graham::compare_position;
  
  //far left point as start, center point place to index 0
  std::swap(P[0], *std::min_element(P.begin(), P.end(), this->compare_position));

  //other points sort with angle
  std::sort(P.begin() + 1, P.end(), this->compare_angle);

  //center point as start point, counterclockwise.
  //convenient to wrap the last point
  P.push_back(P[0]);
  
  int m = 0; //ConvexHull tops amount
  for(int i = 0; i < P.size(); i++)
  {
    //clean angle < 180° cross
    while(m >= 2 && cross(CH[m-2], CH[m-1], P[i]) <= 0) m--;

    //add new point
    CH[m++] = P[i];
  }
  m--; //last point is recurring point start, so ignore
  return m;
}

int main()
{
  P.clear();
  CH.clear();

  P.push_back({220, 60});
  P.push_back({340, 80});
  P.push_back({220, 200});
  P.push_back({400, 260});
  P.push_back({440, 140});
  P.push_back({460, 40});
  P.push_back({560, 120});
  P.push_back({600, 240});
  P.push_back({500, 180});
  P.push_back({800, 60});

  Jarvis J;
  J.March();

  for(int i = 0; i < CH.size(); i++)
  {
    std::cout << "Point " << i+1 << ": " << CH[i].x << " " << CH[i].y << std::endl;
  }

  std::cout << std::endl;
  CH.clear();
  CH.assign(P.begin(), P.end());

  Graham G;
  int m = G.Scan();

  for(int i = 0; i < m; i++)
  {
    std::cout << "Point " << i+1 << ": " << CH[i].x << " " << CH[i].y << std::endl;
  }

  return 0;
}
