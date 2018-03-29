// FileViewer.cpp

#include "FileViewer.h"

using namespace std;

void FileViewer::display()
{
    const string long_separator(50, '-');
    const string short_separator(8, '-');

    system(clear_command);

    if (!error_message_.empty()) {
        cout << "ERROR: " + error_message_ << endl;
        error_message_.clear();
    }

    if (!string_search_.empty()) {
        cout << string_search_ << endl;
        string_search_.clear();
    }

    string file_name = buffer_.file_name();
    if (file_name.empty())
        cout << "<no file opened>\n";
    else
        cout << file_name << endl;

    cout << long_separator << endl;
    buffer_.display();
    cout << long_separator << endl;
    cout << "  next  previous  search  go  back  open  quit\n";
    cout << short_separator << endl;
}

void FileViewer::execute_command(char command, bool & done)
{
    switch (command) {
        case 'n': {
            buffer_.move_to_next_page();
            break;
        }

        case 's': {
            string search_string;
            cout << "Enter term to search: ";
            getline(cin, search_string);
            string_search_ = buffer_.search_for_string(search_string);
            break;
        }

        case 'o': {
            cout << "file name: ";
            string file_name;
            getline(cin, file_name);
            if (!buffer_.open(file_name))
                error_message_ = "Could not open " + file_name;

            break;
        }

        case 'g': {
            cout << "link number: ";
            int link_number;
            cin >> link_number;
	    if (link_number > buffer_.link_size() || link_number < 1){
            error_message_ = "Invalid link number";
            break;
	    }
            string link = buffer_.link_name(link_number - 1);
            if (!buffer_.open(link))
                error_message_ = "Could not open link [" + to_string(link_number) + "]";
            break;
        }

        case 'b':{
            history_ = buffer_.get_history();
            cout << "History: " << to_string(history_.size()) << endl;
//            for (int i = 0; i< history_.size();i++)
//            {
//                cout << "Number: " << i+1 << ":" << history_[i] << endl;
//            }
//            cin.get();
            history_.pop_back();
            string file_name = history_[history_.size()-1];
            if(!buffer_.open(file_name))
                error_message_ = "Could not open " + file_name;
            break;
        }

        case 'p': {
            buffer_.move_to_previous_page();
            break;
        }

        case 'q': {
            done = true;
            break;
        }
    }
}

void FileViewer::run()
{
    cout << "Window height? ";
    cin >> window_height_;
    cin.get();  // '\n'
    cout << '\n';
    buffer_.set_window_height(window_height_);

    cout << "Window length? ";
    cin >> window_length_;
    cin.get();  // '\n'
    cout << '\n';
    buffer_.set_window_length(window_length_);


    bool done = false;
    while (!done) {
        display();

        cout << "command: ";
        char command;
        cin >> command;
        cin.get(); // '\n'

        execute_command(command, done);

        cout << endl;
    }
}


