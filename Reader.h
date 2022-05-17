#pragma once
#define READER_H

#include "TFile.h"
#include "TTree.h"
#include <map>
#include <functional>

struct content{
	double val;
	TLorentzVector mu;
	TLorentzVector mu2;
	TLorentzVector dmu;
};
using EventData=std::unordered_map<std::string, content>;

class readerHlt;
class readerOnia;
class EffCalc;

class readerBase
{
	public :
		readerBase(){};
		~readerBase();
		readerBase( std::string name_file );
//		readerBase( TFile* _file ){ 
//			file = _file; 
//		};

		void setTree( std::string name_tree, std::string name_alias ="" );

	protected :
		bool checkBranch( std::string name_tree, std::string name_branch );

	private :
		TFile* file;
		std::map< std::string, TTree*> map_tree;

	friend readerHlt;
	friend readerOnia;
	friend EffCalc;
};

class readerHlt : public readerBase 
{

	public :
		readerBase base;
		readerHlt() : readerBase() {};
		~readerHlt();
		readerHlt( std::string name_file );
		
		void registerTrig( std::string name_trig, std::string name_base_trig = "" );
	
		std::vector<EventData> getEventContent();
		EventData getEventPrimitive();
//		EventData getCandsContent();
		UInt_t GetEventNb(){ return eventNb; };
		int GetEntry( int idx ){
			return base.map_tree["HltTree"]->GetEntry(idx);
		};

		bool isDerived;
	protected :


	private :
		bool triggered;
		std::vector<Float_t> *pts, *etas, *phis, *masses;
		Float_t pt, eta, phi, mass;
		Int_t runNb;
		ULong64_t eventNb;
};

class readerOnia : public readerBase 
{

	protected :

		static constexpr int maxArraySize = 100;
		static constexpr int maxCloneArraySize = 32000;

	public :

		UInt_t eventNb;
		Int_t Centrality;
		Float_t SumET_HF;

		long totQQ = 0;

		Short_t Reco_mu_size;
		Short_t Reco_mu_whichGen[maxArraySize];
		Short_t Reco_QQ_size;
		Short_t Reco_QQ_mupl_idx[maxArraySize];
		Short_t Reco_QQ_mumi_idx[maxArraySize];
		Int_t Reco_mu_nTrkWMea[maxArraySize];
		Int_t Reco_mu_nPixWMea[maxArraySize];
		Int_t Reco_mu_SelectionType[maxArraySize];
		Float_t Reco_mu_dxy[maxArraySize];
		Float_t Reco_mu_dz[maxArraySize];
		Float_t Reco_QQ_VtxProb[maxArraySize];
		TClonesArray* Reco_QQ_4mom;
		TClonesArray* Reco_mu_4mom;
		TClonesArray* Reco_mu_L1_4mom;
//			Reco_mu_4mom = new TClonesArray("TLorentzVector", maxArraySize);
//			Reco_QQ_4mom = new TClonesArray("TLorentzVector", maxArraySize);
//			Reco_mu_L1_4mom = new TClonesArray("TLorentzVector", maxArraySize);

		readerBase base;
		readerOnia() : readerBase() {};
		~readerOnia();
		readerOnia( std::string name_file );

		int GetEntryWithIndex( int evtNb ) {
//			if(Reco_mu_4mom == nullptr)Reco_mu_4mom = new TClonesArray("TLorentzVector", maxCloneArraySize);
//			if(Reco_QQ_4mom == nullptr)Reco_QQ_4mom = new TClonesArray("TLorentzVector", maxCloneArraySize);
//			if(Reco_mu_L1_4mom == nullptr)Reco_mu_L1_4mom = new TClonesArray("TLorentzVector", maxCloneArraySize);
			int x = base.map_tree["myTree"]->GetEntryWithIndex(evtNb);
			return x;
		};
//		void init;

		std::vector<EventData> getEventContent( bool getDimu, bool isL1 );
		std::vector<EventData> getMuonsContent( bool getDimu, bool isL1 );

		void checkArray( );


};

