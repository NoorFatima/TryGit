//
//  GameTimer.cpp
//  SchoolSafety
//
//  Created by Noor Fatima on 7/10/17.
//
//

#include "GameTimer.h"
int GameTimer::timerTypeValue;

GameTimer* GameTimer::create(TimerType value)
{
	timerTypeValue = static_cast<int>(value);
	
    GameTimer *node = new (std::nothrow)GameTimer();
    if(node && node->init())
    {
        node->autorelease();
        return node;
    }
    
    CC_SAFE_DELETE(node);
    return nullptr;
}


bool GameTimer::init()
{
	visibleSize = HelperNode::getSize();
	visibleSize.width = 1920; //design resolution width
	visibleSize.height = 1080; // design resolution height
	
	timerLabelBackground = Sprite::create(TIMER_BACKGROUND);
	this->addChild(timerLabelBackground);
	timerLabelBackground->setPosition(Vec2(visibleSize.width/2, visibleSize.height - 100));
	HelperNode::rescale(timerLabelBackground);

	timerLabel = Label::createWithTTF("0:00", "fonts/arial.ttf", 50);
	timerLabelBackground->addChild(timerLabel);
	timerLabel->setPosition(Vec2(timerLabelBackground->getContentSize().width/2 - 20, timerLabelBackground->getContentSize().height/2 + 10));
	timerLabel->setColor(Color3B::BLACK);
	timerLabel->enableBold();
	HelperNode::rescale(timerLabel);
	timerValue = 0;
	timeComplete = false;
	

	
	
	if(timerTypeValue == 0 )
	{
		secondsValue = 0;
	}
	else if(timerTypeValue == 1)
	{
		secondsValue = 29;
	}
    return true;
}

void GameTimer::startTimer()
{
	//this->schedule(schedule_selector(GameTimer::updateTimer), 0.1);

}

void GameTimer::startForwardTimer()
{
	this->schedule(schedule_selector(GameTimer::updateForwardTimer), 0.1);

}

void GameTimer::startReverseTimer()
{
	this->schedule(schedule_selector(GameTimer::updateReverseTimer), 0.1);
}

void GameTimer::updateForwardTimer(float dt)
{
	if(timerValue == 10)
	{
		timerValue = 0;
		secondsValue = secondsValue + 1;
		
	}
	timerValue = timerValue + 1;
	totalTimeValue = totalTimeValue + 1;
	char c[32];
	sprintf(c, "%d", secondsValue);
	v = static_cast<std::string>(c);
	v.append(":");
	char d[32];
	sprintf(d, "%d", timerValue);
	std::string w = static_cast<std::string>(d);
	if(timerValue <= 9)
		v.append("0");
	v.append(w);
	timerLabel->setString(v);


}
std::string GameTimer::getTimerStringValue()
{
	return v;
}
void GameTimer::updateReverseTimer(float dt)
{
	if(timerValue == 10)
	{
		timerValue = 0;
		secondsValue = secondsValue - 1;
		
	}
	if(secondsValue == 0 )
			timeComplete = true;
	
	timerValue = timerValue + 1;
	
	char c[32];
	sprintf(c, "%d", secondsValue);
	//timerLabel->setString(c);
	std::string v = static_cast<std::string>(c);
	v.append(":");
	char d[32];
	sprintf(d, "%d", timerValue);
	std::string w = static_cast<std::string>(d);
	if(timerValue <= 9)
		v.append("0");
	v.append(w);
	timerLabel->setString(v);
	

	
}


//void GameTimer::updateTimer(float dt)
//{
//	if(timerValue == 10)
//	{
//		timerValue = 0;
//		secondsValue = secondsValue + 1;
//		
//	}
//	timerValue = timerValue + 1;
//	
//	char c[32];
//	sprintf(c, "%d", secondsValue);
//	//timerLabel->setString(c);
//	std::string v = static_cast<std::string>(c);
//	v.append(":");
//	char d[32];
//	sprintf(d, "%d", timerValue);
//	std::string w = static_cast<std::string>(d);
//	if(timerValue <= 9)
//		v.append("0");
//	v.append(w);
//	timerLabel->setString(v);
//	
//	
//	if(secondsValue > 29)
//		timeComplete = true;
//}


bool GameTimer::isTimeComplete()
{
	return timeComplete;
}


void GameTimer::stopTimer()
{
		this->unschedule(schedule_selector(GameTimer::updateReverseTimer));
		this->unschedule(schedule_selector(GameTimer::updateForwardTimer));
}
void GameTimer::resetAll()
{
	timerValue = 0;
	secondsValue = 0;
	timeComplete = false;
}
