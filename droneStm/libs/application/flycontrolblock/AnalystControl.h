/*
@author:truonglx
@des:
*/

typedef enum QuadState{
	OFF,
	ON,
	STARTING,
	FLYING,
	HOLDING_ALTITUDE,
	HOLDING_POSITION,
	HOLDING_ALL
}QuadState;

typedef enum FlyAction{
	TURN_OFF,
	TURN_ON,
	START,
	TAKE_OFF,
	HOLD_ALTITUDE,
	HOLD_POSITION,
	HOLD_ALL,
	NOTHING
}FlyAction;


void initAnalystControl(QuadState *quadState);
FlyAction getFlyAction(void);



