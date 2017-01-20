#include "Tab.hpp"

Tab::Tab()
{
	page = string();
	prevPages = Stack<string>();
	nextPages = Stack<string>(); 	
}

Tab::Tab(const string& url) : page(url) 
{
	prevPages = Stack<string>();
	nextPages = Stack<string>(); 
}

Tab::Tab(const Tab& t)
{
	*this = t;
}

Tab& Tab::operator=(const Tab& t)
{
	if(this != &t)
	{
		page = t.page;
		prevPages = t.prevPages;
		nextPages = t.nextPages;
	}
	return *this;
}

void Tab::setPage(const string& url)
{
	page = url;
}

const string& Tab::getPage() const
{
	return page;
}

void Tab::pushPrev(const string& url)
{
	prevPages.push(url);
}

void Tab::pushNext(const string& url)
{
	nextPages.push(url);
}

string Tab::popPrev()
{
	return prevPages.pop();
}

string Tab::popNext()
{
	return nextPages.pop();
}

void Tab::clearNext()
{
	nextPages.clear();
}

const Stack<string>& Tab::getBackHistory() const
{
	return prevPages;
}

const Stack<string>& Tab::getForwardHistory() const
{
	return nextPages;
}

ostream &operator<<(ostream &out, const Tab& t)
{
	out << t.page;
	return out;
}