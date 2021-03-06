#pragma once

#include "config.h"
static int UseNCores = 40;

#include "TGraph.h"
#include <ROOT/TProcessExecutor.hxx>
#include <thread>
#include <future>
#include <execution>
#include "Reader.cc"
#include "EffCalc.cc"
#include <chrono>

void calculateEff(){

//	string file_name_hlt = INPUT_HLT;
//	string file_name_onia = INPUT_ONIA;
//	string file_output = OUTPUT_EFF;
//	unsigned int dType = SAMPLE_TYPE;
//	string tag = TAG;


	std::vector<std::pair<std::string, std::string> > v_names = { 
//trigger of menu v12
		{ "HLT_HIL1DoubleMu0_Open_v", "L1DoubleMuOpen"}, 
		{ "HLT_HIL1DoubleMu0_Zero_v", "L1DoubleMuZero"}, 
		{ "HLT_HIL1DoubleMu0_dRMax3p5_Zero_v", "L1DoubleMuOpen_drMax3p5_Zero"}, 
		{ "HLT_HIL1DoubleMu0_dRMax3p5_Open_v", "L1DoubleMuOpen_drMax3p5_Open"}, 
		{ "HLT_HIL1DoubleMu0_dRMax3p5M0to7_Open_v", "L1DoubleMuOpen_drMax3p5M0to7_Open"}, 
		{ "HLT_HIL1DoubleMu0_SQ_v"  , "L1DoubleMuSQ"}, 
  	{ "HLT_HIL2DoubleMu0_Open_v", "L2DoubleMuOpen"}, 
		{ "HLT_HIL2DoubleMu0_dRMax3p5M0to7_Open_v", "L2DoubleMuOpen_drMax3p5_M0to7_Open"}, 
		{ "HLT_HIL2DoubleMu0_Zero_v", "L2DoubleMuZero"}, 
		{ "HLT_HIL2DoubleMu0_SQ_v"  , "L2DoubleMuSQ"}, 
		{ "HLT_HIL3DoubleMu0_Open_v", "L3DoubleMuOpen"}, 
  	
		{ "HLT_HIL2DoubleMu0_Open_v", "L2DoubleMuOpen_DoHLTCut_Mass"}, 
		{ "HLT_HIL2DoubleMu0_Zero_v", "L2DoubleMuZer_DoHLTCut_Mass"}, 
		{ "HLT_HIL2DoubleMu0_SQ_v", "L2DoubleMuSQ_DoHLTCut_Mass"}, 
		{ "HLT_HIL3DoubleMu0_Open_v", "L3DoubleMuOpen_DoHLTCut_Mass"}, 
		{ "HLT_HIL3DoubleMu0_Zero_v", "L3DoubleMuZero_DoHLTCut_Mass"}, 
		{ "HLT_HIL3DoubleMu0_SQ_v", "L3DoubleMuSQ_DoHLTCut_Mass"}, 

		{ "HLT_HIL3DoubleMu0_dRMax3p5M0to7_Open_v", "L3DoubleMuOpen_drMax3p5_M0to7_Open"}, 
		{ "HLT_HIL3DoubleMu0_dRMax3p5M2p2to4p4_Open_v", "L3DoubleMuOpen_drMax3p5_M2p2to4p4_Open"}, 
		{ "HLT_HIL3DoubleMu0_dRMax3p5M2p2to4p4_Open_Vtx_v", "L3DoubleMuOpen_drMax3p5_M2p2to4p4_Open_Vtx"}, 
		{ "HLT_HIL3DoubleMu0_Zero_v", "L3DoubleMuZero"}, 
		{ "HLT_HIL3DoubleMu0_SQ_v"  , "L3DoubleMuSQ"}, 
		{ "HLT_HIL1Mu0_v", ""}, 
		{ "HLT_HIL2Mu0_v", ""}, 
		{ "HLT_HIL3Mu0_v", ""}, 
//		{ "HLT_HIL1Mu0_v", "L1DoubleMuOpen_fake"}, 
//		{ "HLT_HIL2Mu0_v", "L2DoubleMuOpen_fake"}, 
//		{ "HLT_HIL3Mu0_v", "L3DoubleMuOpen_fake"}, 
		//{ "HLT_HIL1DoubleMu0_Open_v", ""}, 
		//{ "HLT_HIL1DoubleMu0_Zero_v", ""}, 
		//{ "HLT_HIL1DoubleMu0_SQ_v"  , ""}, 
		//{ "HLT_HIL2DoubleMu0_Open_v", ""}, 
		//{ "HLT_HIL2DoubleMu0_Zero_v", ""}, 
		//{ "HLT_HIL2DoubleMu0_SQ_v"  , ""}, 
		//{ "HLT_HIL3DoubleMu0_Open_v", ""}, 
		//{ "HLT_HIL3DoubleMu0_Zero_v", ""}, 
		//{ "HLT_HIL3DoubleMu0_SQ_v"  , ""}, 
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
		int level;
		bool dmu =false;
		std::string _trig = v_names[idx].first;
		std::string _trig2 = v_names[idx].second;
		if( _trig2.find("Double") != std::string::npos) dmu = true;
		if( _trig.find("HIL1") != std::string::npos){ l1 = true; level = 1; } 
		if( _trig.find("HIL2") != std::string::npos) level = 2;
		if( _trig.find("HIL3") != std::string::npos) level = 3;
		return std::make_pair(dmu, l1);
	};
	auto trigLvl = [v_names](int idx){
		int level;
		std::string _trig = v_names[idx].first;
		if( _trig.find("HIL1") != std::string::npos) level = 1; 
		if( _trig.find("HIL2") != std::string::npos) level = 2;
		if( _trig.find("HIL3") != std::string::npos) level = 3;
		return level;
	};
	
	//Enable MultiThreading, the thread executor creates threads per trigger and make use of the available CPU cores
	ROOT::EnableImplicitMT(UseNCores);
	ROOT::TThreadExecutor mpe(UseNCores);

	//Define cuts
	std::vector<double> cuts;
	for(auto idx : ROOT::TSeqI(31)){
		cuts.push_back(0.5 *(double) idx);
	}

	//Run calculator
	long max_events = 3.1e+6;
	TH1::AddDirectory(false);
	auto extractEffs = [=](int idx){
		EffCalc calc = EffCalc( file_name_hlt, file_name_onia, dType );
		calc.objT.setTag(tag);
		calc.setTrigger(v_names[idx].first, v_names[idx].second);
		calc.setTriggerLvl(trigLvl(idx));
		calc.init(trigAttr(idx));
		if(v_names[idx].second.find("DoHLTCut") != std::string::npos ){
			calc.setHltCustomMassFilter((const std::pair<double, double>) hltFilter.at(trigLvl(idx)));
		}
		calc.setOniaCustomFilter(oniaFilter);
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
