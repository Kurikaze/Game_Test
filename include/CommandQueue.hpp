/***********************************************************************************
 * CommandQueue.hpp
 * C++ Final Project - A Certain Side Scrolling Game
 * Vietnamese-German University
 * Authors: Tran Tien Huy, Nguyen Huy Thong - EEIT2015
 ************************************************************************************
 * Description:
 * Queue structure to manage the command (Oldest commands need to be applied first)
 ************************************************************************************/


#ifndef COMMANDQUEUE_HPP_INCLUDED
#define COMMANDQUEUE_HPP_INCLUDED
#include <queue>
#include "include/Command.hpp"

class CommandQueue
{
public:
    void        push(const Command& command); //Push command to the queue
    Command     pop();  //Pop and return the first command (in the front of the queue)
    bool        isEmpty() const; //Return true if queue is empty
private:
    std::queue<Command> mQueue;
};

#endif // COMMANDQUEUE_HPP_INCLUDED
