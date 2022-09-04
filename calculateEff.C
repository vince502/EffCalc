#pragma once

#include "config2.h"
static int UseNCores = 160;
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
	system(Form("mkdir /home/vince402/RunPrep_2022/EffCalc/MatchTree/%s", SUBDIR.c_str()));

//	string file_name_hlt = INPUT_HLT;
//	string file_name_onia = INPUT_ONIA;
//	string file_output = OUTPUT_EFF;
//	unsigned int dType = SAMPLE_TYPE;
//	string tag = TAG;


	std::vector<std::pair<std::string, std::string> > v_names = { 
//trigger of menu v12
//		{ "HLT_HIL1DoubleMu0_Open_v", "L1DoubleMuOpen"}, 

//		{ "HLT_HIL1DoubleMu0_dRMax3p5_Zero_v", "L1DoubleMuOpen_drMax3p5_Zero"}, 
//		{ "HLT_HIL1DoubleMu0_dRMax3p5_Open_v", "L1DoubleMuOpen_drMax3p5_Open"}, 
//		{ "HLT_HIL1DoubleMu0_dRMax3p5M0to7_Open_v", "L1DoubleMuOpen_drMax3p5M0to7_Open"}, 

//		{ "HLT_HIL2DoubleMu0_Open_v", "L2DoubleMuOpen"}, 
//		{ "HLT_HIL2DoubleMu0_dRMax3p5M0to7_Open_v", "L2DoubleMuOpen_drMax3p5_M0to7_Open"}, 
//		{ "HLT_HIL2DoubleMu0_Zero_v", "L2DoubleMuZero"}, 
//		{ "HLT_HIL2DoubleMu0_SQ_v"  , "L2DoubleMuSQ"}, 
//		{ "HLT_HIL3DoubleMu0_Open_v", "L3DoubleMuOpen"}, 
//		{ "HLT_HIL3DoubleMu0_Cosmic_v", "L3DoubleMuCosmic"}, 
  	
//		{ "HLT_HIL2DoubleMu0_Open_v", "L2DoubleMuOpen_DoHLTCut_Mass"}, 

//		{ "HLT_HIL2DoubleMu0_SQ_v", "L2DoubleMuSQ_DoHLTCut_Mass"}, 
//		{ "HLT_HIL3DoubleMu0_Open_v", "L3DoubleMuOpen_DoHLTCut_Mass"}, 

//		{ "HLT_HIL3DoubleMu0_SQ_v", "L3DoubleMuSQ_DoHLTCut_Mass"}, 

//		{ "HLT_HIL3DoubleMu0_dRMax3p5M0to7_Open_v", "L3DoubleMuOpen_drMax3p5_M0to7_Open"}, 
//		{ "HLT_HIL3DoubleMu0_dRMax3p5M2p2to4p4_Open_v", "L3DoubleMuOpen_drMax3p5_M2p2to4p4_Open"}, 
//		{ "HLT_HIL3DoubleMu0_dRMax3p5M2p2to4p4_Open_Vtx_v", "L3DoubleMuOpen_drMax3p5_M2p2to4p4_Open_Vtx"}, 
//		{ "HLT_HIL3DoubleMu0_Zero_v", "L3DoubleMuZero"}, 
//		{ "HLT_HIL3DoubleMu0_SQ_v"  , "L3DoubleMuSQ"}, 
//		{ "HLT_HIL1Mu0_v", ""}, 
//		{ "HLT_HIL2Mu0_v", ""}, 
//		{ "HLT_HIL3Mu0_v", ""}, 


//		{ "HLT_HIL2DoubleMu0_M1to6p5Acop1toPiAlphamiPito1_Open_v", "HLT_HIL2DoubleMu0_M1to6p5Acop1toPiAlphamiPito1Open_v"},
//		{ "HLT_HIL2DoubleMu0_M1to6p5Acop1toPi_Open_v", "HLT_HIL2DoubleMu0_M1to6p5Acop1toPiOpen_v"},
//		{ "HLT_HIL2DoubleMu0_M1to6p5_Open_v", "HLT_HIL2DoubleMu0_M1to6p5Open_DoHLTCut_Mass"},
//		{ "HLT_HIL2DoubleMu0_M1to6p5_Open_v", "HLT_HIL2DoubleMu0_M1to6p5Open_v"},
//		{ "HLT_HIL2DoubleMu0_M1to6p5_Open_wL2F_v", "HLT_HIL2DoubleMu0_M1to6p5OpenwL2F_v"},
//		{ "HLT_HIL2DoubleMu0_M1to6p5_Open_NoChmb_v", "HLT_HIL2DoubleMu0_M1to6p5OpenNoChmb_v"},
//		{ "HLT_HIL2DoubleMu0_M1to6p5_Open_OneChmb_v", "HLT_HIL2DoubleMu0_M1to6p5OpenOneChmb_v"},
//		{ "HLT_HIL2DoubleMu0_M1to6p5_Open_NoChmb_OneStn_v", "HLT_HIL2DoubleMu0_M1to6p5OpenNoChmbOneStn_v"},
//		{ "HLT_HIL2DoubleMu0_MmiInftoInf_Open_v", "HLT_HIL2DoubleMu0_MmiInftoInfOpen_v"},
//		{ "HLT_HIL2DoubleMu0_MmiInftoInf_Open_NoChmb_v", "HLT_HIL2DoubleMu0_MmiInfotoInfOpenNoChmb_v"},
//		{ "HLT_HIL2DoubleMu0_MmiInftoInf_Open_OneChmb_v", "HLT_HIL2DoubleMu0_MmiInfotoInfOpenOneChmb_v"},
//		{ "HLT_HIL2DoubleMu0_MmiInftoInf_Open_NoChmb_OneStn_v", "HLT_HIL2DoubleMu0_MmiInfotoInfOpenNoChmbOneStn_v"},
//		{ "HLT_HIL2DoubleMu0_MmiInftoInf_Open_v", "HLT_HIL2DoubleMu0_MmiInftoInfOpen_DoHLTCut_Mass_v"},
//		{ "HLT_HIL3DoubleMu0_M2to4p5Acop1p2toPi_Open_v", "HLT_HIL3DoubleMu0_M2to4p5Acop1p2toPiOpen_v"},
//		{ "HLT_HIL3DoubleMu0_M2to4p5_Open_v", "HLT_HIL3DoubleMu0_M2to4p5Open_v"},
//		{ "HLT_HIL3DoubleMu0_M2to4p5_Open_OneMu_v", "HLT_HIL3DoubleMu0_M2to4p5OpenOneMu_v"},
//		{ "HLT_HIL3DoubleMu0_M2to4p5_Open_NoMu_v", "HLT_HIL3DoubleMu0_M2to4p5OpenNoMu_v"},
//		{ "HLT_HIL3DoubleMu0_M2to4p5_Open_OneMu_NoSG_v", "HLT_HIL3DoubleMu0_M2to4p5OpenOneMuNoSG_v"},
//		{ "HLT_HIL3DoubleMu0_M2to4p5_Open_v", "HLT_HIL3DoubleMu0_M2to4p5Open_DoHLTCut_Mass_v"},
//		{ "HLT_HIL3DoubleMu0_M2to4p5NoL3Pre_Open_v", "HLT_HIL3DoubleMu0_M2to4p5NoL3PreOpen_v"},
//		{ "HLT_HIL3DoubleMu0_M2to4p5NoL3PreFast_Open_v", "HLT_HIL3DoubleMu0_M2to4p5NoL3PreFastOpen_v"},
//		{ "HLT_HIL3DoubleMu0_M2to4p5NoL3PreFast_Open_v", "HLT_HIL3DoubleMu0_M2to4p5NoL3PreFastOpen_DoHLTCut_Mass_v"},
//		{ "HLT_HIL3DoubleMu0_M2to4p5AND8to12_Open_v", "HLT_HIL3DoubleMu0_M2to4p5AND8to12Open_v"},
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
{"HLT_HIL1DoubleMu0_Open_v"								,	"HLT_HIL1DoubleMu0_Open"},
{"HLT_HIL2DoubleMu0_Open_v"                             ,    "HLT_HIL2DoubleMu0_Open"},
{"HLT_HIL2DoubleMu0_M1to6p5_Open_v"                     ,    "HLT_HIL2DoubleMu0_M1to6p5_Open"},
{"HLT_HIL2DoubleMu0_M6p5to16_Open_v"                    ,    "HLT_HIL2DoubleMu0_M6p5to16_Open"},
{"HLT_HIL2DoubleMu0_M1to16_Open_v"                      ,    "HLT_HIL2DoubleMu0_M1to16_Open"},
{"HLT_HIL2DoubleMu4_Open_v"                             ,    "HLT_HIL2DoubleMu4_Open"},
{"HLT_HIL2SingleMu3_Open_v"                             ,    "HLT_HIL2SingleMu3_Open"},
{"HLT_HIL2SingleMu5_Open_v"                             ,    "HLT_HIL2SingleMu5_Open"},
{"HLT_HIL2SingleMu7_Open_v"                             ,    "HLT_HIL2SingleMu7_Open"},
{"HLT_HIL3DoubleMuPre0_Open_v"                          ,    "HLT_HIL3DoubleMuPre0_Open"},
{"HLT_HIL3DoubleMuPre3p8_Open_v"                        ,    "HLT_HIL3DoubleMuPre3p8_Open"},
{"HLT_HIL3DoubleMuPre0_M2to4p5_Open_v"                  ,    "HLT_HIL3DoubleMuPre0_M2to4p5_Open"},
{"HLT_HIL3DoubleMuPre0_M7to15_Open_v"                   ,    "HLT_HIL3DoubleMuPre0_M7to15_Open"},
{"HLT_HIL3DoubleMu0_M2to4p5_Open_v"                     ,    "HLT_HIL3DoubleMu0_M2to4p5_Open"},
{"HLT_HIL3DoubleMu0_M0toInf_Open_v"                     ,    "HLT_HIL3DoubleMu0_M0toInf_Open"},
{"HLT_HIL3DoubleMu3p8_M0toInf_Open_v"                   ,    "HLT_HIL3DoubleMu3p8_M0toInf_Open"},
{"HLT_HIL3DoubleMu0_M7to15_Open_v"                      ,    "HLT_HIL3DoubleMu0_M7to15_Open"},
{"HLT_HIL3DoubleMu2_M7to15_Open_v"                      ,    "HLT_HIL3DoubleMu2_M7to15_Open"},
{"HLT_HIL3DoubleMu1p5_M7to15_Open_v"                    ,    "HLT_HIL3DoubleMu1p5_M7to15_Open"},
{"HLT_HIL3DoubleMu1_M7to15_Open_v"                      ,    "HLT_HIL3DoubleMu1_M7to15_Open"},
{"HLT_HIL3DoubleMu0_Quarkonia_Open_v"                   ,    "HLT_HIL3DoubleMu0_Quarkonia_Open"},
{"HLT_HIL3DoubleMu0_Quarkonia_LowMpT2_Open_v"           ,    "HLT_HIL3DoubleMu0_Quarkonia_LowMpT2_Open"},
{"HLT_HIL3DoubleMu0_Quarkonia_LowMpT2HighMpT1p5_Open_v" ,    "HLT_HIL3DoubleMu0_Quarkonia_LowMpT2HighMpT1p5_Open"},
{"HLT_HIL3DoubleMu0_Quarkonia_LowMpT2HighMpT1_Open_v"   ,    "HLT_HIL3DoubleMu0_Quarkonia_LowMpT2HighMpT1_Open"},
{"HLT_HIL3DoubleMu2_Quarkonia_Open_v"                   ,    "HLT_HIL3DoubleMu2_Quarkonia_Open"},
{"HLT_HIL3DoubleMu2_M2to4p5_Open_v"                     ,    "HLT_HIL3DoubleMu2_M2to4p5_Open"},
{"HLT_HIL3DoubleMu1p5_M2to4p5_Open_v"                   ,    "HLT_HIL3DoubleMu1p5_M2to4p5_Open"},
{"HLT_HIL3DoubleMu1_M2to4p5_Open_v"                     ,    "HLT_HIL3DoubleMu1_M2to4p5_Open"},
{"HLT_HIL3SingleMu3_Open_v"                             ,    "HLT_HIL3SingleMu3_Open"},
{"HLT_HIL3SingleMu5_Open_v"                             ,    "HLT_HIL3SingleMu5_Open"},
{"HLT_HIL3SingleMu7_Open_v"                             ,    "HLT_HIL3SingleMu7_Open"},

//		{ "HLT_HIL3DoubleMu0_Open_v"  , "L3DoubleMuOpen"}, 
//		{ "HLT_HIL2DoubleMu0_Open_v"  , "L2DoubleMuOpen"}, 
//		{ "HLT_HIL1DoubleMu0_Open_v", "L1DoubleMuOpen"}, 
//
//		{ "HLT_HIL3DoubleMu2_M2to4p5_Open_v"  , "L3DoubleMuOpen2_M2to4p5"}, 
//		{ "HLT_HIL3DoubleMu2_M2to4p5_Open_inDimuFilter_v"  , "L3DoubleMuOpen2_M2to4p5_inDimuFilter"}, 
//		{ "HLT_HIL3DoubleMu1p5_M2to4p5_Open_v"  , "L3DoubleMuOpen1p5_M2to4p5"}, 
//		{ "HLT_HIL3DoubleMu1_M2to4p5_Open_v"  , "L3DoubleMuOpen1_M2to4p5"}, 
//		{ "HLT_HIL3DoubleMu0p5_M2to4p5_Open_v"  , "L3DoubleMuOpen0p5_M2to4p5"}, 
//		{ "HLT_HIL3DoubleMu0_M2to4p5_Open_noL3Pre_v"  , "L3DoubleMuOpen0_M2to4p5_noL3Pre"}, 
//		{ "HLT_HIL3DoubleMu0_M2to4p5_Open_v"  , "L3DoubleMuOpen_M2to4p5"}, 
//		{ "HLT_HIL3DoubleMu0_M2to4p5_Open_minN1minNhits1_v"  , "L3DoubleMuOpen_M2to4p5_minNhits1"}, 
//		{ "HLT_HIL3DoubleMu0_M7to15_Open_v"  , "L3DoubleMuOpen_M7to15"}, 
//		{ "HLT_HIL3DoubleMu0_Quarkonia_Open_v"  , "L3DoubleMuOpen_Quarkonia"}, 
//		{ "HLT_HIL3DoubleMu0_Quarkonia_LowMpT2_Open_v"  , "L3DoubleMuOpen_Quarkonia_LowMpT2"}, 
//		{ "HLT_HIL2DoubleMu0_M1to6p5_Open_v"  , "L2DoubleMuOpen_M1to6p5"}, 
//		{ "HLT_HIL2DoubleMu0_M6p5to16_Open_v"  , "L2DoubleMuOpen_M6p5to16"}, 
//		{ "HLT_HIL2DoubleMu0_M1to16_Open_v"  , "L2DoubleMuOpen_M1to16"}, 
//
//		{ "HLT_HIL2SingleMu3_Open_v", ""}, 
//		{ "HLT_HIL3SingleMu3_Open_v", ""}, 
//		{ "HLT_HIL2SingleMu5_Open_v", ""}, 
//		{ "HLT_HIL3SingleMu5_Open_v", ""}, 
//		{ "HLT_HIL2SingleMu7_Open_v", ""}, 
//		{ "HLT_HIL3SingleMu7_Open_v", ""}, 

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
//	ROOT::EnableImplicitMT(80);
	ROOT::TThreadExecutor mpe(UseNCores);

	//Define cuts
	std::vector<double> cuts;
	for(auto idx : ROOT::TSeqI(31)){
		cuts.push_back(0.5 *(double) idx);
	}

	//Run calculator
	long max_events = 1.0e+06;
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
