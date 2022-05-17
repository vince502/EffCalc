#pragma once
#include "utils.h"

EventData Events::reduce(EventData &data, std::string expr){
	auto strings =  parse(expr);
	EventData new_data;
	for( auto item : strings ){
		new_data[item] = data[item];
	}
	return new_data;
};

std::vector<EventData> Events::reduce(std::vector<EventData> &data, std::string expr){
	auto strings =  parse(expr);
	std::vector<EventData> new_data;
	for( auto& cont : data ){
		new_data.push_back(Events::reduce(cont, expr) );
	}
	return new_data;
};

double Events::get(EventData &data, string type){
	return data[type];
};

std::vector<std::string> parse(std::string expr,std::string delim = ":"){
	if(expr.find(delim) == std::string::npos) return std::vector<std::string>{expr.c_str()};
	std::vector<size_t> positions;
	size_t pos = expr.find(delim,0);
	while(pos != std::string::npos){
	  positions.push_back(pos);
	  pos = expr.find(delim, pos+1);
	}
	std::vector<std::string> result_parse;
	size_t front =0;
	for (size_t pos : positions){
	  result_parse.push_back(expr.substr(front,pos-front));
	  front = pos +delim.length();
	}
	result_parse.push_back(expr.substr(front));
	
	return result_parse;

};
