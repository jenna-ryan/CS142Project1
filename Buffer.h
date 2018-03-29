// Buffer.h

#ifndef _Buffer_h_
#define _Buffer_h_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Buffer
{
public:
    void display() const;
    const std::string & file_name() const { return file_name_; }
    std::string search_for_string(const std::string & s);
    void move_to_next_page();
    void move_to_previous_page();
    bool open(const std::string & file_name);
    void set_window_height(int h) { window_height_ = h; }
    void set_window_length(int l) { window_length_ = l; }
    void set_top_line(int tl) {ix_top_line_ = tl;}
    const std::string & link_name(const int number) const { return v_links_[number];}
    const int link_size() const { return v_links_.size();}
    void add_history(const std::string & name) { history_.push_back(name);}
    std::string get_history();


private:
    std::vector<std::string> v_lines_;
    std::vector<std::string> v_links_;
    int ix_top_line_ = 0;
    std::string file_name_;
    int window_height_;
    int window_length_;
    void anchor(std::string & link, std::string & info);
    std::vector <std::string> history_;

};

inline std::string Buffer::get_history()
{
    if(history_.size() <= 1)
            return "";
    history_.pop_back();
    std::string last_element = history_[history_.size()-1];
    return last_element;
}


inline void Buffer::move_to_next_page()
{
    ix_top_line_ += window_height_;
    if (ix_top_line_ >= v_lines_.size())
        ix_top_line_ -= window_height_;
}

inline void Buffer::move_to_previous_page()
{
    ix_top_line_ -= window_height_;
    if (ix_top_line_ < 0)
        ix_top_line_ = 0;
}

#endif
