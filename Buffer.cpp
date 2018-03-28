// Buffer.cpp

#include "Buffer.h"

using namespace std;

string Buffer::search_for_string(const string & s)
{
    bool found = 0;
    int idx;
    string not_found_msg = "";

//    int line = ix_top_line_;
    for(int line = ix_top_line_; line < v_lines_.size(); line++)
    {
    //  v_lines_[line] is the line at the moment
        size_t n = v_lines_[line].find(s);
        if (n != string::npos)
        {
            idx = line;
            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        not_found_msg = "ERROR: string \"" + s + "\" was not found";
    }
    else
    {
        ix_top_line_ = idx;
    }

    return not_found_msg;
}

void Buffer::display() const
{
    int ix_stop_line_ = ix_top_line_ + window_height_;
    for (int i = ix_top_line_; i < ix_stop_line_; ++i) {
        if (i < v_lines_.size())
            cout << std::setw(6) << i+1 << "  " << v_lines_[i];
        cout << '\n';
    }
}

bool Buffer::open(const string & new_file_name)
{
    std::ifstream file(new_file_name);
    if (!file)
        return false;

    v_lines_.clear();
    v_links_.clear();
    // Note: the vector is cleared only after we know the file
    // opened successfully.

//    string line;
//    while (getline(file, line))
//        v_lines_.push_back(line);
///READS IN INDIVIDUAL WORDS
    string word;
    string line;
    while(file >> word)
    {

        if (word.size() > window_length_ )
        {
            if(!line.empty())
                v_lines_.push_back(line);
            v_lines_.push_back(word);
            line.clear();

        }
        else
        {
            if(line.size() + word.size() > window_length_)
            {
                    v_lines_.push_back(line);
                    line = word + ' ';
            }
            else if(line.size() + word.size() <= window_length_)
            {
                line = line + word + ' ';
            }
        }
    }

    file_name_ = new_file_name;
    ix_top_line_ = 0;
    return true;
}

void Buffer::anchor(string & line)
{
    	string link;
    	string info;
    	size_t start_anchor = line.find("<a");
    	if (start_anchor != string::npos){
            	size_t end_anchor = line.find(">", start_anchor);
            	if(end_anchor != string::npos){
                    	istringstream anchor_stream(line.substr(start_anchor + 2, end_anchor - start_anchor - 2));
                    	anchor_stream >> link >> info;
                    	anchor_stream >> ws;
                    	if(anchor_stream.eof()){
                            	v_links_.push_back(link);
                            	line.replace(start_anchor + 1, end_anchor - start_anchor, info + ">" + "[" + to_string(v_links_.size()) + "]");
                    	}
            	}
    	}
}

