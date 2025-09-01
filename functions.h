#pragma once
#include <iostream>
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <vector>
#include <string>
#include "ansii_colorcodes.h"
using namespace std;
namespace fs = filesystem;
// The function below me is for printing out the ascii art at the beginning
inline void printFOOL() {
    cout << green << R"(
        /$$    /$$$$$$$$ /$$$$$$   /$$$$$$  /$$        (version 1.0.0)   
      /$$$$$$ | $$_____//$$$_  $$ /$$$_  $$| $$      
     /$$__  $$| $$     | $$$$\ $$| $$$$\ $$| $$      
    | $$  \__/| $$$$$  | $$ $$ $$| $$ $$ $$| $$      
    |  $$$$$$ | $$__/  | $$\ $$$$| $$\ $$$$| $$      
     \____  $$| $$     | $$ \ $$$| $$ \ $$$| $$      
     /$$  \ $$| $$     |  $$$$$$/|  $$$$$$/| $$$$$$$$
    |  $$$$$$/|__/      \______/  \______/ |________/
     \_  $$_/                                        
       \__/                                          
                                                 
    )" << reset_color << endl;
}

//? functions for commands and other stuff.

// This function below me is to lowerize strings, because C++ doesn't have a built in function so I have to make it myself ;-;
inline string lowerize(string text) {
  transform(text.begin(), text.end(), text.begin(), ::tolower);
  return text;
}


// This function below me is to print out the help menu
inline void printHelpMenu() {
    // list of commands
    cout << green << "\nhelp, --help" << reset_color << " - " << "displays this menu. Duh" << endl;
    cout << green << "ls, ls [DIR] (optional)" << reset_color << " - " << "list every file/folder in the current or given directory." << endl;
    cout << green << "exit, quit" << reset_color << " - " << "Terminates the running of $F00L." << endl;
    cout << green << "clear, cls" << reset_color << " - " << "Clears terminal's screen." << endl;
    cout << green << "output [TEXT]" << reset_color << " - " << "prints out the text you give." << endl;
    cout << green << "pwd" << reset_color << " - " << "outputs your currently working directory." << endl;
    cout << green << "cd {directory}" << reset_color << " - " << "change your currently working directory to another one." << endl;
    cout << green << "touch {file_name}" << reset_color << " - " << "create a file with the given name & prefix." << endl;
    cout << green << "rm {file_name}" << reset_color << " - " << "remove an existing file with the given name. (if doesn't already exist.)" << endl;
    cout << green << "mkdir {dir_name}" << reset_color << " - " << "create a directory with the given name. (if doesn't already exist.)" << endl;
    cout << green << "deldir {dir_name}" << reset_color << "- " << "deletes a directory with the given name. Asks you again if folder isn't empty.\n" << endl;

}

inline void clearScreen() {
    cout << "\033[2J\033[H"; // this is the ANSII color code to clear the screen + move cursor to the top left of the screen.
    //                          (yeah, chatgpt told me the color code. Im not a genie that can memorise some gibberish like that lmao)
}
inline string printSpace(int n) { // this function just prints space as `n` times. I'll need it soon, dont worry
  string spaces = ""; // empty string first
  for(int i=0; i<n; i++) { // n times
    spaces += " "; // concatinate " " (space) to the empty string.
  }

  return spaces; // return it.
}

inline string toPrintBorder(int n) { // prints the border (I used the minus sign for it) n times (without newline)
  string borders = ""; // concatinate the borders here (empty string, similar to the printSpace function)
  for(int i=0; i<n; i++) { // iterate thru n times
    borders += "-"; // the concatination part
  }

  return borders; // return our long border string. This will be useful once again, I promise
}

inline string returnPrefix(string filename) { // This function finds the prefix of given filenames. (e.g. script.py -> .py)
  size_t pos = filename.find_last_of("."); // find the last dot
  if (pos != 0 && pos != std::string::npos) {
    return "[" + filename.substr(pos) + "]";
  } else if(pos == std::string::npos) {
    return "[FILE]";
  } else {
    return "";
  }
}
//* holy this is a mess... only i can navigate thru this LOL
//* my code is getting insanely repetitive, however I believe that as my knowledge of the C++ programming language expands, so will my
//* approach options.


inline bool is_directory(string folderPath, string iterator) { // only used it 2 times, but it was repeating so I decided to make it a function.
  return fs::is_directory(fs::path(folderPath) / iterator);   // Returns a boolean value, depending on whether the combined paths are a directory or not.
}

inline void doit(vector<string>& array_to_iterate, size_t biggestSize, const string& folderPath, bool printHeader = true){ // Print files in the directory
  if(printHeader && !array_to_iterate.empty()) { // if printHeader is true and the array to iterate is not empty
    cout << pink << "ITEMS" << printSpace(biggestSize+2) << "PREFIXES\n+" << toPrintBorder(biggestSize+2) << "+\n" << reset_color;
  // print the top text & border too. (+ sign is the corner, since using special characters causes an error for some particular reason.)
  }

  for (size_t i = 0; i < array_to_iterate.size(); i++) { // iterate thru the array
      const string& iterator = array_to_iterate[i]; // set our iterator as... the wordy iterator
      int amountOfSpaces = biggestSize - iterator.size(); // calculate the amount of spaces I need

      cout << pink << "| " << (is_directory(folderPath, iterator) ? blue : reset_color) << iterator << printSpace(amountOfSpaces) << pink << " | " 
          << reset_color << (is_directory(folderPath, iterator) ? "[directory]" : returnPrefix(iterator)) << endl;
      // and then print the rest of the files that is in the given array to iterate array along with the border ascii art
      // (We later on pass in an array where we added the contains of a given/current path's items.)
  }

  if(!array_to_iterate.empty()) // If the array to iterate is empty
      cout << pink << "+" << toPrintBorder(biggestSize+2) << "+\n" << reset_color; // then print the last border.
}

// listing algorithm
inline void list_dir(string path) {
  vector<string> folders_withDot, folders, files_withDot, files, inorder; // creating every list where we will store certain stuff in 1 line
  for(const auto& entry : fs::directory_iterator(path)) { // iterate thru the given path
    string filename = entry.path().filename().string(); // This is our readable filename
    // first = Folders starting with .
    if (filename.starts_with(".") && fs::is_directory(entry.path())) // if it starts with a dot and is a directory
      folders_withDot.push_back(filename);                           // then it belongs in the folder_withDot string vector.

    // second = Ordinary Folders (not starting with .)
    if (fs::is_directory(entry.path()) && !(filename.starts_with("."))) // if it is a directory and it doesn't start with a dot
      folders.push_back(filename);                                      // then it belongs in the normal folders string vector
    
    // third = Files starting with a .
    if (!(fs::is_directory(entry.path())) && filename.starts_with(".")) // if it isn't a directory but does start with a dot
      files_withDot.push_back(filename);                                // then it belongs in the files_withDot string vector

    // fourth = files that dont start with a dot.
    if (!(fs::is_directory(entry.path())) && !(filename.starts_with("."))) // if it isn't a directory and it doesnt start with a dot
      files.push_back(filename);                                           // then it belongs in the normal files string vector.

    // iterate thru each one... this is gonna be so so so slow...
    // idk how to iterate thru 4 arrays in 1 for loop without knowing their length for sure
  }


  // inorder, adding everything inorder into the inorder vector string
  
  for(const string& element : folders_withDot)
    inorder.push_back(element);

  for(const string& element : folders)
    inorder.push_back(element);

  for(const string& element : files_withDot)
    inorder.push_back(element);

  for(const string& element : files)
    inorder.push_back(element);

  


  size_t biggestSize = 0; // using `size_t` because we can't know it's size

  for (const string& filename : inorder) { // iterate thru the list that contains everything INORDER
    if (filename.size() > biggestSize){ // if the iterator (filename) is bigger than the "biggest"Size
      biggestSize = filename.size(); // then set the iterator (filename) AS the biggest size
    } else { // if it isn't bigger that biggestSize
      // just pass
    }
  }
  
  // got it. Now thanks to that information, I can make a more aesthetic design >:3
  
  doit(inorder, biggestSize, path); // As previously mentioned, our doit's "array_to_iterate" here is "inorder".
  // where it's already sorted out, so no need to worry about that. I do think that our sorting algorithm for "inorder"
  // is kinda repetitive, I am looking for alternatives in the moment.



}

// replacing algorithm since c++ doesn't have one as far as i'm concerned
// so i need to write a new one
inline string replaceChar(string stringToReplace, char whatToReplace, char replaceWith) {
  for(char& c : stringToReplace) {
    if (c == whatToReplace) {
      c = replaceWith;
    }
  }
  return stringToReplace;
}