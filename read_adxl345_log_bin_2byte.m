
function [gData ovrn] = read_adxl345_log_bin_2byte(fname)

  # gData(:,1) : Time [s]
  # gData(:,2) : Acceleration [G]
  # gData(:,3) : Measure interval [s]

  fid = fopen(fname, "r");
  d = dir(fname);
  dataSize = d.bytes;

  ########################
  # Read header
  ########################
  hdrId = fread(fid, 1, "uint32");
  
  if (hdrId == 0x4C4F4748) # 'LOGH', little endian
    hdrVer = fread(fid, 1, "uint32");
    hdrSize = fread(fid, 1, "uint32");
    
    printf("Header detected, Ver:%d, Size:%d\n", hdrVer, hdrSize);

    if(hdrVer >= 1)
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

    if(hdrVer >= 2)
      intMeasureFreq = fread(fid, 1, "uint16");
      
      hdrIntMeasureClkDiv = fread(fid, 1, "uint16");
      switch(hdrIntMeasureClkDiv)
        case 0x0
          intMeasureClkDiv = 8;
        case 0x1
          intMeasureClkDiv = 32;
        case 0x2
          intMeasureClkDiv = 128;
        case 0x3
          intMeasureClkDiv = 512;
        otherwise
          intMeasureClkDiv = 8;
      endswitch

      intMeasureCntUnit = 50 * 10^-9 * intMeasureClkDiv; # 50 ns * (divide count)

    else
      # Interval count is not included in the log
      intMeasureFreq = 0;
      intMeasureCntUnit = 1;

    endif

    dataTop = 12 + hdrSize;
    dataSize -= 12 + hdrSize;

  else # Header was not detected
    dt = 1;
    gUnit = 0.004; # 4mg/LSB
    fseek(fid, 0, SEEK_SET);
    dataTop = 0;

    intMeasureFreq = 0;
    intMeasureCntUnit = 1;

    printf("Header was not detected\n");
  endif

  ########################
  # Read data body
  ########################
  if(intMeasureFreq == 0)
    gData = fread(fid, Inf, "int16", 2);
    gData = [dt*[1:size(gData)(1)].', gUnit*gData, dt];
      # gData(:,1) : Time [s]
      # gData(:,2) : Acceleration [G]
      # gData(:,3) : Measure interval [s]
    fseek(fid, dataTop + 2, SEEK_SET);
    ovrn = fread(fid, Inf, "int16", 2);

  else
    # Allocate data array (Reduced later)
    gData = zeros(dataSize/2/2, 3);
      # gData(:,1) : Time [s]
      # gData(:,2) : Acceleration [G]
      # gData(:,3) : Measure interval [s]
    ovrn = zeros(dataSize/2/2);

    p = 0;
    t = 0;
    while(1)
      # Get data unit from log file
      [d c] = fread(fid, 2, "int16=>int16");
      if(c != 2)
        break;
      endif

      ov = bitget(d(2),1);
      MsIntCnt = bitget(d(2),2);

      if(MsIntCnt == 1)
        # Update dt
        dt = double(d(1)) * intMeasureCntUnit / intMeasureFreq;
      else
        p++; # Increment in advance, finally p indicates the number of acceleration data
        gData(p,1) = t;
        gData(p,2) = d(1);
        gData(p,3) = dt;
        ovrn(p) = ov;
        t += dt;
      endif

    endwhile

    # Remove unnecessary area
    gData = gData(1:p,:);
    ovrn = ovrn(1:p);

  endif

  fclose(fid);


endfunction
