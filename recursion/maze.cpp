
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <algorithm>

struct Maze
{
    struct Possibity
    {
        int dx, dy, dist;
    };

    std::vector<std::string> maze;
    std::vector<std::vector<int>> dist;
    int dtime = 10000;
    char wall = '#';
    char empty = ' ';
    char filled = '.';
    char backtrack = 'a';


    Maze(std::string filename)
    {
        load(filename);
    }

    void load(std::string filename)
    {
        // std::fstream in;
        // std::string line;

        // in.open(filename);
        // while (std::getline(in, line))
        // {
        //     maze.push_back(line);
        // }

        std::string line;

        while (std::getline(std::cin, line))
        {
            maze.push_back(line);
        }
        
    }

    static bool possibilityComparator(Possibity a, Possibity b)
    {
        return a.dist < b.dist;
    }
    
    bool solveHelp(int x, int y)
    {
        std::cout << x << ", " << y << std::endl;
        
        char currCell = maze[x][y];

        if (currCell == 'S')
        {
            maze[x][y] = empty;
            currCell = empty;
        }

        if (currCell == 'E')
        {
            maze[x][y] = 'F';
            print();
            usleep(dtime);
            return true;
        }

        if (currCell == wall)
        {
            return false;
        }

        if (currCell == empty)
        {
            // std::cout << maze[x][y+1] << std::endl;
            print();
            usleep(dtime);
            maze[x][y] = filled;

            int deltas[4][2] = {
                {0, 1},
                {0, -1},
                {1, 0},
                {-1, 0}
            };

            std::vector<Possibity> possibilities;

            for (auto d:deltas)
            {
                possibilities.push_back(
                    Possibity{
                        x+d[0], 
                        y+d[1], 
                        dist[x+d[0]][y+d[1]]
                    }
                );
            }


            std::sort(possibilities.begin(), possibilities.end(), possibilityComparator);

            for (auto m:possibilities)
            {
                if (solveHelp(m.dx, m.dy))
                {
                    return true;
                }
                std::cout << m.dx << " " << m.dy << std::endl;
            }





            // if (solveHelp(x, y+1))
            // {
            //     return true;
            // }
            // if (solveHelp(x, y-1))
            // {
            //     return true;
            // }
            // if (solveHelp(x+1, y))
            // {
            //     return true;
            // }
            // if (solveHelp(x-1, y))
            // {
            //     return true;
            // }

            maze[x][y] = backtrack;
            print();
            usleep(dtime);

            return false;

        }


        return false;

    }

    int distance(int x1, int y1, int x2, int y2)
    {
        return std::abs(x2 - x1) + std::abs(y2 - y1);
    }

    void solve()
    {
        int startx, starty;
        int endx, endy;
        for (int x = 0; x < maze.size(); x++)
        {
            for (int y = 0; y < maze[x].size(); y++)
            {
                if (maze[x][y] == 'S')
                {
                    std::cout << "HERE" << std::endl;
                    startx = x;
                    starty = y;
                }
                if (maze[x][y] == 'E')
                {
                    endx = x;
                    endy = y;
                }
            }
        }

        std::vector<int> row;

        for (int x = 0; x < maze.size(); x++)
        {
            for (int y = 0; y < maze[x].size(); y++)
            {
                row.push_back(distance(x, y, endx, endy));
            }
            dist.push_back(row);
            row.clear();
        }


        // for(auto x: dist)
        // {
        //     for (auto y: x)
        //     {
        //         std::cout << y << " ";
        //     }
        //     std::cout << "" << std::endl;
            
        // }
        solveHelp(startx, starty);
    }

    void print()
    {
        std::cout << "\033[2J" << std::endl;
        
        for (auto line: maze)
        {
            for (char x: line)
            {
                if (x == filled)
                {
                    std::cout << "\e[0;37m";
                    std::cout << filled;
                    std::cout << "\e[0m";
                    
                    // std::cout << "\033[48;5;46m\033[38;5;$46m*\033[0m";
                }

                else if (x == backtrack)
                {
                    std::cout << "\e[0;31m";
                    std::cout << filled;
                    std::cout << "\e[0m";   
                }

                else 
                {
                    std::cout << x;
                }
            }
            std::cout << std::endl;
            // std::cout << line << std::endl;
            
        }
    }

};


int main(int argc, char const *argv[])
{
    Maze m("maze.txt");

    m.solve();

    
    // int x = m.distance(7, 8, 10, 3);

    // std::cout << x << std::endl;
    

    return 0;
}