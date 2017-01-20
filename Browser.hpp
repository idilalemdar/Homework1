#ifndef _BROWSER_H_
#define _BROWSER_H_

#include <string>
#include "LinkedList.hpp"
#include "Stack.hpp"
#include "Tab.hpp"

class Browser{

    private:
        Node<Tab>* selected;
        LinkedList<Tab> pages;
        Stack<Tab> closedPages;

    public:

        Browser(); // default constructor
        Browser& operator=(const Browser& br); //assignment operator
        void open_new_page(const string& url);
        void open_link(const string& url);
        void open_link_in_new_tab(const string& url);
        void close_tab(int index);
        void reopen_closed_tab(int index);
        void move_tab(int from, int to);
        void display();
        void select_tab(int index);
        void display_tab_details();
        void close_selected_tab();
        void back();
        void forward();

       	int getTabIndex(Node<Tab>* node);
        void handleTask(string task);
};

#endif