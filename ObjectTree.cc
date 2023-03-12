#pragma once

#include "ObjectTree.h"

void objectTree::init( std::string _trig, bool _isDimu, unsigned int dataType){
	trig = _trig;
	isDimu = _isDimu;
	string subdir = "";
	subdir = string(SUBDIR);
	fout = new TFile(Form("MatchTree/%s/outputMatchTree_%s_SampleType%u_%s_v2.root", subdir.c_str(), trig.c_str(), dataType, file_tag.c_str() ), "recreate");

	fullTree = new TTree("fullTree", "hlt vs. onia full matched tree");
	fullTree->SetAutoSave(-30000);
	oniaTree = new TTree("oniaTree", "per onia entry tree");
	oniaTree->SetAutoSave(-30000);
	
	fullTree->Branch( "evtNb", &nevt, "eventNb/D");
	fullTree->Branch( "cent", &cent, "centrality/D");
	fullTree->Branch( "Ncoll", &nColl, "Ncoll/D");
	fullTree->Branch( "Muidx", &passMu, "Mu Idx/I");
	fullTree->Branch( "oniaN", &oniaN, "OniaN/I");
	fullTree->Branch( "hpt", &hpt, "hlt pt/D");
	fullTree->Branch( "heta", &heta, "hlt eta/D");
	fullTree->Branch( "hphi", &hphi, "hlt phi/D");
	fullTree->Branch( "opt1", &opt1, "onia pt1/D");
	fullTree->Branch( "oeta1", &oeta1, "onia eta 1/D");
	fullTree->Branch( "ophi1", &ophi1, "onia phi 1/D");
	fullTree->Branch( "om1", &om1, "onia mass 1/D");
	fullTree->Branch( "dr1", &dr1, "dR 1/D");
	fullTree->Branch( "dpt1", &dpt1, "dPt 1/D");
	if( isDimu ){
		fullTree->Branch( "opt2", &opt2, "onia pt2/D");
		fullTree->Branch( "oeta2", &oeta2, "onia eta 2/D");
		fullTree->Branch( "ophi2", &ophi2, "onia phi 2/D");
		fullTree->Branch( "om2", &om2, "onia mass 2/D");
		fullTree->Branch( "dipt", &dipt, "dimu pt/D");
		fullTree->Branch( "diy", &diy, "dimu y/D");
		fullTree->Branch( "diphi", &diphi, "dimu phi/D");
		fullTree->Branch( "dim", &dim, "dimu m/D");
		fullTree->Branch( "dr2", &dr2, "dR 2/D");
		fullTree->Branch( "dpt2", &dpt2, "dPt 2/D");
	}

	oniaTree->Branch( "evtNb", &nevt, "eventNb/D");
	oniaTree->Branch( "cent", &cent, "centrality/D");
	oniaTree->Branch( "Muidx", &passMu, "Mu Idx/I");
	oniaTree->Branch( "Ncoll", &nColl, "Ncoll/D");
	oniaTree->Branch( "hpt1", &hpt1, "hlt pt/D");
	oniaTree->Branch( "heta1", &heta1, "hlt eta/D");
	oniaTree->Branch( "hphi1", &hphi1, "hlt phi/D");
	oniaTree->Branch( "opt1", &opt1, "onia pt1/D");
	oniaTree->Branch( "oeta1", &oeta1, "onia eta 1/D");
	oniaTree->Branch( "ophi1", &ophi1, "onia phi 1/D");
	oniaTree->Branch( "om1", &om1, "onia mass 1/D");
	oniaTree->Branch( "dr1", &tdr1, "dR 1/D");
	oniaTree->Branch( "dpt1", &tdpt1, "dPt 1/D");
	if( isDimu ){
		oniaTree->Branch( "hpt2", &hpt2, "hlt pt/D");
		oniaTree->Branch( "heta2", &heta2, "hlt eta/D");
		oniaTree->Branch( "hphi2", &hphi2, "hlt phi/D");
		oniaTree->Branch( "opt2", &opt2, "onia pt2/D");
		oniaTree->Branch( "oeta2", &oeta2, "onia eta 2/D");
		oniaTree->Branch( "ophi2", &ophi2, "onia phi 2/D");
		oniaTree->Branch( "om2", &om2, "onia mass 2/D");
		oniaTree->Branch( "dipt", &dipt, "dimu pt/D");
		oniaTree->Branch( "diy", &diy, "dimu y/D");
		oniaTree->Branch( "diphi", &diphi, "dimu phi/D");
		oniaTree->Branch( "dim", &dim, "dimu m/D");
		oniaTree->Branch( "dr2", &tdr2, "dR 2/D");
		oniaTree->Branch( "dpt2", &tdpt2, "dPt 2/D");
	}


};

void objectTree::setTag(string tag){
	file_tag = tag;
};

void objectTree::setOniaIndex(){
	oniaCount ++;
};

void objectTree::setEventWideContent( EventData edat){
	cent = edat["Centrality"].val;
	nColl = findNcoll(cent);
	nevt = edat["eventNb"].val;
};

void objectTree::parcelEntry( evtFlatDimu parcel ){
	eventMatrix.push_back( evtFlatSummary{nevt, cent, parcel.hpt, parcel.heta, parcel.hphi, parcel.omu1.Pt(), parcel.omu2.Pt(), parcel.omu1.Eta(), parcel.omu2.Eta(), parcel.omu1.Phi(), parcel.omu2.Phi(), parcel.omu1.M(), parcel.omu2.M(), parcel.odmu.Pt(), parcel.odmu.Rapidity(), parcel.odmu.Phi(), parcel.odmu.M(), parcel.dR1, parcel.dR2, parcel.dPt1, parcel.dPt2, parcel.passMu, oniaCount} ); 

};

void objectTree::parcelEntry( evtFlatSimu parcel ){
	eventMatrix.push_back( evtFlatSummary{nevt, cent, parcel.hpt, parcel.heta, parcel.hphi, parcel.omu1.Pt(), 0, parcel.omu1.Eta(),0,  parcel.omu1.Phi(), 0,  parcel.omu1.M(), 0,0,0,0,0, parcel.dR1, -1, parcel.dPt1, -1, parcel.passMu, oniaCount} );
};


void objectTree::flush(){
	evtCount++;
	bool hasGoodHLT; 
	bool getNext;
	tdr1 = 10;
	tdr2 = 10;
	tdpt1 = 10;
	tdpt2 = 10;
	auto evt = eventMatrix.begin();
	while( evt != eventMatrix.end()){
		oniaN =  (*evt).oniaN;
		if( tdr1 > (*evt).dr1 ){
			tdr1 = (*evt).dr1;
			tdpt1 = (*evt).dpt1;
			hpt1 = (*evt).hpt;
			heta1 = (*evt).heta;
			hphi1 = (*evt).hphi;
		}

		hpt = (*evt).hpt;
		heta = (*evt).heta;
		hphi = (*evt).hphi;
		opt1 = (*evt).opt1;
		oeta1 = (*evt).oeta1;
		ophi1 = (*evt).ophi1;
		om1 = (*evt).om1;
		if( isDimu ){
			if( tdr2 > (*evt).dr2 ){
				tdr2 = (*evt).dr2;
				tdpt2 = (*evt).dpt2;
				hpt2 = (*evt).hpt;
				heta2 = (*evt).heta;
				hphi2 = (*evt).hphi;
			}
			dr2 = (*evt).dr2;
			dpt2 = (*evt).dpt2;
			opt2 = (*evt).opt2;
			oeta2 = (*evt).oeta2;
			ophi2 = (*evt).ophi2;
			om2 = (*evt).om2;
			dipt = (*evt).dipt;
			diy = (*evt).diy;
			diphi = (*evt).diphi;
			dim = (*evt).dim;
		}
		dr1 = (*evt).dr1;
		dpt1 = (*evt).dpt1;
		passMu = (*evt).passMu;
		fullTree->Fill();
		auto kit = evt;
		auto kit2 = evt;
		kit++; kit2++;
		if(   (((*kit).oniaN) !=oniaN) || (kit2 == eventMatrix.end()) ){
			oniaTree->Fill();
		}
		evt++;
	}
	eventMatrix.clear();
	oniaCount = 0;
    if (evtCount%5000 == 1){
        std::cout << "Passing event " << evtCount << std::endl;
    	if (evtCount%20000 == 1){
    	    fullTree->AutoSave("SaveSelf");
    	    oniaTree->AutoSave("SaveSelf");
    	    std::cout << "AutoSaving until event " << evtCount << std::endl;
    	}
	}
};


void objectTree::write(){
	fout->cd();
	fullTree->Write();
	oniaTree->Write();
	fout->Close();
};
