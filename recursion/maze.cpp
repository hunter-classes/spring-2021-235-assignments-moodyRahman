
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>

struct Maze
{
    std::vector<std::string> maze;
    int dtime = 10000;
    char wall = '#';
    char empty = ' ';
    char filled = '^';
    char backtrack = 'a';


    Maze(std::string filename)
    {
        load(filename);
    }

    void load(std::string filename)
    {
        std::fstream in;
        std::string line;

        in.open(filename);
        while (std::getline(in, line))
        {
            maze.push_back(line);
        }
        
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

            if (solveHelp(x, y+1))
            {
                return true;
            }
            if (solveHelp(x, y-1))
            {
                return true;
            }
            if (solveHelp(x+1, y))
            {
                return true;
            }
            if (solveHelp(x-1, y))
            {
                return true;
            }

            maze[x][y] = backtrack;
            print();
            usleep(dtime);

            return false;

        }


        return false;

    }

    void solve()
    {
        for (int x = 0; x < maze.size(); x++)
        {
            for (int y = 0; y < maze[x].size(); y++)
            {
                if (maze[x][y] == 'S')
                {
                    std::cout << "HERE" << std::endl;
                    solveHelp(x, y);
                }
            }
        }
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


    return 0;
}