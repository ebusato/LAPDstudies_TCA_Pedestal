
void SRout() {
  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);

  TFile* f = new TFile("/home/ebusato/Travail/gowork2/src/gitlab.in2p3.fr/avirm/analysis-go/dpgatca/godaq/file.root", "read");
  f->Print();
  TTree* t = (TTree*) f->Get("tree");

  /////////////////////////////////////////////
  // Implement conversion to in automatically
  TString noPulse("8");
  int noPulseI(8);
  /////////////////////////////////////////////

  TCanvas* c = new TCanvas("c", "c", 1200, 1200);
  int nrows = 6;
  int ncols = 3;
  c->Divide(ncols,nrows);
  int j=1;
  for(int i=1; i<=nrows; i++) {
    TString cut("Evt == ");
    cut+=i*10;
    //cut+=i*1;
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
    t->Draw("Pulse["+noPulse+"]:CapaId["+noPulse+"]", cut.Data());
    TLine* line = new TLine(SRout, 0, SRout, 500);
    line->Draw();
    PutText(0.5, 0.9, kBlack, cut.Data(), 0.07); 
    PutText(0.65, 0.9, kBlack, SRoutString.Data(), 0.07);
    j+=3;
  }
}
