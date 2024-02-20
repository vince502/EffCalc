#pragma once

#include "EffCalc.h"
#include "Reader.cc"
#include "ObjectTree.cc"
#include <vector>
#include <chrono>

EffCalc::EffCalc( std::string name_file_hlt, std::string name_file_onia, unsigned int feedType = kMCJP ) : hltData( name_file_hlt ), oniaData( name_file_onia, feedType) {
	dataType = feedType;
};

EffCalc::~EffCalc(){
};

void EffCalc::init(bool _getDimu, bool _isL1){
	getDimu = _getDimu;
	isL1 = _isL1;
	rap = ( getDimu ) ? "y" : "eta" ;
	std::cout << "initializing efficiencies" << std::endl;
	map_eff =  {
//					{"pt",
//					{rap.c_str(),
//					{"cent",
//					{"hltpass", 
//					{"hltfake", 
//					{"hltmass", 
//					{"hltpt", 
//					{"hlteta",
//					{"hltphi",
//					{"passdr1", 
//					{"passdr2", 
				};
	map_hist[true] =  {
					{"pt", new TH1D("pt_pass", "", pt_bins.size()-1, &pt_bins[0]) },
					{"phi", new TH1D("phi_pass", "", phi_bins.size()-1, &phi_bins[0]) },
					{rap.c_str(), new TH1D((rap + "_pass").c_str(), "", rap_bins.size()-1, &rap_bins[0]) },
//					{rap.c_str(), new TH1D((rap + "_pass").c_str(), "", 1, -2.4, 2.4) },
					{"cent", new TH1D("cent_pass", "", cent_bins.size()-1, &cent_bins[0]) },
					{"hltpass", new TH1D("hltpass_pass","", 1, 0,1) },
					{"hltfake", new TH1D("hltfake_pass","", 1, 0,1) },
					{"hltmass", new TH1D("hltmass_pass","", pt_bins_fine.size()-1, &pt_bins_fine[0]) },
					{"hltpt", new TH1D("hltpt_pass","", pt_bins_fine.size()-1, &pt_bins_fine[0]) },
					{"hlteta", new TH1D("hlteta_pass","", 24, -2.4, 2.4) },
					{"hltphi", new TH1D("hltphi_pass","", 72, -2*TMath::Pi(), 2*TMath::Pi()) },
					{"passdr1", new TH1D("passdr_pass","", 80, -2, 2) },
					{"passdr2", new TH1D("passdr_pass","", 80, -2, 2) },
				};
	map_hist[false] =  {
					{"pt", new TH1D("pt_fail", "", pt_bins.size()-1, &pt_bins[0]) },
					{"phi", new TH1D("phi_fail", "", phi_bins.size()-1, &phi_bins[0]) },
					{rap.c_str(), new TH1D((rap + "_fail").c_str(), "", rap_bins.size()-1, &rap_bins[0]) },
					//{rap.c_str(), new TH1D((rap + "_fail").c_str(), "", 1, -2.4, 2.4) },
					{"cent", new TH1D("cent_fail", "", cent_bins.size()-1, &cent_bins[0]) },
					{"hltpass", new TH1D("hltpass_fail","", 1, 0,1) },
					{"hltfake", new TH1D("hltfake_fail","", 1, 0,1) },
					{"hltmass", new TH1D("hltmass_fail","", pt_bins_fine.size()-1, &pt_bins_fine[0]) },
					{"hltpt", new TH1D("hltpt_fail","", pt_bins_fine.size()-1, &pt_bins_fine[0]) },
					{"hlteta", new TH1D("hlteta_fail","", 24, -2.4, 2.4) },
					{"hltphi", new TH1D("hltphi_fail","", 72, -2*TMath::Pi(), 2*TMath::Pi()) },
					{"passdr1", new TH1D("passdr_fail","", 80, -2, 2) },
					{"passdr2", new TH1D("passdr_fail","", 80, -2, 2) },
				};
	if (hltData.isDerived){
		for( auto cut : derivedPtCuts ){
			map_eff.insert({Form("pt_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut ))), new TEfficiency(Form("pt_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut ))), "", pt_bins.size()-1, &pt_bins[0] ) });
			map_hist[true].insert({Form("pt_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut ))), new TH1D(Form("pt_pass_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut ))), "", pt_bins.size()-1, &pt_bins[0] ) });
			map_hist[false].insert({Form("pt_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut ))), new TH1D(Form("pt_fail_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut ))), "", pt_bins.size()-1, &pt_bins[0] ) });
		}
		for( auto cut : derivedMassCuts ){
			map_eff.insert({Form("mass_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut ))), new TEfficiency(Form("pt_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut ))), "", pt_bins.size()-1, &pt_bins[0] ) });
			map_hist[true].insert({Form("mass_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut ))), new TH1D(Form("pt_pass_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut ))), "", pt_bins.size()-1, &pt_bins[0] ) });
			map_hist[false].insert({Form("mass_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut ))), new TH1D(Form("pt_fail_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut ))), "", pt_bins.size()-1, &pt_bins[0] ) });
		}
	}
	objT.init( registered_trigger, getDimu, dataType );
};

void EffCalc::init( std::pair<bool, bool> dp){
	return init(dp.first, dp.second);
};

void EffCalc::setTrigger( std::string name_trig, std::string name_base_trig = "" ){
	std::cout << "Registering Trigger " << name_trig.c_str() << std::endl;
	hltData.registerTrig( name_trig, name_base_trig ); 
	registered_trigger = hltData.nickname;
	cuthltrange = false;
	if( name_base_trig.find("DoHLTCut") != std::string::npos) cuthltrange = true;
};

void EffCalc::setTriggerLvl( int lvl ){
	level = lvl;
	// dRcut = (level == 3) ? 0.1 : 0.3;
	//dRcut = (level == 3) ? 0.1 : 0.1;
	 dRcut = (level == 3) ? 999. : 999.3;
	 dPtcut = (level == 3) ? 999. : 9999.;; // Only for this version!
	//dPtcut = (level == 3) ? 0.5 : 9999.;; // Only for this version!
};

void EffCalc::setHltCustomMassFilter( std::pair<double, double> m ){
	hlt_m_low = m.first;
	hlt_m_high = m.second;
};

void EffCalc::setHltCustomPtFilter( std::pair<double, double> m ){
	hlt_pt_1 = m.first;
	hlt_pt_2 = m.second;
};

void EffCalc::eval(int idx){
//	auto start = std::chrono::steady_clock::now();
	hltData.GetEntry(idx);
//	std::vector<std::chrono::steady_clock::time_point> v_end;
//	/* 0 */v_end.push_back(std::chrono::steady_clock::now());
	auto hltPrim = hltData.getEventPrimitive( );
	int chksum;
	if( dataType == kData ) chksum = oniaData.GetEntryWithIndex( hltData.GetRunNb(), hltData.GetEventNb() );
	if( dataType != kData) chksum = oniaData.GetEntryWithIndex( hltData.GetEventNb() );
	if( chksum < 0 ) return;

//	std::cout << "Debug : Onia Passed, EvtNb :  " << oniaData.eventNb <<std::endl;
//	/* 1 */v_end.push_back(std::chrono::steady_clock::now());
	auto oniaCont = filterOniaData(oniaData.getEventContent( getDimu, isL1 ));
//	if( oniaCont[0]["Reco_mu_size"].val != 2 && dataType == kMCJP) return;
	for( auto base : oniaCont ) {
		if( base["front"].val==1 ) continue;
//		std::cout << "Debug : dimuon Y : " << base["dbmu"].dmu.Rapidity() << std::endl;
	}
	objT.setEventWideContent( oniaCont[0] );

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
//	std::cout << "Debug : Pair size             : " << oniaCont.size() << ", " << hltCont.size() << std::endl;
	auto pair_oniaCont = matchedData( oniaCont, hltCont , true);
//	std::cout << "Debug : Pass : " << pair_oniaCont.first.size() << ", Fail : " << pair_oniaCont.second.size() << std::endl;
	objT.flush();
	fillHist(pair_oniaCont.first, pair_oniaCont.second);
//	/* 4 */v_end.push_back(std::chrono::steady_clock::now());
	if( hltData.isDerived ){
		for( auto cut : derivedPtCuts){
			hltCont = filterHltData(hltCont, cut);
			auto _pair_oniaCont = matchedData( oniaCont, hltCont, false);
			fillDerivedHist(_pair_oniaCont.first, _pair_oniaCont.second, cut );
		}
		for(auto cut : derivedMassCuts){
			hltCont = filterHltDataMass(hltCont, cut);
			auto _pair_oniaCont = matchedData( oniaCont, hltCont, false);
			fillDerivedMassHist(_pair_oniaCont.first, _pair_oniaCont.second, cut );
		}
	}
	return;
};

void EffCalc::eval(std::pair<long, long> indexes){
//	hltData.GetEntry(indexes.first);
//	auto hltPrim = hltData.getEventPrimitive( );
//	oniaData.GetEntry( indexes.second );
//	auto oniaCont = filterOniaData(oniaData.getEventContent( getDimu, isL1 ));
//	if( !((bool) hltPrim["passed"].val) ){
//		fillHist(std::vector<EventData>{oniaCont[0]}, oniaCont);
//		if( hltData.isDerived ){
//			for( auto cut : derivedPtCuts ){
//				fillDerivedHist(std::vector<EventData>{oniaCont[0]}, oniaCont, cut );
//			}
//		}
//		return;
//	}
//	auto hltCont = hltData.getEventContent();
//	auto pair_oniaCont = matchedData( oniaCont, hltCont, false);
//    fillHist(pair_oniaCont.first, pair_oniaCont.second);
//    if( hltData.isDerived ){
//        std::for_each(
//            derivedPtCuts.begin(), derivedPtCuts.end(),
//            [&, hltCont, oniaCont](auto&& cut) mutable {
//                hltCont = filterHltData(hltCont, cut);
//                auto _pair_oniaCont = matchedData( oniaCont, hltCont, false);
//				fillDerivedHist(_pair_oniaCont.first, _pair_oniaCont.second, cut );
//			}
//			);
//	}
	return;

};

void EffCalc::evalHLT( int idx ){
	hltData.GetEntry(idx);
	auto hltPrim = hltData.getEventPrimitive( );
		if( !((bool) hltPrim["passed"].val) ){
			return;
		}
	int chksum = oniaData.GetEntryWithIndex( hltData.GetEventNb() );
	auto hltCont = hltData.getEventContent();
	if( chksum < 0 ){
			map_eff["hltfake"]->Fill(true,0.5,  hltCont.size() -1); 
		return;
	}
//	if( !((bool) hltPrim["passed"].val) ){
//	}
	fillHLTHist(hltCont);
};

void EffCalc::evalAllHLT(int maxEvents = -1){
	int totEntries = hltData.base.map_tree["HltTree"]->GetEntries();
	oniaData.turnObjTreeOff();
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
		if( ( iEvt % 30000 ) == 0 ) std::cout << "Processing event ["<<registered_trigger.c_str()<<"] " << iEvt << std::endl;
		eval(iEvt);
	}
	objT.write();
	std::cout << "Done " << std::endl;
};

void EffCalc::evalSegment(int startIdx, int endIdx){
	int totEntries = hltData.base.map_tree["HltTree"]->GetEntries();
	for( int iEvt = startIdx; iEvt< endIdx && iEvt < totEntries; iEvt ++){
		if( ( iEvt % 30000 ) == 0 ) std::cout << "Processing event ["<<registered_trigger.c_str()<<"] " << iEvt << std::endl;
		eval(iEvt);
	}
	objT.write();
	std::cout << "Done " << std::endl;
};

void EffCalc::evalAll(int maxEvents , std::vector<std::pair<long, long> > indexes){
	long count = 0;
	for( auto p : indexes ){
		if( ( count % 10000 ) == 0 ) std::cout << "Processing event ["<<registered_trigger.c_str()<<"] " << count << std::endl;
		eval(p);
		if(maxEvents < count ) return; 
		count ++;
	}
	objT.write();
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

std::vector<EventData> EffCalc::filterHltDataMass( std::vector<EventData> hltCont, double cut ){
	std::vector<EventData> tmp;
	tmp.push_back(hltCont[0]);
	//auto combination = [=](std::vector<EventData> &tmp, std::vector<EventData> cont){
	//for(int x =1; x<hltCont.size(); x++){
	//	for(int y =1; y<hltCont.size() && x<y; ++y){
	//		//double mass1 = cont[x]["mu"].mu.M();
	//		//double mass2 = cont[y]["mu"].mu.M();
	//		double invarmass = (hltCont[x]["mu"].mu+hltCont[y]["mu"].mu).M();
	//		if(invarmass > cut){
	//			tmp.push_back(hltCont[x]);
	//			tmp.push_back(hltCont[y]);
	//		}
	//	}	
	//}
	for(auto x = hltCont.begin()+1; x!=hltCont.end(); x++){
		for(auto y = hltCont.begin()+1; y<hltCont.end() && x<y; y++){
			double invarmass = (((*x)["mu"].mu)+((*y)["mu"].mu)).M();
			if(invarmass < cut){
				tmp.push_back(*x);
				tmp.push_back(*y);
			}

		}

	}
	tmp.erase(std::unique(tmp.begin(),tmp.end()),tmp.end());
	return std::move(tmp);
};		

std::vector<EventData> EffCalc::filterOniaData( std::vector<EventData> oniaCont ){
	auto passQuality = [=](EventData d){
		if(offlineSel == kHybridSoft){
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
		}
		if(offlineSel == kSoft){
			return (
				(( static_cast<int>(d["Sel1"].val) & ((int)pow(2,1)) ) &&
				( static_cast<int>(d["Sel1"].val) & ((int)pow(2,3)) ) &&
				((int) d["Pix1"].val) > 0 &&
				( d["TMOne1"].val) > 0.1  &&
				d["dxy1"].val < 0.3 &&
				d["dz1"].val  < 20) && 
				( !(getDimu) || 
				(( static_cast<int>(d["Sel2"].val) & ((int)pow(2,1)) ) &&
				( static_cast<int>(d["Sel2"].val) & ((int)pow(2,3)) ) &&
				((int) d["Pix2"].val) > 0 &&
				( d["TMOne2"].val) > 0.1  &&
				d["dxy2"].val < 0.3 &&
				d["dz2"].val  < 20)  )
			);
		}
		else{
			return true;
		}
	};
	auto passAcceptance = [=](EventData d){
		auto accPass = [=](TLorentzVector mu1){
				if(dataType == kMCJP || dataType == kData) return (
					(fabs(mu1.Eta()) < 2.4) &&
					(
						(fabs(mu1.Eta()) > 1.2 && fabs(mu1.Eta()) < 2.1  && ( mu1.Pt() >= 5.47 - 1.89 * fabs(mu1.Eta()) ) )||
						(fabs(mu1.Eta()) > 2.1 && fabs(mu1.Eta()) < 2.4 && mu1.Pt() > 1.5) ||
						(fabs(mu1.Eta()) < 1.2 && mu1.Pt() > 3.5)
					)
//					&& ( mu1.Pt() > 3.5)
				);
				if(dataType == kMCUp) return(
					fabs(mu1.Eta()) < 2.4 &&
					fabs(mu1.Pt()) > 4
				);
				if(dataType == kMCmuLoose) return(
					fabs(mu1.Eta()) < 2.4 
				);
				if(dataType == kMCmu) return (
					(fabs(mu1.Eta()) < 2.4) &&
					(
						(fabs(mu1.Eta()) > 1.2 && fabs(mu1.Eta()) < 2.1  && ( mu1.Pt() >= 5.47 - 1.89 * fabs(mu1.Eta()) ) )||
						(fabs(mu1.Eta()) > 2.1 && fabs(mu1.Eta()) < 2.4 && mu1.Pt() > 1.5) ||
						(fabs(mu1.Eta()) < 1.2 && mu1.Pt() > 3.5)
					)
				);
				else return false;
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
	auto passGenMatching = [=](EventData d){
		auto dimuGM = [](EventData dd){
			if(dd["QQisGen"].val >=0) return true;
			return false;
		};
		auto simuGM = [](EventData dd){
			if((dd["QQisGen"].val >=0) ) return true;
			return false;
//			return true;
		};
//		if( dataType == kMCJP && d["Reco_mu_size"].val < 2 ) return false;
		if( dataType == kData ) return true;
		if( getDimu ) return dimuGM(d);
		else return simuGM(d);
	};
	auto passCustomFilter = [=](EventData d){
		bool ret = false;
		if( getDimu ){
//			std::cout <<  d["dbmu"].dmu.M()<< std::endl;
			if( d["dbmu"].dmu.M() > map_oniafilter_limit["m"].first &&
				d["dbmu"].dmu.M() < map_oniafilter_limit["m"].second
			) ret = true;
			if( ret == true ){
				if( !(d["dbmu"].dmu.Pt() > map_oniafilter_limit["pt"].first &&
					d["dbmu"].dmu.Pt() < map_oniafilter_limit["pt"].second)
				) ret = false;
			}
		}
		else if( !getDimu ){
			if( d["mu"].mu.Pt() > map_oniafilter_limit["pt1"].first &&
				d["mu"].mu.Pt() < map_oniafilter_limit["pt1"].second //&&
			) ret = true;
		}
		return ret;
	};

	auto vit = oniaCont.begin();
	bool hastwoMu = (*vit)["Reco_mu_size"].val >=1.5;
	vit++;
//	if( (!hastwoMu) && (dataType == kMCJP) ){
//		std::cout << "Debug erasing event" << std::endl;
//		while( vit != oniaCont.end()){
//			vit = oniaCont.erase(vit);
//		}
//	}
//	else {
		while( vit != oniaCont.end()){
//				std::cout << "Debug onia qual pass Gen : "   << passGenMatching(*vit) << std::endl;
//				std::cout << "Debug onia qual pass Acc : "   << passAcceptance(*vit) << std::endl;
//				std::cout << "Debug onia qual pass Custom: " << passCustomFilter(*vit) << std::endl;
//				std::cout << "Debug onia qual pass ID : "    << passQuality(*vit) << std::endl;
			if( false || !(passGenMatching(*vit) && passAcceptance(*vit) && passCustomFilter(*vit) && (passQuality(*vit))) ){
			//if( false || !(passAcceptance(*vit))   ){
				vit = oniaCont.erase(vit);
//				std::cout << "fail onia" << std::endl;
			}
			else{
				vit++;
//				std::cout << "pass onia" << std::endl;
			}
		}
//	}
//	std::cout << "Debug onia qual pass : " << oniaCont.size() - 1 << std::endl;
	return std::move(oniaCont);
};

std::pair<std::vector<EventData>, std::vector<EventData> > EffCalc::matchedData( std::vector<EventData> onia, std::vector<EventData> hlt, bool sendParcel){
	std::vector<EventData> d_cpy_pass = {onia[0]};
	std::vector<EventData> d_cpy_fail = {onia[0]};
	// std::cout << " cpy pass : " << d_cpy_pass.size() << ", fail : " << d_cpy_fail.size() << std::endl;
//	auto match_dR = [=](EventData base, double cut){
//		if( getDimu ){
//			double oeta1 = base["dbmu"].mu.Eta();
//			double ophi1 = base["dbmu"].mu.Phi();
//			double oeta2 = base["dbmu"].mu2.Eta();
//			double ophi2 = base["dbmu"].mu2.Phi();
//			bool pass1, pass2;
//			for( auto hltcont : hlt ){
//				double heta = hltcont["mu"].mu.Eta();
//				double hphi = hltcont["mu"].mu.Phi();
////				std::cout << 	sqrt(pow(fabs(oeta1 -heta ) ,2) +  pow( std::min( fabs(ophi1 - hphi), fabs( 2.*TMath::Pi() - ophi1 + hphi ) ), 2)) << std::endl;
//				if( !pass1 )pass1 = sqrt(pow(fabs(oeta1 -heta ) ,2) +  pow( std::min( fabs(ophi1 - hphi), fabs( 2.*TMath::Pi() - ophi1 + hphi ) ), 2)) < cut;
//				if( !pass2 )pass2 = sqrt(pow(fabs(oeta2 -heta ) ,2) +  pow( std::min( fabs(ophi2 - hphi), fabs( 2.*TMath::Pi() - ophi2 + hphi ) ), 2)) < cut;
//			}
//			return (pass1 && pass2 );
//		}
//		if( !getDimu ){
//			double oeta1 = base["mu"].mu.Eta();
//			double ophi1 = base["mu"].mu.Phi();
//			bool pass1;
//			for( auto hltcont : hlt ){
//				double heta = hltcont["mu"].mu.Eta();
//				double hphi = hltcont["mu"].mu.Phi();
//				if( !pass1 ) pass1 = sqrt(pow(fabs(oeta1 -heta ) ,2) +  pow( std::min( fabs(ophi1 - hphi), fabs( 2.*TMath::Pi() - ophi1 + hphi ) ),2)) < cut;
//			}
//			return (pass1);
//		}
//		return true;
//	};
	auto match = [&](EventData base, double cutdR, double cutdPt){
		if( getDimu ){
			double oeta1 = base["dbmu"].mu.Eta();
			double ophi1 = base["dbmu"].mu.Phi();
			double oeta2 = base["dbmu"].mu2.Eta();
			double ophi2 = base["dbmu"].mu2.Phi();
			double opt1 = base["dbmu"].mu.Pt();
			double opt2 = base["dbmu"].mu2.Pt();
			double gpt1 = base["dbmu"].gen_mu.Pt();
			double gpt2 = base["dbmu"].gen_mu2.Pt();
			double om1 = base["dbmu"].mu.M();
			double om2 = base["dbmu"].mu2.M();
			bool passdR1=false;
			bool passdR2=false;
			bool passdPt1=false;
			bool passdPt2=false;
			int  countN = 0;
			int  counter = 0;
			int  countM1 = 0;
			int  countM2 = 0;
			int  posM1 = 0;
			int  posM2 = 0;
			int  M1matchedWith = -1;
			if(!cuthltrange){
				for( auto hltcont : hlt ){
					double heta = hltcont["mu"].mu.Eta();
					double hphi = hltcont["mu"].mu.Phi();
					double hpt = hltcont["mu"].mu.Pt();
//					std::cout << 	sqrt(pow(fabs(oeta1 -heta ) ,2) +  pow( std::min( fabs(ophi1 - hphi), fabs( 2.*TMath::Pi() - ophi1 + hphi ) ), 2)) << std::endl;
					double dR1 = sqrt(pow(fabs(oeta1 -heta ) ,2) +  pow( std::min( fabs(ophi1 - hphi), fabs( 2.*TMath::Pi() - ophi1 + hphi ) ), 2));
					double dR2 = sqrt(pow(fabs(oeta2 -heta ) ,2) +  pow( std::min( fabs(ophi2 - hphi), fabs( 2.*TMath::Pi() - ophi2 + hphi ) ), 2));
					double dPt1 = (fabs(hpt - opt1) / opt1);
					double dPt2 = (fabs(hpt - opt2) / opt2);
					if( !passdR1 ) passdR1 =  dR1 < cutdR;
					if( !passdR2 ) passdR2 =  dR2 < cutdR;
					if( !passdPt1 ) passdPt1 = dPt1 < cutdPt;
					if( !passdPt2 ) passdPt2 = dPt2 < cutdPt;
					if( sendParcel )objT.parcelEntry( evtFlatDimu{hpt, heta, hphi, base["dbmu"].mu, base["dbmu"].mu2, base["dbmu"].dmu, dR1, dR2, dPt1, dPt2,(int)( passdR1 && passdPt1) + 2*( (int) passdR2 && passdPt2)}); 
//					std::cout << (int)( passdR1 && passdPt1) << std::endl;
//					if( (( M1matchedWith != 1) && (dR1 < cutdR && dPt1 < cutdPt) ) || ( (M1matchedWith !=2) && (dR2 < cutdR && dPt2 < cutdPt )) ){
					if( (( true) && (dR1 < cutdR && dPt1 < cutdPt) ) || ( (true) && (dR2 < cutdR && dPt2 < cutdPt )) ){
						countN++;
						if( countM1 == 0 ) posM1 = counter;
						if(dR1 < cutdR && dPt1 < cutdPt){ M1matchedWith = 1; countM1+=1; }
						else{ M1matchedWith = 2; countM2+=1;}
						if( countM1 !=0 ){ 
							if( M1matchedWith == 1 && dR2 < cutdR && dPt2 < cutdPt) posM2 = counter;
							else if( M1matchedWith == 2 && dR1 < cutdR && dPt1 < cutdPt) posM2 = counter;
						}
					}
					counter ++;
				}
			//	if( countM2 !=0 && countM1 != 0 ){ auto v = hlt.begin(); std::advance(v, posM1); hlt.erase(v);
			//		if( ( posM1 > posM2) ){ auto v = hlt.begin(); std::advance(v, posM2); hlt.erase(v);}
			//		else if( ( posM1 < posM2) ){ auto v = hlt.begin(); std::advance(v, posM2 -1); hlt.erase(v);}
			//	}
				//else if( countM2 !=0 ){ auto v = hlt.begin(); std::advance(v, posM2); hlt.erase(v);} 

			}
			if(cuthltrange){
				countN = 2;
				int hltsize = hlt.size();
				for( auto jump : ROOT::TSeqI(1,hltsize)){
					for( auto idx : ROOT::TSeqI(hltsize - jump) ){
						auto hltcont = hlt[idx];
						auto hltcont2 = hlt[idx+jump];
						auto dimumass = (hltcont["mu"].mu + hltcont2["mu"].mu).M();
						if ( !( dimumass < hlt_m_high&& dimumass > hlt_m_low  )) continue;
//						std::cout << "Debug : dimumass " << dimumass << std::endl;
						double heta1 = hltcont["mu"].mu.Eta();
						double hphi1 = hltcont["mu"].mu.Phi();
						double hpt1 = hltcont["mu"].mu.Pt();
						double heta2 = hltcont2["mu"].mu.Eta();
						double hphi2 = hltcont2["mu"].mu.Phi();
						double hpt2 = hltcont2["mu"].mu.Pt();
						if ( !( hpt1 > hlt_pt_1 &&  hpt2 > hlt_pt_2  )) continue;
						double dR1 = sqrt(pow(fabs(oeta1 -heta1 ) ,2) +  pow( std::min( fabs(ophi1 - hphi1), fabs( 2.*TMath::Pi() - ophi1 + hphi1 ) ), 2));
						double dR2 = sqrt(pow(fabs(oeta2 -heta2 ) ,2) +  pow( std::min( fabs(ophi2 - hphi2), fabs( 2.*TMath::Pi() - ophi2 + hphi2 ) ), 2));
						double dPt1 = (fabs(hpt1 - opt1) / opt1);
						double dPt2 = (fabs(hpt2 - opt2) / opt2);
						if( !passdR1 ) passdR1 =  dR1 < cutdR;
						if( !passdR2 ) passdR2 =  dR2 < cutdR;
						if( !passdPt1 ) passdPt1 = dPt1 < cutdPt;
						if( !passdPt2 ) passdPt2 = dPt2 < cutdPt;
						if( !(passdR1&& passdR2 && passdPt1 && passdPt2) ){
							passdR1=false;passdR2=false;passdPt1=false;passdPt2=false;
							auto hltcontx=hltcont;hltcont=hltcont2;hltcont2=hltcontx;
							heta1 = hltcont["mu"].mu.Eta();
							hphi1 = hltcont["mu"].mu.Phi();
							hpt1 = hltcont["mu"].mu.Pt();
							heta2 = hltcont2["mu"].mu.Eta();
							hphi2 = hltcont2["mu"].mu.Phi();
							hpt2 = hltcont2["mu"].mu.Pt();
							dR1 = sqrt(pow(fabs(oeta1 -heta1 ) ,2) +  pow( std::min( fabs(ophi1 - hphi1), fabs( 2.*TMath::Pi() - ophi1 + hphi1 ) ), 2));
							dR2 = sqrt(pow(fabs(oeta2 -heta2 ) ,2) +  pow( std::min( fabs(ophi2 - hphi2), fabs( 2.*TMath::Pi() - ophi2 + hphi2 ) ), 2));
							dPt1 = (fabs(hpt1 - opt1) / opt1);
							dPt2 = (fabs(hpt2 - opt2) / opt2);
							if( !passdR1 ) passdR1 =  dR1 < cutdR;
							if( !passdR2 ) passdR2 =  dR2 < cutdR;
							if( !passdPt1 ) passdPt1 = dPt1 < cutdPt;
							if( !passdPt2 ) passdPt2 = dPt2 < cutdPt;
							if( (dR1 < cutdR && dPt1 < cutdPt) || (dR2 < cutdR && dPt2 < cutdPt) ) countN++;
						}
//						if( sendParcel )objT.parcelEntry( evtFlatDimu{hpt, heta, hphi, base["dbmu"].mu, base["dbmu"].mu2, base["dbmu"].dmu, dR1, dR2, dPt1, dPt2,(int)( passdR1 && passdPt1) + 2*( (int) passdR2 && passdPt2)}); 
//						std::cout << (int)( passdR1 && passdPt1) << std::endl;
					}
				}
			}
			return ( false || ((countN>0) &&passdR1 && passdR2 && passdPt1 && passdPt2));
		}
		if( !getDimu ){
			double oeta1 = base["mu"].mu.Eta();
			double ophi1 = base["mu"].mu.Phi();
			double opt1 = base["mu"].mu.Pt();
			double om1 = base["mu"].mu.M();
			bool passdR1, passdPt1;
			int  counter = 0;
			int  countM1 = 0;
			for( auto hltcont : hlt ){
				double heta = hltcont["mu"].mu.Eta();
				double hphi = hltcont["mu"].mu.Phi();
				double hpt = hltcont["mu"].mu.Pt();
				double dR1 = sqrt(pow(fabs(oeta1 -heta ) ,2) +  pow( std::min( fabs(ophi1 - hphi), fabs( 2.*TMath::Pi() - ophi1 + hphi ) ),2));
				double dPt1 = (fabs(hpt - opt1) / opt1);
				if( !passdR1 ) passdR1 = dR1 < cutdR;
				if( !passdPt1 ) passdPt1 = dPt1 < cutdPt;
				if( sendParcel ) objT.parcelEntry( evtFlatSimu{hpt, heta, hphi, base["mu"].mu, dR1, dPt1,(int)( passdR1 && passdPt1) }); 
				if( (dR1 < cutdR && dPt1 < cutdPt) ){
					if( countM1 == 0 ) countM1 = counter;
				}
			}
			if( countM1 != 0 ){ auto v = hlt.begin(); std::advance(v, countM1); hlt.erase(v);}
			return (passdR1 && passdPt1);
		}
		return true;
	};
//	auto match_dPt = [=](EventData base, double cut){
//		if( getDimu ){
//			double opt1 = base["dbmu"].mu.Pt();
//			double opt2 = base["dbmu"].mu2.Pt();
//			bool pass1, pass2;
//			for( auto hltcont : hlt ){
//				double hpt = hltcont["mu"].mu.Pt();
//				if( !pass1 ) pass1 =  (fabs(hpt - opt1) / opt1)< cut;
//				if( !pass2 ) pass2 =  (fabs(hpt - opt2) / opt2)< cut;
//			}
//			return (pass1 && pass2);
//		}
//		if( !getDimu ){
//			double opt1 = base["mu"].mu.Pt();
//			bool pass1;
//			for( auto hltcont : hlt ){
//				double hpt = hltcont["mu"].mu.Pt();
//				if( !pass1 ) pass1 =  (fabs(hpt - opt1) / opt1)< cut;
//			}
//			return (pass1);
//		}
//		return true;
//	};
	auto vit = onia.begin();
	vit++;
	while( vit != onia.end()){
		if( sendParcel ) {
			objT.setOniaIndex();
//			std::cout << objT.oniaCount << std::endl;
		}
	//	if( false ||( match_dR(*vit,0.3) && match_dPt(*vit, 99999.) ) ){
		if( false || match(*vit,dRcut, dPtcut) ){
			d_cpy_pass.push_back(*vit);
		}
		else {
			d_cpy_fail.push_back(*vit);
		}
		vit++;
	}
	return std::move(std::make_pair(d_cpy_pass, d_cpy_fail));
};


void EffCalc::fillHist( std::vector<EventData> oniaPass, std::vector<EventData> oniaFail){
	auto vitF = oniaFail.begin();
	auto vitP = oniaPass.begin();
	auto nColl = (useNColl) ? findNcoll(getHiBinFromhiHF((*vitF)["SumET_HF"].val)) : (double) 1.;
	auto fn_fill = [&](bool pass, EventData oniaObj){
		if(getDimu){
			map_hist[pass]["pt"]->Fill(oniaObj["dbmu"].dmu.Pt(), nColl);
			map_hist[pass]["phi"]->Fill(oniaObj["dbmu"].dmu.Phi(), nColl);
			map_hist[pass][rap]->Fill(oniaObj["dbmu"].dmu.Rapidity(), nColl);
			//fill total histo
			if( pass ){
				map_hist[false]["pt"]->Fill(oniaObj["dbmu"].dmu.Pt(), nColl);
				map_hist[false]["phi"]->Fill(oniaObj["dbmu"].dmu.Phi(), nColl);
				map_hist[false][rap]->Fill(oniaObj["dbmu"].dmu.Rapidity(), nColl);
			}
		}
		if(!getDimu){
			map_hist[pass]["pt"]->Fill(oniaObj["mu"].mu.Pt(), nColl);
			map_hist[pass]["phi"]->Fill(oniaObj["mu"].mu.Phi(), nColl);
			map_hist[pass][rap]->Fill(oniaObj["mu"].mu.Eta(), nColl);
			if( pass ){
				map_hist[false]["pt"]->Fill(oniaObj["mu"].mu.Pt(), nColl);
				map_hist[false][rap]->Fill(oniaObj["mu"].mu.Eta(), nColl);
			}
		}
		return;
	};

	if( oniaFail.size() > 1 ){ 
			map_hist[false]["cent"]->Fill(getHiBinFromhiHF((*vitF)["SumET_HF"].val), nColl); 
	}
	if( oniaPass.size() > 1 ){ 
			map_hist[true]["cent"]->Fill(getHiBinFromhiHF((*vitF)["SumET_HF"].val), nColl);
			map_hist[false]["cent"]->Fill(getHiBinFromhiHF((*vitF)["SumET_HF"].val), nColl);
	}
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
	return;
};

void EffCalc::fillDerivedHist( std::vector<EventData> oniaPass, std::vector<EventData> oniaFail, double cut){
	auto vitF = oniaFail.begin();
	auto vitP = oniaPass.begin();
	auto nColl = (useNColl) ? findNcoll((*vitF)["Centrality"].val) : (double) 1. ;
	std::cout << "nColl : " << nColl << std::endl;
	auto fn_fill = [&](bool pass, EventData oniaObj){
		if(getDimu){
				std::cout << "pt : " << oniaObj["dbmu"].dmu.Pt() << std::endl;
			map_hist[pass][Form("pt_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut )))]->Fill(oniaObj["dbmu"].dmu.Pt(), nColl);
			if( pass ){
				map_hist[false][Form("pt_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut )))]->Fill(oniaObj["dbmu"].dmu.Pt(), nColl);
			}
		}
		if(!getDimu){
			map_hist[pass][Form("pt_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut )))]->Fill(oniaObj["mu"].mu.Pt(), nColl);
			if ( pass ){
				map_hist[false][Form("pt_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut )))]->Fill(oniaObj["mu"].mu.Pt(), nColl);
			}
		}
		return;
	};


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

void EffCalc::fillDerivedMassHist( std::vector<EventData> oniaPass, std::vector<EventData> oniaFail, double cut){
	auto vitF = oniaFail.begin();
	auto vitP = oniaPass.begin();
	auto nColl = findNcoll((*vitF)["Centrality"].val);
	auto fn_fill = [&](bool pass, EventData oniaObj){
		if(getDimu){
			map_hist[pass][Form("mass_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut )))]->Fill(oniaObj["dbmu"].dmu.Pt(), nColl);
			if( pass ){
				map_hist[pass][Form("mass_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut )))]->Fill(oniaObj["dbmu"].dmu.Pt(), nColl);
			}
		}
		if(!getDimu){
			map_hist[pass][Form("mass_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut )))]->Fill(oniaObj["mu"].mu.Pt(), nColl);
			if( pass ){
				map_hist[pass][Form("mass_%dp%ld", (int) cut, std::lround(10 * (cut - (int) cut )))]->Fill(oniaObj["mu"].mu.Pt(), nColl);
			}
		}
		return;
	};

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


//void EffCalc::fillDerivedHist( std::vector<EventData> oniaPass, std::vector<EventData> oniaFail, double cut){
//	auto fn_fill = [&](bool pass, EventData oniaObj){
//		if(getDimu){
//			map_eff[Form("Mass_%dp%d", (int) cut, (int) (10 * (cut - (int) cut )))]->Fill(pass, oniaObj["dbmu"].dmu.M());
//		}
//
//		if(!getDimu){
//			map_eff[Form("Mass_%dp%d", (int) cut, (int) (10 * (cut - (int) cut )))]->Fill(pass, oniaObj["mu"].mu.M());
//		}
//		return;
//	};
//
//	auto vitF = oniaFail.begin();
//	auto vitP = oniaPass.begin();
//	vitF++;
//	vitP++;
//	while( vitF != oniaFail.end()){
//		fn_fill(false, *vitF);
//		vitF++;
//	}
//	while( vitP != oniaPass.end()){
//		fn_fill(true, *vitP);
//		vitP++;
//	}
//}

std::pair<std::string, std::unordered_map<std::string, TEfficiency*> > EffCalc::getEfficiencies(){
	for( auto item_pair : map_hist[true]){
		std::cout << item_pair.first << std::endl;
		for( auto i : ROOT::TSeqI(((*item_pair.second).GetNbinsX()))){
			std::cout << "Pass : " << (*item_pair.second).GetBinContent(i+1) << " Total : " << (*(map_hist[false][item_pair.first])).GetBinContent(i+1) << std::endl;
			if( (*(map_hist[false][item_pair.first])).GetBinContent(i+1) == 0 ){
				(*(map_hist[false][item_pair.first])).SetBinContent(i+1, 1 );
			}
		}
		map_eff[item_pair.first] = new TEfficiency(*item_pair.second, *(map_hist[false][item_pair.first]) );
		map_eff[item_pair.first]->SetName(item_pair.first.c_str());
	}
	return std::move(std::make_pair(std::move(registered_trigger), std::move(map_eff) ));
};

void EffCalc::setOniaCustomFilter( std::map<std::string, std::pair<double, double>> m ){
	auto findAndSet = [&](std::string var){
		if( m.find(var.c_str()) != m.end() ){
			map_oniafilter_limit[var].first = m[var].first;
			map_oniafilter_limit[var].second = m[var].second;
		}
	};
	for( auto item : (std::vector<std::string>) {"m", "pt", "rap"} ){
		findAndSet(item);
	}
};







