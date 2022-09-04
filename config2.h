#pragma once
#include "pset.h"
#include "util.h"
#include "Reader.h"
#include "EffCalc.h"
#include "ObjectTree.h"

#define GLB_DPT_CUT "On"


//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_JPsi_pTHat2_v1_9.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_JPsi_pTHatMin2_CMSSW_12_3_0.root";
//	string file_output = Form("output_pTHat2_JPsi_v3_9_GenMatched_hltMassCut_dPt_%s_v2.root", GLB_DPT_CUT);
//	unsigned int dType = kMCJP; string tag = "JPsi";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {2.6, 3.5}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {1., 6.5}},
//		{3, {2., 4.5}},
////		{1, {0., 9999.}},
////		{2, {0., 9999.}},
////		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "JPsi/v3_9_Gen_v2";

	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_JPsiEMB_pTHat2_v1_9.root";
	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_JPsiEMB_pTHatMin2_MuonSelAll_CMSSW_12_3_0.root";
	string file_output = Form("output_pTHat2_JPsiEMB_v3_9_GenMatched_hltMassCut_dPt_%s_v1_SameDRDPTL3.root", GLB_DPT_CUT);
	unsigned int dType = kMCJP; string tag = "JPsi";
	std::map<string, std::pair<double, double> > oniaFilter{{"m", {2.6, 3.5}} };
	std::map<int, std::pair<double, double> > hltFilter{ 
		{1, {0., 9999.}},
		{2, {1., 6.5}},
		{3, {2., 4.5}},
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
	} ;
	static string SUBDIR= "JPsiEMB/v3_9_Gen_sameDelta";






//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_Upsilon_v1_9.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_Upsilon_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = Form("output_UPsi_v3_9_GenMatched_hltMassCut_dPt_%s_v1.root", GLB_DPT_CUT);
//	unsigned int dType = kMCUp; string tag = "Upsi";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0., 999.0}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
////		{1, {0., 9999.}},
////		{2, {1., 6.5}},
////		{3, {2., 4.5}},
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "Upsi/v3_9_Gen";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_UpsilonEMB_v1_9.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_UpsilonEMB_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = Form("output_UPsiEMB_v3_9_GenMatched_hltMassCut_dPt_%s_v1.root", GLB_DPT_CUT);
//	unsigned int dType = kMCUp; string tag = "UPsi";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0., 999.0}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
////		{1, {0., 9999.}},
////		{2, {1., 6.5}},
////		{3, {2., 4.5}},
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "UpsiEMB/v3_9_Gen";



//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_ZBoson_v1_9.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_Zboson_CMSSW_12_4_7_220825.root";
//	string file_output = Form("output_ZBoson_v3_9_GenMatched_hltMassCut_dPt_%s_v1.root", GLB_DPT_CUT);
//	unsigned int dType = kMCmuLoose; string tag = "ZBoson";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0., 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
////		{1, {0., 9999.}},
////		{2, {1., 6.5}},
////		{3, {2., 4.5}},
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "ZBoson/v3_9_Gen";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_Data_v1_9.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_miniAOD_HIMBPD2_FullRun_MuonNoSel.root";
//	string file_output = Form("output_Data_v3_9_GenMatched_hltMassCut_dPt_%s_v1.root", GLB_DPT_CUT);
//	unsigned int dType = kData; string tag = "Data";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0., 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
////		{1, {0., 9999.}},
////		{2, {1., 6.5}},
////		{3, {2., 4.5}},
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "Run2MB/v3_9";
