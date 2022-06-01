#pragma once 
#define OBJECTTREE_H

#include "Reader.h"

class objectTree;

struct evtFlatDimu{
	double hpt; double heta; double hphi; TLorentzVector omu1; TLorentzVector omu2; TLorentzVector odmu; double dR1; double dR2; double dPt1; double dPt2; 
};
struct evtFlatSimu{
	double hpt; double heta; double hphi; TLorentzVector omu1; double dR1; double dPt1;
};
struct evtFlatSummary{
	double nevt; double cent; double hpt; double heta; double hphi; double opt1; double opt2; double oeta1; double oeta2; double ophi1; double phi2; double om1; double om2; double dipt; double diy; double diphi; double dim; double dr1; double dr2; double dpt1; double dpt2;
};

class objectTree {
	public :
		objectTree(){};
		void init( std::string _trig, bool _isDimu );
		~objectTree(){};
		void setOniaIndex();
		void setEventWideContent( EventData edat );
		void parcelEntry(evtFlatDimu parcel);
		void parcelEntry(evtFlatSimu parcel);
//		void getOniaFriend();
		void flush();
		void write();
	private :
		int oniaCount =0;
		std::string trig;
		bool isDimu;

		TFile* fout;
		TTree *fullTree, *oniaTree;
		double nevt, cent, hpt, heta, hphi, opt1, opt2, oeta1, oeta2, ophi1, phi2, om1, om2, dipt, diy, diphi, dim, dr1, dr2, dpt1, dpt2;
		std::vector<evtFlatSummary> eventMatrix;
		
};
