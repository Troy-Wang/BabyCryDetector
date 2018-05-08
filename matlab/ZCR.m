function [ feature_ZCR ] = ZCR( voice, fs, nBit )
%ZCR Calc Zero-crossing Rate
%   input: voice data
%   input: sample rate
%   input: number of bits per sample
%   output: zero-cross rate feature of the voice data

    disp('Feature ZCR');
    frameLength = 20*0.001*fs; %frame length
    frameInc = frameLength/2;   %frame inc
    voiceFrames = enframe(voice, frameLength, frameInc);
    
    zcr=zcro(voiceFrames);
    feature_ZCR = mean(zcr(zcr~=0));
    
%     plot(zcr);
%     disp(mean(zcr));
%     xlabel('Frame Num');
%     ylabel('ZCR');
%     title(mean(zcr));

end

