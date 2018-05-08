for i=1:21
    name = strcat(num2str(i),'.wav');
    [voice,fs,nBit] = wavread(name);
    figure(i)
    PitchFreq(voice,fs,nBit);
end