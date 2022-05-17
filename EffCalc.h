#pragma once
#define EFFCALC_H

#include "Reader.h"
//#include "Reader.cc"
#include "TEfficiency.h"
#include "pset.h"

using EffMap=std::map<std::string,TEfficiency*>;
using MatchData=std::map<std::pair<string,double>,EventData>;

class EffCalc : public readerHlt, readerOnia
{
	public :

		readerHlt hltData;
		readerOnia oniaData;
		EffCalc() : hltData(), oniaData() {};
		~EffCalc();
		EffCalc( std::string name_file_hlt, std::string name_file_onia );

		void init( bool _getDimu, bool _isL1 );
		void init( std::pair<bool, bool> dp );

		void setTrigger( std::string name_trig, std::string name_base_trig = "" );
//		void setTrigger( std::vector<std::string> v_trigs );
		EffMap generateHist( std::string );
		bool indexMatched( double iHlt, double iOnia);
		std::vector<EventData> filterOniaData( std::vector<EventData> oniaCont );
		std::vector<EventData> filterHltData( std::vector<EventData> hltCont, double cut );
		std::pair<std::vector<EventData>, std::vector<EventData> > matchedData( std::vector<EventData> onia, std::vector<EventData> hlt );
		void requestHist( std::string types );
		void fillProjHist( TEfficiency hist_eff, std::string type );
		void fillHist( std::vector<EventData> oniaPass, std::vector<EventData> oniaTotal) ;
		void fillDerivedHist( std::vector<EventData> oniaPass, std::vector<EventData>, double cut );
		void eval(int idx);
		void evalAll(int maxEvents);
		std::pair<std::string, std::unordered_map<std::string, TEfficiency*> > getEfficiencies();
//		void writeOutput();
		
//		void check;
		std::unordered_map<std::string, TEfficiency*> map_eff;
		std::string registered_trigger;
	protected :

	private :
		TFile* file_output;
//		std::unordered_map<string, bool> map_hlt;


		bool getDimu, isL1;
		std::string rap;
};
