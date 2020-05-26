{
   TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,500,500);
#define n 50000
   Double_t x[n], y[n];
   double sx=0,sy=0;
   double A=(sqrt(5)+1.0)/2/6;
   double B=3.14159265/4;
   for (Int_t i=0;i<n;i++) {
     x[i] = sx;
     y[i] = sy;
     sx=sx+A;
     sy=sy+B;
     if(sx>2) sx=sx-2;
     if(sy>2) sy=sy-2;
   }
   TGraph* gr = new TGraph(n,x,y);
   gr ->Draw("AP");
}

