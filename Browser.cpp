#include "Browser.hpp"
#include <cstdlib>

Stack<int> closedIndexes = Stack<int>();

Browser::Browser() : selected(0), pages(LinkedList<Tab>()) {}

Browser& Browser::operator=(const Browser& br)
{
	if(this != &br)
	{
		pages = br.pages;
		closedPages = br.closedPages;
		selected = new Node<Tab>;
		*selected = *(br.selected);
	}
}

void Browser::open_new_page(const string& url)
{
	Tab t(url);
	pages.insert(&pages.getBack(), t);
	selected = &pages.getBack();
}

void Browser::open_link(const string& url)
{
	if(pages.isEmpty())
	{
		open_new_page(url);
	}
	else
	{
		Tab *t = selected->getDataPtr();
		t->pushPrev(t->getPage());
		t->setPage(url);
		t->clearNext();
	}
}

void Browser::open_link_in_new_tab(const string& url)
{
	Tab t(url);
	pages.insert(selected, t);
	selected = selected->getNext();
}

void Browser::close_tab(int index)
{
	if(index == getTabIndex(selected))
	{
		close_selected_tab();
	}
	else
	{
		closedPages.push((pages.getNodePtrAt(index))->getData());
		pages.eraseFrom(index);
	}
}

void Browser::reopen_closed_tab(int index)
{
	pages.insertAt(index, closedPages.pop());
	selected = pages.getNodePtrAt(index);
}

void Browser::move_tab(int from, int to)
{
	if(from != to)
	{
		Node<Tab>* n = pages.getNodePtrAt(from);
		if(from < to)
		{
	    	pages.insertAt(to + 1, n->getData());
		}
		else
		{
		    pages.insertAt(to , n->getData());
		}
		pages.erase(n);
		selected = pages.getNodePtrAt(to);
	}
}

void Browser::display()
{
	if(selected)
	{
		int pos = getTabIndex(selected);
		cout << "CURRENT TAB: " << pos << endl;
		cout << (selected->getData()).getPage() << endl;
	}
	int countOpenTabs = pages.getSize();
	cout << "OPEN TABS: " << countOpenTabs << endl;
	for (int i = 0; i < countOpenTabs ;i++)
	{
		cout << ((pages.getNodeAt(i)).getData()).getPage() << endl;
	}
	int countClosedTabs = closedPages.getSize();
	cout << "CLOSED TABS: " << countClosedTabs << endl;
	closedPages.print();
}

void Browser::select_tab(int index)
{
	selected = pages.getNodePtrAt(index);
}

void Browser::display_tab_details()
{
	Tab* current = selected->getDataPtr();
	(current->getForwardHistory()).printReversed();
	cout << "> " << current->getPage() << endl;
	(current->getBackHistory()).print();
}

void Browser::close_selected_tab()
{
	Node<Tab>* tmp = selected;
	closedPages.push(selected->getData());
	if(!selected->getNext()) //either only node or last node
	{
		if(!selected->getPrev()) //only node
		{	
			selected = 0;
		}
		else
		{
			selected = selected->getPrev();
		}
	}
	else
	{
		selected = selected->getNext();
	}
	pages.erase(tmp);
}

void Browser::back()
{
	Tab *t = selected->getDataPtr();
	if(!t->getBackHistory().isEmpty())
	{
		string url = t->getPage();
		t->pushNext(url);
		t->setPage(t->popPrev());
	}
}

void Browser::forward()
{
	Tab *t = selected->getDataPtr();
	if(!t->getForwardHistory().isEmpty())
	{
		string url = t->getPage();
		t->pushPrev(url);
		t->setPage(t->popNext());
	}
}

int Browser::getTabIndex(Node<Tab>* node)
{
	Node<Tab>* fr = &pages.getFront();
	if(fr)
	{
		int pos = 0;
		while(fr != node)
		{
			fr = fr->getNext();
			pos++;
		}
		return pos;
	}
	else
	{
		return -1;
	}
}

void Browser::handleTask(string task)
{
	int delimindex = task.find(' ');
	string task_description = task.substr(0, delimindex);
	if(task_description == "open_new_page")
	{
		string url = task.substr(delimindex+1);
		open_new_page(url);
	}
	else if(task_description == "open_link")
	{
		string url = task.substr(delimindex+1);
		open_link(url);
	}
	else if(task_description == "open_link_in_new_tab")
	{
		string url = task.substr(delimindex+1);
		open_link_in_new_tab(url);
	}
	else if(task_description == "close_tab")
	{
		int index = atoi((task.substr(delimindex+1)).c_str());
		close_tab(index);
		closedIndexes.push(index);
	}
	else if(task_description == "reopen_closed_tab")
	{
		reopen_closed_tab(closedIndexes.pop());
	}
	else if(task_description == "move_tab")
	{
		int from = atoi((task.substr(delimindex+1, task.find(' ', delimindex+1) - delimindex - 1)).c_str());
		int to = atoi((task.substr(task.find(' ', delimindex+1)+1)).c_str());
		move_tab(from, to);
	}
	else if(task_description == "display")
	{
		display();
	}
	else if(task_description == "select_tab")
	{
		int index = atoi((task.substr(delimindex+1)).c_str());
		select_tab(index);
	}
	else if(task_description == "display_tab_details")
	{
		display_tab_details();
	}
	else if(task_description == "close_selected_tab")
	{
		closedIndexes.push(getTabIndex(selected));
		close_selected_tab();
	}
	else if(task_description == "back")
	{
		back();
	}
	else if(task_description == "forward")
	{
		forward();
	}
}