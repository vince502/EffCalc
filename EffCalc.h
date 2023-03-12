#pragma once
#define EFFCALC_H

#include "Reader.h"
//#include "Reader.cc"
#include "TEfficiency.h"
#include "ObjectTree.h"
#include "pset.h"

enum kDtype{
	kMCmuLoose = (unsigned int) 4,
	kMCmu = (unsigned int) 3,
	kMCUp = (unsigned int) 2,
	kMCJP = (unsigned int) 1,
	kData = (unsigned int) 0,
};

using EffMap=std::map<std::string,TEfficiency*>;
using MatchData=std::map<std::pair<string,double>,EventData>;

class EffCalc : public readerHlt, readerOnia, objectTree
{
	public :

		objectTree objT;	
		readerHlt hltData;
		readerOnia oniaData;
		EffCalc() : hltData(), oniaData() {};
		~EffCalc();
		EffCalc( std::string name_file_hlt, std::string name_file_onia, unsigned int feedType = kMCJP );

		void init( bool _getDimu, bool _isL1 );
		void init( std::pair<bool, bool> dp );

		void setTrigger( std::string name_trig, std::string name_base_trig = "" );
		void setTriggerLvl(int lvl);
		bool indexMatched( double iHlt, double iOnia);
		void requestHist( std::string types );
		void eval(int idx);
		void evalHLT(int idx);
		void eval(std::pair<long, long> indexes);
		void eval(int idx, double cut);
		void evalAll(int maxEvents);
		void evalSegment(int startIdx, int endIdx);
		void evalAllHLT(int maxEvents);
		void evalAll(int maxEvents, std::vector<std::pair<long, long> > indexes);
		void mapIndex();
		std::pair<std::string, std::unordered_map<std::string, TEfficiency*> > getEfficiencies();
		void setOniaCustomFilter( std::map<string, std::pair<double, double> > m );
		void setHltCustomMassFilter( std::pair<double, double> m );
		void setHltCustomPtFilter( std::pair<double, double> m );
		
//		void check;
		std::unordered_map<std::string, TEfficiency*> map_eff;
		std::map<bool, std::unordered_map<std::string, TH1D*> >map_hist;
		std::string registered_trigger;
		std::vector<std::pair<long, long> >vec_idx;
//	protected :
	public :
		std::vector<EventData> filterOniaData( std::vector<EventData> oniaCont );
		std::vector<EventData> filterHltData( std::vector<EventData> hltCont, double cut );
		std::vector<EventData> filterHltDataMass( std::vector<EventData> hltCont, double cut );
		std::pair<std::vector<EventData>, std::vector<EventData> > matchedData( std::vector<EventData> onia, std::vector<EventData> hlt , bool sendParcel);
		EffMap generateHist( std::string );
		void fillProjHist( TEfficiency hist_eff, std::string type );
		void fillHist( std::vector<EventData> oniaPass, std::vector<EventData> oniaTotal) ;
		void fillHLTHist( std::vector<EventData> hlt) ;
		void fillDerivedHist( std::vector<EventData> oniaPass, std::vector<EventData>, double cut );
		void fillDerivedMassHist( std::vector<EventData> oniaPass, std::vector<EventData>, double cut );


//	private :
	public :
		TFile* file_output;
//		std::unordered_map<string, bool> map_hlt;
		bool getDimu, isL1;
		int level;
		bool cuthltrange;
		unsigned int dataType;
		double dRcut, dPtcut;
		double hlt_m_low, hlt_m_high;
		double hlt_pt_1 = -1.;
		double hlt_pt_2 = -1.;
		std::string rap;
		std::map<std::string, std::pair<double, double> > map_oniafilter_limit{
			{"m", {0., 999.}},
			{"pt", {0., 999.}},
			{"pt1", {0., 999.}},
			{"pt2", {0., 999.}},
			{"rap", {-2.5, 2.5}},
		};
		friend objectTree;
};
