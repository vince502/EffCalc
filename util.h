#pragma once
#define UTILS_H

#include "Reader.h"

namespace Events
{
	EventData reduce(EventData &data, std::string expr);
	std::vector<EventData> reduce( std::vector<EventData> &data, std::string expr);
	double get(EventData &data);
};


enum offlineSelection{
	kSoft = 0,
	kHybridSoft =1,
};