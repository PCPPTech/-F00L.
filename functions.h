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
inline string printSpace(int n) {
  string spaces = "";
  for(int i=0; i<n; i++) {
    spaces += " ";
  }

  return spaces;
}

inline string toPrintBorder(int n) {
  string borders = ""; // concatinate the borders here
  for(int i=0; i<n; i++) {
    borders += "-"; // the concatination part
  }

  return borders; // return it
}

inline string returnPrefix(string filename) {
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

// please work, finding the error here is gonna be such a pain in the ass
// This is a mess but I will document everything

inline bool is_directory(string folderPath, string iterator) {
  return fs::is_directory(fs::path(folderPath) / iterator);
}

inline void doit(vector<string>& array_to_iterate, size_t biggestSize, const string& folderPath, bool printHeader = true){
  if(printHeader && !array_to_iterate.empty()) {
    cout << pink << "ITEMS" << printSpace(biggestSize+2) << "PREFIXES\n+" << toPrintBorder(biggestSize+2) << "+\n" << reset_color;
  }

  for (size_t i = 0; i < array_to_iterate.size(); i++) {
      const string& iterator = array_to_iterate[i];
      int amountOfSpaces = biggestSize - iterator.size();

      cout << pink << "| " << (is_directory(folderPath, iterator) ? blue : reset_color) << iterator << printSpace(amountOfSpaces) << pink << " | " 
          << reset_color << (is_directory(folderPath, iterator) ? "[directory]" : returnPrefix(iterator)) << endl;
  }

  if(!array_to_iterate.empty())
      cout << pink << "+" << toPrintBorder(biggestSize+2) << "+\n" << reset_color;
}

// sorting algorithm (e.g. if the file starts with a dot, then that first)
inline void list_dir(string path) {
  vector<string> folders_withDot, folders, files_withDot, files, inorder;
  for(const auto& entry : fs::directory_iterator(path)) {
    string filename = entry.path().filename().string();
    // first = Folders starting with .
    if (filename.starts_with(".") && fs::is_directory(entry.path()))
      folders_withDot.push_back(filename);

    // second = Ordinary Folders (not starting with .)
    if (fs::is_directory(entry.path()) && !(filename.starts_with(".")))
      folders.push_back(filename);
    
    // third = Files starting with a .
    if (!(fs::is_directory(entry.path())) && filename.starts_with("."))
      files_withDot.push_back(filename);

    // fourth = loser files 😂 (files that doesnt start with a . 😂😂😂)
    if (!(fs::is_directory(entry.path())) && !(filename.starts_with(".")))
      files.push_back(filename);

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

  


  size_t biggestSize = 0;

  // This is gonna be long...
  // but first lets determine the biggest file length of them all
  for (const string& filename : inorder) {
    if (filename.size() > biggestSize){
      biggestSize = filename.size();
    } else {
      //pass
    }
  }
  
  // got it. Now thanks to that information, I can make a more aesthetic design >:3
  
  doit(inorder, biggestSize, path);


}
