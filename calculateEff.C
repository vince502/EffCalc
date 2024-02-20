#pragma once

#include "config2023PbPb_1.h"
static int UseNCores = 40;
//static int UseNCores = 1;

#include "TGraph.h"
#include <ROOT/TProcessExecutor.hxx>
#include <thread>
#include <future>
#include <execution>
#include "Reader.cc"
#include "EffCalc.cc"
#include <chrono>

void calculateEff(){
	system(Form("mkdir -p /home/vince402/RunPrep_2022/EffCalc/MatchTree/%s", SUBDIR.c_str()));

//	string file_name_hlt = INPUT_HLT;
//	string file_name_onia = INPUT_ONIA;
//	string file_output = OUTPUT_EFF;
//	unsigned int dType = SAMPLE_TYPE;
//	string tag = TAG;


	std::vector<std::pair<std::string, std::string> > v_names = { 
//trigger of menu v12
// {"HLT_HIL1SingleMu0_Open_v","HLT_HIL1SingleMu0_Open_v"},
// {"HLT_HIL1SingleMu0_Cosmic_v","HLT_HIL1SingleMu0_Cosmic_v"},
// {"HLT_HIL1SingleMu0_v","HLT_HIL1SingleMu0_v"},
// {"HLT_HIL1SingleMu3_v","HLT_HIL1SingleMu3_v"},
// {"HLT_HIL1SingleMu5_v","HLT_HIL1SingleMu5_v"},
// {"HLT_HIL1SingleMu7_v","HLT_HIL1SingleMu7_v"},
// {"HLT_HIL2SingleMu3_Open_v","HLT_HIL2SingleMu3_Open_v"},
// {"HLT_HIL2SingleMu5_Open_v","HLT_HIL2SingleMu5_Open_v"},
// {"HLT_HIL2SingleMu7_Open_v","HLT_HIL2SingleMu7_Open_v"},
// {"HLT_HIL3SingleMu3_Open_v","HLT_HIL3SingleMu3_Open_v"},
// {"HLT_HIL3SingleMu5_Open_v","HLT_HIL3SingleMu5_Open_v"},
// {"HLT_HIL3SingleMu7_Open_v","HLT_HIL3SingleMu7_Open_v"},
// {"HLT_HIL3SingleMu12_Open_v","HLT_HIL3SingleMu12_Open_v"},
// {"HLT_HIL3SingleMu12_Open_v","HLT_HIL3DoubleMuLikeMu12_Open_v"},
// {"HLT_HIL2DoubleMu0_Open_v","HLT_HIL2DoubleMu0_Open_v"},
// {"HLT_HIL1DoubleMu0_MaxDr3p5_Open_v","HLT_HIL1DoubleMu0_MaxDr3p5_Open_v"},
// {"HLT_HIL1DoubleMu0_Zero_v","HLT_HIL1DoubleMu0_Zero_v"},
// {"HLT_HIL1DoubleMu0_SQ_v","HLT_HIL1DoubleMu0_SQ_v"},
// {"HLT_HIL3DoubleMu0_M0toInf_Open_v","HLT_HIL3DoubleMu0_M0toInf_Open_v"},
// {"HLT_HIL3DoubleMu0_Quarkonia_Open_v","HLT_HIL3DoubleMu0_Quarkonia_Open_v"},
// {"HLT_HIL3DoubleMu2_Quarkonia_Open_v","HLT_HIL3DoubleMu2_Quarkonia_Open_v"},
// {"HLT_HIL2DoubleMu0_M1p5to6_Open_v","HLT_HIL2DoubleMu0_M1p5to6_Open_v"},
// {"HLT_HIL2DoubleMu2p8_M1p5to6_Open_v","HLT_HIL2DoubleMu2p8_M1p5to6_Open_v"},
// {"HLT_HIL2DoubleMu0_M7to15_Open_v","HLT_HIL2DoubleMu0_M7to15_Open_v"},
// {"HLT_HIL2DoubleMu3_M7to15_Open_v","HLT_HIL2DoubleMu3_M7to15_Open_v"},
// {"HLT_HIL3DoubleMu0_M2to4p5_Open_v","HLT_HIL3DoubleMu0_M2to4p5_Open_v"},
// {"HLT_HIL3DoubleMu2_M2to4p5_Open_v","HLT_HIL3DoubleMu2_M2to4p5_Open_v"},
// {"HLT_HIL3DoubleMu0_M7to15_Open_v","HLT_HIL3DoubleMu0_M7to15_Open_v"},
// {"HLT_HIL3DoubleMu2_M7to15_Open_v","HLT_HIL3DoubleMu2_M7to15_Open_v"},
		
//		{"HLT_HIL1DoubleMu0_Open_v", "HLT_HIL1DoubleMu0_Open_v"},
//		{"HLT_HIL1DoubleMu0_Zero_v", "HLT_HIL1DoubleMu0_Zero_v"},
//		{"HLT_HIL1DoubleMu0_SQ_v", "HLT_HIL1DoubleMu0_SQ_v"},
//		{"HLT_HIL1SingleMu0_Open_v", "HLT_HIL1SingleMu0_Open_v"},
//		{"HLT_HIL1SingleMu0_Cosmic_v", "HLT_HIL1SingleMu0_Cosmic_v"},
//		{"HLT_HIL1SingleMu0_v", "HLT_HIL1SingleMu0_v"},
//		{"HLT_HIL2DoubleMu0_Open_v", "HLT_HIL2DoubleMu0_Open_v"},
//		{"HLT_HIL3DoubleMu0_M0toInf_Open_v", "HLT_HIL3DoubleMu0_M0toInf_Open_v"},
//		{"HLT_HIL3DoubleMu0_Quarkonia_Open_v", "HLT_HIL3DoubleMu0_Quarkonia_Open_v"},
//		{"HLT_HIL3DoubleMu2_Quarkonia_Open_v", "HLT_HIL3DoubleMu2_Quarkonia_Open_v"},
//		{"HLT_HIL2SingleMu3_Open_v", "HLT_HIL2SingleMu3_Open_v"},
//		{"HLT_HIL2SingleMu5_Open_v", "HLT_HIL2SingleMu5_Open_v"},
//		{"HLT_HIL2SingleMu7_Open_v", "HLT_HIL2SingleMu7_Open_v"},
//		{"HLT_HIL3SingleMu3_Open_v", "HLT_HIL3SingleMu3_Open_v"},
//		{"HLT_HIL3SingleMu5_Open_v", "HLT_HIL3SingleMu5_Open_v"},
//		{"HLT_HIL3SingleMu7_Open_v", "HLT_HIL3SingleMu7_Open_v"},
//		{"HLT_HIL3SingleMu12_Open_v", "HLT_HIL3SingleMu12_Open_v"},
//	{"HLT_HIL2DoubleMu0_M1to6p5_Open_v", "HLT_HIL2DoubleMu0_M1to6p5_Open_v"},
//	{"HLT_HIL2DoubleMu2p8_M1to6p5_Open_v", "HLT_HIL2DoubleMu2p8_M1to6p5_Open_v"},
//	{"HLT_HIL2DoubleMu0_M6p5to16_Open_v", "HLT_HIL2DoubleMu0_M6p5to16_Open_v"},
//	{"HLT_HIL2DoubleMu3_M6p5to16_Open_v", "HLT_HIL2DoubleMu3_M6p5to16_Open_v"},
//	{"HLT_HIL3DoubleMu0_M2to4p5_Open_v", "HLT_HIL3DoubleMu0_M2to4p5_Open_v"},
//	{"HLT_HIL3DoubleMu2_M2to4p5_Open_v", "HLT_HIL3DoubleMu2_M2to4p5_Open_v"},
//	{"HLT_HIL3DoubleMu0_M7to15_Open_v", "HLT_HIL3DoubleMu0_M7to15_Open_v"},
//	{"HLT_HIL3DoubleMu2_M7to15_Open_v", "HLT_HIL3DoubleMu2_M7to15_Open_v"},
//		{"HLT_HIL3DoubleMu0_MuPt2p5_M7to15_Open_v", "HLT_HIL3DoubleMu0_MuPt2p5_M7to15_Open_v"},
//		{"HLT_HIL3DoubleMu0_MuPt3_M7to15_Open_v","HLT_HIL3DoubleMu0_MuPt3_M7to15_Open_v"},
//		{"HLT_HIL3DoubleMu0_OneMuPt3_M7to15_Open_v","HLT_HIL3DoubleMu0_OneMuPt3_M7to15_Open_v"}

		
		{"HLT_PPRefL1SingleMu0_Cosmics_v","HLT_PPRefL1SingleMu0_Cosmics_v"},
		{"HLT_PPRefL1DoubleMu0_Open_v","HLT_PPRefL1DoubleMu0_Open_v"},
		{"HLT_PPRefL2DoubleMu0_Open_v","HLT_PPRefL2DoubleMu0_Open_v"},
		{"HLT_PPRefL3DoubleMu0_Open_v","HLT_PPRefL3DoubleMu0_Open_v"},
		{"HLT_PPRefL1DoubleMu0_v","HLT_PPRefL1DoubleMu0_v"},
		{"HLT_PPRefL2DoubleMu0_v","HLT_PPRefL2DoubleMu0_v"},
		{"HLT_PPRefL3DoubleMu0_v","HLT_PPRefL3DoubleMu0_v"},
		{"HLT_PPRefL2SingleMu7_v","HLT_PPRefL2SingleMu7_v"},
		{"HLT_PPRefL2SingleMu12_v","HLT_PPRefL2SingleMu12_v"},
		{"HLT_PPRefL2SingleMu15_v","HLT_PPRefL2SingleMu15_v"},
		{"HLT_PPRefL2SingleMu20_v","HLT_PPRefL2SingleMu20_v"},
		{"HLT_PPRefL3SingleMu3_v","HLT_PPRefL3SingleMu3_v"},
		{"HLT_PPRefL3SingleMu5_v","HLT_PPRefL3SingleMu5_v"},
		{"HLT_PPRefL3SingleMu7_v","HLT_PPRefL3SingleMu7_v"},
		{"HLT_PPRefL3SingleMu12_v","HLT_PPRefL3SingleMu12_v"},
		{"HLT_PPRefL3SingleMu15_v","HLT_PPRefL3SingleMu15_v"},
		{"HLT_PPRefL3SingleMu20_v","HLT_PPRefL3SingleMu20_v"},


	};
	std::vector<std::string> v_names2 = { "HLT_HIL1DoubleMu0_Open_v", "HLT_HIL2DoubleMu0_Open_v", "HLT_HIL3DoubleMu0_Open_v"};
	auto trigAttr = [v_names](int idx){
		bool l1 = false;
		int level;
		bool dmu =false;
		std::string _trig = v_names[idx].first;
		std::string _trig2 = v_names[idx].second;
		if( _trig2.find("Double") != std::string::npos) dmu = true;
		if( _trig.find("HIL1") != std::string::npos){ l1 = true; level = 1; } 
		if( _trig.find("HIL2") != std::string::npos) level = 2;
		if( _trig.find("HIL3") != std::string::npos) level = 3;
		if( _trig.find("PPRefL1") != std::string::npos){ l1 = true; level = 1; } // Does not work until L1 prop objects available on Onia 
		if( _trig.find("PPRefL2") != std::string::npos) level = 2;
		if( _trig.find("PPRefL3") != std::string::npos) level = 3;
		return std::make_pair(dmu, l1);
	};
	auto trigLvl = [v_names](int idx){
		int level;
		std::string _trig = v_names[idx].first;
		if( _trig.find("HIL1") != std::string::npos) level = 1; 
		if( _trig.find("HIL2") != std::string::npos) level = 2;
		if( _trig.find("HIL3") != std::string::npos) level = 3;
		if( _trig.find("PPRefL1") != std::string::npos) level = 1; 
		if( _trig.find("PPRefL2") != std::string::npos) level = 2;
		if( _trig.find("PPRefL3") != std::string::npos) level = 3;
		return level;
	};
	
	//Enable MultiThreading, the thread executor creates threads per trigger and make use of the available CPU cores
//	ROOT::EnableImplicitMT(80);
	// TO DO : separate files
	ROOT::TThreadExecutor mpe(UseNCores);

	//Define cuts
	std::vector<double> cuts;
	for(auto idx : ROOT::TSeqI(31)){
		cuts.push_back(0.5 *(double) idx);
	}

	//Run calculator
	long max_events = -1;
	TH1::AddDirectory(false);
	auto extractEffs = [=](int idx){
		EffCalc calc = EffCalc( file_name_hlt, file_name_onia, dType );
		calc.objT.setTag(tag);
		calc.setTrigger(v_names[idx].first, v_names[idx].second);
		calc.setTriggerLvl(trigLvl(idx));
		calc.init(trigAttr(idx));
		if(v_names[idx].second.find("DoHLTCut") != std::string::npos ){
			calc.setHltCustomMassFilter((const std::pair<double, double>) hltFilter.at(trigLvl(idx)));
			if(v_names[idx].second.find("PT") != std::string::npos ){
				calc.setHltCustomPtFilter( hltPtFilter[trigLvl(idx)] );
			}
		}

		if(v_names[idx].second.find("DoONIACut") != std::string::npos ){
			calc.setOniaCustomFilter(oniaFilter);
		}
		if(v_names[idx].second.find("DoONIACut") == std::string::npos ){
			if( dType == kMCJP )	calc.setOniaCustomFilter(oniaFilterJPsi);
			if( dType == kMCUp )	calc.setOniaCustomFilter(oniaFilterUpsilon);
		}
		calc.evalAll(max_events);
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
};
