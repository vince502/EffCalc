#pragma once
#include "pset.h"
#include "util.h"
#include "Reader.h"
#include "EffCalc.h"
#include "ObjectTree.h"

#define GLB_DPT_CUT "Off"
	std::map<string, std::pair<double, double> > oniaFilterJPsi{{"m", {2.6, 3.5}} };
	std::map<string, std::pair<double, double> > oniaFilterUpsilon{{"m", {8.5,10.5}} };
	std::map<int, std::pair<double, double> > hltPtFilter{
		{1, { 0., 0.}},
		{2, { 2.8, 2.8}},
		{3, { 2., 2.}},
	};

/***************************************************************************************

	string file_name_hlt = "/home/CMS/soohwan/store/HLT/CMSSW_13X/openHLT_SimuHJ2.root"; // FinalFilter MinN = 0 
	string file_name_onia = "/home/CMS/soohwan/store/OniaTree/Oniatree_SingleMu_1320pre2.root";
//	string file_output = Form("output_CMSSW132_FilterNotModified_pTHat2_JPsiEMB_v1_0_GenMatched_hltMassCut_dPt_%s_v1_iter1_part1.root", GLB_DPT_CUT);
	string file_output = Form("output_CMSSW132_FilterMinN0_pTHat15_SiMuEMB_v1_0_GenMatched_hltMassCut_dPt_%s_v1_iter1_part1.root", GLB_DPT_CUT);
	unsigned int dType = kMCmu; string tag = "Z";

	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0., 999.}} };
	std::map<int, std::pair<double, double> > hltFilter{ 
		{1, {0., 9999.}},
		{2, {0., 9999.}},
		{3, {0., 9999.}},
	} ;
	static bool useNColl = false;
	static bool offlineSel = kSoft; 
	static string SUBDIR= "PbPb2023/SimuMBCMSSW132_5p36TeV/v0_1_Gen_1";

***************************************************************************************

	//string file_name_hlt = "/home/CMS/soohwan/store/HLT/CMSSW_13X/openHLT_JpsiHJ_wL1Simu.root"; // FinalFilter MinN = 0 
//	string file_name_hlt = "/home/CMS/soohwan/store/HLT/CMSSW_13X/openHLT_JpsiHJ2.root"; // Dimu L3 : L1 dR 0.3 -> 0.6 
	string file_name_hlt = "/home/CMS/soohwan/store/HLT/CMSSW_13X/openHLT_JpsiHJ5.root"; // Dimu L3 : L1 NHit 10 -> 3
	string file_name_onia = "/home/CMS/soohwan/store/OniaTree/Oniatree_MC_JpsiEMB_miniAOD.root";
//	string file_output = Form("output_CMSSW132_FilterNotModified_pTHat2_JPsiEMB_v1_0_GenMatched_hltMassCut_dPt_%s_v1_iter1_part1.root", GLB_DPT_CUT);
	string file_output = Form("output_CMSSW132_pTHat2_JpsiEMB_trig_v5_4_6_dPt_%s_v4.root", GLB_DPT_CUT);
	unsigned int dType = kMCJP; string tag = "JPsi";

	std::map<string, std::pair<double, double> > oniaFilter{{"m", {2.6, 3.5}} };
	std::map<int, std::pair<double, double> > hltFilter{ 
		{1, {0., 9999.}},
		{2, {0., 9999.}},
		{3, {0., 9999.}},
	} ;
	static bool useNColl = false;
	static bool offlineSel = kSoft; 
	static string SUBDIR= "PbPb2023/JPsiHydjetCMSSW132_5p36TeV/v0_1_Gen_1";

***************************************************************************************/

	string file_name_hlt = "/home/CMS/soohwan/store/HLT/CMSSW_13X/openHLT_jpsi_new_ppref.root"; // FinalFilter MinN = 0 
	string file_name_onia = "/home/CMS/soohwan/store/OniaTree/OniaTree_Jpsi_pp_1321.root";
//	string file_output = Form("output_CMSSW132_FilterNotModified_pTHat2_JPsiEMB_v1_0_GenMatched_hltMassCut_dPt_%s_v1_iter1_part1.root", GLB_DPT_CUT);
	string file_output = Form("output_CMSSW132_pTHat2_JpsiPPRef_trig_v4_19_dPt_%s_v3.root", GLB_DPT_CUT);
	unsigned int dType = kMCJP; string tag = "JPsi";

	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0, 9999.}} };
	std::map<int, std::pair<double, double> > hltFilter{ 
		{1, {0., 9999.}},
		{2, {0., 9999.}},
		{3, {0., 9999.}},
	} ;
	static bool useNColl = false;
	static bool offlineSel = kSoft; 
	static string SUBDIR= "PbPb2023/JPsiHydjetCMSSW132_5p36TeV/v0_1_Gen_1";


/***************************************************************************************/
