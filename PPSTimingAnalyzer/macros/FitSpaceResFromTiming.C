/*
 * PPS timing resolution fits. Simple binned with 2 Gaussians, 1 for signal and 1 for background
 */
void FitSpaceResFromTiming(Int_t bkgmode = 0)
{
  TFile *f1 = TFile::Open("OuptutTimingHistograms.root");

  TH1F *h1;
  h1 = (TH1F *)f1->Get("zminustimediff");

  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  c1->SetLeftMargin(0.18);
  c1->SetRightMargin(0.08);
  c1->SetBottomMargin(0.12);

  h1->SetLineWidth(3); h1->SetLineColor(1); h1->SetMarkerStyle(20);
  h1->SetBinErrorOption(TH1::kPoisson);

  h1->SetYTitle("Events");
  h1->SetXTitle("z_{PPS, timing} - z_{vertex} [cm]");
  //  h1->SetStats(11111111);
  h1->SetStats(0);
  h1->Draw("E0");
  h1->Rebin(5);

  h1->GetXaxis()->SetTitleSize(0.05);
  h1->GetYaxis()->SetTitleSize(0.05);
  h1->GetXaxis()->SetLabelSize(0.05);
  h1->GetYaxis()->SetLabelSize(0.05);

  // Note - inital values and ranges are just copied from the 2018 study
  TF1 *fit1 = new TF1("fit1", "gaus(0)+gaus(3)",-1.5,1.5);
  fit1->SetParameter(0,200);
  fit1->SetParLimits(0,1,20000);
  fit1->SetParameter(1,0);
  fit1->SetParLimits(1,-3,3);
  fit1->SetParameter(2,2);
  fit1->SetParLimits(2,0,10);

  fit1->SetParameter(3,200);
  fit1->SetParLimits(3,1,5000);

  // Leave bkg shape freely floating within large range
  if(bkgmode == 0)
    {
      fit1->SetParameter(4,0);
      fit1->SetParLimits(4,-3,3);
      fit1->SetParameter(5,5);
      fit1->SetParLimits(5,0,10);
    }
  // Constrain bkg shape from event mixing sample - both arms                                                                                                                                           
  // Values are copied from 2018 study
  if(bkgmode == 1)
    {
      fit1->SetParameter(4,1.75888e-01);
      fit1->SetParLimits(4,1.75888e-01-1.07269e-01,1.75888e-01 + 1.07269e-01);
      fit1->SetParameter(5,6.13935e+00);
      fit1->SetParLimits(5,6.13935e+00-7.77560e-02, 6.13935e+00 + 7.77560e-02);
    }
  // Constrain bkg shape from event mixing sample - single arm mixed                                                                                                                                    
  // Values are copied from 2018 study                                                                                                                                                                  
  if(bkgmode == 2)
    {
      fit1->SetParameter(4,8.82919e-02);
      fit1->SetParLimits(4,8.82919e-02 - 8.11096e-02,8.82919e-02 + 8.11096e-02);
      fit1->SetParameter(5,5.13337e+00);
      fit1->SetParLimits(5,5.13337e+00 - 6.19168e-02,5.13337e+00 + 6.19168e-02);
    }

  fit1->SetParName(0,"Signal norm.");
  fit1->SetParName(1,"Signal mean");
  fit1->SetParName(2,"Signal width");
  fit1->SetParName(3,"Bkg. norm.");
  fit1->SetParName(4,"Bkg. mean");
  fit1->SetParName(5,"Bkg. width");
  
  TFitResultPtr fitr = h1->Fit("fit1","LEMVS","",-20,20);
  TF1 *fit1bkg = new TF1("fit1bkg","gaus(0)",-20,20);
  fit1bkg->SetParameter(0,fit1->GetParameter(3));
  fit1bkg->SetParameter(1,fit1->GetParameter(4));
  fit1bkg->SetParameter(2,fit1->GetParameter(5));
  if(bkgmode == 0)
    fit1bkg->SetLineColor(4); 
  if(bkgmode == 1 || bkgmode == 2)
    fit1bkg->SetLineColor(8);

  fit1bkg->SetLineWidth(3); fit1bkg->SetLineStyle(2); fit1bkg->Draw("same"); fit1->Draw("same");

  TF1 *fit1sig = new TF1("fit1sig","gaus(0)",-20,20);
  fit1sig->SetParameter(0,fit1->GetParameter(0));
  fit1sig->SetParameter(1,fit1->GetParameter(1));
  fit1sig->SetParameter(2,fit1->GetParameter(2));
  fit1sig->SetLineColor(2); fit1sig->SetLineWidth(3); fit1sig->SetLineStyle(2); fit1sig->Draw("same"); //fit1->Draw("same");                              

  fit1->SetLineWidth(3); fit1->SetMarkerSize(0);
  fit1bkg->SetLineWidth(3); fit1bkg->SetMarkerSize(0);
  fit1sig->SetLineWidth(3); fit1sig->SetMarkerSize(0);


  TLegend *l1 = new TLegend(0.63,0.5,0.92,0.9);
  l1->AddEntry(h1,"Data");
  l1->AddEntry(fit1,"Total fit");
  l1->AddEntry(fit1sig,"Signal");
  l1->AddEntry(fit1bkg,"Background");
  l1->SetTextSize(0.035);
  l1->SetMargin(0.15);
  l1->Draw("same");

  
  std::cout << "Signal integral = " << fit1sig->Integral(-20,20) << std::endl;
  std::cout << "Background integral = " << fit1bkg->Integral(-20,20) << std::endl;
}
