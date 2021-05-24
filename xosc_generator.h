#ifndef _XOSC_GENERATOR_
#define _XOSC_GENERATOR_
#include "common.h"
#include "tinyxml2.h"
#include "Actor.h"
#include "Environment.h"
#include "StopTrigger.h"
#include "Story.h"
#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;
// using namespace tinyxml2;

// static XMLElement* newStopConditionElement(XMLDocument *doc, const char *name, const char *pararef = NULL, const char *value = NULL);
// static XMLElement* newConditionElement(XMLDocument *doc, Condition *condition);

class XOSC {
private:
	const char *savepath;
	tinyxml2::XMLDocument *doc;
	tinyxml2::XMLElement *OpenSCENARIO;
	int   	actornum;
	vector<Actor> actorlist;
	Environment environment;
	Story story;
	StopTrigger stopTrigger;
	bool saveflag;
public:
	XOSC();
	XOSC(const char *filepath);
	~XOSC();
	void 	initXML();
	void 	cleanall();
	SETRES 	setFilename(const char *file);
	SETRES 	setGlobalParaDeclaration(const char *name, const char *type, const char *value);
	SETRES 	setMap(const char *mapname);
	SETRES 	setActorNum(const int num);
	SETRES	setActor(const int n, const Actor *actor);
	SETRES 	setActorName(const int num, const char* name = NULL);
	SETRES 	setEnvironment(const Environment *env);
	SETRES  setStopTrigger(const StopTrigger *trig);
	SETRES  setStory(const Story *s);

	bool	saveXOSC();
	void   	test();
};




#endif

