#pragma once

#include "ObjectTree.h"

void objectTree::init( std::string _trig, bool _isDimu){
	trig = _trig;
	isDimu = _isDimu;
	fout = new TFile(Form("outputMatchTree_%s.root", trig.c_str() ), "recreate");
	fullTree = new TTree("fullTree", "hlt vs. onia full matched tree");
	oniaTree = new TTree("oniaTree", "per onia entry tree");
	
	fullTree->Branch( "evtNb", &nevt, "eventNb/D");
	fullTree->Branch( "cent", &cent, "centrality/D");
	fullTree->Branch( "oniaN", &oniaCount, "OniaN/I");
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
		fullTree->Branch( "ophi1", &ophi1, "onia phi 2/D");
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
	oniaTree->Branch( "hpt", &hpt, "hlt pt/D");
	oniaTree->Branch( "heta", &heta, "hlt eta/D");
	oniaTree->Branch( "hphi", &hphi, "hlt phi/D");
	oniaTree->Branch( "opt1", &opt1, "onia pt1/D");
	oniaTree->Branch( "oeta1", &oeta1, "onia eta 1/D");
	oniaTree->Branch( "ophi1", &ophi1, "onia phi 1/D");
	oniaTree->Branch( "om1", &om1, "onia mass 1/D");
	oniaTree->Branch( "dr1", &dr1, "dR 1/D");
	oniaTree->Branch( "dpt1", &dpt1, "dPt 1/D");
	if( isDimu ){
		oniaTree->Branch( "opt2", &opt2, "onia pt2/D");
		oniaTree->Branch( "oeta2", &oeta2, "onia eta 2/D");
		oniaTree->Branch( "ophi1", &ophi1, "onia phi 2/D");
		oniaTree->Branch( "om2", &om2, "onia mass 2/D");
		oniaTree->Branch( "dipt", &dipt, "dimu pt/D");
		oniaTree->Branch( "diy", &diy, "dimu y/D");
		oniaTree->Branch( "diphi", &diphi, "dimu phi/D");
		oniaTree->Branch( "dim", &dim, "dimu m/D");
		oniaTree->Branch( "dr2", &dr2, "dR 2/D");
		oniaTree->Branch( "dpt2", &dpt2, "dPt 2/D");
	}


};

void objectTree::setOniaIndex(){
	oniaCount ++;
};

void objectTree::setEventWideContent( EventData edat){
	cent = edat["Centrality"].val;
	nevt = edat["eventNb"].val;
	std::cout << cent << " , " << nevt << std::endl;
};

void objectTree::parcelEntry( evtFlatDimu parcel ){
	eventMatrix.push_back( evtFlatSummary{nevt, cent, parcel.hpt, parcel.heta, parcel.hphi, parcel.omu1.Pt(), parcel.omu2.Pt(), parcel.omu1.Eta(), parcel.omu2.Eta(), parcel.omu1.Phi(), parcel.omu2.Phi(), parcel.omu1.M(), parcel.omu2.M(), parcel.odmu.Pt(), parcel.odmu.Y(), parcel.odmu.Phi(), parcel.odmu.M(), parcel.dR1, parcel.dR2, parcel.dPt1, parcel.dPt2} ); 

};

void objectTree::parcelEntry( evtFlatSimu parcel ){
	eventMatrix.push_back( evtFlatSummary{nevt, cent, parcel.hpt, parcel.heta, parcel.hphi, parcel.omu1.Pt(), 0, parcel.omu1.Eta(),0,  parcel.omu1.Phi(), 0,  parcel.omu1.M(), 0,0,0,0,0, parcel.dR1, -1, parcel.dPt1 -1} );
};


void objectTree::flush(){
	for( auto evt : eventMatrix ){
		hpt = evt.hpt;
		heta = evt.heta;
		hphi = evt.hphi;
		opt1 = evt.opt1;
		oeta1 = evt.oeta1;
		ophi1 = evt.ophi1;
		om1 = evt.om1;
		if( isDimu ){
			dr2 = evt.dr2;
			dpt2 = evt.dpt2;
			opt2 = evt.opt2;
			oeta2 = evt.oeta2;
			phi2 = evt.phi2;
			om2 = evt.om2;
			dipt = evt.dipt;
			diy = evt.diy;
			diphi = evt.diphi;
			dim = evt.dim;
		}
		dr1 = evt.dr1;
		dpt1 = evt.dpt1;
		fullTree->Fill();
	}
	eventMatrix.clear();
	oniaCount = 0;
};


void objectTree::write(){
	fout->cd();
	fullTree->Write();
	oniaTree->Write();
	fout->Close();
};
