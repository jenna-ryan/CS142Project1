// FileViewer.h

#ifndef _FileViewer_h_
#define _FileViewer_h_

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "Buffer.h"

const char clear_command[] = "cls"; // for Windows
//const char clear_command[] = "clear"; // for Linux and possibly Mac's

class FileViewer
{
public:
    void run();

private:
    void display();
    void execute_command(char command, bool & done);

    Buffer buffer_;
    int window_height_;
///MODIFICATION
    int window_length_;
    std::string error_message_;
    std::string string_search_;
    std::vector <std::string> history_;

};

#endif
