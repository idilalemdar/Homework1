#ifndef _TAB_H_
#define _TAB_H_

#include <iostream>
#include <string>
#include "Stack.hpp"

using namespace std;

class Tab{

    private:
        string page;
        Stack<string> prevPages;
        Stack<string> nextPages;

    public:
    	Tab();
    	Tab(const string& url);
    	Tab(const Tab& t); //copy constructor
    	Tab& operator=(const Tab& t); // assignment operator
    	void setPage(const string& url);
    	const string& getPage() const;
    	void pushPrev(const string& url);
    	void pushNext(const string& url);
        string popPrev();
        string popNext();
    	void clearNext();
    	const Stack<string>& getForwardHistory() const;
    	const Stack<string>& getBackHistory() const;

    	friend ostream &operator<<(ostream &out, const Tab& t);
};
#endif