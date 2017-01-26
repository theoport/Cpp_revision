#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <string>
#include "maze.h"
using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  bool success = get_maze_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }
  
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

bool find_marker(char ch, char** maze, int height, int width, int& row, int& column){
	for (size_t i=0;i<height;i++){
		for (size_t m=0;m<width;m++){
			if (maze[i][m]==ch){
				row=i;
				column=m;
				return true;
			}
		}
	}
	row=-1;
	column=-1;
	return false;
}
bool valid_solution(const char* path, char** maze, int height, int width){
	int row, column;
	assert(find_marker('>',maze,height,width,row,column)); 
	for (size_t i=0;i<strlen(path);i++){
		switch (path[i]){
			case 'E':
				if (iswall(maze[row][column+1]))
					return false;
				else if((column+1)>(width-1))
					return false;
				else{
					column++;
				}
				break;
			case 'W':
				if (iswall(maze[row][column-1]))
					return false;
				else if((column-1)<0)
					return false;
				else{
					column--;
				}
				break;
			case 'S':
				if (iswall(maze[row+1][column]))
					return false;
				else if((row+1)>(height-1))
					return false;
				else{
					row++;
				}
				break;
			case 'N':
				if (iswall(maze[row-1][column]))
					return false;
				else if((row-1)<0)
					return false;
				else{
					row--;
				}
				break;
		}
	}
	return true;
}
bool iswall(char a){
	switch (a){
		case '-':
		case '|':
		case '+':
		case '#':
			return true;
		default:
			return false;
	}
}
const char* find_path(char** maze, int height, int width, char start, char end){
	int row_e,column_e,row_s,column_s;
	assert (find_marker(start,maze,height,width,row_s,column_s));
	assert (find_marker(end,maze,height,width,row_e,column_e));
	char path[512];
	int count(0);
	if (make_path(maze,height,width,row_s,column_s,row_s,column_s,row_e,column_e,path,count))
		return reverse(path,count);
	else
		return "no solution";
}
bool make_path(char** maze, int height, int width, int current_row, int current_column, 
				int row_s, int column_s, int row_e, int column_e, char* path, int& count){
	if (current_row==row_e&&current_column==column_e)
		return true;
	else if(iswall(maze[current_row][current_column]))
		return false;
	else if(out_of_scope(current_row,current_column,height,width))
		return false;
	else if ((isalpha(maze[current_row][current_column])||(maze[current_row][current_column]=='>'))
			&&!(current_row==row_s&&current_column==column_s))
		return false;
	maze[current_row][current_column]='#';
	if (make_path(maze,height,width,current_row+1,current_column,row_s,column_s,row_e,column_e,
		path,count)){
		strcat(path,"S");
		count++;
		return true;
	}
	else if (make_path(maze,height,width,current_row-1,current_column,row_s,column_s,row_e,column_e,
		path,count)){
		strcat(path,"N");
		count++;
		return true;
	}
	else if (make_path(maze,height,width,current_row,current_column+1,row_s,column_s,row_e,column_e,
		path,count)){
		strcat(path,"E");
		count++;
		return true;
	}
	else if (make_path(maze,height,width,current_row,current_column-1,row_s,column_s,row_e,column_e,
		path,count)){
		strcat(path,"W");
		count++;
		return true;
	}
	else{
		maze[current_row][current_column]=' ';
		return false;
	}
}
	
bool out_of_scope(int a, int b, int x, int y){
	return (a<0||a>x||b<0||b>y);
}
char* reverse(char *p,int count){
	char temp[512];
	for (size_t i=0;i<count;i++)
		temp[i]=p[count-(i+1)];
	strcpy(p,temp);
	p[count]='\0';
	return p;
}	
