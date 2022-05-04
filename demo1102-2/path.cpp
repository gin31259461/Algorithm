#include <vector>
#include <iostream>

std::vector<std::vector<int>> AD;

class Dijkstra
{
  public:
    void Path(int source);
};

void Dijkstra::Path(int source)
{
  std::vector<int> L(AD.size()), P(AD.size()); //length, parent
  std::vector<bool> V(AD.size()); //visited

  //initialize
  for(int i = 0; i < V.size(); i++)
  {
    V[i] = false;
    L[i] = 1e9;
    P[i] = -1;
  }

  //choose start source
  L[source] = 0;
  P[source] = source;

  //find next minimal length
  for(int k = 0; k < V.size(); k++)
  {
    //a -> b
    int a = -1, b = -1, min = 1e9;
    for(int i = 0; i < V.size(); i++)
    {
      if(!V[i] && L[i] < min)
      {
        a = i;
        min = L[i];
      }
    }

    if(a == -1) //all points are visited
      break;

    V[a] = true; //add new point

    //relaxation a -> b
    for(b = 0; b < V.size(); b++)
    {
      //a -> b-1 : no edge
      if(AD[a][b] == -1)
        continue;

      if(!V[b] && L[a] + AD[a][b] < L[b])
      {
        L[b] = L[a] + AD[a][b];
        P[b] = a;
      }
    }
  }

  //Debug
  for(int c = 0; c < P.size(); c++)
  {
    if(P[c] == c)
      continue;
    std::cout << P[c] << " -> " << c << std::endl;
  }
}

int main()
{
  AD.assign(9, std::vector<int>(9, -1));
  AD[0][1] = 8;
  AD[0][2] = 12;
  AD[1][2] = 13;
  AD[2][6] = 21;
  AD[6][8] = 11;
  AD[7][8] = 9;
  AD[5][7] = 11;
  AD[4][5] = 19;
  AD[4][1] = 9;
  AD[2][3] = 14;
  AD[1][3] = 25;
  AD[3][4] = 20;
  AD[3][5] = 8;
  AD[3][7] = 12;
  AD[3][8] = 16;
  AD[3][6] = 12;

  Dijkstra D;
  D.Path(0);
  std::cout << std::endl;
  D.Path(3);

  return 0;
}
