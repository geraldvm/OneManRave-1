#define L 0
#define R 1

bool ReadFFT() {

  if (Lfft.available() && Rfft.available()) {                               // every bin (in parens) is 43 hertz.  

    levels[L][0] = Lfft.read(0);         levels[R][0] = Rfft.read(0);       //0 - 43HZ
    levels[L][1] = Lfft.read(1);         levels[R][1] = Rfft.read(1);       // 43 - 86 HZ  
    levels[L][2] = Lfft.read(2, 3);      levels[R][2] = Rfft.read(2, 3);    
    levels[L][3] =  Lfft.read(4, 6);     levels[R][2] = Rfft.read(4, 6);    // start combining more bins into one band
    levels[L][4] = Lfft.read(7, 10);     levels[R][4] = Rfft.read(7, 10);   
    levels[L][5] = Lfft.read(11, 15);    levels[R][5] = Rfft.read(11, 15);
    levels[L][6] =  Lfft.read(16, 22);   levels[R][6] =  Rfft.read(16, 22);
    levels[L][7] =  Lfft.read(23, 32);   levels[R][7] =  Rfft.read(23, 32);
    levels[L][8] =  Lfft.read(33, 46);   levels[R][8] =  Rfft.read(33, 66);
    levels[L][9] =  Lfft.read(47, 66) ;  levels[R][9] =  Rfft.read(67, 131) ;
    levels[L][10] = Lfft.read(67, 93) ;  levels[R][10] = Rfft.read(132, 257) ;
    levels[L][11] = Lfft.read(94, 131);  levels[R][11] = Rfft.read(258, 511) ;   // tops out at 22000hz
    return true;
  }
  else {
    return false;
  }
}
