function [gData ovrn] = read_adxl345_log_bin_2byte(fname)

  fid = fopen(fname, "r");

  # Read header
  hdrId = fread(fid, 1, "uint32");
  
  if (hdrId == 0x4C4F4748) # 'LOGH', little endian
    hdrVer = fread(fid, 1, "uint32");
    hdrSize = fread(fid, 1, "uint32");
    
    printf("Header detected, Ver:%d, Size:%d\n", hdrVer, hdrSize);

    if(hdrVer == 1)
      hdrRate = fread(fid, 1, "uint32");
      hdrRange = fread(fid, 1, "uint32");
      
      rateCodes = [0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,  ...
                   0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF];
      rateVals = [0.1, 0.2, 0.39, 0.78, 1.56, 3.13, 6.5, 12.5,  ...
                  25, 50, 100, 200, 400, 800, 1600, 3200]; # Measure frequency in Hz
      
      rangeCodes = [0x0, 0x1, 0x2, 0x3];
      rangeVals = [2.0, 4.0, 8.0, 16.0]; # Measure range in G

      rate = rateVals(find(rateCodes == hdrRate)(1));
      range = rangeVals(find(rangeCodes == hdrRange)(1));
      
      dt = 1 / rate;
      gUnit = range * 2 / 1024.0; # 10bit ADC, -range ~ +range
      
      printf("Rate:%d[Hz], Range:%d[G]\n", rate, range);
      
    endif
    
    dataTop = 12 + hdrSize;
    
  else # Header was not detected
    dt = 1;
    gUnit = 0.004; # 4mg/LSB
    fseek(fid, 0, SEEK_SET);
    dataTop = 0;
    
    printf("Header was not detected\n");
  endif

  # Data body
  gData = fread(fid, Inf, "int16", 2);
  gData = [dt*[1:size(gData)(1)].', gUnit*gData];
    # gData(:,1) : Time
    # gData(:,2) : Acceleration
  fseek(fid, dataTop + 2, SEEK_SET);
  ovrn = fread(fid, Inf, "int16", 2);
  fclose(fid);
endfunction
