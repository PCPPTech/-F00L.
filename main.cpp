#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string> // for `substr()` and other commands
#include <unordered_map> // It's like a dictionary in python. There is a big difference between `unordered_map` and `map`.
// headers
#include "ansii_colorcodes.h"
#include "functions.h"
namespace fs = std::filesystem;

/*
Hello! Another one of my projects... i will be working on DOIT soon too, but im learning c++ as of right now.
! AI HAS NO PART IN THIS, ALL THE CODE AND FILES WERE WRITTEN BY HAND, BY ME, PCPPTECH(EIDNOXON) !
*/

//? an unordered map of color codes we will use later on, you'll see
std::unordered_map<std::string, std::string> color_codes = {
    {"red", red},
    {"blue", blue},
    {"black", black},
    {"yellow", yellow},
    {"brown", brown},
    {"pink", pink},
    {"purple", purple},
    {"green", green},
    {"light_green", light_green}
};



int main() {
    clearScreen();
    std::cout << "Eidnoxon (PCPPTech), 16/08/2025." << std::endl;
    std::cout << "Welcome\nTo..." << std::endl;
    printFOOL();
    std::cout << "if you have no idea how to use this terminal, use '--help' or 'help'!" << std::endl;
    std::string command;
    std::string cmd;
    std::string user_color = blue;
    std::string ctag_color = green;
    
    
    while(cmd != "exit" || cmd != "quit") {
        std::ifstream file("data/wdcolor.txt"); // read from the saved working directory (current path) color in the terminal.
        if(!file.is_open()) {
            std::cout << yellow << "[WARNING]" << reset_color << " failed to read from data/wdcolor.txt... defaulting blue." << std::endl;
        } else {
            std::string temp;
            std::getline(file, temp);
            user_color = color_codes[temp]; // if this throws an error then the file has definitely been modified manually.
            
        }

        std::ifstream ctagcolor("data/ctagcolor.txt");
        if(!ctagcolor.is_open()) {
            std::cout << yellow << "[WARNING]" << reset_color << " failed to read from data/ctagcolor.txt... defaulting green." << std::endl;
        } else {
            std::string temp;
            std::getline(ctagcolor, temp);
            ctag_color = color_codes[temp];
        }
        
        std::string wd = fs::current_path().string(); // get working directory
        // The working directory variable is inside the while loop so it will update everytime the current_path() is updated
        std::cout << ctag_color << "[CONSOLE] " << user_color << wd << reset_color << red << "-$ " << reset_color; // no endl or \n so the input will be on the same line
        getline(cin, command);
        cmd = lowerize(command);
        // forced to use if / else if since switch only works for integers and stuff not for string :c
        // this coding language is insanely overcomplicated what...
        if (cmd == "help" || cmd == "--help") {                                                                 // help menu
            printHelpMenu();
        } else if (cmd == "pwd") {                                                                              // print working directory
            std::cout << wd << std::endl;
        } else if (cmd == "") {                                                                                 // if "cmd" is left empty
            continue;
        } else if(cmd == "clear" || cmd == "cls") {                                                             // clearing terminal
            clearScreen();
        } else if(cmd == "exit" || cmd == "quit") {                                                             // quit
            std::cout << blue << "[INFO] " << reset_color << "quitting..." << std::endl;
            exit(0); // this function was included in the `cstdlib` library
        } else if(cmd.size() > 6 && cmd.starts_with("output")) {
            std::cout << command.substr(7) << "\n" << std::endl;
        } else if(cmd.size() == 6 && cmd.starts_with("output")) {
            std::cout << "Usage: output {your_message}" << std::endl;
        } else if(cmd.starts_with("ls")) {
            if (cmd.size() > 2) {
                std::string given_directory = command.substr(3); // '3' to not include the space
                list_dir(given_directory);
            } else {
                list_dir(wd);
            }
        } else if(cmd.starts_with("cd")) {
            if (cmd.size() > 2 && command.substr(3) != "") {
                std::string dir = command.substr(3);
                try {
                    fs::current_path(dir);
                } catch (const fs::filesystem_error& e) {
                    std::cout << red << "[ERROR]" << reset_color << " " << e.what() << std::endl;
                }
            } else {
                std::cout << blue << "[INFO]" << reset_color << " Usage: cd {directory} or .. to go back." << std::endl;
            }
        } else if(cmd.starts_with("touch")) {
            if (cmd.size() > 5 && cmd.substr(6) != "") {
                std::string filename = command.substr(6);
                std::ofstream file(filename);
                if (file) {
                    std::cout << light_green << "\n[SUCCESS]" << reset_color << " File '" << filename << "' created successfully!\n" << std::endl;
                } else{
                    std::cout << red << "[ERROR]" << reset_color << " Failed to create file '" << filename << "'." << std::endl;
                }
            } else {
                std::cout << blue << "[INFO]" << reset_color << " Usage: touch {file_name}" << std::endl;
            }
        } else if(cmd.starts_with("rm")) {
            if (cmd.size() > 2 && cmd.substr(3) != "") {
                fs::path fileToRemove = command.substr(3); // path to it / file name (e.g. path/to/yourfile.txt)
                if (fs::remove(fileToRemove)) {
                    std::cout << light_green << "\n[SUCCESS]" << reset_color << " File '" << fileToRemove.string() << "' removed!\n" << std::endl;
                } else {
                    std::cout << red << "'\n[ERROR]" << reset_color << " Couldn't remove file '" << fileToRemove.string() << "'.\n" << std::endl;
                }
            } else {
                std::cout << blue << "[INFO]" << reset_color << " Usage: rm {file_name}" << std::endl;
            }
        } else if(cmd.starts_with("deldir")) { 
            if(cmd.size() > 6 && cmd.substr(7) != "") {
                std::string filename = command.substr(7); // using the variable `command` so it will be case-sensitive.
                if(fs::exists(filename) && fs::is_directory(filename)) {
                    if(fs::is_empty(filename)) {
                        // just error handling
                        if(fs::remove(filename)) {
                            std::cout << light_green << "[SUCCESS]" << reset_color << " Successfully terminated directory '" << filename << "'!" << std::endl;
                        } else {
                            std::cout << red << "[ERROR]" << reset_color << " Failed to terminate directory '" << filename << "'." << std::endl;
                        }
                    } else {
                        std::string useranswer;
                        std::cout << yellow << "[INPUT]" << reset_color << " '" << filename << "' is not empty. Delete anyways? (y/n)";
                        std::getline(std::cin, useranswer);
                        if(lowerize(useranswer) == "y") {
                            fs::remove_all(filename);
                            std::cout << light_green << "[SUCCESS]" << reset_color << " Directory '" << filename << "' has been terminated successfully." << std::endl; 
                        } else {
                            std::cout << blue << "[INFO]" << reset_color << " Terminating process..." << std::endl;
                        }
                    }
                } else {
                    std::cout << red << "[ERROR]" << reset_color << " Given filename was either not a directory or it doesnt exist." << std::endl;
                }
            } else {
                std::cout << blue << "[INFO]" << reset_color << " Usage: deldir {dir_name}." << std::endl;
            }
        } else if(cmd.starts_with("mkdir")) {
            if(cmd.size() > 5 && cmd.substr(6) != "") {
                std::string foldername = command.substr(6);
                if(fs::create_directory(foldername)) {
                    std::cout << light_green << "[SUCCESS]" << reset_color << " Directory '" << foldername << "' created successfully!" << std::endl;
                } else {
                    std::cout << red << "[ERROR]" << reset_color << " Directory '" << foldername << "' already exists." << std::endl;
                }
            } else {
                std::cout << blue << "[INFO]" << reset_color << " Usage: mkdir {directory_name}." << endl;
            }
        } else if(cmd.starts_with("cat")) {
            if(cmd.size() > 3 && cmd.substr(3) != " " || cmd.substr(3) != "") {
                std::string filename = cmd.substr(4);
                std::ifstream file(filename);
                if (!file.is_open()) {
                    std::cout << red << "[ERROR]" << reset_color << " Failed to open file." << std::endl;
                    return 1;
                }

                std::string line;
                std::cout << "\n";
                while(std::getline(file, line)) {
                    std::cout << line << endl;
                }
                std::cout << "\n";

            }
        } else if(cmd.starts_with("color")) { // Lets make a command to make this terminal a little bit customisable.
            if(cmd.size() > 6) { // if there is something after "color"
                std::string color = cmd.substr(6); // get that "thing"
                if(color_codes.count(color) == 1) { // and if that "thing" is in the unordered map (it can only appear once)
                    user_color = color_codes[color]; // then rewrite the variable to the ansii color code of the given color
                    std::ofstream file("data/wdcolor.txt", std::ios::trunc); // open data/wdcolor.txt
                    file << color; // save the data there
                } else {
                    std::cout << "Color code invalid. Please type 'color' to see the color code list." << std::endl;
                    // if it isn't found on the list however, then print this error.
                }
            } else { // else if there is nothing after "color"
                // display the list of available colors
                std::cout << purple << "\nList of available colors:" << std::endl;
                std::cout << blue << "color blue" << std::endl;
                std::cout << red << "color red" << std::endl;
                std::cout << black << "color black" << std::endl;
                std::cout << yellow << "color yellow" << std::endl;
                std::cout << brown << "color brown" << std::endl;
                std::cout << pink << "color pink" << std::endl;
                std::cout << green << "color green" << std::endl;
                std::cout << light_green << "color light_green\n" << reset_color << std::endl;
            }
        } else if(cmd.starts_with("ctagc")) {
            if (cmd.size() > 6) {
                std::string givenColor = cmd.substr(6);
                if (color_codes.count(givenColor) == 1) {
                    ctag_color = color_codes[givenColor];
                    std::ofstream file("data/ctagcolor.txt", std::ios::trunc);
                    if(!file.is_open()) {
                        std::cout << red << "[ERROR]" << reset_color << " Could not open data/ctagcolor.txt; please make sure the file exists in that directory." << std::endl;
                    } else {
                        file << givenColor;
                        file.close();
                    }
                } else {
                    std::cout << red << "[ERROR]" << reset_color << " color '" << givenColor << "' is invalid." << std::endl;
                }
            } else {
                std::cout << purple << "\nList of available colors:" << std::endl;
                std::cout << blue << "color blue" << std::endl;
                std::cout << red << "color red" << std::endl;
                std::cout << black << "color black" << std::endl;
                std::cout << yellow << "color yellow" << std::endl;
                std::cout << brown << "color brown" << std::endl;
                std::cout << pink << "color pink" << std::endl;
                std::cout << green << "color green" << std::endl;
                std::cout << light_green << "color light_green\n" << reset_color << std::endl;
            }
        } else {
            std::string run_this = command + " 2>nul"; // "2>nul" tells windows to not print the error, so mine should print now.
            /*
            if you're wondering, no, my whole terminal isnt just this, my terminal has/will have colorings and a more aesthetic design,
            maybe even a history on what you've typed, we can't know what I will add :3
            */
            int result = std::system(run_this.c_str()); // case-sensitive
            if (result != 0) {
                std::cout << red << "\n[ERROR]" << reset_color << " Command '" << cmd << "' not found.\n" << std::endl; 
            }
        }

    }
    
}