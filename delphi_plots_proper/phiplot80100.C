/*
How to run this code:
Copy it to the same folder as the 13TeV_CR0_RHoff.root file
From your terminal navigate to the same folder and type
root phiplot.C

This code solves for
-maximum pT value for the multiplicity class 0-20 in the dataset 13TeV_CR0_RHoff.root
-corresponding ntrack for the maximum pT value
-corresponding phi value for the maximum pT value
-Plots a 1D histogram of the absolute difference between each phi value and the
phi value corresponding to maximum pT.
*/

void phiplot80100()
{
  TFile *f = new TFile("13TeV_CR0_RHoff.root"); //opens file 13TeV_CR0_RHoff.root
  TTree *tree = (TTree*)f->Get("pytree80100"); //opens tree of multiplicity class 20-40
  Int_t entries = tree->GetEntries(); /*gets no. of entries in the tree (total
                                        occurences of ntrack)*/

  const Int_t maxTrack = 200;

  Int_t ntrack = 0; //declares and initialises ntrack value to 0
  Double_t pT[maxTrack]; //declaring arrays of maximum ntrack value length
  Double_t eta[maxTrack];
  Double_t rap[maxTrack];
  Double_t phi[maxTrack];

  //setting the branches for each variable we declared previously
  tree->SetBranchAddress("ntrack",&ntrack);
  tree->SetBranchAddress("phi",&phi);
  tree->SetBranchAddress("pT",&pT);
  tree->SetBranchAddress("eta",&eta);

  //initialising the variables for maximum pT and corresponding ntrack
  // and corresponding phi value for that maximum pT
  Double_t maxpt = 0;
  //Int_t maxptntrk = 0;
  Double_t phimax = 0;

  //creating a canvas for the histogram of size 500px * 500px
  TCanvas *c1 = new TCanvas("c1", "Delta Phi distribution", 900, 750);

  //declaring a histogram with 125 bins, and X axis range from 0 to Pi
  TH1D *delphi = new TH1D("delphi", "Delta Phi dist", 125, 0, TMath::Pi());
  Double_t dphi = 0; //declaring variable to store difference in phi

  for(Int_t i = 0; i<entries; i++) //going through all ntrack entries
  {
    tree->GetEntry(i); //getting all values of ntrack, phi, eta and pT for that entry
    maxpt = 0;
    phimax = 0;
    for(Int_t j = 0; j<ntrack; j++) //going through all ntracks in that entry
    {
      if(pT[j]>maxpt) //finding max value of pT in the multiplicity class
      {
        maxpt = pT[j];
        phimax = phi[j];
      }
    }
    for(Int_t j = 0; j<ntrack; j++)
    {
      dphi = abs(phimax - phi[j]); //dphi is absolute difference between phi[j] and phimax
      if(dphi>TMath::Pi()){
        dphi = 2*TMath::Pi() - dphi; /*if the difference goes over 2pi then we
        bring it back to range (0 to pi)*/
      }
      //Double_t dphi = abs(phi[j] - phimax);
      if(dphi != 0)
      {
        delphi->Fill(dphi);
      }
    }



  }

  delphi->SetTitle("|#Delta#phi| distribution for 80-100 class");
  //delphi->SetTitleSize(20);
  delphi->SetStats(0);
  delphi->GetXaxis()->SetTitle("|#Delta#phi| (radians)");
  delphi->GetXaxis()->CenterTitle();
  delphi->GetYaxis()->SetTitle("Counts");
  delphi->GetYaxis()->CenterTitle();

  //Double_t factor = 1.;
  //delphi->Scale(factor/delphi->GetMaximum());
  //delphi->GetYaxis()->SetRangeUser(0,1);
  //Double_t scale = delphi->GetXaxis()->GetBinWidth(1)/(delphi->Integral());
  //delphi->Scale(scale);
  ////////////////////////////DRAWING///////////////////////////

  delphi -> Draw("HIST");

  ////////////////////////////DRAWING///////////////////////////

  c1->SaveAs("delphi80100.pdf");


  //printing out the three values (for checking)
  //std::cout<<"max pt = "<<maxpt<<endl<<"corres ntrack = "<<maxptntrk<<endl;
  //std::cout<<"corres phi = "<<phimax<<endl;
  /*
  for(Int_t i = 0; i<entries; i++)
  {
    tree->GetEntry(i); //getting all values of ntrack, phi, eta and pT for that entry

    for(Int_t j = 0; j<ntrack; j++)
    {
      dphi = abs(phi[j] - phimax); //dphi is absolute difference between phi[j] and phimax
      if(dphi>TMath::Pi()){
        dphi = 2*TMath::Pi() - dphi; //if the difference goes over 2pi then we
        //bring it back to range (0 to pi)
      }
      //Double_t dphi = abs(phi[j] - phimax);
      delphi->Fill(dphi); //filling the histogram with the dphi values
    }
  }
  delphi->Draw(); //drawing the histogram
  */
}
