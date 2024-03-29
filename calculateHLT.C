#pragma once

#include "TGraph.h"
#include <ROOT/TProcessExecutor.hxx>
#include <thread>
#include <future>
#include <execution>
#include "Reader.cc"
#include "EffCalc.cc"
#include <chrono>

static int UseNCores = 4;

void calculateHLT(){
//	string file_name_hlt = "../store/openHLT_Gmenu_JPsiEMB_NoSPClimit_v1230_v8.root";
//	string file_name_onia = "../store/Oniatree_Jpsi_Embedded_CMSSW_12_3_0_pre1_20220312.root";
//	string file_output = "outputHLT_MCJpsiEMB.root";

//	string file_name_hlt = "../store/openHLT_data2018MB_NewMenu_v9.root";
//	string file_name_onia = "../store/OniaTree_miniAOD_HIMBPD2_Run327237_MuonNoSel.root";
//	string file_output = "outputHLT_Data2018_newMenudRCut0p3.root";

//	string file_name_hlt = "../store/openHLT_data2018MB_NewMenu_v2_7_mod1.root";
//	string file_name_onia = "../store/OniaTree_miniAOD_HIMBPD2_Run327237_MuonNoSel.root";
//	string file_output = "outputHLT_Data2018_v2_7_mod1_2.root";

//	string file_name_hlt = "../store/openHLT_NewMumenu_JPsi_v2_9.root";
//	string file_name_onia = "../store/Oniatree_Jpsi_CMSSW_12_3_0_pre1_20220312.root";
//	string file_output = "outputHLT_JPsi_v2_9.root";

//	string file_name_hlt = "../store/openHLT_HIMuon_LegacyTrigger_MBPD2018.root";
//	string file_name_onia = "../store/OniaTree_miniAOD_HIMBPD2_Run327237_MuonNoSel.root";
//	string file_output = "outputHLT_Data2018_LegacydR0p3_v2.root";

//	string file_name_hlt = "../store/openHLT_NewMumenu_UpsiEMB_v2_11.root";
//	string file_name_onia = "../store/Oniatree_UpsilonEMB_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = "outputHLT_UpsiEMB_v2_11.root";

	string file_name_hlt = "../store/openHLT_NewMumenu_MuonGunHighPt_half_v2_11.root";
	string file_name_onia = "../store/Oniatree_SingleMuPt_3_100_MuonSelAll_CMSSW_12_3_0_220519.root";
	string file_output = "outputHLT_MuonGunHighPt_v2_11.root";

	//std::vector<sstd::string> v_names = {"HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v", "HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_v", "HLT_HIL1DoubleMuOpen_v", "HLT_HIL2DoubleMuOpen_v", "HLT_HIL3DoubleMuOpen_v"};
//	std::vector<std::string> v_names = { "HLT_HIL1DoubleMu0_Open_v", "HLT_HIL2DoubleMu0_Open_v", "HLT_HIL3DoubleMu0_Open_v"};
//	std::vector<std::string> v_names = { "HLT_HIL1DoubleMuOpen_v", "HLT_HIL2DoubleMuOpen_v", "HLT_HIL3DoubleMuOpen_v"};
	std::vector<std::pair<std::string, std::string> > v_names = { 
//v2_7(_mod1)
///		{ "HLT_HIL1DoubleMu0_Open_v", ""}, 
///		{ "HLT_HIL1DoubleMu0_Zero_v", ""}, 
///		{ "HLT_HIL1DoubleMu0_dRMax3p5_Zero_v", ""}, 
///		{ "HLT_HIL1DoubleMu0_dRMax3p5M0to7_Zero_v", ""}, 
///		{ "HLT_HIL1DoubleMu0_dRMax3p5_Open_v", ""}, 
///		{ "HLT_HIL1DoubleMu0_SQ_v"  , ""}, 
///		{ "HLT_HIL2DoubleMu0_Open_v", ""}, 
///		{ "HLT_HIL2DoubleMu0_dRMax3p5M0to7_Open_v", ""}, 
///		{ "HLT_HIL2DoubleMu0_Zero_v", ""}, 
///		{ "HLT_HIL2DoubleMu0_SQ_v"  , ""}, 
///		{ "HLT_HIL3DoubleMu0_Open_v", ""}, 
///		{ "HLT_HIL3DoubleMu0_dRMax3p5M0to7_Open_v", ""}, 
///		{ "HLT_HIL3DoubleMu0_Zero_v", ""}, 
		{ "HLT_HIL3DoubleMu0_SQ_v"  , ""}, 
	//	{ "HLT_HIL1Mu0_v", ""}, 
	//	{ "HLT_HIL2Mu0_v", ""}, 
		{ "HLT_HIL3Mu0_v", ""}, 
//trigger of menu v12
//		{ "HLT_HIL1DoubleMu0_Open_v", "L1DoubleMuOpen"}, 
//		{ "HLT_HIL1DoubleMu0_Zero_v", "L1DoubleMuZero"}, 
//		{ "HLT_HIL1DoubleMu0_SQ_v"  , "L1DoubleMuSQ"}, 
//		{ "HLT_HIL2DoubleMu0_Open_v", "L2DoubleMuOpen"}, 
//		{ "HLT_HIL2DoubleMu0_Zero_v", "L2DoubleMuZero"}, 
//		{ "HLT_HIL2DoubleMu0_SQ_v"  , "L2DoubleMuSQ"}, 
//		{ "HLT_HIL3DoubleMu0_Open_v", "L3DoubleMuOpen"}, 
//		{ "HLT_HIL3DoubleMu0_Zero_v", "L3DoubleMuZero"}, 
//		{ "HLT_HIL3DoubleMu0_SQ_v"  , "L3DoubleMuSQ"}, 
//		{ "HLT_HIL1Mu0_v", ""}, 
//		{ "HLT_HIL2Mu0_v", ""}, 
//		{ "HLT_HIL3Mu0_v", ""}, 
//		{ "HLT_HIL1DoubleMu0_Open_v", ""}, 
//		{ "HLT_HIL1DoubleMu0_Zero_v", ""}, 
//		{ "HLT_HIL1DoubleMu0_SQ_v"  , ""}, 
//		{ "HLT_HIL2DoubleMu0_Open_v", ""}, 
//		{ "HLT_HIL2DoubleMu0_Zero_v", ""}, 
//		{ "HLT_HIL2DoubleMu0_SQ_v"  , ""}, 
//		{ "HLT_HIL3DoubleMu0_Open_v", ""}, 
//		{ "HLT_HIL3DoubleMu0_Zero_v", ""}, 
//		{ "HLT_HIL3DoubleMu0_SQ_v"  , ""}, 
//trigger of menu v9
//		{ "HLT_HIL1DoubleMuOpen_v", "L1DoubleMuOpen"}, 
//		{ "HLT_HIL2Mu0_L1DoubleMuOpen_v", "L2DoubleMuOpen"}, 
//		{ "HLT_HIL3Mu0_L1DoubleMuOpen_v", "L3DoubleMuOpen"}, 
//		{ "HLT_HIL3Mu0_L1DoubleMuOpen_v", ""}, 
//		{ "HLT_HIL3Mu0L1SingleMuOpen_v", "L1SingleMuOpen"}, 
//		{"HLT_HIL1DoubleMuOpen_v", ""},
//		{"HLT_HIL2Mu0_L1DoubleMu0_v", ""},
//		{"HLT_Mu12_v", ""},
//trigger of run2 legacy menu
//		{ "HLT_HIL1DoubleMuOpen_v", ""}, 
//		{ "HLT_HIL2DoubleMuOpen_v", ""}, 
//		{ "HLT_HIL3DoubleMuOpen_v", ""}, 
//		{ "HLT_HIL3DoubleMuOpen_v", ""}, 
//		{ "HLT_HIL3Mu12_v", ""},
	};
	std::vector<std::string> v_names2 = { "HLT_HIL1DoubleMu0_Open_v", "HLT_HIL2DoubleMu0_Open_v", "HLT_HIL3DoubleMu0_Open_v"};
	auto trigAttr = [v_names](int idx){
		bool l1 = false;
		bool dmu =false;
		std::string _trig = v_names[idx].first;
		if( _trig.find("Double") != std::string::npos) dmu = true;
		if( _trig.find("HIL1") != std::string::npos) l1 = true;
		return std::make_pair(dmu, l1);
	};
	
//	EffCalc calc = EffCalc( file_name_hlt, file_name_onia );

	//Enable MultiThreading, the thread executor creates threads per trigger and make use of the available CPU cores
	ROOT::EnableImplicitMT(UseNCores);
	ROOT::TThreadExecutor mpe(UseNCores);
//	ROOT::TThreadExecutor mpe(v_names.size());

	//Define cuts
	std::vector<double> cuts;
	for(auto idx : ROOT::TSeqI(31)){
		cuts.push_back(0.5 *(double) idx);
	}

	//Run calculator
	long max_events = 3.5e+8;
	TH1::AddDirectory(false);
	auto extractEffs = [=](int idx){
		EffCalc calc = EffCalc( file_name_hlt, file_name_onia );
		calc.setTrigger(v_names[idx].first, v_names[idx].second);
		calc.init(trigAttr(idx));
		calc.evalAllHLT(max_events);
		std::cout << Form("Done trigger [%s]", v_names[idx].first.c_str()) << std::endl;
		return std::move(calc.getEfficiencies());
	};

	//Result container
	std::map< string, std::unordered_map<string, TEfficiency*> >result_map;
	std::map<string, TGraph*> graps;

	//Map results
	auto t_start = std::chrono::steady_clock::now();
	const auto& res = mpe.Map(extractEffs, ROOT::TSeqI(v_names.size()));
	auto t_end = std::chrono::steady_clock::now();
	std::chrono::duration<double> t_elapsed =  t_end -t_start;
	std::cout << "elapsed time for Timing evaluaiton : " << t_elapsed.count() << std::endl;
//	auto res= extractEffs(0);

	std::cout << "Run Fin" << std::endl;
	TFile* output = new TFile(file_output.c_str(), "recreate");
	output->cd();
	for( auto idx : res ){
		output->mkdir(idx.first.c_str());
		output->cd(idx.first.c_str());
		for( auto plotp : idx.second){
			plotp.second->Write();
		}
		output->cd("/");
		result_map[idx.first] = idx.second;
	}
	output->Close();
	

	std::cout << "Draw" << std::endl;
//	result_map["HLT_HIL1DoubleMuOpen_v"]["pt"]->Draw();

};
