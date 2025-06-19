//
//  main.cpp
//  CS300 THE1
//
//  Created by KORHAN ERDOĞDU on 3.11.2023.
//

//Korhan Erdoğdu 30838

/*
       * Deep copy.
       */

/*
 
 
 Sığ Kopya (Shallow Copy): Sığ kopya, bir nesnenin tüm veri elemanlarını kopyalar, ancak referans türü veri elemanları için yeni bir kopya oluşturmaz. Bunun yerine, referanslar aynı bellek adresine işaret eder. Bu, orijinal nesnenin ve kopyanın aynı nesnelere işaret ettiği anlamına gelir. Bu durumda, bir nesnenin değiştirilmesi, diğerini etkileyebilir.

 Derin Kopya (Deep Copy): Derin kopya ise, bir nesnenin tüm içeriğini ve iç içe geçmiş tüm veri elemanlarını da kopyalar. Bu, referans türü veri elemanları için yeni bir kopya oluşturur. Yani, her iki nesne birbirinden bağımsız olur ve birinde yapılan değişiklik, diğerini etkilemez.


 */


#include <iostream>
#include <vector>
#include "linkedlist.h"
#include <fstream>
#include <string>
#include "randgen.h"

#include <random>

using namespace std;


/*
 C++ dilinde bir linked list veya stack içinde bir struct yapısı kullanabilirsiniz.
 
 vector<vector<mazeCell>> maze(M,vector<mazeCell>(N)); bu kod ne yapar
 Örneğin, M = 3 ve N = 4 olduğunu varsayarsak, 3 satır ve 4 sütundan oluşan bir labirent oluşturulacaktır. Her hücre, mazeCell yapısından bir öğeyi temsil eder. Bu şekilde, iki boyutlu bir vektör, labirentin bir matrisini temsil eder.

 Her bir hücrenin mazeCell yapısının içinde, duvarlarını, ziyaret durumunu ve diğer özelliklerini takip etmek için değişkenler bulunur.
 
 
 */


struct cell

{
    int down = 1;  // wall generated at the bottom of the cell
    int up = 1;  // wall generated at the top of the cell
    int right = 1;  // wall generated at the right of the cell
    int left = 1;  // wall generated at the left of the cell
    
    
    bool visited = false; // for cheching whether the cell is visited or not.
    bool visitedpath = false;  // while creatimng the path, after creating the maze.
    
    int x; //storing the cordinates
    int y;
    
};




bool knockdownleft(vector<vector<cell> > & maze, cell & node){
    
    bool are_there_any_cell = true;
    
    if((node.x - 1) < 0){   // if this happens, we are out of the maze.
        are_there_any_cell = false;
        
    }
    

    
    if(node.left != 0 && maze[node.x - 1][node.y].visited == false && are_there_any_cell == true ){  // first parameter checks whether there is a wall or not at the left, and the second parameter checks the left cell is visited or not because if it is visited we do not have to knock down the wall
        
        maze[node.x][node.y].left = 0; // our current cell's left wall is now destructed.
        maze[node.x-1][node.y].visited = true; // it is now visited.
        maze[node.x-1][node.y].right  = 0; // the left cell's right wall is also automatically destructed.
        
        return true;  // we boke the left wall of the cell
        
    }
    
    else {
        
        return false;
            
    }
    
}


bool knockdownright(vector<vector<cell> > & maze, cell & node , int row){
    
    
    bool are_there_any_cell = true;
    
    if((node.x + 1) > row ){   // if this happens, we are out of the maze.
        are_there_any_cell = false;
        
    }
    
    if(node.right != 0 && maze[node.x + 1][node.y].visited == false && are_there_any_cell == true){  // first parameter checks whether there is a wall or not at the right, and the second parameter checks the right cell is visited or not because if it is visited we do not have to knock down the wall
        
        
        maze[node.x][node.y].right = 0; // our current cell's right wall is now destructed.
        maze[node.x + 1][node.y].visited = true; // it is now visited.
        maze[node.x + 1][node.y].left  = 0; // the right cell's left wall is also automatically destructed.
        
        return true;  // we boke the right wall of the cell
        

    }
    
    else {
        
        return false;
        
    }
    
   
}


bool knockdownup(vector<vector<cell> > & maze, cell & node, int column){
    
    
    bool are_there_any_cell = true;
    
    if((node.y + 1) > column){   // if this happens, we are out of the maze.
        are_there_any_cell = false;
        
    }
    
    if(node.up != 0 && maze[node.x][node.y + 1 ].visited == false && are_there_any_cell == true){  // first parameter checks whether there is a wall or not at the top, and the second parameter checks the top cell is visited or not because if it is visited we do not have to knock down the wall
        
        
        maze[node.x][node.y].up = 0; // our current cell's top wall is now destructed.
        maze[node.x][node.y + 1].visited = true; // it is now visited.
        maze[node.x][node.y + 1].down  = 0; // the top cell's bottom wall is also automatically destructed.
        
        return true;  // we boke the top wall of the cell
        

    }
    
    else {
        
        
        return false;
        
    }
    

}


bool knockdowndown(vector<vector<cell> > & maze, cell & node){
    
    
    bool are_there_any_cell = true;
    
    if((node.y - 1) < 0){   // if this happens, we are out of the maze.
        are_there_any_cell = false;
        
    }
    
    
    if(node.down != 0 && maze[node.x][node.y - 1].visited == false && are_there_any_cell == true){  // first parameter checks whether there is a wall or not at the bottom, and the second parameter checks the bottom cell is visited or not because if it is visited we do not have to knock down the wall
        
        
        maze[node.x][node.y].down = 0; // our current cell's bottom wall is now destructed.
        maze[node.x][node.y - 1].visited = true; // it is now visited.
        maze[node.x][node.y - 1].up  = 0; // the bottom cell's up wall is also automatically destructed.
        
        
        return true;  // we boke the left wall of the cell

    }
    
    else {
        
        return false;
        
    }
    

}


void knockdownrandom(vector<vector< cell > > & maze, Stack<cell> ourstack , cell & node, int row, int column){  // first parameter holds the all cells. We will add the cells into the stack respectively. If this function returns true, then we understand that random wall is destructed.
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 4);
    int randomnumber= dis(gen);
    
    
    if (randomnumber == 1 ){  // if the left wall is going to be destructed
        
        
        if(knockdownleft(maze, node) == true){  // if we can break the left wall
            node = maze[node.x - 1][node.y];  // we updated the node.
            ourstack.push(maze[node.x][node.y]);  // we are adding that cell to the stack.
            
            
          
            
        }
    
        
    }
    
    else if(randomnumber == 2){  // if the right wall is going to be destructed
        

        if(knockdownright(maze, node , row) == true){  // if we can break the right wall
            node = maze[node.x + 1][node.y];  // we updated the node.
            
            ourstack.push(maze[node.x][node.y]);  // we are adding that cell to the stack.
           

        }
        
    }
    
    else if(randomnumber == 3){  // if the top wall is going to be destructed
        

        
        if(knockdownup(maze, node , column) == true){  // if we can break the top wall
            node = maze[node.x][node.y + 1];  // we updated the node.
            ourstack.push(maze[node.x][node.y]);  // we are adding that cell to the stack.
            

        }
        
    }
    
    
    
    else if(randomnumber == 4){   // if the bottom wall is going to be destructed
        
        if(knockdowndown(maze, node) == true){  // if we can break the bottom wall
            node = maze[node.x][node.y - 1];  // we updated the node.
            ourstack.push(maze[node.x][node.y]);  // we are adding that cell to the stack.
            

        }
        
        
    }
    
    
    
    
    

}

void PrintStackReverse(Stack<cell> & stack, ofstream & print)
{
    // Use a temporary stack to reverse the order
    Stack<cell> tempStack;

    while (!stack.isEmpty()) {
        cell k;
        stack.pop(k);
        tempStack.push(k);
    }
    
    // Printing the elements in the reversed order
    while (!tempStack.isEmpty()) {
        cell k;
        tempStack.pop(k);

        // Convert coordinates to the requested structure
        print << k.x << " " << k.y << endl;
    }
}


int main(){
    
    
    vector<vector<vector<cell>>> fourmazes;
    
    cout << "Enter the number of mazes:" << endl;
    
    int K;
    int M;
    int N;
    
    cout << "Enter the number of mazes: ";
    cin >> K;
    
    cout << "Enter the number of rows and columns (M and N): ";
    cin >> M >> N ;
    
    
    
    
    for(int m = 1; m <= K; m ++ ){  // for generating K number of mazes.
        
        vector<vector<cell> > maze(M,vector<cell>(N)); // creates a vector has M rows and N columns with all walls.

        
        
        for(int i = 0 ; i < M ; i ++){
        
            for(int j = 0; j < N ; j ++){
                
                maze[i][j].x = i;   // we are creating the coordinates. Each node has a coordinate
                maze[i][j].y = j;
                
                
                
            }
        }
        
        
        fourmazes.push_back(maze); // we are creating 4 mazes, this will be useful for us when solving the maze.
        
        
        
        Stack<cell> mystack;
        cell first_cell =  maze[0][0];
        cell temp = maze[0][0];
        first_cell.visited = true;
        
        mystack.push(first_cell); // we are pushing the first cell into the stack, which has (0,0) coordinates.
        
        
        
       
        
        
        int cellcheck = M * N;  // Untill M*N  visited cell, the function will execute.
        int current_cell = 1;  // since we alredy pushed the bottom left cell to the stack.
        
        
        
        
        while(current_cell <= cellcheck){   // we are creaating the maze with the wals destructed randomly.
            
            knockdownrandom(maze, mystack, first_cell, M, N);  // Might be void. The parameters will be updated.
            
            if(first_cell.x != temp.x && first_cell.y != temp.y){  // if the cells are not equal means that we succesfully broke the wall and added the new cell to the stack.
                current_cell += 1;  // updating the cell. Moving on the other cell. Such as we modev to the second cell, which means current_cell is 2.
            }
            
                    
        }
        
        
    
        ofstream out;
        string filename = "maze_" + to_string(m) + ".txt";
        out.open(filename.c_str());
        out << maze.size() << " " << maze[0].size() << endl;  // we are writing to the file.
        
        
        
        
        
        for (int x = 0; x < maze.size(); x++)
        {
            for (int y = 0; y < maze[0].size(); y++)
            {
                out << "x=" << y  << " y=" << x << " l=" << maze[y][x].left << " r=" << maze[y][x].right << " u=" << maze[y][x].up << " d=" << maze[y][x].down << endl;
            }
           
            
        }
        
        
        
        
        out.close(); //closing the file
        
    }
    
    
    cout << "All mazes are generated." << endl;
    
    
    int choice;
    
    int x1;
    int x2;
    
    int y1;
    int y2;
    
    
    cout << "Enter a maze ID between 1 and " << K << " inclusive to find a path: ";
    cin >> choice;
    cout << endl;
    
    cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
    cin >> x1 >> y1;
    cout << endl;
    cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
    cin >> x2 >> y2;
    cout << endl;
    
    
    
    
    Stack<cell> secondstack;  // for including the cells that shows the route
    
    
    vector<vector<cell> > selected_maze_to_solve;  // this is the maze that we want to find the path of it.
    
    
    selected_maze_to_solve = fourmazes[K]; // selected_maze_to_solve is a 2d vector that represents one of the mazes.
    
    
    cell first_cell_to_be_added = selected_maze_to_solve[x1][x2];
    
    
    cell last_cell_to_be_added = selected_maze_to_solve[x2][y2];
    
    
    // between the first and last cell to be added we should find the path.
    
    
    
    cell searchingcell; // our current cell temp
    
    
    cell previous;
    
    searchingcell = first_cell_to_be_added;
    
    secondstack.push(searchingcell);
    
    
    while(searchingcell.x != last_cell_to_be_added.x && searchingcell.y != last_cell_to_be_added.y){  // (while there are cells to complete the path)
        
        

        // if one of the if conditions can be done, the other if condition will not work.
        
        if (selected_maze_to_solve[searchingcell.x][searchingcell.y].right== 0 && !(previous.x == searchingcell.x+1 && previous.y == searchingcell.y) && !selected_maze_to_solve[searchingcell.x-1][searchingcell.y].visitedpath)
        {
            selected_maze_to_solve[searchingcell.x+1][searchingcell.y].visitedpath = true;
            previous = searchingcell;
            
            searchingcell = selected_maze_to_solve[searchingcell.x+1][searchingcell.y];
            secondstack.push(selected_maze_to_solve[searchingcell.x][searchingcell.y]);
        }
        
        
        else if (selected_maze_to_solve[searchingcell.x][searchingcell.y].left== 0 && !(previous.x == searchingcell.x-1 && previous.y == searchingcell.y) && !selected_maze_to_solve[searchingcell.x-1][searchingcell.y].visitedpath)
        {
            selected_maze_to_solve[searchingcell.x-1][searchingcell.y].visitedpath = true;
            previous = searchingcell;
            searchingcell = selected_maze_to_solve[searchingcell.x-1][searchingcell.y];
            secondstack.push(selected_maze_to_solve[searchingcell.x][searchingcell.y]);
        }
        
        
        else if (selected_maze_to_solve[searchingcell.x][searchingcell.y].up== 0 && !(previous.x == searchingcell.x && previous.y == searchingcell.y +1) && !selected_maze_to_solve[searchingcell.x][searchingcell.y].visitedpath)
        {
            selected_maze_to_solve[searchingcell.x][searchingcell.y + 1].visitedpath = true;
            previous = searchingcell;
            searchingcell = selected_maze_to_solve[searchingcell.x][searchingcell.y + 1];
            secondstack.push(selected_maze_to_solve[searchingcell.x][searchingcell.y]);
        }
        
        
        
        else if (selected_maze_to_solve[searchingcell.x][searchingcell.y].down== 0 && !(previous.x == searchingcell.x && previous.y - 1 == searchingcell.y) && !selected_maze_to_solve[searchingcell.x-1][searchingcell.y].visitedpath)
        {
            selected_maze_to_solve[searchingcell.x][searchingcell.y - 1].visitedpath = true;
            previous = searchingcell;
            searchingcell = selected_maze_to_solve[searchingcell.x][searchingcell.y - 1];
            secondstack.push(selected_maze_to_solve[searchingcell.x][searchingcell.y]);
            
        }
        
    }
    
    
    ofstream print;
    
    
    string filename = "maze_" + to_string(choice) + "_path_" + to_string(x1) + "_" + to_string(y1) + "_" + to_string(x2) + "_" + to_string(y2) + ".txt"; //set the filename
    
    print.open(filename.c_str());
        

    PrintStackReverse(secondstack, print); //reversely output it from the stack
    
    print.close(); //closing the output file
    return 0;
    
    

}

