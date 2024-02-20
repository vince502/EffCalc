from ROOT import TEfficiency, TFile, TDirectory, TCanvas, gStyle, TGraphAsymmErrors, TLegend, EColor, TMarker

canv_tmp = TCanvas("ctmp", "" ,700, 600);

x =  ( 0.5, 1., 1.5, 2., 2.1, 2.2, 2.3, 2.4, 2.5, 2.7, 2.8, 2.9, 3., 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4., 4.5, 5., 5.5, 6., 6.5, 7.)
x =  (-2.4, -2.1, -1.8, -1.5, -1., 0, 1, 1.5, 1.8, 2.1, 2.4)
#vcol = (EColor.kRed-9, EColor.kRed-4, EColor.kRed, EColor.kRed+2, EColor.kYellow -3, EColor.kYellow, EColor.kGreen, EColor.kGreen+1, EColor.kGreen+2, EColor.kAzure-4, EColor.kAzure+1, EColor.kAzure, EColor.kMagenta, EColor.kMagenta +1)
vcol = (EColor.kRed-9, EColor.kRed-4, EColor.kRed, EColor.kRed+2, EColor.kYellow -3, EColor.kYellow, EColor.kGreen, EColor.kGreen+1, EColor.kGreen+2, EColor.kAzure-4, EColor.kAzure+1, EColor.kAzure, EColor.kMagenta, EColor.kMagenta +1)
def getCol(i, j =2) :
    return vcol[i]
def getcolor(i, j =2) :
    return  99 - (i * 2)
def getcolorOne(i, j) :
    if ( i != j ) :
        return 17
    else :
        return 99 - ( i *2)

def DrawTrigPTSeq(trigDir, canv,  _leg = 0, _header = "", _pallet = getCol, _paux = 0) :
    canv.Clear();
    canv.SetGrid()
    canv.cd();
    # leg = TLegend(0.5, 0.2, 0.8, 0.45)
    _leg.SetBorderSize(0)
    _leg.SetNColumns(3)
    _leg.SetHeader( _header )
    first = True;
    ptmp = TGraphAsymmErrors()
    for i in reversed(range(len(x))):
        hist = trigDir.Get('pt_%dp%d' % (int(x[i]), int(10 *(x[i] - int(x[i]) ))))
        canv_tmp.cd()
        hist.Draw("AP")
        canv_tmp.Update()
        if( (hist.IsA()).GetName() == "TEfficiency") :
            hist = hist.GetPaintedGraph()
        canv.cd()
        hist.SetLineColor( _pallet(i, _paux) )
        hist.SetMarkerColor( _pallet(i, _paux) )
        hist.SetMarkerSize(marker_size)
        if( (i % 2) == 0) :
            hist.SetMarkerStyle(marker_style)
        if( (i % 2) == 1) :
            hist.SetMarkerStyle(marker_style2)
        hist.GetYaxis().SetRangeUser(range_do,range_up)
        hist.GetYaxis().SetNdivisions(int((range_up ) *10))
        hist.GetXaxis().SetRangeUser(0,50)
        hist.GetXaxis().SetNdivisions(25)
        hist.GetXaxis().SetTitle("p_{T} (GeV/c)")
        hist.GetYaxis().SetTitle("Efficiency")
        hist.Draw( "APL " if first else "PL ")
        if(_paux == i) :
            ptmp = hist
        leg.AddEntry(hist, "pt > %.1f" % x[i])
        first = False
    ptmp.Draw("PL")
    leg.DrawClone()
    canv.Draw()
    return canv, leg

def DrawTrigOne(trigDir, obj, canv, _and = False, _col = 221) :
    if not ( _and ) :
        canv.Clear();
    first = True;
    hist = trigDir.Get(obj)
#    canv_tmp.cd()
#    hist.Draw()
#    canv_tmp.Update()
    if( (hist.IsA()).GetName() == "TEfficiency") :
        canv_tmp.cd()
        hist.Draw()
        canv_tmp.Update()
        hist = hist.GetPaintedGraph()
    canv.cd()
    canv.Draw()
    col = _col
    if( _and ) : col = col-1
    hist.SetLineColor(col)
    hist.SetMarkerColor(col)
    hist.SetMarkerSize(marker_size)
    hist.SetMarkerStyle(marker_style)
    hist.GetYaxis().SetRangeUser(range_do,range_up)
    hist.GetYaxis().SetNdivisions(int((range_up - range_do) *10))
    hist.GetXaxis().SetRangeUser(0,50)
    hist.GetXaxis().SetNdivisions(25)
    hist.GetXaxis().SetTitle("p_{T} (GeV/c)")
    hist.GetYaxis().SetTitle("Efficiency")
    if( _and ) :
        print("and")
        hist.Draw( "PE" )
    else : 
        hist.Draw( "APE" )
    
    canv.Draw()
    return canv

def DrawTrigSeq(trigDir, obj, canv, _and = False, _col = 221, _leg = 0, _marker = 1, _disc = "", _pltmode = "") :
    if not ( _and ) :
        canv.Clear();
    first = True;
    hist = trigDir.Get(obj)
    if( (hist.IsA()).GetName() == "TEfficiency") :
        canv_tmp.cd()
        hist.Draw()
        canv_tmp.Update()
        hist = hist.GetPaintedGraph()
    canv.cd()
    canv.Draw()
    col = _col
    if( _and ) : col = col-1
    hist.SetLineColor(col)
    hist.SetMarkerColor(col)
    hist.SetMarkerSize(marker_size)
    hist.SetMarkerStyle(_marker)
    hist.GetYaxis().SetRangeUser(range_do,range_up)
    hist.GetYaxis().SetNdivisions(int((range_up)*10))
    hist.GetXaxis().SetRangeUser(0, 50)
    hist.GetXaxis().SetNdivisions(20)
    hist.GetXaxis().SetTitle("p_{T} (GeV/c)")
    if( _pltmode == 'Y' ):
        hist.GetXaxis().SetRangeUser(-2.4, 2.4)
        hist.GetXaxis().SetNdivisions(8)
        hist.GetXaxis().SetTitle("Rapidity/#eta")
    if( _pltmode == 'C' ):
        hist.GetXaxis().SetRangeUser(0, 200)
        hist.GetXaxis().SetNdivisions(20)
        hist.GetXaxis().SetTitle("Centrality (x2)")

    
    hist.GetYaxis().SetTitle("Efficiency")

    if( _leg != 0 ) :
        leg.AddEntry(hist, _disc)
    if( _and ) :
        hist.Draw( "PEL" )
    else : 
        hist.Draw( "APEL" )

    canv.Draw()
    if ( _leg == 0) :
        return canv, 0
    else :
        return canv, leg
