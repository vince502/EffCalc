#pragma once

#include "EffCalc.h"
#include "Reader.cc"
#include <vector>

EffCalc::EffCalc( std::string name_file_hlt, std::string name_file_onia ) : hltData( name_file_hlt ), oniaData( name_file_onia) {
};

EffCalc::~EffCalc(){
//	for ( auto item : map_eff ){
//		if( item.second ) delete item.second;
//	}
};

void EffCalc::init(bool _getDimu, bool _isL1){
	getDimu = _getDimu;
	isL1 = _isL1;
	rap = ( getDimu ) ? "y" : "eta" ;
	std::cout << "initializing efficiencies" << std::endl;
	map_eff =  {
					{"pt", new TEfficiency("pt", "", pt_bins.size()-1, &pt_bins[0]) },
					{rap.c_str(), new TEfficiency(rap.c_str(), "", rap_bins.size()-1, &rap_bins[0]) },
					{"cent", new TEfficiency("cent", "", cent_bins.size()-1, &cent_bins[0]) },
				};
	if (hltData.isDerived){
		for( auto cut : derivedPtCuts ){
			map_eff.insert({Form("pt_%dp%d", (int) cut, (int) (10 * (cut - (int) cut ))), new TEfficiency(Form("pt_%dp%d", (int) cut, (int) (10 * (cut - (int) cut ))), "", pt_bins.size()-1, &pt_bins[0] ) });
		}
	}
	
};

void EffCalc::init( std::pair<bool, bool> dp){
	return init(dp.first, dp.second);
};

void EffCalc::setTrigger( std::string name_trig, std::string name_base_trig = "" ){
	std::cout << "Registering Trigger " << name_trig.c_str() << std::endl;
	hltData.registerTrig( name_trig, name_base_trig ); 
	registered_trigger = hltData.nickname;
};

//bool EffCalc::indexMatched(EventData &headHlt, EventData &headOnia){
//	if( (bool) headHlt["passed"] ){
//	}
//	return false;
//};

void EffCalc::eval(int idx){
	hltData.GetEntry(idx);
	auto hltPrim = hltData.getEventPrimitive( );
	int chksum = oniaData.GetEntryWithIndex( hltData.GetEventNb() );
	if( chksum < 0 ) return;
	auto hltCont = hltData.getEventContent();
	auto oniaCont = filterOniaData(oniaData.getEventContent( getDimu, isL1 ));
	if( !((bool) hltPrim["passed"].val) ){
		fillHist(std::vector<EventData>{oniaCont[0]}, oniaCont);
		if( hltData.isDerived ){
			for( auto cut : derivedPtCuts ){
				fillDerivedHist(std::vector<EventData>{oniaCont[0]}, oniaCont, cut );
			}
		}
		return;
	}
	auto pair_oniaCont = matchedData( oniaCont, hltCont );
	fillHist(pair_oniaCont.first, pair_oniaCont.second);
	if( hltData.isDerived ){
		for( auto cut : derivedPtCuts ){
			hltCont = filterHltData(hltCont, cut);
			pair_oniaCont = matchedData( oniaCont, hltCont);
			fillDerivedHist(pair_oniaCont.first, pair_oniaCont.second, cut );
		}

	}
	return;

};

void EffCalc::evalAll(int maxEvents = -1){
	int totEntries = hltData.base.map_tree["HltTree"]->GetEntries();
	unsigned int iEntries = (maxEvents > 0 ) ? std::min( maxEvents, totEntries ) : totEntries;
	for( auto iEvt : ROOT::TSeqI(iEntries) ){
		if( ( iEvt % 1000 ) == 0 ) std::cout << "Processing event " << iEvt << std::endl;
		eval(iEvt);
	}
	std::cout << "Done " << std::endl;
};

std::vector<EventData> EffCalc::filterHltData( std::vector<EventData> hltCont, double cut ){
	std::vector<EventData> d_cpy = {hltCont[0]};
	bool ofront  =true;
	for( auto cont : hltCont ){
		if( ofront ) {if( cont["front"].val == 1 ) ofront = false; continue; }
		if( cont["mu"].mu.Pt() > cut ) d_cpy.push_back(cont);
	}
	return d_cpy;
};

std::vector<EventData> EffCalc::filterOniaData( std::vector<EventData> oniaCont ){
	std::vector<EventData> d_cpy = {oniaCont[0]};
	auto passQuality = [=](EventData d){
		if( getDimu ){
			return (
				d["Pix1"].val > 0 &&
				d["Pix2"].val > 0 && 
				d["Trk1"].val > 5 &&
				d["Trk2"].val > 5 &&
				d["dxy1"].val < 0.3 &&
				d["dxy2"].val < 0.3 &&
				d["dz1"].val  < 20 &&
				d["dz2"].val  < 20 ); 
		}
		else {
			return (
				d["Pix1"].val > 0 &&
				d["Trk1"].val > 5 &&
				d["dxy1"].val < 0.3 &&
				d["dz1"].val  < 20 );
		}
	};
	auto passAcceptance = [=](EventData d){
		TLorentzVector mu1;
		if( !getDimu ){
			mu1 = d["mu"].mu;	
			return (
				(fabs(mu1.Eta()) < 2.4) &&
				(
					(fabs(mu1.Eta()) < 1.2 && mu1.Pt() > 3.5) ||
					(fabs(mu1.Eta()) > 1.2 && fabs(mu1.Eta()) < 2.1  && mu1.Pt() >= 5.47 - 1.89 * fabs(mu1.Eta()) )||
					(fabs(mu1.Eta()) > 2.1 && fabs(mu1.Eta()) < 2.4 && mu1.Pt() > 1.5)
				)
			);
		}
		if( getDimu ){
			mu1 = d["dbmu"].mu;
			auto mu2 = d["dbmu"].mu2;
			
			return (
				(fabs(mu1.Eta()) < 2.4) &&
				(
					(fabs(mu1.Eta()) < 1.2 && mu1.Pt() > 3.5) ||
					(fabs(mu1.Eta()) > 1.2 && fabs(mu1.Eta()) < 2.1  && mu1.Pt() >= 5.47 - 1.89 * fabs(mu1.Eta()) )||
					(fabs(mu1.Eta()) > 2.1 && fabs(mu1.Eta()) < 2.4 && mu1.Pt() > 1.5)
				) &&
				(fabs(mu2.Eta()) < 2.4) &&
				(
					(fabs(mu2.Eta()) < 1.2 && mu2.Pt() > 3.5) ||
					(fabs(mu2.Eta()) > 1.2 && fabs(mu2.Eta()) < 2.1  && mu2.Pt() >= 5.47 - 1.89 * fabs(mu2.Eta()) )||
					(fabs(mu2.Eta()) > 2.1 && fabs(mu2.Eta()) < 2.4 && mu2.Pt() > 1.5)
				)
			);
		}
		else return false;
	};
	bool ofront  =true;
	for( auto cont : oniaCont ){
		if( ofront ) {if( cont["front"].val == 1 ) ofront = false; continue; }
		if( passQuality(cont) && passAcceptance(cont) ) d_cpy.push_back(cont);
	}
	return d_cpy;
};

std::pair<std::vector<EventData>, std::vector<EventData> > EffCalc::matchedData( std::vector<EventData> onia, std::vector<EventData> hlt ){
	std::vector<EventData> d_cpy_pass = {onia[0]};
	std::vector<EventData> d_cpy_fail = {onia[0]};
	auto match_dR = [=](EventData base, double cut){
		if( getDimu ){
			double oeta1 = base["dbmu"].mu.Eta();
			double ophi1 = base["dbmu"].mu.Phi();
			double oeta2 = base["dbmu"].mu2.Eta();
			double ophi2 = base["dbmu"].mu2.Phi();
			bool pass1, pass2;
			for( auto cont : hlt ){
				double heta = cont["mu"].mu.Eta();
				double hphi = cont["mu"].mu.Phi();
				if( !pass1 )pass1 = sqrt(pow(fabs(oeta1 -heta ) ,2) +  pow( std::min( fabs(ophi1 - hphi), fabs( 2.*TMath::Pi() - ophi1 + hphi ) ), 2)) < cut;
				if( !pass2 )pass2 = sqrt(pow(fabs(oeta2 -heta ) ,2) +  pow( std::min( fabs(ophi2 - hphi), fabs( 2.*TMath::Pi() - ophi2 + hphi ) ), 2)) < cut;
			}
			return (pass1 && pass2);
		}
		if( !getDimu ){
			double oeta1 = base["mu"].mu.Eta();
			double ophi1 = base["mu"].mu.Phi();
			bool pass1;
			for( auto cont : hlt ){
				double heta = cont["mu"].mu.Eta();
				double hphi = cont["mu"].mu.Phi();
				if( !pass1 ) pass1 = sqrt(pow(fabs(oeta1 -heta ) ,2) +  pow( std::min( fabs(ophi1 - hphi), fabs( 2.*TMath::Pi() - ophi1 + hphi ) ),2)) < cut;
			}
			return (pass1);
		}
		return true;
	};
	auto match_dPt = [=](EventData base, double cut){
		if( getDimu ){
			double opt1 = base["dbmu"].mu.Pt();
			double opt2 = base["dbmu"].mu2.Pt();
			bool pass1, pass2;
			for( auto cont : hlt ){
				double hpt = cont["mu"].mu.Pt();
				if( !pass1 ) pass1 =  (fabs(hpt - opt1) / opt1)< cut;
				if( !pass2 ) pass2 =  (fabs(hpt - opt2) / opt2)< cut;
			}
			return (pass1 && pass2);
		}
		if( !getDimu ){
			double opt1 = base["mu"].mu.Pt();
			bool pass1, pass2;
			for( auto cont : hlt ){
				double hpt = cont["mu"].mu.Pt();
				if( !pass1 ) pass1 =  (fabs(hpt - opt1) / opt1)< cut;
			}
			return (pass1);
		}
		return true;
	};

	bool ofront  =true;
	for( auto cont : onia ){
		if( ofront ) {if( cont["front"].val == 1 ) ofront = false; continue; }
		if( match_dR(cont, 0.3) && match_dPt(cont, 0.1) ) d_cpy_pass.push_back(cont);
		else d_cpy_fail.push_back(cont);
	}
	return std::make_pair(d_cpy_pass, d_cpy_fail);
};


void EffCalc::fillHist( std::vector<EventData> oniaPass, std::vector<EventData> oniaTotal){
	std::string objName = ( getDimu ) ? "dbmu" : "mu";
	auto fn_fill = [&](bool pass, EventData oniaObj){
		if(getDimu){
			map_eff["pt"]->Fill(pass, oniaObj[objName].dmu.Pt());
			map_eff[rap]->Fill(pass, oniaObj[objName].dmu.Y());
		}
		if(!getDimu){
			map_eff["pt"]->Fill(pass, oniaObj[objName].mu.Pt());
			map_eff[rap]->Fill(pass, oniaObj[objName].mu.Eta());
		}
		return;
	};

	for( auto item : oniaTotal ){
		if(item["front"].val == 1) {if( oniaTotal.size() > 1 ){ map_eff["pt"]->Fill(false, item["Centrality"].val); } continue;}
		fn_fill(false, item);
	}
	for( auto item : oniaPass ){
		if(item["front"].val == 1) {if( oniaPass.size() > 1 ){ map_eff["pt"]->Fill(true, item["Centrality"].val); } continue;}
		fn_fill(true, item);
	}
};

void EffCalc::fillDerivedHist( std::vector<EventData> oniaPass, std::vector<EventData> oniaTotal, double cut){
	std::string objName = ( getDimu ) ? "dbmu" : "mu";
	auto fn_fill = [&](bool pass, EventData oniaObj){
		if(getDimu){
			map_eff[Form("pt_%dp%d", (int) cut, (int) (10 * (cut - (int) cut )))]->Fill(pass, oniaObj[objName].dmu.Pt());
		}
		if(!getDimu){
			map_eff[Form("pt_%dp%d", (int) cut, (int) (10 * (cut - (int) cut )))]->Fill(pass, oniaObj[objName].mu.Pt());
		}
		return;
	};

	for( auto item : oniaTotal ){
		if(item["front"].val == 1)  continue;
		fn_fill(false, item);
	}
	for( auto item : oniaPass ){
		if(item["front"].val == 1)  continue;
		fn_fill(true, item);
	}
};

std::pair<std::string, std::unordered_map<std::string, TEfficiency*> > EffCalc::getEfficiencies(){
//	std::cout << "Callled get efficiencies" << std::endl;
//	std::unordered_map<std::string, TEfficiency> res_map;
//	for( auto cont : map_eff ){
//		res_map.insert({cont.first, *cont.second});
//	}
//	return res_map;
	return std::make_pair(registered_trigger, map_eff);
};









