#ifndef ACTOR_H
#define ACTOR_H

class Actor
{
public:
	virtual ~Actor(){}
	virtual void update() = 0;
};

#endif