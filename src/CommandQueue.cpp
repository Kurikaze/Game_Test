/***********************************************************************************
 * CommandQueue.cpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Implementation file for class CommandQueue.
 ************************************************************************************/


#include "include/CommandQueue.hpp"

void CommandQueue::push(const Command& command)
{
    mQueue.push(command);
}

Command CommandQueue::pop()
{
    Command command = mQueue.front();

    mQueue.pop();

    return command;
}

bool CommandQueue::isEmpty() const
{
    return mQueue.empty();
}
