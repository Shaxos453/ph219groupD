void sum_pT_plot()
{
  TFile *f = new TFile("13TeV_CR0_RHoff.root"); //opens file 13TeV_CR0_RHoff.root
  TTree *tree = (TTree*)f->Get("pytree2040"); //opens tree of multiplicity class 20-40
  Int_t entries = tree->GetEntries(); /*gets no. of entries in the tree (total
                                        occurences of ntrack)*/

  const Int_t maxTrack = 40; //sets maximum number of tracks to 40
  //since the max number of tracks in this multiplicity class 20-40 is 40

  Int_t ntrack = 0; //declares and initialises ntrack value to 0
  Double_t pT[maxTrack]; //declaring arrays of maximum ntrack value length
  Double_t eta[maxTrack];
  Double_t phi[maxTrack];

  //setting the branches for each variable we declared previously
  tree->SetBranchAddress("ntrack",&ntrack);
  tree->SetBranchAddress("phi",&phi);
  tree->SetBranchAddress("pT",&pT);
  tree->SetBranchAddress("eta",&eta);

  //initialising the variables for maximum pT and corresponding ntrack
  // and corresponding phi value for that maximum pT
  Double_t maxpt = 0;
  Double_t phimax = 0;
  Double_t sum_pT=0;
  Double_t dphi = 0; //declaring variable to store difference in phi


  //creating a canvas for the histogram of size 500px * 500px
  TCanvas *c2 = new TCanvas("c2", "Average number density for toward region", 500, 500);

  //declaring a histogram with 125 bins, and X axis range from 0 to Pi
  TH2D * d2_sum_pT = new TH2D("d2N", "Avg. number density",20,0,5,20,0,4);
  for(Int_t i = 0; i<entries; i++) //going through all ntrack entries
  {
    tree->GetEntry(i); //getting all values of ntrack, phi, eta and pT for that entry
    maxpt = 0;
    phimax = 0;
    sum_pT=0;
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
        if(dphi>TMath::Pi())
        {
            dphi = 2*TMath::Pi() - dphi; /*if the difference goes over 2pi then we
            bring it back to range (0 to pi)*/
        }
        if(dphi<TMath::Pi()/3)
        {
            sum_pT+=pT[j];
        }  
    }
    sum_pT=sum_pT/(5*TMath::Pi()/3);
    
    d2_sum_pT->Fill(maxpt,sum_pT);
}
  d2_sum_pT->Draw("LEGO");
  
}