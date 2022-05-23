#pragma once

#include "EffCalc.h"
#include "Reader.cc"
#include <vector>
#include <chrono>

EffCalc::EffCalc( std::string name_file_hlt, std::string name_file_onia ) : hltData( name_file_hlt ), oniaData( name_file_onia) {
};

EffCalc::~EffCalc(){
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
					{"hltpass", new TEfficiency("hltpass","", 1, 0,1) },
					{"hltmass", new TEfficiency("hltmass","", pt_bins_fine.size()-1, &pt_bins_fine[0]) },
					{"hltpt", new TEfficiency("hltpt","", pt_bins_fine.size()-1, &pt_bins_fine[0]) },
					{"hlteta", new TEfficiency("hlteta","", 24, -2.4, 2.4) },
					{"hltphi", new TEfficiency("hltphi","", 72, -2*TMath::Pi(), 2*TMath::Pi()) },
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


void EffCalc::eval(int idx){
//	auto start = std::chrono::steady_clock::now();
	hltData.GetEntry(idx);
//	std::vector<std::chrono::steady_clock::time_point> v_end;
//	/* 0 */v_end.push_back(std::chrono::steady_clock::now());
	auto hltPrim = hltData.getEventPrimitive( );
	int chksum = oniaData.GetEntryWithIndex( hltData.GetEventNb() );
	if( chksum < 0 ) return;
//	/* 1 */v_end.push_back(std::chrono::steady_clock::now());
	auto oniaCont = filterOniaData(oniaData.getEventContent( getDimu, isL1 ));
//	/* 2 */v_end.push_back(std::chrono::steady_clock::now());
	if( !((bool) hltPrim["passed"].val) ){
		fillHist(std::vector<EventData>{oniaCont[0]}, oniaCont);
		if( hltData.isDerived ){
			for( auto cut : derivedPtCuts ){
				fillDerivedHist(std::vector<EventData>{oniaCont[0]}, oniaCont, cut );
			}
		}
		return;
	}
//	/* 3 */v_end.push_back(std::chrono::steady_clock::now());
	auto hltCont = hltData.getEventContent();
	auto pair_oniaCont = matchedData( oniaCont, hltCont );
	fillHist(pair_oniaCont.first, pair_oniaCont.second);
//	/* 4 */v_end.push_back(std::chrono::steady_clock::now());
	if( hltData.isDerived ){
		for( auto cut : derivedPtCuts){
				hltCont = filterHltData(hltCont, cut);
				auto _pair_oniaCont = matchedData( oniaCont, hltCont);
				fillDerivedHist(_pair_oniaCont.first, _pair_oniaCont.second, cut );
		}
	}
	return;
};

void EffCalc::eval(std::pair<long, long> indexes){
	hltData.GetEntry(indexes.first);
	auto hltPrim = hltData.getEventPrimitive( );
	oniaData.GetEntry( indexes.second );
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
	auto hltCont = hltData.getEventContent();
	auto pair_oniaCont = matchedData( oniaCont, hltCont );
	fillHist(pair_oniaCont.first, pair_oniaCont.second);
	if( hltData.isDerived ){
		std::for_each( 
			derivedPtCuts.begin(), derivedPtCuts.end(),
			[&, hltCont, oniaCont](auto&& cut) mutable {
				hltCont = filterHltData(hltCont, cut);
				auto _pair_oniaCont = matchedData( oniaCont, hltCont);
				fillDerivedHist(_pair_oniaCont.first, _pair_oniaCont.second, cut );
			});
	}
	return;

};

void EffCalc::evalHLT( int idx ){
	hltData.GetEntry(idx);
	auto hltPrim = hltData.getEventPrimitive( );
	int chksum = oniaData.GetEntryWithIndex( hltData.GetEventNb() );
	if( chksum < 0 ) return;
//	if( !((bool) hltPrim["passed"].val) ){
//	}
	auto hltCont = hltData.getEventContent();
	fillHLTHist(hltCont);
};

void EffCalc::evalAllHLT(int maxEvents = -1){
	int totEntries = hltData.base.map_tree["HltTree"]->GetEntries();
	unsigned int iEntries = (maxEvents > 0 ) ? std::min( maxEvents, totEntries ) : totEntries;
	for( auto iEvt : ROOT::TSeqI(iEntries) ){
		if( ( iEvt % 10000 ) == 0 ) std::cout << "Processing event " << iEvt << std::endl;
		evalHLT(iEvt);
	}
	std::cout << "Done " << std::endl;
};

void EffCalc::evalAll(int maxEvents = -1){
	int totEntries = hltData.base.map_tree["HltTree"]->GetEntries();
	unsigned int iEntries = (maxEvents > 0 ) ? std::min( maxEvents, totEntries ) : totEntries;
	for( auto iEvt : ROOT::TSeqI(iEntries) ){
		if( ( iEvt % 10000 ) == 0 ) std::cout << "Processing event " << iEvt << std::endl;
		eval(iEvt);
	}
	std::cout << "Done " << std::endl;
};

void EffCalc::evalAll(int maxEvents , std::vector<std::pair<long, long> > indexes){
	long count = 0;
	for( auto p : indexes ){
		if( ( count % 10000 ) == 0 ) std::cout << "Processing event " << count << std::endl;
		eval(p);
		if(maxEvents < count ) return; 
		count ++;
	}
	std::cout << "Done " << std::endl;
};

void EffCalc::mapIndex(){
	auto p_sort = [](std::pair<long, long> i1, std::pair<long, long> i2){return i1.second < i2.second;};
	std::sort(hltData.vec_idx.begin(), hltData.vec_idx.end(), p_sort);
	std::sort(oniaData.vec_idx.begin(), oniaData.vec_idx.end(), p_sort);
	std::vector<std::pair<long, long> >::iterator vit_hlt = hltData.vec_idx.begin();
	std::vector<std::pair<long, long> >::iterator vit_onia = oniaData.vec_idx.begin();
	std::vector<std::pair<long, long> > v;
	while( vit_hlt != hltData.vec_idx.end()){
		while(((*vit_onia).second < vit_hlt[1].second) && vit_onia != oniaData.vec_idx.end() ){
			if( (*vit_hlt).second == (*vit_onia).second ){
				v.push_back(std::make_pair((*vit_hlt).first, (*vit_onia).first));
				break;
			}
			vit_onia++;
		}
		vit_hlt++;
	}
	vec_idx = std::move(v);
};

std::vector<EventData> EffCalc::filterHltData( std::vector<EventData> hltCont, double cut ){
	auto vit = hltCont.begin();
	vit++;
	while( vit != hltCont.end()){
		if( (*vit)["mu"].mu.Pt() < cut ){
			vit = hltCont.erase(vit);
		}
		else vit++;
	}
	return std::move(hltCont);
};

std::vector<EventData> EffCalc::filterOniaData( std::vector<EventData> oniaCont ){
	auto passQuality = [=](EventData d){
		return (
			(( static_cast<int>(d["Sel1"].val) & ((int)pow(2,1)) ) &&
			( static_cast<int>(d["Sel1"].val) & ((int)pow(2,3)) ) &&
			((int) d["Pix1"].val) > 0 &&
			((int) d["Trk1"].val) > 5 &&
			d["dxy1"].val < 0.3 &&
			d["dz1"].val  < 20) && 
			( !(getDimu) || 
			(( static_cast<int>(d["Sel2"].val) & ((int)pow(2,1)) ) &&
			( static_cast<int>(d["Sel2"].val) & ((int)pow(2,3)) ) &&
			((int) d["Pix2"].val) > 0 &&
			((int) d["Trk2"].val) > 5 &&
			d["dxy2"].val < 0.3 &&
			d["dz2"].val  < 20)  )
		);
	};
	auto passAcceptance = [=](EventData d){
		auto accPass = [](TLorentzVector mu1){
				return (
					(fabs(mu1.Eta()) < 2.4) &&
					(
						(fabs(mu1.Eta()) > 1.2 && fabs(mu1.Eta()) < 2.1  && ( mu1.Pt() >= 5.47 - 1.89 * fabs(mu1.Eta()) ) )||
						(fabs(mu1.Eta()) > 2.1 && fabs(mu1.Eta()) < 2.4 && mu1.Pt() > 1.5) ||
						(fabs(mu1.Eta()) < 1.2 && mu1.Pt() > 3.5)
					)
				);
		};
//		TLorentzVector mu1;
		if( !getDimu ){
			return accPass(d["mu"].mu);
//			mu1 = d["mu"].mu;	
//			return (
//				(fabs(mu1.Eta()) < 2.4) &&
//				(
//					(fabs(mu1.Eta()) < 1.2 && mu1.Pt() > 3.5) ||
//					(fabs(mu1.Eta()) > 1.2 && fabs(mu1.Eta()) < 2.1  && ( mu1.Pt() >= 5.47 - 1.89 * fabs(mu1.Eta()) ) )||
//					(fabs(mu1.Eta()) > 2.1 && fabs(mu1.Eta()) < 2.4 && mu1.Pt() > 1.5)
//				)
//			);
		}
		if( getDimu ){
			return ( accPass(d["dbmu"].mu) && accPass(d["dbmu"].mu2));
//			mu1 = d["dbmu"].mu;
//			auto mu2 = d["dbmu"].mu2;
//			
//			return (
//				(fabs(mu1.Eta()) < 2.4) &&
//				(
//					(fabs(mu1.Eta()) < 1.2 && mu1.Pt() > 3.5) ||
//					(fabs(mu1.Eta()) > 1.2 && fabs(mu1.Eta()) < 2.1  && (mu1.Pt() >= 5.47 - 1.89 * fabs(mu1.Eta())) )||
//					(fabs(mu1.Eta()) > 2.1 && fabs(mu1.Eta()) < 2.4 && mu1.Pt() > 1.5)
//				) &&
//				(fabs(mu2.Eta()) < 2.4) &&
//				(
//					(fabs(mu2.Eta()) < 1.2 && mu2.Pt() > 3.5) ||
//					(fabs(mu2.Eta()) > 1.2 && fabs(mu2.Eta()) < 2.1  && (mu2.Pt() >= 5.47 - 1.89 * fabs(mu2.Eta())) )||
//					(fabs(mu2.Eta()) > 2.1 && fabs(mu2.Eta()) < 2.4 && mu2.Pt() > 1.5)
//				)
//			);
		}
		else return false;
	};

	auto vit = oniaCont.begin();
	vit++;
	while( vit != oniaCont.end()){
		if( false || !((passQuality(*vit) && passAcceptance(*vit))) ){
			vit = oniaCont.erase(vit);
		}
		else vit++;
	}
	return std::move(oniaCont);
};

std::pair<std::vector<EventData>, std::vector<EventData> > EffCalc::matchedData( std::vector<EventData> onia, std::vector<EventData> hlt){
	std::vector<EventData> d_cpy_pass = {onia[0]};
	std::vector<EventData> d_cpy_fail = {onia[0]};
	auto match_dR = [=](EventData base, double cut){
		if( getDimu ){
			double oeta1 = base["dbmu"].mu.Eta();
			double ophi1 = base["dbmu"].mu.Phi();
			double oeta2 = base["dbmu"].mu2.Eta();
			double ophi2 = base["dbmu"].mu2.Phi();
			bool pass1, pass2;
			for( auto hltcont : hlt ){
				double heta = hltcont["mu"].mu.Eta();
				double hphi = hltcont["mu"].mu.Phi();
//				std::cout << 	sqrt(pow(fabs(oeta1 -heta ) ,2) +  pow( std::min( fabs(ophi1 - hphi), fabs( 2.*TMath::Pi() - ophi1 + hphi ) ), 2)) << std::endl;
				if( !pass1 )pass1 = sqrt(pow(fabs(oeta1 -heta ) ,2) +  pow( std::min( fabs(ophi1 - hphi), fabs( 2.*TMath::Pi() - ophi1 + hphi ) ), 2)) < cut;
				if( !pass2 )pass2 = sqrt(pow(fabs(oeta2 -heta ) ,2) +  pow( std::min( fabs(ophi2 - hphi), fabs( 2.*TMath::Pi() - ophi2 + hphi ) ), 2)) < cut;
			}
			return (pass1 && pass2 );
		}
		if( !getDimu ){
			double oeta1 = base["mu"].mu.Eta();
			double ophi1 = base["mu"].mu.Phi();
			bool pass1;
			for( auto hltcont : hlt ){
				double heta = hltcont["mu"].mu.Eta();
				double hphi = hltcont["mu"].mu.Phi();
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
			for( auto hltcont : hlt ){
				double hpt = hltcont["mu"].mu.Pt();
				if( !pass1 ) pass1 =  (fabs(hpt - opt1) / opt1)< cut;
				if( !pass2 ) pass2 =  (fabs(hpt - opt2) / opt2)< cut;
			}
			return (pass1 && pass2);
		}
		if( !getDimu ){
			double opt1 = base["mu"].mu.Pt();
			bool pass1;
			for( auto hltcont : hlt ){
				double hpt = hltcont["mu"].mu.Pt();
				if( !pass1 ) pass1 =  (fabs(hpt - opt1) / opt1)< cut;
			}
			return (pass1);
		}
		return true;
	};
	auto vit = onia.begin();
	vit++;
	while( vit != onia.end()){
		if( false ||( match_dR(*vit,0.3) && match_dPt(*vit, 99999.) ) ) d_cpy_pass.push_back(*vit);
		else d_cpy_fail.push_back(*vit);
		vit++;
	}
	return std::move(std::make_pair(d_cpy_pass, d_cpy_fail));
};


void EffCalc::fillHist( std::vector<EventData> oniaPass, std::vector<EventData> oniaFail){
	auto fn_fill = [&](bool pass, EventData oniaObj){
		if(getDimu){
			map_eff["pt"]->Fill(pass, oniaObj["dbmu"].dmu.Pt());
			map_eff[rap]->Fill(pass, oniaObj["dbmu"].dmu.Y());
		}
		if(!getDimu){
			map_eff["pt"]->Fill(pass, oniaObj["mu"].mu.Pt());
			map_eff[rap]->Fill(pass, oniaObj["mu"].mu.Eta());
		}
		return;
	};

	auto vitF = oniaFail.begin();
	auto vitP = oniaPass.begin();
	if( oniaFail.size() > 1 ){ map_eff["cent"]->Fill(false, (*vitF)["Centrality"].val); }
	if( oniaPass.size() > 1 ){ map_eff["cent"]->Fill(true, (*vitP)["Centrality"].val); }
	vitF++;
	vitP++;
	while( vitF != oniaFail.end()){
		fn_fill(false, *vitF);
		vitF++;
	}
	while( vitP != oniaPass.end()){
		fn_fill(true, *vitP);
		vitP++;
	}
};

void EffCalc::fillHLTHist( std::vector<EventData> hlt){
	auto fn_fill = [&](bool pass, EventData hltObj){
			map_eff["hltmass"]->Fill(pass, hltObj["mu"].mu.M());
			map_eff["hltpt"]->Fill(pass, hltObj["mu"].mu.Pt());
			map_eff["hlteta"]->Fill(pass, hltObj["mu"].mu.Eta());
			map_eff["hltphi"]->Fill(pass, hltObj["mu"].mu.Phi());
		return;
	};

	auto vit = hlt.begin();
	bool passhlt = (bool) ((*vit)["passed"].val);
	vit++;
	while( vit != hlt.end()){
		fn_fill(passhlt, *vit);
		vit++;
	}
};

void EffCalc::fillDerivedHist( std::vector<EventData> oniaPass, std::vector<EventData> oniaFail, double cut){
	auto fn_fill = [&](bool pass, EventData oniaObj){
		if(getDimu){
			map_eff[Form("pt_%dp%d", (int) cut, (int) (10 * (cut - (int) cut )))]->Fill(pass, oniaObj["dbmu"].dmu.Pt());
		}
		if(!getDimu){
			map_eff[Form("pt_%dp%d", (int) cut, (int) (10 * (cut - (int) cut )))]->Fill(pass, oniaObj["mu"].mu.Pt());
		}
		return;
	};

	auto vitF = oniaFail.begin();
	auto vitP = oniaPass.begin();
	vitF++;
	vitP++;
	while( vitF != oniaFail.end()){
		fn_fill(false, *vitF);
		vitF++;
	}
	while( vitP != oniaPass.end()){
		fn_fill(true, *vitP);
		vitP++;
	}
};

std::pair<std::string, std::unordered_map<std::string, TEfficiency*> > EffCalc::getEfficiencies(){
	return std::move(std::make_pair(std::move(registered_trigger), std::move(map_eff) ));
};









