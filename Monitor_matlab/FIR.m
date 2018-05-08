function [ FIRVoice ] = FIR( voice, fs, nBit, lowBound)
%FIR Low pass filter (For this system, we're interested in voice<3000Hz)
%   input: voice data
%   input: sample rate
%   input: number of bits per sample
%   input: low pass bound
%   output: filtered voice data

    voice=voice(:,1);

    %µÍÍ¨¼ÓHanmming
    fp0 = lowBound;
    fc0 = lowBound+500;        
    wp = 2*pi*fp0/fs;
    ws = 2*pi*fc0/fs;
    Bt = ws-wp;               
    N0 = ceil(11*pi/Bt);     
    N = N0+mod(N0+1,2);
    wc = (wp+ws)/2/pi;         
    hn = fir1(N-1,wc,hamming(N));
    [h,w] = freqz(hn);
    FIRVoice = conv(hn,voice);

end

