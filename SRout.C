
TGraph *PlotPulse(TTree* t, int noPulse, TString cutEvt, int color, TString xAxis)
{TString toDraw = "";
  if(xAxis.Contains("CapaId")) {
    toDraw = Form("Pulse[%i]:%s[%i]", noPulse, xAxis.Data(), noPulse);
  }
  else {
    toDraw = Form("Pulse[%i]:%s", noPulse, xAxis.Data());
  }
  cout << "toDraw = " << toDraw << endl;
  int n = t->Draw(toDraw, cutEvt.Data(), "goff");
  TGraph* g = new TGraph(n, t->GetV2(), t->GetV1());
  g->SetLineColor(color);
  g->SetMarkerColor(color);
  g->SetLineWidth(1);
  return g;
}

TMultiGraph* DrawMultiGraph(TTree* t, int noPulseStart, TString cutEvt, TString xAxis)
{
  TGraph *g0 = PlotPulse(t, noPulseStart, cutEvt, kRed, xAxis);
  TGraph *g1 = PlotPulse(t, noPulseStart+1, cutEvt, kGreen+2, xAxis);
  TGraph *g2 = PlotPulse(t, noPulseStart+2, cutEvt, kBlue, xAxis);
  TGraph *g3 = PlotPulse(t, noPulseStart+3, cutEvt, kMagenta, xAxis);
  TMultiGraph* multi = new TMultiGraph();
  multi->Add(g0);
  multi->Add(g1);
  multi->Add(g2);
  multi->Add(g3);
  multi->Draw("apl");
  TString text = Form(", Quartet=%i", noPulseStart/4);
  PutText(0.45, 0.9, kBlack, (cutEvt+text).Data(), 0.07);
  t->Scan(Form("SRout[%i]", noPulseStart), cutEvt.Data());
  int SRout = t->GetLeaf("SRout")->GetValue(noPulseStart);
  PutText(0.2, 0.8, kBlack, Form("SRout=%i", SRout), 0.07);
  return multi;
}

void SRout(int Evt, TString xAxis="SampleTimes") {
  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);

  TFile* f = new TFile("port06datas/run_500spls/MyFile_enp0s31f6@0_0.root", "read");
  f->Print();
  TTree* t = (TTree*) f->Get("tree");

  ////////////////////////////////////////////
  // Plot pulses for one event
  TCanvas *cEvt = new TCanvas(Form("cEvt_%i_%s", Evt, xAxis.Data()), Form("cEvt_%i_%s", Evt, xAxis.Data()), 1200, 1000);
  cEvt->Divide(2,3);
  TString cutEvt = Form("Evt==%i", Evt);
  cEvt->cd(1);
  DrawMultiGraph(t, 0, cutEvt, xAxis);
  cEvt->cd(2);
  DrawMultiGraph(t, 4, cutEvt, xAxis);
  cEvt->cd(3);
  DrawMultiGraph(t, 8, cutEvt, xAxis);
  cEvt->cd(4);
  DrawMultiGraph(t, 12, cutEvt, xAxis);
  cEvt->cd(5);
  DrawMultiGraph(t, 16, cutEvt, xAxis);
  cEvt->cd(6);
  DrawMultiGraph(t, 20, cutEvt, xAxis);
  ////////////////////////////////////////////

  /*
  /////////////////////////////////////////////
  // Implement conversion to int automatically
  TString noPulse("10");
  int noPulseI(10);
  /////////////////////////////////////////////

  TCanvas* c = new TCanvas("c", "c", 1200, 1200);
  int nrows = 6;
  int ncols = 3;
  c->Divide(ncols,nrows);
  int j=1;
  for(int i=2; i<=nrows; i++) {
    TString cut("Evt == ");
    //cut+=i*10;
    cut+=i*1;
    cout << cut << endl;
    c->cd(j);
    gPad->SetTopMargin(0);
    gPad->SetBottomMargin(0.15);
    t->Draw("Pulse["+noPulse+"]:SampleTimes", cut.Data());
    t->Scan("SRout["+noPulse+"]", cut.Data());
    int SRout = t->GetLeaf("SRout")->GetValue(noPulseI);
    cout << "SRout = " << SRout << endl;
    PutText(0.5, 0.9, kBlack, cut.Data(), 0.07);
    TString SRoutString("SRout=");
    SRoutString+=SRout;
    PutText(0.65, 0.9, kBlack, SRoutString.Data(), 0.07);
    c->cd(j+1);
    gPad->SetTopMargin(0);
    gPad->SetBottomMargin(0.15);
    t->Draw("Pulse["+noPulse+"]:SampleIndices", cut.Data());
    PutText(0.5, 0.9, kBlack, cut.Data(), 0.07); 
    PutText(0.65, 0.9, kBlack, SRoutString.Data(), 0.07);
    c->cd(j+2);
    gPad->SetTopMargin(0);
    gPad->SetBottomMargin(0.15);
    t->Draw("Pulse["+noPulse+"]:CapaId["+noPulse+"]", cut.Data(),"l");
    TLine* line = new TLine(SRout, 0, SRout, 500);
    line->Draw();
    PutText(0.5, 0.9, kBlack, cut.Data(), 0.07); 
    PutText(0.65, 0.9, kBlack, SRoutString.Data(), 0.07);
    j+=3;
  }
  */
}
